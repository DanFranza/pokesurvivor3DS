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
ATLAS = 512
ROWS = (0, 2, 4, 6)          # Down, Right, Up, Left
MAXF = 12                    # fotogramas máximos por animación

# (nombre C, dex)
SPRITES = [
    ("PLAYER_CHARMANDER", 4),
    ("EN_RATTATA", 19),
    ("EN_PIDGEY", 16),
    ("EN_ZUBAT", 41),
    ("EN_CATERPIE", 10),
]


def load_meta():
    txt = (ROOT / "js/data/sprites-meta.js").read_text()
    meta = {}
    for dex, body in re.findall(r"^\s*(\d+): (\{.*\}),?\s*$", txt, re.M):
        meta[int(dex)] = json.loads(body)
    return meta


def main():
    meta = load_meta()
    atlas = Image.new("RGBA", (ATLAS, ATLAS), (0, 0, 0, 0))
    x = y = shelf_h = 0
    entries = []
    for name, dex in SPRITES:
        w = meta[dex]["a"]["Walk"]
        fw, fh, n = w["w"], w["h"], min(w["n"], MAXF)
        sheet = Image.open(ROOT / f"assets/pokemon/{dex}/Walk.png").convert("RGBA")
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
    (OUT / "include/sprites.h").write_text("\n".join(h) + "\n")
    print(f"OK: {len(entries)} sprites, atlas {ATLAS}x{ATLAS}, usado hasta y={y + shelf_h}")


main()
