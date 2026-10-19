// Genera include/lang.h: tabla ordenada {es, en, fr}.
// Entradas: tools/lang_todo.json (inglés de la web), tools/lang_en.json (inglés extra) y tools/lang_fr.json (francés).
// Uso: node tools/extract_strings.js && node tools/export_lang.js
const fs = require('fs'), path = require('path');
const dir = __dirname;
const rd = f => { const p = path.join(dir, f); return fs.existsSync(p) ? JSON.parse(fs.readFileSync(p, 'utf8')) : {}; };
const todo = rd('lang_todo.json'), enx = rd('lang_en.json'), fr = rd('lang_fr.json');
const keys = Object.keys(todo).sort((a, b) => Buffer.compare(Buffer.from(a), Buffer.from(b)));
const q = s => '"' + s.replace(/\\/g, '\\\\').replace(/"/g, '\\"').replace(/\n/g, '\\n') + '"';
const miss = { en: [], fr: [] };
const rows = keys.map(k => {
  const e = enx[k] || todo[k] || '', f = fr[k] || '';
  if (!e) miss.en.push(k);
  if (!f) miss.fr.push(k);
  return `  {${q(k)}, {${q(e)}, ${q(f)}}},`;
});
const out = ['// GENERADO por tools/export_lang.js — no editar', '#pragma once',
  'struct LangStr { const char* es; const char* tr[2]; };   // tr[0] = inglés, tr[1] = francés',
  `#define LANG_N_STR ${keys.length}`, 'static const LangStr LANG_STR[LANG_N_STR] = {', ...rows, '};', ''];
fs.writeFileSync(path.join(dir, '../include/lang.h'), out.join('\n'));
console.log(keys.length, 'textos; sin inglés:', miss.en.length, '; sin francés:', miss.fr.length);
