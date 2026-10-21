#!/usr/bin/env python3
"""Genera una textura por Pokémon (romfs/gfx/pNNNN.t3x) y include/spritemeta.h.

Uso (desde 3ds/):  python3 tools/make_sprites.py
Requiere Pillow y tex3ds (PATH). Rejilla: fotograma (dir,f) en (f*w, dir*h);
dirs = filas 0,2,4,6 de Walk (Abajo, Derecha, Arriba, Izquierda).
"""
import json, re, subprocess, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
ROWS = (0, 2, 4, 6)
MAXF = 12
POKE_MAX = 1100


def pot(v):
    p = 8
    while p < v:
        p *= 2
    return p


def load_meta():
    txt = (ROOT / "js/data/sprites-meta.js").read_text()
    return {int(d): json.loads(b) for d, b in re.findall(r"^\s*(\d+): (\{.*\}),?\s*$", txt, re.M)}


def build(dn, m, tmp):
    w = m["a"]["Walk"]
    fw, fh, n = w["w"], w["h"], min(w["n"], MAXF)
    sheet = Image.open(ROOT / f"assets/pokemon/{dn}/Walk.png").convert("RGBA")
    frames = {}
    bx0, by0, bx1, by1 = fw, fh, 0, 0
    for r in range(4):
        for f in range(n):
            fr = sheet.crop((f * fw, ROWS[r] * fh, (f + 1) * fw, (ROWS[r] + 1) * fh))
            frames[r, f] = fr
            bb = fr.getbbox()
            if bb:
                bx0, by0 = min(bx0, bb[0]), min(by0, bb[1])
                bx1, by1 = max(bx1, bb[2]), max(by1, bb[3])
    if bx1 <= bx0:
        bx0, by0, bx1, by1 = 0, 0, 1, 1
    bw, bh = bx1 - bx0, by1 - by0
    tw, th = pot(n * bw), pot(4 * bh)
    if tw > 1024 or th > 1024:
        raise ValueError(f"dex {dn}: textura {tw}x{th} excede 1024")
    img = Image.new("RGBA", (tw, th), (0, 0, 0, 0))
    for (r, f), fr in frames.items():
        img.paste(fr.crop((bx0, by0, bx1, by1)), (f * bw, r * bh))
    name = f"p{dn:04d}"
    png = tmp / f"{name}.png"
    img.save(png)
    subprocess.run(["tex3ds", "-f", "rgba5551", "-o", str(OUT / f"romfs/gfx/{name}.t3x"), str(png)],
                   check=True, capture_output=True)
    d = w["d"][:n]
    sh = 0
    sp = ROOT / f"assets/pokemon/{dn}/s/Walk.png"
    if m.get("sh") and sp.exists() and "sm" not in m:
        ss = Image.open(sp).convert("RGBA")
        if ss.size == sheet.size:
            im2 = Image.new("RGBA", (tw, th), (0, 0, 0, 0))
            for r in range(4):
                for f in range(n):
                    fr = ss.crop((f * fw, ROWS[r] * fh, (f + 1) * fw, (ROWS[r] + 1) * fh))
                    im2.paste(fr.crop((bx0, by0, bx1, by1)), (f * bw, r * bh))
            png2 = tmp / f"{name}s.png"
            im2.save(png2)
            subprocess.run(["tex3ds", "-f", "rgba5551", "-o", str(OUT / f"romfs/gfx/{name}s.t3x"), str(png2)],
                           check=True, capture_output=True)
            sh = 1
    ms = max(30, int(sum(d) / n * 1000 / 60))
    ax = int(round(w["ax"] - bx0))
    ay = int(round(w["ay"] - by0))
    return dn, (bw, bh, n, tw, th, ms, ax, ay, sh)


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
    lines = ["// GENERADO por tools/make_sprites.py — no editar", "#pragma once",
             f"#define POKE_MAX {POKE_MAX}",
             "struct PokeSpr { short w, h, n, tw, th, ms, ax, ay, sh; };",
             "static const PokeSpr POKE_SPR[POKE_MAX] = {"]
    for i in range(POKE_MAX):
        lines.append("  {" + ",".join(map(str, res.get(i, (0,) * 9))) + "},")
    lines.append("};")
    (OUT / "include/spritemeta.h").write_text("\n".join(lines) + "\n")
    print(len(res), "pokemon")


main()
