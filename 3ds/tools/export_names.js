// Genera include/pkname.h: nombres de Pokémon en inglés y francés por fila de DEX (fuente: PokéAPI, pokemon_species_names.csv).
// Uso: curl -sL https://raw.githubusercontent.com/PokeAPI/pokeapi/master/data/v2/csv/pokemon_species_names.csv -o /tmp/psn.csv && node tools/export_names.js /tmp/psn.csv
const fs = require('fs'), path = require('path');
const root = path.join(__dirname, '..');
const g = fs.readFileSync(path.join(root, 'include/gamedata.h'), 'utf8');
const nums = g.match(/DEX_NUM\[DEX_N\] = \{([^}]*)\}/)[1].split(',').map(Number);
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
const rows = nums.map(n => { if (!en[n] || !fr[n]) miss++;
  return `  {${q(en[n] || '')}, ${q(fr[n] || '')}, ${q(it[n] || en[n] || '')}, ${q(en[n] || '')}, ${q(wzs[en[n]] || zs[n] || '')}, ${q(wzt[en[n]] || zt[n] || '')}},`; });
fs.writeFileSync(path.join(root, 'include/pkname.h'), ['// GENERADO por tools/export_names.js — no editar', '#pragma once',
  'static const char* const PK_NAMES[][6] = {   // {en, fr, it, pt-BR, zh-Hans, zh-Hant} por fila de DEX', ...rows, '};', ''].join('\n'));
console.log(nums.length, 'nombres; sin traducción:', miss);
