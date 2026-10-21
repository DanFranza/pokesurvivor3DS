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
for (const f of ['js/core/util.js', 'js/core/locales.js', 'js/core/i18n.js', 'js/data/lang-en.js', 'js/core/settings.js', 'js/data/pokedex.js', 'js/data/sprites-meta.js',
                 'js/data/types.js', 'js/data/starters.js', 'js/data/items.js', 'js/data/upgrades.js', 'js/data/natures.js', 'js/data/abilities.js',
                 'js/data/tms.js']) load(f);
load('js/data/ability-fx.js');
load('js/data/moves.js', t => t.replace('G.Moves = {', 'G.__evoMods = EVO_MODS; G.Moves = {'));
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

// ---- evolución de movimientos (web: G.Moves.EVO / EVO_MODS)
{
  const NEED = ['hp', 'atk', 'spd', 'cd', 'def', 'rgn', 'mag', 'xp'];
  const EVO = G.Moves.EVO;
  out.push('static const short EVO_NEED[NMOVES] = {' + ids.map(id => EVO[id] ? NEED.indexOf(EVO[id][1]) : -1).join(',') + '};');
  out.push('static const char* EVO_NAME[NMOVES] = {' + ids.map(id => S(EVO[id] ? EVO[id][0] : '')).join(',') + '};');
  const EM = G.__evoMods;
  out.push('struct EvoMod { UpMod m[6]; unsigned char n; const char* text; };');
  out.push('static const EvoMod EVO_MODS[' + KINDS.length + '] = {');
  for (const k of KINDS) {
    const e = EM[k];
    if (!e) { out.push('  {{},0,""},  // ' + k); continue; }
    const ms = Object.entries(e.m).filter(([kk]) => KEYS.includes(kk)).map(([kk, val]) => `{${KEYS.indexOf(kk)},${ADD.includes(kk) ? 1 : (MULT.includes(kk) ? 0 : 2)},${f(val)}}`);
    out.push(`  {{${ms.join(',')}},${ms.length},${S(e.t)}},  // ${k}`);
  }
  out.push('};', '');
}

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
  if (p.dex === 373) p.rarity = 4;   // Salamence: épico en la 3DS
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

// ---- naturalezas
{
  const NS = ['pa', 'sa', 'df', 'sd', 'spd'];
  out.push('', '// nombres: [es, en, fr, it, zh-Hans, zh-Hant]', 'enum { NS_PA, NS_SA, NS_DF, NS_SD, NS_SPD };',
    'struct NatureE { const char* n[6]; signed char up, down; };', `#define NNAT ${G.NATURES.length}`, 'static const NatureE NATURES[NNAT] = {');
  for (const n of G.NATURES) out.push(`  {{${n.n.map(S).join(',')}},${n.up ? NS.indexOf(n.up) : -1},${n.down ? NS.indexOf(n.down) : -1}},`);
  out.push('};');
}

// ---- habilidades: efectos propios de la 3DS (los que no están usan la pasiva genérica de su tipo)
{
  const AOPS = ['OUT_TYPE', 'OUT_PINCH', 'OUT_CAT', 'OUT_ALL', 'OUT_HALFCAT', 'OUT_STAB', 'OUT_KIND', 'OUT_BOSS', 'OUT_ELOW', 'OUT_ETYPE', 'OUT_WX',
    'OUT_DEFEAT', 'OUT_HIGH', 'IN_ALL', 'IN_TYPE', 'IN_CAT', 'IN_FULL', 'IN_SE', 'IN_WONDER', 'ABSORB', 'SPEED', 'SPEED_WX', 'REGEN', 'REGEN_WX',
    'CRIT', 'CRITMUL', 'MAGNET', 'COINS', 'DODGE', 'DODGE_WX', 'CD', 'HP', 'SUMMON', 'MOXIE', 'STURDY'];
  const o = (op, a, k) => ({ op: AOPS.indexOf(op), a: a == null ? 0 : a, k: k == null ? 0 : k });
  const ty = t => T[t];
  const PH = 0, SP = 1;
  const pinch = t => [o('OUT_PINCH', ty(t), 1.35)], boost = (t, k = 1.2) => [o('OUT_TYPE', ty(t), k)];
  const absorb = t => [o('ABSORB', ty(t))], rush = w => [o('SPEED_WX', w, 1.5)];
  const inT = (t, k) => o('IN_TYPE', ty(t), k), inC = (c, k) => [o('IN_CAT', c, k)], inA = k => [o('IN_ALL', 0, k)];
  const moxie = [o('MOXIE', 0, 0.005)], magnet = k => [o('MAGNET', 0, k)], dodge = p => [o('DODGE', 0, p)];
  const MAP = {
    overgrow: pinch('grass'), blaze: pinch('fire'), torrent: pinch('water'), swarm: pinch('bug'),
    steelworker: boost('steel'), 'steely-spirit': boost('steel'), 'dragons-maw': boost('dragon'), transistor: boost('electric'),
    'water-bubble': [o('OUT_TYPE', ty('water'), 1.4), inT('fire', 0.5)],
    'huge-power': [o('OUT_CAT', PH, 1.5)], 'pure-power': [o('OUT_CAT', PH, 1.5)],
    guts: [o('OUT_HALFCAT', PH, 1.3)], adaptability: [o('OUT_STAB', 0, 1.25)], protean: [o('OUT_ALL', 0, 1.12)], libero: [o('OUT_ALL', 0, 1.12)],
    'tough-claws': [o('OUT_KIND', KINDS.indexOf('melee'), 1.25), o('OUT_KIND', KINDS.indexOf('dash'), 1.25)], reckless: [o('OUT_KIND', KINDS.indexOf('dash'), 1.25)],
    sniper: [o('CRITMUL', 0, 2)], 'super-luck': [o('CRIT', 0, 0.1)], 'compound-eyes': [o('CRIT', 0, 0.06)],
    moxie, 'chilling-neigh': moxie, 'grim-neigh': moxie, 'beast-boost': moxie,
    'swift-swim': rush(2), chlorophyll: rush(1), 'sand-rush': rush(3), 'slush-rush': rush(4), 'run-away': [o('SPEED', 0, 1.08)],
    drought: [o('SUMMON', 1)], 'orichalcum-pulse': [o('SUMMON', 1)], drizzle: [o('SUMMON', 2)], 'sand-stream': [o('SUMMON', 3)], 'snow-warning': [o('SUMMON', 4)],
    'rain-dish': [o('REGEN_WX', 2, 0.015)], 'ice-body': [o('REGEN_WX', 4, 0.015)],
    'dry-skin': [o('ABSORB', ty('water')), inT('fire', 1.25), o('REGEN_WX', 2, 0.012)],
    levitate: [inT('ground', 0.3)], 'thick-fat': [inT('fire', 0.6), inT('ice', 0.6)], heatproof: [inT('fire', 0.5)],
    'water-absorb': absorb('water'), 'storm-drain': absorb('water'), 'volt-absorb': absorb('electric'), 'lightning-rod': absorb('electric'),
    'motor-drive': absorb('electric'), 'flash-fire': absorb('fire'), 'well-baked-body': absorb('fire'), 'sap-sipper': absorb('grass'), 'earth-eater': absorb('ground'),
    multiscale: [o('IN_FULL', 0, 0.5)], 'shadow-shield': [o('IN_FULL', 0, 0.5)],
    filter: [o('IN_SE', 0, 0.75)], 'solid-rock': [o('IN_SE', 0, 0.75)], 'prism-armor': [o('IN_SE', 0, 0.75)],
    'fur-coat': inC(PH, 0.6), fluffy: inC(PH, 0.7), 'ice-scales': inC(SP, 0.6),
    'shell-armor': inA(0.92), 'battle-armor': inA(0.92), pressure: inA(0.92), intimidate: inC(PH, 0.88),
    sturdy: [o('STURDY')], regenerator: [o('REGEN', 0, 0.006)],
    pickup: [o('COINS', 0, 1.15)], 'honey-gather': [o('COINS', 0, 1.15)],
    truant: [o('CD', 0, 1.6), o('OUT_ALL', 0, 1.35)], defeatist: [o('OUT_DEFEAT', 0, 1)], 'wonder-guard': [o('IN_WONDER')],
    schooling: [o('HP', 0, 1.25), o('OUT_HIGH', 0, 1.5)], plus: [o('OUT_CAT', SP, 1.1)], minus: [o('OUT_CAT', SP, 1.1)],
    'no-guard': [o('OUT_ALL', 0, 1.15), o('IN_ALL', 0, 1.1)],
    'keen-eye': [o('CRIT', 0, 0.05)], frisk: magnet(1.2), 'magnet-pull': magnet(1.2), 'sticky-hold': magnet(1.2), illuminate: magnet(1.1),
    'sand-veil': [o('DODGE_WX', 3, 0.15)], 'snow-cloak': [o('DODGE_WX', 4, 0.15)], unnerve: inA(0.94), telepathy: dodge(0.08),
    anticipation: dodge(0.06), forewarn: dodge(0.06), overcoat: inC(SP, 0.95), 'natural-cure': [o('REGEN', 0, 0.003)], healer: [o('REGEN', 0, 0.003)],
    'mold-breaker': [o('OUT_BOSS', 0, 1.12)], soundproof: inC(SP, 0.9), 'big-pecks': inC(PH, 0.92), unaware: inA(0.92), 'friend-guard': inA(0.94),
    analytic: [o('OUT_ELOW', 0, 1.15)], 'hyper-cutter': [o('OUT_CAT', PH, 1.06)], bulletproof: inC(SP, 0.85), protosynthesis: [o('OUT_WX', 1, 1.2)],
    justified: [o('OUT_ETYPE', ty('dark'), 1.15)]
  };
  const PLUS = new Set(['keen-eye', 'frisk', 'magnet-pull', 'sticky-hold', 'illuminate', 'sand-veil', 'snow-cloak', 'unnerve', 'telepathy', 'anticipation', 'forewarn',
    'overcoat', 'natural-cure', 'healer', 'mold-breaker', 'soundproof', 'big-pecks', 'unaware', 'friend-guard', 'analytic', 'hyper-cutter', 'bulletproof', 'protosynthesis', 'justified']);
  const ids = Object.keys(G.ABIL).sort();
  const AI = Object.fromEntries(ids.map((id, i) => [id, i + 1]));
  for (const id of Object.keys(MAP)) if (!AI[id]) console.warn('habilidad desconocida', id);
  out.push('', 'enum { ' + AOPS.map((k, i) => 'AO_' + k + '=' + i).join(',') + ' };',
    'struct AbTerm { unsigned char op; signed char a; float k; };',
    'struct AbilE { const char* n[6]; const char* desc; unsigned char nt, plus; AbTerm t[3]; };',
    `#define NABIL ${ids.length}`, 'static const AbilE ABIL[NABIL] = {');
  for (const id of ids) {
    const m = MAP[id], fx = G.AbilityFX.FX[id];
    if (m && m.length > 3) console.warn('demasiados términos', id);
    const ts = (m || []).map(x => `{${x.op},${x.a},${f(x.k)}}`);
    out.push(`  {{${G.ABIL[id].map(S).join(',')}},${m ? S(fx && fx.d || '') : '""'},${ts.length},${PLUS.has(id) ? 1 : 0},{${ts.join(',')}}},  // ${id}`);
  }
  out.push('};');
  out.push('static const char* GENERIC_DESC[NTYPES] = {' + TYPES.map(t => S(G.AbilityFX.of('x', { types: [t] }).d)).join(',') + '};');
  out.push('// [habilidad 1, habilidad 2, oculta]: índice en ABIL + 1 (0 = no tiene)',
    'static const unsigned short DEX_ABIL[DEX_N][3] = {' + dexList.map(p => { const a = G.DEX_ABIL[p.dex] || [0, 0, 0]; return '{' + [0, 1, 2].map(i => (a[i] ? AI[a[i]] || 0 : 0)).join(',') + '}'; }).join(',') + '};');
}

// ---- MT de la Tienda Kecleon
{
  const tms = Object.keys(G.TM_MOVES).sort();
  out.push('', `#define NTM ${tms.length}`, 'static const short TM_MOVE[NTM] = {' + tms.map(id => (MI[id] == null ? -1 : MI[id])).join(',') + '};   // índice en MOVES (-1 = no está en la 3DS)');
  out.push('static const short TM_PRICE[NTM] = {' + tms.map(id => G.TM_PRICE[id] || 400).join(',') + '};');
  out.push('static const char* TM_ID[NTM] = {' + tms.map(S).join(',') + '};');
  const set = {};
  for (const id of tms) for (const d of G.TM_MOVES[id]) (set[d] = set[d] || []).push(tms.indexOf(id));
  out.push('// bit i = el Pokémon aprende la MT i', 'static const unsigned long long TM_MASK[DEX_N] = {' + dexList.map(p => (set[p.dex] || []).reduce((a, i) => a | (1n << BigInt(i)), 0n) + 'ull').join(',') + '};');
  const miss = tms.filter(id => MI[id] == null); if (miss.length) console.warn('MT sin movimiento en la 3DS:', miss.join(' '));
}

fs.writeFileSync(path.join(ROOT, '3ds/include/gamedata.h'), out.join('\n') + '\n');
console.log(`OK: ${ids.length} movimientos, ${dexList.length} Pokémon, ${TYPES.length} tipos`);
