// PokéSurvivor 3DS — bucle principal y pantallas (superior: mundo / información; táctil: controles y menús).
#include "game.h"

enum State { ST_MENU, ST_SELECT, ST_STARTMOVE, ST_LOADOUT, ST_PLAY, ST_PAUSE, ST_LEVELUP, ST_OVER, ST_SHOP, ST_GACHA, ST_BAN, ST_LOADING };
static State gState = ST_MENU;
static const u32 BTN_KEYS[4] = {KEY_X, KEY_Y, KEY_B, KEY_A};
static const char* BTN_NAMES[4] = {"X", "Y", "B", "A"};
static const u32 BG = COL(28, 36, 64, 255), PANEL = COL(20, 30, 70, 255), EDGE = COL(70, 110, 200, 255), WHITE = COL(255, 255, 255, 255);

static touchPosition gTp;
static bool gTap, gTouching;
static int gSel;
static int gPage, gShopPage, gGen = 1, gBanPage;
static int gStartChoice[2], gNStart;
static int gSelBtn = 3, gSelMove = -1;
static CardSet gCards;
static float gMsgT;
static char gMsg[64];
static PullResult gPulls[10];
static int gNPulls, gShown;
static float gRevealT;
static RunStats gRun;
static bool gNewBest, gAfterPause;
static char gTmp[96];

static void msg(const char* s) { snprintf(gMsg, sizeof gMsg, "%s", s); gMsgT = 2.2f; }
static bool tapIn(float x, float y, float w, float h) { return gTap && inRect(gTp.px, gTp.py, x, y, w, h); }
static void panel(float x, float y, float w, float h, u32 edge, u32 fill = PANEL) {
    C2D_DrawRectSolid(x, y, 0.1f, w, h, edge);
    C2D_DrawRectSolid(x + 2, y + 2, 0.2f, w - 4, h - 4, fill);
}
static bool button(float x, float y, float w, float h, const char* label, u32 bg, float sc = 0.5f) {
    C2D_DrawRectSolid(x, y, 0.1f, w, h, bg);
    C2D_DrawRectSolid(x, y, 0.15f, w, 2, COL(255, 255, 255, 60));
    text(label, x + w / 2, y + h / 2 - 9 * sc / 0.5f, sc, WHITE, true);
    return tapIn(x, y, w, h);
}
static void bgFill() { C2D_DrawRectSolid(0, 0, 0, 320, 240, BG); }
static void topBg() { C2D_DrawRectSolid(0, 0, 0, TOP_W, TOP_H, COL(20, 40, 70, 255)); }
static void typeChip(float x, float y, int t) {
    if (t == 255) return;
    C2D_DrawRectSolid(x, y, 0.3f, 56, 14, typeColorDark(t));
    C2D_DrawRectSolid(x + 1, y + 1, 0.35f, 54, 12, typeColor(t));
    text(TYPE_NAMES[t], x + 28, y - 3, 0.36f, WHITE, true);
}

static int ownedList(int* out) {
    int n = 0;
    for (int i = 0; i < DEX_N; i++) if (gSave.owned[i] && sprHas(DEX_NUM[i])) out[n++] = i;
    return n;
}
static int poolFor(int di, int* out) {
    static bool seen[NMOVES];
    memset(seen, 0, sizeof seen);
    int n = 0;
    const DexE& p = DEX[di];
    int ts[2] = {p.t1, p.t2};
    for (int k = 0; k < 2; k++) {
        if (ts[k] == 255) continue;
        const PoolRef& r = POOL_BY_TYPE[ts[k]];
        for (int i = 0; i < r.n; i++) { int m = POOL_ALL[r.off + i]; if (!seen[m] && !gSave.bannedMove[m]) { seen[m] = true; out[n++] = m; } }
    }
    return n;
}
static int defaultStart(int di) {
    if (gSave.startMove[di] && permLv(PU_START) > 0) return gSave.startMove[di] - 1;
    return DEX[di].start;
}

static void beginRun() {
    int n = 1;
    gStartChoice[1] = -1;
    if (permLv(PU_MOVES) > 0) {
        int pool[NMOVES];
        int np = poolFor(gSel, pool);
        for (int tries = 0; tries < 30 && np; tries++) {
            int m = pool[rnd() % np];
            if (m != gStartChoice[0] && MOVES[m].kind != MK_ORBIT) { gStartChoice[1] = m; n = 2; break; }
        }
    }
    gNStart = n;
    gState = ST_LOADING;
}
static void doLoadRun() {
    sprFreeAll();
    playReset(gSel, gStartChoice, gNStart);
    playPreloadSprites();
    gSave.lastChar = gSel;
    musicPlay(MUS_BATTLE);
    gState = ST_PLAY;
}

static void drawMenu() {
    bgFill();
    text("PokéSurvivor", 160, 4, 0.8f, COL(255, 220, 90, 255), true);
    snprintf(gTmp, sizeof gTmp, "%d Pokémonedas · %d tickets · %d ×10", gSave.coins, gSave.t1, gSave.t10);
    text(gTmp, 160, 36, 0.42f, COL(200, 220, 255, 255), true);
    if (button(40, 60, 240, 34, "¡Jugar!", COL(60, 170, 80, 255), 0.7f)) {
        int l[DEX_N];
        int n = ownedList(l);
        if (!(gSave.lastChar >= 0 && gSave.lastChar < DEX_N && gSave.owned[gSave.lastChar])) gSel = n ? l[0] : 0;
        else gSel = gSave.lastChar;
        gPage = 0;
        for (int i = 0; i < n; i++) if (l[i] == gSel) gPage = i / 12;
        gState = ST_SELECT;
        sfxPlay(SFX_UI);
    }
    if (button(40, 102, 114, 30, "Mejoras", EDGE, 0.55f)) { gState = ST_SHOP; gShopPage = 0; sfxPlay(SFX_UI); }
    if (button(166, 102, 114, 30, "Gacha", COL(150, 80, 200, 255), 0.55f)) { gState = ST_GACHA; gNPulls = gShown = 0; sfxPlay(SFX_UI); }
    if (permLv(PU_BAN) > 0 && button(40, 140, 240, 28, "Vetar movimientos", COL(160, 80, 80, 255), 0.5f)) { gState = ST_BAN; gBanPage = 0; }
    snprintf(gTmp, sizeof gTmp, "Mejor tiempo %02d:%02d · Partidas %d · KO %d", gSave.best / 60, gSave.best % 60, gSave.runs, gSave.kills);
    text(gTmp, 160, 178, 0.4f, COL(170, 200, 255, 255), true);
    int own = 0;
    for (int i = 0; i < DEX_N; i++) own += gSave.owned[i];
    snprintf(gTmp, sizeof gTmp, "Colección %d/%d · Volumen %d%% (L/R)", own, DEX_N, (int)(gSave.vol * 100 + 0.5f));
    text(gTmp, 160, 196, 0.4f, COL(170, 200, 255, 255), true);
    text("START: salir", 160, 218, 0.38f, COL(120, 140, 190, 255), true);
}
static void drawMenuTop(u64 ms) {
    topBg();
    text("PokéSurvivor 3DS", 200, 20, 1.0f, COL(255, 220, 90, 255), true);
    text("Sobrevive 15 minutos", 200, 64, 0.55f, COL(200, 230, 200, 255), true);
    int l[DEX_N];
    int n = ownedList(l);
    if (n) {
        int di = (gSave.lastChar >= 0 && gSave.lastChar < DEX_N && gSave.owned[gSave.lastChar]) ? gSave.lastChar : l[0];
        sprDraw(DEX_NUM[di], 0, ms, true, 200, 175, nullptr, 2.0f);
        text(DEX[di].name, 200, 186, 0.5f, WHITE, true);
    }
}

static void drawSelectBottom(u64 ms) {
    bgFill();
    int l[DEX_N];
    int n = ownedList(l);
    int pages = (n + 11) / 12;
    if (gPage >= pages) gPage = pages - 1;
    if (gPage < 0) gPage = 0;
    for (int k = 0; k < 12; k++) {
        int idx = gPage * 12 + k;
        if (idx >= n) break;
        int di = l[idx];
        float x = 6 + (k % 4) * 78, y = 4 + (k / 4) * 60;
        panel(x, y, 74, 56, di == gSel ? COL(255, 220, 90, 255) : EDGE, di == gSel ? COL(40, 60, 120, 255) : PANEL);
        sprDraw(DEX_NUM[di], 0, ms, false, x + 37, y + 46, nullptr, 1.0f);
        if (tapIn(x, y, 74, 56)) { gSel = di; sfxPlay(SFX_UI); }
    }
    snprintf(gTmp, sizeof gTmp, "%d/%d", gPage + 1, pages > 0 ? pages : 1);
    text(gTmp, 160, 186, 0.4f, COL(170, 200, 255, 255), true);
    if (button(6, 200, 50, 34, "◀", EDGE, 0.7f) && gPage > 0) gPage--;
    if (button(264, 200, 50, 34, "▶", EDGE, 0.7f) && gPage < pages - 1) gPage++;
    if (button(62, 204, 80, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (button(148, 204, 110, 30, "Elegir", COL(60, 170, 80, 255), 0.55f)) {
        gStartChoice[0] = defaultStart(gSel);
        if (permLv(PU_START) > 0) { gState = ST_STARTMOVE; gBanPage = 0; }
        else { gSelBtn = 3; gSelMove = -1; gAfterPause = false; gState = ST_LOADOUT; }
        sfxPlay(SFX_UI);
    }
}
static void drawSelectTop(u64 ms) {
    topBg();
    const DexE& p = DEX[gSel];
    text("Elige tu Pokémon", 200, -2, 0.6f, COL(255, 220, 90, 255), true);
    sprDraw(DEX_NUM[gSel], 0, ms, true, 90, 150, nullptr, 2.4f);
    text(p.name, 90, 160, 0.6f, WHITE, true);
    typeChip(190, 40, p.t1);
    typeChip(252, 40, p.t2);
    snprintf(gTmp, sizeof gTmp, "PS %d    Velocidad %d", p.hp, p.spd); text(gTmp, 190, 62, 0.45f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Ataque %d    Atq.Esp %d", (int)(p.pa * 100), (int)(p.sa * 100)); text(gTmp, 190, 82, 0.45f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Defensa %d    Def.Esp %d", p.df, p.sd); text(gTmp, 190, 102, 0.45f, WHITE);
    int dm = defaultStart(gSel);
    snprintf(gTmp, sizeof gTmp, "Mov. inicial: %s", MOVES[dm].name); text(gTmp, 190, 128, 0.45f, typeColorLight(MOVES[dm].type));
    if (p.t2 == 255) text("Monotipo: +20% con ataques de su tipo", 190, 150, 0.36f, COL(255, 230, 120, 255));
    textWrap(MOVES[dm].desc, 190, 170, 200, 0.38f, COL(170, 200, 255, 255));
}

static void drawStartMove() {
    bgFill();
    text("Elige tu movimiento inicial", 160, 0, 0.55f, COL(255, 230, 120, 255), true);
    int pool[NMOVES];
    int np = poolFor(gSel, pool);
    int pages = (np + 9) / 10;
    if (gBanPage >= pages) gBanPage = pages - 1;
    if (gBanPage < 0) gBanPage = 0;
    for (int k = 0; k < 10; k++) {
        int idx = gBanPage * 10 + k;
        if (idx >= np) break;
        int m = pool[idx];
        float x = 6 + (k % 2) * 158, y = 22 + (k / 2) * 34;
        panel(x, y, 154, 30, typeColor(MOVES[m].type), m == gStartChoice[0] ? COL(50, 70, 130, 255) : PANEL);
        text(MOVES[m].name, x + 6, y + 4, 0.45f, WHITE);
        if (tapIn(x, y, 154, 30)) { gStartChoice[0] = m; gSave.startMove[gSel] = (u8)(m + 1); sfxPlay(SFX_UI); }
    }
    if (button(6, 204, 50, 30, "◀", EDGE, 0.6f) && gBanPage > 0) gBanPage--;
    if (button(60, 204, 50, 30, "▶", EDGE, 0.6f) && gBanPage < pages - 1) gBanPage++;
    if (button(116, 204, 90, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_SELECT;
    if (button(212, 204, 100, 30, "Continuar", COL(60, 170, 80, 255), 0.5f)) { gSelBtn = 3; gSelMove = -1; gAfterPause = false; gState = ST_LOADOUT; }
}
static void drawStartTop() {
    topBg();
    int m = gStartChoice[0];
    text(MOVES[m].name, 200, 30, 0.8f, typeColorLight(MOVES[m].type), true);
    textWrap(MOVES[m].desc, 40, 90, 320, 0.5f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Tipo %s · %s", TYPE_NAMES[MOVES[m].type], MOVES[m].cat == 0 ? "Físico" : MOVES[m].cat == 1 ? "Especial" : "Estado");
    text(gTmp, 200, 160, 0.5f, COL(170, 200, 255, 255), true);
}

// Asignación de movimientos a los botones X/Y/B/A (antes de la partida o en pausa).
static void drawLoadoutBottom() {
    bgFill();
    text("Toca dos botones para intercambiarlos", 160, 0, 0.45f, COL(255, 230, 120, 255), true);
    for (int i = 0; i < 4; i++) {
        float x = 8 + i * 78, y = 22;
        bool has = gMoves[i].id >= 0;
        u32 c = has ? typeColor(MOVES[gMoves[i].id].type) : EDGE;
        panel(x, y, 72, 64, i == gSelMove ? COL(255, 255, 255, 255) : c);
        text(BTN_NAMES[i], x + 5, y + 1, 0.6f, c);
        if (has) {
            textWrap(MOVES[gMoves[i].id].name, x + 6, y + 26, 62, 0.36f, WHITE);
            snprintf(gTmp, sizeof gTmp, "Nv %d", gMoves[i].lvl);
            text(gTmp, x + 66, y + 1, 0.4f, COL(255, 230, 120, 255), true);
        } else text("vacío", x + 36, y + 24, 0.4f, COL(120, 140, 190, 255), true);
        if (tapIn(x, y, 72, 64)) {
            if (gSelMove >= 0 && gSelMove != i) { playSwapSlots(gSelMove, i); gSelMove = -1; }
            else gSelMove = gSelMove == i ? -1 : i;
            gSelBtn = i;
            sfxPlay(SFX_UI);
        }
    }
    if (gMoves[gSelBtn].id >= 0) {
        const MoveDef& d = MOVES[gMoves[gSelBtn].id];
        text(d.name, 160, 94, 0.55f, typeColorLight(d.type), true);
        textWrap(d.desc, 20, 118, 280, 0.42f, WHITE);
        snprintf(gTmp, sizeof gTmp, "Recarga %.1f s · %s", gMoves[gSelBtn].v[K_CD], d.cat == 0 ? "Físico" : d.cat == 1 ? "Especial" : "Estado");
        text(gTmp, 160, 160, 0.4f, COL(170, 200, 255, 255), true);
    }
    if (button(8, 196, 98, 36, gAuto ? "Auto: SÍ" : "Auto: NO", EDGE, 0.5f)) gAuto = !gAuto;
    if (button(114, 196, 100, 36, gAfterPause ? "Seguir" : "¡Jugar!", COL(60, 170, 80, 255), 0.6f)) {
        if (gAfterPause) { gState = ST_PLAY; gAfterPause = false; }
        else beginRun();
    }
    if (button(222, 196, 90, 36, gAfterPause ? "Abandonar" : "Volver", COL(180, 80, 80, 255), 0.45f)) {
        if (gAfterPause) { gRun = playStats(); gNewBest = false; gAfterPause = false; gState = ST_OVER; musicPlay(MUS_MENU); }
        else gState = ST_SELECT;
    }
}
static void drawLoadoutTop(u64 ms) {
    topBg();
    text(gAfterPause ? "Pausa" : "Tus movimientos", 200, -2, 0.6f, COL(255, 220, 90, 255), true);
    sprDraw(DEX_NUM[gSel], 0, ms, true, 75, 140, nullptr, 2.0f);
    for (int i = 0; i < 4; i++) {
        float y = 30 + i * 44;
        if (gMoves[i].id < 0) continue;
        const MoveDef& d = MOVES[gMoves[i].id];
        C2D_DrawRectSolid(150, y, 0.2f, 240, 38, typeColorDark(d.type));
        C2D_DrawRectSolid(152, y + 2, 0.25f, 236, 34, COL(14, 26, 50, 255));
        text(BTN_NAMES[i], 158, y + 6, 0.55f, typeColorLight(d.type));
        text(d.name, 184, y + 2, 0.5f, WHITE);
        snprintf(gTmp, sizeof gTmp, "Nv %d · %s", gMoves[i].lvl, d.cat == 0 ? "Físico" : d.cat == 1 ? "Especial" : "Estado");
        text(gTmp, 184, y + 20, 0.36f, COL(170, 200, 255, 255));
    }
    if (gAfterPause) {
        snprintf(gTmp, sizeof gTmp, "%s · Nv %d · %02d:%02d", DEX[gSel].name, playLevel(), (int)playTime() / 60, (int)playTime() % 60);
        text(gTmp, 75, 200, 0.4f, WHITE, true);
    }
}

// ---------------------------------------------------------------- partida
static bool gJoy;
static float gJx0, gJy0;
static void readJoy(int& jx, int& jy, u32 held) {
    circlePosition cp;
    hidCircleRead(&cp);
    float x = cp.dx / 140.0f, y = -cp.dy / 140.0f;
    if (held & KEY_DLEFT) x = -1;
    if (held & KEY_DRIGHT) x = 1;
    if (held & KEY_DUP) y = -1;
    if (held & KEY_DDOWN) y = 1;
    if (gTouching) {
        if (!gJoy && gTp.py < 168) { gJoy = true; gJx0 = gTp.px; gJy0 = gTp.py; }
        if (gJoy) {
            float dx = gTp.px - gJx0, dy = gTp.py - gJy0, l = sqrtf(dx * dx + dy * dy);
            if (l > 50) { gJx0 += dx / l * (l - 50); gJy0 += dy / l * (l - 50); dx = gTp.px - gJx0; dy = gTp.py - gJy0; l = 50; }
            if (l > 6) { x = dx / 50; y = dy / 50; }
        }
    } else gJoy = false;
    jx = (int)(clampf(x, -1, 1) * 100);
    jy = (int)(clampf(y, -1, 1) * 100);
}
static void drawPlayBottom() {
    bgFill();
    char b[64];
    snprintf(b, sizeof b, "Nv %d", playLevel()); text(b, 8, 0, 0.55f, WHITE);
    int secs = (int)playTime();
    snprintf(b, sizeof b, "%02d:%02d", secs / 60, secs % 60); text(b, 160, 0, 0.55f, WHITE, true);
    snprintf(b, sizeof b, "KO %d", playKills()); text(b, 312, 0, 0.55f, COL(255, 230, 120, 255), true);
    C2D_DrawRectSolid(8, 26, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 26, 0.2f, 304 * clampf(playXpFrac(), 0, 1), 8, COL(80, 180, 255, 255));
    C2D_DrawRectSolid(8, 38, 0.1f, 304, 8, COL(0, 0, 0, 160));
    C2D_DrawRectSolid(8, 38, 0.2f, 304 * clampf(playHpFrac(), 0, 1), 8, COL(90, 220, 90, 255));
    for (int i = 0; i < 4; i++) {
        float x = 8 + i * 78, y = 172;
        bool has = gMoves[i].id >= 0;
        panel(x, y, 72, 50, has ? typeColorDark(MOVES[gMoves[i].id].type) : EDGE);
        if (!has) continue;
        u32 c = typeColor(MOVES[gMoves[i].id].type);
        float rdy = 1 - playCdFrac(i);
        C2D_DrawRectSolid(x + 3, y + 43, 0.3f, 66 * clampf(rdy, 0, 1), 4, rdy >= 1 ? COL(255, 255, 255, 255) : c);
        text(BTN_NAMES[i], x + 5, y, 0.6f, c);
        textWrap(MOVES[gMoves[i].id].name, x + 6, y + 22, 62, 0.34f, WHITE);
        snprintf(b, sizeof b, "Nv%d", gMoves[i].lvl);
        text(b, x + 66, y + 2, 0.34f, COL(255, 230, 120, 255), true);
        if (tapIn(x, y, 72, 50)) playFireButton(i);
    }
    text(gAuto ? "Auto" : "Manual", 40, 224, 0.4f, COL(150, 170, 220, 255), true);
    text("START: pausa / ordenar ataques", 210, 224, 0.4f, COL(150, 170, 220, 255), true);
    if (gTouching && gJoy) {
        C2D_DrawCircleSolid(gJx0, gJy0, 0.3f, 50, COL(255, 255, 255, 36));
        C2D_DrawCircleSolid(clampf(gTp.px, 0, 320), clampf(gTp.py, 0, 168), 0.4f, 18, COL(255, 255, 255, 140));
    } else text("Arrastra aquí para moverte", 160, 90, 0.4f, COL(90, 110, 160, 255), true);
}
static void drawLevelUp() {
    bgFill();
    snprintf(gTmp, sizeof gTmp, "¡Nivel %d! Elige una mejora", playLevel());
    text(gTmp, 160, 0, 0.6f, COL(255, 230, 120, 255), true);
    for (int i = 0; i < gCards.n; i++) {
        float y = 24 + i * 62;
        panel(8, y, 304, 58, gCards.c[i].col | 0xFF000000u);
        text(gCards.c[i].title, 18, y + 3, 0.5f, WHITE);
        textWrap(gCards.c[i].desc, 18, y + 26, 286, 0.38f, COL(170, 200, 255, 255));
        if (tapIn(8, y, 304, 58)) { playApplyCard(gCards.c[i]); sfxPlay(SFX_LEVEL); gState = ST_PLAY; return; }
    }
    snprintf(gTmp, sizeof gTmp, "Cambiar cartas (%d)", playRerolls());
    if (button(60, 212, 200, 24, gTmp, playRerolls() > 0 ? EDGE : COL(60, 60, 80, 255), 0.45f) && playRerolls() > 0) { playReroll(gCards); sfxPlay(SFX_UI); }
}

static void finishRun() {
    gRun = playStats();
    gNewBest = (int)gRun.time > gSave.best;
    gSave.coins += gRun.coins;
    gSave.t1 += gRun.t1;
    gSave.t10 += gRun.t10;
    if (gNewBest) gSave.best = (int)gRun.time;
    if (gRun.level > gSave.bestLevel) gSave.bestLevel = gRun.level;
    gSave.runs++;
    gSave.kills += gRun.kills;
    saveWrite();
    musicPlay(MUS_MENU);
}
static void drawOver() {
    bgFill();
    text(gRun.won ? "¡Victoria!" : "¡Has caído!", 160, 14, 0.9f, gRun.won ? COL(120, 255, 140, 255) : COL(255, 100, 100, 255), true);
    snprintf(gTmp, sizeof gTmp, "Tiempo %02d:%02d · Nivel %d · KO %d", (int)gRun.time / 60, (int)gRun.time % 60, gRun.level, gRun.kills);
    text(gTmp, 160, 60, 0.5f, WHITE, true);
    snprintf(gTmp, sizeof gTmp, "Jefes derrotados: %d", gRun.bosses);
    text(gTmp, 160, 84, 0.5f, WHITE, true);
    snprintf(gTmp, sizeof gTmp, "+%d Pokémonedas  +%d tickets", gRun.coins, gRun.t1 + gRun.t10 * 10);
    text(gTmp, 160, 112, 0.55f, COL(255, 220, 90, 255), true);
    if (gNewBest) text("¡Nuevo récord!", 160, 140, 0.6f, COL(120, 255, 140, 255), true);
    if (button(60, 180, 200, 40, "Continuar", COL(60, 170, 80, 255), 0.7f)) { gState = ST_MENU; sprFreeAll(); tilesFree(); }
}

// ---------------------------------------------------------------- mejoras permanentes
static void drawShop() {
    bgFill();
    snprintf(gTmp, sizeof gTmp, "Mejoras permanentes · %d Pokémonedas", gSave.coins);
    text(gTmp, 160, 0, 0.5f, COL(255, 220, 90, 255), true);
    for (int k = 0; k < 6; k++) {
        int i = gShopPage * 6 + k;
        if (i >= NPERM) break;
        float y = 22 + k * 31;
        int lv = gSave.perm[i];
        bool maxed = lv >= PERM[i].max;
        int cost = maxed ? 0 : permCost(i, lv);
        bool can = !maxed && gSave.coins >= cost;
        panel(6, y, 308, 28, maxed ? COL(90, 200, 120, 255) : can ? COL(255, 220, 90, 255) : EDGE);
        snprintf(gTmp, sizeof gTmp, "%s  %d/%d", PERM[i].name, lv, PERM[i].max);
        text(gTmp, 12, y + 1, 0.45f, WHITE);
        text(PERM[i].unit, 12, y + 15, 0.32f, COL(170, 200, 255, 255));
        if (maxed) text("MÁX", 300, y + 6, 0.5f, COL(120, 255, 160, 255), true);
        else { snprintf(gTmp, sizeof gTmp, "%d", cost); text(gTmp, 296, y + 6, 0.5f, can ? COL(255, 220, 90, 255) : COL(150, 150, 170, 255), true); }
        if (tapIn(6, y, 308, 28)) {
            if (can) { gSave.coins -= cost; gSave.perm[i]++; saveWrite(); sfxPlay(SFX_LEVEL); }
            else if (!maxed) { msg("No tienes suficientes Pokémonedas"); sfxPlay(SFX_HURT); }
        }
    }
    int pages = (NPERM + 5) / 6;
    if (button(6, 210, 60, 26, "◀", EDGE, 0.5f) && gShopPage > 0) gShopPage--;
    if (button(72, 210, 60, 26, "▶", EDGE, 0.5f) && gShopPage < pages - 1) gShopPage++;
    if (button(220, 210, 94, 26, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (gMsgT > 0) text(gMsg, 176, 196, 0.4f, COL(255, 120, 120, 255), true);
}
static void drawShopTop() {
    topBg();
    text("Mejoras", 200, -2, 0.7f, COL(255, 220, 90, 255), true);
    textWrap("Las mejoras compradas se aplican a todos tus Pokémon en cada partida. Consigue Pokémonedas jugando y con los duplicados del gacha.", 24, 50, 350, 0.46f, WHITE);
}

// ---------------------------------------------------------------- gacha
static u32 rarCol(int r) {
    static const u32 c[6] = {0, 0x9fb1c9, 0x5fe08a, 0x4fb4ff, 0xc47bff, 0xffcb3d};
    return COL((c[r] >> 16) & 255, (c[r] >> 8) & 255, c[r] & 255, 255);
}
static void drawGacha() {
    bgFill();
    snprintf(gTmp, sizeof gTmp, "Gacha — %s", GACHA_GEN_NAMES[gGen - 1]);
    text(gTmp, 160, 4, 0.65f, COL(220, 170, 255, 255), true);
    if (button(8, 34, 50, 30, "◀", EDGE, 0.7f) && gGen > 1) { gGen--; sfxPlay(SFX_UI); }
    if (button(262, 34, 50, 30, "▶", EDGE, 0.7f) && gGen < 9) { gGen++; sfxPlay(SFX_UI); }
    snprintf(gTmp, sizeof gTmp, "Garantía legendaria: %d/70", gSave.pity[gGen]);
    text(gTmp, 160, 40, 0.42f, COL(170, 200, 255, 255), true);
    snprintf(gTmp, sizeof gTmp, "Tickets %d · ×10: %d · Monedas %d", gSave.t1, gSave.t10, gSave.coins);
    text(gTmp, 160, 80, 0.42f, WHITE, true);
    text("1★ 45% · 2★ 30% · 3★ 17% · 4★ 6.5% · 5★ 1.5%", 160, 100, 0.34f, COL(150, 170, 220, 255), true);
    text("Los repetidos se convierten en Pokémonedas", 160, 114, 0.34f, COL(150, 170, 220, 255), true);
    bool ok1 = gSave.t1 >= 1, ok10 = gSave.t10 >= 1 || gSave.t1 >= 10;
    bool idle = gShown >= gNPulls;
    if (button(14, 140, 140, 44, "Tirar ×1", ok1 ? COL(150, 80, 200, 255) : COL(70, 60, 90, 255), 0.6f) && idle) {
        if (ok1) { gNPulls = gachaPull(gGen, 1, gPulls); gShown = 0; gRevealT = 0; saveWrite(); sfxPlay(SFX_GACHA); } else msg("Sin tickets");
    }
    if (button(166, 140, 140, 44, "Tirar ×10", ok10 ? COL(200, 90, 150, 255) : COL(70, 60, 90, 255), 0.6f) && idle) {
        if (ok10) { gNPulls = gachaPull(gGen, 10, gPulls); gShown = 0; gRevealT = 0; saveWrite(); sfxPlay(SFX_GACHA); } else msg("Necesitas 10 tickets o un ticket ×10");
    }
    if (gMsgT > 0) text(gMsg, 160, 190, 0.42f, COL(255, 120, 120, 255), true);
    if (button(100, 208, 120, 28, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
}
static void drawGachaTop(u64 ms, float dt) {
    topBg();
    text("Resultados", 200, -2, 0.6f, COL(220, 170, 255, 255), true);
    if (gShown < gNPulls) {
        gRevealT += dt;
        if (gRevealT > 0.22f) { gRevealT = 0; gShown++; sfxPlay(gPulls[gShown - 1].rarity >= 4 ? SFX_RARE : SFX_PICK); }
    }
    for (int i = 0; i < gShown; i++) {
        const PullResult& r = gPulls[i];
        float x = 40 + (i % 5) * 76, y = 26 + (i / 5) * 106;
        if (gNPulls == 1) { x = 162; y = 50; }
        C2D_DrawRectSolid(x, y, 0.2f, 72, 98, rarCol(r.rarity));
        C2D_DrawRectSolid(x + 2, y + 2, 0.25f, 68, 94, COL(14, 26, 50, 255));
        sprDraw(DEX_NUM[r.dex], 0, ms, false, x + 36, y + 60, nullptr, 1.2f);
        text(DEX[r.dex].name, x + 36, y + 64, 0.3f, WHITE, true);
        snprintf(gTmp, sizeof gTmp, "%d★", r.rarity);
        text(gTmp, x + 4, y + 2, 0.4f, rarCol(r.rarity));
        if (r.isNew) text("¡NUEVO!", x + 36, y + 80, 0.36f, COL(120, 255, 140, 255), true);
        else { snprintf(gTmp, sizeof gTmp, "+%d", r.refund); text(gTmp, x + 36, y + 80, 0.36f, COL(255, 220, 90, 255), true); }
    }
}

// ---------------------------------------------------------------- vetar movimientos
static void drawBan() {
    bgFill();
    int used = 0;
    for (int i = 0; i < NMOVES; i++) used += gSave.bannedMove[i];
    snprintf(gTmp, sizeof gTmp, "Vetar movimientos %d/%d", used, permLv(PU_BAN));
    text(gTmp, 160, 0, 0.55f, COL(255, 150, 150, 255), true);
    int pages = (NMOVES + 11) / 12;
    for (int k = 0; k < 12; k++) {
        int m = gBanPage * 12 + k;
        if (m >= NMOVES) break;
        float x = 6 + (k % 2) * 158, y = 22 + (k / 2) * 30;
        panel(x, y, 154, 27, gSave.bannedMove[m] ? COL(230, 60, 60, 255) : typeColor(MOVES[m].type));
        text(MOVES[m].name, x + 6, y + 3, 0.4f, WHITE);
        if (tapIn(x, y, 154, 27)) {
            if (gSave.bannedMove[m]) gSave.bannedMove[m] = 0;
            else if (used < permLv(PU_BAN)) gSave.bannedMove[m] = 1;
            else msg("Sin vetos libres");
            saveWrite();
        }
    }
    if (button(6, 206, 50, 28, "◀", EDGE, 0.5f) && gBanPage > 0) gBanPage--;
    if (button(60, 206, 50, 28, "▶", EDGE, 0.5f) && gBanPage < pages - 1) gBanPage++;
    if (button(220, 206, 94, 28, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (gMsgT > 0) text(gMsg, 160, 190, 0.4f, COL(255, 120, 120, 255), true);
}

int main() {
    gfxInitDefault();
    romfsInit();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    textInit();
    saveLoad();
    audioInit();
    musicPlay(MUS_MENU);
    gSel = gSave.lastChar >= 0 && gSave.lastChar < DEX_N ? gSave.lastChar : 0;

    u64 last = osGetTime();
    bool quit = false;
    while (aptMainLoop() && !quit) {
        hidScanInput();
        u32 down = hidKeysDown(), held = hidKeysHeld();
        gTouching = held & KEY_TOUCH;
        gTap = down & KEY_TOUCH;
        if (gTouching || gTap) hidTouchRead(&gTp);
        u64 now = osGetTime();
        float dt = clampf((now - last) / 1000.0f, 0.0f, 0.05f);
        last = now;
        if (gMsgT > 0) gMsgT -= dt;

        if (gState == ST_MENU) {
            if (down & KEY_START) quit = true;
            if (down & KEY_L) gSave.vol = clampf(gSave.vol - 0.1f, 0, 1);
            if (down & KEY_R) gSave.vol = clampf(gSave.vol + 0.1f, 0, 1);
        }
        if (gState == ST_PLAY && (down & KEY_START)) { gState = ST_PAUSE; gAfterPause = true; gSelBtn = 3; gSelMove = -1; gJoy = false; }
        else if (gState == ST_PAUSE && (down & KEY_START)) { gState = ST_PLAY; gAfterPause = false; }
        if (gState == ST_LOADOUT || gState == ST_PAUSE)
            for (int i = 0; i < 4; i++) if (down & BTN_KEYS[i]) {
                if (gSelMove >= 0 && gSelMove != i) { playSwapSlots(gSelMove, i); gSelMove = -1; }
                else gSelMove = gSelMove == i ? -1 : i;
                gSelBtn = i;
            }

        if (gState == ST_PLAY) {
            int jx = 0, jy = 0;
            readJoy(jx, jy, held);
            playUpdate(dt, down, held, jx, jy);
            if (playState() == PS_LEVELUP) { playBuildCards(gCards); gState = ST_LEVELUP; gJoy = false; }
            else if (playState() == PS_OVER || playState() == PS_WIN) { finishRun(); gState = ST_OVER; }
        }
        audioUpdate();

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        textFrame();
        C2D_TargetClear(top, COL(0, 0, 0, 255));
        C2D_TargetClear(bot, COL(0, 0, 0, 255));
        C2D_SceneBegin(top);
        switch (gState) {
            case ST_MENU: drawMenuTop(now); break;
            case ST_SELECT: drawSelectTop(now); break;
            case ST_STARTMOVE: drawStartTop(); break;
            case ST_LOADOUT: case ST_PAUSE: drawLoadoutTop(now); break;
            case ST_SHOP: drawShopTop(); break;
            case ST_GACHA: drawGachaTop(now, dt); break;
            case ST_BAN: topBg(); text("Elige los movimientos que no quieres ver", 200, 100, 0.5f, WHITE, true); break;
            case ST_LOADING: topBg(); text("Cargando…", 200, 100, 0.8f, WHITE, true); break;
            case ST_PLAY: case ST_LEVELUP: playDraw(now); break;
            case ST_OVER: topBg(); text(gRun.won ? "¡Victoria!" : "Fin de la partida", 200, 100, 0.9f, WHITE, true); break;
        }
        C2D_SceneBegin(bot);
        switch (gState) {
            case ST_MENU: drawMenu(); break;
            case ST_SELECT: drawSelectBottom(now); break;
            case ST_STARTMOVE: drawStartMove(); break;
            case ST_LOADOUT: case ST_PAUSE: drawLoadoutBottom(); break;
            case ST_SHOP: drawShop(); break;
            case ST_GACHA: drawGacha(); break;
            case ST_BAN: drawBan(); break;
            case ST_LOADING: bgFill(); text("Cargando…", 160, 100, 0.8f, WHITE, true); break;
            case ST_PLAY: drawPlayBottom(); break;
            case ST_LEVELUP: drawLevelUp(); break;
            case ST_OVER: drawOver(); break;
        }
        C3D_FrameEnd(0);

        if (gState == ST_LOADING) { doLoadRun(); last = osGetTime(); }
    }
    saveWrite();
    audioExit();
    sprFreeAll();
    tilesFree();
    C2D_Fini();
    C3D_Fini();
    romfsExit();
    gfxExit();
    return 0;
}
