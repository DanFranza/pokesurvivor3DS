#!/usr/bin/env python3
"""Genera el atlas de sprites de la 3DS a partir de assets/pokemon/.

Uso (desde 3ds/):  python3 tools/make_atlas.py
Requiere Pillow.   Salida: gfx/atlas.png, gfx/atlas.t3s, include/sprites.h

Por Pokémon se usa la hoja Walk con 4 direcciones (Abajo, Derecha, Arriba,
Izquierda = filas 0, 2, 4, 6 del juego web). Cada fotograma se recorta al
rectángulo común del Pokémon para ahorrar VRAM, y el ancla (pies) se ajusta.
"""
import json, re, sys
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
ATLAS = 1024
ROWS = (0, 2, 4, 6)          # Down, Right, Up, Left
MAXF = 12                    # fotogramas máximos por animación

STARTERS = [1, 4, 7]                       # Bulbasaur, Charmander, Squirtle
# (BST mín, BST máx, vida, velocidad, daño, xp) como los tramos de enemies.js
TIERS = [(180, 330, 17, 56, 6, 3), (300, 405, 32, 62, 9, 5),
         (385, 465, 52, 60, 11, 8), (445, 515, 88, 70, 14, 13)]
PER_TIER = 6
SEED = 3


def load_dex():
    txt = (ROOT / "js/data/pokedex.js").read_text()
    return {d["dex"]: d for d in map(json.loads, re.findall(r"^\s*(\{\"dex\".*\}),?\s*$", txt, re.M))}


def pick_sprites(dex, meta):
    import random
    rng = random.Random(SEED)
    names = [(f"PLAYER_{dex[d]['name'].upper()}", d) for d in STARTERS]
    tiers = []
    for lo, hi, *_ in TIERS:
        pool = [d for d, v in dex.items()
                if lo <= v["bst"] <= hi and v["rarity"] <= 3 and not v["starter"]
                and "Walk" in meta[d]["a"] and meta[d]["a"]["Walk"]["w"] <= 48
                and meta[d]["a"]["Walk"]["h"] <= 56 and d not in STARTERS]
        ch = rng.sample(sorted(pool), PER_TIER)
        tiers.append([(f"EN_{dex[d]['name'].upper().replace('-', '_').replace('.', '').replace(' ', '_')}", d) for d in ch])
    return names, tiers


def load_meta():
    txt = (ROOT / "js/data/sprites-meta.js").read_text()
    meta = {}
    for dex, body in re.findall(r"^\s*(\d+): (\{.*\}),?\s*$", txt, re.M):
        meta[int(dex)] = json.loads(body)
    return meta


def main():
    meta = load_meta()
    dex = load_dex()
    pn, tiers = pick_sprites(dex, meta)
    SPRITES = pn + [t for tt in tiers for t in tt]
    atlas = Image.new("RGBA", (ATLAS, ATLAS), (0, 0, 0, 0))
    x = y = shelf_h = 0
    entries = []
    for name, dn in SPRITES:
        w = meta[dn]["a"]["Walk"]
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
        bw, bh = bx1 - bx0, by1 - by0
        # Duración media por fotograma (1/60 s) -> ms
        dur = sum(w["d"][:n]) / n
        rects = []
        for r in range(4):
            row = []
            for f in range(n):
                if x + bw > ATLAS:
                    x, y, shelf_h = 0, y + shelf_h, 0
                if y + bh > ATLAS:
                    sys.exit("Atlas lleno: sube ATLAS o quita Pokémon")
                atlas.paste(frames[r, f].crop((bx0, by0, bx1, by1)), (x, y))
                row.append((x, y))
                x += bw
                shelf_h = max(shelf_h, bh)
            rects.append(row)
        entries.append(dict(name=name, w=bw, h=bh, n=n,
                            ax=w["ax"] - bx0, ay=w["ay"] - by0,
                            ms=int(dur * 1000 / 60), rects=rects))

    (OUT / "gfx").mkdir(exist_ok=True)
    (OUT / "include").mkdir(exist_ok=True)
    atlas.save(OUT / "gfx/atlas.png")
    (OUT / "gfx/atlas.t3s").write_text("-f rgba5551\natlas.png\n")

    h = ["// GENERADO por tools/make_atlas.py — no editar a mano",
         "#pragma once", f"#define ATLAS_SIZE {ATLAS}", f"#define SPR_MAXF {MAXF}",
         "struct SprDef { short w, h, n; float ax, ay; short ms; short xy[4][SPR_MAXF][2]; };",
         "enum SprId {"]
    h += [f"  SPR_{e['name']}," for e in entries] + ["  SPR_COUNT", "};",
          "static const SprDef SPR_DEFS[SPR_COUNT] = {"]
    for e in entries:
        xy = ",".join("{" + ",".join(f"{{{a},{b}}}" for a, b in row) + "}" for row in e["rects"])
        h.append(f"  {{{e['w']},{e['h']},{e['n']},{e['ax']}f,{e['ay']}f,{e['ms']},{{{xy}}}}},  // {e['name']}")
    h.append("};")
    h.append("#define NPLAYERS %d" % len(pn))
    h.append("static const char* PLAYER_NAMES[NPLAYERS] = {%s};" % ",".join('"%s"' % dex[d]["name"] for d in STARTERS))
    h.append("static const float PLAYER_HP[NPLAYERS] = {%s};" % ",".join(str(round(dex[d]["hp"] * 0.6)) for d in STARTERS))
    h.append("static const float PLAYER_SPD[NPLAYERS] = {%s};" % ",".join(str(round(dex[d]["spd"] * 0.8)) for d in STARTERS))
    h.append("#define NTIERS %d\n#define PER_TIER %d" % (len(TIERS), PER_TIER))
    h.append("struct TierDef { float from, hp, spd, dmg, radius; int xp; short spr[PER_TIER]; };")
    froms = [0, 40, 100, 170]
    rows = []
    for i, (lo, hi, hp, sp, dm, xp) in enumerate(TIERS):
        ids = ",".join(str(len(pn) + i * PER_TIER + k) for k in range(PER_TIER))
        rows.append(f"  {{{froms[i]},{hp},{sp},{dm},9,{xp},{{{ids}}}}}")
    h.append("static const TierDef TIER_DEFS[NTIERS] = {\n" + ",\n".join(rows) + "\n};")
    (OUT / "include/sprites.h").write_text("\n".join(h) + "\n")
    print(f"OK: {len(entries)} sprites, atlas {ATLAS}x{ATLAS}, usado hasta y={y + shelf_h}")


main()
