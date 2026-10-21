#!/usr/bin/env python3
"""Genera romfs/pixel.bcfnt: Pixelify Sans (la fuente de la web) + los símbolos que le faltan
(★ ♥ ◀ ▶ ✔ ✓ → ♀ ♂), dibujados como bitmaps de 7x7.

Uso (desde 3ds/):  python3 tools/make_font.py     (requiere fonttools y mkbcfnt)
"""
import subprocess
from pathlib import Path
from fontTools.ttLib import TTFont
from fontTools.pens.ttGlyphPen import TTGlyphPen

OUT = Path(__file__).resolve().parents[1]
SRC = OUT.parent / 'assets' / 'fonts' / 'PixelifyPS-400.ttf'
U = 93   # unidades por píxel del arte original

G = {
    0x2605: ['...#...', '...#...', '#######', '.#####.', '..###..', '.##.##.', '##...##'],
    0x2665: ['.##.##.', '#######', '#######', '#######', '.#####.', '..###..', '...#...'],
    0x25C0: ['....#..', '...##..', '..###..', '.####..', '..###..', '...##..', '....#..'],
    0x25B6: ['..#....', '..##...', '..###..', '..####.', '..###..', '..##...', '..#....'],
    0x2714: ['......#', '.....##', '#...##.', '##.##..', '.###...', '..#....', '.......'],
    0x2713: ['......#', '.....##', '#...##.', '##.##..', '.###...', '..#....', '.......'],
    0x2192: ['...#...', '....#..', '#######', '#######', '....#..', '...#...', '.......'],
    0x2640: ['.#####.', '#.....#', '#.....#', '.#####.', '...#...', '..###..', '...#...'],
    0x2642: ['....###', '.....##', '..###.#', '.#...#.', '.#...#.', '.#...#.', '..###..'],
}


def main():
    f = TTFont(SRC)
    order = f.getGlyphOrder()
    glyf, hmtx = f['glyf'], f['hmtx']
    for cp, rows in G.items():
        name = 'sym%04X' % cp
        pen = TTGlyphPen(None)
        for y, row in enumerate(rows):
            x = 0
            while x < 7:
                if row[x] != '#':
                    x += 1
                    continue
                x2 = x
                while x2 < 7 and row[x2] == '#':
                    x2 += 1
                y1 = (7 - y) * U - 12
                y0 = y1 - U
                x0, x1 = 60 + x * U, 60 + x2 * U
                pen.moveTo((x0, y0)); pen.lineTo((x0, y1)); pen.lineTo((x1, y1)); pen.lineTo((x1, y0)); pen.closePath()
                x = x2
        g = pen.glyph()
        order.append(name)
        glyf.glyphs[name] = g
        g.recalcBounds(glyf)
        hmtx[name] = (60 + 7 * U + 60, g.xMin)
        for t in f['cmap'].tables:
            if t.isUnicode():
                t.cmap[cp] = name
    f.setGlyphOrder(order)
    f['maxp'].numGlyphs = len(order)
    tmp = OUT / 'build' / 'PixelifyPS-3ds.ttf'
    tmp.parent.mkdir(exist_ok=True)
    f.save(tmp)
    subprocess.check_call(['mkbcfnt', '-s', '30', '-o', str(OUT / 'romfs' / 'pixel.bcfnt'), str(tmp)])


main()
