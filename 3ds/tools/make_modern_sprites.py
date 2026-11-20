#!/usr/bin/env python3
"""Build the added regional, missing-species and Mega Walk sprites.

Run after make_sprites.py from 3ds/. The source PNGs and metadata are vendored,
so rebuilding uses the checked-in PNGs and metadata.
"""
import json
import re
import subprocess
import tempfile
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
META = json.loads((ROOT / "tools/modern_sprite_meta.json").read_text())
HEADER = ROOT / "include/spritemeta.h"
ROWS = (0, 2, 4, 6)
LIMIT = 3904


def pot(n):
    p = 8
    while p < n:
        p *= 2
    return p


def convert(dex, meta, shiny, temp, layout=None):
    src = ROOT / "assets/modern_pokemon" / str(dex)
    png = src / ("s/Walk.png" if shiny else "Walk.png")
    sheet = Image.open(png).convert("RGBA")
    fw, fh = meta["w"], meta["h"]
    if sheet.height != fh * 8 or sheet.width < fw:
        raise ValueError(f"Sprite {dex}: unexpected sheet size {sheet.size}")
    n = min(meta["n"], sheet.width // fw, 12)
    while n > 1 and pot(n * fw) > 1024:
        n -= 1
    if pot(n * fw) > 1024 or pot(4 * fh) > 1024:
        raise ValueError(f"Sprite {dex}: too large for 3DS")
    stride = n
    cells = [sheet.crop((f * fw, r * fh, (f + 1) * fw, (r + 1) * fh))
             for r in ROWS for f in range(n)]
    bbox = list(layout[1]) if layout else [fw, fh, 0, 0]
    if layout is None:
        for cell in cells:
            box = cell.getbbox()
            if box:
                bbox = [min(bbox[0], box[0]), min(bbox[1], box[1]),
                        max(bbox[2], box[2]), max(bbox[3], box[3])]
        if bbox[2] <= bbox[0]:
            bbox = [0, 0, 1, 1]
    w, h = bbox[2] - bbox[0], bbox[3] - bbox[1]
    if layout is not None:
        n = layout[0]
    else:
        while n > 1 and pot(n * w) > 1024:
            n -= 1
    out = Image.new("RGBA", (pot(n * w), pot(4 * h)))
    for ri in range(4):
        for f in range(n):
            cell = cells[ri * stride + f]
            out.paste(cell.crop(tuple(bbox)), (f * w, ri * h))
    name = f"p{dex:04d}{'s' if shiny else ''}"
    tmp = temp / f"{name}.png"
    out.save(tmp)
    subprocess.run(["tex3ds", "-f", "rgba5551", "-o", str(ROOT / f"romfs/gfx/{name}.t3x"), str(tmp)],
                   check=True, capture_output=True)
    return (w, h, n, out.width, out.height, 100, round(meta["ax"] - bbox[0]), round(meta["ay"] - bbox[1])), (n, bbox)


def main():
    text = HEADER.read_text()
    rows = [tuple(map(int, re.findall(r"-?\d+", line))) for line in text.splitlines() if re.fullmatch(r"  \{-?\d+(?:,-?\d+){8}\},", line)]
    if len(rows) < 1100:
        raise ValueError("Run tools/make_sprites.py first")
    rows += [(0,) * 9] * (LIMIT - len(rows))
    # The four costume textures formerly occupied regional-form IDs 1050–1053.
    for i in range(4):
        rows[3900 + i] = rows[1050 + i]
        old = ROOT / f"romfs/gfx/p{1050+i:04d}.t3x"
        (ROOT / f"romfs/gfx/p{3900+i:04d}.t3x").write_bytes(old.read_bytes())
    with tempfile.TemporaryDirectory() as td:
        for key, meta in META.items():
            dex = int(key)
            base, layout = convert(dex, meta, False, Path(td))
            shiny_png = ROOT / "assets/modern_pokemon" / key / "s/Walk.png"
            shiny = shiny_png.exists() and Image.open(shiny_png).size == Image.open(ROOT / "assets/modern_pokemon" / key / "Walk.png").size
            if shiny:
                convert(dex, meta, True, Path(td), layout)
            rows[dex] = (*base, int(shiny))
    lines = ["// GENERADO por tools/make_sprites.py y make_modern_sprites.py", "#pragma once",
             f"#define POKE_MAX {LIMIT}",
             "struct PokeSpr { short w, h, n, tw, th, ms, ax, ay, sh; };",
             "static const PokeSpr POKE_SPR[POKE_MAX] = {"]
    lines += ["  {" + ",".join(map(str, row)) + "}," for row in rows]
    lines.append("};")
    HEADER.write_text("\n".join(lines) + "\n")
    print(f"Built {len(META)} sprites; retained {len(rows)} sprite slots")


if __name__ == "__main__":
    main()
