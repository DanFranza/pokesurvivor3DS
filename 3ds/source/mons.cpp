// Naturaleza, habilidad y MT de cada Pokémon + Tienda Kecleon (reglas de la web: js/systems/mons.js y js/data/shop.js).
#include "game.h"
#include <time.h>

int langNameIdx() {
    static const u8 col[LANG_N] = {0, 1, 2, 3, 1, 4, 5};   // pt-BR usa los nombres en inglés, como la web
    return col[gSave.lang < LANG_N ? gSave.lang : 0];
}
const char* natureName(int n) { return NATURES[n].n[langNameIdx()]; }
const char* abilName(int a) { return a < 0 ? "-" : ABIL[a].n[langNameIdx()]; }

MonStat monStats(int di, int nat) {
    const DexE& p = DEX[di];
    float v[5] = {p.pa, p.sa, (float)p.df, (float)p.sd, (float)p.spd};
    const NatureE& n = NATURES[nat];
    if (n.up >= 0) v[n.up] *= 1.1f;
    if (n.down >= 0) v[n.down] *= 0.9f;
    MonStat m;
    m.pa = v[NS_PA]; m.sa = v[NS_SA]; m.df = v[NS_DF]; m.sd = v[NS_SD]; m.spd = v[NS_SPD];
    m.atk = fmaxf(m.pa, m.sa);
    return m;
}

// ---------------------------------------------------------------- sorteo (determinista por cuenta)
static float roll(int di, int salt) {
    u32 h = 2166136261u;
    auto feed = [&](u32 v) { for (int i = 0; i < 4; i++) { h ^= (v >> (i * 8)) & 255; h *= 16777619u; } };
    feed(gSave.seed); feed((u32)di); feed((u32)salt);
    h ^= h >> 16; h *= 0x85ebca6bu; h ^= h >> 13; h *= 0xc2b2ae35u; h ^= h >> 16;
    return h / 4294967296.0f;
}
int monNature(int di) {
    if (gSave.pnat[di] && gSave.pnat[di] <= NNAT) return gSave.pnat[di] - 1;
    int n = (int)(roll(di, 1) * NNAT);
    return n >= NNAT ? NNAT - 1 : n;
}
int monAbilSlot(int di) {
    const unsigned short* l = DEX_ABIL[di];
    int s = gSave.pabil[di] ? gSave.pabil[di] - 1 : -1;
    if (s < 0 || s > 2 || !l[s]) {
        s = 0;
        if (l[2] && roll(di, 2) < 0.05f) s = 2;
        else if (l[1] && roll(di, 3) < 0.5f) s = 1;
    }
    return l[s] ? s : 0;
}
int monAbil(int di) { return (int)DEX_ABIL[di][monAbilSlot(di)] - 1; }
int monAbilChoices(int di, int* slots, bool hidden) {
    const unsigned short* l = DEX_ABIL[di];
    int cur = monAbilSlot(di), n = 0;
    for (int s = 0; s < 3; s++) {
        if (s == cur || !l[s] || (s == 2 && !hidden)) continue;
        if (l[s] == l[cur] || (s > 0 && l[s] == l[0])) continue;
        slots[n++] = s;
    }
    return n;
}
void abilDesc(int a, int di, char* out, int n) {
    if (a < 0) { out[0] = 0; return; }
    const AbilE& e = ABIL[a];
    const char* g = T(GENERIC_DESC[DEX[di].t1]);
    if (!e.desc[0]) { strncpy(out, g, n - 1); out[n - 1] = 0; return; }
    strncpy(out, T(e.desc), n - 1); out[n - 1] = 0;
    if (e.plus) { size_t l = strlen(out); if (l + 2 < (size_t)n) { out[l] = ' '; strncpy(out + l + 1, g, n - l - 2); out[n - 1] = 0; } }
}

// ---------------------------------------------------------------- MT
static bool moveNatural(int di, int m) {
    const DexE& p = DEX[di];
    if (m == p.start) return true;
    int ts[3] = {0, p.t1, p.t2};
    for (int k = 0; k < 3; k++) {
        if (ts[k] == 255) continue;
        const PoolRef& r = POOL_BY_TYPE[ts[k]];
        for (int i = 0; i < r.n; i++) if (POOL_ALL[r.off + i] == m) return true;
    }
    return false;
}
bool monCanLearn(int di, int tm) {
    if (TM_MOVE[tm] < 0 || !(TM_MASK[di] >> tm & 1) || (gSave.ptm[di] >> tm & 1)) return false;
    return !moveNatural(di, TM_MOVE[tm]);
}
u64 monLearnable(int di) {
    u64 r = 0;
    for (int i = 0; i < NTM; i++) if (monCanLearn(di, i)) r |= 1ull << i;
    return r;
}
bool monTeach(int di, int tm) {
    if (!gSave.tms[tm] || !monCanLearn(di, tm)) return false;
    gSave.tms[tm]--; gSave.ptm[di] |= 1ull << tm;
    saveWrite();
    return true;
}
int monTaughtMoves(int di, int* out) {
    int n = 0;
    for (int i = 0; i < NTM; i++) if ((gSave.ptm[di] >> i & 1) && TM_MOVE[i] >= 0) out[n++] = TM_MOVE[i];
    return n;
}

// ---------------------------------------------------------------- tienda: las 8 MT del día (mismo sorteo que la web)
int shopDate() {
    time_t t = time(nullptr);
    struct tm* l = localtime(&t);
    return (l->tm_year + 1900) * 10000 + (l->tm_mon + 1) * 100 + l->tm_mday;
}
namespace {
struct Mul {
    u32 h;
    explicit Mul(const char* seed) { h = 2166136261u; for (const char* c = seed; *c; c++) { h ^= (u8)*c; h *= 16777619u; } }
    double next() {
        h += 0x6D2B79F5u;
        u32 t = h;
        t = (t ^ (t >> 15)) * (t | 1);
        t ^= t + (t ^ (t >> 7)) * (t | 61);
        return (t ^ (t >> 14)) / 4294967296.0;
    }
};
}
int tmDaily(int* out) {
    char seed[40];
    int all[NTM];
    for (int i = 0; i < NTM; i++) all[i] = i;
    snprintf(seed, sizeof seed, "kecleon:%d", shopDate());
    Mul r(seed);
    for (int i = NTM - 1; i > 0; i--) { int j = (int)floor(r.next() * (i + 1)); int t = all[i]; all[i] = all[j]; all[j] = t; }
    const int N = 8;
    for (int i = 0; i < N; i++) out[i] = all[i];
    int d = gSave.lastChar;
    if (d >= 0 && d < DEX_N && gSave.owned[d]) {
        bool any = false;
        for (int i = 0; i < N; i++) any |= monCanLearn(d, out[i]);
        u64 mine = monLearnable(d);
        if (!any && mine) {
            int l[NTM], n = 0;
            for (int i = 0; i < NTM; i++) if (mine >> i & 1) l[n++] = i;
            char s2[48];
            snprintf(s2, sizeof s2, "kecleon:%d:%d", shopDate(), (int)DEX_NUM[d]);
            Mul r2(s2);
            out[N - 1] = l[(int)floor(r2.next() * n)];
        }
    }
    return N;
}

const int BAG_PRICE[3] = {1500, 1500, 5000};
const char* const BAG_NAME[3] = {"Menta", "Cápsula Habilidad", "Cápsula Habilidad Oculta"};
const char* const BAG_DESC[3] = {"Cambia la naturaleza de un Pokémon por la que tú elijas.",
                                 "Cambia la habilidad de un Pokémon por otra de las suyas (no la oculta).",
                                 "Cambia la habilidad de un Pokémon por cualquiera de las suyas, también la oculta."};
bool shopBuyItem(int id) {
    if (id < 0 || id > 2 || gSave.coins < BAG_PRICE[id]) return false;
    gSave.coins -= BAG_PRICE[id];
    if (gSave.bag[id] < 999) gSave.bag[id]++;
    saveWrite();
    return true;
}
bool shopBuyTm(int tm) {
    if (tm < 0 || tm >= NTM || gSave.coins < TM_PRICE[tm]) return false;
    gSave.coins -= TM_PRICE[tm];
    if (gSave.tms[tm] < 999) gSave.tms[tm]++;
    saveWrite();
    return true;
}
