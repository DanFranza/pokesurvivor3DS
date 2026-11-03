// Audio: sintetizador por software (mono, 22 kHz) servido a ndsp. Música generada desde las partituras de la versión web.
#include "game.h"
#include "music.h"

static const int RATE = 22050, BUFS = 4, BUFN = 1102;
enum { I_FLUTE, I_BELL, I_PLUCK, I_BASS, I_PAD, I_LEAD, I_KICK, I_SNARE, I_HAT, I_SHAKER, I_SFX };

struct Voice {
    bool on, music;
    u8 inst, wave;                 // wave (sólo sfx): 0 seno, 1 cuadrada, 2 triángulo, 3 ruido
    float ph, ph2, f, ratio, age, dur, vol;
    float prev;
};
static Voice gV[24];
static ndspWaveBuf gWb[BUFS];
static s16* gBuf;
static bool gOk;
static int gSong = -1, gStep;
static double gStepAt, gClock;
static float gFade;
static bool gSpooky; static int gTonic;   // Halloween: tempo más lento, tono menor y campana grave
static u32 gNoise = 12345;
static double gSfxLast[SFX_N];

// WAV IMA ADPCM mono, décodé par blocs pour éviter de charger la musique en RAM.
static FILE* gTrack;
static long gTrackData, gTrackEnd;
static s16 gTrackSamples[2048];
static int gTrackPos, gTrackCount;
static const int IMA_STEP[89] = {7,8,9,10,11,12,13,14,16,17,19,21,23,25,28,31,34,37,41,45,50,55,60,66,73,80,88,97,107,118,130,143,157,173,190,209,230,253,279,307,337,371,408,449,494,544,598,658,724,796,876,963,1060,1166,1282,1411,1552,1707,1878,2066,2272,2499,2749,3024,3327,3660,4026,4428,4871,5358,5894,6484,7132,7845,8630,9493,10442,11487,12635,13899,15289,16818,18500,20350,22385,24623,27086,29794,32767};
static const int IMA_INDEX[16] = {-1,-1,-1,-1,2,4,6,8,-1,-1,-1,-1,2,4,6,8};
static u32 readLE32(const u8* p) { return (u32)p[0] | (u32)p[1]<<8 | (u32)p[2]<<16 | (u32)p[3]<<24; }
static void trackClose() { if (gTrack) fclose(gTrack); gTrack = nullptr; gTrackPos = gTrackCount = 0; }
static bool trackOpen(int choice) {
    trackClose();
    if (choice < 1 || choice > 6) return false;
    char path[40]; snprintf(path, sizeof path, "romfs:/music/%d.wav", choice);
    gTrack = fopen(path, "rb"); if (!gTrack) return false;
    u8 h[12]; if (fread(h, 1, 12, gTrack) != 12 || memcmp(h, "RIFF", 4) || memcmp(h+8, "WAVE", 4)) { trackClose(); return false; }
    bool format = false;
    for (int i = 0; i < 64; i++) {
        u8 chunk[8]; if (fread(chunk, 1, 8, gTrack) != 8) break;
        u32 n = readLE32(chunk+4); long start = ftell(gTrack);
        if (!memcmp(chunk, "fmt ", 4) && n >= 20) {
            u8 f[20]; if (fread(f, 1, 20, gTrack) != 20) break;
            format = f[0] == 17 && f[1] == 0 && f[2] == 1 && f[3] == 0 && readLE32(f+4) == RATE && f[12] == 0 && f[13] == 4;
        } else if (!memcmp(chunk, "data", 4) && format) {
            gTrackData = start; gTrackEnd = start + n; return true;
        }
        if (fseek(gTrack, start + n + (n & 1), SEEK_SET)) break;
    }
    trackClose(); return false;
}
static float trackSample() {
    if (!gTrack) return 0;
    if (gTrackPos >= gTrackCount) {
        if (ftell(gTrack) >= gTrackEnd) fseek(gTrack, gTrackData, SEEK_SET);
        u8 block[1024]; long left = gTrackEnd - ftell(gTrack);
        size_t n = fread(block, 1, left < 1024 ? (size_t)left : 1024, gTrack);
        if (n < 4) { trackClose(); return 0; }
        int pred = (s16)(block[0] | block[1] << 8), index = block[2];
        if (index > 88) { trackClose(); return 0; }
        gTrackCount = 0; gTrackSamples[gTrackCount++] = (s16)pred;
        for (size_t j = 4; j < n; j++) for (int half = 0; half < 2; half++) {
            int code = half ? block[j] >> 4 : block[j] & 15, step = IMA_STEP[index];
            int diff = step >> 3; if (code & 1) diff += step >> 2; if (code & 2) diff += step >> 1; if (code & 4) diff += step;
            pred += (code & 8) ? -diff : diff; if (pred < -32768) pred = -32768; if (pred > 32767) pred = 32767;
            index += IMA_INDEX[code]; if (index < 0) index = 0; if (index > 88) index = 88;
            gTrackSamples[gTrackCount++] = (s16)pred;
        }
        gTrackPos = 0;
    }
    return gTrackSamples[gTrackPos++] / 32768.0f;
}

struct SfxDef { u8 wave; float f0, f1, dur, vol, gap; };
static const SfxDef SFX[SFX_N] = {
    /*HIT*/ {2, 220, 110, 0.05f, 0.22f, 0.05f},   /*KILL*/ {3, 330, 110, 0.09f, 0.20f, 0.06f},
    /*PICK*/ {0, 880, 1320, 0.06f, 0.18f, 0.04f}, /*LEVEL*/ {0, 523, 1047, 0.35f, 0.30f, 0.2f},
    /*HURT*/ {1, 160, 80, 0.16f, 0.26f, 0.12f},   /*SHOOT*/ {2, 600, 300, 0.05f, 0.12f, 0.07f},
    /*BOOM*/ {3, 200, 60, 0.30f, 0.40f, 0.1f},    /*BOSS*/ {1, 110, 55, 0.7f, 0.30f, 0.5f},
    /*UI*/ {0, 700, 900, 0.05f, 0.20f, 0.03f},    /*GACHA*/ {0, 400, 1200, 0.45f, 0.28f, 0.1f},
    /*RARE*/ {0, 784, 1568, 0.7f, 0.30f, 0.1f},   /*OVER*/ {2, 330, 82, 0.9f, 0.30f, 0.5f},
    /*BEAM*/ {1, 440, 440, 0.08f, 0.10f, 0.1f},
};

static inline float noise() { gNoise = gNoise * 1664525u + 1013904223u; return ((gNoise >> 8) & 0xFFFF) / 32768.0f - 1.0f; }
static inline float tri(float p) { return p < 0.5f ? 4 * p - 1 : 3 - 4 * p; }
static inline float expo(float x) { return x < 0 ? 1 : (1 - x) * (1 - x); }

static Voice* freeVoice() {
    for (Voice& v : gV) if (!v.on) return &v;
    return nullptr;
}

static void startNote(const SongEv& e, float stepSamples) {
    Voice* v = freeVoice();
    if (!v) return;
    *v = Voice();
    v->on = true; v->music = true; v->inst = e.inst;
    v->vol = e.vel / 100.0f;
    v->dur = e.len * stepSamples;
    if (e.inst < I_KICK) {
        int m = e.midi;
        if (gSpooky) { int d = ((m - gTonic) % 12 + 12) % 12; if (d == 4 || d == 9 || d == 11) m--; }
        v->f = 440.0f * powf(2.0f, (m - 69) / 12.0f);
    }
    else if (e.inst == I_KICK) { v->f = 150; v->ratio = powf(42.0f / 150.0f, 1.0f / (0.13f * RATE)); v->dur = 0.22f * RATE; }
    else if (e.inst == I_SNARE) { v->f = 190; v->dur = 0.13f * RATE; }
    else if (e.inst == I_HAT) v->dur = 0.05f * RATE;
    else v->dur = 0.08f * RATE;
}

static float voiceSample(Voice& v) {
    float t = v.age / RATE, out = 0;
    float rem = v.dur - v.age;
    switch (v.inst) {
        case I_FLUTE: {
            float env = fminf(1.0f, t / 0.04f) * fminf(1.0f, rem / (0.06f * RATE));
            out = (sinf(v.ph * 6.2832f) + 0.18f * sinf(v.ph * 12.566f)) * 0.22f * env; break;
        }
        case I_BELL: out = (sinf(v.ph * 6.2832f) + 0.35f * sinf(v.ph2 * 6.2832f)) * 0.16f * expf(-t * 3.2f); break;
        case I_PLUCK: out = tri(v.ph) * 0.2f * expf(-t * 9.0f); break;
        case I_BASS: {
            float env = fminf(1.0f, t / 0.01f) * fminf(1.0f, rem / (0.05f * RATE)) * (0.5f + 0.5f * expf(-t * 3.0f));
            out = (tri(v.ph) * 0.7f + sinf(v.ph * 6.2832f) * 0.3f) * 0.32f * env; break;
        }
        case I_PAD: {
            float env = fminf(1.0f, t / 0.15f) * fminf(1.0f, rem / (0.2f * RATE));
            out = (sinf(v.ph * 6.2832f) + 0.6f * tri(v.ph2)) * 0.07f * env; break;
        }
        case I_LEAD: {
            float env = fminf(1.0f, t / 0.01f) * fminf(1.0f, rem / (0.05f * RATE)) * (0.6f + 0.4f * expf(-t * 4.0f));
            out = (v.ph < 0.25f ? 1.0f : -1.0f) * 0.12f * env; break;
        }
        case I_KICK: out = sinf(v.ph * 6.2832f) * 0.5f * expf(-t * 18.0f); break;
        case I_SNARE: { float n = noise(); float h = n - v.prev * 0.8f; v.prev = n; out = h * 0.22f * expf(-t * 30.0f) + tri(v.ph) * 0.12f * expf(-t * 45.0f); break; }
        case I_HAT: { float n = noise(); out = (n - v.prev) * 0.09f * expf(-t * 90.0f); v.prev = n; break; }
        case I_SHAKER: { float n = noise(); out = (n - v.prev) * 0.07f * fminf(1.0f, t / 0.012f) * expf(-t * 45.0f); v.prev = n; break; }
        default: {
            float env = fminf(1.0f, t / 0.004f) * expo(v.age / v.dur);
            float w;
            switch (v.wave) {
                case 0: w = sinf(v.ph * 6.2832f); break;
                case 1: w = v.ph < 0.5f ? 1.0f : -1.0f; break;
                case 2: w = tri(v.ph); break;
                default: w = noise() * 0.7f + sinf(v.ph * 6.2832f) * 0.3f; break;
            }
            out = w * env; break;
        }
    }
    out *= v.vol;
    float inc = v.f / RATE;
    v.ph += inc; if (v.ph >= 1) v.ph -= floorf(v.ph);
    v.ph2 += v.inst == I_BELL ? inc * 2.76f : inc * 1.006f; if (v.ph2 >= 1) v.ph2 -= floorf(v.ph2);
    if (v.ratio) v.f *= v.ratio;
    v.age++;
    if (v.age >= v.dur) v.on = false;
    return out;
}

static void fill(s16* dst, int n) {
    const SongDef* sd = gSong >= 0 && !gTrack ? &SONGS[gSong] : nullptr;
    float stepS = sd ? RATE * 60.0f / (sd->bpm * (gSpooky ? 0.88f : 1.0f)) / 4 : 0;
    float vol = clampf(gSave.vol, 0, 1) * 0.9f;
    for (int i = 0; i < n; i++) {
        if (sd) {
            for (;;) {
                double swing = (gStep % 4 == 2) ? sd->swing / 100.0 * stepS : 0;
                if (gClock < gStepAt + swing) break;
                int s = gStep % sd->steps;
                if (gSpooky && s % 16 == 0) {
                    Voice* tv = freeVoice();
                    if (tv) { *tv = Voice(); tv->on = true; tv->music = true; tv->inst = I_BELL; tv->vol = 0.9f; tv->f = 65.4f; tv->dur = 1.6f * RATE; }
                }
                for (int k = 0; k < sd->n; k++) {
                    if (sd->ev[k].step == s) startNote(sd->ev[k], stepS);
                    else if (sd->ev[k].step > s) break;
                }
                gStepAt += stepS;
                gStep++;
            }
        }
        float m = 0, fx = 0;
        for (Voice& v : gV) if (v.on) { float o = voiceSample(v); if (v.music) m += o; else fx += o; }
        float s = ((gTrack ? trackSample() * 0.7f : m * 0.55f) * gFade + fx) * vol;
        if (s > 0.98f) s = 0.98f; else if (s < -0.98f) s = -0.98f;
        dst[i] = (s16)(s * 32000);
        gClock += 1;
    }
    if (gFade < 1) gFade = fminf(1.0f, gFade + n / (0.6f * RATE));
}

void audioInit() {
    if (R_FAILED(ndspInit())) { gOk = false; return; }
    gBuf = (s16*)linearAlloc(sizeof(s16) * BUFN * BUFS);
    if (!gBuf) { ndspExit(); gOk = false; return; }
    ndspSetOutputMode(NDSP_OUTPUT_MONO);
    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, RATE);
    ndspChnSetFormat(0, NDSP_FORMAT_MONO_PCM16);
    float mix[12] = {1, 1};
    ndspChnSetMix(0, mix);
    memset(gWb, 0, sizeof gWb);
    for (int i = 0; i < BUFS; i++) { gWb[i].data_vaddr = gBuf + i * BUFN; gWb[i].nsamples = BUFN; gWb[i].status = NDSP_WBUF_DONE; }
    gOk = true;
}
void audioExit() {
    trackClose();
    if (!gOk) return;
    ndspChnReset(0);
    ndspExit();
    linearFree(gBuf);
    gOk = false;
}
void audioUpdate() {
    if (!gOk) return;
    for (int i = 0; i < BUFS; i++) {
        if (gWb[i].status != NDSP_WBUF_DONE) continue;
        s16* d = gBuf + i * BUFN;
        fill(d, BUFN);
        DSP_FlushDataCache(d, sizeof(s16) * BUFN);
        gWb[i].nsamples = BUFN;
        ndspChnWaveBufAdd(0, &gWb[i]);
    }
}
void musicPlay(int song) {
    if (!gOk || song == gSong) return;
    bool keepTrack = gTrack && song != MUS_MENU && song >= 0;
    if (!keepTrack) { trackClose(); if (song != MUS_MENU && song >= 0 && gSave.musicChoice > 0 && gSave.musicChoice <= 6) trackOpen(gSave.musicChoice); }
    for (Voice& v : gV) if (v.music) v.on = false;
    gSong = song >= 0 && song < MUS_N ? song : -1;
    gSpooky = hwOn() && gSong >= 0;
    gTonic = 0;
    if (gSpooky) { const SongDef& sd = SONGS[gSong]; for (int k = 0; k < sd.n; k++) if (sd.ev[k].inst == I_BASS) { gTonic = sd.ev[k].midi; break; } }
    gStep = 0;
    gStepAt = gClock + 0.05 * RATE;
    gFade = 0;
}
void musicChoose(int choice) {
    if (choice < 0 || choice > 6) return;
    gSave.musicChoice = choice; saveWrite(); trackClose(); gSong = -1; musicPlay(MUS_BATTLE);
}
void sfxPlay(int id) {
    if (!gOk || id < 0 || id >= SFX_N) return;
    const SfxDef& d = SFX[id];
    double now = gClock / RATE;
    if (now - gSfxLast[id] < d.gap) return;
    gSfxLast[id] = now;
    Voice* v = freeVoice();
    if (!v) return;
    *v = Voice();
    v->on = true; v->inst = I_SFX; v->wave = d.wave; v->f = d.f0;
    v->dur = d.dur * RATE; v->vol = d.vol * 1.3f;
    v->ratio = d.f1 != d.f0 ? powf(d.f1 / d.f0, 1.0f / v->dur) : 0;
}
