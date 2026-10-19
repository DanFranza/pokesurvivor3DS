// PokéSurvivor 3DS — juego nativo (Old 3DS XL compatible).
// Pantalla superior: mundo. Pantalla táctil: joystick, HUD, asignación de ataques a X/Y/B/A y cartas.
#include <3ds.h>
#include <citro2d.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "atlas_t3x.h"
#include "sprites.h"

// ---------- límites de memoria (todo estático) ----------
#define MAX_ENEMIES 110
#define MAX_SHOTS   64
#define MAX_GEMS    160
#define MAX_ESHOTS  80
#define MAX_FX      8
static const float TOP_W = 400, TOP_H = 240;
static const float WIN_TIME = 600;      // sobrevivir 10 min = victoria
static const float BOSS_EVERY = 120;

// ---------- utilidades ----------
static u32 rngState = 2463534242u;
static u32 rnd() { rngState ^= rngState << 13; rngState ^= rngState >> 17; rngState ^= rngState << 5; return rngState; }
static float frand() { return (rnd() & 0xFFFFFF) / 16777216.0f; }
static float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
static bool inRect(float px, float py, float x, float y, float w, float h) { return px >= x && px <= x + w && py >= y && py <= y + h; }
#define COL(r, g, b, a) C2D_Color32(r, g, b, a)

// ---------- sprites ----------
static C2D_SpriteSheet gSheet;
static Tex3DS_SubTexture gSub[SPR_COUNT][4][SPR_MAXF];
static C2D_Image gImg[SPR_COUNT][4][SPR_MAXF];

static void initSprites() {
    gSheet = C2D_SpriteSheetLoadFromMem(atlas_t3x, atlas_t3x_size);
    C2D_Image base = C2D_SpriteSheetGetImage(gSheet, 0);
    for (int s = 0; s < SPR_COUNT; s++)
        for (int d = 0; d < 4; d++)
            for (int f = 0; f < SPR_DEFS[s].n; f++) {
                const SprDef& sd = SPR_DEFS[s];
                int x = sd.xy[d][f][0], y = sd.xy[d][f][1];
                Tex3DS_SubTexture& st = gSub[s][d][f];
                st.width = sd.w; st.height = sd.h;
                st.left = (float)x / ATLAS_SIZE;
                st.right = (float)(x + sd.w) / ATLAS_SIZE;
                st.top = 1.0f - (float)y / ATLAS_SIZE;
                st.bottom = 1.0f - (float)(y + sd.h) / ATLAS_SIZE;
                gImg[s][d][f].tex = base.tex;
                gImg[s][d][f].subtex = &st;
            }
}

static void drawSprite(int s, int dir, int frame, float x, float y, const C2D_ImageTint* tint = nullptr, float sc = 1.0f) {
    const SprDef& sd = SPR_DEFS[s];
    C2D_DrawImageAt(gImg[s][dir][frame % sd.n], floorf(x - sd.ax * sc), floorf(y - sd.ay * sc), 0.5f, tint, sc, sc);
}

static int dirFromVec(float dx, float dy, int old) {
    if (fabsf(dx) < 0.01f && fabsf(dy) < 0.01f) return old;
    if (fabsf(dx) > fabsf(dy)) return dx > 0 ? 1 : 3;
    return dy > 0 ? 0 : 2;
}

// ---------- ataques (asignables a X/Y/B/A) ----------
enum { K_PIERCE, K_AIM, K_SPREAD, K_NOVA, K_BURST, K_HEAL, K_DASH, K_BEAM };
struct Atk { const char* name; const char* desc; float cd, dmg; int kind; u32 col; };
static const Atk ATKS[] = {
    {"Látigo Cepa",      "Látigo que atraviesa a 4 enemigos",        0.9f, 6,  K_PIERCE, COL(60, 200, 70, 255)},
    {"Ascuas",           "Bola de fuego rápida al más cercano",       0.5f, 5,  K_AIM,    COL(255, 140, 30, 255)},
    {"Pistola Agua",     "Abanico de 3 chorros de agua",              1.0f, 5,  K_SPREAD, COL(60, 150, 255, 255)},
    {"Terremoto",        "Onda de choque alrededor de ti",            3.5f, 18, K_NOVA,   COL(190, 150, 80, 255)},
    {"Tormenta Hojas",   "8 hojas en todas direcciones",              2.5f, 8,  K_BURST,  COL(130, 230, 90, 255)},
    {"Recuperación",     "Cura el 25% de tu vida máxima",             12.0f, 0, K_HEAL,   COL(255, 120, 180, 255)},
    {"Ataque Rápido",    "Embestida veloz, invulnerable",             3.0f, 0,  K_DASH,   COL(230, 230, 230, 255)},
    {"Hiperrayo",        "Rayo enorme que atraviesa todo",            6.0f, 40, K_BEAM,   COL(255, 230, 80, 255)},
};
static const int NATK = sizeof(ATKS) / sizeof(ATKS[0]);

static const u32 BTN_KEYS[4] = {KEY_X, KEY_Y, KEY_B, KEY_A};
static const char* BTN_NAMES[4] = {"X", "Y", "B", "A"};
static int gSlot[4];          // ataque asignado a cada botón
static float gCd[4];
static int gLv[8];            // nivel de cada ataque
static bool gAuto = true;     // dispara solo los ataques listos

// ---------- entidades ----------
struct Enemy { float x, y, hp, maxHp; u8 type, dir; bool boss; short spr; float flash, t, vx, vy; u32 id; };
struct Shot  { float x, y, vx, vy, life, dmg, r; int pierce; u32 hit[8]; u8 nh; u32 col; };
struct EShot { float x, y, vx, vy, life, dmg; };
struct Gem   { float x, y; int xp; };
struct Fx    { float x, y, t, r; u32 col; };

struct Player {
    float x, y, hp, maxHp, speed, invuln, dashT, dashX, dashY;
    int dir; bool moving;
    float dmg, cdMul, magnet;
    int shots, level, xp, xpNeed;
};

enum State { ST_TITLE, ST_LOADOUT, ST_PLAY, ST_LEVELUP, ST_OVER, ST_WIN };

static Enemy gEn[MAX_ENEMIES]; static int nEn;
static Shot  gSh[MAX_SHOTS];   static int nSh;
static Gem   gGem[MAX_GEMS];   static int nGem;
static EShot gEs[MAX_ESHOTS];  static int nEs;
static Fx    gFx[MAX_FX];      static int nFx;
static Player P;
static State gState = ST_TITLE;
static bool gPaused;
static int gChar = 1, gSel = 3, gBest, gSelAtk = -1;
static float gTime, gSpawnAcc, gNextBoss;
static int gKills, gBossN;
static u32 gNextId;
static u64 gAnimMs;
static u32 gManual;           // bits de botones pulsados este fotograma

static void loadBest() { FILE* f = fopen("sdmc:/3ds/pokesurvivor3ds.sav", "rb"); if (f) { if (fread(&gBest, 4, 1, f) != 1) gBest = 0; fclose(f); } }
static void saveBest() { FILE* f = fopen("sdmc:/3ds/pokesurvivor3ds.sav", "wb"); if (f) { fwrite(&gBest, 4, 1, f); fclose(f); } }

static void defaultLoadout() {
    static const int sig[3] = {0, 1, 2};
    gSlot[3] = sig[gChar]; gSlot[2] = 3; gSlot[0] = 4; gSlot[1] = 5;
}

// ---------- mejoras ----------
static const char* GEN_NAME[] = {"Más daño", "Cadencia", "Proyectil extra", "Velocidad", "Vitalidad", "Imán"};
static const char* GEN_DESC[] = {"+25% de daño", "Ataques 20% más rápidos", "+1 proyectil en ataques de tiro",
                                 "+12% de velocidad", "+20 vida máx. y cura 20", "+40% de alcance al recoger"};
static const int NGEN = 6;
static int gCards[3];
static char gCardName[3][48], gCardDesc[3][48];

static void applyCard(int c) {
    if (c >= NGEN) { gLv[gSlot[c - NGEN]]++; return; }
    switch (c) {
        case 0: P.dmg *= 1.25f; break;
        case 1: P.cdMul *= 0.8f; break;
        case 2: if (P.shots < 4) P.shots++; break;
        case 3: P.speed *= 1.12f; break;
        case 4: P.maxHp += 20; P.hp = fminf(P.maxHp, P.hp + 20); break;
        case 5: P.magnet *= 1.4f; break;
    }
}

static void rollCards() {
    int n = 0, total = NGEN + 4;
    while (n < 3) {
        int c = rnd() % total;
        bool dup = false;
        for (int i = 0; i < n; i++) if (gCards[i] == c) dup = true;
        if (c >= NGEN && ATKS[gSlot[c - NGEN]].kind == K_HEAL && gLv[gSlot[c - NGEN]] >= 3) dup = true;
        if (!dup) gCards[n++] = c;
    }
    for (int i = 0; i < 3; i++) {
        int c = gCards[i];
        if (c < NGEN) { snprintf(gCardName[i], 48, "%s", GEN_NAME[c]); snprintf(gCardDesc[i], 48, "%s", GEN_DESC[c]); }
        else {
            int s = c - NGEN, a = gSlot[s];
            snprintf(gCardName[i], 48, "%s [%s] Nv%d>%d", ATKS[a].name, BTN_NAMES[s], gLv[a] + 1, gLv[a] + 2);
            snprintf(gCardDesc[i], 48, "+30%% de potencia");
        }
    }
}

static void resetGame() {
    memset(&P, 0, sizeof(P));
    P.hp = P.maxHp = PLAYER_HP[gChar]; P.speed = PLAYER_SPD[gChar]; P.dmg = 1; P.cdMul = 1; P.shots = 1;
    P.magnet = 40; P.level = 1; P.xpNeed = 6;
    nEn = nSh = nGem = nEs = nFx = 0; gTime = gSpawnAcc = 0; gKills = 0;
    gNextBoss = BOSS_EVERY; gBossN = 0;
    memset(gCd, 0, sizeof gCd); memset(gLv, 0, sizeof gLv);
}

// ---------- entrada táctil: joystick flotante ----------
static bool gTouching; static float gOx, gOy, gJx, gJy;
static const float JOY_R = 44;

static void readInput(u32 down, u32 held) {
    touchPosition t; hidTouchRead(&t);
    gJx = gJy = 0;
    if (held & KEY_TOUCH) {
        if (!(down & KEY_TOUCH) && gTouching) {
            float dx = t.px - gOx, dy = t.py - gOy;
            float d = sqrtf(dx * dx + dy * dy);
            if (d > JOY_R) { gOx += dx / d * (d - JOY_R); gOy += dy / d * (d - JOY_R); dx = t.px - gOx; dy = t.py - gOy; d = JOY_R; }
            if (d > 6) { gJx = dx / JOY_R; gJy = dy / JOY_R; }
        } else { gTouching = true; gOx = t.px; gOy = t.py; }
    } else gTouching = false;

    circlePosition cp; hidCircleRead(&cp);
    if (fabsf(cp.dx) > 20 || fabsf(cp.dy) > 20) { gJx = cp.dx / 156.0f; gJy = -cp.dy / 156.0f; }
    if (held & KEY_DLEFT) gJx = -1;
    if (held & KEY_DRIGHT) gJx = 1;
    if (held & KEY_DUP) gJy = -1;
    if (held & KEY_DDOWN) gJy = 1;
    float m = sqrtf(gJx * gJx + gJy * gJy);
    if (m > 1) { gJx /= m; gJy /= m; }
}

// ---------- lógica ----------
static void spawnEnemy(bool boss) {
    if (nEn >= MAX_ENEMIES) return;
    int avail = 0;
    for (int i = 0; i < NTIERS; i++) if (gTime >= TIER_DEFS[i].from) avail = i + 1;
    float a = frand() * 6.2831853f, r = 250 + frand() * 40;
    Enemy& e = gEn[nEn++];
    e.boss = boss; e.id = ++gNextId;
    e.type = boss ? NTIERS - 1 : ((avail > 1 && rnd() % 3) ? avail - 1 - rnd() % 2 % avail : rnd() % avail);
    e.spr = TIER_DEFS[e.type].spr[rnd() % PER_TIER];
    e.x = P.x + cosf(a) * r; e.y = P.y + sinf(a) * r;
    e.maxHp = e.hp = boss ? 450 + 300 * gBossN : TIER_DEFS[e.type].hp * (1.0f + gTime / 120.0f);
    e.dir = 0; e.flash = 0; e.t = boss ? 2 : 1 + frand() * 2; e.vx = e.vy = 0;
}

static void dropGem(float x, float y, int xp) {
    if (nGem >= MAX_GEMS) { gGem[rnd() % MAX_GEMS].xp += xp; return; }
    gGem[nGem++] = {x, y, xp};
}

static void addFx(float x, float y, float r, u32 col) { if (nFx < MAX_FX) gFx[nFx++] = {x, y, 0.25f, r, col}; }

static void addShot(float ang, float sp, float life, float dmg, int pierce, float r, u32 col) {
    if (nSh >= MAX_SHOTS) return;
    Shot& s = gSh[nSh++];
    s.x = P.x; s.y = P.y - 8; s.vx = cosf(ang) * sp; s.vy = sinf(ang) * sp;
    s.life = life; s.dmg = dmg; s.r = r; s.pierce = pierce; s.nh = 0; s.col = col;
}

static void damageEnemy(Enemy& e, float d) { e.hp -= d; e.flash = 0.1f; }

static bool findTarget(float& ang) {
    int best = -1; float bd = 240 * 240;
    for (int i = 0; i < nEn; i++) {
        float dx = gEn[i].x - P.x, dy = gEn[i].y - P.y, d = dx * dx + dy * dy;
        if (d < bd) { bd = d; best = i; }
    }
    if (best < 0) return false;
    ang = atan2f(gEn[best].y - P.y, gEn[best].x - P.x);
    return true;
}

static void tryFire(int slot, bool manual) {
    const Atk& A = ATKS[gSlot[slot]];
    float power = P.dmg * (1.0f + 0.3f * gLv[gSlot[slot]]);
    float dmg = A.dmg * power, ang = 0;
    bool has = findTarget(ang);
    if (!has && manual) { static const float fa[4] = {1.5708f, 0, -1.5708f, 3.1416f}; ang = fa[P.dir]; has = true; }
    int extra = P.shots - 1;
    switch (A.kind) {
        case K_PIERCE: if (!has) return;
            for (int k = 0; k <= extra; k++) addShot(ang + (k - extra * 0.5f) * 0.2f, 200, 0.7f, dmg, 4, 7, A.col);
            break;
        case K_AIM: if (!has) return;
            for (int k = 0; k <= extra; k++) addShot(ang + (k - extra * 0.5f) * 0.15f, 300, 1.2f, dmg, 1, 5, A.col);
            break;
        case K_SPREAD: if (!has) return;
            for (int k = 0; k < 3 + extra; k++) addShot(ang + (k - (2 + extra) * 0.5f) * 0.24f, 230, 1.1f, dmg, 1, 5, A.col);
            break;
        case K_BURST:
            if (!has && !manual) return;
            for (int k = 0; k < 8; k++) addShot(k * 0.7854f, 170, 1.0f, dmg, 1, 5, A.col);
            break;
        case K_BEAM: if (!has) return;
            addShot(ang, 400, 0.9f, dmg, 99, 11, A.col); break;
        case K_NOVA: {
            bool any = manual;
            for (int i = 0; i < nEn; i++) {
                float dx = gEn[i].x - P.x, dy = gEn[i].y - P.y, d2 = dx * dx + dy * dy;
                if (d2 < 85 * 85) { damageEnemy(gEn[i], dmg); any = true; float d = sqrtf(d2) + 0.1f; gEn[i].x += dx / d * 24; gEn[i].y += dy / d * 24; }
            }
            if (!any) return;
            addFx(P.x, P.y, 85, A.col); break;
        }
        case K_HEAL:
            if (!manual && P.hp > P.maxHp * 0.6f) return;
            P.hp = fminf(P.maxHp, P.hp + P.maxHp * (0.25f + 0.05f * gLv[gSlot[slot]]));
            addFx(P.x, P.y, 20, A.col); break;
        case K_DASH:
            if (!manual) return;
            P.dashT = 0.3f; P.invuln = fmaxf(P.invuln, 0.35f);
            P.dashX = gJx; P.dashY = gJy;
            if (gJx == 0 && gJy == 0) { static const float dxs[4] = {0, 1, 0, -1}, dys[4] = {1, 0, -1, 0}; P.dashX = dxs[P.dir]; P.dashY = dys[P.dir]; }
            break;
    }
    gCd[slot] = A.cd * P.cdMul;
}

static void update(float dt) {
    gTime += dt;
    P.moving = (gJx != 0 || gJy != 0);
    if (P.dashT > 0) { P.dashT -= dt; P.x += P.dashX * 300 * dt; P.y += P.dashY * 300 * dt; }
    else { P.x += gJx * P.speed * dt; P.y += gJy * P.speed * dt; }
    if (P.moving) P.dir = dirFromVec(gJx, gJy, P.dir);
    if (P.invuln > 0) P.invuln -= dt;

    for (int i = 0; i < 4; i++) {
        gCd[i] -= dt;
        bool man = gManual & BTN_KEYS[i];
        if (gCd[i] <= 0 && (man || gAuto)) tryFire(i, man);
    }

    // oleadas y jefes
    gSpawnAcc += dt;
    float interval = fmaxf(0.14f, 0.9f - gTime * 0.005f);
    int batch = 1 + (int)(gTime / 60);
    while (gSpawnAcc >= interval) { gSpawnAcc -= interval; for (int b = 0; b < batch; b++) spawnEnemy(false); }
    if (gTime >= gNextBoss) { spawnEnemy(true); gBossN++; gNextBoss += BOSS_EVERY; }

    // proyectiles del jugador
    for (int i = 0; i < nSh;) {
        Shot& s = gSh[i];
        s.x += s.vx * dt; s.y += s.vy * dt; s.life -= dt;
        bool dead = s.life <= 0;
        for (int j = 0; j < nEn && !dead; j++) {
            Enemy& e = gEn[j];
            float r = (e.boss ? 18 : TIER_DEFS[e.type].radius) + s.r, dx = e.x - s.x, dy = e.y - s.y;
            if (dx * dx + dy * dy >= r * r) continue;
            bool seen = false;
            for (int k = 0; k < s.nh; k++) if (s.hit[k] == e.id) seen = true;
            if (seen) continue;
            damageEnemy(e, s.dmg);
            if (s.nh < 8) s.hit[s.nh++] = e.id;
            if (--s.pierce <= 0) dead = true;
        }
        if (dead) gSh[i] = gSh[--nSh]; else i++;
    }

    // enemigos
    for (int i = 0; i < nEn;) {
        Enemy& e = gEn[i];
        const TierDef& t = TIER_DEFS[e.type];
        if (e.hp <= 0) {
            dropGem(e.x, e.y, e.boss ? 30 : t.xp); gKills++;
            gEn[i] = gEn[--nEn]; continue;
        }
        float dx = P.x - e.x, dy = P.y - e.y, d = sqrtf(dx * dx + dy * dy);
        if (d > 420 && !e.boss) { gEn[i] = gEn[--nEn]; continue; }
        float mx = dx / (d + 0.01f), my = dy / (d + 0.01f), sp = e.boss ? 38 : t.spd;
        e.t -= dt;
        if (e.boss) {                  // jefe: lento, abanico de disparos
            if (e.t <= 0) {
                for (int k = -3; k <= 3 && nEs < MAX_ESHOTS; k++) {
                    float a = atan2f(dy, dx) + k * 0.28f;
                    gEs[nEs++] = {e.x, e.y, cosf(a) * 120, sinf(a) * 120, 3, 14};
                }
                e.t = 3.0f;
            }
        } else if (e.type == 1) {      // embestidor
            if (e.t < 0.6f && e.t > 0) sp = 0;
            else if (e.t <= 0) { e.vx = mx * 200; e.vy = my * 200; e.t = 2.6f; }
            if (e.t > 2.2f) { e.x += e.vx * dt; e.y += e.vy * dt; sp = 0; }
        } else if (e.type == 2) {      // tirador
            if (d < 110) sp = -sp * 0.6f; else if (d < 160) sp = 0;
            if (e.t <= 0 && d < 220 && nEs < MAX_ESHOTS) { gEs[nEs++] = {e.x, e.y, mx * 110, my * 110, 3, t.dmg}; e.t = 2.2f; }
        }
        e.x += mx * sp * dt; e.y += my * sp * dt;
        e.dir = dirFromVec(dx, dy, e.dir);
        if (e.flash > 0) e.flash -= dt;
        float rad = e.boss ? 18 : t.radius;
        if (d < rad + 7 && P.invuln <= 0) { P.hp -= e.boss ? 20 : t.dmg; P.invuln = 0.6f; }
        i++;
    }

    // proyectiles enemigos
    for (int i = 0; i < nEs;) {
        EShot& b = gEs[i];
        b.x += b.vx * dt; b.y += b.vy * dt; b.life -= dt;
        float dx = P.x - b.x, dy = P.y - b.y;
        bool hit = dx * dx + dy * dy < 100;
        if (hit && P.invuln <= 0) { P.hp -= b.dmg; P.invuln = 0.6f; }
        if (hit || b.life <= 0) gEs[i] = gEs[--nEs]; else i++;
    }

    for (int i = 0; i < nFx;) { gFx[i].t -= dt; if (gFx[i].t <= 0) gFx[i] = gFx[--nFx]; else i++; }

    // gemas de XP
    for (int i = 0; i < nGem;) {
        Gem& g = gGem[i];
        float dx = P.x - g.x, dy = P.y - g.y, d = sqrtf(dx * dx + dy * dy);
        if (d < P.magnet) { float sp = 220 * dt; if (d > 0.1f) { g.x += dx / d * sp; g.y += dy / d * sp; } }
        if (d < 9) {
            P.xp += g.xp; gGem[i] = gGem[--nGem];
            if (P.xp >= P.xpNeed) {
                P.xp -= P.xpNeed; P.level++; P.xpNeed = 6 + P.level * 4;
                rollCards(); gState = ST_LEVELUP; gTouching = false;
                return;
            }
            continue;
        }
        i++;
    }

    if (P.hp <= 0) { P.hp = 0; gState = ST_OVER; }
    else if (gTime >= WIN_TIME) gState = ST_WIN;
    if ((gState == ST_OVER || gState == ST_WIN) && (int)gTime > gBest) { gBest = (int)gTime; saveBest(); }
}

// ---------- dibujo ----------
static C2D_TextBuf gTxt;
static void text(const char* s, float x, float y, float sc, u32 col, bool center = false) {
    C2D_Text t; C2D_TextParse(&t, gTxt, s); C2D_TextOptimize(&t);
    if (center) { float w, h; C2D_TextGetDimensions(&t, sc, sc, &w, &h); x -= w * 0.5f; }
    C2D_DrawText(&t, C2D_WithColor, x, y, 0.9f, sc, sc, col);
}

static void drawWorld() {
    float cx = P.x - TOP_W / 2, cy = P.y - TOP_H / 2;
    C2D_DrawRectSolid(0, 0, 0.0f, TOP_W, TOP_H, COL(74, 140, 72, 255));
    int tx0 = (int)floorf(cx / 32), ty0 = (int)floorf(cy / 32);
    for (int ty = ty0; ty <= ty0 + 8; ty++)
        for (int tx = tx0; tx <= tx0 + 13; tx++) {
            u32 h = (u32)(tx * 73856093) ^ (u32)(ty * 19349663);
            float sx = tx * 32 - cx, sy = ty * 32 - cy;
            if (((tx + ty) & 1) == 0) C2D_DrawRectSolid(sx, sy, 0.1f, 32, 32, COL(82, 150, 78, 255));
            if ((h >> 4) % 7 == 0) C2D_DrawRectSolid(sx + 10, sy + 12, 0.1f, 3, 6, COL(50, 105, 52, 255));
        }

    for (int i = 0; i < nFx; i++) {
        float k = 1.0f - gFx[i].t / 0.25f;
        u32 c = gFx[i].col & 0x00FFFFFF;
        C2D_DrawCircleSolid(gFx[i].x - cx, gFx[i].y - cy, 0.2f, gFx[i].r * (0.4f + 0.6f * k), c | ((u32)(120 * (1 - k)) << 24));
    }

    for (int i = 0; i < nGem; i++) {
        float x = gGem[i].x - cx, y = gGem[i].y - cy;
        if (x < -8 || x > TOP_W + 8 || y < -8 || y > TOP_H + 8) continue;
        C2D_DrawTriangle(x, y - 5, COL(120, 220, 255, 255), x - 4, y, COL(60, 160, 255, 255), x + 4, y, COL(60, 160, 255, 255), 0.3f);
        C2D_DrawTriangle(x, y + 5, COL(40, 110, 220, 255), x - 4, y, COL(60, 160, 255, 255), x + 4, y, COL(60, 160, 255, 255), 0.3f);
    }

    static C2D_ImageTint white; static bool wInit = false;
    if (!wInit) { C2D_PlainImageTint(&white, COL(255, 255, 255, 255), 1.0f); wInit = true; }
    for (int pass = 0; pass < 2; pass++) {
        for (int i = 0; i < nEn; i++) {
            Enemy& e = gEn[i];
            if ((e.y < P.y) != (pass == 0)) continue;
            float x = e.x - cx, y = e.y - cy;
            if (x < -60 || x > TOP_W + 60 || y < -60 || y > TOP_H + 80) continue;
            const SprDef& sd = SPR_DEFS[e.spr];
            float sc = e.boss ? 2.0f : 1.0f;
            drawSprite(e.spr, e.dir, (int)(gAnimMs / sd.ms), x, y, e.flash > 0 ? &white : nullptr, sc);
            if (e.boss) {
                C2D_DrawRectSolid(x - 24, y - sd.h * sc - 4, 0.8f, 48, 4, COL(0, 0, 0, 200));
                C2D_DrawRectSolid(x - 23, y - sd.h * sc - 3, 0.85f, 46 * clampf(e.hp / e.maxHp, 0, 1), 2, COL(230, 60, 60, 255));
            }
        }
        if (pass == 0) {
            C2D_DrawEllipseSolid(P.x - cx - 9, P.y - cy - 4, 0.4f, 18, 8, COL(0, 0, 0, 70));
            if (P.invuln <= 0 || ((int)(gTime * 12) & 1)) {
                const SprDef& sd = SPR_DEFS[gChar];
                drawSprite(gChar, P.dir, P.moving ? (int)(gAnimMs / sd.ms) : 0, P.x - cx, P.y - cy);
            }
        }
    }

    for (int i = 0; i < nEs; i++) {
        C2D_DrawCircleSolid(gEs[i].x - cx, gEs[i].y - cy, 0.6f, 4, COL(220, 60, 200, 255));
    }
    for (int i = 0; i < nSh; i++) {
        float x = gSh[i].x - cx, y = gSh[i].y - cy;
        C2D_DrawCircleSolid(x, y, 0.6f, gSh[i].r, gSh[i].col);
        C2D_DrawCircleSolid(x, y, 0.65f, gSh[i].r * 0.5f, COL(255, 255, 220, 255));
    }

    C2D_DrawRectSolid(TOP_W / 2 - 14, TOP_H / 2 + 6, 0.8f, 28, 4, COL(0, 0, 0, 180));
    C2D_DrawRectSolid(TOP_W / 2 - 13, TOP_H / 2 + 7, 0.85f, 26 * clampf(P.hp / P.maxHp, 0, 1), 2, COL(90, 230, 90, 255));
}

static void drawBottomHud() {
    C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
    char b[64];
    snprintf(b, sizeof b, "Nv %d", P.level);
    text(b, 8, 4, 0.6f, COL(255, 255, 255, 255));
    int secs = (int)gTime;
    snprintf(b, sizeof b, "%02d:%02d", secs / 60, secs % 60);
    text(b, 160, 4, 0.6f, COL(255, 255, 255, 255), true);
    snprintf(b, sizeof b, "KO %d", gKills);
    text(b, 262, 4, 0.6f, COL(255, 230, 120, 255));
    C2D_DrawRectSolid(8, 26, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 26, 0.2f, 304 * clampf((float)P.xp / P.xpNeed, 0, 1), 8, COL(80, 180, 255, 255));
    C2D_DrawRectSolid(8, 38, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 38, 0.2f, 304 * clampf(P.hp / P.maxHp, 0, 1), 8, COL(90, 220, 90, 255));
    for (int i = 0; i < 4; i++) {
        float x = 8 + i * 78, y = 178;
        const Atk& A = ATKS[gSlot[i]];
        C2D_DrawRectSolid(x, y, 0.1f, 72, 34, COL(20, 30, 70, 255));
        float ready = 1.0f - clampf(gCd[i] / (A.cd * P.cdMul), 0, 1);
        C2D_DrawRectSolid(x, y + 30, 0.2f, 72 * ready, 4, A.col);
        snprintf(gCardName[0], 48, "%s", BTN_NAMES[i]);
        text(gCardName[0], x + 4, y + 1, 0.55f, A.col);
        text(A.name, x + 16, y + 6, 0.38f, COL(255, 255, 255, 255));
    }
    text("START: pausa / ataques", 160, 216, 0.45f, COL(150, 170, 220, 255), true);
    if (gTouching) {
        C2D_DrawCircleSolid(gOx, gOy, 0.3f, JOY_R, COL(255, 255, 255, 40));
        C2D_DrawCircleSolid(gOx + gJx * JOY_R, gOy + gJy * JOY_R, 0.4f, 18, COL(255, 255, 255, 140));
    }
}

static const float CARD_X = 10, CARD_W = 300, CARD_H = 64;
static float cardY(int i) { return 28 + i * 70; }

static void drawCards() {
    C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
    char b[32]; snprintf(b, sizeof b, "¡Nivel %d! Elige una mejora", P.level);
    text(b, 160, 6, 0.65f, COL(255, 230, 120, 255), true);
    for (int i = 0; i < 3; i++) {
        float y = cardY(i);
        C2D_DrawRectSolid(CARD_X, y, 0.1f, CARD_W, CARD_H, COL(70, 110, 200, 255));
        C2D_DrawRectSolid(CARD_X + 3, y + 3, 0.2f, CARD_W - 6, CARD_H - 6, COL(20, 30, 70, 255));
        text(gCardName[i], CARD_X + 12, y + 8, 0.6f, COL(255, 255, 255, 255));
        text(gCardDesc[i], CARD_X + 12, y + 34, 0.5f, COL(170, 200, 255, 255));
    }
}

static void drawCentered(const char* a, const char* b, u32 ca) {
    C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
    text(a, 160, 90, 0.8f, ca, true);
    text(b, 160, 140, 0.55f, COL(170, 200, 255, 255), true);
}

// ---------- pantalla de ataques (asignar a X/Y/B/A) ----------
static void drawButton(float x, float y, float w, float h, const char* label, u32 bg, u32 fg) {
    C2D_DrawRectSolid(x, y, 0.1f, w, h, bg);
    text(label, x + w / 2, y + h / 2 - 9, 0.5f, fg, true);
}

static void drawLoadoutBottom() {
    C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
    text("Toca un botón y luego un ataque", 160, 4, 0.5f, COL(255, 230, 120, 255), true);
    for (int i = 0; i < 4; i++) {
        float x = 8 + i * 78, y = 24;
        const Atk& A = ATKS[gSlot[i]];
        C2D_DrawRectSolid(x, y, 0.1f, 72, 44, i == gSel ? A.col : COL(70, 110, 200, 255));
        C2D_DrawRectSolid(x + 2, y + 2, 0.2f, 68, 40, COL(20, 30, 70, 255));
        text(BTN_NAMES[i], x + 5, y + 1, 0.6f, A.col);
        text(A.name, x + 36, y + 14, 0.36f, COL(255, 255, 255, 255), true);
    }
    for (int j = 0; j < NATK; j++) {
        float x = 8 + (j % 2) * 156, y = 76 + (j / 2) * 34;
        bool used = false;
        for (int i = 0; i < 4; i++) if (gSlot[i] == j) used = true;
        C2D_DrawRectSolid(x, y, 0.1f, 150, 30, j == gSelAtk ? ATKS[j].col : (used ? COL(60, 80, 140, 255) : COL(40, 50, 90, 255)));
        text(ATKS[j].name, x + 6, y + 6, 0.5f, COL(255, 255, 255, 255));
    }
    drawButton(8, 210, 96, 26, gAuto ? "Auto: SÍ" : "Auto: NO", COL(70, 110, 200, 255), COL(255, 255, 255, 255));
    drawButton(112, 210, 100, 26, gPaused ? "Reprendre" : "¡Jugar!", COL(90, 190, 90, 255), COL(255, 255, 255, 255));
    drawButton(220, 210, 92, 26, gPaused ? "Quitter" : "Retour", COL(180, 80, 80, 255), COL(255, 255, 255, 255));
}

static void drawLoadoutTop() {
    C2D_DrawRectSolid(0, 0, 0, TOP_W, TOP_H, COL(20, 40, 70, 255));
    int a = gSelAtk >= 0 ? gSelAtk : gSlot[gSel];
    text("Ataques", 200, 14, 0.9f, COL(255, 220, 90, 255), true);
    text(ATKS[a].name, 200, 70, 0.9f, ATKS[a].col, true);
    text(ATKS[a].desc, 200, 110, 0.55f, COL(255, 255, 255, 255), true);
    char b[64]; snprintf(b, sizeof b, "Recarga: %.1f s · Nivel %d", ATKS[a].cd, gLv[a] + 1);
    text(b, 200, 140, 0.5f, COL(170, 200, 255, 255), true);
    snprintf(b, sizeof b, "Botón seleccionado: %s", BTN_NAMES[gSel]);
    text(b, 200, 175, 0.5f, COL(255, 230, 120, 255), true);
    text("Pulsa X / Y / B / A para elegir el botón", 200, 205, 0.45f, COL(150, 170, 220, 255), true);
}

static void assign(int atk) {
    for (int i = 0; i < 4; i++) if (gSlot[i] == atk && i != gSel) { gSlot[i] = gSlot[gSel]; break; }
    gSlot[gSel] = atk;
}

int main() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    gTxt = C2D_TextBufNew(4096);
    initSprites();
    rngState ^= (u32)osGetTime();
    loadBest();
    defaultLoadout();
    resetGame();

    u64 last = osGetTime();
    while (aptMainLoop()) {
        hidScanInput();
        u32 down = hidKeysDown(), held = hidKeysHeld();
        if (down & KEY_START) {
            if (gState == ST_TITLE) break;
            if (gState == ST_PLAY) { gState = ST_LOADOUT; gPaused = true; gSelAtk = -1; gTouching = false; }
        }

        u64 now = osGetTime();
        float dt = clampf((now - last) / 1000.0f, 0.0f, 0.05f);
        last = now;
        gAnimMs = now;

        touchPosition tp; hidTouchRead(&tp);
        bool tap = down & KEY_TOUCH;
        if (gState == ST_TITLE) {
            if (tap) {
                int c = (int)(tp.px / (320.0f / NPLAYERS));
                if (tp.py >= 60 && tp.py <= 180 && c >= 0 && c < NPLAYERS) gChar = c;
                else if (tp.py > 190) { defaultLoadout(); gState = ST_LOADOUT; gPaused = false; gSelAtk = -1; }
            }
            if ((down & KEY_LEFT) && gChar > 0) gChar--;
            if ((down & KEY_RIGHT) && gChar < NPLAYERS - 1) gChar++;
            if (down & KEY_A) { defaultLoadout(); gState = ST_LOADOUT; gPaused = false; gSelAtk = -1; }
        } else if (gState == ST_LOADOUT) {
            for (int i = 0; i < 4; i++) if (down & BTN_KEYS[i]) { gSel = i; gSelAtk = -1; }
            if (tap) {
                for (int i = 0; i < 4; i++) if (inRect(tp.px, tp.py, 8 + i * 78, 24, 72, 44)) { gSel = i; gSelAtk = -1; }
                for (int j = 0; j < NATK; j++)
                    if (inRect(tp.px, tp.py, 8 + (j % 2) * 156, 76 + (j / 2) * 34, 150, 30)) { assign(j); gSelAtk = j; }
                if (inRect(tp.px, tp.py, 8, 210, 96, 26)) gAuto = !gAuto;
                if (inRect(tp.px, tp.py, 112, 210, 100, 26)) {
                    if (!gPaused) resetGame();
                    gState = ST_PLAY; gPaused = false;
                }
                if (inRect(tp.px, tp.py, 220, 210, 92, 26)) gState = ST_TITLE;
            }
        } else if (gState == ST_PLAY) {
            readInput(down, held);
            gManual = down;
            update(dt);
        } else if (gState == ST_LEVELUP) {
            int pick = -1;
            if (tap)
                for (int i = 0; i < 3; i++)
                    if (inRect(tp.px, tp.py, CARD_X, cardY(i), CARD_W, CARD_H)) pick = i;
            if (down & KEY_A) pick = 0;
            if (pick >= 0) { applyCard(gCards[pick]); gState = ST_PLAY; }
        } else if (tap || (down & KEY_A)) {
            gState = ST_TITLE;
        }

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TextBufClear(gTxt);
        C2D_TargetClear(top, COL(0, 0, 0, 255));
        C2D_TargetClear(bot, COL(0, 0, 0, 255));

        C2D_SceneBegin(top);
        if (gState == ST_TITLE) {
            C2D_DrawRectSolid(0, 0, 0, TOP_W, TOP_H, COL(20, 60, 40, 255));
            text("PokéSurvivor 3DS", 200, 80, 1.1f, COL(255, 220, 90, 255), true);
            text("Sobrevive 10 minutos", 200, 130, 0.6f, COL(200, 230, 200, 255), true);
        } else if (gState == ST_LOADOUT) {
            drawLoadoutTop();
        } else {
            drawWorld();
        }

        C2D_SceneBegin(bot);
        char b[64];
        switch (gState) {
            case ST_TITLE:
                C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
                text("Elige tu Pokémon", 160, 10, 0.7f, COL(255, 230, 120, 255), true);
                for (int i = 0; i < NPLAYERS; i++) {
                    float cx = 320.0f / NPLAYERS * (i + 0.5f);
                    C2D_DrawRectSolid(cx - 48, 60, 0.1f, 96, 120, i == gChar ? COL(70, 110, 200, 255) : COL(40, 50, 90, 255));
                    drawSprite(i, 0, (int)(gAnimMs / SPR_DEFS[i].ms), cx, 130);
                    text(PLAYER_NAMES[i], cx, 150, 0.5f, COL(255, 255, 255, 255), true);
                }
                snprintf(b, sizeof b, "Mejor: %02d:%02d", gBest / 60, gBest % 60);
                text(b, 160, 40, 0.5f, COL(170, 200, 255, 255), true);
                C2D_DrawRectSolid(60, 196, 0.1f, 200, 32, COL(90, 190, 90, 255));
                text("Elegir ataques", 160, 202, 0.7f, COL(255, 255, 255, 255), true);
                break;
            case ST_LOADOUT: drawLoadoutBottom(); break;
            case ST_PLAY: drawBottomHud(); break;
            case ST_LEVELUP: drawCards(); break;
            case ST_OVER:
                snprintf(b, sizeof b, "Aguantaste %02d:%02d · KO %d", (int)gTime / 60, (int)gTime % 60, gKills);
                drawCentered("¡Has caído!", b, COL(255, 100, 100, 255));
                text("Toca para volver", 160, 190, 0.5f, COL(170, 200, 255, 255), true);
                break;
            case ST_WIN:
                snprintf(b, sizeof b, "10:00 · KO %d", gKills);
                drawCentered("¡Victoria!", b, COL(120, 255, 140, 255));
                text("Toca para volver", 160, 190, 0.5f, COL(170, 200, 255, 255), true);
                break;
        }
        C3D_FrameEnd(0);
    }

    C2D_TextBufDelete(gTxt);
    C2D_SpriteSheetFree(gSheet);
    C2D_Fini(); C3D_Fini(); gfxExit();
    return 0;
}
