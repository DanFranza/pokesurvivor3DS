// Genera include/pkname.h: nombres de Pokémon en inglés y francés por fila de DEX (fuente: PokéAPI, pokemon_species_names.csv).
// Uso: curl -sL https://raw.githubusercontent.com/PokeAPI/pokeapi/master/data/v2/csv/pokemon_species_names.csv -o /tmp/psn.csv && node tools/export_names.js /tmp/psn.csv
const fs = require('fs'), path = require('path');
const root = path.join(__dirname, '..');
const g = fs.readFileSync(path.join(root, 'include/gamedata.h'), 'utf8');
const nums = g.match(/DEX_NUM\[DEX_N\] = \{([^}]*)\}/)[1].split(',').map(Number);
const regional = Object.fromEntries(JSON.parse(fs.readFileSync(path.join(root, 'tools/modern_dex.json'), 'utf8')).pokemon
  .filter(p => p.reg).map(p => [p.dex, p]));
const en = {}, fr = {}, it = {}, zs = {}, zt = {};
for (const l of fs.readFileSync(process.argv[2], 'utf8').split('\n')) {
  const p = l.split(',');
  if (p[1] === '9') en[p[0]] = p[2];
  if (p[1] === '5') fr[p[0]] = p[2];
  if (p[1] === '8') it[p[0]] = p[2];
  if (p[1] === '12') zs[p[0]] = p[2];
  if (p[1] === '4') zt[p[0]] = p[2];
}
const q = s => '"' + s.replace(/\\/g, '\\\\').replace(/"/g, '\\"') + '"';
let miss = 0;
// Chino: nombres de la web (por nombre inglés); si falta, PokéAPI. Portugués: inglés, como la web.
const webZh = f => { const o = {}, r = /"((?:[^"\\]|\\.)*)"\s*:\s*"((?:[^"\\]|\\.)*)"/g; let m, t = fs.readFileSync(path.join(root, '../js/data', f), 'utf8'); while ((m = r.exec(t))) o[m[1]] = m[2]; return o; };
const wzs = webZh('lang-zh-cn-names.js'), wzt = webZh('lang-zh-hant-names.js');
const suffix = {1: [' of Alola', " d'Alola", ' di Alola', ' de Alola'],
  2: [' of Galar', ' de Galar', ' di Galar', ' de Galar'],
  3: [' of Hisui', ' de Hisui', ' di Hisui', ' de Hisui'],
  4: [' of Paldea', ' de Paldea', ' di Paldea', ' de Paldea']};
const rows = nums.map(n => {
  const r = regional[n], base = r ? r.num : n, suf = r ? suffix[r.reg] : ['', '', '', ''];
  if (!en[base] || !fr[base]) miss++;
  const names = [en[base], fr[base], it[base] || en[base], en[base]].map((name, i) => name ? name + suf[i] : '');
  if (r && r.num === 128) {
    const breed = r.dex === 1056 ? [' (Aqua Breed)', ' (Race Aqua)', ' (Forma Acqua)', ' (Raça Aquática)']
      : r.dex === 1057 ? [' (Blaze Breed)', ' (Race Flamme)', ' (Forma Fuoco)', ' (Raça Ardente)']
      : [' (Combat Breed)', ' (Race Combat)', ' (Forma Lotta)', ' (Raça de Combate)'];
    for (let i = 0; i < 4; i++) names[i] += breed[i];
  }
  return `  {${names.map(q).join(', ')}, ${q(wzs[en[base]] || zs[base] || '')}, ${q(wzt[en[base]] || zt[base] || '')}},`;
});
fs.writeFileSync(path.join(root, 'include/pkname.h'), ['// GENERADO por tools/export_names.js — no editar', '#pragma once',
  'static const char* const PK_NAMES[DEX_N][6] = {   // {en, fr, it, pt-BR, zh-Hans, zh-Hant} por fila de DEX', ...rows, '};', ''].join('\n'));
console.log(nums.length, 'nombres; sin traducción:', miss);
