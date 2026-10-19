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


def main():
    ui = json.loads(subprocess.check_output(['node', '-e', NODE_DUMP, str(ROOT)]))
    ui.update(EXTRA)
    names = list(ui.keys())
    rows = (len(names) + COLS - 1) // COLS
    H = 1
    while H < rows * CELL:
        H *= 2
    sheet = Image.new('RGBA', (COLS * CELL, H), (0, 0, 0, 0))
    for i, n in enumerate(names):
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
