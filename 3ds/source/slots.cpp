// Máquina tragaperras del gacha (pantalla superior): tres rodillos con bolas por rareza.
#include "game.h"

static PullResult sR[10];
static int sN, sCur;
static float sT;
static bool sDone = true, sSfx[3];

u32 rarityColor(int r) {
    static const u32 c[6] = {0x445066, 0x9fb1c9, 0x5fe08a, 0x4fb4ff, 0xff9a3d, 0xc47bff};
    return COL((c[r] >> 16) & 255, (c[r] >> 8) & 255, c[r] & 255, 255);
}
static const char* rarityName(int r) {
    static const char* n[6] = {"", "Común", "Poco común", "Raro", "Épico", "Legendario"};
    return n[r];
}

static bool big(const PullResult& r) { return r.rarity >= 4 || r.shiny; }
// Instante en que se para cada rodillo del tirón actual.
static float stopAt(int reel) {
    bool one = sN == 1;
    float base = one ? 0.8f + reel * 0.5f : 0.22f + reel * 0.14f;
    if (reel == 2 && big(sR[sCur])) base += one ? 1.2f : 0.5f;
    return base;
}
static float holdT() { return sN == 1 ? 0.0f : 0.4f; }

void slotStart(const PullResult* r, int n) {
    sN = n > 10 ? 10 : n;
    for (int i = 0; i < sN; i++) sR[i] = r[i];
    sCur = 0; sT = 0; sDone = sN == 0;
    for (int i = 0; i < 3; i++) sSfx[i] = false;
}
bool slotBusy() { return !sDone; }
void slotSkip() { if (!sDone) { sCur = sN - 1; sT = stopAt(2) + 0.01f; sDone = true; for (int i = 0; i < 3; i++) sSfx[i] = true; } }

void slotUpdate(float dt) {
    if (sDone) return;
    sT += dt;
    for (int k = 0; k < 3; k++)
        if (!sSfx[k] && sT >= stopAt(k)) { sSfx[k] = true; sfxPlay(k == 2 && big(sR[sCur]) ? SFX_RARE : SFX_UI); }
    if (sT >= stopAt(2) + holdT()) {
        if (sCur + 1 >= sN) { sDone = true; return; }
        sCur++; sT = 0;
        for (int i = 0; i < 3; i++) sSfx[i] = false;
    }
}

static void gradV(float x, float y, float w, float h, float z, u32 a, u32 b) { C2D_DrawRectangle(x, y, z, w, h, a, a, b, b); }

static void ball(float cx, float cy, float z, int sym, float r) {
    if (sym >= 6) {                                  // shiny: estrella roja sobre fondo dorado
        C2D_DrawCircleSolid(cx, cy, z, r, COL(255, 215, 80, 255));
        C2D_DrawCircleSolid(cx, cy, z + 0.01f, r - 4, COL(120, 20, 40, 255));
        text("★", cx, cy - 12, 0.9f, COL(255, 90, 90, 255), true);
        return;
    }
    C2D_DrawCircleSolid(cx, cy, z, r, COL(20, 20, 30, 255));
    C2D_DrawCircleSolid(cx, cy, z + 0.01f, r - 3, rarityColor(sym));
    C2D_DrawRectSolid(cx - r + 3, cy - 2, z + 0.02f, 2 * r - 6, 4, COL(20, 20, 30, 255));
    C2D_DrawCircleSolid(cx, cy, z + 0.03f, 6, COL(245, 245, 245, 255));
    C2D_DrawCircleSolid(cx - r / 3, cy - r / 2.5f, z + 0.04f, 3, COL(255, 255, 255, 170));
}

static void drawCard(float x, float y, float w, float h, const PullResult& r, u64 ms, float sc) {
    C2D_DrawRectSolid(x, y, 0.44f, w, h, r.shiny ? COL(255, 215, 80, 255) : rarityColor(r.rarity));
    gradV(x + 2, y + 2, w - 4, h - 4, 0.46f, COL(34, 56, 110, 255), COL(12, 22, 52, 255));
    sprDraw(DEX_NUM[r.dex], 0, ms, false, x + w / 2, y + h * 0.62f, nullptr, sc, r.shiny);
    char b[48];
    snprintf(b, sizeof b, "%d★", r.rarity);
    text(b, x + 4, y + 1, 0.4f, rarityColor(r.rarity));
    if (r.shiny) text("★", x + w - 14, y + 1, 0.4f, COL(255, 90, 90, 255));
    bool small = h < 80;
    if (!small) text(pname(r.dex), x + w / 2, y + h - 30, 0.32f, COL(255, 255, 255, 255), true);
    float ty = small ? y + h - 13 : y + h - 16;
    float ts = small ? 0.3f : 0.36f;
    if (r.isNew) text("¡NUEVO!", x + w / 2, ty, ts, COL(120, 255, 140, 255), true);
    else { snprintf(b, sizeof b, "+%d", r.refund); text(b, x + w / 2, ty, ts, COL(255, 220, 90, 255), true); }
}

void slotDraw(u64 ms) {
    gradV(0, 0, TOP_W, TOP_H, 0.0f, COL(10, 20, 48, 255), COL(24, 44, 96, 255));
    // 10 tiradas terminadas: sólo el resumen, a tamaño grande
    if (sDone && sN > 1) {
        text("¡Resultados!", TOP_W / 2, 0, 0.5f, COL(255, 232, 130, 255), true);
        for (int i = 0; i < sN; i++) drawCard(6 + (i % 5) * 79, 22 + (i / 5) * 109, 76, 105, sR[i], ms, 1.0f);
        return;
    }
    const u32 GOLDC = COL(214, 164, 40, 255), RED = COL(184, 58, 64, 255), DARK = COL(26, 8, 24, 255);
    const float mx = 22, mw = 204;
    // cuerpo de la máquina
    C2D_DrawRectSolid(mx - 2, 40, 0.1f, mw + 4, 192, COL(40, 14, 26, 255));
    C2D_DrawRectSolid(mx, 42, 0.12f, mw, 186, RED);
    C2D_DrawRectSolid(mx, 42, 0.13f, 10, 186, COL(224, 108, 104, 255));
    C2D_DrawRectSolid(mx, 214, 0.13f, mw, 14, COL(130, 40, 50, 255));
    // rótulo con bombillas
    C2D_DrawRectSolid(mx + 6, 4, 0.5f, mw - 12, 42, GOLDC);
    C2D_DrawRectSolid(mx + 10, 8, 0.51f, mw - 20, 34, DARK);
    for (int i = 0; i < 14; i++) {
        bool on = ((ms / 200) + i) % 2 == 0;
        float lx = mx + 9 + i * ((mw - 24) / 13.0f);
        C2D_DrawRectSolid(lx, 4, 0.52f, 5, 4, on ? COL(255, 240, 170, 255) : COL(120, 84, 24, 255));
        C2D_DrawRectSolid(lx, 42, 0.52f, 5, 4, on ? COL(120, 84, 24, 255) : COL(255, 240, 170, 255));
    }
    text("POKÉ SLOTS", mx + mw / 2, 12, 0.6f, COL(255, 214, 70, 255), true);
    // ventana de rodillos
    const float wx = mx + 14, wy = 56, ww = mw - 28, wh = 76;
    C2D_DrawRectSolid(wx - 4, wy - 4, 0.2f, ww + 8, wh + 8, GOLDC);
    C2D_DrawRectSolid(wx - 2, wy - 2, 0.21f, ww + 4, wh + 4, DARK);
    const float rw = ww / 3;
    for (int k = 0; k < 3; k++) C2D_DrawRectSolid(wx + rw * k + 1, wy, 0.22f, rw - 2, wh, COL(244, 238, 224, 255));
    bool have = sN > 0 && sCur < sN;
    for (int k = 0; k < 3; k++) {
        float cx = wx + rw * k + rw / 2;
        bool stopped = have && sT >= stopAt(k);
        bool spinning = have && !stopped;
        if (spinning) {
            const float step = 46;
            float pos = sT * 520 + k * 31;
            float off = fmodf(pos, step);
            int base = (int)(pos / step);
            for (int j = -1; j <= 2; j++) {
                int sym = (int)(hash2(k, base - j, 9) % 5) + 1;
                ball(cx, wy + wh / 2 + (j - 1) * step + off, 0.3f, sym, 16);
            }
        } else if (have) {
            const PullResult& r = sR[sCur];
            ball(cx, wy + wh / 2, 0.3f, r.shiny ? 6 : r.rarity, 18);
        } else ball(cx, wy + wh / 2, 0.3f, 1, 16);
        C2D_DrawRectSolid(wx + rw * k + 1, wy, 0.38f, rw - 2, 6, COL(190, 184, 170, 255));
        C2D_DrawRectSolid(wx + rw * k + 1, wy + wh - 6, 0.38f, rw - 2, 6, COL(190, 184, 170, 255));
    }
    // máscaras para recortar los rodillos en movimiento
    C2D_DrawRectSolid(wx - 4, wy - 50, 0.4f, ww + 8, 46, RED);
    C2D_DrawRectSolid(wx - 4, wy + wh + 4, 0.4f, ww + 8, 50, RED);
    // pantallita de estado
    C2D_DrawRectSolid(mx + 34, 142, 0.2f, mw - 68, 26, DARK);
    C2D_DrawRectSolid(mx + 14, 146, 0.2f, 12, 12, COL(110, 220, 140, 255));
    C2D_DrawRectSolid(mx + mw - 26, 146, 0.2f, 12, 12, COL(250, 206, 70, 255));
    char b[48];
    if (have && sT >= stopAt(2)) {
        const PullResult& r = sR[sCur];
        text(r.shiny ? T("¡SHINY!") : T(rarityName(r.rarity)), mx + mw / 2, 144, 0.5f, r.shiny ? COL(255, 130, 130, 255) : rarityColor(r.rarity), true);
    } else if (have) text("…", mx + mw / 2, 144, 0.5f, COL(255, 214, 70, 255), true);
    else text("¡Buena suerte!", mx + mw / 2, 144, 0.46f, COL(255, 214, 70, 255), true);
    // bandeja de salida
    C2D_DrawRectSolid(mx + 18, 178, 0.2f, mw - 36, 32, COL(40, 14, 26, 255));
    C2D_DrawRectSolid(mx + 20, 180, 0.21f, mw - 40, 28, COL(10, 6, 20, 255));
    C2D_DrawRectSolid(mx + 20, 204, 0.22f, mw - 40, 3, COL(140, 150, 170, 255));
    if (sN > 1 && have) { snprintf(b, sizeof b, "%d/%d", sCur + 1, sN); text(b, mx + mw / 2, 184, 0.5f, COL(255, 255, 255, 255), true); }
    // palanca
    float lever = (have && sT < 0.25f) ? sT * 4 : (have ? 1 : 0);
    if (have && sT > 0.45f) lever = 0;
    float lx = mx + mw + 8;
    C2D_DrawRectSolid(lx + 4, 70, 0.1f, 6, 60, COL(150, 160, 180, 255));
    C2D_DrawRectSolid(lx, 124, 0.1f, 14, 28, COL(190, 200, 215, 255));
    C2D_DrawCircleSolid(lx + 7, 66 + lever * 40, 0.2f, 9, COL(236, 66, 70, 255));

    // resultado de la tirada actual
    if (sDone && sN == 1) drawCard(266, 30, 124, 170, sR[0], ms, 1.7f);
    else if (have && sT >= stopAt(2)) drawCard(266, 30, 124, 170, sR[sCur], ms, 1.7f);
}
