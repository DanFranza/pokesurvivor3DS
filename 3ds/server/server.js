// Servidor comunitario de PokéSurvivor 3DS: pseudos y clasificaciones.
// Protocolo de texto por TCP (una línea por orden), sin dependencias.
//   uso:  node server.js [puerto]        (por defecto 25570)
//   C→S:  HELLO <proto> <id> <pseudo> <mejorTiempo> <bajasTotales> <mejorNivel> <victorias>
//         TOP <categoría 0..3>
//   S→C:  ROW <puesto> <pseudo> <valor> ... END <miPuesto> <total>      |   ERR <motivo>
// Categorías: 0 tiempo (s) · 1 bajas · 2 nivel · 3 victorias.
// Los datos se guardan en ranking.json junto al servidor.
const net = require('net'), fs = require('fs'), path = require('path');
const PORT = parseInt(process.argv[2] || process.env.PORT || '25570', 10);
const FILE = path.join(__dirname, 'ranking.json');
const PROTO = 1, MAXP = 20000, TOPN = 10;

let players = {};                              // id → {nick, t, k, l, w, seen}
try { players = JSON.parse(fs.readFileSync(FILE, 'utf8')); } catch (e) { players = {}; }
let dirty = false;
setInterval(() => {
  if (!dirty) return;
  dirty = false;
  fs.writeFile(FILE + '.tmp', JSON.stringify(players), err => { if (!err) fs.rename(FILE + '.tmp', FILE, () => {}); });
}, 5000);

const KEY = ['t', 'k', 'l', 'w'];
const clean = n => String(n).replace(/[^A-Za-z0-9_\-]/g, '').slice(0, 12);
const num = (s, max) => Math.max(0, Math.min(max, parseInt(s, 10) || 0));

function hello(a) {
  if (a.length < 8 || parseInt(a[1], 10) !== PROTO) return 'ERR PROTO';
  const id = a[2].replace(/[^0-9a-f]/gi, '').slice(0, 8).toLowerCase();
  const nick = clean(a[3]);
  if (!id || nick.length < 2) return 'ERR NICK';
  for (const k in players) if (k !== id && players[k].nick.toLowerCase() === nick.toLowerCase()) return 'ERR NAMETAKEN';
  let p = players[id];
  if (!p) {
    if (Object.keys(players).length >= MAXP) return 'ERR FULL';
    p = players[id] = { nick, t: 0, k: 0, l: 0, w: 0, seen: 0 };
  }
  p.nick = nick; p.seen = Date.now();
  p.t = Math.max(p.t, num(a[4], 86400)); p.k = Math.max(p.k, num(a[5], 1e9));
  p.l = Math.max(p.l, num(a[6], 999)); p.w = Math.max(p.w, num(a[7], 1e6));
  dirty = true;
  return { id };
}

function top(cat, id) {
  const k = KEY[cat];
  const all = Object.entries(players).filter(([, p]) => p[k] > 0).sort((a, b) => b[1][k] - a[1][k] || a[1].seen - b[1].seen);
  const out = all.slice(0, TOPN).map(([, p], i) => `ROW ${i + 1} ${p.nick} ${p[k]}`);
  const me = all.findIndex(([pid]) => pid === id);
  out.push(`END ${me + 1} ${all.length}`);
  return out.join('\n');
}

const hits = new Map();
setInterval(() => hits.clear(), 60000);

net.createServer(sock => {
  const ip = sock.remoteAddress;
  const n = (hits.get(ip) || 0) + 1; hits.set(ip, n);
  if (n > 60) return sock.destroy();
  sock.setTimeout(6000, () => sock.destroy());
  sock.on('error', () => sock.destroy());
  let buf = '', id = null;
  sock.on('data', d => {
    buf += d.toString('latin1');
    if (buf.length > 1024) return sock.destroy();
    let i;
    while ((i = buf.indexOf('\n')) >= 0) {
      const a = buf.slice(0, i).trim().split(/\s+/); buf = buf.slice(i + 1);
      if (a[0] === 'HELLO') {
        const r = hello(a);
        if (typeof r === 'string') { sock.end(r + '\n'); return; }
        id = r.id;
      } else if (a[0] === 'TOP' && id) {
        sock.end(top(num(a[1], 3), id) + '\n'); return;
      } else { sock.end('ERR BAD\n'); return; }
    }
  });
}).listen(PORT, () => console.log(`PokéSurvivor 3DS · servidor comunitario en el puerto ${PORT}`));
