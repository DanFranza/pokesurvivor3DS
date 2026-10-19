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
    bool on, boss, moving, legend, judge;
    short di;                       // fila en DEX
    u8 beh, dir, st;
    float x, y, hp, maxHp, spd, dmg, xp, r, flash, t, t2, tx, ty, kx, ky, shield, hitCd, took;
    float shotDmg, shotCd, range;
    short minion; u8 fanN, zones;
    float burn, burnT, burnTick, poison, poiT, poiTick, slow, slowT, stun;
    float orbCd[8];
    int id;
};
struct Shot {
    bool on, boom, back; u8 own;
    float x, y, vx, vy, life, dmg, r, burn, poison, slow, knock, homing, boomT, bsp, px, py;
    u8 type, pierce, bounce, cat, nh; short mid;
    int hits[8];
};
struct EShot { bool on; float x, y, vx, vy, life, dmg, r; u32 col; };
struct Haz { bool on, line, fired, tru; float x, y, ang, len, w, r, t, delay, dmg, post; u32 col; };
struct Pick { bool on; u8 kind; float x, y, val, t; };       // 0 xp 1 moneda 2 curar 3 ticket 4 imán
struct Field {
    bool on; u8 kind, type, own; short mid;
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

enum { BEH_COUNT = 13, B_THIEF = 99 };
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
// Estado propio de cada jugador (en cooperativo hay dos; el resto del mundo es compartido).
struct Ctx {
    Player p;
    MoveInst moves[4];
    int active, bonds, bondAskN;
    u8 grpN;
    int item, itemNew;
    float itemRegen, sashT, bell, bellT;
    int rerollsLeft, target;
    float aimX, aimY;
    u32 manualDown;
    int statTaken[9];
    int pend;                       // niveles por elegir (cooperativo: la partida no se pausa)
    bool dead, shiny;
    bool bondWait, adead;           // vínculo por decidir (pausa) · caído dentro de la grieta
};
static int gTickN;
static Ctx gC[2];
static Ctx* gCur = &gC[0];
static int gCi, gNP = 1, gLoc;      // contexto activo, nº de jugadores, jugador de esta consola
MoveInst* gMovesL = gC[0].moves;
#undef gMoves
#define gMoves (gCur->moves)
#define P (gCur->p)
#define gActive (gCur->active)
#define gBonds (gCur->bonds)
#define gBondAskN (gCur->bondAskN)
#define gGrpN (gCur->grpN)
#define gItem (gCur->item)
#define gItemNew (gCur->itemNew)
#define gItemRegen (gCur->itemRegen)
#define gSashT (gCur->sashT)
#define gBell (gCur->bell)
#define gBellT (gCur->bellT)
#define gRerollsLeft (gCur->rerollsLeft)
#define gTarget (gCur->target)
#define gAimX (gCur->aimX)
#define gAimY (gCur->aimY)
#define gManualDown (gCur->manualDown)
#define gStatTaken (gCur->statTaken)
// ejecuta código en el contexto de otro jugador
struct Sc {
    Ctx* o; int oi;
    explicit Sc(int i) { o = gCur; oi = gCi; gCur = &gC[i]; gCi = i; }
    ~Sc() { gCur = o; gCi = oi; }
};
static u32 gVrs = 2463534242u;      // RNG sólo visual: no puede alterar la simulación
static float vfrand() { gVrs ^= gVrs << 13; gVrs ^= gVrs >> 17; gVrs ^= gVrs << 5; return (gVrs & 0xFFFFFF) / 16777216.0f; }
static float vfrange(float a, float b) { return a + (b - a) * vfrand(); }

static PlayState gPS = PS_RUN;
static float gTime, gSpawnAcc, gSurgeT, gShake, gBannerT, gPreT;
static char gBanner[80];
static int gKills, gBossesDown, gCoins, gT1, gT10, gNextId, gChar, gSet, gNextBoss;
static int gKillsType[18], gChests, gEvolves, gRifts;
static float gCamX, gCamY;
static Def gCast[6][8]; static int gNCast[6];
static Def gBossDef[5];
// eventos: ladrón de monedas y grieta (arena del legendario)
static float ARENA_H = 320;
static bool gArena, gArenaDead, gPortal;
static float gArenaX, gArenaY, gArenaT, gArenaEnd, gSavedX[2], gSavedY[2];
static float gThiefT, gRiftChk, gRiftMiss, gPortalX, gPortalY, gPortalT;
static int gThiefN;
// Pokémon perdido: lo tocas, te sigue y lo llevas a la marca verde
static struct { bool on, follow, moving; int di, who, dir; float x, y, tx, ty, hp, t, hitCd, flash, r; } gLost;
static float gLostT;
static Enemy sE[MAXE]; static Pick sP[MAXP]; static Field sF[MAXF];
// objetos equipables
struct ItemDef { const char* name; const char* desc; };
static const ItemDef ITEMS[11] = {
    {"Restos", "Recuperas un 1,5% de tu vida por segundo."},
    {"Cinta Elección", "+40% de daño, pero no puedes cambiar de movimiento."},
    {"Garra Rápida", "-20% de recarga en todos tus movimientos."},
    {"Banda Focus", "Un golpe mortal te deja con 1 de vida (cada 60 s)."},
    {"Cascabel Concha", "Recuperas vida con el daño que haces."},
    {"Moneda Amuleto", "+50% de Pokémonedas al acabar."},
    {"Huevo Suerte", "+30% de experiencia."},
    {"Vidasfera", "+30% de daño, pero cada ataque te quita vida."},
    {"Pañuelo Elección", "+35% de velocidad."},
    {"Casco Dentado", "Los que te tocan reciben daño."},
    {"Chaleco Asalto", "-20% de daño recibido."}};
// la Sentencia de Arceus (al llegar a WIN_TIME): arena enorme, Arceus invencible y legendarios cada vez más fuertes
static int gJ, gJN, gJDowns, gJArDi, gJNs; static u8 gJDir; static bool gJMoving;
static float gJT, gJBossT, gJCast, gJTouch, gJLift, gJX, gJY, gJBase, gJSecT, gJSamp[30];
static bool gHazTru;
// clima: 1 sol, 2 lluvia, 3 arena, 4 nieve, 5 niebla
static int gWx; static float gWxT, gWxDur, gWxChk, gWxChip;
static const char* WX_NAMES[6] = {"", "Sol abrasador", "Lluvia", "Tormenta de arena", "Nevada", "Niebla"};
static const char* WX_HINT[6] = {"", "Fuego se potencia, Agua se debilita", "Agua se potencia, Fuego se debilita", "Roca, Tierra y Acero se potencian; el resto sufre", "Hielo se potencia; el resto sufre", "Fantasma, Hada y Psíquico se potencian"};
static const u32 WX_COL[6] = {0, 0xffcb3d, 0x7fb8ff, 0xe0bf73, 0xd8f1ff, 0xc9cfdc};
static float wxLevel() { return gWx ? fmaxf(0, fminf(1, fminf(gWxT / 3, (gWxDur - gWxT) / 3))) : 0; }
static float wxMult(int type) {
    static const float M[6][18] = {
        {}, {0, 1.5f, 0.5f}, {0, 0.5f, 1.5f, 1.2f}, {0, 0, 0, 0, 0, 0, 0, 0, 1.3f, 0, 0, 0, 1.3f, 0, 0, 0, 1.3f}, {0, 0, 0, 0, 0, 1.5f},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.3f, 0, 0, 1.3f, 0, 0, 0, 1.3f}};
    if (!gWx || type < 0 || type > 17 || M[gWx][type] == 0) return 1;
    return 1 + (M[gWx][type] - 1) * wxLevel();
}
static bool wxHurts(int t1, int t2) {
    if (gWx != 3 && gWx != 4) return false;
    auto safe = [](int t) { return gWx == 3 ? (t == 12 || t == 8 || t == 16) : t == 5; };
    return !(safe(t1) || (t2 < 18 && safe(t2)));
}
static float wxSpeed(int t1, int t2) { return gWx == 4 && !(t1 == 5 || t2 == 5) ? 1 - 0.1f * wxLevel() : 1; }
static float gTargetD;
static u8 gBroken[512][2]; static int gNBroken;
static bool gLiqGrid[14][18];
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
        Fx* f = newFx(FX_PART, vfrange(0.25f, 0.5f)); if (!f) return;
        float a = vfrand() * 6.283f, s = vfrange(0.4f, 1.0f) * spd;
        f->x = x; f->y = y; f->vx = cosf(a) * s; f->vy = sinf(a) * s; f->rgb = rgb; f->w = vfrange(2.5f, 4.5f);
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
    if (gArena && fabsf(tx * TS + 16 - gArenaX) < ARENA_H + TS && fabsf(ty * TS + 16 - gArenaY) < ARENA_H + TS) return false;
    return vnoise(tx / 4.5f, ty / 4.5f, wseed() + 3) > 0.78f - pools * 0.85f;
}
enum { PR_NONE, PR_TREE, PR_ROCK, PR_CHEST, PR_BIG };
static bool isBroken(int tx, int ty) {
    for (int i = 0; i < gNBroken; i++) if (gBroken[i][0] == (u8)(tx & 255) && gBroken[i][1] == (u8)(ty & 255)) return true;
    return false;
}
static int propAt(int tx, int ty, int* var) {
    if (tx * tx + ty * ty < 30) return PR_NONE;
    if (gArena && fabsf(tx * TS + 16 - gArenaX) < ARENA_H + TS && fabsf(ty * TS + 16 - gArenaY) < ARENA_H + TS) return PR_NONE;
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

static int grpSize(int g) { int n = 0; for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0 && gMoves[b].grp == g) n++; return n; }
static bool inActive(int b) { return gActive >= 0 && gMoves[b].id >= 0 && gMoves[gActive].id >= 0 && gMoves[b].grp == gMoves[gActive].grp; }
static void slotPlace(int mid) {
    static const int order[4] = {3, 2, 1, 0};
    for (int k = 0; k < 4; k++) {
        int b = order[k];
        if (gMoves[b].id < 0) {
            gMoves[b].id = mid; gMoves[b].lvl = 1; gMoves[b].grp = ++gGrpN; gMoves[b].cd = 0.3f; gMoves[b].dealt = 0; moveRecompute(gMoves[b]);
            if (gActive < 0 || gMoves[gActive].id < 0) gActive = b;
            return;
        }
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
static int itemRoll() { int i; do i = rnd() % 11; while (i == gItem); return i; }
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

static void thiefLoot(Enemy& e);
static void riftWin(Enemy& e);
static void killEnemy(Enemy& e) {
    if (!e.on) return;
    e.on = false;
    gKills++;
    {
        const DexE& dp = DEX[e.di];
        if (dp.t1 < 18) gKillsType[dp.t1]++;
        if (dp.t2 < 18 && dp.t2 != dp.t1) gKillsType[dp.t2]++;
    }
    if (e.beh == B_THIEF) { thiefLoot(e); return; }
    if (e.legend) { riftWin(e); return; }
    fxBurst(e.x, e.y - 8, 0xffffff, e.boss ? 18 : 6, e.boss ? 150 : 90);
    if (e.boss) fxRing(e.x, e.y - 8, 6, 90, 0xffe070, 0.5f, 5);
    sfxPlay(e.boss ? SFX_BOSS : SFX_KILL);
    dropPick(0, e.x, e.y, e.xp);
    if (e.judge) {
        gJDowns++;
        if (gJDowns > gSave.stat[SB_JBEST]) gSave.stat[SB_JBEST] = gJDowns;
        return;
    }
    float r = frand();
    if (e.boss) {
        gBossesDown++;
        dropPick(5, e.x - 26, e.y - 10, (float)itemRoll());
        for (int i = 0; i < 12; i++) dropPick(1, e.x + frange(-24, 24), e.y + frange(-18, 18), 3);
        if (frand() < 1.0f / 3) dropPick(3, e.x, e.y - 10, 10);   // ticket ×10 (como en la web)
        dropPick(2, e.x + 14, e.y, 1);
        gShake = 0.5f;
    } else {
        if (frand() < 1.0f / 400) dropPick(3, e.x + frange(-6, 6), e.y, 1);
        if (r < 0.10f) dropPick(1, e.x + frange(-6, 6), e.y + frange(-4, 4), 1);
        else if (r < 0.115f) dropPick(2, e.x, e.y, 1);
        else if (r < 0.12f) dropPick(4, e.x, e.y, 1);
    }
}

static void damageEnemyRaw(Enemy& e, float dmg) {
    if (e.shield > 0) { float a = fminf(e.shield, dmg); e.shield -= a; dmg -= a; }
    e.hp -= dmg;
    e.took += dmg;
    if (gItem == 4) gBell = fminf(4, gBell + dmg * 0.04f);
    e.flash = 0.12f;
    if (e.hp <= 0) killEnemy(e);
}

static void hitEnemy(Enemy& e, float dmg, int type, int cat, float burn, float poison, float slow, float knock, float dx, float dy, int mid) {
    const DexE& p = DEX[e.di];
    float tm = typeMult(type, p.t1, p.t2);
    float g = cat == 2 ? 1 : guardMul(cat == 1 ? p.sd : p.df);
    bool crit = frand() < P.crit;
    float d = dmg * tm * g * (crit ? 1.5f : 1) * wxMult(type);
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
    for (int i = 0; i < MAXS; i++) if (!gS[i].on) { memset(&gS[i], 0, sizeof gS[i]); gS[i].on = true; gS[i].own = (u8)gCi; return &gS[i]; }
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
        f.on = true; f.own = (u8)gCi; f.kind = kind; f.mid = m.id; f.type = MOVES[m.id].type; f.x = x; f.y = y; memcpy(f.v, m.v, sizeof f.v);
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
        gChests++;
        int n = 4 + rnd() % 4;
        for (int i = 0; i < n; i++) dropPick(1, x + frange(-14, 14), y + frange(-10, 10), 3);
        dropPick(frand() < 0.5f ? 2 : 4, x, y, 1);
        if (frand() < 0.08f) dropPick(5, x + 12, y - 8, (float)itemRoll());
        dropPick(0, x, y, 20);
        fxRing(x, y - 8, 6, 46, 0xf2c443, 0.45f, 4);
    } else if (kind == PR_BIG) {
        gChests++;
        for (int i = 0; i < 9; i++) dropPick(1, x + frange(-22, 22), y + frange(-14, 14), 4);
        int tk = 1 + rnd() % 3;
        for (int i = 0; i < tk; i++) dropPick(3, x + frange(-16, 16), y + frange(-10, 10), 1);
        if (frand() < 0.15f) dropPick(3, x, y - 10, 10);
        if (frand() < 0.5f) dropPick(5, x + 14, y - 10, (float)itemRoll());
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
static Haz* newHaz() { for (int i = 0; i < MAXH; i++) if (!gH[i].on) { memset(&gH[i], 0, sizeof gH[i]); gH[i].on = true; gH[i].tru = gHazTru; return &gH[i]; } return nullptr; }
static void hazCircle(float x, float y, float r, float delay, float dmg, u32 col) {
    Haz* h = newHaz(); if (!h) return; h->x = x; h->y = y; h->r = r; h->delay = delay; h->dmg = dmg; h->col = col; h->post = 0.2f;
}
static void hazLine(float x, float y, float ang, float len, float w, float delay, float dmg, u32 col) {
    Haz* h = newHaz(); if (!h) return; h->line = true; h->x = x; h->y = y; h->ang = ang; h->len = len; h->w = w; h->delay = delay; h->dmg = dmg; h->col = col; h->post = 0.3f;
}
static void eshot(float x, float y, float a, float sp, float dmg, u32 col, float r = 5) {
    for (int i = 0; i < MAXES; i++) if (!gES[i].on) { gES[i] = {true, x, y, cosf(a) * sp, sinf(a) * sp, 3.0f, dmg, r, col}; return; }
}

static void hurtPlayer(float dmg, int cat, int srcDi, bool tru = false) {
    if (P.invuln > 0 || P.hp <= 0) return;
    float g = srcDi >= 0 && !tru ? guardMul(cat == 1 ? pdex().sd : pdex().df) : 1;
    float red = tru ? 0 : clampf(P.dmgReduce + (P.buffDefT > 0 ? P.buffDef : 0), 0, 0.8f);
    float d = dmg * g * (1 - red);
    P.hp -= d; P.invuln = 0.55f; P.flash = 0.2f;
    char b[12]; snprintf(b, sizeof b, "-%d", (int)(d + 0.5f));
    fxText(P.x, P.y - 28, b, 0xff6060, 0.55f);
    shake(0.2f);
    sfxPlay(SFX_HURT);
    if (P.hp <= 0 && gItem == 3 && gTime - gSashT > 60) {
        gSashT = gTime; P.hp = 1; P.invuln = 1.2f;
        fxText(P.x, P.y - 40, "¡Banda Focus!", 0xff9a3d, 0.7f);
        fxRing(P.x, P.y - 8, 6, 70, 0xff9a3d, 0.5f, 4);
        return;
    }
    if (P.hp <= 0) {
        if (gArena && !gJ) {
            P.hp = 1; P.invuln = 99; gCur->adead = true;
            bool all = true; for (int i = 0; i < gNP; i++) if (!gC[i].adead) all = false;
            if (all) gArenaDead = true;
            return;
        }
        P.hp = 0;
        if (gNP > 1) {
            gCur->dead = true;
            fxRing(P.x, P.y - 8, 8, 50, 0xff6060, 0.5f, 4);
            if (gC[0].dead && gC[1].dead) { gPS = PS_OVER; sfxPlay(SFX_OVER); }
            return;
        }
        gPS = PS_OVER; sfxPlay(SFX_OVER);
    }
}
static int enemyCat(const Enemy& e) { return DEX[e.di].sa > DEX[e.di].pa ? 1 : 0; }

static int nearPlayer(float x, float y) {
    int b = -1; float bd = 1e18f;
    for (int i = 0; i < gNP; i++) {
        if (gC[i].dead) continue;
        float dx = gC[i].p.x - x, dy = gC[i].p.y - y, d = dx * dx + dy * dy;
        if (d < bd) { bd = d; b = i; }
    }
    return b < 0 ? 0 : b;
}

static void updateHazards(float dt) {
    for (int i = 0; i < MAXH; i++) {
        Haz& h = gH[i]; if (!h.on) continue;
        h.t += dt;
        if (!h.fired && h.t >= h.delay) {
            h.fired = true;
            if (h.line) {
                float ca = cosf(h.ang), sa = sinf(h.ang);
                for (int pi = 0; pi < gNP; pi++) {
                    if (gC[pi].dead) continue;
                    Sc sc(pi);
                    float px = P.x - h.x, py = P.y - 8 - h.y, along = px * ca + py * sa;
                    if (along > 0 && along < h.len && fabsf(-px * sa + py * ca) < h.w / 2 + 6) hurtPlayer(h.dmg, 1, 0, h.tru);
                }
                fxBeam(h.x, h.y, h.x + ca * h.len, h.y + sa * h.len, h.w, h.col, 0.3f);
            } else {
                for (int pi = 0; pi < gNP; pi++) {
                    if (gC[pi].dead) continue;
                    Sc sc(pi);
                    if (distf(P.x, P.y, h.x, h.y) < h.r + 6) hurtPlayer(h.dmg, enemyCat(gE[0]), 0, h.tru);
                }
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
        bool hit = false;
        for (int pi = 0; pi < gNP && !hit; pi++) {
            if (gC[pi].dead) continue;
            Sc sc(pi);
            if (distf(s.x, s.y, P.x, P.y - 8) < s.r + 7) { hurtPlayer(s.dmg, 1, 0); hit = true; }
        }
        if (hit) { s.on = false; fxBurst(s.x, s.y, s.col, 4, 60); }
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
    float spd = e.spd * wxSpeed(DEX[e.di].t1, DEX[e.di].t2);
    e.t += dt;
    if (e.stun > 0) { e.moving = false; return; }
    if (e.beh == B_THIEF) {
        float a = atan2f(-dy, -dx) + sinf(e.t * 2.2f) * 0.7f;
        float ax = cosf(a), ay = sinf(a);
        moveEnemy(e, ax, ay, dist < 300 ? e.spd : e.spd * 0.35f, dt);
        e.moving = true;
        if (fabsf(ax) > fabsf(ay)) e.dir = ax > 0 ? 1 : 3; else e.dir = ay > 0 ? 0 : 2;
        if (e.t > 15) {
            e.on = false;
            fxBurst(e.x, e.y - 8, 0xffd23f, 10, 110);
            char b[48]; snprintf(b, sizeof b, "¡%s se ha escapado!", pname(e.di)); banner(b);
        }
        return;
    }
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
        if (s >= 0) { char b[48]; snprintf(b, sizeof b, "¡%s salvaje apareció!", pname(gBossDef[gNextBoss].di)); banner(b, 3.4f); shake(0.8f); sfxPlay(SFX_BOSS); }
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
        Sc sc(f.own);
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
        Sc sc(s.own);
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
        if (m.id < 0 || MOVES[m.id].kind != MK_ORBIT || !inActive(b)) continue;
        const MoveDef& d = MOVES[m.id];
        P.orbA[b] += m.v[K_SPEED] * dt;
        int n = (int)fmaxf(1, m.v[K_COUNT]);
        float dmg = m.v[K_DMG] * atkBase(d), rad = m.v[K_RADIUS], sz = m.v[K_SIZE] > 0 ? m.v[K_SIZE] : 8, rehit = fmaxf(0.12f, m.v[K_CD]);
        for (int i = 0; i < n; i++) {
            float a = P.orbA[b] + (float)i / n * 6.283f;
            float ox = P.x + cosf(a) * rad, oy = P.y - 8 + sinf(a) * rad * 0.85f;
            for (int k = 0; k < MAXE; k++) {
                Enemy& e = gE[k]; if (!e.on) continue;
                if (e.orbCd[b + 4 * gCi] > 0) continue;
                if (distf(ox, oy, e.x, e.y - 6) <= sz + e.r) {
                    e.orbCd[b + 4 * gCi] = rehit;
                    hitMove(e, dmg, d.type, d.cat, m.v, e.x - P.x, e.y - P.y, m.id);
                    fxRing(ox, oy, 3, 16, TYPE_RGB[d.type], 0.2f, 2);
                }
            }
        }
    }
}
static void orbitsCool(float dt) {
    for (int k = 0; k < MAXE; k++) if (gE[k].on) for (int b = 0; b < 8; b++) if (gE[k].orbCd[b] > 0) gE[k].orbCd[b] -= dt;
}

static void updateEnemies(float dt) {
    for (int i = 0; i < MAXE; i++) {
        Enemy& e = gE[i]; if (!e.on) continue;
        Sc sc(nearPlayer(e.x, e.y));
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
        if (e.hitCd <= 0 && distf(e.x, e.y, P.x, P.y) < e.r + 9 && e.beh != B_BOMBER && e.beh != B_THIEF) {
            e.hitCd = 0.8f;
            hurtPlayer(e.dmg * wxMult(DEX[e.di].t1), enemyCat(e), e.di);
            if (gItem == 9 && !e.judge) damageEnemyRaw(e, 15 + P.level * 4.0f);
        }
        // lejos de todo: reaparece por delante
        if (distf(e.x, e.y, P.x, P.y) > 520 && !e.boss && e.beh != B_THIEF) {
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
    if (gNP > 1) {
        if (gCur->dead) return;
        while (P.xp >= P.xpNeed) {
            P.xp -= P.xpNeed; P.level++; P.xpNeed = xpFor(P.level); gCur->pend++;
            sfxPlay(SFX_LEVEL); fxRing(P.x, P.y - 8, 10, 60, 0xffee80, 0.5f, 4);
            for (int j = 0; j < gNP; j++) if (gC[j].dead) {
                gC[j].dead = false; gC[j].p.hp = gC[j].p.maxHp * 0.5f; gC[j].p.invuln = 2.5f;
                fxRing(gC[j].p.x, gC[j].p.y - 8, 10, 70, 0x80ff80, 0.6f, 4); fxText(gC[j].p.x, gC[j].p.y - 30, "¡Revivido!", 0x80ff80, 0.7f);
            }
        }
        return;
    }
    if (P.xp >= P.xpNeed && gPS == PS_RUN) {
        P.xp -= P.xpNeed; P.level++; P.xpNeed = xpFor(P.level);
        gPS = PS_LEVELUP; sfxPlay(SFX_LEVEL);
        fxRing(P.x, P.y - 8, 10, 60, 0xffee80, 0.5f, 4);
    }
}

static void itemApply(int id, bool on) {
    if (id < 0) return;
    float k = on ? 1 : -1;
    switch (id) {
        case 0: if (on) { gItemRegen = P.maxHp * 0.015f; P.regen += gItemRegen; } else P.regen -= gItemRegen; break;
        case 1: if (on) P.atkMul *= 1.4f; else P.atkMul /= 1.4f; break;
        case 2: if (on) P.cdMul *= 0.8f; else P.cdMul /= 0.8f; break;
        case 5: if (on) P.coinMul *= 1.5f; else P.coinMul /= 1.5f; break;
        case 6: if (on) P.xpMul *= 1.3f; else P.xpMul /= 1.3f; break;
        case 7: if (on) P.atkMul *= 1.3f; else P.atkMul /= 1.3f; break;
        case 8: if (on) P.spdMul *= 1.35f; else P.spdMul /= 1.35f; break;
        case 10: P.dmgReduce += 0.2f * k; break;
        default: break;
    }
}
static void itemOffer(int id) {
    if (id < 0 || id >= 11) return;
    gSave.items[id] = 1;
    char b[64];
    if (gItem == id) { snprintf(b, sizeof b, "Ya llevas %s", T(ITEMS[id].name)); banner(b, 2); return; }
    if (gItem < 0) {
        gItem = id; itemApply(id, true);
        snprintf(b, sizeof b, "¡Llevas %s!", T(ITEMS[id].name)); banner(b, 2.6f);
        return;
    }
    gItemNew = id; if (gNP == 1) gPS = PS_ITEM;
}
int itemCount() { return 11; }
const char* itemName(int i) { return T(ITEMS[i].name); }
const char* itemDesc(int i) { return T(ITEMS[i].desc); }
int playItem() { return gItem; }
int playItemNew() { return gItemNew; }
void playItemChoose(bool takeNew) {
    if (takeNew && gItemNew >= 0) {
        itemApply(gItem, false); gItem = gItemNew; itemApply(gItem, true);
        char b[64]; snprintf(b, sizeof b, "¡Llevas %s!", T(ITEMS[gItem].name)); banner(b, 2.6f);
    }
    gItemNew = -1; if (gNP == 1) gPS = PS_RUN;
}

static void updatePickups(float dt) {
    for (int i = 0; i < MAXP; i++) {
        Pick& p = gP[i]; if (!p.on) continue;
        p.t += dt;
        Sc sc(nearPlayer(p.x, p.y));
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
                case 3: if (p.val >= 10) gT10++; else gT1++; if (p.val >= 10) fxText(P.x, P.y - 30, "+10 Tickets", 0xc47bff, 0.6f); else fxText(P.x, P.y - 30, "+Ticket", 0xffd23f, 0.5f); sfxPlay(SFX_PICK); break;
                case 4:
                    for (int k = 0; k < MAXP; k++) if (gP[k].on && gP[k].kind <= 1) { gP[k].t = 30; }
                    fxText(P.x, P.y - 30, "¡Imán!", 0x80c0ff, 0.5f); sfxPlay(SFX_PICK); break;
                case 5: sfxPlay(SFX_RARE); itemOffer((int)p.val); break;
            }
        }
    }
}

static void updatePlayer(float dt, float jx, float jy) {
    float spd = P.spd * P.spdMul * (P.buffSpdT > 0 ? 1 + P.buffSpd : 1) * wxSpeed(pdex().t1, pdex().t2);
    if (gJ && spd > 130) spd = 130 + (spd - 130) * 0.25f;
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
    gBellT -= dt;
    if (gBellT <= 0) { gBellT = 0.5f; if (gBell > 0) { healPlayer(gBell); gBell = 0; } }
}

void playFireButton(int b) { gManualDown |= 1u << b; }
bool playIsActive(int b) { return inActive(b); }
int playGrp(int b) { return gMoves[b].grp; }
int playGroupSize(int b) { return gMoves[b].id < 0 ? 0 : grpSize(gMoves[b].grp); }
int playBonds() { return gBonds; }
static int bondGrowGrp() { for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0) { int n = grpSize(gMoves[b].grp); if (n > 1 && n < 4) return gMoves[b].grp; } return -1; }
int playBondNeed() {
    int loose = 0; for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0 && grpSize(gMoves[b].grp) == 1) loose++;
    if (bondGrowGrp() >= 0) return loose ? 1 : 0;
    return loose >= 2 ? 2 : 0;
}
bool playBondLoose(int b) { return gMoves[b].id >= 0 && grpSize(gMoves[b].grp) == 1; }
void playBondApply(const int* btns, int n) {
    int need = playBondNeed();
    if (!need || n < need) return;
    int tg = need == 1 ? bondGrowGrp() : gMoves[btns[0]].grp;
    for (int i = 0; i < n; i++) if (playBondLoose(btns[i])) gMoves[btns[i]].grp = (u8)tg;
    if (gNP > 1) for (int i = 0; i < n; i++) if (!playBondLoose(btns[i])) return;
    gBonds--; gActive = btns[0];
    for (int b = 0; b < 4; b++) if (inActive(b)) gMoves[b].cd = 0.2f;
    fxRing(P.x, P.y - 8, 8, 130, 0xff8ad8, 0.8f, 6);
    fxBurst(P.x, P.y - 10, 0xffb3e6, 30, 220);
    sfxPlay(SFX_RARE);
    char b[48]; snprintf(b, sizeof b, "¡Vínculo! %d movimientos a la vez", grpSize(tg)); banner(b, 2.6f);
    if (gNP == 1) gPS = PS_RUN;
}
void playBondSkip() { gBondAskN = nMoves(); if (gNP == 1) gPS = PS_RUN; }
int playWeather(float* left) { if (left) *left = gWx ? gWxDur - gWxT : 0; return wxLevel() > 0 ? gWx : 0; }
const char* weatherName(int k) { return WX_NAMES[k]; }
const char* weatherHint(int k) { return WX_HINT[k]; }
u32 weatherColor(int k) { return WX_COL[k]; }
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
    // pulsar un botón elige ese ataque (o grupo fusionado); sólo el activo se lanza
    for (int b = 0; b < 4; b++) {
        if (!((down & keys[b]) || (gManualDown & (1u << b))) || gMoves[b].id < 0) continue;
        if (!inActive(b)) {
            if (gItem == 1 && gActive >= 0 && gMoves[gActive].id >= 0) continue;
            gActive = b;
            for (int k = 0; k < 4; k++) if (inActive(k)) gMoves[k].cd = fminf(gMoves[k].cd, fmaxf(0.05f, gMoves[k].v[K_CD] * P.cdMul) * 0.35f);
            fxRing(P.x, P.y - 8, 6, 34, TYPE_RGB[MOVES[gMoves[b].id].type], 0.3f, 3);
            sfxPlay(SFX_UI);
        } else gActive = b;
    }
    if (gActive < 0 || gMoves[gActive].id < 0) { gActive = -1; for (int b = 0; b < 4; b++) if (gMoves[b].id >= 0) { gActive = b; break; } }
    for (int b = 0; b < 4; b++) {
        MoveInst& m = gMoves[b]; if (m.id < 0) continue;
        if (MOVES[m.id].kind == MK_ORBIT) continue;
        m.cd -= dt;
        if (!inActive(b)) { if (m.cd < 0) m.cd = 0; continue; }
        if (m.cd > 0) continue;
        bool pressed = false;
        if (needsTarget(MOVES[m.id].kind) && !pressed) {
            if (gTarget < 0 || distf(P.x, P.y, gE[gTarget].x, gE[gTarget].y) > reachOf(m)) { m.cd = 0.05f; continue; }
        } else if (!needsTarget(MOVES[m.id].kind) && !pressed) {
            // los de zona / mejora no se gastan si no hay nadie cerca
            int k = MOVES[m.id].kind;
            if (k != MK_TRAIL && k != MK_BUFF && gTarget < 0) { m.cd = 0.1f; continue; }
            if (k == MK_BUFF && (gTarget < 0 || distf(P.x, P.y, gE[gTarget].x, gE[gTarget].y) > 300)) { m.cd = 0.2f; continue; }
        }
        if (castMove(b)) {
            m.cd = fmaxf(0.05f, m.v[K_CD] * P.cdMul);
            if (gItem == 7 && MOVES[m.id].kind != MK_ORBIT && MOVES[m.id].kind != MK_TRAIL) P.hp = fmaxf(1, P.hp - fmaxf(1, P.maxHp * 0.01f));
        }
        else m.cd = 0.1f;
    }
    gManualDown = 0;
}

// ---------------------------------------------------------------- eventos: ladrón de monedas y grieta
static bool freeSpot(float x, float y) {
    int tx = (int)floorf(x / TS), ty = (int)floorf(y / TS);
    return !liquidTile(tx, ty) && propAt(tx, ty, nullptr) == PR_NONE;
}
static void ringPos(float minD, float maxD, float* ox, float* oy) {
    for (int i = 0; i < 14; i++) {
        float a = frand() * 6.283f, d = frange(minD, maxD);
        *ox = P.x + cosf(a) * d; *oy = P.y + sinf(a) * d;
        if (freeSpot(*ox, *oy)) return;
    }
}
static bool anyBoss() { for (int i = 0; i < MAXE; i++) if (gE[i].on && gE[i].boss) return true; return false; }

static void thiefSpawn() {
    bool gold = frand() < 0.25f && dexIndexOf(1000) >= 0 && sprHas(1000);
    int di = dexIndexOf(gold ? 1000 : 52);
    if (di < 0 || !sprHas(DEX_NUM[di])) return;
    Def d; memset(&d, 0, sizeof d); d.di = di; d.beh = B_THIEF;
    float x = P.x + 250, y = P.y; ringPos(230, 300, &x, &y);
    int s = spawnEnemy(d, x, y, false, false, gTime);
    if (s < 0) return;
    Enemy& e = gE[s];
    e.hp = e.maxHp = 60 * (1 + gTime / 95) * (gold ? 1.5f : 1);
    e.spd = 92; e.dmg = 0; e.xp = 0; e.st = gold ? 1 : 0; e.t = 0; e.t2 = 0;
    char b[48]; snprintf(b, sizeof b, "¡%s con monedas! ¡Atrápalo!", pname(di)); banner(b, 3.4f);
    sfxPlay(SFX_RARE);
    fxRing(x, y - 8, 6, 50, 0xffd23f, 0.5f, 3);
}
static void thiefLoot(Enemy& e) {
    bool gold = e.st == 1;
    fxBurst(e.x, e.y - 8, 0xffd23f, 16, 140);
    fxRing(e.x, e.y - 8, 6, 70, 0xffd23f, 0.5f, 4);
    sfxPlay(SFX_RARE);
    int n = gold ? 6 : 20;
    if (gold) { dropPick(3, e.x, e.y - 10, 10); fxText(e.x, e.y - 30, "+10 Tickets", 0xffd23f, 0.6f); }
    for (int i = 0; i < n; i++) dropPick(1, e.x + frange(-28, 28), e.y + frange(-20, 20), 5);
}

static void lostSpawn() {
    static short pool[DEX_N]; int n = 0;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].rarity <= 3 && !DEX[i].leg && DEX_NUM[i] < 1000 && sprHas(DEX_NUM[i])) pool[n++] = i;
    if (!n) return;
    float x = P.x + 250, y = P.y, tx = P.x - 250, ty = P.y;
    ringPos(220, 300, &x, &y);
    bool ok = false;
    for (int i = 0; i < 30 && !ok; i++) {
        float a = frand() * 6.283f, d = frange(700, 850);
        tx = x + cosf(a) * d; ty = y + sinf(a) * d * 0.85f;
        ok = freeSpot(tx, ty);
    }
    if (!ok) return;
    gLost = {true, false, false, pool[rnd() % n], 0, 0, x, y, tx, ty, 100, 0, 0, 0, 12};
    char b[56]; snprintf(b, sizeof b, "¡%s se ha perdido! Llévalo a la marca verde", pname(gLost.di)); banner(b, 3.6f);
    sfxPlay(SFX_RARE);
}
static void lostEnd(const char* msg) {
    char b[56]; snprintf(b, sizeof b, msg, pname(gLost.di)); banner(b, 3.0f);
    gLost.on = false; gLostT = frange(240, 300);
}
static void lostUpdate(float dt) {
    if (!gLost.on) return;
    gLost.t += dt; gLost.moving = false;
    if (gLost.flash > 0) gLost.flash -= dt;
    if (!gLost.follow) {
        for (int i = 0; i < gNP; i++) {
            Player& q = gC[i].p;
            if (!gC[i].dead && distf(q.x, q.y, gLost.x, gLost.y) < 12 + gLost.r + 18) {
                gLost.follow = true; gLost.who = i;
                char b[56]; snprintf(b, sizeof b, "¡%s te sigue! Llévalo a la marca verde", pname(gLost.di)); banner(b, 3.0f);
                sfxPlay(SFX_UI); break;
            }
        }
    } else {
        int w = gC[gLost.who].dead ? (gC[0].dead ? 1 : 0) : gLost.who;
        Player& q = gC[w].p;
        float d = distf(gLost.x, gLost.y, q.x, q.y), keep = 12 + gLost.r + 14;
        if (d > keep) {
            float sp = fminf(d - keep, fmaxf(120, q.spd * 1.15f) * dt), ux = (q.x - gLost.x) / d, uy = (q.y - gLost.y) / d;
            float nx = gLost.x + ux * sp, ny = gLost.y + uy * sp;
            if (freeSpot(nx, gLost.y)) gLost.x = nx;
            if (freeSpot(gLost.x, ny)) gLost.y = ny;
            gLost.moving = true;
            if (fabsf(ux) > fabsf(uy)) gLost.dir = ux > 0 ? 1 : 3; else gLost.dir = uy > 0 ? 0 : 2;
        }
        if (distf(gLost.x, gLost.y, gLost.tx, gLost.ty) < 56) {
            for (int i = 0; i < 12; i++) dropPick(1, gLost.tx + frange(-40, 40), gLost.ty + frange(-30, 30), 5);
            dropPick(3, gLost.tx, gLost.ty - 12, 1);
            for (int i = 0; i < gNP; i++) { Sc sc(i); if (!gC[i].dead) { healPlayer(P.maxHp * 0.5f); fxRing(P.x, P.y, 6, 70, 0x5fe08a, 0.5f, 3); } }
            fxBurst(gLost.tx, gLost.ty - 10, 0x7dffb0, 24, 180);
            sfxPlay(SFX_LEVEL);
            int di = gLost.di; char b[56];
            if (frand() < 0.2f && !gSave.owned[di]) { gSave.owned[di] = 1; snprintf(b, sizeof b, "¡%s se une a tu colección!", pname(di)); }
            else snprintf(b, sizeof b, "¡Has llevado a %s a casa! Te lo agradece", pname(di));
            banner(b, 3.4f);
            gLost.on = false; gLostT = frange(240, 300);
            return;
        }
    }
    if ((gLost.hitCd -= dt) <= 0) {
        float dmg = 0;
        for (int i = 0; i < MAXE; i++) {
            Enemy& e = gE[i];
            if (e.on && e.beh != B_THIEF && distf(e.x, e.y, gLost.x, gLost.y) < e.r + gLost.r) dmg += 4 + e.dmg * 0.12f;
        }
        if (dmg > 0) {
            gLost.hitCd = 0.5f; gLost.hp -= fminf(30, dmg); gLost.flash = 0.1f;
            fxBurst(gLost.x, gLost.y - 10, 0xff5f6d, 4, 60);
            if (gLost.hp <= 0) { lostEnd("¡%s se ha asustado y ha huido…!"); return; }
        }
    }
    if (gLost.t > 120) lostEnd("%s se ha cansado de esperar y se ha ido…");
}

static void riftOpen() {
    bool any = false;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].leg && sprHas(DEX_NUM[i])) { any = true; break; }
    if (!any) return;
    gPortalX = P.x + 450; gPortalY = P.y;
    ringPos(380, 560, &gPortalX, &gPortalY);
    gPortal = true; gPortalT = 45; gRiftMiss = 0;
    banner("¡Se abrió una grieta!", 3.2f); sfxPlay(SFX_BOSS); gShake = fmaxf(gShake, 0.4f);
}
static void riftEnter() {
    static short leg[DEX_N]; int n = 0;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].leg && sprHas(DEX_NUM[i])) leg[n++] = i;
    if (!n) { gPortal = false; return; }
    memcpy(sE, gE, sizeof gE); memcpy(sP, gP, sizeof gP); memcpy(sF, gF, sizeof gF);
    memset(gE, 0, sizeof gE); memset(gS, 0, sizeof gS); memset(gES, 0, sizeof gES); memset(gH, 0, sizeof gH);
    memset(gP, 0, sizeof gP); memset(gF, 0, sizeof gF);
    gWx = 0;
    gArena = true; gArenaDead = false; gArenaT = 0; gArenaEnd = 0; gPortal = false; gLost.on = false;
    gArenaX = gPortalX; gArenaY = gPortalY;
    for (int i = 0; i < gNP; i++) {
        Ctx& c = gC[i];
        gSavedX[i] = c.p.x; gSavedY[i] = c.p.y;
        c.target = -1; c.adead = false;
        if (c.dead) { c.dead = false; c.p.hp = c.p.maxHp * 0.3f; }
        c.p.x = gArenaX + (gNP > 1 ? (i ? 30 : -30) : 0); c.p.y = gArenaY + 160; c.p.vx = c.p.vy = 0; c.p.invuln = 1.5f;
    }    int di = leg[rnd() % n];
    Def d; memset(&d, 0, sizeof d);
    d.di = di; d.beh = B_CHASE; d.hp = 1; d.spd = 58; d.dmg = 1; d.xp = 0;
    int s = spawnEnemy(d, gArenaX, gArenaY - 120, true, false, 0);
    if (s >= 0) {
        Enemy& e = gE[s];
        e.legend = true; e.hp = e.maxHp = (5000 + 6 * gTime) * (gNP > 1 ? 1.8f : 1.0f);
        e.spd = 58; e.dmg = 45 + gTime * 0.05f; e.shotDmg = e.dmg * 0.55f; e.xp = 0; e.shotCd = 1.1f; e.range = 260;
    }
    char b[48]; snprintf(b, sizeof b, "¡%s te desafía!", pname(di)); banner(b, 3.4f);
    musicPlay(MUS_BOSS); sfxPlay(SFX_BOSS); gShake = fmaxf(gShake, 0.6f);
}
static void riftExit(bool won, bool dead) {
    memcpy(gE, sE, sizeof gE); memcpy(gP, sP, sizeof gP); memcpy(gF, sF, sizeof gF);
    memset(gS, 0, sizeof gS); memset(gES, 0, sizeof gES); memset(gH, 0, sizeof gH);
    gArena = false;
    for (int i = 0; i < gNP; i++) {
        Ctx& c = gC[i];
        c.target = -1;
        c.p.x = gSavedX[i]; c.p.y = gSavedY[i]; c.p.vx = c.p.vy = 0; c.p.invuln = 2.5f;
        if (won) { c.p.hp = fminf(c.p.maxHp, c.p.hp + c.p.maxHp * 0.3f); c.bonds++; c.bondAskN = -1; }
        else if (dead || c.adead) c.p.hp = c.p.maxHp * 0.35f;
        c.adead = false;
    }
    if (won) {
        gRifts++;
        banner("¡Grieta superada! ¡Vínculo!", 2.8f);
        fxRing(P.x, P.y - 8, 8, 90, 0xff8ad8, 0.7f, 5);
    }
    else banner("La grieta se cierra…", 2.8f);
    gRiftChk = 30;
    musicPlay(MUS_BATTLE);
}
static void riftWin(Enemy& e) {
    gSave.legends[e.di] = 1;
    for (int i = 0; i < MAXE; i++) gE[i].on = false;
    fxBurst(e.x, e.y - 10, 0xe0a0ff, 30, 190);
    fxRing(e.x, e.y - 10, 8, 130, 0xe0a0ff, 0.7f, 5);
    sfxPlay(SFX_BOSS); gShake = 0.8f;
    if (frand() < 0.5f) dropPick(3, e.x, e.y - 10, 10);
    for (int i = 0; i < 10; i++) dropPick(1, e.x + frange(-30, 30), e.y + frange(-20, 20), 8);
    for (int i = 0; i < MAXP; i++) if (gP[i].on) gP[i].t = 30;
    gArenaEnd = 3.5f;
    banner("¡Legendario derrotado!", 3.2f);
}
// ---------------------------------------------------------------- Sentencia de Arceus
static bool judgeStart() {
    gJArDi = -1;
    for (int i = 0; i < DEX_N; i++) if (DEX_NUM[i] == 493 && sprHas(493)) gJArDi = i;
    if (gJArDi < 0) return false;
    memset(gE, 0, sizeof gE); memset(gS, 0, sizeof gS); memset(gES, 0, sizeof gES); memset(gH, 0, sizeof gH);
    memset(gP, 0, sizeof gP); memset(gF, 0, sizeof gF);
    float best = 0; int n = gJNs < 30 ? gJNs : 30;
    float sum = 0; static float tmp[30];
    for (int i = 0; i < n; i++) tmp[i] = gJSamp[i];
    for (int i = 0; i < n; i++) for (int k = i + 1; k < n; k++) if (tmp[k] > tmp[i]) { float x = tmp[i]; tmp[i] = tmp[k]; tmp[k] = x; }
    int m = n < 6 ? n : 6;
    for (int i = 0; i < m; i++) sum += tmp[i];
    best = m ? sum / m : 0;
    gJBase = fmaxf(2000, best * 3);
    gWx = 0; gPortal = false; gLost.on = false;
    gArena = true; gArenaDead = false; gArenaT = 0; gArenaEnd = 0; ARENA_H = 560;
    gArenaX = P.x; gArenaY = P.y;
    for (int i = 0; i < gNP; i++) {
        Ctx& c = gC[i];
        c.target = -1; c.adead = false; c.dead = false;
        if (gNP > 1) { c.p.x = gArenaX + (i ? 30 : -30); c.p.y = gArenaY; c.p.vx = c.p.vy = 0; }
        c.p.invuln = 5; c.p.hp = c.p.maxHp;
    }
    gJ = 1; gJT = 0; gJN = 0; gJDowns = 0; gJBossT = 5; gJCast = 3; gJTouch = 0; gJLift = 700;
    gJX = gArenaX; gJY = gArenaY - 140; gJDir = 0; gJMoving = false;
    gSave.stat[SB_JUDGE]++;
    banner("LA SENTENCIA DE ARCEUS", 3.2f);
    musicPlay(MUS_BOSS); sfxPlay(SFX_BOSS); gShake = fmaxf(gShake, 0.8f);
    return true;
}
static void judgeSpawnLegend() {
    static short leg[DEX_N]; int n = 0;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].leg && DEX_NUM[i] != 493 && sprHas(DEX_NUM[i])) leg[n++] = i;
    if (!n) return;
    int di = leg[rnd() % n];
    float k = powf(2.0f, (float)(gJN < 100 ? gJN : 100));
    Def d; memset(&d, 0, sizeof d);
    d.di = di; d.hp = 1; d.spd = 60; d.dmg = 1;
    u8 t1 = DEX[di].t1, t2 = DEX[di].t2;
    bool rng = false;
    static const u8 R[] = {10, 3, 13, 17, 1, 2, 5, 14};
    for (u8 r : R) if (t1 == r || t2 == r) rng = true;
    d.beh = rng ? B_RANGED : B_CHARGER;
    int s = spawnEnemy(d, P.x, P.y, true, false, 0);
    if (s < 0) return;
    Enemy& e = gE[s];
    float ang = frand() * 6.2832f;
    e.x = clampf(gArenaX + cosf(ang) * (ARENA_H - 30), gArenaX - ARENA_H + 30, gArenaX + ARENA_H - 30);
    e.y = clampf(gArenaY + sinf(ang) * (ARENA_H - 30), gArenaY - ARENA_H + 30, gArenaY + ARENA_H - 30);
    e.judge = true; e.hp = e.maxHp = gJBase * k;
    e.dmg = (30 + gTime / 20) * k; e.shotDmg = (16 + gTime / 40) * k; e.xp = 500 + gTime * 1.2f;
    e.shotCd = 1.3f; e.range = 260;
    e.spd = fmaxf(clampf(48 + (baseSpd(DEX[di]) - 78) * 0.6f, 48, 105), P.spd * P.spdMul * 0.8f);
    gJN++;
}
static void judgeUpdate(float dt) {
    gJT += dt;
    if (gJ == 1) {
        gJLift = fmaxf(0, 700 * (1 - gJT / 3.2f));
        for (int i = 0; i < gNP; i++) gC[i].p.invuln = fmaxf(gC[i].p.invuln, 1);
        if (gJT >= 3.2f) { gJ = 2; gJT = 0; gJLift = 0; gShake = 0.6f; sfxPlay(SFX_BOSS); fxRing(gJX, gJY - 10, 8, 160, 0xffe070, 0.8f, 6); }
        return;
    }
    // Arceus persigue al jugador más cercano y cada vez va más rápido
    int tgt = nearPlayer(gJX, gJY); if (tgt < 0) tgt = 0;
    Ctx& tc = gC[tgt];
    float dx = tc.p.x - gJX, dy = tc.p.y - gJY, dl = sqrtf(dx * dx + dy * dy) + 0.001f;
    float sp = 52 + gJT * 0.15f + (gJT > 300 ? (gJT - 300) * 0.5f : 0);
    gJMoving = dl > 6;
    if (gJMoving) { gJX += dx / dl * sp * dt; gJY += dy / dl * sp * dt; gJDir = (u8)(fabsf(dx) > fabsf(dy) ? (dx > 0 ? 2 : 1) : (dy > 0 ? 0 : 3)); }
    float lo = ARENA_H - 20;
    gJX = clampf(gJX, gArenaX - lo, gArenaX + lo); gJY = clampf(gJY, gArenaY - lo, gArenaY + lo);
    gJTouch -= dt;
    if (gJTouch <= 0) {
        for (int i = 0; i < gNP; i++) {
            if (gC[i].dead || distf(gC[i].p.x, gC[i].p.y, gJX, gJY) >= 26) continue;
            Sc sc(i);
            gJTouch = 0.9f; P.invuln = 0;
            float pct = fminf(1, 0.4f + fmaxf(0, gJT - 420) / 180 * 0.6f);
            hurtPlayer(P.maxHp * pct, 0, -1, true);
            fxRing(P.x, P.y - 8, 6, 60, 0xffe070, 0.4f, 4);
        }
    }
    gJCast -= dt;
    if (gJCast <= 0) {
        gJCast = fmaxf(1.4f, 3.2f - gJT * 0.025f);
        float mh = 0; for (int i = 0; i < gNP; i++) if (!gC[i].dead) mh = fmaxf(mh, gC[i].p.maxHp);
        float dmg = mh * 0.25f; u32 gold = 0xffd860;
        gHazTru = true;
        switch (rnd() % 3) {
            case 0: {
                int c = 3 + (int)(gJT / 120); if (c > 8) c = 8;
                for (int pi = 0; pi < gNP; pi++) {
                    if (gC[pi].dead) continue;
                    for (int i = 0; i < c; i++) hazCircle(gC[pi].p.x + (i ? frange(-130, 130) : 0), gC[pi].p.y + (i ? frange(-100, 100) : 0), 42, 0.9f, dmg, gold);
                }
                break;
            }
            case 1: { float a = frand() * 6.2832f; for (int i = 0; i < 4; i++) hazLine(gJX, gJY - 8, a + i * 1.5708f, 700, 34, 0.9f, dmg, gold); break; }
            default: hazCircle(gJX, gJY, 130, 0.9f, dmg, gold); break;
        }
        gHazTru = false;
    }
    gJBossT -= dt;
    if (gJBossT <= 0) { gJBossT = gNP > 1 ? 4 : 5; judgeSpawnLegend(); }
    if (gNP == 1 && (P.hp <= 0 || gArenaDead)) { gPS = PS_OVER; sfxPlay(SFX_OVER); }
}

static void eventsUpdate(float dt) {
    if (gArena) {
        gArenaT += dt;
        float lo = ARENA_H - 10;
        for (int i = 0; i < gNP; i++) { Player& q = gC[i].p; q.x = clampf(q.x, gArenaX - lo, gArenaX + lo); q.y = clampf(q.y, gArenaY - lo, gArenaY + lo); }
        for (int i = 0; i < MAXE; i++) if (gE[i].on) {
            gE[i].x = clampf(gE[i].x, gArenaX - lo, gArenaX + lo); gE[i].y = clampf(gE[i].y, gArenaY - lo, gArenaY + lo);
        }
        if (gJ) { judgeUpdate(dt); return; }
        if (gArenaDead) riftExit(false, true);
        else if (gArenaEnd > 0) { gArenaEnd -= dt; if (gArenaEnd <= 0) riftExit(true, false); }
        else if (gArenaT > 120) riftExit(false, false);
        return;
    }
    bool boss = anyBoss();
    // clima
    if (gWx) {
        gWxT += dt;
        if (gWxT >= gWxDur) gWx = 0;
    } else if (gTime > 120) {
        gWxChk -= dt;
        if (gWxChk <= 0) {
            gWxChk = 60;
            if (frand() < 0.18f) {
                static const float W[3][6] = {{0, 1.5f, 3, 0.5f, 0.5f, 2}, {0, 1, 1, 1, 2.5f, 3}, {0, 3, 0, 3, 0, 1}};
                const float* w = W[gSet % 3]; float tot = 0; for (int k = 1; k < 6; k++) tot += w[k];
                float r = frand() * tot; int k = 1;
                for (; k < 5; k++) { r -= w[k]; if (r <= 0) break; }
                gWx = k; gWxT = 0; gWxDur = frange(55, 75);
                char b[48]; snprintf(b, sizeof b, "%s", WX_NAMES[k]); banner(b, 3.0f);
                sfxPlay(SFX_UI);
            }
        }
    }
    gWxChip -= dt;
    if (gWxChip <= 0) {
        gWxChip = 2;
        if (wxLevel() > 0.5f) {
            for (int pi = 0; pi < gNP; pi++) {
                if (gC[pi].dead) continue;
                Sc sc(pi);
                if (!wxHurts(pdex().t1, pdex().t2)) continue;
                float d = fmaxf(1, P.maxHp * 0.012f);
                if (P.hp > d + 1) { P.hp -= d; char b[12]; snprintf(b, sizeof b, "-%d", (int)d); fxText(P.x, P.y - 28, b, WX_COL[gWx], 0.5f); }
            }
            for (int i = 0; i < MAXE; i++) {
                Enemy& e = gE[i]; if (!e.on || e.boss || e.beh == B_THIEF || !wxHurts(DEX[e.di].t1, DEX[e.di].t2)) continue;
                e.hp -= e.maxHp * 0.02f + 1; e.flash = 0.05f;
                if (e.hp <= 0) killEnemy(e);
            }
        }
    }
    // vínculo pendiente tras vencer a un legendario
    if (gNP == 1 && gBonds > 0 && gArenaEnd <= 0 && gPS == PS_RUN && nMoves() > gBondAskN && playBondNeed()) gPS = PS_BOND;
    gThiefT -= dt;
    if (gThiefT <= 0) {
        if (boss) gThiefT = 8;
        else { thiefSpawn(); gThiefN++; gThiefT = gThiefN < 2 ? frange(240, 360) : 1e9f; }
    }
    if (gLost.on) lostUpdate(dt);
    else {
        gLostT -= dt;
        if (gLostT <= 0) { if (boss || gPortal) gLostT = 8; else lostSpawn(); if (!gLost.on && gLostT <= 0) gLostT = frange(60, 120); }
    }
    if (gPortal) {
        gPortalT -= dt;
        if (gPortalT <= 0) { gPortal = false; banner("La grieta se cerró…", 2.5f); }
        else {
            for (int i = 0; i < gNP; i++) if (!gC[i].dead && distf(gC[i].p.x, gC[i].p.y, gPortalX, gPortalY) < 30) { riftEnter(); break; }
        }
    } else if (gTime >= 75 && gTime <= WIN_TIME - 120 && !boss) {
        gRiftChk -= dt;
        if (gRiftChk <= 0) {
            gRiftChk = 30;
            if (frand() < 0.2f * (1 + gRiftMiss)) riftOpen(); else gRiftMiss++;
        }
    }
}

static void fxStep(float dt) {
    gMs = osGetTime();
    for (int i = 0; i < MAXFX; i++) {
        Fx& f = gFx[i]; if (!f.on) continue;
        f.t += dt; f.x += f.vx * dt; f.y += f.vy * dt;
        if (f.kind == FX_PART) { f.vx *= expf(-4 * dt); f.vy *= expf(-4 * dt); }
        if (f.t >= f.life) f.on = false;
    }
    if (gBannerT > 0) gBannerT -= dt;
    if (gShake > 0) gShake -= dt * 2;
}
static void biomeStep() {
    int setNow = ((int)(gTime / 300)) % 3;
    static int lastBiome = -1;
    if (setNow != lastBiome) {
        if (lastBiome >= 0) { gSet = (gChar % 3 + setNow) % 3; tilesLoad(gSet); banner(TILESET_NAMES[gSet], 3.0f); }
        lastBiome = setNow;
    }
    if (gTime < 0.05f) lastBiome = -1;
}
static void bossMusicStep() {
    bool boss = false; for (int i = 0; i < MAXE; i++) if (gE[i].on && gE[i].boss) boss = true;
    static bool wasBoss; if (wasBoss && !boss) musicPlay(MUS_BATTLE); wasBoss = boss;
}

void playUpdate(float dt, u32 down, u32 held, int jx, int jy) {
    (void)held;
    fxStep(dt);
    if (gPS != PS_RUN) return;
    gTime += dt;
    if (gTime >= WIN_TIME && !gJ && !gArena && gArenaEnd <= 0) {
        if (judgeStart()) return;
        gPS = PS_WIN; sfxPlay(SFX_LEVEL); return;
    }
    if (!gJ) {
        gJSecT += dt;
        if (gJSecT >= 1) {
            gJSecT = 0; float b = 0;
            for (int i = 0; i < MAXE; i++) { if (gE[i].on && gE[i].took > b) b = gE[i].took; gE[i].took = 0; }
            gJSamp[gJNs % 30] = b; gJNs++;
        }
    }

    biomeStep();

    updatePlayer(dt, jx / 100.0f, jy / 100.0f);
    updateMoves(dt, down);
    orbitsUpdate(dt);
    orbitsCool(dt);
    if (!gArena) spawnWave(dt);
    updateEnemies(dt);
    updateShots(dt);
    updateFields(dt);
    updateHazards(dt);
    updatePickups(dt);
    levelUpCheck();
    eventsUpdate(dt);
    bossMusicStep();
}

// un paso fijo del cooperativo: las dos consolas lo ejecutan con las mismas entradas
void playCoopTick(float dt, const CoopIn* in) {
    if (gPS != PS_RUN) return;
    for (int i = 0; i < 2; i++) {
        Sc sc(i);
        u16 cmd = in[i].cmd;
        if (cmd & 0x8000) {
            Card c; memset(&c, 0, sizeof c); c.kind = (cmd >> 8) & 3; c.arg = cmd & 0xff;
            if (gCur->pend > 0) playApplyCard(c);
        } else if (cmd & 0x4000) {
            if (gItemNew >= 0) playItemChoose(cmd & 1);
        } else if ((cmd & 0x2000) && gCur->bondWait) {
            int b[4], n = 0;
            for (int k = 0; k < 4; k++) if (cmd >> k & 1) b[n++] = k;
            int need = playBondNeed();
            if (need && n >= need) playBondApply(b, n); else playBondSkip();
            gCur->bondWait = false;
        }
    }
    // el vínculo pausa la partida hasta que los dos hayan elegido
    if (gC[0].bondWait || gC[1].bondWait) return;
    gTickN++;
    gTime += dt;
    int lead0 = gC[0].dead ? 1 : 0;
    if (gTime >= WIN_TIME && !gJ && !gArena && gArenaEnd <= 0) {
        bool started; { Sc sc(lead0); started = judgeStart(); }
        if (started) return;
        gPS = PS_WIN; sfxPlay(SFX_LEVEL); return;
    }
    if (!gJ) {
        gJSecT += dt;
        if (gJSecT >= 1) {
            gJSecT = 0; float b = 0;
            for (int i = 0; i < MAXE; i++) { if (gE[i].on && gE[i].took > b) b = gE[i].took; gE[i].took = 0; }
            gJSamp[gJNs % 30] = b; gJNs++;
        }
    }
    biomeStep();
    for (int i = 0; i < 2; i++) {
        Sc sc(i);
        if (gCur->dead) continue;
        if (gCur->pend > 0 || gItemNew >= 0) P.invuln = fmaxf(P.invuln, 0.3f);
        gManualDown |= in[i].btn & 15;
        updatePlayer(dt, in[i].jx / 100.0f, in[i].jy / 100.0f);
        updateMoves(dt, 0);
        orbitsUpdate(dt);
    }
    orbitsCool(dt);
    int lead = (gTickN & 1);
    if (gC[lead].dead) lead ^= 1;
    if (!gArena) { Sc sc(lead); spawnWave(dt); }
    updateEnemies(dt);
    updateShots(dt);
    updateFields(dt);
    updateHazards(dt);
    updatePickups(dt);
    for (int i = 0; i < 2; i++) { Sc sc(i); levelUpCheck(); }
    lead = gC[0].dead ? 1 : 0;
    { Sc sc(lead); eventsUpdate(dt); }
    for (int i = 0; i < 2; i++) {
        Sc sc(i);
        if (!gCur->dead && !gArena && gArenaEnd <= 0 && gBonds > 0 && nMoves() > gBondAskN && playBondNeed()) gCur->bondWait = true;
    }
    bossMusicStep();
}
int playCoopBond() { return (gC[gLoc].bondWait ? 1 : 0) | (gC[gLoc ^ 1].bondWait ? 2 : 0); }
void playCoopFrame(float dt) { fxStep(dt); }
u8 playCoopTakeBtn() { u8 b = (u8)(gC[gLoc].manualDown & 15); gC[gLoc].manualDown = 0; return b; }
u32 playCoopChecksum() {
    u32 h = 2166136261u;
    auto mix = [&](u32 v) { h = (h ^ v) * 16777619u; };
    mix(gTickN); mix(rngGet()); mix((u32)(gTime * 1000));
    for (int i = 0; i < 2; i++) { mix((u32)(int)(gC[i].p.x * 8)); mix((u32)(int)(gC[i].p.y * 8)); mix((u32)(int)(gC[i].p.hp * 8)); mix(gC[i].p.level); }
    int n = 0; for (int i = 0; i < MAXE; i++) if (gE[i].on) n++;
    mix(n); mix(gKills); mix(gArena); mix(gJ); mix(gC[0].bondWait | gC[1].bondWait << 1);
    return h;
}
int playCoopPending() { return gC[gLoc].pend; }
bool playCoopDead() { return gC[gLoc].dead; }
void playCoopPartner(float* x, float* y, float* hpFrac, bool* dead) {
    const Ctx& o = gC[gLoc ^ 1];
    *x = o.p.x; *y = o.p.y; *hpFrac = clampf(o.p.hp / o.p.maxHp, 0, 1); *dead = o.dead;
}
int playCoopPartnerDi() { return gC[gLoc ^ 1].p.di; }
bool playCoopActive() { return gNP > 1; }

// ---------------------------------------------------------------- reinicio
static void resetWorld(int charIdx) {
    memset(gE, 0, sizeof gE); memset(gS, 0, sizeof gS); memset(gES, 0, sizeof gES); memset(gH, 0, sizeof gH);
    memset(gP, 0, sizeof gP); memset(gF, 0, sizeof gF); memset(gFx, 0, sizeof gFx);
    gNBroken = 0; gTime = 0; gSpawnAcc = 0; gSurgeT = 32; gKills = 0; gBossesDown = 0; gCoins = 0; gT1 = gT10 = 0;
    memset(gKillsType, 0, sizeof gKillsType); gChests = gEvolves = gRifts = 0;
    gNextBoss = 0; gNextId = 0; gPS = PS_RUN; gShake = 0; gBannerT = 0; gTickN = 0;
    gArena = gArenaDead = gPortal = false; gThiefN = 0; gThiefT = frange(120, 240); gLost.on = false; gLostT = frange(150, 210); gRiftChk = 30; gRiftMiss = 0;
    gJ = 0; ARENA_H = 320; gJNs = 0; gJSecT = 0; gHazTru = false;
    gWx = 0; gWxChk = 60; gWxChip = 2;
    gChar = charIdx; gSet = charIdx % 3;
}
// jugador nuevo: estadísticas de su Pokémon + sus mejoras permanentes
static void ctxInit(int ci, int di, const u8* perm, const int* startMoves, int nStart, bool shiny) {
    Sc sc(ci);
    memset(gCur, 0, sizeof(Ctx));
    gActive = -1; gBondAskN = -1; gItem = gItemNew = -1; gSashT = -999;
    gCur->shiny = shiny;
    P.di = di;
    const DexE& p = DEX[di];
    int lv[NPERM]; for (int i = 0; i < NPERM; i++) lv[i] = perm[i];
    P.maxHp = p.hp + lv[PU_HP] * 8; P.hp = P.maxHp; P.spd = p.spd * 0.9f;
    P.atkMul = 1 + lv[PU_ATK] * 0.04f; P.spdMul = 1 + lv[PU_SPD] * 0.03f; P.cdMul = 1 - lv[PU_CD] * 0.03f;
    P.dmgReduce = lv[PU_DEF] * 0.02f; P.regen = lv[PU_REGEN] * 0.2f; P.magnet = 78 * (1 + lv[PU_MAGNET] * 0.12f);
    P.xpMul = 1 + lv[PU_XP] * 0.05f; P.coinMul = 1 + lv[PU_COINS] * 0.08f; P.crit = lv[PU_CRIT] * 0.03f;
    P.level = 1; P.xpNeed = xpFor(1); P.rerolls = 0; P.dir = 0;
    gRerollsLeft = 1 + lv[PU_REROLL];
    for (int b = 0; b < 4; b++) { gMoves[b].id = -1; gMoves[b].cd = 0; gMoves[b].grp = 0; }
    for (int i = 0; i < nStart && i < 4; i++) slotPlace(startMoves[i]);
    gAimX = 0; gAimY = 1; gTarget = -1;
}
static void finishReset() {
    rollRun();
    tilesLoad(gSet);
    gTierNow = 0;
    banner(TILESET_NAMES[gSet], 3.0f);
}
void playReset(int charIdx, const int* startMoves, int nStart) {
    gNP = 1; gLoc = 0; gCur = &gC[0]; gCi = 0; gMovesL = gC[0].moves;
    memset(gC, 0, sizeof gC);
    resetWorld(charIdx);
    ctxInit(0, charIdx, gSave.pupg[charIdx], startMoves, nStart, gSave.shinyOn[charIdx] && gSave.shiny[charIdx]);
    finishReset();
}
// cooperativo: el anfitrión (0) define personaje/mundo; todo se genera con la misma semilla en las dos consolas
void playResetCoop(int me, const CoopHello* h, u32 seed) {
    gNP = 2; gLoc = me; gCur = &gC[me]; gCi = me; gMovesL = gC[me].moves;
    memset(gC, 0, sizeof gC);
    rngSet(seed);
    resetWorld(h[0].di);
    for (int i = 0; i < 2; i++) {
        int sm[2] = {h[i].start[0], h[i].start[1]};
        ctxInit(i, h[i].di, h[i].perm, sm, h[i].nStart, h[i].shiny != 0);
    }
    { Sc sc(0); finishReset(); }
    gC[1].p.x = gC[0].p.x + 26; gC[1].p.y = gC[0].p.y;
    gCur = &gC[me]; gCi = me;
}

PlayState playState() { return gPS; }
void playSetState(PlayState s) { gPS = s; }
RunStats playStats() {
    RunStats r;
    r.time = gTime; r.kills = gKills; r.level = P.level; r.bosses = gBossesDown; r.t1 = gT1 + (int)(gTime / 300); r.t10 = gT10; r.won = gPS == PS_WIN || gJ > 0; r.jdowns = gJDowns;
    float base = floorf(gTime / 5) + floorf(gKills * 0.25f) + gBossesDown * 80 + gCoins;
    r.coins = (int)roundf(base * P.coinMul);
    return r;
}
float playHpFrac() { return clampf(P.hp / P.maxHp, 0, 1); }
MissionRun playMissionStats() {
    MissionRun r;
    memset(&r, 0, sizeof r);
    r.kills = gKills; r.bosses = gBossesDown; r.chests = gChests; r.evolves = gEvolves; r.rifts = gRifts;
    r.coins = gCoins; r.level = P.level; r.minutes = gTime / 60;
    r.ct1 = DEX[P.di].t1; r.ct2 = DEX[P.di].t2;
    memcpy(r.killsByType, gKillsType, sizeof r.killsByType);
    return r;
}
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
static u32 gUiRng = 88172645u;      // las cartas se sortean con su propio RNG para no desincronizar el cooperativo
void playBuildCards(CardSet& cs) {
    u32 svR = rngGet();
    if (gNP > 1) rngSet(gUiRng);
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
    if (gNP > 1) { gUiRng = rngGet(); rngSet(svR); }
}
bool playReroll(CardSet& cs) {
    if (gRerollsLeft <= 0) return false;
    gRerollsLeft--; playBuildCards(cs); return true;
}
void playApplyCard(const Card& c) {
    if (c.kind == 0) slotPlace(c.arg);
    else if (c.kind == 1) { MoveInst& m = gMoves[c.arg]; if (m.lvl < 5) { m.lvl++; moveRecompute(m); if (m.lvl == 5) gEvolves++; } }
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
    if (gNP == 1) gPS = PS_RUN;
    else if (gCur->pend > 0) gCur->pend--;
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
                float x2 = f.x2 - cx, y2 = f.y2 - cy, mx = (x + x2) / 2 + vfrange(-8, 8), my = (y + y2) / 2 + vfrange(-8, 8);
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

static void edgeArrow(float wx, float wy, float cx, float cy, u32 col) {
    float sx = wx - cx, sy = wy - cy;
    if (sx > 0 && sx < TOP_W && sy > 14 && sy < TOP_H) return;
    float dx = sx - TOP_W / 2, dy = sy - TOP_H / 2, l = sqrtf(dx * dx + dy * dy);
    if (l < 1) return;
    float t = fminf((TOP_W / 2 - 14) / fmaxf(fabsf(dx), 0.01f), (TOP_H / 2 - 24) / fmaxf(fabsf(dy), 0.01f));
    float ux = dx / l, uy = dy / l, ax = TOP_W / 2 + dx * t, ay = TOP_H / 2 + dy * t;
    C2D_DrawTriangle(ax + ux * 9, ay + uy * 9, col, ax - uy * 6 - ux * 5, ay + ux * 6 - uy * 5, col, ax + uy * 6 - ux * 5, ay - ux * 6 - uy * 5, col, 0.78f);
}
static void drawWeather() {
    float lv = wxLevel();
    if (!gWx || lv <= 0) return;
    static const u8 TINT[6][4] = {{0}, {255, 190, 90, 18}, {50, 90, 170, 24}, {200, 160, 90, 24}, {210, 230, 255, 20}, {190, 195, 210, 32}};
    C2D_DrawRectSolid(0, 0, 0.7f, TOP_W, TOP_H, COL(TINT[gWx][0], TINT[gWx][1], TINT[gWx][2], (int)(TINT[gWx][3] * lv)));
    int n = (int)((gWx == 2 ? 46 : gWx == 4 ? 34 : gWx == 3 ? 30 : gWx == 1 ? 10 : 0) * lv);
    float T0 = gMs * 0.001f;
    for (int i = 0; i < n; i++) {
        u32 h = hash2(i, 7, 99);
        float sx = (h & 1023) / 1023.0f * TOP_W, sy = ((h >> 10) & 1023) / 1023.0f * TOP_H, ph = ((h >> 20) & 255) / 255.0f;
        float x, y;
        if (gWx == 2) { x = fmodf(sx - 120 * T0 + 4000, TOP_W); y = fmodf(sy + 520 * T0, TOP_H); C2D_DrawLine(x, y, COL(200, 220, 255, 150), x - 3, y - 9, COL(200, 220, 255, 0), 1, 0.71f); }
        else if (gWx == 4) { x = fmodf(sx + sinf(T0 + ph * 6) * 14 + 4000, TOP_W); y = fmodf(sy + 55 * T0, TOP_H); C2D_DrawRectSolid(x, y, 0.71f, 2, 2, COL(255, 255, 255, 190)); }
        else if (gWx == 3) { x = fmodf(sx - 420 * T0 + 8000, TOP_W); y = fmodf(sy + 30 * T0, TOP_H); C2D_DrawRectSolid(x, y, 0.71f, 8, 1, COL(232, 207, 143, 120)); }
        else { x = sx; y = fmodf(sy - 20 * T0 + 4000, TOP_H); C2D_DrawRectSolid(x, y, 0.71f, 2, 2, COL(255, 241, 176, (int)(60 + 60 * sinf(T0 * 2 + ph * 6)))); }
    }
}
static void drawEvents(float cx, float cy) {
    drawWeather();
    if (gPortal) {
        float x = gPortalX - cx, y = gPortalY - cy, p = 0.5f + 0.5f * sinf(gMs * 0.006f);
        circle(x, y, 20 + 3 * p, COL(40, 0, 70, 200), 0.42f);
        ringDraw(x, y, 22 + 4 * p, 3, COL(190, 90, 255, 255), 0.43f);
        ringDraw(x, y, 12 + 3 * (1 - p), 2, COL(235, 190, 255, 255), 0.44f);
        edgeArrow(gPortalX, gPortalY, cx, cy, COL(190, 90, 255, 255));
    }
    for (int i = 0; i < MAXE; i++) if (gE[i].on && gE[i].beh == B_THIEF) edgeArrow(gE[i].x, gE[i].y, cx, cy, COL(255, 215, 60, 255));
    if (gLost.on && !gArena) {
        float p = 0.5f + 0.5f * sinf(gMs * 0.006f), mx = gLost.tx - cx, my = gLost.ty - cy;
        circle(mx, my, 56, COL(40, 200, 110, 50), 0.41f);
        ringDraw(mx, my, 56, 2, COL(125, 255, 176, (int)(150 + 100 * p)), 0.43f);
        ringDraw(mx, my, 24 + 4 * p, 2, COL(125, 255, 176, 255), 0.44f);
        float x = gLost.x - cx, y = gLost.y - cy;
        C2D_DrawEllipseSolid(x - gLost.r, y - gLost.r * 0.35f, 0.4f, gLost.r * 2, gLost.r * 0.7f, COL(0, 0, 0, 80));
        C2D_ImageTint tint; bool tn = gLost.flash > 0;
        if (tn) C2D_PlainImageTint(&tint, COL(255, 255, 255, 255), 0.85f);
        sprDraw(DEX_NUM[gLost.di], gLost.dir, gMs, gLost.moving, x, y, tn ? &tint : nullptr, 1.0f);
        if (gLost.hp < 100) {
            C2D_DrawRectSolid(x - 14, y - 40, 0.7f, 28, 3, COL(0, 0, 0, 180));
            C2D_DrawRectSolid(x - 14, y - 40, 0.71f, 28 * gLost.hp / 100, 3, COL(95, 224, 138, 255));
        }
        if (!gLost.follow) ringDraw(x, y - 8, 22, 1, COL(125, 255, 176, 200), 0.6f);
        edgeArrow(gLost.follow ? gLost.tx : gLost.x, gLost.follow ? gLost.ty : gLost.y, cx, cy, COL(125, 255, 176, 255));
    }
    if (!gArena) return;
    float aL = gArenaX - ARENA_H - cx, aR = gArenaX + ARENA_H - cx, aT = gArenaY - ARENA_H - cy, aB = gArenaY + ARENA_H - cy;
    u32 dark = COL(12, 0, 28, 235);
    if (aT > 0) C2D_DrawRectSolid(0, 0, 0.75f, TOP_W, fminf(aT, TOP_H), dark);
    if (aB < TOP_H) C2D_DrawRectSolid(0, fmaxf(aB, 0), 0.75f, TOP_W, TOP_H - fmaxf(aB, 0), dark);
    float y0 = fmaxf(aT, 0), y1 = fminf(aB, TOP_H);
    if (y1 > y0) {
        if (aL > 0) C2D_DrawRectSolid(0, y0, 0.75f, fminf(aL, TOP_W), y1 - y0, dark);
        if (aR < TOP_W) C2D_DrawRectSolid(fmaxf(aR, 0), y0, 0.75f, TOP_W - fmaxf(aR, 0), y1 - y0, dark);
    }
    u32 pc = gJ ? COL(255, 220, 90, 255) : COL(190, 90, 255, 255);
    C2D_DrawRectSolid(aL - 2, aT - 2, 0.76f, aR - aL + 4, 3, pc); C2D_DrawRectSolid(aL - 2, aB - 1, 0.76f, aR - aL + 4, 3, pc);
    C2D_DrawRectSolid(aL - 2, aT - 2, 0.76f, 3, aB - aT + 4, pc); C2D_DrawRectSolid(aR - 1, aT - 2, 0.76f, 3, aB - aT + 4, pc);
    if (gJ) {
        float ax = gJX - cx, ay = gJY - cy - gJLift;
        circle(ax, gJY - cy + 4, 20, COL(0, 0, 0, 90), 0.4f);
        if (gJ == 1) C2D_DrawRectSolid(ax - 14, fmaxf(0, ay - 40), 0.5f, 28, fmaxf(0, gJY - cy - (ay - 40)), COL(255, 240, 160, 110));
        ringDraw(ax, ay - 12, 30 + 3 * sinf(gMs * 0.006f), 3, COL(255, 220, 90, 200), 0.49f);
        sprDraw(493, gJDir, gMs, gJMoving, ax, ay, nullptr, 1.5f);
        if (gJ == 1) {
            C2D_DrawRectSolid(0, 0, 0.77f, TOP_W, TOP_H, COL(0, 0, 0, (int)(160 * (1 - gJT / 3.2f))));
            text("LA SENTENCIA DE ARCEUS", TOP_W / 2 - 78, TOP_H / 2 - 50, 0.7f, COL(255, 230, 120, 255));
        } else {
            edgeArrow(gJX, gJY, cx, cy, COL(255, 220, 90, 255));
            char jb[40]; snprintf(jb, sizeof jb, "Sentencia: %d legendarios", gJDowns);
            text(jb, TOP_W - 150, 12, 0.5f, COL(255, 230, 140, 255));
        }
        return;
    }
    char b[24]; snprintf(b, sizeof b, "%d s", (int)fmaxf(0, 120 - gArenaT));
    if (gArenaEnd <= 0) text(b, TOP_W - 40, 12, 0.5f, COL(220, 170, 255, 255));
}

void playDraw(u64 ms) {
    gMs = ms;
    float shx = gShake > 0 ? vfrange(-1, 1) * gShake * 6 : 0, shy = gShake > 0 ? vfrange(-1, 1) * gShake * 6 : 0;
    int camI = gNP > 1 && gC[gLoc].dead ? (gLoc ^ 1) : gLoc;
    const Player& CP = gC[camI].p;
    float cx = floorf(CP.x - TOP_W / 2 + shx), cy = floorf(CP.y - 10 - TOP_H / 2 + shy);
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
    for (int i = 0; i < MAXE && n < 296; i++) if (gE[i].on && fabsf(gE[i].x - CP.x) < 280 && fabsf(gE[i].y - CP.y) < 200) gDI[n++] = {gE[i].y, 1, (short)i};
    for (int i = 0; i < gNP; i++) if (!gC[i].dead) gDI[n++] = {gC[i].p.y, 2, (short)i};
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
            else if (e.beh == B_THIEF && e.st == 1) { C2D_PlainImageTint(&tint, COL(255, 215, 60, 255), 0.4f); tinted = true; }
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
            const Ctx& pc = gC[di.idx]; const Player& PP = pc.p;
            float x = PP.x - cx, y = PP.y - cy;
            C2D_DrawEllipseSolid(x - 10, y - 4, 0.4f, 20, 8, COL(0, 0, 0, 90));
            if (PP.invuln <= 0 || ((int)(gTime * 14) & 1)) {
                C2D_ImageTint tint; bool t = false;
                if (PP.flash > 0) { C2D_PlainImageTint(&tint, COL(255, 80, 80, 255), 0.7f); t = true; }
                sprDraw(DEX_NUM[PP.di], PP.dir, gMs, PP.moving, x, y, t ? &tint : nullptr, 1.0f, pc.shiny);
            }
            C2D_DrawRectSolid(x - 15, y - 4, 0.8f, 30, 4, COL(0, 0, 0, 200));
            C2D_DrawRectSolid(x - 14, y - 3, 0.85f, 28 * clampf(PP.hp / PP.maxHp, 0, 1), 2, di.idx == gLoc ? COL(90, 230, 90, 255) : COL(90, 170, 255, 255));
        }
    }
    for (int pi = 0; pi < gNP; pi++) {
    if (gC[pi].dead) continue;
    Sc sc(pi);
    for (int b = 0; b < 4; b++) {
        MoveInst& m = gMoves[b]; if (m.id < 0 || MOVES[m.id].kind != MK_ORBIT || !inActive(b)) continue;
        int cnt = (int)fmaxf(1, m.v[K_COUNT]); float rad = m.v[K_RADIUS], sz = m.v[K_SIZE] > 0 ? m.v[K_SIZE] : 8; u32 rgb = TYPE_RGB[MOVES[m.id].type];
        for (int i = 0; i < cnt; i++) {
            float a = P.orbA[b] + (float)i / cnt * 6.283f;
            float ox = P.x - cx + cosf(a) * rad, oy = P.y - cy - 8 + sinf(a) * rad * 0.85f;
            circle(ox, oy, sz + 3, rgbA(darken(rgb, 0.35f), 255), 0.6f); circle(ox, oy, sz, rgbA(lighten(rgb, 0.15f), 255), 0.61f); circle(ox, oy, sz * 0.5f, rgbA(0xffffff, 255), 0.62f);
        }
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
            case 3: if (p.val >= 10) icon(IC_TICKET10, x - 12, y - 12, 0.75f); else icon(IC_TICKET, x - 8, y - 8, 0.5f); break;
            case 4: circle(x, y, 6, COL(60, 90, 230, 255), 0.45f); circle(x, y, 3, COL(230, 60, 60, 255), 0.46f); break;
            case 5: C2D_DrawRectSolid(x - 7, y - 7, 0.45f, 14, 14, COL(255, 255, 255, 255)); C2D_DrawRectSolid(x - 6, y - 6, 0.46f, 12, 12, COL(255, 120, 200, 255)); C2D_DrawRectSolid(x - 2, y - 2, 0.47f, 4, 4, COL(255, 230, 90, 255)); break;
        }
    }
    drawFx(cx, cy, true);
    drawEvents(cx, cy);

    // HUD superior mínimo
    float bx = TOP_W / 2;
    char b[48];
    C2D_DrawRectSolid(0, 0, 0.8f, TOP_W, 14, COL(0, 0, 0, 120));
    snprintf(b, sizeof b, "Nv %d", P.level); text(b, 4, -2, 0.45f, COL(255, 255, 255, 255));
    int sec = (int)gTime; snprintf(b, sizeof b, "%02d:%02d", sec / 60, sec % 60); text(b, bx, -2, 0.45f, COL(255, 255, 255, 255), true);
    snprintf(b, sizeof b, "KO %d", gKills); text(b, TOP_W - 52, -2, 0.45f, COL(255, 230, 120, 255));
    if (gBannerT > 0) text(gBanner, bx, 30, strlen(gBanner) > 30 ? 0.5f : 0.7f, COL(255, 240, 160, 255), true);
    if (int wk = playWeather(nullptr)) { snprintf(b, sizeof b, "%s", weatherName(wk)); text(b, TOP_W - 4, 14, 0.4f, rgbA(weatherColor(wk), 255)); }
}
