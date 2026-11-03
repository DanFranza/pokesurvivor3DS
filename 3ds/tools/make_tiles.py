#!/usr/bin/env python3
"""Genera un tileset por bioma/arena (romfs/gfx/tilesNN.t3x) e include/tiles.h.

Uso (desde 3ds/):  python3 tools/make_tiles.py
Requiere Pillow, node y tex3ds (PATH). Lee las paletas de js/world/tiles.js
ejecutándolo en un vm de node. Arte a 16 px por tile, ampliado ×2 (nearest).
Cada textura es UNA imagen 256x256 rgba5551 (sin trim ni atlas de tex3ds).
Vista previa: build/tiles_preview.png
"""
import json, math, subprocess
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
WORK = OUT / 'build' / 'tiles'
GFX = OUT / 'romfs' / 'gfx'
SZ = 256
S = 2          # ampliación del arte

NODE_DUMP = r"""
const fs=require('fs'),vm=require('vm'),path=require('path');
const noop=()=>{};const G={};
const sb={G,window:{},console,Math,JSON,Date,Map,Set,Object,Array,Number,String,parseInt,
 document:{createElement:()=>({getContext:()=>new Proxy({},{get:()=>noop})}),documentElement:{}},
 navigator:{language:'es'},location:{pathname:'/'},localStorage:{getItem:()=>'es',setItem:noop},
 addEventListener:noop,performance:{now:()=>0},setTimeout:noop};
sb.window=sb;vm.createContext(sb);
for(const f of ['js/core/util.js','js/world/tiles.js'])vm.runInContext(fs.readFileSync(path.join(process.argv[1],f),'utf8'),sb);
const T=G.Tiles;
console.log(JSON.stringify({biomes:T.BIOMES,themes:T.ARENA_THEMES,types:T.ARENA_TYPES,arena:T.ARENA}));
"""


def load_palettes():
    raw = subprocess.check_output(['node', '-e', NODE_DUMP, str(ROOT)])
    d = json.loads(raw)
    sets = []
    for i in range(3):
        sets.append(dict(pal=d['biomes'][i], name=d['biomes'][i]['name'], pools=0.12, tree=0.03, pillars=0.02))
    types = [t for t in d['types'] if t != 'judgment']
    for t in types:
        th = d['themes'][t]
        pr = th.get('props') or {}
        sets.append(dict(pal=d['biomes'][d['arena'] + d['types'].index(t)], name=th['name'],
                         pools=float(th.get('pools', 0.10)), tree=float(pr.get('tree', 0.03)),
                         pillars=float(th.get('pillars', 0.02))))
    for i in range(3):   # biomas de noche de Halloween (al final de la lista web)
        b = d['biomes'][len(d['biomes']) - 3 + i]
        sets.append(dict(pal=b, name=b['name'], pools=0.12, tree=0.03, pillars=0.02))
    assert len(sets) == 24, len(sets)
    return sets


# ---------------- utilidades ----------------

def hx(h):
    n = int(h[1:], 16)
    return ((n >> 16) & 255, (n >> 8) & 255, n & 255)


def H(x, y, seed=0):
    m = 0xFFFFFFFF
    h = ((int(x) * 374761393) & m) ^ ((int(y) * 668265263) & m) ^ ((int(seed) * 2246822519) & m)
    h = ((h ^ (h >> 13)) * 1274126177) & m
    h ^= h >> 16
    return h / 4294967296


def mix(a, b, t):
    return tuple(round(a[i] + (b[i] - a[i]) * t) for i in range(3))


def shade(c, k):
    return tuple(round(v + (255 - v) * k) if k >= 0 else round(v * (1 + k)) for v in c)


class Art:
    def __init__(self, w, h, fill=None):
        self.w, self.h = w, h
        self.p = [[fill] * w for _ in range(h)]

    def set(self, x, y, c):
        if 0 <= x < self.w and 0 <= y < self.h and c is not None:
            self.p[y][x] = c

    def get(self, x, y):
        return self.p[y][x] if 0 <= x < self.w and 0 <= y < self.h else None

    def outline(self, col):
        marks = []
        for y in range(self.h):
            for x in range(self.w):
                if self.p[y][x] is None and any(self.get(x + a, y + b) is not None for a, b in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                    marks.append((x, y))
        for x, y in marks:
            self.p[y][x] = col

    def image(self):
        im = Image.new('RGBA', (self.w, self.h), (0, 0, 0, 0))
        px = im.load()
        for y in range(self.h):
            for x in range(self.w):
                c = self.p[y][x]
                if c is not None:
                    px[x, y] = (c[0], c[1], c[2], 255)
        return im.resize((self.w * S, self.h * S), Image.NEAREST)


def disc(a, cx, cy, r, fn):
    for y in range(math.floor(cy - r), math.ceil(cy + r) + 1):
        for x in range(math.floor(cx - r), math.ceil(cx + r) + 1):
            d = math.hypot(x - cx, y - cy)
            if d <= r:
                a.set(x, y, fn(x, y, d / r))


class Pal:
    def __init__(self, b):
        g = lambda k: [hx(v) for v in b[k]]
        self.floor, self.dirt, self.flowers = g('floor'), g('dirt'), g('flowers')
        self.leaf, self.trunk, self.rock, self.grass = g('leaf'), g('trunk'), g('rock'), g('grass')
        self.speck, self.light, self.liq, self.liqDeep = hx(b['speck']), hx(b['light']), hx(b['liq']), hx(b['liqDeep'])
        self.foam, self.shore, self.wallEdge = hx(b['foam']), hx(b['shore']), hx(b['wallEdge'])
        self.liqLight = mix(self.liq, self.foam, 0.28)
        self.kind, self.prop = b['liquid'], b['prop']


# ---------------- suelo ----------------

def floor_tile(P, v):
    a = Art(16, 16)
    ox, oy = 16 * (v * 5 + 3), 16 * (v * 3 + 7)
    for y in range(16):
        for x in range(16):
            gx, gy = ox + x, oy + y
            band = H(gx >> 3, gy >> 3, 11) * 0.7 + H(gx, gy, 12) * 0.5
            col = P.floor[min(2, int(band * 3 / 1.2))]
            r = H(gx, gy, 13)
            if r < 0.045:
                col = P.speck
            elif r > 0.975:
                col = P.light
            a.set(x, y, col)
    # manchas de luz y de sombra suaves (2 px) y brizna corta
    for k in range(3):
        px, py = int(H(v, k, 101) * 13) + 1, int(H(v, k, 102) * 14) + 1
        c = P.light if k != 1 else P.speck
        a.set(px, py, c); a.set(px + 1, py, c)
        if k == 0:
            a.set(px, py + 1, mix(P.floor[0], P.light, 0.5))
    px, py = int(H(v, 5, 103) * 10) + 3, int(H(v, 6, 104) * 8) + 3
    a.set(px, py, P.light); a.set(px - 1, py - 1, P.light); a.set(px + 1, py - 1, P.light)
    return a


def dirt_tile(P, v):
    a = Art(16, 16)
    ox, oy = 16 * (v * 4 + 40), 16 * (v * 2 + 9)
    for y in range(16):
        for x in range(16):
            gx, gy = ox + x, oy + y
            band = H(gx >> 2, gy >> 2, 11) * 0.7 + H(gx, gy, 12) * 0.5
            col = P.dirt[min(2, int(band * 3 / 1.2))]
            r = H(gx, gy, 13)
            if r < 0.05:
                col = P.speck
            elif r > 0.97:
                col = P.light
            a.set(x, y, col)
    for k in range(2 + v):
        px, py = int(H(v, k, 111) * 12) + 1, int(H(v, k, 112) * 12) + 1
        a.set(px, py, P.light); a.set(px + 1, py, P.light)
        a.set(px, py + 1, P.speck); a.set(px + 1, py + 1, P.speck)
    return a


# ---------------- decoraciones (16x16 de arte) ----------------

def deco_flower(P, ci):
    a = Art(16, 16)
    fc = P.flowers[ci % len(P.flowers)]
    dk = P.grass[0]
    x, y = 8, 8
    for i in range(3):
        a.set(x, y + 2 + i, dk)
    a.set(x - 1, y + 3, P.grass[1]); a.set(x + 1, y + 4, P.grass[1])
    for dx, dy in ((0, -1), (-1, 0), (1, 0), (0, 1)):
        a.set(x + dx, y + dy, fc)
    a.set(x, y, P.light if mix(fc, (255, 255, 255), 0) != P.light else (255, 255, 200))
    a.set(x - 1, y - 1, shade(fc, 0.35)); a.set(x + 1, y + 1, shade(fc, -0.3))
    return a


def deco_tuft(P):
    a = Art(16, 16)
    for pass_ in range(2):
        for b in range(pass_, 7, 2):
            t = b / 6
            x0 = 4 + t * 8
            h = 4 + int(H(b, 3, 51) * 4) + (2 if abs(t - 0.5) < 0.25 else 0)
            lean = (t - 0.5) * 4
            for i in range(h + 1):
                k = i / h
                c = P.grass[2] if k > 0.7 else P.grass[1] if k > 0.25 else P.grass[0]
                if pass_ == 0 and k <= 0.7:
                    c = P.grass[0]
                a.set(round(x0 + lean * k * k), 13 - i, c)
    a.outline(shade(P.grass[0], -0.65))
    return a


def deco_pebble(P):
    a = Art(16, 16)
    r = P.rock
    for (x, y, c) in ((6, 8, r[1]), (7, 8, r[2]), (8, 8, r[1]), (6, 9, r[0]), (7, 9, r[1]), (8, 9, r[0]), (9, 9, r[0]),
                      (11, 10, r[1]), (12, 10, r[2]), (11, 11, r[0]), (12, 11, r[0]), (3, 11, r[1]), (4, 11, r[0])):
        a.set(x, y, c)
    a.outline(shade(r[0], -0.6))
    return a


def deco_light(P):
    a = Art(16, 16)
    for (x, y, c) in ((6, 6, P.light), (7, 6, P.light), (8, 6, P.light), (5, 7, mix(P.floor[0], P.light, 0.5)), (6, 7, P.light),
                      (7, 7, shade(P.light, 0.3)), (8, 7, P.light), (9, 7, mix(P.floor[0], P.light, 0.5)),
                      (7, 8, P.light), (8, 8, mix(P.floor[0], P.light, 0.5)), (11, 4, P.light), (3, 10, P.light)):
        a.set(x, y, c)
    return a


# ---------------- líquido ----------------

def liquid_tile(P, f):
    a = Art(16, 16)
    k = P.kind
    base = P.liq if k == 'ice' else P.liqDeep
    mid = P.liqLight if k == 'ice' else P.liq
    for y in range(16):
        for x in range(16):
            blk = H((x >> 1) + 20, (y >> 1) + 20, 31)
            a.set(x, y, mid if blk < 0.25 else base)
    for y in range(16):
        for x in range(16):
            if H(x + 7, y + 7, 32) < 0.03:
                a.set(x, y, mid)
    rows = (2, 5, 9, 12, 14)
    for ri, row in enumerate(rows):
        x0 = int(H(row, 3, 33) * 16)
        ln = 3 + (ri % 2)
        if k == 'ice':
            x0 = int(H(row, 3, 33) * 16)
            for i in range(ln + 1):
                a.set(x0 + i, row, P.foam if i < 2 else P.liqLight)
            continue
        if k == 'spark':
            x1 = (x0 + f * 3) % 16
            for i in range(ln):
                a.set((x1 + i) % 16, row + (i % 2), P.foam if (i + ri) % 2 == 0 else P.liqLight)
            continue
        sh = (x0 + f * 4) % 16
        c = P.foam if (k == 'lava' and ri % 2 == 0) else P.liqLight
        for i in range(ln):
            a.set((sh + i) % 16, row, c)
        if k == 'lava' and i:
            a.set((sh + 1) % 16, row + 1, P.liq)
    if k == 'lava':
        for q in range(4):
            x, y = int(H(q, 1, 35) * 14), int(H(q, 2, 36) * 14)
            a.set(x, y, shade(P.liqDeep, -0.45)); a.set(x + 1, y, shade(P.liqDeep, -0.3))
    if k in ('swamp', 'poison'):
        for q in range(3):
            x, y = int(H(q, 4, 37) * 12) + 2, int(H(q, 5, 38) * 12) + 2
            y -= f
            ring = P.foam if k == 'poison' else P.liqLight
            a.set(x, y, ring); a.set(x + 1, y, ring); a.set(x, y + 1, ring)
            a.set(x + 1, y + 1, shade(ring, -0.35))
    if k == 'ice':
        for q in range(3):
            x, y = int(H(q, 7, 39) * 13) + 1, int(H(q, 8, 40) * 13) + 1
            c = P.foam if (q + f) % 2 == 0 else P.liqLight
            a.set(x, y, c); a.set(x + 1, y + 1, c)
    if k == 'water':
        for q in range(3):
            x, y = int(H(q, 9, 41) * 14), int(H(q, 10, 42) * 14)
            if (q + f) % 2 == 0:
                a.set(x, y, P.foam)
    return a


def edge_strips(P):
    """N,E,S,W: capas de orilla de 4 px de arte (labio, espuma, somera)."""
    cols = [P.shore, P.foam, P.liqLight, P.liq]
    N = Art(16, 4)
    for y in range(4):
        for x in range(16):
            c = cols[y]
            if y == 3 and (x + y) % 2:
                c = None
            if y == 0 and H(x, 0, 51) < 0.2:
                c = P.foam
            N.set(x, y, c)
    S_ = Art(16, 4)
    for y in range(4):
        for x in range(16):
            S_.p[3 - y][x] = N.p[y][x]
    E = Art(4, 16)
    W = Art(4, 16)
    for y in range(16):
        for x in range(4):
            c = N.p[3 - x][y]
            E.p[y][x] = c
            W.p[y][3 - x] = c
    return [N, E, S_, W]


# ---------------- props ----------------

def tree_sprite(P, v):
    a = Art(24, 32)
    L, T = P.leaf, P.trunk
    edge = shade(P.leaf[0], -0.7)
    tx = 11 + (v == 1)
    for y in range(21, 30):
        for x in range(tx, tx + 4):
            a.set(x, y, T[0 if x in (tx, tx + 3) else 1])
    a.set(tx - 1, 29, T[0]); a.set(tx + 4, 29, T[0])
    blobs = [
        [(12, 16, 8), (7, 13, 6), (17, 13, 6), (12, 8, 6), (8, 18, 5), (16, 18, 5)],
        [(12, 15, 8), (6, 14, 5), (18, 14, 5), (12, 7, 6), (7, 19, 4), (17, 19, 4), (12, 20, 5)],
        [(12, 13, 9), (7, 18, 5), (17, 18, 5), (12, 7, 5), (6, 11, 4), (18, 11, 4)],
    ][v]
    for bx, by, br in blobs:
        def fn(x, y, d, bx=bx, by=by, br=br):
            lit = ((x - bx) * -0.6 + (y - by) * -0.8) / br
            idx = 3 if lit > 0.45 else 2 if lit > 0.05 else 1 if lit > -0.45 else 0
            return L[idx - 1] if (H(x, y, 41 + v) < 0.12 and idx > 0) else L[idx]
        disc(a, bx, by, br, fn)
    if v == 2:
        for q in range(5):
            x, y = 5 + int(H(q, v, 43) * 14), 8 + int(H(q, v, 44) * 12)
            if a.get(x, y) is not None:
                a.set(x, y, P.flowers[q % len(P.flowers)])
    a.outline(edge)
    return a, 12, 30


def clearing_tree(P, v):
    # Bosque Umbrío: misma silueta, tamaño y paleta que PAINT.tree de la web.
    a = Art(30, 40)
    L, T = P.leaf, P.trunk
    for y in range(26, 38):
        for x in range(13, 18):
            a.set(x, y, T[0 if x in (13, 17) else 1])
    for x, y in ((12, 37), (18, 37), (11, 38), (19, 38)):
        a.set(x, y, T[0])
    for bx, by, br in ((15, 20, 10), (9, 16, 7), (21, 16, 7), (15, 10, 8), (10, 23, 6), (20, 23, 6)):
        def color(x, y, d, bx=bx, by=by, br=br):
            lit = ((x - bx) * -0.6 + (y - by) * -0.8) / br
            idx = 3 if lit > 0.45 else 2 if lit > 0.05 else 1 if lit > -0.45 else 0
            return L[idx - 1] if H(x, y, 41) < 0.12 and idx > 0 else L[idx]
        disc(a, bx, by, br, color)
    a.outline(hx('#14200f'))
    return a, 15, 39


def crystal_sprite(P, v):
    a = Art(24, 32)
    L, D = P.leaf, P.trunk
    spires = [
        [(12, 1, 4, 30), (6, 11, 3, 30), (18, 9, 3, 30)],
        [(12, 4, 4, 30), (5, 9, 3, 30), (19, 12, 3, 30), (9, 16, 2, 30)],
        [(10, 2, 4, 30), (17, 8, 4, 30), (4, 16, 2, 30), (20, 18, 2, 30)],
    ][v]
    for cx, top, half, bot in spires:
        for y in range(top, bot + 1):
            t = min(1, (y - top) / 7)
            hw = round(half * t)
            for x in range(cx - hw, cx + hw + 1):
                side = (3 if x == cx - hw else 2) if x < cx else 1 if x == cx else 0
                a.set(x, y, L[side] if side >= 2 or y <= bot - 3 else D[1])
                if side == 2 and y % 5 == 3:
                    a.set(x, y, L[3])
        a.set(cx - 1, top + 2, (255, 255, 255))
    a.outline(D[0])
    return a, 12, 30


def dead_sprite(P, v):
    a = Art(24, 32)
    T, L = P.trunk, P.leaf
    tx = 10 + (v == 2)
    for y in range(12, 30):
        for x in range(tx, tx + 4):
            a.set(x, y, T[0 if x < tx + 2 else 1])
    a.set(tx - 1, 29, T[0]); a.set(tx + 4, 29, T[0])

    def branch(x0, y0, dx, ln):
        for i in range(ln):
            a.set(x0 + dx * i, y0 - i, L[1]); a.set(x0 + dx * i, y0 - i + 1, L[0])
        a.set(x0 + dx * (ln - 1), y0 - ln + 1, L[2])
    sets = [
        [(tx, 19, -1, 8), (tx + 3, 16, 1, 9), (tx + 1, 12, -1, 6), (tx + 2, 11, 1, 5)],
        [(tx, 21, -1, 6), (tx + 3, 18, 1, 8), (tx + 1, 14, -1, 8), (tx + 2, 12, 1, 4)],
        [(tx, 17, -1, 9), (tx + 3, 20, 1, 6), (tx + 1, 12, -1, 4), (tx + 2, 13, 1, 8)],
    ][v]
    for b in sets:
        branch(*b)
    a.outline(shade(P.trunk[0], -0.7))
    return a, 12, 30


def rock_sprite(P, v):
    a = Art(16, 12)
    R = P.rock
    for y in range(1, 11):
        for x in range(0, 16):
            nx, ny = (x - 7.5) / 7.5, (y - 6.0) / 5.0
            d = nx * nx + ny * ny + (H(x, y, 61 + v) - 0.5) * 0.1
            if d > 1:
                continue
            lit = -nx * 0.55 - ny * 0.85 + (H(x, y, 62) - 0.5) * 0.25
            c = R[2 if lit > 0.4 else 1 if lit > -0.15 else 0]
            if y >= 9:
                c = R[0]
            a.set(x, y, c)
    for x, y in ((4, 3), (5, 3), (4, 4), (6, 2)):
        a.set(x, y, shade(R[2], 0.5))
    for x, y in ((9, 5), (10, 6), (6, 7), (12, 7)):
        a.set(x, y, R[0])
    if v == 1:
        for x, y in ((7, 2), (7, 3), (8, 4), (8, 5), (7, 6), (9, 6), (10, 7)):
            a.set(x, y, shade(R[0], -0.6))
    a.outline(shade(R[0], -0.7))
    return a, 8, 11


# ---------------- empaquetado ----------------

def build(i, st):
    P = Pal(st['pal'])
    cells = []   # (clave, idx, imagen, ax, ay)
    for v in range(4): cells.append(('floor', v, floor_tile(P, v).image(), 0, 0))
    for v in range(2): cells.append(('dirt', v, dirt_tile(P, v).image(), 0, 0))
    decos = [deco_flower(P, 0), deco_flower(P, 1), deco_flower(P, 2), deco_tuft(P), deco_pebble(P), deco_light(P)]
    for v, d in enumerate(decos): cells.append(('deco', v, d.image(), 16, 26 if v < 5 else 16))
    for v in range(2): cells.append(('liquid', v, liquid_tile(P, v).image(), 0, 0))
    ed = edge_strips(P)
    offs = [(0, 0), (24, 0), (0, 24), (0, 0)]
    for v in range(4): cells.append(('edge', v, ed[v].image(), offs[v][0], offs[v][1]))
    mk = clearing_tree if i == 0 else {'tree': tree_sprite, 'crystal': crystal_sprite, 'dead': dead_sprite}[P.prop]
    for v in range(3):
        a, ax, ay = mk(P, v)
        cells.append(('tree', v, a.image(), ax * S, ay * S))
    for v in range(2):
        a, ax, ay = rock_sprite(P, v)
        cells.append(('rock', v, a.image(), ax * S, ay * S))
    order = sorted(range(len(cells)), key=lambda j: (-cells[j][2].height, j))
    tex = Image.new('RGBA', (SZ, SZ), (0, 0, 0, 0))
    x = y = rowh = 0
    pos = {}
    for j in order:
        im = cells[j][2]
        if x + im.width > SZ:
            x, y, rowh = 0, y + rowh + 1, 0
        pos[j] = (x, y)
        tex.paste(im, (x, y))
        x += im.width + 1
        rowh = max(rowh, im.height)
    assert y + rowh <= SZ, 'no cabe'
    layout = {}
    for j, (key, idx, im, ax, ay) in enumerate(cells):
        layout.setdefault(key, [None] * (idx + 1))
        l = layout[key]
        while len(l) <= idx: l.append(None)
        l[idx] = (pos[j][0], pos[j][1], im.width, im.height, ax, ay)
    return tex, layout


def q5551(tex):
    im = tex.copy()
    px = im.load()
    for yy in range(im.height):
        for xx in range(im.width):
            r, g, b, al = px[xx, yy]
            px[xx, yy] = (0, 0, 0, 0) if al < 128 else (r, g, b, 255)
    return im


KINDS = {'water': 0, 'lava': 1, 'swamp': 2, 'poison': 3, 'spark': 4, 'ice': 5}
ORDER = [('floor', 4), ('dirt', 2), ('deco', 6), ('liquid', 2), ('edge', 4), ('tree', 3), ('rock', 2)]


def rgba(c, a=255):
    return '0x%02X%02X%02X%02X' % (c[0], c[1], c[2], a)


def main():
    sets = load_palettes()
    WORK.mkdir(parents=True, exist_ok=True)
    GFX.mkdir(parents=True, exist_ok=True)
    layouts, texs = [], []
    for i, st in enumerate(sets):
        tex, lay = build(i, st)
        tex = q5551(tex)
        tex.save(WORK / ('tiles%02d.png' % i))
        subprocess.check_call(['tex3ds', '-f', 'rgba5551', '-o', str(GFX / ('tiles%02d.t3x' % i)), str(WORK / ('tiles%02d.png' % i))])
        layouts.append(lay); texs.append(tex)

    L = ['#pragma once', '// Generado por tools/make_tiles.py — no editar.', '#define NTILESETS %d' % len(sets),
         '// Cada textura tilesNN.t3x es 256x256 rgba5551. (ax,ay) = ancla dentro de la celda: pies en props/deco;',
         '// en edge[] es el desplazamiento dentro del tile 32x32 donde se dibuja la tira (N 0,0 · E 24,0 · S 0,24 · W 0,0).',
         'struct TCell { short x, y, w, h, ax, ay; };',
         'struct TileSet {', '  TCell floor[4];', '  TCell dirt[2];', '  TCell deco[6];', '  TCell liquid[2];',
         '  TCell edge[4];', '  TCell tree[3];', '  TCell rock[2];', '};', 'static const TileSet TILESETS[NTILESETS] = {']
    for i, lay in enumerate(layouts):
        L.append('  { // %02d %s' % (i, sets[i]['name']))
        for key, n in ORDER:
            cs = ', '.join('{%d,%d,%d,%d,%d,%d}' % c for c in lay[key][:n])
            L.append('    {%s},' % cs)
        L.append('  },')
    L.append('};')
    L.append('static const char* TILESET_NAMES[NTILESETS] = {' + ', '.join(json.dumps(s['name'], ensure_ascii=False) for s in sets) + '};')
    L.append('static const unsigned char TILESET_LIQUID[NTILESETS] = {' + ', '.join(str(KINDS.get(s['pal']['liquid'], 0)) for s in sets) + '};')
    L.append('static const unsigned int TILESET_FLOOR_RGBA[NTILESETS] = {' + ', '.join(rgba(hx(s['pal']['floor'][0])) for s in sets) + '};')
    L.append('static const unsigned int TILESET_LIQUID_RGBA[NTILESETS] = {' + ', '.join(rgba(hx(s['pal']['liq'])) for s in sets) + '};')
    for nm, k in (('POOLS', 'pools'), ('TREES', 'tree'), ('PILLARS', 'pillars')):
        L.append('static const float TILESET_%s[NTILESETS] = {' % nm + ', '.join('%.4ff' % s[k] for s in sets) + '};')
    (OUT / 'include').mkdir(exist_ok=True)
    (OUT / 'include' / 'tiles.h').write_text('\n'.join(L) + '\n', encoding='utf-8')

    # Vista previa: escena 12x8 de tiles 0, 2 y 5
    scenes = []
    for i in (0, 2, 5):
        scenes.append(preview(i, sets[i], texs[i], layouts[i]))
    W = sum(s.width for s in scenes) + 8 * (len(scenes) - 1)
    pv = Image.new('RGBA', (W, scenes[0].height), (20, 20, 20, 255))
    x = 0
    for s in scenes:
        pv.paste(s, (x, 0)); x += s.width + 8
    pv.save(OUT / 'build' / 'tiles_preview.png')
    size = sum((GFX / ('tiles%02d.t3x' % i)).stat().st_size for i in range(len(sets)))
    print('tiles*.t3x total bytes:', size)


def preview(i, st, tex, lay):
    cw, ch = 12, 8
    M = 64
    sc = Image.new('RGBA', (cw * 32, ch * 32 + M), (0, 0, 0, 255))
    pool = set()
    for (cx, cy, r) in ((8, 3, 2.2), (9, 5, 1.6), (2, 6, 1.4)):
        for y in range(ch):
            for x in range(cw):
                if math.hypot(x - cx, (y - cy) * 1.1) < r:
                    pool.add((x, y))
    def cut(c):
        return tex.crop((c[0], c[1], c[0] + c[2], c[1] + c[3]))
    for y in range(ch):
        for x in range(cw):
            if (x, y) in pool:
                c = lay['liquid'][(x + y) % 2]
            elif H(x // 2, y // 2, 5) < 0.2:
                c = lay['dirt'][int(H(x, y, 6) * 2)]
            else:
                c = lay['floor'][int(H(x, y, 7) * 4)]
            sc.paste(cut(c), (x * 32, y * 32 + M))
    for y in range(ch):
        for x in range(cw):
            if (x, y) in pool:
                for d, (dx, dy) in enumerate(((0, -1), (1, 0), (0, 1), (-1, 0))):
                    if (x + dx, y + dy) not in pool:
                        c = lay['edge'][d]
                        sc.alpha_composite(cut(c), (x * 32 + c[4], y * 32 + c[5] + M))
                continue
            r = H(x, y, 14)
            if r < 0.35:
                k = [0, 1, 2, 3, 3, 4, 5][int(H(x, y, 15) * 7)]
                c = lay['deco'][k]
                sc.alpha_composite(cut(c), (x * 32, y * 32 + M))
    for y in range(ch):
        for x in range(cw):
            if (x, y) in pool:
                continue
            r = H(x, y, 21)
            if r < 0.13:
                c = lay['tree'][int(H(x, y, 22) * 3)]
                sc.alpha_composite(cut(c), (x * 32 + 16 - c[4], y * 32 + 30 - c[5] + M))
            elif r < 0.2:
                c = lay['rock'][int(H(x, y, 23) * 2)]
                sc.alpha_composite(cut(c), (x * 32 + 16 - c[4], y * 32 + 30 - c[5] + M))
    return sc.crop((0, 0, cw * 32, ch * 32 + M))


if __name__ == '__main__':
    main()
