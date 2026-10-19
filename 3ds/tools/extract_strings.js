// Recoge los textos en español del código 3DS y busca su traducción inglesa en la web.
// Salida: tools/lang_todo.json  {es: en|null}. Uso: node tools/extract_strings.js
const fs = require('fs'), path = require('path');
const root = path.join(__dirname, '..');
let src = '';
for (const f of fs.readdirSync(path.join(root, 'source'))) if (f.endsWith('.cpp')) src += fs.readFileSync(path.join(root, 'source', f), 'utf8') + '\n';
let gd = fs.readFileSync(path.join(root, 'include/gamedata.h'), 'utf8');
gd = gd.replace(/static const DexE DEX\[[\s\S]*?\n\};/, '').replace(/static const char\* TYPE_NAMES[^\n]*\n/, '');
src += gd + fs.readFileSync(path.join(root, 'include/tiles.h'), 'utf8');
src = src.replace(/\/\/[^\n]*/g, '');

const en = {};
const web = fs.readFileSync(path.join(root, '../js/data/lang-en.js'), 'utf8');
const re = /'((?:[^'\\]|\\.)*)'\s*:\s*'((?:[^'\\]|\\.)*)'/g;
let m;
while ((m = re.exec(web))) en[m[1].replace(/\\'/g, "'")] = m[2].replace(/\\'/g, "'");

const out = {};
const lit = /"((?:[^"\\]|\\.)*)"/g;
while ((m = lit.exec(src))) {
  let s = m[1].replace(/\\n/g, '\n').replace(/\\"/g, '"');
  if (!/[A-Za-zÁÉÍÓÚáéíóúñÑ]{2}/.test(s)) continue;
  if (/^(romfs|sdmc):|\.h$|\.t3x|^%/.test(s) || s.length < 2) continue;
  if (/^[a-z_]+$/.test(s) && s.length < 12 && !en[s]) continue;
  out[s] = en[s] || null;
}
fs.writeFileSync(path.join(root, 'tools/lang_todo.json'), JSON.stringify(out, null, 1));
const keys = Object.keys(out);
console.log(keys.length, 'textos;', keys.filter(k => out[k]).length, 'con inglés de la web');
