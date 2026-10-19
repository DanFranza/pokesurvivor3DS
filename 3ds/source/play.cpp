// Simulación y dibujo de la partida: mundo, enemigos, movimientos, efectos.
#include "game.h"

// ---------------------------------------------------------------- límites (todo estático)
#define MAXE   84
#define CAPE   64
#define MAXS   110
#define MAXES  70
#define MAXP   170
#define MAXF   44
#define MAXH   26
#define MAXFX  120
#define TS     32
#define PI_F   3.14159265f

// ---------------------------------------------------------------- tipos de datos
struct Enemy {
    bool on, boss, moving;
    short di;                       // fila en DEX
    u8 beh, dir, st;
    float x, y, hp, maxHp, spd, dmg, xp, r, flash, t, t2, tx, ty, kx, ky, shield, hitCd;
    float shotDmg, shotCd, range;
    short minion; u8 fanN, zones;
    float burn, burnT, burnTick, poison, poiT, poiTick, slow, slowT, stun;
    float orbCd[4];
    int id;
};
struct Shot {
    bool on, boom, back;
    float x, y, vx, vy, life, dmg, r, burn, poison, slow, knock, homing, boomT, bsp, px, py;
    u8 type, pierce, bounce, cat, nh; short mid;
    int hits[8];
};
struct EShot { bool on; float x, y, vx, vy, life, dmg, r; u32 col; };
struct Haz { bool on, line, fired; float x, y, ang, len, w, r, t, delay, dmg, post; u32 col; };
struct Pick { bool on; u8 kind; float x, y, val, t; };       // 0 xp 1 moneda 2 curar 3 ticket 4 imán
struct Field {
    bool on; u8 kind, type; short mid;
    float x, y, t, life, r, dmg, ca, sa, next, a;
    int n, i;
    float v[NK_];
};
enum { FD_MINE, FD_METEOR, FD_TURRET, FD_PATCH, FD_CHARGE, FD_SPIN, FD_QUAKE, FD_VORTEX, FD_STUN };
enum { FX_RING, FX_ARC, FX_BEAM, FX_PART, FX_TEXT, FX_FLASH, FX_BOLT };
struct Fx {
    bool on; u8 kind, rimmed;
    float x, y, x2, y2, r0, r1, a, arc, t, life, w, vx, vy;
    u32 rgb; char txt[28];
};
struct Player {
    float x, y, hp, maxHp, spd, invuln, flash, aim, vx, vy, dashT;
    int dir; bool moving;
    float atkMul, spdMul, cdMul, dmgReduce, regen, magnet, xpMul, coinMul, crit;
    int level; float xp, xpNeed;
    int di;
    float buffAtk, buffAtkT, buffSpd, buffSpdT, buffDef, buffDefT;
    float slowT, liqT;
    int rerolls;
    float orbA[4];
};

enum { BEH_COUNT = 13 };
struct Def {
    short di; u8 beh, fanN, zones; short minion;
    float hp, spd, dmg, xp, shotDmg, shotCd, range;
};
struct TierT { float from; int bstLo, bstHi; float hp, spd, dmg, xp; int cast; };
static const TierT TIERS[6] = {
    {0, 180, 330, 17, 56, 6, 3.5f, 7},   {70, 300, 405, 32, 62, 8.5f, 5, 7}, {160, 385, 465, 52, 60, 11, 8, 7},
    {260, 445, 515, 88, 70, 14, 13, 7},  {380, 495, 560, 150, 66, 22, 24, 7}, {500, 530, 620, 250, 72, 28, 38, 7}};
struct BossSlot { float at, hp, dmg, xp; int bstLo, bstHi; };
static const BossSlot BOSS_SLOTS[5] = {
    {180, 1400, 34, 220, 490, 545}, {360, 3200, 42, 420, 520, 580}, {540, 5600, 48, 680, 540, 600},
    {720, 9000, 56, 1000, 580, 700}, {900, 16000, 68, 1800, 600, 700}};

// ---------------------------------------------------------------- estado global
static Enemy gE[MAXE];
static Shot gS[MAXS];
static EShot gES[MAXES];
static Haz gH[MAXH];
static Pick gP[MAXP];
static Field gF[MAXF];
static Fx gFx[MAXFX];
static Player P;
MoveInst gMoves[4];
bool gAuto = true;

static PlayState gPS = PS_RUN;
static float gTime, gSpawnAcc, gSurgeT, gShake, gBannerT, gPreT;
static char gBanner[48];
static int gKills, gBossesDown, gCoins, gT1, gT10, gNextId, gChar, gSet, gNextBoss, gRerollsLeft;
static float gCamX, gCamY;
static Def gCast[6][8]; static int gNCast[6];
static Def gBossDef[5];
static int gTarget;
static float gTargetD;
static u32 gManualDown;
static u8 gBroken[512][2]; static int gNBroken;
static bool gLiqGrid[14][18];
static float gAimX = 1, gAimY = 0;
static int gTierNow;
static u64 gMs;

// ---------------------------------------------------------------- utilidades
static float distf(float ax, float ay, float bx, float by) { return sqrtf((ax - bx) * (ax - bx) + (ay - by) * (ay - by)); }
static u32 rgbA(u32 rgb, int a) { return COL((rgb >> 16) & 255, (rgb >> 8) & 255, rgb & 255, a); }
static u32 lighten(u32 rgb, float k) {
    int r = (rgb >> 16) & 255, g = (rgb >> 8) & 255, b = rgb & 255;
    r += (int)((255 - r) * k); g += (int)((255 - g) * k); b += (int)((255 - b) * k);
    return ((u32)r << 16) | ((u32)g << 8) | (u32)b;
}
static u32 darken(u32 rgb, float k) {
    int r = (rgb >> 16) & 255, g = (rgb >> 8) & 255, b = rgb & 255;
    return ((u32)(r * k) << 16) | ((u32)(g * k) << 8) | (u32)(b * k);
}
static float guardMul(float def) { return clampf(powf(75.0f / (def < 5 ? 5 : def), 0.35f), 0.78f, 1.25f); }

float typeMult(int a, int t1, int t2) {
    float m = TYPE_CHART[a][t1];
    if (t2 != 255) m *= TYPE_CHART[a][t2];
    return clampf(m, 0.3f, 2.4f);
}
const char* effLabel(float m) {
    if (m >= 1.55f) return "¡Eficaz!";
    if (m <= 0.4f) return "Inmune";
    if (m <= 0.8f) return "Poco";
    return "";
}

void moveRecompute(MoveInst& m) {
    const MoveDef& d = MOVES[m.id];
    memcpy(m.v, d.v, sizeof m.v);
    for (int l = 0; l < m.lvl - 1 && l < 4; l++) {
        const MoveUp& u = d.ups[l];
        for (int i = 0; i < u.n; i++) {
            int k = u.m[i].key;
            float v = u.m[i].v;
            if (u.m[i].op == 1) m.v[k] += v;
            else if (u.m[i].op == 0 && m.v[k] != 0) m.v[k] *= v;
            else m.v[k] = v;
        }
    }
}

// ---------------------------------------------------------------- efectos
static Fx* newFx(u8 kind, float life) {
    static int cur;
    for (int k = 0; k < MAXFX; k++) {
        int i = (cur + k) % MAXFX;
        if (!gFx[i].on) { cur = i + 1; Fx& f = gFx[i]; memset(&f, 0, sizeof f); f.on = true; f.kind = kind; f.life = life; return &f; }
    }
    return nullptr;
}
static void fxRing(float x, float y, float r0, float r1, u32 rgb, float life, float w) {
    Fx* f = newFx(FX_RING, life); if (!f) return; f->x = x; f->y = y; f->r0 = r0; f->r1 = r1; f->rgb = rgb; f->w = w;
}
static void fxArc(float x, float y, float r, float aim, float arc, u32 rgb, float life) {
    Fx* f = newFx(FX_ARC, life); if (!f) return; f->x = x; f->y = y; f->r1 = r; f->a = aim; f->arc = arc; f->rgb = rgb;
}
static void fxBeam(float x, float y, float x2, float y2, float w, u32 rgb, float life) {
    Fx* f = newFx(FX_BEAM, life); if (!f) return; f->x = x; f->y = y; f->x2 = x2; f->y2 = y2; f->w = w; f->rgb = rgb;
}
static void fxFlash(float x, float y, float r, u32 rgb, float life) {
    Fx* f = newFx(FX_FLASH, life); if (!f) return; f->x = x; f->y = y; f->r1 = r; f->rgb = rgb;
}
static void fxBurst(float x, float y, u32 rgb, int n, float spd) {
    for (int i = 0; i < n; i++) {
        Fx* f = newFx(FX_PART, frange(0.25f, 0.5f)); if (!f) return;
        float a = frand() * 6.283f, s = frange(0.4f, 1.0f) * spd;
        f->x = x; f->y = y; f->vx = cosf(a) * s; f->vy = sinf(a) * s; f->rgb = rgb; f->w = frange(2.5f, 4.5f);
    }
}
static void fxText(float x, float y, const char* s, u32 rgb, float scale) {
    Fx* f = newFx(FX_TEXT, 0.8f); if (!f) return;
    f->x = x; f->y = y; f->rgb = rgb; f->w = scale; f->vy = -38;
    snprintf(f->txt, sizeof f->txt, "%s", T(s));
}
static void fxBolt(float x, float y, float x2, float y2, u32 rgb) {
    Fx* f = newFx(FX_BOLT, 0.22f); if (!f) return; f->x = x; f->y = y; f->x2 = x2; f->y2 = y2; f->rgb = rgb;
}
static void banner(const char* s, float t = 2.8f) { snprintf(gBanner, sizeof gBanner, "%s", T(s)); gBannerT = t; }

// ---------------------------------------------------------------- mundo procedural
static u32 wseed() { return (u32)gSet * 7919u + 13u; }
static float vnoise(float x, float y, u32 seed) {
    int xi = (int)floorf(x), yi = (int)floorf(y);
    float fx = x - xi, fy = y - yi;
    fx = fx * fx * (3 - 2 * fx); fy = fy * fy * (3 - 2 * fy);
    float a = (hash2(xi, yi, seed) & 0xFFFF) / 65535.0f, b = (hash2(xi + 1, yi, seed) & 0xFFFF) / 65535.0f;
    float c = (hash2(xi, yi + 1, seed) & 0xFFFF) / 65535.0f, d = (hash2(xi + 1, yi + 1, seed) & 0xFFFF) / 65535.0f;
    return a + (b - a) * fx + (c - a) * fy + (a - b - c + d) * fx * fy;
}
static bool liquidTile(int tx, int ty) {
    float pools = TILESET_POOLS[gSet];
    if (pools <= 0) return false;
    if (tx * tx + ty * ty < 36) return false;
    return vnoise(tx / 4.5f, ty / 4.5f, wseed() + 3) > 0.78f - pools * 0.85f;
}
enum { PR_NONE, PR_TREE, PR_ROCK, PR_CHEST, PR_BIG };
static bool isBroken(int tx, int ty) {
    for (int i = 0; i < gNBroken; i++) if (gBroken[i][0] == (u8)(tx & 255) && gBroken[i][1] == (u8)(ty & 255)) return true;
    return false;
}
static int propAt(int tx, int ty, int* var) {
    if (tx * tx + ty * ty < 30) return PR_NONE;
    u32 h = hash2(tx, ty, wseed() + 1);
    float r = (h & 0xFFFF) / 65536.0f;
    int kind = PR_NONE;
    float a = TILESET_TREES[gSet], b = a + TILESET_PILLARS[gSet];
    if (r < a) kind = PR_TREE;
    else if (r < b) kind = PR_ROCK;
    else if (r < b + 0.0016f) kind = PR_CHEST;
    else if (r < b + 0.0021f) kind = PR_BIG;
    if (kind == PR_NONE) return kind;
    if (liquidTile(tx, ty)) return PR_NONE;
    if (kind >= PR_ROCK && isBroken(tx, ty)) return PR_NONE;
    if (var) *var = (h >> 16) % (kind == PR_TREE ? 3 : 2);
    return kind;
}
static float propR(int k) { return k == PR_TREE ? 8.0f : k == PR_ROCK ? 11.0f : 9.0f; }
static void propPos(int tx, int ty, float* x, float* y) { *x = tx * TS + 16; *y = ty * TS + 27; }
static void pushOut(float& x, float& y, float r) {
    int tx0 = (int)floorf(x / TS), ty0 = (int)floorf(y / TS);
    for (int ty = ty0 - 1; ty <= ty0 + 1; ty++)
        for (int tx = tx0 - 1; tx <= tx0 + 1; tx++) {
            int k = propAt(tx, ty, nullptr);
            if (k == PR_NONE) continue;
            float px, py; propPos(tx, ty, &px, &py);
            float dx = x - px, dy = y - py, d = sqrtf(dx * dx + dy * dy), m = r + propR(k);
            if (d < m) {
                if (d < 0.01f) { dx = 1; dy = 0; d = 1; }
                x = px + dx / d * m; y = py + dy / d * m;
            }
        }
}
static int liquidKind() { return TILESET_LIQUID[gSet]; }

// ---------------------------------------------------------------- jugador y estadísticas
static const DexE& pdex() { return DEX[P.di]; }
static float atkBase(const MoveDef& d) {
    const DexE& p = pdex();
    float a = P.atkMul * (P.buffAtkT > 0 ? 1 + P.buffAtk : 1) * p.atk;
    float fit = d.cat == 0 ? p.pa / p.atk : d.cat == 1 ? p.sa / p.atk : 1;
    if (d.cat != 2 && p.t2 == 255 && d.type == p.t1) fit *= 1.2f;
    return a * fit;
}
static float xpFor(int lv) { return floorf((8 + lv * 6 + powf((float)lv, 1.75f) * 1.6f) * 4); }

static void healPlayer(float v) { P.hp = fminf(P.maxHp, P.hp + v); }

static void slotPlace(int mid) {
    static const int order[4] = {3, 2, 1, 0};
    for (int k = 0; k < 4; k++) {
        int b = order[k];
        if (gMoves[b].id < 0) { gMoves[b].id = mid; gMoves[b].lvl = 1; gMoves[b].cd = 0.3f; gMoves[b].dealt = 0; moveRecompute(gMoves[b]); return; }
    }
}
static bool ownsMove(int mid) { for (int b = 0; b < 4; b++) if (gMoves[b].id == mid) return true; return false; }
static int nMoves() { int n = 0; for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0) n++; return n; }

void playSwapSlots(int a, int b) { MoveInst t = gMoves[a]; gMoves[a] = gMoves[b]; gMoves[b] = t; }

// ---------------------------------------------------------------- enemigos: tablas de reparto
static float baseHp(const DexE& p) { return (p.hp - 70) / 0.45f; }
static float baseSpd(const DexE& p) { return (p.spd - 78) / 0.42f; }
static bool isPlain(int b) { return b == B_CHASE || b == B_CHARGER || b == B_RANGED || b == B_TANK; }
static bool isSupport(int b) { return b == B_HEALER || b == B_SHIELDER || b == B_SUMMONER; }

static Def defFor(int di, int ti) {
    const DexE& p = DEX[di]; const TierT& tier = TIERS[ti];
    Def d; memset(&d, 0, sizeof d);
    d.di = di; d.beh = p.beh;
    float hpK = clampf(baseHp(p) / 65, 0.7f, 1.6f), spdK = clampf(0.75f + baseSpd(p) / 260, 0.75f, 1.3f);
    bool tank = d.beh == B_TANK;
    d.hp = tier.hp * hpK * (tank ? 1.5f : 1); d.spd = tier.spd * spdK * (tank ? 0.7f : 1);
    d.dmg = tier.dmg * (tank ? 1.2f : 1); d.xp = fmaxf(3, tier.xp * (tank ? 1.3f : 1));
    float cd = 0;
    switch (d.beh) {
        case B_RANGED: cd = 2.2f - ti * 0.15f; break;
        case B_FAN: cd = 3.2f - ti * 0.15f; break;
        case B_BEAMER: cd = 4.4f - ti * 0.2f; break;
        case B_ZONER: cd = 4.6f - ti * 0.2f; break;
        case B_HEALER: cd = 3.5f; break;
        case B_SUMMONER: cd = 7; break;
    }
    if (cd > 0) {
        d.shotDmg = tier.dmg * (d.beh == B_FAN ? 0.7f : 0.8f); d.shotCd = cd;
        d.range = (d.beh == B_BEAMER ? 260 : (d.beh == B_HEALER || d.beh == B_SUMMONER) ? 230 : 190) + ti * 6;
    }
    d.minion = p.minion; d.fanN = ti < 2 ? 3 : 5; d.zones = ti < 2 ? 1 : ti < 4 ? 2 : 3;
    if (d.beh == B_BOMBER) { d.spd *= 1.25f; d.hp *= 0.8f; }
    return d;
}
static bool candidate(int i, int ti) {
    const DexE& p = DEX[i];
    return p.rarity < 5 && !p.leg && p.bst >= TIERS[ti].bstLo && p.bst <= TIERS[ti].bstHi && sprHas(DEX_NUM[i]);
}
static void rollRun() {
    static short all[DEX_N], pick[16];
    for (int ti = 0; ti < 6; ti++) {
        int n = 0;
        for (int i = 0; i < DEX_N; i++) if (candidate(i, ti)) all[n++] = i;
        int cnt = 0;
        auto take = [&](bool (*pred)(int), int want) {
            for (int tries = 0; tries < 60 && want > 0 && cnt < TIERS[ti].cast; tries++) {
                if (!n) return;
                int di = all[rnd() % n];
                if (!pred(DEX[di].beh)) continue;
                bool dup = false; for (int k = 0; k < cnt; k++) if (pick[k] == di) dup = true;
                if (dup) continue;
                pick[cnt++] = di; want--;
            }
        };
        // un tipo de apoyo a partes iguales
        int kinds[3], nk = 0;
        for (int b : {B_HEALER, B_SHIELDER, B_SUMMONER}) { for (int k = 0; k < n; k++) if (DEX[all[k]].beh == b) { kinds[nk++] = b; break; } }
        if (nk) {
            int sk = kinds[rnd() % nk];
            for (int tries = 0; tries < 80; tries++) { int di = all[rnd() % n]; if (DEX[di].beh == sk) { pick[cnt++] = di; break; } }
        }
        if (ti > 0) take([](int b) { return !isPlain(b) && !isSupport(b); }, 1);
        if (ti == 0) take(isPlain, TIERS[ti].cast); else take([](int) { return true; }, TIERS[ti].cast);
        gNCast[ti] = cnt;
        for (int k = 0; k < cnt; k++) gCast[ti][k] = defFor(pick[k], ti);
        // el más rápido de los sencillos pasa a corredor
        int best = -1;
        for (int k = 0; k < cnt; k++) { u8 b = gCast[ti][k].beh; if ((b == B_CHASE || b == B_CHARGER || b == B_TANK) && (best < 0 || gCast[ti][k].spd > gCast[ti][best].spd)) best = k; }
        if (best >= 0) { Def& d = gCast[ti][best]; d.beh = B_RUNNER; d.spd *= 1.6f; d.hp *= 0.7f; }
    }
    bool used[DEX_N]; memset(used, 0, sizeof used);
    for (int s = 0; s < 5; s++) {
        int n = 0;
        for (int i = 0; i < DEX_N; i++)
            if (!DEX[i].leg && sprHas(DEX_NUM[i]) && !used[i] && DEX[i].bst >= BOSS_SLOTS[s].bstLo && DEX[i].bst <= BOSS_SLOTS[s].bstHi) all[n++] = i;
        if (!n) for (int i = 0; i < DEX_N; i++) if (!DEX[i].leg && sprHas(DEX_NUM[i]) && !used[i] && DEX[i].bst >= 580) all[n++] = i;
        int di = all[rnd() % n]; used[di] = true;
        Def& d = gBossDef[s]; memset(&d, 0, sizeof d);
        d.di = di; d.hp = BOSS_SLOTS[s].hp * 1.35f; d.spd = clampf(40 + baseSpd(DEX[di]) * 0.5f, 40, 100);
        d.dmg = BOSS_SLOTS[s].dmg * 1.2f; d.xp = BOSS_SLOTS[s].xp;
        d.beh = DEX[di].beh == B_RANGED ? B_RANGED : (baseSpd(DEX[di]) > 90 ? B_CHARGER : B_CHASE);
        d.shotDmg = BOSS_SLOTS[s].dmg * 0.55f; d.shotCd = 1.1f; d.range = 260;
    }
}
void playPreloadSprites() {
    sprLoad(DEX_NUM[P.di]);
    for (int ti = 0; ti < 6; ti++) for (int k = 0; k < gNCast[ti]; k++) { sprLoad(DEX_NUM[gCast[ti][k].di]); if (gCast[ti][k].minion) sprLoad(gCast[ti][k].minion); }
    for (int s = 0; s < 5; s++) sprLoad(DEX_NUM[gBossDef[s].di]);
}

// ---------------------------------------------------------------- recogidas
static void dropPick(u8 kind, float x, float y, float val) {
    for (int i = 0; i < MAXP; i++)
        if (!gP[i].on) { gP[i] = {true, kind, x, y, val, 0}; return; }
    if (kind == 0) { P.xp += val * P.xpMul; }
    else if (kind == 1) gCoins += (int)val;
}

// ---------------------------------------------------------------- enemigos
static int spawnEnemy(const Def& d, float x, float y, bool boss, bool elite, float t) {
    int slot = -1;
    for (int i = 0; i < MAXE; i++) if (!gE[i].on) { slot = i; break; }
    if (slot < 0) return -1;
    Enemy& e = gE[slot]; memset(&e, 0, sizeof e);
    e.on = true; e.boss = boss; e.di = d.di; e.beh = d.beh; e.x = x; e.y = y; e.id = ++gNextId;
    float hpK, dmgK, spdK;
    if (boss) { hpK = 1 + t / 600; dmgK = 1 + t / 600; spdK = 1; }
    else { hpK = (1 + t / 95) * (3.3f + fminf(1.7f, t / 210)); dmgK = (1 + t / 420) * 2.4f; spdK = 1 + fminf(0.35f, t / 1400); }
    e.maxHp = e.hp = d.hp * hpK; e.spd = d.spd * spdK; e.dmg = d.dmg * dmgK; e.xp = boss ? d.xp : roundf(d.xp * 5.6f);
    e.shotDmg = d.shotDmg * dmgK * (boss ? 1 : 2.4f); e.shotCd = d.shotCd; e.range = d.range; e.minion = d.minion; e.fanN = d.fanN; e.zones = d.zones;
    if (elite) { e.maxHp = e.hp = e.hp * 1.6f; e.dmg *= 1.25f; e.xp = roundf(e.xp * 1.6f); }
    const PokeSpr& s = POKE_SPR[DEX_NUM[d.di]];
    float sz = fminf((float)s.w, (float)s.h);
    e.r = clampf(sz * 0.34f, 8, 16) * (boss ? 1.9f : 1);
    e.t = frange(0, 2); e.t2 = frange(0, 1);
    return slot;
}

static void killEnemy(Enemy& e) {
    if (!e.on) return;
    e.on = false;
    gKills++;
    fxBurst(e.x, e.y - 8, 0xffffff, e.boss ? 18 : 6, e.boss ? 150 : 90);
    if (e.boss) fxRing(e.x, e.y - 8, 6, 90, 0xffe070, 0.5f, 5);
    sfxPlay(e.boss ? SFX_BOSS : SFX_KILL);
    dropPick(0, e.x, e.y, e.xp);
    float r = frand();
    if (e.boss) {
        gBossesDown++;
        for (int i = 0; i < 12; i++) dropPick(1, e.x + frange(-24, 24), e.y + frange(-18, 18), 3);
        dropPick(3, e.x, e.y - 10, 1);
        dropPick(2, e.x + 14, e.y, 1);
        gShake = 0.5f;
    } else {
        if (r < 0.10f) dropPick(1, e.x + frange(-6, 6), e.y + frange(-4, 4), 1);
        else if (r < 0.115f) dropPick(2, e.x, e.y, 1);
        else if (r < 0.12f) dropPick(4, e.x, e.y, 1);
    }
}

static void damageEnemyRaw(Enemy& e, float dmg) {
    if (e.shield > 0) { float a = fminf(e.shield, dmg); e.shield -= a; dmg -= a; }
    e.hp -= dmg;
    e.flash = 0.12f;
    if (e.hp <= 0) killEnemy(e);
}

static void hitEnemy(Enemy& e, float dmg, int type, int cat, float burn, float poison, float slow, float knock, float dx, float dy, int mid) {
    const DexE& p = DEX[e.di];
    float tm = typeMult(type, p.t1, p.t2);
    float g = cat == 2 ? 1 : guardMul(cat == 1 ? p.sd : p.df);
    bool crit = frand() < P.crit;
    float d = dmg * tm * g * (crit ? 1.5f : 1);
    for (int b = 0; b < 4; b++) if (gMoves[b].id == mid) gMoves[b].dealt += d;
    knock *= e.boss ? 0.25f : 1;
    float L = sqrtf(dx * dx + dy * dy);
    if (L > 0.01f && knock > 0) { e.kx += dx / L * knock; e.ky += dy / L * knock; }
    if (burn > 0) { e.burn = fminf(8, e.burn + burn); e.burnT = 3; }
    if (poison > 0) { e.poison = fminf(8, e.poison + poison); e.poiT = 4; }
    if (slow > 0) { e.slow = fmaxf(e.slow, clampf(slow, 0, 0.85f)); e.slowT = 1.2f; }
    int num = (int)(d + 0.5f);
    char b[12]; snprintf(b, sizeof b, "%d", num);
    const char* lab = effLabel(tm);
    u32 col = crit ? 0xffee55 : tm >= 1.55f ? 0xff8a3d : tm <= 0.8f ? 0xa0a8b8 : 0xffffff;
    if (e.boss || tm >= 1.55f || tm <= 0.8f || crit || frand() < 0.5f) {
        fxText(e.x, e.y - 22, lab[0] ? lab : b, col, lab[0] ? 0.42f : crit ? 0.6f : 0.46f);
        if (lab[0] && frand() < 0.7f) fxText(e.x, e.y - 34, b, col, 0.5f);
    }
    fxBurst(e.x, e.y - 8, typeColor(type) & 0xFFFFFF ? (u32)(TYPE_RGB[type]) : 0xffffff, 2, 70);
    damageEnemyRaw(e, d);
}

// ---------------------------------------------------------------- disparos del jugador
static Shot* newShot() {
    for (int i = 0; i < MAXS; i++) if (!gS[i].on) { memset(&gS[i], 0, sizeof gS[i]); gS[i].on = true; return &gS[i]; }
    return nullptr;
}
static void fillShot(Shot* s, const MoveInst& m, float x, float y, float a, float sp, float dmg, float life) {
    const MoveDef& d = MOVES[m.id];
    s->x = x; s->y = y; s->px = x; s->py = y; s->vx = cosf(a) * sp; s->vy = sinf(a) * sp; s->life = life; s->dmg = dmg; s->r = m.v[K_SIZE] > 0 ? m.v[K_SIZE] : 6;
    s->pierce = (u8)m.v[K_PIERCE]; s->bounce = (u8)m.v[K_BOUNCE]; s->homing = m.v[K_HOMING]; s->mid = m.id;
    s->burn = m.v[K_BURN]; s->poison = m.v[K_POISON]; s->slow = m.v[K_SLOW]; s->knock = m.v[K_KNOCK];
    s->type = d.type; s->cat = d.cat;
}
static float reachOf(const MoveInst& m) {
    const MoveDef& d = MOVES[m.id]; const float* v = m.v;
    switch (d.kind) {
        case MK_MELEE: return v[K_RADIUS] + 30;
        case MK_BEAM: return v[K_RADIUS] + 20;
        case MK_BOOMERANG: return v[K_RADIUS] + 40;
        case MK_CHAIN: return 280;
        case MK_METEOR: return 340;
        case MK_DASH: return v[K_RADIUS] + 60;
        case MK_CONE: return v[K_SPEED] * v[K_LIFE] + 30;
        case MK_SPIN: case MK_SHOVE: case MK_CHARGE: return v[K_RADIUS] + 20;
        case MK_QUAKE: return (int)v[K_COUNT] * 34 + v[K_RADIUS];
        case MK_VORTEX: case MK_STUN: return 300;
        default: return 360;
    }
}
static bool needsTarget(int kind) {
    switch (kind) {
        case MK_AURA: case MK_NOVA: case MK_BUFF: case MK_MINE: case MK_TURRET: case MK_TRAIL: case MK_ORBIT: return false;
        default: return true;
    }
}
static Field* newField(int kind, const MoveInst& m, float x, float y) {
    for (int i = 0; i < MAXF; i++) if (!gF[i].on) {
        Field& f = gF[i]; memset(&f, 0, sizeof f);
        f.on = true; f.kind = kind; f.mid = m.id; f.type = MOVES[m.id].type; f.x = x; f.y = y; memcpy(f.v, m.v, sizeof f.v);
        return &f;
    }
    return nullptr;
}
static float segDist2(float ax, float ay, float bx, float by, float cx, float cy) {
    float dx = bx - ax, dy = by - ay, l2 = dx * dx + dy * dy;
    float t = l2 > 0 ? clampf(((cx - ax) * dx + (cy - ay) * dy) / l2, 0, 1) : 0;
    float px = ax + dx * t - cx, py = ay + dy * t - cy;
    return px * px + py * py;
}
static void hitMove(Enemy& e, float dmg, int type, int cat, const float* v, float dx, float dy, int mid, float knockOverride = -1) {
    hitEnemy(e, dmg, type, cat, v[K_BURN], v[K_POISON], v[K_SLOW], knockOverride >= 0 ? knockOverride : v[K_KNOCK], dx, dy, mid);
}

static int nearestEnemy(float x, float y, float maxD, const int* skipIds = nullptr, int nSkip = 0) {
    int best = -1; float bd = maxD * maxD;
    for (int i = 0; i < MAXE; i++) {
        if (!gE[i].on) continue;
        bool skip = false; for (int k = 0; k < nSkip; k++) if (skipIds[k] == gE[i].id) skip = true;
        if (skip) continue;
        float dx = gE[i].x - x, dy = gE[i].y - y, d = dx * dx + dy * dy;
        if (d < bd) { bd = d; best = i; }
    }
    return best;
}
static void shake(float s) { if (s > gShake) gShake = s; }

static void blastAt(const Field& f, float r, float k) {
    for (int i = 0; i < MAXE; i++) {
        Enemy& e = gE[i];
        if (!e.on) continue;
        if (distf(e.x, e.y, f.x, f.y) <= r + e.r) hitMove(e, f.dmg * k, f.type, MOVES[f.mid].cat, f.v, e.x - f.x, e.y - f.y, f.mid);
    }
}
static void breakProps(float x, float y, float r, float dmg);

static bool castMove(int b) {
    MoveInst& m = gMoves[b];
    const MoveDef& d = MOVES[m.id]; const float* v = m.v;
    float dmg = v[K_DMG] * atkBase(d);
    float ca = cosf(P.aim), sa = sinf(P.aim);
    u32 rgb = TYPE_RGB[d.type];
    float cx = P.x, cy = P.y - 8;
    switch (d.kind) {
        case MK_PROJECTILE: case MK_HOMING: case MK_BOUNCE: {
            int n = (int)fmaxf(1, v[K_COUNT]); float spread = v[K_SPREAD];
            for (int i = 0; i < n; i++) {
                float off = n == 1 ? 0 : ((float)i / (n - 1) - 0.5f) * spread * n;
                Shot* s = newShot(); if (!s) break;
                float a = P.aim + off + frange(-0.03f, 0.03f);
                fillShot(s, m, cx + cosf(a) * 4, cy + sinf(a) * 4, a, v[K_SPEED], dmg, v[K_LIFE]);
            }
            fxFlash(cx + ca * 10, cy + sa * 10, 9, rgb, 0.12f);
            sfxPlay(SFX_SHOOT);
            break;
        }
        case MK_NOVA: {
            int n = (int)fmaxf(3, v[K_COUNT]);
            for (int i = 0; i < n; i++) {
                Shot* s = newShot(); if (!s) break;
                float a = (float)i / n * 6.283f + frange(-0.06f, 0.06f);
                fillShot(s, m, cx, cy, a, v[K_SPEED], dmg, v[K_LIFE]);
            }
            fxRing(cx, cy, 8, 46, rgb, 0.3f, 4);
            sfxPlay(SFX_BOOM);
            break;
        }
        case MK_CONE: {
            int n = (int)fmaxf(2, v[K_COUNT]); float arc = v[K_ARC] > 0 ? v[K_ARC] : 0.9f;
            for (int i = 0; i < n; i++) {
                Shot* s = newShot(); if (!s) break;
                float a = P.aim + ((float)i / (n - 1) - 0.5f) * arc + frange(-0.05f, 0.05f);
                fillShot(s, m, cx + cosf(a) * 5, cy + sinf(a) * 5, a, v[K_SPEED] * frange(0.85f, 1.1f), dmg, v[K_LIFE] * frange(0.85f, 1.05f));
            }
            fxFlash(cx + ca * 12, cy + sa * 12, 12, rgb, 0.14f);
            sfxPlay(SFX_SHOOT);
            break;
        }
        case MK_MELEE: {
            float half = fminf(v[K_ARC], 6.283f) / 2;
            fxArc(cx, cy, v[K_RADIUS], P.aim, half * 2, rgb, 0.22f);
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on) continue;
                float dx = e.x - P.x, dy = e.y - P.y, dist = sqrtf(dx * dx + dy * dy);
                if (dist > v[K_RADIUS] + e.r) continue;
                float da = atan2f(dy, dx) - P.aim;
                while (da > PI_F) da -= 6.283f; while (da < -PI_F) da += 6.283f;
                if (dist > 12 && fabsf(da) > half + e.r / (dist + 1)) continue;
                hitMove(e, dmg, d.type, d.cat, v, dx, dy, m.id);
            }
            breakProps(P.x + ca * v[K_RADIUS] * 0.5f, P.y + sa * v[K_RADIUS] * 0.5f, v[K_RADIUS] * 0.6f, dmg);
            sfxPlay(SFX_HIT);
            break;
        }
        case MK_BEAM: {
            float len = v[K_RADIUS], w = v[K_WIDTH] > 0 ? v[K_WIDTH] : 20;
            fxBeam(cx, cy, cx + ca * len, cy + sa * len, w, rgb, 0.3f);
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on) continue;
                float px = e.x - P.x, py = e.y - P.y, along = px * ca + py * sa;
                if (along < -e.r || along > len + e.r) continue;
                if (fabsf(-px * sa + py * ca) <= w / 2 + e.r) hitMove(e, dmg, d.type, d.cat, v, ca, sa, m.id);
            }
            breakProps(P.x + ca * len / 2, P.y + sa * len / 2, len / 2, dmg * 0.3f);
            shake(0.12f); sfxPlay(SFX_BEAM);
            break;
        }
        case MK_AURA: {
            fxRing(P.x, P.y, v[K_RADIUS] * 0.5f, v[K_RADIUS], rgb, 0.3f, 3);
            fxFlash(P.x, P.y, v[K_RADIUS], rgb, 0.18f);
            float heal = 0;
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on) continue;
                if (distf(e.x, e.y, P.x, P.y) <= v[K_RADIUS] + e.r) { hitMove(e, dmg, d.type, d.cat, v, e.x - P.x, e.y - P.y, m.id); heal += 0; }
            }
            break;
        }
        case MK_BUFF: {
            int st = d.stat;
            float amt = v[K_AMOUNT], dur = v[K_DUR];
            if (st == ST_ATK || st == ST_PATK || st == ST_SATK) { P.buffAtk = amt; P.buffAtkT = dur; }
            else if (st == ST_SPD) { P.buffSpd = amt; P.buffSpdT = dur; }
            else if (st == ST_DEF) { P.buffDef = amt; P.buffDefT = dur; }
            else if (st == ST_REGEN) healPlayer(P.maxHp * 0.25f);
            fxRing(P.x, P.y, 28, 6, rgb, 0.4f, 3);
            fxText(P.x, P.y - 30, MOVES[m.id].name, rgb, 0.45f);
            sfxPlay(SFX_PICK);
            break;
        }
        case MK_BOOMERANG: {
            int n = (int)fmaxf(1, v[K_COUNT]); float spread = v[K_SPREAD] > 0 ? v[K_SPREAD] : 0.5f;
            float out = v[K_RADIUS] / v[K_SPEED];
            for (int i = 0; i < n; i++) {
                Shot* s = newShot(); if (!s) break;
                float a = P.aim + (n == 1 ? 0 : ((float)i / (n - 1) - 0.5f) * spread * fminf((float)n, 3));
                fillShot(s, m, cx, cy, a, v[K_SPEED], dmg, out * 4 + 1.5f);
                s->pierce = 250; s->boom = true; s->boomT = out; s->bsp = v[K_SPEED] * 1.1f; s->r = fmaxf(s->r, 8);
            }
            sfxPlay(SFX_SHOOT);
            break;
        }
        case MK_CHAIN: {
            int cur = gTarget >= 0 && gE[gTarget].on && distf(P.x, P.y, gE[gTarget].x, gE[gTarget].y) <= 280 ? gTarget : nearestEnemy(P.x, P.y, 280);
            if (cur < 0) return false;
            float fx = cx, fy = cy, k = 1;
            int done[12]; int nd = 0;
            int n = (int)fminf(12, fmaxf(1, v[K_COUNT]));
            for (int i = 0; i < n && cur >= 0; i++) {
                Enemy& e = gE[cur]; done[nd++] = e.id;
                float tx = e.x, ty = e.y - 8;
                fxBolt(fx, fy, tx, ty, rgb);
                hitMove(e, dmg * k, d.type, d.cat, v, tx - fx, ty - fy, m.id);
                k *= 0.85f; fx = tx; fy = ty;
                cur = nearestEnemy(tx, e.y, v[K_RADIUS] > 0 ? v[K_RADIUS] : 120, done, nd);
            }
            shake(0.05f); sfxPlay(SFX_BEAM);
            break;
        }
        case MK_MINE: {
            int n = (int)fmaxf(1, v[K_COUNT]);
            for (int i = 0; i < n; i++) {
                float a = frand() * 6.283f, dist = n == 1 ? 0 : frange(18, 46);
                Field* f = newField(FD_MINE, m, P.x + cosf(a) * dist, P.y + sinf(a) * dist * 0.8f); if (!f) break;
                f->life = v[K_DUR] > 0 ? v[K_DUR] : 7; f->r = v[K_RADIUS]; f->dmg = dmg; f->next = 0.35f;
            }
            int cnt = 0, lim = 4 + n * 2;
            for (int i = 0; i < MAXF; i++) if (gF[i].on && gF[i].kind == FD_MINE && gF[i].mid == m.id) cnt++;
            for (int i = 0; i < MAXF && cnt > lim; i++) if (gF[i].on && gF[i].kind == FD_MINE && gF[i].mid == m.id) { gF[i].on = false; cnt--; }
            break;
        }
        case MK_METEOR: {
            int n = (int)fmaxf(1, v[K_COUNT]);
            for (int i = 0; i < n; i++) {
                int ei = nearestEnemy(P.x + frange(-60, 60), P.y + frange(-60, 60), 340);
                float x = ei >= 0 ? gE[ei].x + frange(-8, 8) : P.x + frange(-140, 140);
                float y = ei >= 0 ? gE[ei].y + frange(-6, 6) : P.y + frange(-100, 100);
                Field* f = newField(FD_METEOR, m, x, y); if (!f) break;
                f->t = -i * 0.09f; f->life = 0.5f; f->r = v[K_RADIUS]; f->dmg = dmg;
            }
            sfxPlay(SFX_SHOOT);
            break;
        }
        case MK_TURRET: {
            float a = P.aim + PI_F + frange(-0.6f, 0.6f);
            Field* f = newField(FD_TURRET, m, P.x + cosf(a) * 26, P.y + sinf(a) * 20); if (!f) break;
            f->life = v[K_DUR] > 0 ? v[K_DUR] : 6; f->next = 0.3f; f->dmg = dmg;
            int cnt = 0, lim = (int)fmaxf(1, v[K_COUNT]);
            for (int i = 0; i < MAXF; i++) if (gF[i].on && gF[i].kind == FD_TURRET && gF[i].mid == m.id) cnt++;
            for (int i = 0; i < MAXF && cnt > lim; i++) if (gF[i].on && gF[i].kind == FD_TURRET && gF[i].mid == m.id && &gF[i] != f) { gF[i].on = false; cnt--; }
            fxRing(P.x, P.y, 4, 30, rgb, 0.3f, 2);
            break;
        }
        case MK_DASH: {
            float sx = P.x, sy = P.y, len = 0;
            for (float dd = 8; dd <= v[K_RADIUS]; dd += 8) {
                float tx = sx + ca * dd, ty = sy + sa * dd;
                float px = tx, py = ty; pushOut(px, py, 7);
                if (fabsf(px - tx) > 0.5f || fabsf(py - ty) > 0.5f) break;
                len = dd;
            }
            P.x = sx + ca * len; P.y = sy + sa * len; P.invuln = fmaxf(P.invuln, 0.3f);
            fxBeam(sx, sy - 8, P.x, P.y - 8, 18, rgb, 0.3f);
            fxArc(P.x, P.y - 8, 34, P.aim, 2.2f, rgb, 0.2f);
            float w = v[K_WIDTH] > 0 ? v[K_WIDTH] : 34;
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on) continue;
                float lim = w / 2 + e.r;
                if (segDist2(sx, sy, P.x, P.y, e.x, e.y) <= lim * lim) hitMove(e, dmg, d.type, d.cat, v, ca, sa, m.id);
            }
            shake(0.12f); sfxPlay(SFX_HIT);
            break;
        }
        case MK_TRAIL: {
            for (int i = 0; i < MAXF; i++)
                if (gF[i].on && gF[i].kind == FD_PATCH && gF[i].mid == m.id && gF[i].t < 1 && distf(gF[i].x, gF[i].y, P.x, P.y) < v[K_RADIUS] * 0.9f) return true;
            Field* f = newField(FD_PATCH, m, P.x, P.y); if (!f) break;
            f->life = v[K_DUR] > 0 ? v[K_DUR] : 3; f->r = v[K_RADIUS]; f->dmg = dmg; f->next = 0;
            int cnt = 0;
            for (int i = 0; i < MAXF; i++) if (gF[i].on && gF[i].kind == FD_PATCH) cnt++;
            for (int i = 0; i < MAXF && cnt > 20; i++) if (gF[i].on && gF[i].kind == FD_PATCH && &gF[i] != f) { gF[i].on = false; cnt--; }
            break;
        }
        case MK_CHARGE: {
            Field* f = newField(FD_CHARGE, m, P.x, P.y); if (!f) break;
            f->life = v[K_CHARGE] > 0 ? v[K_CHARGE] : 0.75f; f->dmg = dmg; f->ca = ca; f->sa = sa;
            fxRing(P.x, P.y - 8, 60, 10, rgb, f->life, 3);
            break;
        }
        case MK_SPIN: {
            Field* f = newField(FD_SPIN, m, P.x, P.y); if (!f) break;
            f->n = (int)fmaxf(1, v[K_COUNT]); f->a = P.aim; f->dmg = dmg; f->r = v[K_RADIUS];
            break;
        }
        case MK_QUAKE: {
            Field* f = newField(FD_QUAKE, m, P.x, P.y); if (!f) break;
            f->ca = ca; f->sa = sa; f->n = (int)fmaxf(1, v[K_COUNT]); f->dmg = dmg; f->r = v[K_RADIUS];
            shake(0.1f); sfxPlay(SFX_BOOM);
            break;
        }
        case MK_VORTEX: {
            int ei = gTarget >= 0 ? gTarget : -1;
            float x = ei >= 0 ? gE[ei].x : P.x + ca * 120, y = ei >= 0 ? gE[ei].y : P.y + sa * 100;
            Field* f = newField(FD_VORTEX, m, x, y); if (!f) break;
            f->life = v[K_DUR] > 0 ? v[K_DUR] : 2.6f; f->r = v[K_RADIUS]; f->dmg = dmg; f->next = 0.15f; f->a = v[K_PULL] > 0 ? v[K_PULL] : 140;
            fxRing(x, y, v[K_RADIUS], 6, rgb, 0.4f, 3);
            int cnt = 0;
            for (int i = 0; i < MAXF; i++) if (gF[i].on && gF[i].kind == FD_VORTEX && gF[i].mid == m.id) cnt++;
            for (int i = 0; i < MAXF && cnt > 2; i++) if (gF[i].on && gF[i].kind == FD_VORTEX && gF[i].mid == m.id && &gF[i] != f) { gF[i].on = false; cnt--; }
            break;
        }
        case MK_SHOVE: {
            fxRing(P.x, P.y, 10, v[K_RADIUS], rgb, 0.35f, 5);
            fxBurst(P.x, P.y - 8, rgb, 8, 140);
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on) continue;
                if (distf(e.x, e.y, P.x, P.y) <= v[K_RADIUS] + e.r) hitMove(e, dmg, d.type, d.cat, v, e.x - P.x, e.y - P.y, m.id, v[K_KNOCK] > 0 ? v[K_KNOCK] : 300);
            }
            breakProps(P.x, P.y, v[K_RADIUS], dmg);
            shake(0.1f); sfxPlay(SFX_BOOM);
            break;
        }
        case MK_STUN: {
            int ei = gTarget;
            if (ei < 0) return false;
            Field* f = newField(FD_STUN, m, gE[ei].x, gE[ei].y); if (!f) break;
            f->life = 0.45f; f->r = v[K_RADIUS]; f->dmg = dmg;
            break;
        }
        default: break;
    }
    return true;
}

static void breakProp(int tx, int ty, int kind) {
    if (gNBroken < 512) { gBroken[gNBroken][0] = (u8)(tx & 255); gBroken[gNBroken][1] = (u8)(ty & 255); gNBroken++; }
    float x, y; propPos(tx, ty, &x, &y);
    fxBurst(x, y - 8, kind == PR_ROCK ? 0x9a9488 : 0xf2c443, kind == PR_BIG ? 30 : 12, 130);
    if (kind == PR_ROCK) {
        float r = frand();
        if (r < 0.4f) dropPick(0, x, y, 6);
        if (r > 0.75f) dropPick(1, x + 6, y, 2);
        if (r > 0.94f) dropPick(2, x - 6, y, 1);
    } else if (kind == PR_CHEST) {
        int n = 4 + rnd() % 4;
        for (int i = 0; i < n; i++) dropPick(1, x + frange(-14, 14), y + frange(-10, 10), 3);
        dropPick(frand() < 0.5f ? 2 : 4, x, y, 1);
        dropPick(0, x, y, 20);
        fxRing(x, y - 8, 6, 46, 0xf2c443, 0.45f, 4);
    } else if (kind == PR_BIG) {
        for (int i = 0; i < 9; i++) dropPick(1, x + frange(-22, 22), y + frange(-14, 14), 4);
        int tk = 1 + rnd() % 3;
        for (int i = 0; i < tk; i++) dropPick(3, x + frange(-16, 16), y + frange(-10, 10), 1);
        if (frand() < 0.15f) dropPick(3, x, y - 10, 10);
        dropPick(0, x, y, xpFor(P.level));
        fxRing(x, y - 8, 6, 80, 0xf2c443, 0.6f, 5);
        shake(0.3f);
    }
    sfxPlay(SFX_BOOM);
}
static void breakProps(float x, float y, float r, float dmg) {
    (void)dmg;
    int tx0 = (int)floorf((x - r) / TS), tx1 = (int)floorf((x + r) / TS), ty0 = (int)floorf((y - r) / TS), ty1 = (int)floorf((y + r) / TS);
    for (int ty = ty0; ty <= ty1; ty++)
        for (int tx = tx0; tx <= tx1; tx++) {
            int k = propAt(tx, ty, nullptr);
            if (k < PR_ROCK) continue;
            float px, py; propPos(tx, ty, &px, &py);
            if (distf(x, y, px, py) <= r + propR(k)) breakProp(tx, ty, k);
        }
}

// ---------------------------------------------------------------- hazards y disparos enemigos
static Haz* newHaz() { for (int i = 0; i < MAXH; i++) if (!gH[i].on) { memset(&gH[i], 0, sizeof gH[i]); gH[i].on = true; return &gH[i]; } return nullptr; }
static void hazCircle(float x, float y, float r, float delay, float dmg, u32 col) {
    Haz* h = newHaz(); if (!h) return; h->x = x; h->y = y; h->r = r; h->delay = delay; h->dmg = dmg; h->col = col; h->post = 0.2f;
}
static void hazLine(float x, float y, float ang, float len, float w, float delay, float dmg, u32 col) {
    Haz* h = newHaz(); if (!h) return; h->line = true; h->x = x; h->y = y; h->ang = ang; h->len = len; h->w = w; h->delay = delay; h->dmg = dmg; h->col = col; h->post = 0.3f;
}
static void eshot(float x, float y, float a, float sp, float dmg, u32 col, float r = 5) {
    for (int i = 0; i < MAXES; i++) if (!gES[i].on) { gES[i] = {true, x, y, cosf(a) * sp, sinf(a) * sp, 3.0f, dmg, r, col}; return; }
}

static void hurtPlayer(float dmg, int cat, int srcDi) {
    if (P.invuln > 0 || P.hp <= 0) return;
    float g = srcDi >= 0 ? guardMul(cat == 1 ? pdex().sd : pdex().df) : 1;
    float red = clampf(P.dmgReduce + (P.buffDefT > 0 ? P.buffDef : 0), 0, 0.8f);
    float d = dmg * g * (1 - red);
    P.hp -= d; P.invuln = 0.55f; P.flash = 0.2f;
    char b[12]; snprintf(b, sizeof b, "-%d", (int)(d + 0.5f));
    fxText(P.x, P.y - 28, b, 0xff6060, 0.55f);
    shake(0.2f);
    sfxPlay(SFX_HURT);
    if (P.hp <= 0) { P.hp = 0; gPS = PS_OVER; sfxPlay(SFX_OVER); }
}
static int enemyCat(const Enemy& e) { return DEX[e.di].sa > DEX[e.di].pa ? 1 : 0; }

static void updateHazards(float dt) {
    for (int i = 0; i < MAXH; i++) {
        Haz& h = gH[i]; if (!h.on) continue;
        h.t += dt;
        if (!h.fired && h.t >= h.delay) {
            h.fired = true;
            if (h.line) {
                float ca = cosf(h.ang), sa = sinf(h.ang);
                float px = P.x - h.x, py = P.y - 8 - h.y, along = px * ca + py * sa;
                if (along > 0 && along < h.len && fabsf(-px * sa + py * ca) < h.w / 2 + 6) hurtPlayer(h.dmg, 1, 0);
                fxBeam(h.x, h.y, h.x + ca * h.len, h.y + sa * h.len, h.w, h.col, 0.3f);
            } else {
                if (distf(P.x, P.y, h.x, h.y) < h.r + 6) hurtPlayer(h.dmg, enemyCat(gE[0]), 0);
                fxRing(h.x, h.y, 4, h.r, h.col, 0.3f, 4);
                fxFlash(h.x, h.y, h.r, h.col, 0.2f);
                fxBurst(h.x, h.y - 4, h.col, 6, 100);
            }
            sfxPlay(SFX_BOOM);
        }
        if (h.t >= h.delay + h.post) h.on = false;
    }
    for (int i = 0; i < MAXES; i++) {
        EShot& s = gES[i]; if (!s.on) continue;
        s.x += s.vx * dt; s.y += s.vy * dt; s.life -= dt;
        if (s.life <= 0) { s.on = false; continue; }
        if (distf(s.x, s.y, P.x, P.y - 8) < s.r + 7) { hurtPlayer(s.dmg, 1, 0); s.on = false; fxBurst(s.x, s.y, s.col, 4, 60); }
    }
}

// ---------------------------------------------------------------- IA de enemigos
static void moveEnemy(Enemy& e, float dirx, float diry, float spd, float dt) {
    float k = spd * (1 - e.slow) * dt;
    e.x += dirx * k; e.y += diry * k;
}
static void spawnMinions(Enemy& e) {
    if (!e.minion || !sprHas(e.minion)) return;
    int di = dexIndexOf(e.minion); if (di < 0) return;
    int ti = gTierNow;
    Def d = defFor(di, ti); d.beh = B_CHASE; d.hp *= 0.6f;
    for (int k = 0; k < 2; k++) {
        int s = spawnEnemy(d, e.x + frange(-20, 20), e.y + frange(-14, 14), false, false, gTime);
        if (s >= 0) gE[s].xp *= 0.3f;
    }
    fxRing(e.x, e.y - 8, 6, 36, 0xd8d060, 0.4f, 3);
}

static void enemyAI(Enemy& e, float dt) {
    float dx = P.x - e.x, dy = P.y - e.y, dist = sqrtf(dx * dx + dy * dy);
    float ux = dist > 0.01f ? dx / dist : 0, uy = dist > 0.01f ? dy / dist : 0;
    float spd = e.spd;
    e.t += dt;
    if (e.stun > 0) { e.moving = false; return; }
    bool mv = true;
    switch (e.beh) {
        case B_CHASE: case B_TANK: moveEnemy(e, ux, uy, spd, dt); break;
        case B_RUNNER: {
            float tx = P.x + P.vx * 0.7f - e.x, ty = P.y + P.vy * 0.7f - e.y, l = sqrtf(tx * tx + ty * ty);
            if (l > 0.01f) moveEnemy(e, tx / l, ty / l, spd, dt);
            break;
        }
        case B_CHARGER: {
            if (e.st == 0) { moveEnemy(e, ux, uy, spd, dt); if (dist < 170 && dist > 60 && e.t > 2.2f) { e.st = 1; e.t = 0; e.tx = ux; e.ty = uy; } }
            else if (e.st == 1) { mv = false; e.tx = ux; e.ty = uy; if (e.t > 0.75f) { e.st = 2; e.t = 0; } }
            else if (e.st == 2) { moveEnemy(e, e.tx, e.ty, spd * 3.6f, dt); if (e.t > 0.5f) { e.st = 3; e.t = 0; } }
            else { mv = false; if (e.t > 0.7f) { e.st = 0; e.t = 0; } }
            break;
        }
        case B_RANGED: case B_FAN: {
            if (dist > e.range * 0.9f) moveEnemy(e, ux, uy, spd, dt);
            else if (dist < e.range * 0.6f) moveEnemy(e, -ux, -uy, spd * 0.8f, dt);
            else { moveEnemy(e, -uy, ux, spd * 0.5f, dt); }
            e.t2 -= dt;
            if (e.t2 <= 0 && dist < e.range + 70) {
                e.t2 = e.shotCd * frange(0.9f, 1.15f);
                float a = atan2f(dy, dx);
                int n = e.beh == B_FAN ? e.fanN : 1;
                for (int i = 0; i < n; i++) eshot(e.x, e.y - 8, a + (n == 1 ? 0 : ((float)i / (n - 1) - 0.5f) * 0.32f * n), 130, e.shotDmg, TYPE_RGB[DEX[e.di].t1]);
            }
            break;
        }
        case B_BEAMER: {
            if (e.st == 0) {
                if (dist > e.range) moveEnemy(e, ux, uy, spd, dt); else if (dist < e.range * 0.6f) moveEnemy(e, -ux, -uy, spd * 0.8f, dt);
                e.t2 -= dt;
                if (e.t2 <= 0 && dist < e.range + 60) { e.t2 = e.shotCd; e.st = 1; e.t = 0; hazLine(e.x, e.y - 8, atan2f(dy, dx), 340, 22, 0.95f, e.shotDmg * 1.6f, TYPE_RGB[DEX[e.di].t1]); }
            } else { mv = false; if (e.t > 1.2f) e.st = 0; }
            break;
        }
        case B_ZONER: {
            if (dist > e.range * 0.8f) moveEnemy(e, ux, uy, spd, dt); else if (dist < e.range * 0.45f) moveEnemy(e, -ux, -uy, spd * 0.7f, dt);
            e.t2 -= dt;
            if (e.t2 <= 0 && dist < e.range + 100) {
                e.t2 = e.shotCd;
                for (int i = 0; i < e.zones; i++) hazCircle(P.x + (i ? frange(-60, 60) : 0), P.y + (i ? frange(-45, 45) : 0), 38, 1.0f, e.shotDmg * 1.5f, TYPE_RGB[DEX[e.di].t1]);
            }
            break;
        }
        case B_JUMPER: {
            if (e.st == 0) { moveEnemy(e, ux, uy, spd, dt); if (e.t > 3 && dist < 220 && dist > 60) { e.st = 1; e.t = 0; e.tx = P.x; e.ty = P.y; hazCircle(e.tx, e.ty, 34, 0.7f, e.dmg * 1.3f, 0xffd070); } }
            else { mv = false; if (e.t > 0.7f) { e.x = e.tx; e.y = e.ty; e.st = 0; e.t = 0; } }
            break;
        }
        case B_BOMBER: {
            if (e.st == 0) { moveEnemy(e, ux, uy, spd, dt); if (dist < 36) { e.st = 1; e.t = 0; } }
            else {
                mv = false;
                if (e.t > 0.55f) { hazCircle(e.x, e.y, 58, 0.01f, e.dmg * 1.5f, 0xff9a3d); killEnemy(e); return; }
            }
            break;
        }
        case B_HEALER: case B_SHIELDER: case B_SUMMONER: {
            float want = e.range > 0 ? e.range : 200;
            if (dist > want) moveEnemy(e, ux, uy, spd, dt); else if (dist < want * 0.7f) moveEnemy(e, -ux, -uy, spd * 0.8f, dt); else moveEnemy(e, -uy, ux, spd * 0.4f, dt);
            e.t2 -= dt;
            float cd = e.beh == B_SHIELDER ? 5.0f : e.beh == B_SUMMONER ? 7.0f : 3.5f;
            if (e.t2 <= 0) {
                e.t2 = cd;
                if (e.beh == B_SUMMONER) { int n = 0; for (int i = 0; i < MAXE; i++) if (gE[i].on) n++; if (n < CAPE + 8) spawnMinions(e); }
                else {
                    bool heal = e.beh == B_HEALER;
                    fxRing(e.x, e.y - 8, 8, 90, heal ? 0x60e080 : 0x70b0ff, 0.5f, 3);
                    for (int i = 0; i < MAXE; i++) {
                        Enemy& o = gE[i]; if (!o.on || distf(o.x, o.y, e.x, e.y) > 95) continue;
                        if (heal) o.hp = fminf(o.maxHp, o.hp + o.maxHp * 0.2f);
                        else o.shield = fminf(o.maxHp * 0.35f, o.shield + o.maxHp * 0.25f);
                    }
                }
            }
            break;
        }
        default: moveEnemy(e, ux, uy, spd, dt); break;
    }
    e.moving = mv;
    if (fabsf(ux) > fabsf(uy)) e.dir = ux > 0 ? 1 : 3; else e.dir = uy > 0 ? 0 : 2;
    // los jefes añaden ataques con aviso
    if (e.boss) {
        e.hitCd -= 0;
        static float bt; (void)bt;
        e.t2 -= (e.beh == B_RANGED ? 0 : dt);
        if (e.beh != B_RANGED && e.t2 <= 0 && dist < 320) {
            e.t2 = 4.5f;
            int k = rnd() % 3;
            if (k == 0) for (int i = 0; i < 3; i++) hazCircle(P.x + (i ? frange(-70, 70) : 0), P.y + (i ? frange(-50, 50) : 0), 40, 1.0f, e.shotDmg * 1.4f, TYPE_RGB[DEX[e.di].t1]);
            else if (k == 1) { for (int i = 0; i < 8; i++) eshot(e.x, e.y - 12, i * 0.785f, 120, e.shotDmg, TYPE_RGB[DEX[e.di].t1], 6); }
            else hazLine(e.x, e.y - 8, atan2f(dy, dx), 380, 26, 1.0f, e.shotDmg * 1.8f, TYPE_RGB[DEX[e.di].t1]);
        }
    }
}

// ---------------------------------------------------------------- actualización de la partida
static void spawnWave(float dt) {
    int count = 0; bool bossAlive = false;
    for (int i = 0; i < MAXE; i++) if (gE[i].on) { count++; if (gE[i].boss) bossAlive = true; }
    if (gNextBoss < 5 && gTime >= BOSS_SLOTS[gNextBoss].at) {
        float a = frand() * 6.283f;
        int s = spawnEnemy(gBossDef[gNextBoss], P.x + cosf(a) * 230, P.y + sinf(a) * 200, true, false, gTime);
        if (s >= 0) { char b[48]; snprintf(b, sizeof b, "¡%s salvaje apareció!", DEX[gBossDef[gNextBoss].di].name); banner(b, 3.4f); shake(0.8f); sfxPlay(SFX_BOSS); }
        gNextBoss++;
        musicPlay(MUS_BOSS);
    }
    float rate = (1.6f + gTime * 0.028f + powf(gTime / 60, 1.6f) * 0.5f) * 0.24f;
    gSpawnAcc += rate * (bossAlive ? 0.25f : 1) * dt;
    gTierNow = 0; for (int t = 0; t < 6; t++) if (gTime >= TIERS[t].from) gTierNow = t;
    auto spawnOne = [&](float ang) {
        static Def* bag[6 * 8 * 10]; int nb = 0;
        for (int t = 0; t < 6; t++) {
            if (gTime < TIERS[t].from) continue;
            int w = gTime - TIERS[t].from > 260 ? 3 : 10;
            for (int k = 0; k < gNCast[t]; k++) for (int i = 0; i < w && nb < 480; i++) bag[nb++] = &gCast[t][k];
        }
        if (!nb) return;
        Def* d = bag[rnd() % nb];
        int sup = 0;
        if (isSupport(d->beh)) { for (int i = 0; i < MAXE; i++) if (gE[i].on && gE[i].beh == d->beh) sup++; if (sup >= 3) d = bag[rnd() % nb]; if (sup >= 3 && isSupport(d->beh)) return; }
        for (int tries = 0; tries < 6; tries++) {
            float a = tries ? ang + frange(-0.9f, 0.9f) : ang, dd = 230 + frange(10, 70);
            float x = P.x + cosf(a) * dd, y = P.y + sinf(a) * dd * 0.75f;
            if (liquidTile((int)floorf(x / TS), (int)floorf(y / TS))) continue;
            int cnt = 0; for (int i = 0; i < MAXE; i++) if (gE[i].on) cnt++;
            spawnEnemy(*d, x, y, false, cnt >= CAPE * 0.85f, gTime);
            return;
        }
    };
    if (count < CAPE) {
        while (gSpawnAcc >= 1) { gSpawnAcc -= 1; spawnOne(frand() * 6.283f); }
    }
    if (!bossAlive) gSurgeT -= dt;
    if (gSurgeT <= 0) {
        gSurgeT = frange(38, 56);
        float base = frand() * 6.283f;
        int n = (int)((14 + floorf(gTime / 22)) * 0.4f);
        for (int i = 0; i < n && count + i < CAPE; i++) spawnOne(base + frange(-0.55f, 0.55f));
        banner("¡Marea de Pokémon!", 2.2f);
    }
}

static void updateFields(float dt) {
    for (int i = 0; i < MAXF; i++) {
        Field& f = gF[i]; if (!f.on) continue;
        f.t += dt;
        u32 rgb = TYPE_RGB[f.type];
        const MoveDef& d = MOVES[f.mid];
        switch (f.kind) {
            case FD_MINE: {
                bool trig = false;
                if (f.t >= f.next) for (int k = 0; k < MAXE; k++) if (gE[k].on && distf(gE[k].x, gE[k].y, f.x, f.y) < 14 + gE[k].r) { trig = true; break; }
                if (trig || f.t >= f.life) {
                    fxRing(f.x, f.y, 4, f.r, rgb, 0.3f, 4); fxBurst(f.x, f.y - 6, rgb, 10, 150); fxFlash(f.x, f.y, f.r, rgb, 0.15f);
                    blastAt(f, f.r, trig ? 1 : 0.5f); breakProps(f.x, f.y, f.r, f.dmg); sfxPlay(SFX_BOOM); f.on = false;
                }
                break;
            }
            case FD_METEOR:
                if (f.t >= f.life) {
                    fxRing(f.x, f.y, 4, f.r, rgb, 0.35f, 4); fxBurst(f.x, f.y - 6, rgb, 12, 170); fxFlash(f.x, f.y, f.r, rgb, 0.2f);
                    blastAt(f, f.r, 1); breakProps(f.x, f.y, f.r, f.dmg); shake(0.12f); sfxPlay(SFX_BOOM); f.on = false;
                }
                break;
            case FD_TURRET:
                if (f.t >= f.life) { f.on = false; break; }
                f.next -= dt;
                if (f.next <= 0) {
                    int ti = nearestEnemy(f.x, f.y, f.v[K_RANGE] > 0 ? f.v[K_RANGE] : 300);
                    f.next = ti >= 0 ? (f.v[K_RATE] > 0 ? f.v[K_RATE] : 0.6f) : 0.15f;
                    if (ti >= 0) {
                        Shot* s = newShot();
                        if (s) {
                            MoveInst tmp; tmp.id = f.mid; memcpy(tmp.v, f.v, sizeof tmp.v);
                            float a = atan2f(gE[ti].y - f.y, gE[ti].x - f.x);
                            fillShot(s, tmp, f.x, f.y - 8, a, f.v[K_SPEED] > 0 ? f.v[K_SPEED] : 300, f.dmg, 1.4f);
                            s->r = f.v[K_SIZE] > 0 ? f.v[K_SIZE] : 6;
                        }
                    }
                }
                break;
            case FD_PATCH:
                if (f.t >= f.life) { f.on = false; break; }
                f.next -= dt;
                if (f.next <= 0) { f.next = 0.5f; blastAt(f, f.r, 1); }
                break;
            case FD_CHARGE:
                f.x = P.x; f.y = P.y;
                if (f.t >= f.life) {
                    float len = f.v[K_RADIUS], w = f.v[K_WIDTH] > 0 ? f.v[K_WIDTH] : 40;
                    fxBeam(P.x, P.y - 8, P.x + f.ca * len, P.y - 8 + f.sa * len, w, rgb, 0.4f);
                    for (int k = 0; k < MAXE; k++) {
                        Enemy& e = gE[k]; if (!e.on) continue;
                        float px = e.x - P.x, py = e.y - P.y, along = px * f.ca + py * f.sa;
                        if (along < -e.r || along > len + e.r) continue;
                        if (fabsf(-px * f.sa + py * f.ca) <= w / 2 + e.r) hitMove(e, f.dmg, f.type, d.cat, f.v, f.ca, f.sa, f.mid);
                    }
                    shake(0.25f); sfxPlay(SFX_BEAM); f.on = false;
                }
                break;
            case FD_SPIN:
                f.next -= dt;
                if (f.next <= 0) {
                    f.next = 0.13f;
                    fxArc(P.x, P.y - 8, f.r, f.a, 3.6f, rgb, 0.2f);
                    f.a += 2.2f;
                    for (int k = 0; k < MAXE; k++) { Enemy& e = gE[k]; if (e.on && distf(e.x, e.y, P.x, P.y) <= f.r + e.r) hitMove(e, f.dmg, f.type, d.cat, f.v, e.x - P.x, e.y - P.y, f.mid, 40); }
                    breakProps(P.x, P.y, f.r, f.dmg); sfxPlay(SFX_HIT);
                    if (--f.n <= 0) f.on = false;
                }
                break;
            case FD_QUAKE:
                f.next -= dt;
                while (f.next <= 0 && f.i < f.n) {
                    f.next += 0.07f; f.i++;
                    float x = f.x + f.ca * f.i * 34, y = f.y + f.sa * f.i * 34;
                    fxRing(x, y, 4, f.r, rgb, 0.3f, 3); fxBurst(x, y - 4, rgb, 5, 120); fxFlash(x, y, f.r * 0.8f, rgb, 0.12f);
                    Field tmp = f; tmp.x = x; tmp.y = y; blastAt(tmp, f.r, 1); breakProps(x, y, f.r, f.dmg);
                }
                if (f.i >= f.n) f.on = false;
                break;
            case FD_VORTEX: {
                if (f.t >= f.life) { f.on = false; break; }
                for (int k = 0; k < MAXE; k++) {
                    Enemy& e = gE[k]; if (!e.on) continue;
                    float dx = f.x - e.x, dy = f.y - e.y, dd = sqrtf(dx * dx + dy * dy);
                    if (dd > f.r * 1.4f || dd < 4) continue;
                    float kk = fminf(dd, f.a * dt * (e.boss ? 0.25f : 1));
                    e.x += dx / dd * kk; e.y += dy / dd * kk;
                }
                f.next -= dt;
                if (f.next <= 0) { f.next = 0.4f; blastAt(f, f.r, 1); }
                break;
            }
            case FD_STUN:
                if (f.t >= f.life) {
                    fxRing(f.x, f.y, 4, f.r, rgb, 0.35f, 4); fxBurst(f.x, f.y - 6, rgb, 12, 160); fxFlash(f.x, f.y, f.r, rgb, 0.2f);
                    for (int k = 0; k < MAXE; k++) {
                        Enemy& e = gE[k]; if (!e.on || distf(e.x, e.y, f.x, f.y) > f.r + e.r) continue;
                        hitMove(e, f.dmg, f.type, d.cat, f.v, e.x - f.x, e.y - f.y, f.mid);
                        if (e.on) e.stun = fmaxf(e.stun, (f.v[K_STUN] > 0 ? f.v[K_STUN] : 1) * (e.boss ? 0.35f : 1));
                    }
                    breakProps(f.x, f.y, f.r, f.dmg); sfxPlay(SFX_BOOM); f.on = false;
                }
                break;
        }
    }
}

static void updateShots(float dt) {
    for (int i = 0; i < MAXS; i++) {
        Shot& s = gS[i]; if (!s.on) continue;
        s.life -= dt;
        if (s.life <= 0) { s.on = false; continue; }
        s.px = s.x; s.py = s.y;
        if (s.boom) {
            s.boomT -= dt;
            if (s.boomT <= 0) {
                s.back = true;
                float dx = P.x - s.x, dy = P.y - 8 - s.y, d = sqrtf(dx * dx + dy * dy);
                if (d < 14) { s.on = false; continue; }
                s.vx = dx / d * s.bsp; s.vy = dy / d * s.bsp;
                s.nh = 0;
            }
        }
        if (s.homing > 0) {
            int t = nearestEnemy(s.x, s.y, 260);
            if (t >= 0) {
                float dx = gE[t].x - s.x, dy = gE[t].y - 8 - s.y, d = sqrtf(dx * dx + dy * dy);
                float sp = sqrtf(s.vx * s.vx + s.vy * s.vy), k = 1 - expf(-s.homing * dt);
                s.vx += (dx / d * sp - s.vx) * k; s.vy += (dy / d * sp - s.vy) * k;
            }
        }
        s.x += s.vx * dt; s.y += s.vy * dt;
        for (int k = 0; k < MAXE; k++) {
            Enemy& e = gE[k]; if (!e.on) continue;
            if (distf(s.x, s.y, e.x, e.y - 6) > s.r + e.r) continue;
            bool seen = false; for (int h = 0; h < s.nh; h++) if (s.hits[h] == e.id) seen = true;
            if (seen) continue;
            hitEnemy(e, s.dmg, s.type, s.cat, s.burn, s.poison, s.slow, s.knock, s.vx, s.vy, s.mid);
            if (s.nh < 8) s.hits[s.nh++] = e.id;
            fxRing(s.x, s.y, 3, 14, TYPE_RGB[s.type], 0.18f, 2);
            if (!s.boom && s.pierce == 0) {
                if (s.bounce > 0) {
                    int nt = nearestEnemy(s.x, s.y, 220, s.hits, s.nh);
                    if (nt >= 0) {
                        s.bounce--; float sp = sqrtf(s.vx * s.vx + s.vy * s.vy);
                        float dx = gE[nt].x - s.x, dy = gE[nt].y - s.y, d = sqrtf(dx * dx + dy * dy);
                        s.vx = dx / d * sp; s.vy = dy / d * sp; s.life += 0.5f; break;
                    }
                }
                s.on = false; break;
            } else if (!s.boom && s.pierce > 0) s.pierce--;
            if (!s.on) break;
        }
        if (s.on) {
            int tx = (int)floorf(s.x / TS), ty = (int)floorf(s.y / TS);
            int k = propAt(tx, ty, nullptr);
            if (k >= PR_ROCK) { float px, py; propPos(tx, ty, &px, &py); if (distf(s.x, s.y, px, py) < propR(k) + s.r) { breakProp(tx, ty, k); s.on = false; } }
        }
    }
}

static void orbitsUpdate(float dt) {
    for (int b = 0; b < 4; b++) {
        MoveInst& m = gMoves[b];
        if (m.id < 0 || MOVES[m.id].kind != MK_ORBIT) continue;
        const MoveDef& d = MOVES[m.id];
        P.orbA[b] += m.v[K_SPEED] * dt;
        int n = (int)fmaxf(1, m.v[K_COUNT]);
        float dmg = m.v[K_DMG] * atkBase(d), rad = m.v[K_RADIUS], sz = m.v[K_SIZE] > 0 ? m.v[K_SIZE] : 8, rehit = fmaxf(0.12f, m.v[K_CD]);
        for (int i = 0; i < n; i++) {
            float a = P.orbA[b] + (float)i / n * 6.283f;
            float ox = P.x + cosf(a) * rad, oy = P.y - 8 + sinf(a) * rad * 0.85f;
            for (int k = 0; k < MAXE; k++) {
                Enemy& e = gE[k]; if (!e.on) continue;
                e.orbCd[b] -= 0;
                if (e.orbCd[b] > 0) continue;
                if (distf(ox, oy, e.x, e.y - 6) <= sz + e.r) {
                    e.orbCd[b] = rehit;
                    hitMove(e, dmg, d.type, d.cat, m.v, e.x - P.x, e.y - P.y, m.id);
                    fxRing(ox, oy, 3, 16, TYPE_RGB[d.type], 0.2f, 2);
                }
            }
        }
    }
    for (int k = 0; k < MAXE; k++) if (gE[k].on) for (int b = 0; b < 4; b++) if (gE[k].orbCd[b] > 0) gE[k].orbCd[b] -= dt;
}

static void updateEnemies(float dt) {
    for (int i = 0; i < MAXE; i++) {
        Enemy& e = gE[i]; if (!e.on) continue;
        if (e.flash > 0) e.flash -= dt;
        if (e.stun > 0) e.stun -= dt;
        if (e.slowT > 0) { e.slowT -= dt; if (e.slowT <= 0) e.slow = 0; }
        if (e.burn > 0) {
            e.burnT -= dt; e.burnTick -= dt;
            if (e.burnTick <= 0) { e.burnTick = 0.5f; float d = 1.6f * e.burn * (1 + P.level * 0.06f); damageEnemyRaw(e, d); if (!e.on) continue; fxBurst(e.x, e.y - 10, 0xff8a3d, 1, 40); }
            if (e.burnT <= 0) e.burn = 0;
        }
        if (e.poison > 0) {
            e.poiT -= dt; e.poiTick -= dt;
            if (e.poiTick <= 0) { e.poiTick = 0.6f; damageEnemyRaw(e, e.maxHp * 0.012f * e.poison + 1); if (!e.on) continue; }
            if (e.poiT <= 0) e.poison = 0;
        }
        enemyAI(e, dt);
        if (!e.on) continue;
        e.x += e.kx * dt; e.y += e.ky * dt; e.kx *= expf(-8 * dt); e.ky *= expf(-8 * dt);
        pushOut(e.x, e.y, e.r * 0.5f);
        // contacto con el jugador
        e.hitCd -= dt;
        if (e.hitCd <= 0 && distf(e.x, e.y, P.x, P.y) < e.r + 9 && e.beh != B_BOMBER) {
            e.hitCd = 0.8f;
            hurtPlayer(e.dmg, enemyCat(e), e.di);
        }
        // lejos de todo: reaparece por delante
        if (distf(e.x, e.y, P.x, P.y) > 520 && !e.boss) {
            float a = atan2f(P.vy, P.vx) + frange(-0.9f, 0.9f);
            if (fabsf(P.vx) + fabsf(P.vy) < 5) a = frand() * 6.283f;
            e.x = P.x + cosf(a) * 250; e.y = P.y + sinf(a) * 200;
        }
    }
    // separación entre enemigos
    for (int i = 0; i < MAXE; i++) {
        Enemy& a = gE[i]; if (!a.on) continue;
        for (int j = i + 1; j < MAXE; j++) {
            Enemy& b = gE[j]; if (!b.on) continue;
            float dx = b.x - a.x; if (dx > 24 || dx < -24) continue;
            float dy = b.y - a.y; if (dy > 24 || dy < -24) continue;
            float d2 = dx * dx + dy * dy, m = (a.r + b.r) * 0.7f;
            if (d2 < m * m && d2 > 0.01f) {
                float d = sqrtf(d2), push = (m - d) * 0.35f;
                a.x -= dx / d * push; a.y -= dy / d * push; b.x += dx / d * push; b.y += dy / d * push;
            }
        }
    }
}

static void levelUpCheck() {
    if (P.xp >= P.xpNeed && gPS == PS_RUN) {
        P.xp -= P.xpNeed; P.level++; P.xpNeed = xpFor(P.level);
        gPS = PS_LEVELUP; sfxPlay(SFX_LEVEL);
        fxRing(P.x, P.y - 8, 10, 60, 0xffee80, 0.5f, 4);
    }
}

static void updatePickups(float dt) {
    for (int i = 0; i < MAXP; i++) {
        Pick& p = gP[i]; if (!p.on) continue;
        p.t += dt;
        float dx = P.x - p.x, dy = P.y - p.y, d = sqrtf(dx * dx + dy * dy);
        bool vac = p.kind == 4;
        if (d < P.magnet * (vac ? 0.5f : 1) || p.t > 25) {
            float sp = 160 + (P.magnet - d) * 3;
            if (d > 1) { p.x += dx / d * sp * dt; p.y += dy / d * sp * dt; }
        }
        if (d < 12) {
            p.on = false;
            switch (p.kind) {
                case 0: P.xp += p.val * P.xpMul; sfxPlay(SFX_PICK); break;
                case 1: gCoins += (int)p.val; sfxPlay(SFX_PICK); break;
                case 2: healPlayer(P.maxHp * 0.25f); fxText(P.x, P.y - 30, "+PS", 0x60e080, 0.5f); sfxPlay(SFX_PICK); break;
                case 3: if (p.val >= 10) gT10++; else gT1++; fxText(P.x, P.y - 30, "+Ticket", 0xffd23f, 0.5f); sfxPlay(SFX_PICK); break;
                case 4:
                    for (int k = 0; k < MAXP; k++) if (gP[k].on && gP[k].kind <= 1) { gP[k].t = 30; }
                    fxText(P.x, P.y - 30, "¡Imán!", 0x80c0ff, 0.5f); sfxPlay(SFX_PICK); break;
            }
        }
    }
}

static void updatePlayer(float dt, float jx, float jy) {
    float spd = P.spd * P.spdMul * (P.buffSpdT > 0 ? 1 + P.buffSpd : 1);
    if (P.buffSpdT > 0) P.buffSpdT -= dt;
    if (P.buffAtkT > 0) P.buffAtkT -= dt;
    if (P.buffDefT > 0) P.buffDefT -= dt;
    int tx = (int)floorf(P.x / TS), ty = (int)floorf(P.y / TS);
    bool inLiq = liquidTile(tx, ty);
    if (inLiq) {
        int k = liquidKind();
        spd *= k == 5 ? 0.85f : 0.62f;
        P.liqT -= dt;
        if (P.liqT <= 0) {
            P.liqT = 0.5f;
            bool fire = pdex().t1 == 1 || pdex().t2 == 1; (void)fire;
            if (k == 1 && !(pdex().t1 == 1 || pdex().t2 == 1)) hurtPlayer(P.maxHp * 0.04f, -1, -1);
            if (k == 3 && !(pdex().t1 == 7 || pdex().t2 == 7)) hurtPlayer(P.maxHp * 0.02f, -1, -1);
            if (k == 4 && !(pdex().t1 == 3 || pdex().t2 == 3)) hurtPlayer(P.maxHp * 0.02f, -1, -1);
        }
    }
    float l = sqrtf(jx * jx + jy * jy);
    if (l > 1) { jx /= l; jy /= l; l = 1; }
    P.moving = l > 0.12f;
    float vx = P.moving ? jx * spd : 0, vy = P.moving ? jy * spd : 0;
    P.vx += (vx - P.vx) * clampf(dt * 14, 0, 1); P.vy += (vy - P.vy) * clampf(dt * 14, 0, 1);
    P.x += P.vx * dt; P.y += P.vy * dt;
    pushOut(P.x, P.y, 7);
    if (P.moving) {
        if (fabsf(jx) > fabsf(jy)) P.dir = jx > 0 ? 1 : 3; else P.dir = jy > 0 ? 0 : 2;
        gAimX = jx; gAimY = jy;
    }
    if (P.invuln > 0) P.invuln -= dt;
    if (P.flash > 0) P.flash -= dt;
    healPlayer(P.regen * dt);
}

void playFireButton(int b) { gManualDown |= 1u << b; }
float playCdFrac(int b) {
    if (gMoves[b].id < 0) return 0;
    float cd = fmaxf(0.05f, gMoves[b].v[K_CD] * P.cdMul);
    return clampf(gMoves[b].cd / cd, 0, 1);
}

static void updateMoves(float dt, u32 down) {
    gTarget = nearestEnemy(P.x, P.y, 520);
    if (gTarget >= 0) {
        float dx = gE[gTarget].x - P.x, dy = gE[gTarget].y - 8 - P.y + 8;
        P.aim = atan2f(dy, dx);
    } else P.aim = atan2f(gAimY, gAimX);
    static const u32 keys[4] = {KEY_X, KEY_Y, KEY_B, KEY_A};
    for (int b = 0; b < 4; b++) {
        MoveInst& m = gMoves[b]; if (m.id < 0) continue;
        if (MOVES[m.id].kind == MK_ORBIT) continue;
        m.cd -= dt;
        if (m.cd > 0) continue;
        bool pressed = (down & keys[b]) || (gManualDown & (1u << b));
        if (!gAuto && !pressed) continue;
        if (needsTarget(MOVES[m.id].kind) && !pressed) {
            if (gTarget < 0 || distf(P.x, P.y, gE[gTarget].x, gE[gTarget].y) > reachOf(m)) { m.cd = 0.05f; continue; }
        } else if (!needsTarget(MOVES[m.id].kind) && !pressed) {
            // los de zona / mejora no se gastan si no hay nadie cerca
            int k = MOVES[m.id].kind;
            if (k != MK_TRAIL && k != MK_BUFF && gTarget < 0) { m.cd = 0.1f; continue; }
            if (k == MK_BUFF && (gTarget < 0 || distf(P.x, P.y, gE[gTarget].x, gE[gTarget].y) > 300)) { m.cd = 0.2f; continue; }
        }
        if (castMove(b)) m.cd = fmaxf(0.05f, m.v[K_CD] * P.cdMul);
        else m.cd = 0.1f;
    }
    gManualDown = 0;
}

void playUpdate(float dt, u32 down, u32 held, int jx, int jy) {
    (void)held;
    gMs = osGetTime();
    // efectos siempre
    for (int i = 0; i < MAXFX; i++) {
        Fx& f = gFx[i]; if (!f.on) continue;
        f.t += dt; f.x += f.vx * dt; f.y += f.vy * dt;
        if (f.kind == FX_PART) { f.vx *= expf(-4 * dt); f.vy *= expf(-4 * dt); }
        if (f.t >= f.life) f.on = false;
    }
    if (gBannerT > 0) gBannerT -= dt;
    if (gShake > 0) gShake -= dt * 2;
    if (gPS != PS_RUN) return;
    gTime += dt;
    if (gTime >= WIN_TIME) { gPS = PS_WIN; sfxPlay(SFX_LEVEL); return; }

    int setNow = ((int)(gTime / 300)) % 3;
    static int lastBiome = -1;
    if (setNow != lastBiome) {
        if (lastBiome >= 0) { gSet = (gChar % 3 + setNow) % 3; tilesLoad(gSet); banner(TILESET_NAMES[gSet], 3.0f); }
        lastBiome = setNow;
    }
    if (gTime < 0.05f) lastBiome = -1;

    updatePlayer(dt, jx / 100.0f, jy / 100.0f);
    updateMoves(dt, down);
    orbitsUpdate(dt);
    spawnWave(dt);
    updateEnemies(dt);
    updateShots(dt);
    updateFields(dt);
    updateHazards(dt);
    updatePickups(dt);
    levelUpCheck();
    // música de jefe: vuelve a la normal al caer
    bool boss = false; for (int i = 0; i < MAXE; i++) if (gE[i].on && gE[i].boss) boss = true;
    static bool wasBoss; if (wasBoss && !boss) musicPlay(MUS_BATTLE); wasBoss = boss;
}

// ---------------------------------------------------------------- reinicio
void playReset(int charIdx, const int* startMoves, int nStart) {
    memset(gE, 0, sizeof gE); memset(gS, 0, sizeof gS); memset(gES, 0, sizeof gES); memset(gH, 0, sizeof gH);
    memset(gP, 0, sizeof gP); memset(gF, 0, sizeof gF); memset(gFx, 0, sizeof gFx);
    gNBroken = 0; gTime = 0; gSpawnAcc = 0; gSurgeT = 32; gKills = 0; gBossesDown = 0; gCoins = 0; gT1 = gT10 = 0;
    gNextBoss = 0; gNextId = 0; gPS = PS_RUN; gShake = 0; gBannerT = 0; gManualDown = 0;
    gChar = charIdx; gSet = charIdx % 3;
    memset(&P, 0, sizeof P);
    P.di = charIdx;
    const DexE& p = DEX[charIdx];
    int lv[NPERM]; for (int i = 0; i < NPERM; i++) lv[i] = gSave.perm[i];
    P.maxHp = p.hp + lv[PU_HP] * 8; P.hp = P.maxHp; P.spd = p.spd * 0.9f;
    P.atkMul = 1 + lv[PU_ATK] * 0.04f; P.spdMul = 1 + lv[PU_SPD] * 0.03f; P.cdMul = 1 - lv[PU_CD] * 0.03f;
    P.dmgReduce = lv[PU_DEF] * 0.02f; P.regen = lv[PU_REGEN] * 0.2f; P.magnet = 78 * (1 + lv[PU_MAGNET] * 0.12f);
    P.xpMul = 1 + lv[PU_XP] * 0.05f; P.coinMul = 1 + lv[PU_COINS] * 0.08f; P.crit = lv[PU_CRIT] * 0.03f;
    P.level = 1; P.xpNeed = xpFor(1); P.rerolls = 0; P.dir = 0;
    gRerollsLeft = 1 + lv[PU_REROLL];
    for (int b = 0; b < 4; b++) { gMoves[b].id = -1; gMoves[b].cd = 0; }
    for (int i = 0; i < nStart && i < 4; i++) slotPlace(startMoves[i]);
    rollRun();
    tilesLoad(gSet);
    gAimX = 0; gAimY = 1; gTarget = -1;
    gTierNow = 0;
    banner(TILESET_NAMES[gSet], 3.0f);
}

PlayState playState() { return gPS; }
void playSetState(PlayState s) { gPS = s; }
RunStats playStats() {
    RunStats r;
    r.time = gTime; r.kills = gKills; r.level = P.level; r.bosses = gBossesDown; r.t1 = gT1 + (int)(gTime / 300); r.t10 = gT10; r.won = gPS == PS_WIN;
    float base = floorf(gTime / 5) + floorf(gKills * 0.25f) + gBossesDown * 80 + gCoins;
    r.coins = (int)roundf(base * P.coinMul);
    return r;
}
float playHpFrac() { return clampf(P.hp / P.maxHp, 0, 1); }
float playXpFrac() { return clampf(P.xp / P.xpNeed, 0, 1); }
int playLevel() { return P.level; }
float playTime() { return gTime; }
int playKills() { return gKills; }
int playCoins() { return gCoins; }
int playCharIdx() { return gChar; }
int playRerolls() { return gRerollsLeft; }

// ---------------------------------------------------------------- cartas de nivel
static const char* STAT_NAME[9] = {"Vigor", "Potencia", "Carrera", "Reflejos", "Coraza", "Síntesis", "Imán", "Aprendizaje", "Baya Zidra"};
static const char* STAT_DESC[9] = {"+20 de vida máxima (y la recupera).", "+10% de daño con todos los movimientos.", "+7% de velocidad.",
                                   "-8% de recarga en todos los movimientos.", "+6% de reducción de daño recibido.", "+0.9 de vida por segundo.",
                                   "+30% de radio de recogida.", "+12% de experiencia ganada.", "Recupera el 45% de tu vida ahora."};
static int gStatTaken[9];
void playBuildCards(CardSet& cs) {
    struct Cand { int kind, arg, w; };
    Cand c[160]; int n = 0;
    if (nMoves() < 4) {
        const DexE& p = pdex();
        static bool seen[NMOVES]; memset(seen, 0, sizeof seen);
        auto addPool = [&](int t) {
            const PoolRef& r = POOL_BY_TYPE[t];
            for (int i = 0; i < r.n; i++) { int mid = POOL_ALL[r.off + i]; if (seen[mid] || ownsMove(mid) || gSave.bannedMove[mid]) continue; seen[mid] = true; if (n < 150) c[n++] = {0, mid, 6}; }
        };
        addPool(0); addPool(p.t1); if (p.t2 != 255) addPool(p.t2);
    }
    for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0 && gMoves[b].lvl < 5) c[n++] = {1, b, 9};
    for (int s = 0; s < 9; s++) {
        if (s == 1 && gStatTaken[1] >= 40) continue; if (s == 2 && gStatTaken[2] >= 8) continue; if (s == 3 && gStatTaken[3] >= 10) continue;
        if (s == 4 && gStatTaken[4] >= 12) continue; if (s == 6 && gStatTaken[6] >= 6) continue; if (s == 7 && gStatTaken[7] >= 8) continue;
        c[n++] = {2, s, nMoves() < 4 ? 2 : 4};
    }
    cs.n = 0;
    for (int pick = 0; pick < 3 && n > 0; pick++) {
        int tot = 0; for (int i = 0; i < n; i++) tot += c[i].w;
        int x = (int)(rnd() % (u32)tot), idx = 0;
        for (; idx < n - 1; idx++) { x -= c[idx].w; if (x < 0) break; }
        Card& cd = cs.c[cs.n++]; memset(&cd, 0, sizeof cd);
        cd.kind = c[idx].kind; cd.arg = c[idx].arg;
        if (cd.kind == 0) {
            const MoveDef& d = MOVES[cd.arg];
            snprintf(cd.title, sizeof cd.title, "Nuevo: %s", T(d.name)); snprintf(cd.desc, sizeof cd.desc, "%s", T(d.desc)); cd.col = TYPE_RGB[d.type];
        } else if (cd.kind == 1) {
            const MoveInst& m = gMoves[cd.arg]; const MoveDef& d = MOVES[m.id];
            snprintf(cd.title, sizeof cd.title, "%s  Nv %d → %d", T(d.name), m.lvl, m.lvl + 1); snprintf(cd.desc, sizeof cd.desc, "%s", T(d.ups[m.lvl - 1].text)); cd.col = TYPE_RGB[d.type];
        } else {
            snprintf(cd.title, sizeof cd.title, "%s", T(STAT_NAME[cd.arg])); snprintf(cd.desc, sizeof cd.desc, "%s", T(STAT_DESC[cd.arg])); cd.col = 0x8fa3c4;
        }
        c[idx] = c[--n];
    }
}
bool playReroll(CardSet& cs) {
    if (gRerollsLeft <= 0) return false;
    gRerollsLeft--; playBuildCards(cs); return true;
}
void playApplyCard(const Card& c) {
    if (c.kind == 0) slotPlace(c.arg);
    else if (c.kind == 1) { MoveInst& m = gMoves[c.arg]; if (m.lvl < 5) { m.lvl++; moveRecompute(m); } }
    else {
        gStatTaken[c.arg]++;
        switch (c.arg) {
            case 0: P.maxHp += 20; healPlayer(20); break;
            case 1: P.atkMul *= 1.10f; break;
            case 2: P.spdMul *= 1.07f; break;
            case 3: P.cdMul *= 0.92f; break;
            case 4: P.dmgReduce = fminf(0.7f, P.dmgReduce + 0.06f); break;
            case 5: P.regen += 0.9f; break;
            case 6: P.magnet *= 1.3f; break;
            case 7: P.xpMul *= 1.12f; break;
            case 8: healPlayer(P.maxHp * 0.45f); break;
        }
    }
    gPS = PS_RUN;
    P.invuln = fmaxf(P.invuln, 0.8f);
    levelUpCheck();
}

// ---------------------------------------------------------------- dibujo
static void quadLine(float x1, float y1, float x2, float y2, float w, u32 col, float z) {
    float dx = x2 - x1, dy = y2 - y1, l = sqrtf(dx * dx + dy * dy);
    if (l < 0.01f) return;
    float nx = -dy / l * w / 2, ny = dx / l * w / 2;
    C2D_DrawTriangle(x1 + nx, y1 + ny, col, x1 - nx, y1 - ny, col, x2 + nx, y2 + ny, col, z);
    C2D_DrawTriangle(x1 - nx, y1 - ny, col, x2 - nx, y2 - ny, col, x2 + nx, y2 + ny, col, z);
}
static void ringDraw(float x, float y, float r, float w, u32 col, float z) {
    int n = r < 20 ? 12 : r < 50 ? 18 : 24;
    float px = x + r, py = y;
    for (int i = 1; i <= n; i++) {
        float a = i * 6.2832f / n, nx = x + cosf(a) * r, ny = y + sinf(a) * r * 0.85f;
        C2D_DrawLine(px, py, col, nx, ny, col, w, z);
        px = nx; py = ny;
    }
}
static void fanDraw(float x, float y, float r, float a0, float a1, u32 col, float z) {
    int n = 8; float px = x + cosf(a0) * r, py = y + sinf(a0) * r * 0.85f;
    for (int i = 1; i <= n; i++) {
        float a = a0 + (a1 - a0) * i / n, nx = x + cosf(a) * r, ny = y + sinf(a) * r * 0.85f;
        C2D_DrawTriangle(x, y, col, px, py, col, nx, ny, col, z);
        px = nx; py = ny;
    }
}
static void circle(float x, float y, float r, u32 col, float z) { C2D_DrawCircleSolid(x, y, z, r, col); }

static void drawFx(float cx, float cy, bool top) {
    for (int i = 0; i < MAXFX; i++) {
        Fx& f = gFx[i]; if (!f.on) continue;
        float p = f.t / f.life, x = f.x - cx, y = f.y - cy;
        int al = (int)(255 * (1 - p));
        u32 hi = lighten(f.rgb, 0.7f);
        switch (f.kind) {
            case FX_RING: {
                float r = f.r0 + (f.r1 - f.r0) * p;
                ringDraw(x, y, r, f.w + 3, rgbA(darken(f.rgb, 0.5f), al / 2), 0.62f);
                ringDraw(x, y, r, f.w, rgbA(hi, al), 0.64f);
                break;
            }
            case FX_ARC: {
                float r = f.r1 * (0.6f + 0.4f * p), a0 = f.a - f.arc / 2, a1 = f.a + f.arc / 2;
                fanDraw(x, y - 8, r, a0, a1, rgbA(f.rgb, (int)(al * 0.55f)), 0.6f);
                float px = x + cosf(a0) * r, py = y - 8 + sinf(a0) * r * 0.85f;
                for (int k = 1; k <= 8; k++) {
                    float a = a0 + (a1 - a0) * k / 8, nx = x + cosf(a) * r, ny = y - 8 + sinf(a) * r * 0.85f;
                    C2D_DrawLine(px, py, rgbA(0xffffff, al), nx, ny, rgbA(0xffffff, al), 3, 0.66f);
                    px = nx; py = ny;
                }
                break;
            }
            case FX_BEAM: {
                float w = f.w * (1 - p * 0.6f);
                quadLine(x, y, f.x2 - cx, f.y2 - cy, w + 8, rgbA(darken(f.rgb, 0.6f), al / 2), 0.6f);
                quadLine(x, y, f.x2 - cx, f.y2 - cy, w, rgbA(f.rgb, al), 0.62f);
                quadLine(x, y, f.x2 - cx, f.y2 - cy, w * 0.4f, rgbA(0xffffff, al), 0.64f);
                break;
            }
            case FX_BOLT: {
                float x2 = f.x2 - cx, y2 = f.y2 - cy, mx = (x + x2) / 2 + frange(-8, 8), my = (y + y2) / 2 + frange(-8, 8);
                quadLine(x, y, mx, my, 5, rgbA(f.rgb, al), 0.62f); quadLine(mx, my, x2, y2, 5, rgbA(f.rgb, al), 0.62f);
                quadLine(x, y, mx, my, 2, rgbA(0xffffff, al), 0.64f); quadLine(mx, my, x2, y2, 2, rgbA(0xffffff, al), 0.64f);
                break;
            }
            case FX_FLASH: circle(x, y - 6, f.r1 * (0.5f + p * 0.5f), rgbA(hi, al / 2), 0.58f); break;
            case FX_PART: circle(x, y, f.w * (1 - p * 0.5f), rgbA(hi, al), 0.66f); break;
            case FX_TEXT: if (top) text(f.txt, x, y - 6, f.w, rgbA(f.rgb, al), true); break;
        }
    }
}

struct DrawItem { float y; u8 kind; short idx; };
static DrawItem gDI[300];
static int diCmp(const void* a, const void* b) { float d = ((const DrawItem*)a)->y - ((const DrawItem*)b)->y; return d < 0 ? -1 : d > 0; }

static void drawFieldsGround(float cx, float cy) {
    for (int i = 0; i < MAXF; i++) {
        Field& f = gF[i]; if (!f.on) continue;
        float x = f.x - cx, y = f.y - cy; u32 rgb = TYPE_RGB[f.type];
        switch (f.kind) {
            case FD_MINE: {
                bool armed = f.t >= f.next; float pulse = 0.5f + 0.5f * sinf(f.t * 9);
                circle(x, y, 7, rgbA(darken(rgb, 0.4f), 255), 0.3f); circle(x, y, 5, rgbA(armed ? lighten(rgb, 0.5f * pulse) : rgb, 255), 0.31f);
                ringDraw(x, y, f.r * 0.5f, 1.5f, rgbA(rgb, 70), 0.29f);
                break;
            }
            case FD_METEOR: {
                float p = clampf(f.t / f.life, 0, 1);
                if (f.t < 0) break;
                ringDraw(x, y, f.r * (0.4f + 0.6f * p), 3, rgbA(0xffffff, 150), 0.3f);
                ringDraw(x, y, f.r, 2, rgbA(rgb, 200), 0.3f);
                circle(x, y - (1 - p) * 150, 10 + p * 4, rgbA(lighten(rgb, 0.5f), 255), 0.7f);
                circle(x, y - (1 - p) * 150, 6, rgbA(0xffffff, 255), 0.71f);
                break;
            }
            case FD_TURRET: {
                circle(x, y, 8, rgbA(darken(rgb, 0.4f), 255), 0.4f); circle(x, y - 4, 7, rgbA(rgb, 255), 0.41f); circle(x, y - 4, 3, rgbA(0xffffff, 255), 0.42f);
                break;
            }
            case FD_PATCH: {
                int a = (int)(110 * (1 - f.t / f.life) + 40);
                circle(x, y, f.r, rgbA(darken(rgb, 0.6f), a), 0.28f); circle(x, y, f.r * 0.7f, rgbA(rgb, a), 0.29f);
                ringDraw(x, y, f.r, 2, rgbA(lighten(rgb, 0.4f), a + 40), 0.29f);
                break;
            }
            case FD_CHARGE: {
                float p = f.t / f.life;
                circle(x, y - 8, 6 + p * 18, rgbA(lighten(rgb, 0.4f), 100 + (int)(120 * p)), 0.6f);
                quadLine(x, y - 8, x + f.ca * f.v[K_RADIUS], y - 8 + f.sa * f.v[K_RADIUS], 3, rgbA(rgb, 120), 0.3f);
                break;
            }
            case FD_VORTEX: {
                float ph = f.t * 6;
                circle(x, y, f.r, rgbA(darken(rgb, 0.5f), 70), 0.28f);
                for (int k = 0; k < 3; k++) { float a = ph + k * 2.09f; ringDraw(x + cosf(a) * f.r * 0.3f, y + sinf(a) * f.r * 0.25f, f.r * (0.55f + k * 0.15f), 2.5f, rgbA(lighten(rgb, 0.3f), 170), 0.29f); }
                break;
            }
            case FD_STUN: {
                float p = f.t / f.life;
                ringDraw(x, y, f.r, 3, rgbA(0xffffff, 120 + (int)(100 * p)), 0.3f);
                circle(x, y, f.r * p, rgbA(rgb, 90), 0.29f);
                break;
            }
        }
    }
    for (int i = 0; i < MAXH; i++) {
        Haz& h = gH[i]; if (!h.on || h.fired) continue;
        float p = h.t / h.delay, x = h.x - cx, y = h.y - cy;
        int pulse = ((int)(h.t * 12) & 1) ? 190 : 120;
        if (h.line) {
            float ex = x + cosf(h.ang) * h.len, ey = y + sinf(h.ang) * h.len;
            quadLine(x, y, ex, ey, h.w * p, rgbA(0xff4040, pulse), 0.35f);
            quadLine(x, y, ex, ey, 2, rgbA(0xffffff, 200), 0.36f);
        } else {
            circle(x, y, h.r, rgbA(0xff3030, (int)(60 + 50 * p)), 0.34f);
            circle(x, y, h.r * p, rgbA(0xff6040, pulse), 0.35f);
            ringDraw(x, y, h.r, 2.5f, rgbA(0xffffff, 230), 0.36f);
        }
    }
}

static void drawShot(Shot& s, float cx, float cy) {
    float x = s.x - cx, y = s.y - cy;
    u32 rgb = TYPE_RGB[s.type];
    float r = s.r < 5 ? 5.5f : s.r + 1.5f;
    // rastro
    float dx = s.x - s.px, dy = s.y - s.py;
    float vl = sqrtf(s.vx * s.vx + s.vy * s.vy);
    if (vl > 1) { float tx = -s.vx / vl * r * 1.6f, ty = -s.vy / vl * r * 1.6f;
        circle(x + tx, y + ty, r * 0.8f, rgbA(rgb, 130), 0.58f); circle(x + tx * 2, y + ty * 2, r * 0.55f, rgbA(rgb, 70), 0.57f); }
    (void)dx; (void)dy;
    circle(x, y, r + 2.5f, rgbA(darken(rgb, 0.35f), 255), 0.6f);
    circle(x, y, r, rgbA(lighten(rgb, 0.15f), 255), 0.61f);
    circle(x, y, r * 0.5f, rgbA(0xffffff, 255), 0.62f);
}

static void drawWorldTiles(float cx, float cy) {
    const TileSet& T = TILESETS[gSet];
    int tx0 = (int)floorf(cx / TS) - 1, ty0 = (int)floorf(cy / TS) - 1;
    int cols = 15, rows = 10;
    for (int j = 0; j < rows; j++) for (int i = 0; i < cols; i++) gLiqGrid[j][i] = liquidTile(tx0 + i, ty0 + j);
    int liqAnim = (int)(gMs / 500) & 1;
    for (int j = 1; j < rows; j++) {
        for (int i = 1; i < cols; i++) {
            int tx = tx0 + i, ty = ty0 + j;
            float sx = tx * TS - cx, sy = ty * TS - cy;
            if (sx < -TS || sx > TOP_W || sy < -TS || sy > TOP_H) continue;
            u32 h = hash2(tx, ty, wseed());
            if (gLiqGrid[j][i]) {
                tileDraw(T.liquid[((h >> 4) + liqAnim) & 1], sx, sy, 0.1f);
                continue;
            }
            if ((h & 15) == 0) tileDraw(T.dirt[(h >> 8) & 1], sx, sy, 0.1f);
            else tileDraw(T.floor[(h >> 4) & 3], sx, sy, 0.1f);
            if (gLiqGrid[j - 1][i]) tileDraw(T.edge[0], sx + T.edge[0].ax, sy + T.edge[0].ay, 0.12f);
            if (gLiqGrid[j][i + 1]) tileDraw(T.edge[1], sx + T.edge[1].ax, sy + T.edge[1].ay, 0.12f);
            if (gLiqGrid[j + 1][i]) tileDraw(T.edge[2], sx + T.edge[2].ax, sy + T.edge[2].ay, 0.12f);
            if (gLiqGrid[j][i - 1]) tileDraw(T.edge[3], sx + T.edge[3].ax, sy + T.edge[3].ay, 0.12f);
            if (((h >> 12) & 15) < 2) tileDraw(T.deco[(h >> 16) % 6], sx, sy, 0.15f);
        }
    }
}

static void drawProp(int kind, int tx, int ty, float cx, float cy) {
    const TileSet& T = TILESETS[gSet];
    float px, py; propPos(tx, ty, &px, &py);
    float sx = px - cx, sy = py - cy;
    int var = 0; propAt(tx, ty, &var);
    if (kind == PR_TREE) { C2D_DrawEllipseSolid(sx - 12, sy - 4, 0.38f, 24, 8, COL(0, 0, 0, 70)); tileDraw(T.tree[var], sx - T.tree[var].ax, sy - T.tree[var].ay, 0.5f); }
    else if (kind == PR_ROCK) { C2D_DrawEllipseSolid(sx - 12, sy - 4, 0.38f, 24, 8, COL(0, 0, 0, 70)); tileDraw(T.rock[var], sx - T.rock[var].ax, sy - T.rock[var].ay, 0.5f); }
    else {
        bool big = kind == PR_BIG; float w = big ? 22 : 16, h = big ? 16 : 12;
        C2D_DrawEllipseSolid(sx - w / 2 - 2, sy - 4, 0.38f, w + 4, 8, COL(0, 0, 0, 70));
        C2D_DrawRectSolid(sx - w / 2 - 1, sy - h - 1, 0.5f, w + 2, h + 2, COL(70, 40, 10, 255));
        C2D_DrawRectSolid(sx - w / 2, sy - h, 0.51f, w, h, big ? COL(240, 190, 40, 255) : COL(190, 120, 40, 255));
        C2D_DrawRectSolid(sx - w / 2, sy - h, 0.52f, w, 4, big ? COL(255, 235, 120, 255) : COL(220, 160, 70, 255));
        C2D_DrawRectSolid(sx - 2, sy - h / 2 - 1, 0.53f, 4, 5, COL(255, 255, 255, 255));
    }
}

void playDraw(u64 ms) {
    gMs = ms;
    float shx = gShake > 0 ? frange(-1, 1) * gShake * 6 : 0, shy = gShake > 0 ? frange(-1, 1) * gShake * 6 : 0;
    float cx = floorf(P.x - TOP_W / 2 + shx), cy = floorf(P.y - 10 - TOP_H / 2 + shy);
    gCamX = cx; gCamY = cy;
    C2D_DrawRectSolid(0, 0, 0, TOP_W, TOP_H, rgbA(TILESET_FLOOR_RGBA[gSet] >> 8, 255));
    drawWorldTiles(cx, cy);
    drawFieldsGround(cx, cy);

    // objetos ordenados por y
    int n = 0;
    int tx0 = (int)floorf(cx / TS) - 1, tx1 = (int)floorf((cx + TOP_W) / TS) + 1, ty0 = (int)floorf(cy / TS) - 1, ty1 = (int)floorf((cy + TOP_H) / TS) + 3;
    for (int ty = ty0; ty <= ty1 && n < 250; ty++)
        for (int tx = tx0; tx <= tx1 && n < 250; tx++) {
            int k = propAt(tx, ty, nullptr);
            if (k != PR_NONE) { float px, py; propPos(tx, ty, &px, &py); gDI[n++] = {py, (u8)(10 + k), (short)((tx & 0xff) | 0)}; gDI[n - 1].idx = 0; gDI[n - 1].y = py; gDI[n - 1].kind = (u8)(10 + k); gDI[n - 1].idx = (short)0; (void)tx; (void)ty; gDI[n - 1].idx = 0; }
        }
    // (las coordenadas de los props se recalculan en el bucle de dibujo; guardamos tx,ty en tablas paralelas)
    static short ptx[256], pty[256]; int np = 0;
    n = 0;
    for (int ty = ty0; ty <= ty1 && np < 250; ty++)
        for (int tx = tx0; tx <= tx1 && np < 250; tx++) {
            int k = propAt(tx, ty, nullptr);
            if (k == PR_NONE) continue;
            float px, py; propPos(tx, ty, &px, &py);
            ptx[np] = (short)tx; pty[np] = (short)ty;
            gDI[n++] = {py, (u8)(10 + k), (short)np}; np++;
        }
    for (int i = 0; i < MAXE && n < 296; i++) if (gE[i].on && fabsf(gE[i].x - P.x) < 280 && fabsf(gE[i].y - P.y) < 200) gDI[n++] = {gE[i].y, 1, (short)i};
    gDI[n++] = {P.y, 2, 0};
    qsort(gDI, n, sizeof(DrawItem), diCmp);
    for (int i = 0; i < n; i++) {
        DrawItem& di = gDI[i];
        if (di.kind >= 10) { drawProp(di.kind - 10, ptx[di.idx], pty[di.idx], cx, cy); continue; }
        if (di.kind == 1) {
            Enemy& e = gE[di.idx];
            float x = e.x - cx, y = e.y - cy, sc = e.boss ? 2.0f : 1.0f;
            C2D_DrawEllipseSolid(x - e.r, y - e.r * 0.35f, 0.4f, e.r * 2, e.r * 0.7f, COL(0, 0, 0, 80));
            C2D_ImageTint tint;
            bool tinted = false;
            if (e.flash > 0) { C2D_PlainImageTint(&tint, COL(255, 255, 255, 255), 0.85f); tinted = true; }
            else if (e.stun > 0) { C2D_PlainImageTint(&tint, COL(255, 240, 80, 255), 0.5f); tinted = true; }
            else if (e.st == 1 && (e.beh == B_BOMBER)) { C2D_PlainImageTint(&tint, ((int)(e.t * 16) & 1) ? COL(255, 60, 40, 255) : COL(255, 255, 255, 255), 0.7f); tinted = true; }
            else if (e.burn > 0) { C2D_PlainImageTint(&tint, COL(255, 120, 40, 255), 0.35f); tinted = true; }
            else if (e.poison > 0) { C2D_PlainImageTint(&tint, COL(190, 90, 220, 255), 0.35f); tinted = true; }
            else if (e.slow > 0) { C2D_PlainImageTint(&tint, COL(120, 200, 255, 255), 0.35f); tinted = true; }
            sprDraw(DEX_NUM[e.di], e.dir, gMs, e.moving, x, y, tinted ? &tint : nullptr, sc);
            if (e.shield > 0) ringDraw(x, y - 12 * sc, e.r + 6, 2, COL(120, 180, 255, 220), 0.7f);
            if (e.beh >= B_HEALER && e.beh <= B_SUMMONER && !e.boss) {}
            if (e.boss) {
                const PokeSpr& s = POKE_SPR[DEX_NUM[e.di]]; float yy = y - s.h * sc - 10;
                C2D_DrawRectSolid(x - 26, yy, 0.8f, 52, 5, COL(0, 0, 0, 220));
                C2D_DrawRectSolid(x - 25, yy + 1, 0.85f, 50 * clampf(e.hp / e.maxHp, 0, 1), 3, COL(230, 60, 60, 255));
            } else if (e.hp < e.maxHp) {
                float yy = y - 4;
                C2D_DrawRectSolid(x - 10, yy, 0.8f, 20, 3, COL(0, 0, 0, 170));
                C2D_DrawRectSolid(x - 9, yy + 0.5f, 0.85f, 18 * clampf(e.hp / e.maxHp, 0, 1), 2, COL(230, 80, 80, 255));
            }
        } else {
            float x = P.x - cx, y = P.y - cy;
            C2D_DrawEllipseSolid(x - 10, y - 4, 0.4f, 20, 8, COL(0, 0, 0, 90));
            if (P.invuln <= 0 || ((int)(gTime * 14) & 1)) {
                C2D_ImageTint tint; bool t = false;
                if (P.flash > 0) { C2D_PlainImageTint(&tint, COL(255, 80, 80, 255), 0.7f); t = true; }
                sprDraw(DEX_NUM[P.di], P.dir, gMs, P.moving, x, y, t ? &tint : nullptr, 1.0f);
            }
        }
    }
    // órbitas
    for (int b = 0; b < 4; b++) {
        MoveInst& m = gMoves[b]; if (m.id < 0 || MOVES[m.id].kind != MK_ORBIT) continue;
        int cnt = (int)fmaxf(1, m.v[K_COUNT]); float rad = m.v[K_RADIUS], sz = m.v[K_SIZE] > 0 ? m.v[K_SIZE] : 8; u32 rgb = TYPE_RGB[MOVES[m.id].type];
        for (int i = 0; i < cnt; i++) {
            float a = P.orbA[b] + (float)i / cnt * 6.283f;
            float ox = P.x - cx + cosf(a) * rad, oy = P.y - cy - 8 + sinf(a) * rad * 0.85f;
            circle(ox, oy, sz + 3, rgbA(darken(rgb, 0.35f), 255), 0.6f); circle(ox, oy, sz, rgbA(lighten(rgb, 0.15f), 255), 0.61f); circle(ox, oy, sz * 0.5f, rgbA(0xffffff, 255), 0.62f);
        }
    }
    for (int i = 0; i < MAXS; i++) if (gS[i].on) drawShot(gS[i], cx, cy);
    for (int i = 0; i < MAXES; i++) if (gES[i].on) {
        float x = gES[i].x - cx, y = gES[i].y - cy;
        circle(x, y, gES[i].r + 2.5f, COL(30, 0, 30, 255), 0.6f); circle(x, y, gES[i].r, rgbA(gES[i].col, 255), 0.61f); circle(x, y, gES[i].r * 0.45f, COL(255, 255, 255, 255), 0.62f);
    }
    for (int i = 0; i < MAXP; i++) {
        Pick& p = gP[i]; if (!p.on) continue;
        float x = p.x - cx, y = p.y - cy - 4 + sinf(p.t * 5) * 1.5f;
        if (x < -10 || x > TOP_W + 10 || y < -10 || y > TOP_H + 10) continue;
        switch (p.kind) {
            case 0: circle(x, y, 4.5f, COL(20, 60, 120, 255), 0.45f); circle(x, y, 3.5f, COL(90, 200, 255, 255), 0.46f); circle(x - 1, y - 1, 1.2f, COL(255, 255, 255, 255), 0.47f); break;
            case 1: circle(x, y, 5, COL(120, 80, 0, 255), 0.45f); circle(x, y, 4, COL(255, 210, 50, 255), 0.46f); break;
            case 2: circle(x, y, 6, COL(255, 255, 255, 255), 0.45f); C2D_DrawRectSolid(x - 1.5f, y - 4, 0.47f, 3, 8, COL(230, 50, 80, 255)); C2D_DrawRectSolid(x - 4, y - 1.5f, 0.47f, 8, 3, COL(230, 50, 80, 255)); break;
            case 3: C2D_DrawRectSolid(x - 7, y - 5, 0.45f, 14, 10, COL(255, 255, 255, 255)); C2D_DrawRectSolid(x - 6, y - 4, 0.46f, 12, 8, COL(255, 190, 40, 255)); break;
            case 4: circle(x, y, 6, COL(60, 90, 230, 255), 0.45f); circle(x, y, 3, COL(230, 60, 60, 255), 0.46f); break;
        }
    }
    drawFx(cx, cy, true);

    // HUD superior mínimo
    float bx = TOP_W / 2;
    C2D_DrawRectSolid(bx - 15, TOP_H / 2 + 6, 0.8f, 30, 4, COL(0, 0, 0, 200));
    C2D_DrawRectSolid(bx - 14, TOP_H / 2 + 7, 0.85f, 28 * playHpFrac(), 2, COL(90, 230, 90, 255));
    char b[48];
    C2D_DrawRectSolid(0, 0, 0.8f, TOP_W, 14, COL(0, 0, 0, 120));
    snprintf(b, sizeof b, "Nv %d", P.level); text(b, 4, -2, 0.45f, COL(255, 255, 255, 255));
    int sec = (int)gTime; snprintf(b, sizeof b, "%02d:%02d", sec / 60, sec % 60); text(b, bx, -2, 0.45f, COL(255, 255, 255, 255), true);
    snprintf(b, sizeof b, "KO %d", gKills); text(b, TOP_W - 52, -2, 0.45f, COL(255, 230, 120, 255));
    if (gBannerT > 0) text(gBanner, bx, 30, 0.7f, COL(255, 240, 160, 255), true);
}
