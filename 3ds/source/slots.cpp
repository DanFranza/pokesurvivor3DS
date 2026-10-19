// Máquina tragaperras del gacha (pantalla superior): tres rodillos con bolas por rareza.
#include "game.h"

static PullResult sR[10];
static int sN, sCur;
static float sT;
static bool sDone = true, sSfx[3];

u32 rarityColor(int r) {
    static const u32 c[6] = {0x445066, 0x9fb1c9, 0x5fe08a, 0x4fb4ff, 0xc47bff, 0xffcb3d};
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
    const float mx = 14, my = 8, mw = 236, mh = 224;
    // cuerpo de la máquina
    C2D_DrawRectSolid(mx - 3, my - 3, 0.1f, mw + 6, mh + 6, COL(255, 210, 70, 255));
    gradV(mx, my, mw, mh, 0.12f, COL(214, 52, 56, 255), COL(130, 22, 36, 255));
    text("GACHA", mx + mw / 2, my + 2, 0.7f, COL(255, 232, 130, 255), true);
    // luces
    for (int i = 0; i < 12; i++) {
        bool on = ((ms / 180) + i) % 2 == 0;
        float lx = mx + 12 + i * ((mw - 24) / 11.0f);
        C2D_DrawCircleSolid(lx, my + 32, 0.2f, 4, on ? COL(255, 240, 150, 255) : COL(110, 60, 30, 255));
    }
    // ventana de rodillos
    const float wx = mx + 18, wy = my + 46, ww = mw - 36, wh = 82;
    C2D_DrawRectSolid(wx - 3, wy - 3, 0.2f, ww + 6, wh + 6, COL(255, 210, 70, 255));
    C2D_DrawRectSolid(wx, wy, 0.22f, ww, wh, COL(245, 240, 225, 255));
    const float rw = ww / 3;
    bool have = sN > 0 && sCur < sN;
    for (int k = 0; k < 3; k++) {
        float cx = wx + rw * k + rw / 2;
        if (k) C2D_DrawRectSolid(wx + rw * k - 1, wy, 0.3f, 2, wh, COL(150, 140, 120, 255));
        bool stopped = have && sT >= stopAt(k);
        bool spinning = have && !stopped;
        if (spinning) {
            const float step = 56;
            float pos = sT * 520 + k * 31;
            float off = fmodf(pos, step);
            int base = (int)(pos / step);
            for (int j = -1; j <= 2; j++) {
                int sym = (int)(hash2(k, base - j, 9) % 5) + 1;
                ball(cx, wy + wh / 2 + (j - 1) * step + off, 0.3f, sym, 20);
            }
        } else if (have) {
            const PullResult& r = sR[sCur];
            ball(cx, wy + wh / 2, 0.3f, r.shiny ? 6 : r.rarity, 22);
        } else ball(cx, wy + wh / 2, 0.3f, 1 + k, 20);
    }
    // máscaras arriba y abajo para recortar los rodillos en movimiento
    C2D_DrawRectSolid(wx - 3, wy - 60, 0.4f, ww + 6, 57, COL(160, 30, 40, 255));
    C2D_DrawRectSolid(wx - 3, wy + wh + 3, 0.4f, ww + 6, 60, COL(130, 22, 36, 255));
    C2D_DrawRectSolid(wx - 3, wy + wh / 2 - 1, 0.35f, ww + 6, 2, COL(255, 80, 80, 140));
    // texto de estado
    char b[48];
    if (have && sT >= stopAt(2)) {
        const PullResult& r = sR[sCur];
        text(r.shiny ? T("¡SHINY!") : T(rarityName(r.rarity)), mx + mw / 2, my + 140, 0.7f, r.shiny ? COL(255, 130, 130, 255) : rarityColor(r.rarity), true);
    } else if (have) text("…", mx + mw / 2, my + 140, 0.7f, COL(255, 255, 255, 255), true);
    else text("Tira de la palanca", mx + mw / 2, my + 146, 0.5f, COL(255, 232, 130, 255), true);
    if (sN > 1 && have) {
        snprintf(b, sizeof b, "%d/%d", sCur + 1, sN);
        text(b, mx + mw / 2, my + 184, 0.5f, COL(255, 255, 255, 255), true);
    }
    // palanca
    float lever = (have && sT < 0.25f) ? sT * 4 : (have ? 1 : 0);
    if (have && sT > 0.45f) lever = 0;
    C2D_DrawRectSolid(mx + mw + 10, my + 60, 0.1f, 8, 70, COL(150, 150, 160, 255));
    C2D_DrawCircleSolid(mx + mw + 14, my + 60 + lever * 56, 0.2f, 12, COL(240, 60, 70, 255));

    // tarjeta del resultado actual / resumen
    if (sDone && sN == 1) drawCard(268, 40, 120, 160, sR[0], ms, 1.6f);
    else if (sDone && sN > 1) {
        gradV(256, 4, 142, 232, 0.42f, COL(10, 20, 48, 255), COL(10, 20, 48, 255));
        for (int i = 0; i < sN; i++) drawCard(258 + (i % 2) * 70, 6 + (i / 2) * 45, 68, 43, sR[i], ms, 0.5f);
    } else if (have && sT >= stopAt(2)) drawCard(268, 40, 120, 160, sR[sCur], ms, 1.6f);
}
