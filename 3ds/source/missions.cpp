// Misiones diarias (3 por día) y semanales (2 por semana), como en la versión web.
#include "game.h"
#include <time.h>

struct MDef { u8 n; int goals[3]; bool typed; u8 t1, t10; int coins; const char* one; const char* many; };
// Las plantillas están en el mismo orden que en js/data/missions.js (sin la de "objeto", que aquí no hay objetos).
static const MDef DAILY[9] = {
    {3, {300, 500, 800}, false, 2, 0, 150, nullptr, "Derrota a %d Pokémon"},
    {3, {30, 50, 80}, true, 2, 0, 200, nullptr, "Derrota a %d Pokémon de tipo %s"},
    {3, {5, 7, 9}, false, 3, 0, 200, nullptr, "Aguanta %d minutos en una run"},
    {3, {8, 12, 15}, false, 2, 0, 200, nullptr, "Llega al nivel %d en una run"},
    {2, {1, 2}, false, 3, 0, 250, "Derrota a un jefe", "Derrota a %d jefes"},
    {2, {1, 2}, false, 2, 0, 200, "Abre un cofre con candado", "Abre %d cofres con candado"},
    {3, {100, 200, 300}, false, 2, 0, 150, nullptr, "Recoge %d monedas en tus runs"},
    {1, {3}, true, 3, 0, 200, nullptr, "Aguanta %d minutos con un Pokémon de tipo %s"},
    {1, {1}, false, 3, 0, 250, "Evoluciona un movimiento", "Evoluciona %d movimientos"},
};
static const MDef WEEKLY[6] = {
    {2, {4000, 6000}, false, 0, 1, 800, nullptr, "Derrota a %d Pokémon"},
    {2, {1, 2}, false, 0, 1, 1000, "Gana una pelea en una grieta", "Gana %d peleas en grietas"},
    {2, {4, 6}, false, 0, 1, 900, nullptr, "Derrota a %d jefes"},
    {2, {12, 15}, false, 0, 1, 1000, nullptr, "Aguanta %d minutos en una run"},
    {2, {3, 5}, false, 0, 1, 900, nullptr, "Evoluciona %d movimientos"},
    {2, {8, 12}, false, 0, 1, 800, nullptr, "Completa %d misiones diarias"},
};

static const MDef& defOf(const MSlot& m, bool weekly) { return weekly ? WEEKLY[m.def] : DAILY[m.def]; }
int missionGoal(const MSlot& m, bool weekly) { return defOf(m, weekly).goals[m.tier]; }
bool missionDone(const MSlot& m, bool weekly) { return m.prog >= missionGoal(m, weekly); }
void missionReward(const MSlot& m, bool weekly, int* t1, int* t10, int* coins) {
    const MDef& d = defOf(m, weekly);
    *t1 = d.t1; *t10 = d.t10; *coins = d.coins;
}
void missionText(const MSlot& m, bool weekly, char* out, int n) {
    const MDef& d = defOf(m, weekly);
    int g = missionGoal(m, weekly);
    if (g == 1 && d.one) snprintf(out, n, "%s", T(d.one));
    else if (d.typed) snprintf(out, n, d.many, g, typeName(m.param));
    else snprintf(out, n, d.many, g);
}

static u32 gSeed;
static u32 lcg() { gSeed = gSeed * 1664525u + 1013904223u; return gSeed >> 8; }
static void roll(MSlot* out, int count, int total, const MDef* defs, u32 seed) {
    gSeed = seed * 2654435761u + 12345u;
    u8 order[9];
    for (int i = 0; i < total; i++) order[i] = (u8)i;
    for (int i = total - 1; i > 0; i--) { int j = lcg() % (i + 1); u8 t = order[i]; order[i] = order[j]; order[j] = t; }
    for (int i = 0; i < count; i++) {
        MSlot& m = out[i];
        memset(&m, 0, sizeof m);
        m.def = order[i];
        m.tier = (u8)(lcg() % defs[m.def].n);
        m.param = (u8)(lcg() % 18);
    }
}

void missionsRefresh() {
    int day = (int)(time(nullptr) / 86400);
    int week = (day + 3) / 7;                   // las semanas empiezan en lunes
    bool dirty = false;
    if (day != gSave.dayKey) { roll(gSave.md, 3, 9, DAILY, (u32)day); gSave.dayKey = day; dirty = true; }
    if (week != gSave.weekKey) { roll(gSave.mw, 2, 6, WEEKLY, (u32)week + 777u); gSave.weekKey = week; dirty = true; }
    if (dirty) saveWrite();
}

static void addProg(MSlot& m, bool weekly, int v, bool isMax) {
    if (m.claimed || v <= 0) return;
    int g = missionGoal(m, weekly);
    if (m.prog >= g) return;
    m.prog = isMax ? (v > m.prog ? v : m.prog) : m.prog + v;
    if (m.prog > g) m.prog = g;
}

void missionsReport(const MissionRun& r) {
    missionsRefresh();
    int doneBefore = 0;
    for (int i = 0; i < 3; i++) doneBefore += missionDone(gSave.md[i], false);
    for (int i = 0; i < 3; i++) {
        MSlot& m = gSave.md[i];
        switch (m.def) {
            case 0: addProg(m, false, r.kills, false); break;
            case 1: addProg(m, false, r.killsByType[m.param], false); break;
            case 2: addProg(m, false, (int)r.minutes, true); break;
            case 3: addProg(m, false, r.level, true); break;
            case 4: addProg(m, false, r.bosses, false); break;
            case 5: addProg(m, false, r.chests, false); break;
            case 6: addProg(m, false, r.coins, false); break;
            case 7: if (r.ct1 == m.param || r.ct2 == m.param) addProg(m, false, (int)r.minutes, true); break;
            case 8: addProg(m, false, r.evolves, false); break;
        }
    }
    int doneNow = 0;
    for (int i = 0; i < 3; i++) doneNow += missionDone(gSave.md[i], false);
    for (int i = 0; i < 2; i++) {
        MSlot& m = gSave.mw[i];
        switch (m.def) {
            case 0: addProg(m, true, r.kills, false); break;
            case 1: addProg(m, true, r.rifts, false); break;
            case 2: addProg(m, true, r.bosses, false); break;
            case 3: addProg(m, true, (int)r.minutes, true); break;
            case 4: addProg(m, true, r.evolves, false); break;
            case 5: addProg(m, true, doneNow - doneBefore, false); break;
        }
    }
    saveWrite();
}

bool missionClaim(MSlot& m, bool weekly) {
    if (m.claimed || !missionDone(m, weekly)) return false;
    int t1, t10, coins;
    missionReward(m, weekly, &t1, &t10, &coins);
    gSave.t1 += t1; gSave.t10 += t10; gSave.coins += coins;
    m.claimed = 1;
    gSave.stat[SB_MIS]++;
    achCheck();
    saveWrite();
    return true;
}
