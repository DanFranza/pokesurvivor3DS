#!/usr/bin/env python3
"""Genera la hoja de iconos pixel art (romfs/gfx/icons.t3x) e include/icons.h.

Uso (desde 3ds/):  python3 tools/make_icons.py
Requiere Pillow, node y tex3ds. Lee los mapas de js/ui/icons.js (los mismos de la web)
y añade las flechas ◀ ▶. Celdas de 32x32 (arte 12-16 px ampliado x2), textura 256x512.
"""
import json, subprocess
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
WORK = OUT / 'build'
CELL, S, COLS = 32, 2, 8

NODE_DUMP = r"""
const fs=require('fs'),vm=require('vm'),path=require('path');
const noop=()=>{};const G={};
const sb={G,window:{},console,Math,JSON,Date,Map,Set,Object,Array,Number,String,parseInt,
 document:{createElement:()=>({getContext:()=>new Proxy({},{get:()=>noop})}),documentElement:{style:{setProperty:noop}}},
 navigator:{language:'es'},location:{pathname:'/'},localStorage:{getItem:()=>'es',setItem:noop},
 addEventListener:noop,performance:{now:()=>0},setTimeout:noop};
sb.window=sb;vm.createContext(sb);
vm.runInContext(fs.readFileSync(path.join(process.argv[1],'js/ui/icons.js'),'utf8'),sb);
console.log(JSON.stringify(G.Icons.UI));
"""

EXTRA = {
    'left': {'pal': {'y': '#ffd23f', 'o': '#c98a14'}, 'rows': [
        '.......kk...', '.....kkyk...', '...kkyyyk...', '.kkyyyyok...', 'kyyyyyyok...', 'kyyyyyyok...',
        '.kkyyyyok...', '...kkyyok...', '.....kkok...', '.......kk...']},
    'right': {'pal': {'y': '#ffd23f', 'o': '#c98a14'}, 'rows': [
        '...kk.......', '...kykk.....', '...kyyykk...', '...kyyyyykk.', '...kyyyyyyyk', '...kyyyyyyok',
        '...kyyyyokk.', '...kyyokk...', '...kokk.....', '...kk.......']},
}


def render(d):
    rows = d['rows']
    h, w = len(rows), max(len(r) for r in rows)
    pad = 1 if d.get('outline') else 0
    pal = {'k': '#1b1528'}
    pal.update(d['pal'])
    im = Image.new('RGBA', (w + 2 * pad, h + 2 * pad), (0, 0, 0, 0))
    px = im.load()

    def col(c):
        return tuple(int(c[i:i + 2], 16) for i in (1, 3, 5)) + (255,)
    if pad:
        for y, row in enumerate(rows):
            for x, ch in enumerate(row):
                if ch in '. ':
                    continue
                for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    px[x + pad + dx, y + pad + dy] = col('#1b1528')
    for y, row in enumerate(rows):
        for x, ch in enumerate(row):
            if ch in '. ' or ch not in pal:
                continue
            px[x + pad, y + pad] = col(pal[ch])
    return im


def hexc(c):
    return tuple(int(c[i:i + 2], 16) for i in (1, 3, 5)) + (255,)


def outline_img(im, col):
    src = im.copy().load()
    px = im.load()
    for y in range(im.height):
        for x in range(im.width):
            if src[x, y][3]:
                continue
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 0 <= nx < im.width and 0 <= ny < im.height and src[nx, ny][3]:
                    px[x, y] = col
                    break
    return im


def bigchest(state):
    """Cofre grande de la web (js/world/tiles.js). state 0 candado cerrado, 1 candado abierto."""
    im = Image.new('RGBA', (24, 20), (0, 0, 0, 0))
    P = im.load()
    wood, woodL, woodD = hexc('#6b3a1e'), hexc('#8e5329'), hexc('#432210')
    iron, ironD, gold, goldD = hexc('#9aa6b5'), hexc('#5d6773'), hexc('#f2c443'), hexc('#b5832a')
    for y in range(2, 19):
        for x in range(1, 23):
            c = woodL if y < 8 else wood
            if y in (8, 9):
                c = ironD
            if x in (1, 22) or y == 18:
                c = woodD
            if x in (5, 6, 17, 18):
                c = iron if x in (5, 17) else ironD
            if y == 2 and 1 < x < 22:
                c = iron
            P[x, y] = c
    if state == 0:
        for x in range(10, 14):
            P[x, 5] = iron
        for p in ((9, 6), (14, 6), (9, 7), (14, 7)):
            P[p] = iron
    else:
        for x in range(10, 13):
            P[x, 3] = iron
        for p in ((9, 4), (9, 5), (9, 6)):
            P[p] = iron
    for y in range(8, 14):
        for x in range(8, 16):
            P[x, y] = gold if (x + y) % 4 else goldD
    for p in ((11, 10), (12, 10), (11, 11), (11, 12)):
        P[p] = woodD
    return outline_img(im, hexc('#1e0f06'))


def smallchest():
    im = Image.new('RGBA', (16, 14), (0, 0, 0, 0))
    P = im.load()
    gold, goldD, wood, woodD, lid = hexc('#f2c443'), hexc('#b5832a'), hexc('#8a4f2a'), hexc('#5e3418'), hexc('#c4662e')
    for y in range(2, 13):
        for x in range(1, 15):
            c = lid if y < 6 else wood
            if y == 6:
                c = goldD
            if x in (1, 14):
                c = woodD
            if x in (4, 11) and y > 1:
                c = gold if y < 6 else goldD
            if y == 12:
                c = woodD
            P[x, y] = c
    for x in range(6, 10):
        for y in range(5, 9):
            P[x, y] = gold if (x + y) % 3 else goldD
    return outline_img(im, hexc('#2a160a'))


IMAGES = {'chest': smallchest, 'bigchest': lambda: bigchest(0), 'bigchest2': lambda: bigchest(1)}


def main():
    ui = json.loads(subprocess.check_output(['node', '-e', NODE_DUMP, str(ROOT)]))
    ui.update(EXTRA)
    names = list(ui.keys()) + list(IMAGES.keys())
    rows = (len(names) + COLS - 1) // COLS
    H = 1
    while H < rows * CELL:
        H *= 2
    sheet = Image.new('RGBA', (COLS * CELL, H), (0, 0, 0, 0))
    for i, n in enumerate(names):
        if n in IMAGES:
            im = IMAGES[n]()
        else:
            im = render(ui[n])
            im = im.resize((im.width * S, im.height * S), Image.NEAREST)
        cx, cy = (i % COLS) * CELL, (i // COLS) * CELL
        sheet.paste(im, (cx + (CELL - im.width) // 2, cy + (CELL - im.height) // 2))
    WORK.mkdir(exist_ok=True)
    (OUT / 'romfs' / 'gfx').mkdir(parents=True, exist_ok=True)
    sheet.save(WORK / 'icons.png')
    subprocess.check_call(['tex3ds', '-f', 'rgba5551', '-o', str(OUT / 'romfs' / 'gfx' / 'icons.t3x'), str(WORK / 'icons.png')])
    L = ['#pragma once', '// Generado por tools/make_icons.py — no editar.', '#define ICON_CELL %d' % CELL,
         '#define ICON_COLS %d' % COLS, '#define ICON_TEX_H %d' % H, 'enum {']
    L += ['    IC_%s,' % n.upper() for n in names]
    L += ['    IC_COUNT', '};']
    (OUT / 'include' / 'icons.h').write_text('\n'.join(L) + '\n')
    print(len(names), 'iconos', sheet.size)


main()
