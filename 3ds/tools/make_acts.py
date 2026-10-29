#!/usr/bin/env python3
"""Genera las animaciones de ataque del jugador: romfs/gfx/pNNNN{a,h,c}[s].t3x e include/actmeta.h.

a = Attack, h = Shoot, c = Charge (la web elige una según el tipo de movimiento);
sufijo s = variante shiny. Rejilla: fotograma f en columna f, dirección en fila
(Abajo, Derecha, Arriba, Izquierda = filas 0,2,4,6 de la hoja original).
Se conservan como mucho NF fotogramas repartidos por toda la animación.

Uso (desde 3ds/):  python3 tools/make_acts.py     (requiere Pillow y tex3ds)
"""
import json, re, subprocess, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
ROWS = (0, 2, 4, 6)
ANIMS = (("Attack", "a"), ("Shoot", "h"), ("Charge", "c"))
NF = 6
POKE_MAX = 1100


def pot(v):
    p = 8
    while p < v:
        p *= 2
    return p


def load_meta():
    txt = (ROOT / "js/data/sprites-meta.js").read_text()
    return {int(d): json.loads(b) for d, b in re.findall(r"^\s*(\d+): (\{.*\}),?\s*$", txt, re.M)}


def pick(n, k):
    return list(range(n)) if n <= k else [round(i * (n - 1) / (k - 1)) for i in range(k)]


def build_anim(dn, m, name, suf, tmp):
    a = m["a"].get(name)
    path = ROOT / f"assets/pokemon/{dn}/{name}.png"
    if not a or not path.exists():
        return (0,) * 8
    fw, fh = a["w"], a["h"]
    sheet = Image.open(path).convert("RGBA")
    nf = NF
    while nf >= 3:
        idx = pick(a["n"], nf)
        frames = {(r, j): sheet.crop((f * fw, ROWS[r] * fh, (f + 1) * fw, (ROWS[r] + 1) * fh))
                  for r in range(4) for j, f in enumerate(idx)}
        bx0, by0, bx1, by1 = fw, fh, 0, 0
        for fr in frames.values():
            bb = fr.getbbox()
            if bb:
                bx0, by0, bx1, by1 = min(bx0, bb[0]), min(by0, bb[1]), max(bx1, bb[2]), max(by1, bb[3])
        if bx1 <= bx0:
            bx0, by0, bx1, by1 = 0, 0, 1, 1
        bw, bh = bx1 - bx0, by1 - by0
        tw, th = pot(len(idx) * bw), pot(4 * bh)
        if tw <= 1024 and th <= 1024:
            break
        nf -= 1
    else:
        return (0,) * 8

    def write(sh, tag):
        img = Image.new("RGBA", (tw, th), (0, 0, 0, 0))
        for r in range(4):
            for j, f in enumerate(idx):
                img.paste(sh.crop((f * fw, ROWS[r] * fh, (f + 1) * fw, (ROWS[r] + 1) * fh)).crop((bx0, by0, bx1, by1)),
                          (j * bw, r * bh))
        png = tmp / f"p{dn:04d}{suf}{tag}.png"
        img.save(png)
        subprocess.run(["tex3ds", "-f", "rgba5551", "-o", str(OUT / f"romfs/gfx/p{dn:04d}{suf}{tag}.t3x"), str(png)],
                       check=True, capture_output=True)
    write(sheet, "")
    sh = 0
    sp = ROOT / f"assets/pokemon/{dn}/s/{name}.png"
    if m.get("sh") and "sm" not in m and sp.exists():
        ss = Image.open(sp).convert("RGBA")
        if ss.size == sheet.size:
            write(ss, "s")
            sh = 1
    return (bw, bh, len(idx), tw, th, int(round(a["ax"] - bx0)), int(round(a["ay"] - by0)), sh)


def build(dn, m, tmp):
    return dn, [build_anim(dn, m, n, s, tmp) for n, s in ANIMS]


def main():
    meta = load_meta()
    (OUT / "romfs/gfx").mkdir(parents=True, exist_ok=True)
    todo = {d: m for d, m in meta.items() if "Walk" in m["a"] and d < POKE_MAX}
    res = {}
    with tempfile.TemporaryDirectory() as t:
        tmp = Path(t)
        with ThreadPoolExecutor() as ex:
            for dn, e in ex.map(lambda kv: build(kv[0], kv[1], tmp), sorted(todo.items())):
                res[dn] = e
    L = ["// GENERADO por tools/make_acts.py — no editar", "#pragma once",
         "// animaciones de ataque: [0] Attack, [1] Shoot, [2] Charge (w = 0: no existe)",
         "struct ActSpr { short w, h, n, tw, th, ax, ay, sh; };",
         "static const ActSpr ACT_SPR[POKE_MAX][3] = {"]
    for i in range(POKE_MAX):
        e = res.get(i, [(0,) * 8] * 3)
        L.append("  {" + ",".join("{" + ",".join(map(str, x)) + "}" for x in e) + "},")
    L.append("};")
    (OUT / "include/actmeta.h").write_text("\n".join(L) + "\n")
    ok = sum(1 for e in res.values() if any(x[0] for x in e))
    print(ok, "pokemon con animaciones")


main()
