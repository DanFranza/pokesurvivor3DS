// Genera include/pkname.h: nombres de Pokémon en inglés y francés por fila de DEX (fuente: PokéAPI, pokemon_species_names.csv).
// Uso: curl -sL https://raw.githubusercontent.com/PokeAPI/pokeapi/master/data/v2/csv/pokemon_species_names.csv -o /tmp/psn.csv && node tools/export_names.js /tmp/psn.csv
const fs = require('fs'), path = require('path');
const root = path.join(__dirname, '..');
const g = fs.readFileSync(path.join(root, 'include/gamedata.h'), 'utf8');
const nums = g.match(/DEX_NUM\[DEX_N\] = \{([^}]*)\}/)[1].split(',').map(Number);
const en = {}, fr = {};
for (const l of fs.readFileSync(process.argv[2], 'utf8').split('\n')) {
  const p = l.split(',');
  if (p[1] === '9') en[p[0]] = p[2];
  if (p[1] === '5') fr[p[0]] = p[2];
}
const q = s => '"' + s.replace(/\\/g, '\\\\').replace(/"/g, '\\"') + '"';
let miss = 0;
const rows = nums.map(n => { if (!en[n] || !fr[n]) miss++; return `  {${q(en[n] || '')}, ${q(fr[n] || '')}},`; });
fs.writeFileSync(path.join(root, 'include/pkname.h'), ['// GENERADO por tools/export_names.js — no editar', '#pragma once',
  'static const char* const PK_NAMES[][2] = {   // {inglés, francés} por fila de DEX', ...rows, '};', ''].join('\n'));
console.log(nums.length, 'nombres; sin traducción:', miss);
