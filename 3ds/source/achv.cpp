// PokéSurvivor 3DS — logros (medallas 1/2/3). Los premios se cobran solos al cumplirse.
#include "game.h"

enum { A_OWN, A_SHINY, A_PULLS, A_TIME, A_LEVEL, A_KILLS, A_BOSS, A_EVO, A_RIFT, A_LEG, A_MIS, A_RUNS, A_LEGONE };
enum { C_COL, C_SURV, C_COMBAT, C_RIFT, C_LEG, C_OTHER };
struct AchDef { const char* name; const char* desc; int tier, cat, src, goal, t1, t10, coins; };

static const AchDef BASE[] = {
    {"Coleccionista", "Consigue %d Pokémon.", 1, C_COL, A_OWN, 20, 0, 0, 300},
    {"Gran coleccionista", "Consigue %d Pokémon.", 2, C_COL, A_OWN, 100, 0, 1, 0},
    {"Maestro coleccionista", "Consigue %d Pokémon.", 3, C_COL, A_OWN, 300, 0, 3, 0},
    {"Brillo", "Consigue %d Pokémon variocolor.", 1, C_COL, A_SHINY, 1, 1, 0, 0},
    {"Cazador de brillos", "Consigue %d Pokémon variocolor.", 2, C_COL, A_SHINY, 10, 0, 1, 0},
    {"Tirador", "Haz %d tiradas de gacha.", 1, C_COL, A_PULLS, 10, 0, 0, 200},
    {"Apostador", "Haz %d tiradas de gacha.", 2, C_COL, A_PULLS, 100, 0, 1, 0},
    {"Adicto al gacha", "Haz %d tiradas de gacha.", 3, C_COL, A_PULLS, 500, 0, 2, 0},
    {"Superviviente", "Aguanta %d minutos en una partida.", 1, C_SURV, A_TIME, 5, 0, 0, 200},
    {"Resistente", "Aguanta %d minutos en una partida.", 2, C_SURV, A_TIME, 10, 1, 0, 0},
    {"Imparable", "Aguanta %d minutos en una partida.", 3, C_SURV, A_TIME, 15, 0, 1, 0},
    {"Entrenador", "Llega al nivel %d.", 1, C_SURV, A_LEVEL, 15, 0, 0, 200},
    {"Veterano", "Llega al nivel %d.", 2, C_SURV, A_LEVEL, 30, 1, 0, 0},
    {"Leyenda viva", "Llega al nivel %d.", 3, C_SURV, A_LEVEL, 50, 0, 1, 0},
    {"Luchador", "Derrota a %d Pokémon.", 1, C_COMBAT, A_KILLS, 500, 0, 0, 200},
    {"Guerrero", "Derrota a %d Pokémon.", 2, C_COMBAT, A_KILLS, 5000, 0, 1, 0},
    {"Exterminador", "Derrota a %d Pokémon.", 3, C_COMBAT, A_KILLS, 50000, 0, 3, 0},
    {"Cazajefes", "Derrota a %d jefes.", 1, C_COMBAT, A_BOSS, 5, 1, 0, 0},
    {"Azote de jefes", "Derrota a %d jefes.", 2, C_COMBAT, A_BOSS, 50, 0, 1, 0},
    {"Evolucionista", "Evoluciona %d veces.", 1, C_COMBAT, A_EVO, 5, 0, 0, 250},
    {"Maestro evolutivo", "Evoluciona %d veces.", 2, C_COMBAT, A_EVO, 50, 0, 1, 0},
    {"Explorador de grietas", "Supera %d grietas.", 1, C_RIFT, A_RIFT, 1, 0, 0, 300},
    {"Rompegrietas", "Supera %d grietas.", 2, C_RIFT, A_RIFT, 10, 0, 1, 0},
    {"Señor de las grietas", "Supera %d grietas.", 3, C_RIFT, A_RIFT, 50, 0, 3, 0},
    {"Primer legendario", "Derrota a %d legendarios distintos.", 1, C_LEG, A_LEG, 1, 1, 0, 0},
    {"Cazalegendarios", "Derrota a %d legendarios distintos.", 2, C_LEG, A_LEG, 10, 0, 1, 0},
    {"Todos los legendarios", "Derrota a todos los legendarios.", 3, C_LEG, A_LEG, -1, 0, 5, 0},
    {"Aplicado", "Cobra %d misiones.", 1, C_OTHER, A_MIS, 5, 0, 0, 250},
    {"Mercenario", "Cobra %d misiones.", 2, C_OTHER, A_MIS, 50, 0, 1, 0},
    {"Constante", "Juega %d partidas.", 1, C_OTHER, A_RUNS, 10, 0, 0, 200},
    {"Incansable", "Juega %d partidas.", 2, C_OTHER, A_RUNS, 100, 0, 1, 0},
};
static const int NBASE = sizeof BASE / sizeof BASE[0];
static const char* CATS[6] = {"Colección", "Supervivencia", "Combate", "Grietas", "Legendarios", "Otros"};

int achLast = -1;
static int gLegIdx[256], gNLeg;
static bool gInit;

static void init() {
    if (gInit) return;
    gInit = true;
    for (int i = 0; i < DEX_N && NBASE + gNLeg < 256; i++)
        if (DEX[i].leg && sprHas(DEX_NUM[i])) gLegIdx[gNLeg++] = i;
}
int achCount() { init(); return NBASE + gNLeg; }
int achCats() { return 6; }
const char* achCatName(int c) { return CATS[c]; }
static int catOf(int i) { return i < NBASE ? BASE[i].cat : C_LEG; }
int achInCat(int c, int* out, int max) {
    init();
    int n = 0, tot = achCount();
    for (int i = 0; i < tot && n < max; i++) if (catOf(i) == c) out[n++] = i;
    return n;
}
static long srcVal(int src, int di) {
    long v = 0;
    switch (src) {
        case A_OWN: for (int i = 0; i < DEX_N; i++) v += gSave.owned[i]; break;
        case A_SHINY: for (int i = 0; i < DEX_N; i++) v += gSave.shiny[i] ? 1 : 0; break;
        case A_PULLS: v = gSave.stat[SB_PULLS]; break;
        case A_TIME: v = gSave.best / 60; break;
        case A_LEVEL: v = gSave.bestLevel; break;
        case A_KILLS: v = gSave.kills; break;
        case A_BOSS: v = gSave.stat[SB_BOSS]; break;
        case A_EVO: v = gSave.stat[SB_EVO]; break;
        case A_RIFT: v = gSave.stat[SB_RIFT]; break;
        case A_LEG: for (int i = 0; i < DEX_N; i++) v += gSave.legends[i] ? 1 : 0; break;
        case A_MIS: v = gSave.stat[SB_MIS]; break;
        case A_RUNS: v = gSave.runs; break;
        case A_LEGONE: v = gSave.legends[di] ? 1 : 0; break;
    }
    return v;
}
static void def(int i, int* tier, int* src, long* goal, int* di) {
    *di = 0;
    if (i < NBASE) {
        *tier = BASE[i].tier; *src = BASE[i].src;
        *goal = BASE[i].goal < 0 ? gNLeg : BASE[i].goal;
        if (BASE[i].src == A_OWN && BASE[i].tier == 3) *goal = DEX_N < 300 ? DEX_N : 300;
    } else { *tier = 2; *src = A_LEGONE; *goal = 1; *di = gLegIdx[i - NBASE]; }
}
void achInfo(int i, char* name, char* desc, int n, int* tier, long* val, long* goal, bool* done) {
    init();
    int t, s, di; long g;
    def(i, &t, &s, &g, &di);
    if (i < NBASE) {
        snprintf(name, n, "%s", T(BASE[i].name));
        char f[64]; snprintf(f, sizeof f, "%s", BASE[i].desc);
        snprintf(desc, n, f, (int)g);
    } else {
        snprintf(name, n, "Vence a %s", pname(di));
        snprintf(desc, n, "Derrota a %s en una grieta.", pname(di));
    }
    long v = srcVal(s, di);
    *tier = t; *goal = g; *val = v > g ? g : v; *done = gSave.ach[i] != 0;
}
void achReward(int i, int* t1, int* t10, int* coins) {
    if (i < NBASE) { *t1 = BASE[i].t1; *t10 = BASE[i].t10; *coins = BASE[i].coins; }
    else { *t1 = 0; *t10 = 0; *coins = 500; }
}
int achDoneCount() {
    int n = 0, tot = achCount();
    for (int i = 0; i < tot; i++) n += gSave.ach[i] ? 1 : 0;
    return n;
}
int achCheck() {
    init();
    int tot = achCount(), fresh = 0;
    for (int i = 0; i < tot; i++) {
        if (gSave.ach[i]) continue;
        int t, s, di; long g;
        def(i, &t, &s, &g, &di);
        if (g <= 0 || srcVal(s, di) < g) continue;
        gSave.ach[i] = 1;
        int t1, t10, c; achReward(i, &t1, &t10, &c);
        gSave.t1 += t1; gSave.t10 += t10; gSave.coins += c;
        achLast = i; fresh++;
    }
    return fresh;
}
