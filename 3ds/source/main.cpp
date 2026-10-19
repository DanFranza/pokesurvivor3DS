// PokéSurvivor 3DS — prototipo nativo (Old 3DS XL compatible).
// Pantalla superior: mundo. Pantalla táctil: joystick virtual, HUD y cartas.
#include <3ds.h>
#include <citro2d.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "atlas_t3x.h"
#include "sprites.h"

// ---------- límites de memoria (todo estático, nada de malloc en juego) ----------
static const int MAX_ENEMIES = 110;
static const int MAX_SHOTS   = 48;
static const int MAX_GEMS    = 160;

static const float TOP_W = 400, TOP_H = 240;

// ---------- utilidades ----------
static u32 rngState = 2463534242u;
static u32 rnd() { rngState ^= rngState << 13; rngState ^= rngState >> 17; rngState ^= rngState << 5; return rngState; }
static float frand() { return (rnd() & 0xFFFFFF) / 16777216.0f; }
static float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
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

static void drawSprite(int s, int dir, int frame, float x, float y, const C2D_ImageTint* tint = nullptr) {
    const SprDef& sd = SPR_DEFS[s];
    C2D_DrawImageAt(gImg[s][dir][frame % sd.n], floorf(x - sd.ax), floorf(y - sd.ay), 0.5f, tint);
}

static int dirFromVec(float dx, float dy, int old) {
    if (fabsf(dx) < 0.01f && fabsf(dy) < 0.01f) return old;
    if (fabsf(dx) > fabsf(dy)) return dx > 0 ? 1 : 3;
    return dy > 0 ? 0 : 2;
}

// ---------- entidades ----------
static const int NTYPES = NTIERS;

struct Enemy { float x, y, hp; u8 type, dir; short spr; float flash, t, vx, vy; };
struct EShot { float x, y, vx, vy, life; };
struct Shot  { float x, y, vx, vy, life; int hitsLeft; };
struct Gem   { float x, y; int xp; };

struct Player {
    float x, y, hp, maxHp, speed, invuln;
    int dir; bool moving;
    float dmg, cooldown, cdTimer, magnet;
    int shots, level, xp, xpNeed;
};

enum State { ST_TITLE, ST_PLAY, ST_LEVELUP, ST_OVER };

static Enemy gEn[110]; static int nEn;
static Shot  gSh[48];  static int nSh;
static Gem   gGem[160]; static int nGem;
static EShot gEs[40]; static int nEs;
static Player P;
static int gBest;

static void loadBest() { FILE* f = fopen("sdmc:/3ds/pokesurvivor3ds.sav", "rb"); if (f) { if (fread(&gBest, 4, 1, f) != 1) gBest = 0; fclose(f); } }
static void saveBest() { FILE* f = fopen("sdmc:/3ds/pokesurvivor3ds.sav", "wb"); if (f) { fwrite(&gBest, 4, 1, f); fclose(f); } }
static State gState = ST_TITLE;
static int gChar = 1;
static float gTime, gSpawnAcc;
static int gKills;
static u64 gAnimMs;

// ---------- mejoras ----------
struct Upgrade { const char* name; const char* desc; };
static const Upgrade UPS[] = {
    {"Más daño",       "+25% de daño"},
    {"Cadencia",       "Dispara 20% más rápido"},
    {"Doble disparo",  "+1 proyectil por ráfaga"},
    {"Velocidad",      "+12% de velocidad"},
    {"Vitalidad",      "+20 vida máx. y cura 20"},
    {"Imán",           "+40% de alcance al recoger"},
};
static const int NUPS = sizeof(UPS) / sizeof(UPS[0]);
static int gCards[3];

static void applyUpgrade(int u) {
    switch (u) {
        case 0: P.dmg *= 1.25f; break;
        case 1: P.cooldown *= 0.8f; break;
        case 2: if (P.shots < 5) P.shots++; break;
        case 3: P.speed *= 1.12f; break;
        case 4: P.maxHp += 20; P.hp = fminf(P.maxHp, P.hp + 20); break;
        case 5: P.magnet *= 1.4f; break;
    }
}

static void rollCards() {
    int n = 0;
    while (n < 3) {
        int c = rnd() % NUPS;
        bool dup = false;
        for (int i = 0; i < n; i++) if (gCards[i] == c) dup = true;
        if (!dup) gCards[n++] = c;
    }
}

static void resetGame() {
    memset(&P, 0, sizeof(P));
    P.hp = P.maxHp = PLAYER_HP[gChar]; P.speed = PLAYER_SPD[gChar]; P.dmg = 7; P.cooldown = 0.8f; P.shots = 1;
    P.magnet = 40; P.level = 1; P.xpNeed = 6;
    nEn = nSh = nGem = nEs = 0; gTime = gSpawnAcc = 0; gKills = 0;
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

    // Respaldo con el Circle Pad / cruceta
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
static void spawnEnemy() {
    if (nEn >= MAX_ENEMIES) return;
    int avail = 0;
    for (int i = 0; i < NTYPES; i++) if (gTime >= TIER_DEFS[i].from) avail = i + 1;
    float a = frand() * 6.2831853f, r = 250 + frand() * 40;
    Enemy& e = gEn[nEn++];
    e.type = (avail > 1 && rnd() % 3) ? avail - 1 - rnd() % 2 % avail : rnd() % avail;
    e.spr = TIER_DEFS[e.type].spr[rnd() % PER_TIER];
    e.x = P.x + cosf(a) * r; e.y = P.y + sinf(a) * r;
    e.hp = TIER_DEFS[e.type].hp * (1.0f + gTime / 120.0f);
    e.dir = 0; e.flash = 0; e.t = 1 + frand() * 2; e.vx = e.vy = 0;
}

static void dropGem(float x, float y, int xp) {
    if (nGem >= MAX_GEMS) { gGem[rnd() % MAX_GEMS].xp += xp; return; }
    gGem[nGem++] = {x, y, xp};
}

static void fire() {
    int best = -1; float bd = 230 * 230;
    for (int i = 0; i < nEn; i++) {
        float dx = gEn[i].x - P.x, dy = gEn[i].y - P.y, d = dx * dx + dy * dy;
        if (d < bd) { bd = d; best = i; }
    }
    if (best < 0) return;
    float ang = atan2f(gEn[best].y - P.y, gEn[best].x - P.x);
    for (int k = 0; k < P.shots && nSh < MAX_SHOTS; k++) {
        float a = ang + (k - (P.shots - 1) * 0.5f) * 0.18f;
        float sp = gChar == 1 ? 280 : (gChar == 0 ? 190 : 230);
        gSh[nSh++] = {P.x, P.y - 8, cosf(a) * sp, sinf(a) * sp, gChar == 0 ? 1.0f : 1.3f, gChar == 0 ? 4 : (gChar == 2 ? 2 : 1)};
    }
    P.cdTimer = P.cooldown;
}

static void update(float dt) {
    gTime += dt;
    // jugador
    P.moving = (gJx != 0 || gJy != 0);
    P.x += gJx * P.speed * dt; P.y += gJy * P.speed * dt;
    if (P.moving) P.dir = dirFromVec(gJx, gJy, P.dir);
    if (P.invuln > 0) P.invuln -= dt;
    P.cdTimer -= dt;
    if (P.cdTimer <= 0) fire();

    // oleadas
    gSpawnAcc += dt;
    float interval = fmaxf(0.14f, 0.9f - gTime * 0.005f);
    int batch = 1 + (int)(gTime / 60);
    while (gSpawnAcc >= interval) { gSpawnAcc -= interval; for (int b = 0; b < batch; b++) spawnEnemy(); }

    // proyectiles
    for (int i = 0; i < nSh;) {
        Shot& s = gSh[i];
        s.x += s.vx * dt; s.y += s.vy * dt; s.life -= dt;
        bool dead = s.life <= 0;
        for (int j = 0; j < nEn && !dead; j++) {
            Enemy& e = gEn[j];
            float r = TIER_DEFS[e.type].radius + 5, dx = e.x - s.x, dy = e.y - s.y;
            if (dx * dx + dy * dy < r * r) {
                e.hp -= P.dmg; e.flash = 0.1f;
                if (--s.hitsLeft <= 0) dead = true;
                break;
            }
        }
        if (dead) gSh[i] = gSh[--nSh]; else i++;
    }

    // enemigos
    for (int i = 0; i < nEn;) {
        Enemy& e = gEn[i];
        const TierDef& t = TIER_DEFS[e.type];
        if (e.hp <= 0) {
            dropGem(e.x, e.y, t.xp); gKills++;
            gEn[i] = gEn[--nEn]; continue;
        }
        float dx = P.x - e.x, dy = P.y - e.y, d = sqrtf(dx * dx + dy * dy);
        if (d > 420) { gEn[i] = gEn[--nEn]; continue; }
        float mx = dx / (d + 0.01f), my = dy / (d + 0.01f), sp = t.spd;
        e.t -= dt;
        if (e.type == 1) {            // chargeur: se arrête, vise, embiste
            if (e.t < 0.6f && e.t > 0) sp = 0;
            else if (e.t <= 0) { e.vx = mx * 200; e.vy = my * 200; e.t = 0.4f + 2.2f; }
            if (e.t > 2.2f) { e.x += e.vx * dt; e.y += e.vy * dt; sp = 0; }
        } else if (e.type == 2) {     // tirador: mantiene distancia y dispara
            if (d < 110) sp = -sp * 0.6f; else if (d < 160) sp = 0;
            if (e.t <= 0 && d < 220 && nEs < 40) {
                gEs[nEs++] = {e.x, e.y, mx * 110, my * 110, 3};
                e.t = 2.2f;
            }
        }
        e.x += mx * sp * dt; e.y += my * sp * dt;
        e.dir = dirFromVec(dx, dy, e.dir);
        if (e.flash > 0) e.flash -= dt;
        if (d < t.radius + 7 && P.invuln <= 0) { P.hp -= t.dmg; P.invuln = 0.6f; }
        i++;
    }

    // proyectiles enemigos
    for (int i = 0; i < nEs;) {
        EShot& b = gEs[i];
        b.x += b.vx * dt; b.y += b.vy * dt; b.life -= dt;
        float dx = P.x - b.x, dy = P.y - b.y;
        bool hit = dx * dx + dy * dy < 100;
        if (hit && P.invuln <= 0) { P.hp -= TIER_DEFS[2].dmg; P.invuln = 0.6f; }
        if (hit || b.life <= 0) gEs[i] = gEs[--nEs]; else i++;
    }

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
            }
            continue;
        }
        i++;
    }

    if (P.hp <= 0) { P.hp = 0; gState = ST_OVER; if ((int)gTime > gBest) { gBest = (int)gTime; saveBest(); } }
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

    for (int i = 0; i < nGem; i++) {
        float x = gGem[i].x - cx, y = gGem[i].y - cy;
        if (x < -8 || x > TOP_W + 8 || y < -8 || y > TOP_H + 8) continue;
        C2D_DrawTriangle(x, y - 5, COL(120, 220, 255, 255), x - 4, y, COL(60, 160, 255, 255), x + 4, y, COL(60, 160, 255, 255), 0.3f);
        C2D_DrawTriangle(x, y + 5, COL(40, 110, 220, 255), x - 4, y, COL(60, 160, 255, 255), x + 4, y, COL(60, 160, 255, 255), 0.3f);
    }

    // Enemigos "detrás" del jugador, jugador, enemigos "delante"
    const C2D_ImageTint* tintNone = nullptr;
    static C2D_ImageTint white; static bool wInit = false;
    if (!wInit) { C2D_PlainImageTint(&white, COL(255, 255, 255, 255), 1.0f); wInit = true; }
    for (int pass = 0; pass < 2; pass++) {
        for (int i = 0; i < nEn; i++) {
            Enemy& e = gEn[i];
            if ((e.y < P.y) != (pass == 0)) continue;
            float x = e.x - cx, y = e.y - cy;
            if (x < -40 || x > TOP_W + 40 || y < -40 || y > TOP_H + 60) continue;
            const SprDef& sd = SPR_DEFS[e.spr];
            drawSprite(e.spr, e.dir, (int)(gAnimMs / sd.ms), x, y, e.flash > 0 ? &white : tintNone);
        }
        if (pass == 0) {
            C2D_DrawEllipseSolid(P.x - cx - 9, P.y - cy - 4, 0.4f, 18, 8, COL(0, 0, 0, 70));
            if (P.invuln <= 0 || ((int)(gTime * 12) & 1)) {
                const SprDef& sd = SPR_DEFS[gChar];
                drawSprite(gChar, P.dir, P.moving ? (int)(gAnimMs / sd.ms) : 0, P.x - cx, P.y - cy);
            }
        }
    }

    for (int i = 0; i < nEs; i++)
        C2D_DrawCircleSolid(gEs[i].x - cx, gEs[i].y - cy, 0.6f, 4, COL(220, 60, 200, 255));
    for (int i = 0; i < nSh; i++) {
        float x = gSh[i].x - cx, y = gSh[i].y - cy;
        static const u32 outer[3] = {COL(60, 200, 70, 255), COL(255, 140, 30, 255), COL(60, 150, 255, 255)};
        C2D_DrawCircleSolid(x, y, 0.6f, 5, outer[gChar]);
        C2D_DrawCircleSolid(x, y, 0.65f, 2.5f, COL(255, 255, 220, 255));
    }

    // Marco de vida sobre el jugador
    C2D_DrawRectSolid(TOP_W / 2 - 14, TOP_H / 2 + 6, 0.8f, 28, 4, COL(0, 0, 0, 180));
    C2D_DrawRectSolid(TOP_W / 2 - 13, TOP_H / 2 + 7, 0.85f, 26 * P.hp / P.maxHp, 2, COL(90, 230, 90, 255));
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
    text(b, 312 - 50, 4, 0.6f, COL(255, 230, 120, 255));
    C2D_DrawRectSolid(8, 26, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 26, 0.2f, 304 * clampf((float)P.xp / P.xpNeed, 0, 1), 8, COL(80, 180, 255, 255));
    C2D_DrawRectSolid(8, 38, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 38, 0.2f, 304 * clampf(P.hp / P.maxHp, 0, 1), 8, COL(90, 220, 90, 255));
    text("Toca y arrastra para moverte", 160, 215, 0.5f, COL(150, 170, 220, 255), true);
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
        text(UPS[gCards[i]].name, CARD_X + 12, y + 8, 0.7f, COL(255, 255, 255, 255));
        text(UPS[gCards[i]].desc, CARD_X + 12, y + 34, 0.55f, COL(170, 200, 255, 255));
    }
}

static void drawCentered(const char* a, const char* b, u32 ca) {
    C2D_DrawRectSolid(0, 0, 0, 320, 240, COL(28, 36, 64, 255));
    text(a, 160, 90, 0.8f, ca, true);
    text(b, 160, 140, 0.55f, COL(170, 200, 255, 255), true);
}

int main() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    gTxt = C2D_TextBufNew(2048);
    initSprites();
    rngState ^= (u32)osGetTime();
    loadBest();
    resetGame();

    u64 last = osGetTime();
    while (aptMainLoop()) {
        hidScanInput();
        u32 down = hidKeysDown(), held = hidKeysHeld();
        if (down & KEY_START) break;

        u64 now = osGetTime();
        float dt = clampf((now - last) / 1000.0f, 0.0f, 0.05f);
        last = now;
        gAnimMs = now;

        touchPosition tp; hidTouchRead(&tp);
        if (gState == ST_TITLE) {
            if (down & KEY_TOUCH) {
                int c = (int)(tp.px / (320.0f / NPLAYERS));
                if (tp.py >= 60 && tp.py <= 180 && c >= 0 && c < NPLAYERS) gChar = c;
                else if (tp.py > 190) { resetGame(); gState = ST_PLAY; }
            }
            if (down & KEY_LEFT && gChar > 0) gChar--;
            if (down & KEY_RIGHT && gChar < NPLAYERS - 1) gChar++;
            if (down & KEY_A) { resetGame(); gState = ST_PLAY; }
        } else if (gState == ST_PLAY) {
            readInput(down, held);
            update(dt);
        } else if (gState == ST_LEVELUP) {
            int pick = -1;
            if (down & KEY_TOUCH)
                for (int i = 0; i < 3; i++)
                    if (tp.px >= CARD_X && tp.px <= CARD_X + CARD_W && tp.py >= cardY(i) && tp.py <= cardY(i) + CARD_H) pick = i;
            if (down & KEY_A) pick = 0;
            if (pick >= 0) { applyUpgrade(gCards[pick]); gState = ST_PLAY; }
        } else if (gState == ST_OVER) {
            if ((down & KEY_TOUCH) || (down & KEY_A)) gState = ST_TITLE;
        }

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TextBufClear(gTxt);
        C2D_TargetClear(top, COL(0, 0, 0, 255));
        C2D_TargetClear(bot, COL(0, 0, 0, 255));

        C2D_SceneBegin(top);
        if (gState == ST_TITLE) {
            C2D_DrawRectSolid(0, 0, 0, TOP_W, TOP_H, COL(20, 60, 40, 255));
            text("PokéSurvivor 3DS", 200, 80, 1.1f, COL(255, 220, 90, 255), true);
            text("Prototipo nativo", 200, 130, 0.6f, COL(200, 230, 200, 255), true);
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
                C2D_DrawRectSolid(60, 196, 0.1f, 200, 32, COL(90, 190, 90, 255));
                snprintf(b, sizeof b, "Mejor: %02d:%02d", gBest / 60, gBest % 60);
                text(b, 160, 40, 0.5f, COL(170, 200, 255, 255), true);
                text("¡Jugar!", 160, 202, 0.7f, COL(255, 255, 255, 255), true);
                break;
            case ST_PLAY: drawBottomHud(); break;
            case ST_LEVELUP: drawCards(); break;
            case ST_OVER:
                snprintf(b, sizeof b, "Aguantaste %02d:%02d · KO %d", (int)gTime / 60, (int)gTime % 60, gKills);
                drawCentered("¡Has caído!", b, COL(255, 100, 100, 255));
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
