// Compila las partituras de js/data/music.js a include/music.h (eventos por paso de semicorchea).
// Uso: node tools/export_music.js
const fs = require('fs'), path = require('path'), vm = require('vm');
const root = path.join(__dirname, '..', '..');
const G = {};
vm.runInNewContext(fs.readFileSync(path.join(root, 'js/data/music.js'), 'utf8'), { G });

const NOTE = { C: 0, D: 2, E: 4, F: 5, G: 7, A: 9, B: 11 };
const midiOf = n => { const m = /^([A-G])(#|b)?(-?\d)$/.exec(n); return m ? 12 * (+m[3] + 1) + NOTE[m[1]] + (m[2] === '#' ? 1 : m[2] === 'b' ? -1 : 0) : null; };
const parseChord = c => {
  const m = /^([A-G])(#|b)?(m?)(?:\/([A-G])(#|b)?)?$/.exec(c);
  const pc = (l, a) => (NOTE[l] + (a === '#' ? 1 : a === 'b' ? -1 : 0) + 12) % 12;
  const root = pc(m[1], m[2]);
  return { root, minor: m[3] === 'm', bass: m[4] ? pc(m[4], m[5]) : root };
};
const INST = ['flute', 'bell', 'pluck', 'bass', 'pad', 'lead', 'kick', 'snare', 'hat', 'shaker'];

function compile(song) {
  const bars = song.bars || song.chords.length, steps = bars * 16, ev = [];
  const add = (s, inst, midi, len, v) => ev.push([s, INST.indexOf(inst), midi, len, Math.round(v * 100)]);
  for (const tr of song.melody || []) tr.bars.forEach((bar, bi) => {
    let s = 0;
    for (const tok of bar.trim().split(/\s+/)) {
      const [n, len] = tok.split(':'); const L = +len || 1;
      if (n !== '-') add((bi * 16 + s) % steps, tr.inst, midiOf(n) + (tr.shift || 0), L, tr.vel || 1);
      s += L;
    }
  });
  const chords = song.chords.map(parseChord);
  const tone = (ch, i, base) => base + ch.root + [0, ch.minor ? 3 : 4, 7, 12, 12 + (ch.minor ? 3 : 4), 19][i];
  for (let b = 0; b < bars; b++) {
    const ch = chords[b % chords.length];
    for (const tr of song.parts || []) {
      const pat = tr.pattern, base = 12 * (tr.octave + 1);
      for (let s = 0; s < 16; s++) {
        const c = pat[s];
        if (!c || c === '.' || c === '-') continue;
        let len = 1; while (s + len < 16 && pat[s + len] === '-') len++;
        let midi;
        if (c === 'R') midi = base + (tr.useBass ? ch.bass : ch.root);
        else if (c === 'F') midi = base + ch.root + 7;
        else if (c === 'O') midi = base + ch.root + 12;
        else if (c === 'T') midi = base + ch.root + (ch.minor ? 3 : 4);
        else if (c === 'C') { for (let i = 0; i < 3; i++) add(b * 16 + s, tr.inst, tone(ch, i, base), len, tr.vel || 1); continue; }
        else midi = tone(ch, +c, base);
        add(b * 16 + s, tr.inst, midi, len, tr.vel || 1);
      }
    }
    for (const [inst, pat] of Object.entries(song.drums || {}))
      for (let s = 0; s < 16; s++) { const c = pat[s]; if (c && c !== '.') add(b * 16 + s, inst, 0, 1, c === 'X' ? 1 : c === 'x' ? 0.75 : 0.45); }
  }
  ev.sort((a, b) => a[0] - b[0]);
  return { steps, ev, bpm: song.bpm, swing: Math.round((song.swing || 0) * 100) };
}

const songs = ['village', 'forest', 'boss'];
let h = '// Generado por tools/export_music.js — no editar.\n#pragma once\nstruct SongEv { unsigned short step; unsigned char inst, midi, len, vel; };\nstruct SongDef { const SongEv* ev; int n, steps, bpm, swing; };\n';
const defs = [];
for (const name of songs) {
  const c = compile(G.MUSIC[name]);
  h += `static const SongEv SONG_${name}[] = {${c.ev.map(e => `{${e[0]},${e[1]},${e[2]},${e[3]},${e[4]}}`).join(',')}};\n`;
  defs.push(`{SONG_${name},${c.ev.length},${c.steps},${c.bpm},${c.swing}}`);
}
h += `static const SongDef SONGS[${songs.length}] = {${defs.join(',')}};\n`;
fs.writeFileSync(path.join(__dirname, '..', 'include', 'music.h'), h);
console.log('canciones', songs.length, 'bytes', h.length);
