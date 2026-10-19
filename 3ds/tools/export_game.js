/* Exporta los datos del juego web (pokédex, movimientos, tipos, comportamientos)
 * a include/gamedata.h para la versión 3DS.   node 3ds/tools/export_game.js */
const fs = require('fs'), path = require('path'), vm = require('vm');
const ROOT = path.join(__dirname, '..', '..');
const noop = () => {};
const fakeCtx = new Proxy({}, { get: () => noop });
const G = {};
const sb = {
  G, window: {}, console, Math, JSON, Date, Map, Set, Object, Array, Number, String, RegExp, Promise, Symbol, Infinity, NaN, isFinite, parseInt, parseFloat,
  location: { pathname: '/', protocol: 'file:' }, navigator: { language: 'es', languages: ['es'] }, localStorage: { getItem: () => 'es', setItem: noop },
  document: { documentElement: {}, createElement: () => ({ getContext: () => fakeCtx, width: 0, height: 0 }), addEventListener: noop, querySelector: () => null, body: {} },
  addEventListener: noop, matchMedia: () => ({ matches: false }), CanvasRenderingContext2D: function () {}, Image: function () {}, performance: { now: () => 0 },
  setTimeout: noop, setInterval: noop, requestAnimationFrame: noop
};
sb.window = sb;
vm.createContext(sb);
const read = f => fs.readFileSync(path.join(ROOT, f), 'utf8');
const load = (f, patch) => vm.runInContext(patch ? patch(read(f)) : read(f), sb, { filename: f });
for (const f of ['js/core/util.js', 'js/core/i18n.js', 'js/data/lang-en.js', 'js/core/settings.js', 'js/data/pokedex.js', 'js/data/sprites-meta.js',
                 'js/data/moves.js', 'js/data/types.js', 'js/data/starters.js', 'js/data/items.js', 'js/data/upgrades.js']) load(f);
load('js/data/enemies.js', s => s.replace('function behaviorOf(p) {', 'G.__beh = p => behaviorOf(p); G.__summon = SUMMON; function behaviorOf(p) {'));

const TYPES = Object.keys(G.Types.CHART);
const T = Object.fromEntries(TYPES.map((t, i) => [t, i]));
const SOFT = { 2: 1.6, 0.5: 0.6, 0: 0.3 };
const KEYS = ['cd', 'dmg', 'speed', 'count', 'spread', 'pierce', 'life', 'size', 'radius', 'arc', 'knock', 'width', 'dur', 'rate', 'range',
              'amount', 'stacks', 'charge', 'pull', 'bounce', 'slow', 'stun', 'homing', 'burn', 'poison'];
const MULT = ['dmg','cd','speed','radius','dur','amount','arc','width','spread','life','size','rate','pull','knock','stun','charge'];
const ADD = ['count', 'pierce', 'stacks', 'bounce'];
const KINDS = ['projectile', 'melee', 'beam', 'orbit', 'nova', 'aura', 'buff', 'boomerang', 'chain', 'mine', 'meteor', 'turret', 'dash', 'trail',
               'cone', 'homing', 'bounce', 'charge', 'spin', 'quake', 'vortex', 'shove', 'stun'];
const STATS = ['atk', 'patk', 'satk', 'spd', 'def', 'regen'];
const BEH = ['chase', 'charger', 'ranged', 'tank', 'healer', 'shielder', 'summoner', 'bomber', 'beamer', 'zoner', 'fan', 'jumper', 'runner'];
const S = s => JSON.stringify(String(s == null ? '' : s));
const f = n => (Math.round(n * 10000) / 10000).toString();
const out = ['// GENERADO por tools/export_game.js — no editar a mano', '#pragma once', ''];

// ---- tipos
out.push(`#define NTYPES ${TYPES.length}`, 'static const char* TYPE_NAMES[NTYPES] = {' + TYPES.map(S).join(',') + '};');
const col = G.U.TYPE_COLOR || {};
const hex = c => { c = (c || '#999999').replace('#', ''); return '0x' + c.slice(0, 6); };
out.push('static const unsigned TYPE_RGB[NTYPES] = {' + TYPES.map(t => hex(col[t])).join(',') + '};');
out.push('static const float TYPE_CHART[NTYPES][NTYPES] = {');
for (const a of TYPES) {
  out.push('  {' + TYPES.map(d => { const v = G.Types.CHART[a][d]; return f(v == null ? 1 : SOFT[v]); }).join(',') + '},');
}
out.push('};', '');

// ---- movimientos
const ids = Object.keys(G.Moves.BY_ID);
const MI = Object.fromEntries(ids.map((id, i) => [id, i]));
out.push('enum { NK_ = ' + KEYS.length + ' };');
out.push('enum { ' + KEYS.map((k, i) => 'K_' + k.toUpperCase() + '=' + i).join(',') + ' };');
out.push('enum { ' + KINDS.map((k, i) => 'MK_' + k.toUpperCase() + '=' + i).join(',') + ' };');
out.push('enum { ' + STATS.map((k, i) => 'ST_' + k.toUpperCase() + '=' + i).join(',') + ' };');
out.push('struct UpMod { unsigned char key, op; float v; };   // op 0 ×, 1 +, 2 =',
         'struct MoveUp { UpMod m[4]; unsigned char n; const char* text; };',
         'struct MoveDef { const char* name; const char* desc; unsigned char type, kind, cat, stat; float v[NK_]; MoveUp ups[4]; };',
         `#define NMOVES ${ids.length}`, 'static const MoveDef MOVES[NMOVES] = {');
const catOf = m => (m.cat === 'special' ? 1 : m.cat === 'physical' ? 0 : 2);
for (const id of ids) {
  const m = G.Moves.BY_ID[id];
  const v = KEYS.map(k => f(m[k] == null ? 0 : m[k]));
  const ups = [0, 1, 2, 3].map(i => {
    const u = (m.ups || [])[i];
    if (!u) return '{{},0,""}';
    const mods = Object.entries(u.m).filter(([k]) => KEYS.includes(k)).slice(0, 4);
    const ms = mods.map(([k, val]) => `{${KEYS.indexOf(k)},${ADD.includes(k) ? 1 : (MULT.includes(k) ? 0 : 2)},${f(val)}}`);
    return `{{${ms.join(',')}},${ms.length},${S(u.t)}}`;
  });
  out.push(`  {${S(m.name)},${S(m.desc)},${T[m.type]},${KINDS.indexOf(m.kind)},${catOf(m)},${Math.max(0, STATS.indexOf(m.stat))},{${v.join(',')}},{${ups.join(',')}}},  // ${id}`);
}
out.push('};', '');
const unknownKinds = ids.filter(id => KINDS.indexOf(G.Moves.BY_ID[id].kind) < 0);
if (unknownKinds.length) console.warn('tipos de movimiento desconocidos', unknownKinds);

// ---- pools de movimientos por tipo
const POOL = G.Moves.POOL;
const flat = [], offs = [];
for (const t of ['normal', ...TYPES.filter(t => t !== 'normal')]) {
  const l = (POOL[t] || []).map(id => MI[id]).filter(i => i != null);
  offs.push([t, flat.length, l.length]);
  flat.push(...l);
}
out.push('static const short POOL_ALL[] = {' + flat.join(',') + '};');
out.push('struct PoolRef { short off, n; };', 'static const PoolRef POOL_BY_TYPE[NTYPES] = {' +
  TYPES.map(t => { const o = offs.find(x => x[0] === t); return `{${o[1]},${o[2]}}`; }).join(',') + '};', '');

// ---- pokédex
const dexList = G.DEX;
out.push('enum { ' + BEH.map((b, i) => 'B_' + b.toUpperCase() + '=' + i).join(',') + ' };');
out.push('struct DexE { const char* name; unsigned char t1, t2, rarity, gen, leg, beh, start; short minion; unsigned short hp, spd, bst; float atk, pa, sa; unsigned char df, sd; };');
out.push(`#define DEX_N ${dexList.length}`, 'static const DexE DEX[DEX_N] = {');
const dexIdx = {};
dexList.forEach((p, i) => { dexIdx[p.dex] = i; });
for (const p of dexList) {
  let start = 0;
  try { start = MI[G.Moves.startFor(G.STARTERS.find(x => x.dex === p.dex) || p)] || 0; } catch (e) { /* sin movimiento inicial */ }
  const beh = Math.max(0, BEH.indexOf(G.__beh(p)));
  const mn = G.__summon[p.dex] || 0;
  out.push(`  {${S(p.name)},${T[p.types[0]]},${p.types[1] ? T[p.types[1]] : 255},${p.rarity},${p.gen},${p.leg ? 1 : 0},${beh},${start},${mn},${p.hp},${p.spd},${p.bst},${f(p.atk)},${f(p.pa)},${f(p.sa)},${p.df},${p.sd}},  // #${p.dex}`);
}
out.push('};', '');
out.push('static const short DEX_NUM[DEX_N] = {' + dexList.map(p => p.dex).join(',') + '};   // número de pokédex de cada fila');
out.push('static const short STARTERS_IDX[] = {' + G.STARTERS.map(s => dexIdx[s.dex]).join(',') + '};');
out.push(`#define NSTARTERS ${G.STARTERS.length}`, '');

// ---- objetos y mejoras permanentes
out.push(`#define NITEMS ${G.Items.LIST.length}`, 'static const char* ITEM_NAMES[NITEMS] = {' + G.Items.LIST.map(i => S(i.name)).join(',') + '};');
out.push('static const char* ITEM_DESCS[NITEMS] = {' + G.Items.LIST.map(i => S(i.desc)).join(',') + '};');
const UPG = G.Upgrades.LIST;
out.push('struct PermUp { const char* name; const char* unit; unsigned char max; float base, grow; };');
out.push(`#define NPERM ${UPG.length}`, 'static const PermUp PERM[NPERM] = {' +
  UPG.map(u => `{${S(u.name)},${S(u.unit)},${u.max},${u.base},${u.grow}}`).join(',') + '};');
out.push('static const char* PERM_IDS[NPERM] = {' + UPG.map(u => S(u.id)).join(',') + '};');

fs.writeFileSync(path.join(ROOT, '3ds/include/gamedata.h'), out.join('\n') + '\n');
console.log(`OK: ${ids.length} movimientos, ${dexList.length} Pokémon, ${TYPES.length} tipos`);
