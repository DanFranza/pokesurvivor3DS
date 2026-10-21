// Genera include/lang.h: tabla ordenada {es, en, fr}.
// Entradas: tools/lang_todo.json (inglés de la web), tools/lang_en.json (inglés extra) y tools/lang_fr.json (francés).
// Uso: node tools/extract_strings.js && node tools/export_lang.js
const fs = require('fs'), path = require('path');
const dir = __dirname;
const rd = f => { const p = path.join(dir, f); return fs.existsSync(p) ? JSON.parse(fs.readFileSync(p, 'utf8')) : {}; };
const todo = rd('lang_todo.json'), enx = rd('lang_en.json'), fr = rd('lang_fr.json');
// Diccionarios de la web (js/lang/*.js, clave = texto en español); sirven de base y el JSON propio de 3DS manda.
const web = f => { const w = { PS_LANG_Q: [] }; new Function('window', fs.readFileSync(path.join(dir, '../../js/lang', f), 'utf8'))(w); return Object.assign({}, ...w.PS_LANG_Q.map(x => x[0])); };
const wf = web('fr.js'), wi = web('it.js'), wp = web('pt-BR.js'), wzs = web('zh-Hans.js'), wzt = web('zh-Hant.js');
const keys = Object.keys(todo).sort((a, b) => Buffer.compare(Buffer.from(a), Buffer.from(b)));
const q = s => '"' + s.replace(/\\/g, '\\\\').replace(/"/g, '\\"').replace(/\n/g, '\\n') + '"';
const miss = { en: [], fr: [] };
const clean = v => (v && !/\{x\}|\{[a-z]+\}/.test(v) ? v : '');
const rows = keys.map(k => {
  const e = enx[k] || todo[k] || '', f = fr[k] || clean(wf[k]);
  const it = clean(wi[k]) || e, pt = clean(wp[k]) || e, zs = clean(wzs[k]) || e, zt = clean(wzt[k]) || e;
  if (!e) miss.en.push(k);
  if (!f) miss.fr.push(k);
  return `  {${q(k)}, {${q(e)}, ${q(f)}, ${q(it)}, ${q(pt)}, ${q(zs)}, ${q(zt)}}},`;
});
const out = ['// GENERADO por tools/export_lang.js — no editar', '#pragma once',
  'struct LangStr { const char* es; const char* tr[6]; };   // en, fr, it, pt-BR, zh-Hans, zh-Hant',
  `#define LANG_N_STR ${keys.length}`, 'static const LangStr LANG_STR[LANG_N_STR] = {', ...rows, '};', ''];
fs.writeFileSync(path.join(dir, '../include/lang.h'), out.join('\n'));
console.log(keys.length, 'textos; sin inglés:', miss.en.length, '; sin francés:', miss.fr.length);
