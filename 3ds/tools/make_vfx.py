#!/usr/bin/env python3
"""Genera la hoja de efectos de ataque (romfs/gfx/vfx.t3x) e include/vfxmeta.h.

Usa las MISMAS formas que la web (js/entities/vfx.js): las ejecuta con node,
pinta cada forma con cada paleta de tipo y las pone en un atlas. También
escribe, para cada movimiento de gamedata.h, qué forma/paleta lleva.

Uso (desde 3ds/):  python3 tools/make_vfx.py     (requiere Pillow, node y tex3ds)
Atlas: celdas de 16x16; columna = (forma, fotograma), fila = paleta.
"""
import json, re, subprocess, tempfile
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).resolve().parents[1]
CELL = 16
TYPES = ['normal', 'fire', 'water', 'electric', 'grass', 'ice', 'fighting', 'poison', 'ground',
         'flying', 'psychic', 'bug', 'rock', 'ghost', 'dragon', 'dark', 'steel', 'fairy']

NODE = r"""
const fs=require('fs'),vm=require('vm'),path=require('path');
const root=process.argv[1];
const G={Sprites:{PX:2}};const win={G};
const mk=()=>{const r=[];const ctx={fillStyle:'',fillRect(x,y,w,h){r.push([x,y,w,h,this.fillStyle]);}};
  return {width:0,height:0,rects:r,getContext:()=>ctx};};
const sb={window:win,G,Math,JSON,Map,Set,Object,Array,Number,String,parseInt,console,
  document:{createElement:()=>mk()}};
vm.createContext(sb);
vm.runInContext(fs.readFileSync(path.join(root,'js/core/util.js'),'utf8'),sb);
vm.runInContext(fs.readFileSync(path.join(root,'js/entities/vfx.js'),'utf8'),sb);
const V=sb.G.VFX, out={pal:Object.keys(V.PAL),shapes:{},cells:{},moves:{}};
const types=JSON.parse(process.argv[2]);
for(const [n,S] of Object.entries(V.SHAPES)){
  out.shapes[n]={w:S.w,h:S.h,frames:S.frames||1,dir:!!S.dir,spin:!!S.spin};
  for(const p of out.pal) for(let f=0;f<(S.frames||1);f++) out.cells[n+'|'+p+'|'+f]=V.sprite(n,p,f).rects;
}
const slugs=JSON.parse(process.argv[3]);
for(const s of Object.keys(slugs)){
  const m=slugs[s]; out.moves[s]=V.forMove({id:s,type:types[m]});
}
console.log(JSON.stringify(out));
"""


def main():
    gd = (OUT / "include/gamedata.h").read_text()
    body = gd[gd.index("static const MoveDef MOVES"):]
    body = body[:body.index("\n};")]
    slugs, mt = [], []
    for ln in body.splitlines():
        m = re.search(r"//\s*([a-z0-9-]+)\s*$", ln)
        t = re.match(r'\s*\{"(?:[^"\\]|\\.)*","(?:[^"\\]|\\.)*",(\d+),', ln)
        if m and t:
            slugs.append(m.group(1)); mt.append(int(t.group(1)))
    sl = {s: mt[i] for i, s in enumerate(slugs)}
    res = subprocess.run(["node", "-e", NODE, str(ROOT), json.dumps(TYPES), json.dumps(sl)],
                         check=True, capture_output=True, text=True).stdout
    d = json.loads(res)
    pals = d["pal"]
    shapes = list(d["shapes"].keys())
    col = {}
    n = 0
    for s in shapes:
        col[s] = n
        n += d["shapes"][s]["frames"]
    W, H = 1024, 512
    assert n * CELL <= W and len(pals) * CELL <= H, (n, len(pals))
    img = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    px = img.load()

    def rgb(c):
        if c.startswith("rgba"):
            a = [float(x) for x in c[5:-1].split(",")]
            return int(a[0]), int(a[1]), int(a[2]), int(a[3] * 255)
        h = int(c[1:], 16)
        return h >> 16 & 255, h >> 8 & 255, h & 255, 255
    for pi, p in enumerate(pals):
        for s in shapes:
            S = d["shapes"][s]
            for f in range(S["frames"]):
                ox, oy = (col[s] + f) * CELL, pi * CELL
                for x, y, w, h, c in d["cells"][f"{s}|{p}|{f}"]:
                    for yy in range(int(y), int(y + h)):
                        for xx in range(int(x), int(x + w)):
                            px[ox + xx, oy + yy] = rgb(c)
    with tempfile.TemporaryDirectory() as t:
        png = Path(t) / "vfx.png"
        img.save(png)
        subprocess.run(["tex3ds", "-f", "rgba5551", "-o", str(OUT / "romfs/gfx/vfx.t3x"), str(png)],
                       check=True, capture_output=True)
    sidx = {s: i for i, s in enumerate(shapes)}
    pidx = {p: i for i, p in enumerate(pals)}
    L = ["// GENERADO por tools/make_vfx.py — no editar", "#pragma once",
         f"#define VFX_NSHAPE {len(shapes)}", f"#define VFX_NPAL {len(pals)}",
         "// forma: ancho, alto, fotogramas, primera columna, flags (1 = direccional, 2 = gira)",
         "struct VfxShape { unsigned char w, h, frames, col, flags; };",
         "static const VfxShape VFX_SHAPE[VFX_NSHAPE] = {"]
    for s in shapes:
        S = d["shapes"][s]
        L.append(f"  {{{S['w']},{S['h']},{S['frames']},{col[s]},{(1 if S['dir'] else 0) | (2 if S['spin'] else 0)}}},  // {s}")
    L += ["};", "// por movimiento (mismo orden que MOVES): forma del proyectil, del rayo (-1 = ninguna), de buff y paleta",
          "struct VfxMove { signed char proj, beam, buff, pal; };",
          "static const VfxMove VFX_MOVE[NMOVES] = {"]
    for s in slugs:
        v = d["moves"][s]
        bm = sidx.get(v.get("beam"), -1)
        L.append(f"  {{{sidx.get(v['proj'], sidx['ball'])},{bm},{sidx.get(v.get('buff', 'arrow'), sidx['arrow'])},{pidx.get(v['pal'], 0)}}},  // {s}")
    L += ["};", "static const signed char VFX_TYPE_PAL[18] = {" + ",".join(str(pidx[t]) for t in TYPES) + "};",
          "static const signed char VFX_TYPE_SHAPE[18] = {" + ",".join(
              str(sidx[x]) for x in ["star", "fire", "drop", "bolt", "leaf", "shard", "ball", "blob", "blob",
                                      "wind", "ring", "needle", "rock", "shadow", "fire", "crescent", "shard", "star"]) + "};"]
    (OUT / "include/vfxmeta.h").write_text("\n".join(L) + "\n")
    print(len(shapes), "formas,", len(pals), "paletas,", len(slugs), "movimientos")


main()
