// PokéSurvivor 3DS — bucle principal y pantallas (superior: mundo / información; táctil: controles y menús).
#include "game.h"

enum State { ST_MENU, ST_DEX, ST_STARTMOVE, ST_LOADOUT, ST_PLAY, ST_PAUSE, ST_LEVELUP, ST_OVER, ST_SHOP, ST_GACHA, ST_BAN, ST_LOADING, ST_LANG, ST_MISSIONS, ST_BOND, ST_ACH, ST_ITEM, ST_COOP, ST_COOPWAIT, ST_KECLEON };
static State gState = ST_MENU;
static const u32 BTN_KEYS[4] = {KEY_X, KEY_Y, KEY_B, KEY_A};
static const char* BTN_NAMES[4] = {"X", "Y", "B", "A"};
static const u32 BG = COL(14, 24, 56, 255), PANEL = COL(34, 66, 140, 255), EDGE = COL(61, 103, 192, 255), WHITE = COL(255, 255, 255, 255);
static const u32 GOLD = COL(255, 210, 63, 255), GOLD_BTN = COL(240, 175, 40, 255);

static touchPosition gTp;
static bool gTap, gTouching;
static int gSel;
static int gPage, gShopPage, gGen = 1, gBanPage;
static bool gPick2;
static int gKecPage, gKecSel = -1;
static int partner();
static int gMonMode, gMonPage;   // detalles del Pokémon: 0 = acciones · 1 = menta · 2 = habilidad · 3 = MT
static int gDexGen = 1, gDexPage, gDexSel, gDexTop, gDexSort;
static int gStartChoice[2], gNStart;
static int gSelBtn = 3, gSelMove = -1;
static CardSet gCards;
static float gMsgT;
static char gMsg[64];
static PullResult gPulls[10];
static int gNPulls;
static RunStats gRun;
static bool gNewBest, gAfterPause;
static char gTmp[96];
static int gAchNew, gAchCat, gAchPage;
static bool gBondSel[4];
// cooperativo local
static bool gCoop, gJoining, gCoopCards;
static int gCoopMe, gCoopErr, gCoopEnd;          // gCoopErr: 1 versiones distintas · 2 conexión perdida; gCoopEnd: 1 compañero salió · 2 desincronizado · 3 sin conexión
static CoopHello gCH[2];
static u32 gCoopSeed;
static float gAcc, gStall;
static u8 gCoopBtn;

static void msg(const char* s) { snprintf(gMsg, sizeof gMsg, "%s", s); gMsgT = 2.2f; }
// Navegación con botones: cada zona táctil se registra al dibujarse; la cruceta mueve el foco y A pulsa.
struct FocR { float x, y, w, h; };
static FocR gFoc[96], gFocPrev[96];
static int gFocN, gFocPrevN, gFocIdx = -1;
static bool gFocShow, gFocOn, gFocAct, gBotScene, gBackReq;
static u64 gFocMs;
static bool tapIn(float x, float y, float w, float h) {
    bool hit = gTap && inRect(gTp.px, gTp.py, x, y, w, h);
    if (!gBotScene || !gFocOn || gFocN >= 96) return hit;
    int i = gFocN++;
    gFoc[i] = {x, y, w, h};
    if (gFocShow && i == gFocIdx) {
        int a = 120 + (int)(110 * (0.5f + 0.5f * sinf(gFocMs * 0.012f)));
        u32 c = COL(255, 235, 90, 255), f = COL(255, 235, 90, 40);
        C2D_DrawRectSolid(x, y, 0.95f, w, h, f);
        C2D_DrawRectSolid(x - 2, y - 2, 0.96f, w + 4, 3, c);
        C2D_DrawRectSolid(x - 2, y + h - 1, 0.96f, w + 4, 3, c);
        C2D_DrawRectSolid(x - 2, y - 2, 0.96f, 3, h + 4, c);
        C2D_DrawRectSolid(x + w - 1, y - 2, 0.96f, 3, h + 4, c);
        C2D_DrawRectSolid(x + 1, y + 1, 0.97f, w - 2, 1, COL(255, 255, 255, a));
        C2D_DrawRectSolid(x + 1, y + h - 2, 0.97f, w - 2, 1, COL(255, 255, 255, a));
        if (gFocAct) { gFocAct = false; return true; }
    }
    return hit;
}
static void focusMove(u32 down) {
    int dx = (down & KEY_DRIGHT) ? 1 : (down & KEY_DLEFT) ? -1 : 0, dy = (down & KEY_DDOWN) ? 1 : (down & KEY_DUP) ? -1 : 0;
    if (!dx && !dy) return;
    gFocShow = true;
    if (gFocPrevN <= 0) return;
    if (gFocIdx < 0 || gFocIdx >= gFocPrevN) { gFocIdx = 0; return; }
    const FocR& a = gFocPrev[gFocIdx];
    float ax = a.x + a.w / 2, ay = a.y + a.h / 2, best = 1e9f;
    int bi = -1;
    for (int i = 0; i < gFocPrevN; i++) {
        if (i == gFocIdx) continue;
        float bx = gFocPrev[i].x + gFocPrev[i].w / 2 - ax, by = gFocPrev[i].y + gFocPrev[i].h / 2 - ay;
        float pri = dx ? bx * dx : by * dy, per = dx ? fabsf(by) : fabsf(bx);
        if (pri < 4) continue;
        float sc = pri + per * 2.5f;
        if (sc < best) { best = sc; bi = i; }
    }
    if (bi >= 0) gFocIdx = bi;
}
static u32 shade(u32 c, float k) {
    int r = (int)((c & 255) * k), g = (int)(((c >> 8) & 255) * k), b = (int)(((c >> 16) & 255) * k);
    return COL(r > 255 ? 255 : r, g > 255 ? 255 : g, b > 255 ? 255 : b, c >> 24);
}
static void gradRect(float x, float y, float w, float h, float z, u32 top, u32 bot) { C2D_DrawRectangle(x, y, z, w, h, top, top, bot, bot); }
// Caja azul con borde blanco/dorado, como las del juego web.
static const u32 INK = COL(27, 21, 40, 255);     // el contorno oscuro de los iconos y cajas de la web
// Caja pixel art como las de la web: contorno oscuro, marco de color, relleno degradado y esquinas cortadas.
static void panel(float x, float y, float w, float h, u32 edge, u32 fill = PANEL) {
    C2D_DrawRectSolid(x + 2, y, 0.08f, w - 4, h, INK);
    C2D_DrawRectSolid(x, y + 2, 0.08f, w, h - 4, INK);
    C2D_DrawRectSolid(x + 2, y + 1, 0.1f, w - 4, h - 2, edge);
    C2D_DrawRectSolid(x + 1, y + 2, 0.1f, w - 2, h - 4, edge);
    gradRect(x + 3, y + 3, w - 6, h - 6, 0.2f, shade(fill, 1.1f), shade(fill, 0.6f));
    C2D_DrawRectSolid(x + 3, y + 3, 0.21f, w - 6, 1, COL(255, 255, 255, 40));
}
// Botón con relieve (barra inferior más oscura) e icono opcional delante de la etiqueta.
static bool button(float x, float y, float w, float h, const char* label, u32 bg, float sc = 0.5f, int ic = -1) {
    bool press = gTouching && inRect(gTp.px, gTp.py, x, y, w, h);
    float dy = press ? 2 : 0;
    C2D_DrawRectSolid(x + 2, y, 0.09f, w - 4, h, INK);
    C2D_DrawRectSolid(x, y + 2, 0.09f, w, h - 4, INK);
    C2D_DrawRectSolid(x + 1, y + 1 + dy, 0.1f, w - 2, h - 2 - dy, shade(bg, 0.55f));
    gradRect(x + 2, y + 2 + dy, w - 4, h - 7 - dy, 0.12f, shade(bg, 1.3f), shade(bg, 1.0f));
    C2D_DrawRectSolid(x + 2, y + 2 + dy, 0.15f, w - 4, 1, COL(255, 255, 255, 90));
    float tx = x + w / 2, ty = y + (h - 4 - textH(label, sc)) / 2 + dy;
    if (ic >= 0) {
        float isc = h >= 50 ? 1.0f : h >= 34 ? 0.75f : 0.5f, isz = 32 * isc;
        icon(ic, x + 6, y + (h - isz) / 2 + dy - 2, isc);
        tx += isz / 2 - 2;
    }
    text(label, tx, ty, sc, WHITE, true);
    if (gBackReq && (!strcmp(label, "Volver") || !strcmp(label, "Atrás"))) { gBackReq = false; return true; }
    return tapIn(x, y, w, h);
}
// Flecha ◀ / ▶ para pasar de página.
static bool arrowBtn(float x, float y, float w, float h, bool right, bool on = true) {
    bool press = on && gTouching && inRect(gTp.px, gTp.py, x, y, w, h);
    u32 bg = on ? EDGE : COL(40, 54, 96, 255);
    C2D_DrawRectSolid(x + 2, y, 0.09f, w - 4, h, INK);
    C2D_DrawRectSolid(x, y + 2, 0.09f, w, h - 4, INK);
    C2D_DrawRectSolid(x + 1, y + 1, 0.1f, w - 2, h - 2, shade(bg, 0.55f));
    gradRect(x + 2, y + 2 + (press ? 2 : 0), w - 4, h - 7, 0.12f, shade(bg, 1.3f), shade(bg, 1.0f));
    float isc = h >= 28 ? 0.75f : 0.5f, isz = 32 * isc;
    icon(right ? IC_RIGHT : IC_LEFT, x + (w - isz) / 2, y + (h - isz) / 2 - 2 + (press ? 2 : 0), isc, on ? 0xFFFFFFFF : COL(140, 140, 160, 255));
    return on && tapIn(x, y, w, h);
}
// Barra de título de una pantalla: icono + nombre sobre franja oscura.
static void headerBar(const char* title, int ic) {
    gradRect(0, 0, 320, 24, 0.3f, COL(8, 14, 36, 255), COL(20, 36, 84, 255));
    C2D_DrawRectSolid(0, 24, 0.31f, 320, 2, INK);
    C2D_DrawRectSolid(0, 22, 0.31f, 320, 2, EDGE);
    if (ic >= 0) icon(ic, 6, -3, 0.75f);
    text(title, ic >= 0 ? 34 : 10, -1, 0.55f, COL(120, 60, 0, 255));
    text(title, ic >= 0 ? 33 : 9, -2, 0.55f, GOLD);
}
// Monedas y tickets (icono + cifra), centrados en y.
static void currencyBar(float y, bool coins = true) {
    char a[16], b[16], c[16];
    snprintf(a, sizeof a, "%d", gSave.coins); snprintf(b, sizeof b, "%d", gSave.t1); snprintf(c, sizeof c, "%d", gSave.t10);
    float x = coins ? 12 : 60;
    if (coins) { icon(IC_COIN, x, y - 6, 0.5f); text(a, x + 18, y - 2, 0.42f, GOLD); x += 100; }
    icon(IC_TICKET, x, y - 6, 0.5f); text(b, x + 18, y - 2, 0.42f, WHITE); x += 70;
    icon(IC_TICKET10, x, y - 6, 0.5f); text(c, x + 18, y - 2, 0.42f, COL(220, 170, 255, 255));
}
static void bgFill() { gradRect(0, 0, 320, 240, 0, COL(10, 20, 48, 255), COL(26, 48, 104, 255)); }
static void topBg() { gradRect(0, 0, TOP_W, TOP_H, 0, COL(10, 20, 48, 255), COL(26, 48, 104, 255)); }
// Suelo de la "Pradera Eterna" como fondo de las pantallas superiores.
static bool gTileBgOk;                  // los tiles de la pradera están cargados para el fondo
static void tileBg() {
    if (!gTileBgOk) { tilesLoad(3); gTileBgOk = true; }
    const TileSet& ts = TILESETS[3];
    for (int j = 0; j < 8; j++) for (int i = 0; i < 13; i++) {
        u32 h = hash2(i, j, 5);
        tileDraw(ts.floor[(h >> 4) & 3], (float)(i * 32), (float)(j * 32), 0.05f);
    }
    C2D_DrawRectangle(0, 0, 0.06f, TOP_W, TOP_H, COL(0, 10, 40, 150), COL(0, 10, 40, 150), COL(0, 10, 40, 60), COL(0, 10, 40, 60));
}
static void logo(float cx, float y, float sc) {
    text("PokéSurvivor", cx + 2, y + 3, sc, COL(120, 60, 0, 255), true);
    text("PokéSurvivor", cx, y, sc, GOLD, true);
}
static void typeChip(float x, float y, int t) {
    if (t == 255) return;
    C2D_DrawRectSolid(x, y, 0.3f, 56, 14, typeColorDark(t));
    C2D_DrawRectSolid(x + 1, y + 1, 0.35f, 54, 12, typeColor(t));
    text(typeName(t), x + 28, y - 3, 0.36f, WHITE, true);
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
    int tg[NTM], nt = monTaughtMoves(di, tg);
    for (int i = 0; i < nt; i++) if (!seen[tg[i]] && !gSave.bannedMove[tg[i]]) { seen[tg[i]] = true; out[n++] = tg[i]; }
    return n;
}
// Segundo movimiento elegido (Mejoras → Segundo movimiento inicial, necesita Repertorio), o -1 = al azar.
static int pick2Of(int di, int first) {
    int m = gSave.startMove2[di] - 1;
    if (m < 0 || m == first || m >= NMOVES || !permLvOf(di, PU_START2) || !permLvOf(di, PU_MOVES) || MOVES[m].kind == MK_ORBIT) return -1;
    int pool[NMOVES], np = poolFor(di, pool);
    for (int i = 0; i < np; i++) if (pool[i] == m) return m;
    return -1;
}
static int defaultStart(int di) {
    if (gSave.startMove[di] && permLv(PU_START) > 0) return gSave.startMove[di] - 1;
    return DEX[di].start;
}

// El orden elegido en la pantalla de movimientos (puesto de cada ataque en X/Y/B/A).
static int gOrder[4] = {0, 1, 2, 3};
// Antes de enseñar los movimientos del compañero elegido: se prepara su partida (si no, saldrían los de la anterior).
static void prepareLoadout() {
    int n = 1;
    gStartChoice[1] = -1;
    int p2 = permLv(PU_MOVES) > 0 ? pick2Of(gSel, gStartChoice[0]) : -1;
    if (p2 >= 0) { gStartChoice[1] = p2; n = 2; }
    else if (permLv(PU_MOVES) > 0) {
        int pool[NMOVES];
        int np = poolFor(gSel, pool);
        for (int tries = 0; tries < 30 && np; tries++) {
            int m = pool[rnd() % np];
            if (m != gStartChoice[0] && MOVES[m].kind != MK_ORBIT) { gStartChoice[1] = m; n = 2; break; }
        }
    }
    gNStart = n;
    playReset(gSel, gStartChoice, gNStart);
    for (int i = 0; i < 4; i++) gOrder[i] = i;
    gSelBtn = 3; gSelMove = -1; gAfterPause = false;
}
static void beginRun() {
    if (gCoop) {
        CoopHello h; memset(&h, 0, sizeof h);
        h.di = gSel; h.shiny = gSave.shinyOn[gSel] && gSave.shiny[gSel]; h.nStart = gNStart;
        h.start[0] = gStartChoice[0]; h.start[1] = gStartChoice[1];
        for (int i = 0; i < NPERM; i++) h.perm[i] = (u8)permLvOf(gSel, i);
        h.nat = (u8)monNature(gSel); h.abil = (s16)monAbil(gSel);
        coopHelloSet(h);
        gCoopErr = 0;
        gState = ST_COOPWAIT;
        return;
    }
    gState = ST_LOADING;
}
static void doLoadRun() {
    sprFreeAll();
    gTileBgOk = false;
    if (gCoop) {
        playResetCoop(gCoopMe, gCH, gCoopSeed);
        coopRunBegin(gCoopMe);
        gAcc = gStall = 0; gCoopBtn = 0; gCoopCards = false; gCoopEnd = 0;
    } else
    {
        playReset(gSel, gStartChoice, gNStart);
        MoveInst keep[4];
        for (int i = 0; i < 4; i++) keep[i] = gMoves[i];
        for (int i = 0; i < 4; i++) gMoves[i] = keep[gOrder[i]];
    }
    playPreloadSprites();
    gSave.lastChar = gSel;
    musicPlay(MUS_BATTLE);
    gState = ST_PLAY;
}

// ---------------------------------------------------------------- tienda de Kecleon (menta, cápsulas y las MT del día)
static void drawKecleon() {
    bgFill();
    headerBar("Kecleon", IC_COIN);
    icon(IC_COIN, 232, 3, 0.5f);
    snprintf(gTmp, sizeof gTmp, "%d", gSave.coins);
    text(gTmp, 252, 1, 0.5f, GOLD);
    static const u32 bc[3] = {COL(70, 150, 90, 255), COL(70, 110, 190, 255), COL(150, 90, 190, 255)};
    static const char* const bn[3] = {"Menta", "Cápsula", "Cáp. oculta"};
    for (int i = 0; i < 3; i++) {
        float x = 6 + i * 104;
        panel(x, 30, 102, 62, gKecSel == 100 + i ? GOLD : EDGE, COL(26, 49, 112, 255));
        text(bn[i], x + 51, 30, 0.4f, WHITE, true);
        snprintf(gTmp, sizeof gTmp, "En bolsa: %d", gSave.bag[i]);
        text(gTmp, x + 51, 45, 0.32f, COL(170, 200, 255, 255), true);
        snprintf(gTmp, sizeof gTmp, "%d", BAG_PRICE[i]);
        if (button(x + 6, 60, 90, 26, gTmp, gSave.coins >= BAG_PRICE[i] ? bc[i] : COL(80, 84, 110, 255), 0.42f, IC_COIN)) {
            gKecSel = 100 + i;
            if (shopBuyItem(i)) sfxPlay(SFX_LEVEL); else { msg("No tienes suficientes Pokémonedas"); sfxPlay(SFX_HURT); }
        }
    }
    int tm[8], n = tmDaily(tm);
    text("MT del día", 6, 94, 0.4f, GOLD);
    int di = partner();
    for (int k = 0; k < n; k++) {
        float x = 6 + (k % 2) * 158, y = 112 + (k / 2) * 21;
        int t = tm[k];
        bool can = gSave.coins >= TM_PRICE[t];
        snprintf(gTmp, sizeof gTmp, "%s %d", MOVES[TM_MOVE[t]].name, TM_PRICE[t]);
        if (button(x, y, 154, 19, gTmp, can ? typeColor(MOVES[TM_MOVE[t]].type) : COL(80, 84, 110, 255), 0.3f)) {
            gKecSel = t;
            if (shopBuyTm(t)) sfxPlay(SFX_LEVEL); else { msg("No tienes suficientes Pokémonedas"); sfxPlay(SFX_HURT); }
        }
        if (gSave.tms[t]) { snprintf(gTmp, sizeof gTmp, "×%d", gSave.tms[t]); text(gTmp, x + 5, y + 2, 0.28f, COL(255, 255, 160, 255)); }
        if (monCanLearn(di, t)) C2D_DrawRectSolid(x + 148, y + 2, 0.4f, 4, 15, COL(120, 255, 140, 255));
    }
    text("Barra verde: tu compañero puede aprenderla", 6, 197, 0.3f, COL(120, 255, 140, 255));
    if (button(220, 204, 94, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (gMsgT > 0) text(gMsg, 110, 214, 0.38f, COL(255, 120, 120, 255), true);
}
static void drawKecleonTop() {
    topBg();
    tileBg();
    text("Tienda de Kecleon", 200, 4, 0.7f, GOLD, true);
    textWrap("Menta: cambia la naturaleza de un Pokémon. Cápsula: cambia su habilidad (la oculta necesita la cápsula oculta). Las MT enseñan movimientos que su tipo no le da; se usan en «Pokémon» → Detalles.", 24, 40, 352, 0.42f, WHITE);
    textWrap("La lista de 8 MT cambia cada día (según la fecha de la consola). Cada MT se gasta al enseñarla.", 24, 130, 352, 0.38f, COL(170, 200, 255, 255));
    if (gKecSel >= 100) textWrap(BAG_DESC[gKecSel - 100], 24, 170, 352, 0.4f, COL(255, 220, 120, 255));
    else if (gKecSel >= 0) textWrap(MOVES[TM_MOVE[gKecSel]].desc, 24, 170, 352, 0.4f, COL(255, 220, 120, 255));
}

// ---------------------------------------------------------------- idioma
static void drawLang() {
    bgFill();
    text("Idioma · Language · Langue", 160, 14, 0.6f, COL(255, 220, 90, 255), true);
    static const u32 cols[LANG_N] = {COL(200, 60, 60, 255), COL(60, 100, 200, 255), COL(60, 140, 200, 255), COL(60, 150, 90, 255), COL(60, 150, 70, 255), COL(190, 60, 60, 255), COL(150, 80, 170, 255)};
    for (int i = 0; i < LANG_N; i++) {
        float x = 12 + (i & 1) * 152, y = 36 + (i >> 1) * 44;
        bool cur = gSave.langSet && gSave.lang == i;
        C2D_DrawRectSolid(x - 2, y - 2, 0.05f, 148, 40, cur ? COL(255, 255, 255, 255) : COL(10, 20, 50, 255));
        if (button(x, y, 144, 36, LANG_NAMES[i], cols[i], 0.5f)) {
            gSave.lang = (u8)i; gSave.langSet = 1; textSetLang(); saveWrite(); sfxPlay(SFX_UI);
            gState = ST_MENU;
        }
    }
    if (gSave.langSet && button(100, 212, 120, 24, "Volver", COL(180, 80, 80, 255), 0.45f)) gState = ST_MENU;
}

static bool validPartner(int d) { return d >= 0 && d < DEX_N && gSave.owned[d] && sprHas(DEX_NUM[d]); }
static int partner() {
    if (validPartner(gSave.lastChar)) return gSave.lastChar;
    int l[DEX_N];
    int n = ownedList(l);
    return n ? l[0] : 0;
}
static void startRun() {                       // «Jugar»: sale con el compañero elegido en «Pokémon»
    gSel = partner();
    gStartChoice[0] = defaultStart(gSel);
    if (permLv(PU_START) > 0 || (permLv(PU_START2) > 0 && permLv(PU_MOVES) > 0)) { gState = ST_STARTMOVE; gBanPage = 0; gPick2 = false; }
    else { prepareLoadout(); gState = ST_LOADOUT; }
    sfxPlay(SFX_UI);
}
static bool missionClaimable() {
    for (int i = 0; i < 3; i++) if (!gSave.md[i].claimed && missionDone(gSave.md[i], false)) return true;
    for (int i = 0; i < 2; i++) if (!gSave.mw[i].claimed && missionDone(gSave.mw[i], true)) return true;
    return false;
}
static void shopEnter();
static void drawMenu() {
    bgFill();
    panel(8, 4, 304, 26, EDGE, COL(20, 36, 84, 255));
    currencyBar(17);
    if (button(20, 38, 184, 56, "¡Jugar!", GOLD_BTN, 0.95f, IC_BALL)) { gCoop = false; gCoopEnd = 0; startRun(); }
    if (button(210, 38, 90, 56, "Coop", COL(40, 160, 170, 255), 0.6f, IC_FRIENDS)) { if (coopOpen()) { gState = ST_COOP; gJoining = false; sfxPlay(SFX_UI); } else msg("No se pudo iniciar la red local"); }
    if (button(20, 102, 136, 40, "Pokémon", EDGE, 0.55f, IC_BOOK)) { gState = ST_DEX; gDexSel = partner(); gDexGen = DEX[gDexSel].gen; gDexPage = 0; sprFreeAll(); sfxPlay(SFX_UI); }
    if (button(164, 102, 136, 40, "Mejoras", EDGE, 0.55f, IC_UP)) { shopEnter(); gState = ST_SHOP; sfxPlay(SFX_UI); }
    if (button(20, 150, 92, 40, "Gacha", COL(150, 80, 200, 255), 0.45f, IC_BALL4)) { gState = ST_GACHA; gNPulls = 0; slotStart(nullptr, 0); sfxPlay(SFX_UI); }
    if (button(118, 150, 92, 40, "Misiones", COL(60, 150, 90, 255), 0.42f, IC_MEDAL3)) { missionsRefresh(); gState = ST_MISSIONS; sfxPlay(SFX_UI); }
    if (button(216, 150, 84, 40, "Kecleon", COL(110, 170, 70, 255), 0.4f, IC_COIN)) { gKecPage = 0; gState = ST_KECLEON; sfxPlay(SFX_UI); }
    if (missionClaimable()) { C2D_DrawCircleSolid(202, 154, 0.5f, 8, COL(255, 255, 255, 255)); C2D_DrawCircleSolid(202, 154, 0.55f, 6, COL(230, 40, 40, 255)); text("!", 202, 145, 0.45f, WHITE, true); }
    bool ban = permLv(PU_BAN) > 0;
    if (ban && button(20, 198, 88, 24, "Vetar", COL(160, 80, 80, 255), 0.42f, IC_BAN)) { gState = ST_BAN; gBanPage = 0; }
    if (button(ban ? 114 : 20, 198, ban ? 98 : 190, 24, "Logros", COL(200, 140, 40, 255), 0.42f, IC_TROPHY)) { achCheck(); gState = ST_ACH; gAchCat = 0; gAchPage = 0; sfxPlay(SFX_UI); }
    if (button(218, 198, 82, 24, LANG_NAMES[gSave.lang], COL(60, 80, 140, 255), 0.4f, IC_GEAR)) { gState = ST_LANG; sfxPlay(SFX_UI); }
    snprintf(gTmp, sizeof gTmp, "START: salir · Volumen %d%% (L/R)", (int)(gSave.vol * 100 + 0.5f));
    text(gTmp, 160, 224, 0.34f, COL(140, 165, 220, 255), true);
}
static void drawMenuTop(u64 ms) {
    topBg();
    tileBg();
    logo(200, 8, 1.3f);
    text("MUNDO MISTERIOSO", 200, 52, 0.5f, COL(255, 255, 255, 255), true);
    int di = partner();
    C2D_DrawEllipseSolid(150, 178, 0.3f, 100, 24, COL(0, 0, 0, 90));
    C2D_DrawEllipseSolid(156, 180, 0.31f, 88, 18, COL(255, 255, 255, 40));
    sprDraw(DEX_NUM[di], 0, ms, true, 200, 182, nullptr, 2.0f, gSave.shinyOn[di] && gSave.shiny[di]);
    text(pname(di), 200, 190, 0.5f, WHITE, true);
    int own = 0;
    for (int i = 0; i < DEX_N; i++) own += gSave.owned[i];
    snprintf(gTmp, sizeof gTmp, "Mejor tiempo %02d:%02d · Partidas %d · Colección %d/%d", gSave.best / 60, gSave.best % 60, gSave.runs, own, DEX_N);
    text(gTmp, 200, 218, 0.38f, WHITE, true);
}

// ---------------------------------------------------------------- Pokémon (Pokédex por regiones)
static int dexOfGen(int gen, int* out) {
    int n = 0;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].gen == gen) out[n++] = i;
    if (gDexSort)       // por rareza (la más alta primero), estable
        for (int i = 1; i < n; i++) { int v = out[i], j = i; while (j > 0 && DEX[out[j - 1]].rarity < DEX[v].rarity) { out[j] = out[j - 1]; j--; } out[j] = v; }
    return n;
}
static void drawMonBottom(int di);
static void drawDex(u64 ms) {
    bgFill();
    if (gDexTop == 1 && gSave.owned[gDexSel] && sprHas(DEX_NUM[gDexSel])) { drawMonBottom(gDexSel); return; }
    static const char* ab[9] = {"Kan", "Joh", "Hoe", "Sin", "Tes", "Kal", "Alo", "Gal", "Pal"};
    for (int g = 1; g <= 9; g++) {
        float x = 4 + (g - 1) * 34;
        if (button(x, 2, 32, 20, ab[g - 1], g == gDexGen ? GOLD_BTN : EDGE, 0.34f) && g != gDexGen) { gDexGen = g; gDexPage = 0; sprFreeAll(); sfxPlay(SFX_UI); }
    }
    static int list[DEX_N];
    int n = dexOfGen(gDexGen, list);
    int pages = (n + 17) / 18;
    if (gDexPage >= pages) gDexPage = pages - 1;
    if (gDexPage < 0) gDexPage = 0;
    for (int k = 0; k < 18; k++) {
        int idx = gDexPage * 18 + k;
        if (idx >= n) break;
        int di = list[idx];
        float x = 5 + (k % 6) * 52, y = 28 + (k / 6) * 46;
        bool own = gSave.owned[di] && sprHas(DEX_NUM[di]);
        panel(x, y, 50, 44, di == gDexSel ? GOLD : (own ? WHITE : COL(80, 100, 150, 255)), own ? PANEL : COL(20, 32, 70, 255));
        if (own) {
            sprDraw(DEX_NUM[di], 0, ms, false, x + 25, y + 38, nullptr, 0.75f);
            if (gSave.shiny[di]) icon(IC_SHINY, x + 32, y + 1, 0.5f);
            if (di == gSave.lastChar) icon(IC_HEART, x + 1, y + 1, 0.5f);
        } else text("?", x + 25, y + 8, 0.7f, COL(110, 130, 180, 255), true);
        if (tapIn(x, y, 50, 44)) { gDexSel = di; sfxPlay(SFX_UI); }
    }
    bool own = gSave.owned[gDexSel] && sprHas(DEX_NUM[gDexSel]);
    if (own && button(6, 168, 100, 26, validPartner(gDexSel) && gSave.lastChar == gDexSel ? "Compañero actual" : "Elegir compañero", GOLD_BTN, 0.34f)) {
        gSave.lastChar = gDexSel; saveWrite(); sfxPlay(SFX_LEVEL);
    }
    if (own && gSave.shiny[gDexSel]) {
        bool on = gSave.shinyOn[gDexSel];
        if (button(110, 168, 100, 26, on ? "Aspecto: Shiny ★" : "Aspecto: Normal", on ? COL(200, 70, 90, 255) : EDGE, 0.34f)) { gSave.shinyOn[gDexSel] ^= 1; saveWrite(); sprFreeAll(); sfxPlay(SFX_UI); }
    }
    if (own && button(214, 168, 100, 26, "Detalles", COL(90, 110, 190, 255), 0.4f)) { gDexTop = 1; gMonMode = 0; gMonPage = 0; sfxPlay(SFX_UI); }
    if (arrowBtn(6, 204, 50, 30, false, gDexPage > 0)) { gDexPage--; sprFreeAll(); sfxPlay(SFX_UI); }
    if (arrowBtn(264, 204, 50, 30, true, gDexPage < pages - 1)) { gDexPage++; sprFreeAll(); sfxPlay(SFX_UI); }
    if (button(60, 204, 98, 30, gDexSort ? "Orden: Rareza" : "Orden: N.º", gDexSort ? COL(200, 110, 40, 255) : EDGE, 0.4f)) { gDexSort ^= 1; gDexPage = 0; sprFreeAll(); sfxPlay(SFX_UI); }
    if (button(162, 204, 98, 30, "Volver", COL(180, 80, 80, 255), 0.4f)) { gState = ST_MENU; sprFreeAll(); }
    int have = 0;
    for (int i = 0; i < n; i++) have += gSave.owned[list[i]];
    snprintf(gTmp, sizeof gTmp, "%s %d/%d", GACHA_GEN_NAMES[gDexGen - 1], have, n);
    char pg[16]; snprintf(pg, sizeof pg, " · %d/%d", gDexPage + 1, pages > 0 ? pages : 1);
    strncat(gTmp, pg, sizeof gTmp - strlen(gTmp) - 1);
    text(gTmp, 160, 184 + 12, 0.34f, COL(170, 200, 255, 255), true);
}
// Página 2: naturaleza, habilidad y todos los movimientos que puede aprender (por sus tipos y MT), con el inicial primero.
static void drawDexMoves(int di) {
    const DexE& p = DEX[di];
    panel(8, 28, 384, 196, WHITE, COL(26, 49, 112, 255));
    snprintf(gTmp, sizeof gTmp, "Movimientos de %s", pname(di));
    text(gTmp, 200, 28, 0.5f, GOLD, true);
    const NatureE& nt = NATURES[monNature(di)];
    static const char* SN[5] = {"Ataque", "Atq.Esp", "Defensa", "Def.Esp", "Velocidad"};
    char nb[96];
    if (nt.up >= 0) snprintf(nb, sizeof nb, "Naturaleza: %s (+%s −%s)", natureName(monNature(di)), T(SN[nt.up]), T(SN[nt.down]));
    else snprintf(nb, sizeof nb, "Naturaleza: %s", natureName(monNature(di)));
    text(nb, 18, 46, 0.4f, WHITE);
    int ab = monAbil(di);
    snprintf(gTmp, sizeof gTmp, "Habilidad: %s", abilName(ab));
    text(gTmp, 18, 60, 0.4f, GOLD);
    char dsc[200]; abilDesc(ab, di, dsc, sizeof dsc);
    textWrap(dsc, 18, 74, 360, 0.34f, COL(170, 200, 255, 255));
    int list[60], n = 0; list[n++] = p.start;
    int ts[2] = {p.t1, p.t2};
    for (int k = 0; k < 2; k++) {
        if (ts[k] == 255) continue;
        const PoolRef& r = POOL_BY_TYPE[ts[k]];
        for (int i = 0; i < r.n && n < 40; i++) { int m = POOL_ALL[r.off + i], dup = 0; for (int j = 0; j < n; j++) dup |= list[j] == m; if (!dup) list[n++] = m; }
    }
    int nNat = n, tg[NTM], nT = monTaughtMoves(di, tg);
    for (int i = 0; i < nT && n < 60; i++) list[n++] = tg[i];
    for (int i = 0; i < n && i < 20; i++) {
        float x = 18 + (i / 10) * 190, y = 104 + (i % 10) * 11;
        C2D_DrawRectSolid(x, y + 2, 0.3f, 7, 7, typeColor(MOVES[list[i]].type));
        text(MOVES[list[i]].name, x + 11, y - 3, 0.32f, i == 0 ? GOLD : i >= nNat ? COL(140, 230, 160, 255) : WHITE);
    }
    text("L: página 1", 20, 212, 0.34f, COL(170, 200, 255, 255));
}
// Pantalla táctil de los detalles: menta (naturaleza), cápsulas (habilidad) y MT (movimientos extra).
static void drawMonBottom(int di) {
    bgFill();
    headerBar("Detalles", IC_BOOK);
    snprintf(gTmp, sizeof gTmp, "%s", pname(di));
    text(gTmp, 160, 28, 0.5f, WHITE, true);
    if (button(214, 204, 100, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) { if (gMonMode) gMonMode = 0; else gDexTop = 0; return; }
    if (gMonMode == 0) {
        snprintf(gTmp, sizeof gTmp, "Menta ×%d", gSave.bag[BAG_MINT]);
        if (button(10, 56, 300, 30, gTmp, COL(70, 150, 90, 255), 0.5f)) { if (gSave.bag[BAG_MINT]) { gMonMode = 1; sfxPlay(SFX_UI); } else msg("No tienes Mentas: cómpralas a Kecleon"); }
        snprintf(gTmp, sizeof gTmp, "Cápsula habilidad ×%d  ·  oculta ×%d", gSave.bag[BAG_CAP], gSave.bag[BAG_CAPH]);
        if (button(10, 92, 300, 30, gTmp, COL(150, 90, 190, 255), 0.42f)) {
            int s[3];
            if ((gSave.bag[BAG_CAP] || gSave.bag[BAG_CAPH]) && monAbilChoices(di, s, gSave.bag[BAG_CAPH] > 0)) { gMonMode = 2; sfxPlay(SFX_UI); }
            else msg("Sin cápsulas o sin habilidades que elegir");
        }
        int tm = 0; for (int i = 0; i < NTM; i++) tm += gSave.tms[i] && monCanLearn(di, i);
        snprintf(gTmp, sizeof gTmp, "Enseñar una MT (%d disponibles)", tm);
        if (button(10, 128, 300, 30, gTmp, COL(200, 130, 50, 255), 0.45f)) { if (tm) { gMonMode = 3; gMonPage = 0; sfxPlay(SFX_UI); } else msg("Ninguna MT que pueda aprender"); }
        text("Consíguelas en la tienda de Kecleon.", 160, 168, 0.36f, COL(170, 200, 255, 255), true);
    } else if (gMonMode == 1) {
        text("Elige la nueva naturaleza", 160, 44, 0.42f, GOLD, true);
        for (int i = 0; i < NNAT; i++) {
            float x = 6 + (i % 5) * 62, y = 60 + (i / 5) * 28;
            if (button(x, y, 60, 26, natureName(i), i == monNature(di) ? COL(120, 120, 60, 255) : EDGE, 0.32f) && i != monNature(di)) {
                if (gSave.bag[BAG_MINT]) { gSave.bag[BAG_MINT]--; gSave.pnat[di] = (u8)(i + 1); saveWrite(); gMonMode = 0; sfxPlay(SFX_LEVEL); }
            }
        }
    } else if (gMonMode == 2) {
        text("Elige la nueva habilidad", 160, 44, 0.42f, GOLD, true);
        int s[3], n = monAbilChoices(di, s, gSave.bag[BAG_CAPH] > 0);
        for (int k = 0; k < n; k++) {
            float y = 62 + k * 44;
            int a = (int)DEX_ABIL[di][s[k]] - 1;
            bool hid = s[k] == 2;
            snprintf(gTmp, sizeof gTmp, "%s%s", abilName(a), hid ? " (oculta)" : "");
            if (button(10, y, 300, 38, gTmp, hid ? COL(150, 90, 190, 255) : COL(70, 110, 190, 255), 0.45f)) {
                int b = hid ? BAG_CAPH : (gSave.bag[BAG_CAP] ? BAG_CAP : BAG_CAPH);
                if (gSave.bag[b]) { gSave.bag[b]--; gSave.pabil[di] = (u8)(s[k] + 1); saveWrite(); gMonMode = 0; sfxPlay(SFX_LEVEL); }
            }
        }
    } else {
        text("Elige la MT a enseñar", 160, 44, 0.42f, GOLD, true);
        int l[NTM], n = 0;
        for (int i = 0; i < NTM; i++) if (gSave.tms[i] && monCanLearn(di, i)) l[n++] = i;
        int pages = (n + 7) / 8;
        if (gMonPage >= pages) gMonPage = pages ? pages - 1 : 0;
        for (int k = 0; k < 8; k++) {
            int idx = gMonPage * 8 + k;
            if (idx >= n) break;
            int t = l[idx];
            float x = 6 + (k % 2) * 158, y = 60 + (k / 2) * 34;
            snprintf(gTmp, sizeof gTmp, "%s ×%d", MOVES[TM_MOVE[t]].name, gSave.tms[t]);
            if (button(x, y, 154, 30, gTmp, typeColor(MOVES[TM_MOVE[t]].type), 0.36f) && monTeach(di, t)) { sfxPlay(SFX_LEVEL); msg("¡Movimiento aprendido!"); }
        }
        if (arrowBtn(6, 204, 50, 30, false, gMonPage > 0)) gMonPage--;
        if (arrowBtn(60, 204, 50, 30, true, gMonPage < pages - 1)) gMonPage++;
    }
    if (gMsgT > 0) text(gMsg, 160, 190, 0.38f, COL(255, 120, 120, 255), true);
}
static void drawDexTop(u64 ms) {
    topBg();
    tileBg();
    const DexE& p = DEX[gDexSel];
    bool own = gSave.owned[gDexSel] && sprHas(DEX_NUM[gDexSel]);
    snprintf(gTmp, sizeof gTmp, "Pokédex — %s", GACHA_GEN_NAMES[p.gen - 1]);
    text(gTmp, 200, 2, 0.6f, GOLD, true);
    if (own && gDexTop == 1) { drawDexMoves(gDexSel); return; }
    panel(14, 28, 160, 196, WHITE, COL(26, 49, 112, 255));
    if (own) {
        bool sh = gSave.shinyOn[gDexSel] && gSave.shiny[gDexSel];
        sprDraw(DEX_NUM[gDexSel], 0, ms, true, 94, 160, nullptr, 2.0f, sh);
        text(pname(gDexSel), 94, 176, 0.55f, WHITE, true);
        snprintf(gTmp, sizeof gTmp, "N.º %d", DEX_NUM[gDexSel]);
        text(gTmp, 94, 196, 0.38f, COL(170, 200, 255, 255), true);
    } else {
        text("?", 94, 80, 2.0f, COL(110, 130, 180, 255), true);
        text("Aún no lo tienes: consíguelo en el Gacha", 94, 180, 0.34f, COL(170, 200, 255, 255), true);
    }
    if (!own) return;
    static const char* rn[6] = {"", "Común", "Poco común", "Raro", "Épico", "Legendario"};
    panel(182, 28, 204, 196, WHITE, COL(26, 49, 112, 255));
    typeChip(192, 38, p.t1);
    typeChip(254, 38, p.t2);
    text(rn[p.rarity], 192, 58, 0.45f, rarityColor(p.rarity));
    snprintf(gTmp, sizeof gTmp, "PS %d    Velocidad %d", p.hp, p.spd); text(gTmp, 192, 80, 0.42f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Ataque %d    Atq.Esp %d", (int)(p.pa * 100), (int)(p.sa * 100)); text(gTmp, 192, 98, 0.42f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Defensa %d    Def.Esp %d", p.df, p.sd); text(gTmp, 192, 116, 0.42f, WHITE);
    int dm = p.start;
    snprintf(gTmp, sizeof gTmp, "Mov. inicial: %s", T(MOVES[dm].name)); text(gTmp, 192, 140, 0.42f, typeColorLight(MOVES[dm].type));
    textWrap(MOVES[dm].desc, 192, 160, 188, 0.36f, COL(170, 200, 255, 255));
    text("R: movimientos", 284, 210, 0.34f, COL(170, 200, 255, 255), true);
    if (gSave.shiny[gDexSel]) text("★ Shiny conseguido", 192, 206, 0.38f, COL(255, 120, 120, 255));
}

static void drawStartMove() {
    bgFill();
    bool has1 = permLv(PU_START) > 0, has2 = permLv(PU_START2) > 0 && permLv(PU_MOVES) > 0;
    if (!has1) gPick2 = true;
    if (!has2) gPick2 = false;
    text(gPick2 ? "Elige tu segundo movimiento" : "Elige tu movimiento inicial", 160, 0, 0.55f, COL(255, 230, 120, 255), true);
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
        bool on = gPick2 ? m == gSave.startMove2[gSel] - 1 : m == gStartChoice[0];
        panel(x, y, 154, 30, typeColor(MOVES[m].type), on ? COL(50, 70, 130, 255) : PANEL);
        text(MOVES[m].name, x + 6, y + 4, 0.45f, m == gStartChoice[0] && gPick2 ? COL(120, 125, 150, 255) : WHITE);
        if (tapIn(x, y, 154, 30)) {
            if (!gPick2) { gStartChoice[0] = m; gSave.startMove[gSel] = (u8)(m + 1); sfxPlay(SFX_UI); }
            else if (m != gStartChoice[0]) { gSave.startMove2[gSel] = gSave.startMove2[gSel] == m + 1 ? 0 : (u8)(m + 1); saveWrite(); sfxPlay(SFX_UI); }
        }
    }
    if (has1 && has2 && button(116, 168, 196, 26, gPick2 ? "Cambiar el primero" : "Cambiar el segundo", COL(90, 110, 190, 255), 0.42f)) gPick2 = !gPick2;
    if (gPick2) text(gSave.startMove2[gSel] ? "Toca de nuevo para dejarlo al azar" : "Segundo ataque: al azar", 6, 170, 0.34f, COL(170, 200, 255, 255));
    if (arrowBtn(6, 204, 50, 30, false, gBanPage > 0)) { gBanPage--; sfxPlay(SFX_UI); }
    if (arrowBtn(60, 204, 50, 30, true, gBanPage < pages - 1)) { gBanPage++; sfxPlay(SFX_UI); }
    if (button(116, 204, 90, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (button(212, 204, 100, 30, "Continuar", COL(60, 170, 80, 255), 0.5f)) { prepareLoadout(); gState = ST_LOADOUT; }
}
static void drawStartTop() {
    topBg();
    int m = gStartChoice[0];
    text(MOVES[m].name, 200, 30, 0.8f, typeColorLight(MOVES[m].type), true);
    textWrap(MOVES[m].desc, 40, 90, 320, 0.5f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Tipo %s · %s", typeName(MOVES[m].type), T(MOVES[m].cat == 0 ? "Físico" : MOVES[m].cat == 1 ? "Especial" : "Estado"));
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
            textWrap(moveName(gMoves[i]), x + 6, y + 26, 62, 0.36f, WHITE);
            snprintf(gTmp, sizeof gTmp, "Nv %d", gMoves[i].lvl);
            text(gTmp, x + 66, y + 1, 0.4f, COL(255, 230, 120, 255), true);
        } else text("vacío", x + 36, y + 24, 0.4f, COL(120, 140, 190, 255), true);
        if (tapIn(x, y, 72, 64)) {
            if (gSelMove >= 0 && gSelMove != i) { playSwapSlots(gSelMove, i); if (!gAfterPause) { int t = gOrder[gSelMove]; gOrder[gSelMove] = gOrder[i]; gOrder[i] = t; } gSelMove = -1; }
            else gSelMove = gSelMove == i ? -1 : i;
            gSelBtn = i;
            sfxPlay(SFX_UI);
        }
    }
    if (gMoves[gSelBtn].id >= 0) {
        const MoveDef& d = MOVES[gMoves[gSelBtn].id];
        text(moveName(gMoves[gSelBtn]), 160, 94, 0.55f, typeColorLight(d.type), true);
        textWrap(d.desc, 20, 118, 280, 0.42f, WHITE);
        snprintf(gTmp, sizeof gTmp, "Recarga %.1f s · %s", gMoves[gSelBtn].v[K_CD], T(d.cat == 0 ? "Físico" : d.cat == 1 ? "Especial" : "Estado"));
        text(gTmp, 160, 160, 0.4f, COL(170, 200, 255, 255), true);
    }
    textWrap("En partida, toca X/Y/B/A para elegir el ataque activo.", 8, 176, 98, 0.3f, COL(150, 170, 220, 255));
    if (button(114, 196, 100, 36, gAfterPause ? "Seguir" : "¡Jugar!", COL(60, 170, 80, 255), 0.6f)) {
        if (gAfterPause) { gState = ST_PLAY; gAfterPause = false; }
        else beginRun();
    }
    if (button(222, 196, 90, 36, gAfterPause ? "Abandonar" : "Volver", COL(180, 80, 80, 255), 0.45f)) {
        if (gAfterPause) { gRun = playStats(); gNewBest = false; gAfterPause = false; gState = ST_OVER; musicPlay(MUS_MENU); }
        else gState = ST_MENU;
    }
}
static void drawLoadoutTop(u64 ms) {
    topBg();
    text(gAfterPause ? "Pausa" : "Tus movimientos", 200, -2, 0.6f, COL(255, 220, 90, 255), true);
    sprDraw(DEX_NUM[gSel], 0, ms, true, 75, 140, nullptr, 2.0f, gSave.shinyOn[gSel] && gSave.shiny[gSel]);
    for (int i = 0; i < 4; i++) {
        float y = 30 + i * 44;
        if (gMoves[i].id < 0) continue;
        const MoveDef& d = MOVES[gMoves[i].id];
        C2D_DrawRectSolid(150, y, 0.2f, 240, 38, typeColorDark(d.type));
        C2D_DrawRectSolid(152, y + 2, 0.25f, 236, 34, COL(14, 26, 50, 255));
        text(BTN_NAMES[i], 158, y + 6, 0.55f, typeColorLight(d.type));
        text(moveName(gMoves[i]), 184, y + 2, 0.5f, WHITE);
        snprintf(gTmp, sizeof gTmp, "Nv %d · %s", gMoves[i].lvl, T(d.cat == 0 ? "Físico" : d.cat == 1 ? "Especial" : "Estado"));
        text(gTmp, 184, y + 20, 0.36f, COL(170, 200, 255, 255));
    }
    if (gAfterPause) {
        snprintf(gTmp, sizeof gTmp, "%s · Nv %d · %02d:%02d", pname(gSel), playLevel(), (int)playTime() / 60, (int)playTime() % 60);
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
        bool act = has && playIsActive(i);
        panel(x, y, 72, 50, act ? WHITE : (has ? typeColorDark(MOVES[gMoves[i].id].type) : EDGE), has ? typeColorDark(MOVES[gMoves[i].id].type) : PANEL);
        if (!has) continue;
        if (playGroupSize(i) > 1) text("+", x + 36, y + 1, 0.45f, COL(255, 140, 220, 255), true);
        u32 c = typeColor(MOVES[gMoves[i].id].type);
        float rdy = 1 - playCdFrac(i);
        C2D_DrawRectSolid(x + 3, y + 43, 0.3f, 66 * clampf(rdy, 0, 1), 4, rdy >= 1 ? COL(255, 255, 255, 255) : c);
        text(BTN_NAMES[i], x + 5, y, 0.6f, c);
        textWrap(moveName(gMoves[i]), x + 6, y + 22, 62, 0.34f, WHITE);
        snprintf(b, sizeof b, "Nv%d", gMoves[i].lvl);
        text(b, x + 66, y + 2, 0.34f, COL(255, 230, 120, 255), true);
        if (tapIn(x, y, 72, 50)) playFireButton(i);
    }
    if (playItem() >= 0) { snprintf(b, sizeof b, "Objeto: %s", itemName(playItem())); text(b, 160, 50, 0.38f, COL(255, 150, 210, 255), true); }
    text("START: pausa / ordenar ataques", 160, 224, 0.4f, COL(150, 170, 220, 255), true);
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
    MissionRun mr = playMissionStats();
    gSave.stat[SB_BOSS] += mr.bosses; gSave.stat[SB_EVO] += mr.evolves; gSave.stat[SB_RIFT] += mr.rifts;
    missionsReport(mr);
    gAchNew = achCheck();
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
    if (gRun.jdowns > 0) { snprintf(gTmp, sizeof gTmp, "Legendarios de la Sentencia: %d", gRun.jdowns); text(gTmp, 160, 138, 0.5f, COL(255, 230, 140, 255), true); }
    if (gCoopEnd) text(gCoopEnd == 1 ? "Compañero desconectado" : gCoopEnd == 2 ? "Partida desincronizada" : "Conexión perdida", 160, 138, 0.5f, COL(255, 140, 140, 255), true);
    if (gNewBest) text("¡Nuevo récord!", 160, 156 - 0, 0.6f, COL(120, 255, 140, 255), true);
    if (gAchNew > 0) { snprintf(gTmp, sizeof gTmp, "¡Logros nuevos: %d!", gAchNew); text(gTmp, 160, 160, 0.5f, COL(255, 200, 80, 255), true); }
    if (button(60, 180, 200, 40, "Continuar", COL(60, 170, 80, 255), 0.7f)) { if (gCoop) { coopClose(); gCoop = false; } gState = ST_MENU; sprFreeAll(); tilesFree(); gTileBgOk = false; }
}

// ---------------------------------------------------------------- mejoras permanentes
static const u8 PERM_ICON[NPERM] = {IC_HEART, IC_FIST, IC_BOOT, IC_CLOCK, IC_SHIELD, IC_SPROUT, IC_MAGNET, IC_BOOK, IC_COIN, IC_CARDS, IC_STAR, IC_UP, IC_BAN, IC_CURSOR, IC_CURSOR};
static int gUpgList[DEX_N], gUpgN, gUpgI;
static int pokeLevels(int di) { int t = 0; for (int i = 0; i < NPERM; i++) t += permLvOf(di, i); return t; }
// Cada Pokémon tiene sus mejoras: el compañero va primero, luego los que ya tienen niveles.
static void shopEnter() {
    gUpgN = ownedList(gUpgList);
    int p = partner();
    for (int i = 1; i < gUpgN; i++) {
        int v = gUpgList[i], j = i - 1;
        auto key = [&](int d) { return d == p ? 100000 : pokeLevels(d) * 1000 - d; };
        while (j >= 0 && key(gUpgList[j]) < key(v)) { gUpgList[j + 1] = gUpgList[j]; j--; }
        gUpgList[j + 1] = v;
    }
    gUpgI = 0; gShopPage = 0;
    sprFreeAll();
}
static int upgDex() { return gUpgN ? gUpgList[gUpgI] : partner(); }
static void drawShop() {
    bgFill();
    int di = upgDex();
    headerBar("Mejoras", IC_UP);
    icon(IC_COIN, 232, 3, 0.5f);
    snprintf(gTmp, sizeof gTmp, "%d", gSave.coins);
    text(gTmp, 252, 1, 0.5f, GOLD);
    // selector de Pokémon
    if (arrowBtn(6, 29, 36, 22, false, gUpgN > 1)) { gUpgI = (gUpgI + gUpgN - 1) % gUpgN; gShopPage = 0; sprFreeAll(); sfxPlay(SFX_UI); }
    if (arrowBtn(278, 29, 36, 22, true, gUpgN > 1)) { gUpgI = (gUpgI + 1) % gUpgN; gShopPage = 0; sprFreeAll(); sfxPlay(SFX_UI); }
    panel(46, 29, 228, 22, WHITE, COL(26, 49, 112, 255));
    snprintf(gTmp, sizeof gTmp, "%s%s", pname(di), di == partner() ? " ♥" : "");
    text(gTmp, 56, 28, 0.42f, WHITE);
    snprintf(gTmp, sizeof gTmp, "Niveles: %d", pokeLevels(di));
    text(gTmp, 266, 33, 0.36f, COL(170, 200, 255, 255), false);
    for (int k = 0; k < 3; k++) {
        int i = gShopPage * 3 + k;
        if (i >= NPERM) break;
        float y = 55 + k * 49;
        int lv = permLvOf(di, i);
        bool locked = i == PU_START2 && !permLvOf(di, PU_MOVES);   // el segundo movimiento inicial necesita Repertorio
        bool maxed = lv >= PERM[i].max;
        int cost = maxed ? 0 : permCost(i, lv);
        bool can = !maxed && !locked && gSave.coins >= cost;
        panel(6, y, 308, 47, maxed ? COL(90, 200, 120, 255) : EDGE, COL(26, 49, 112, 255));
        icon(PERM_ICON[i], 9, y + 7, 1.0f);
        text(PERM[i].name, 46, y + 2, 0.5f, WHITE);
        textWrap(PERM[i].unit, 46, y + 20, 170, 0.36f, COL(190, 215, 255, 255));
        char b[16];
        if (locked) snprintf(b, sizeof b, "Bloq.");
        else if (maxed) snprintf(b, sizeof b, "Máx.");
        else snprintf(b, sizeof b, "%d", cost);
        if (button(226, y + 5, 82, 26, b, maxed ? COL(70, 130, 90, 255) : locked ? COL(60, 64, 90, 255) : can ? GOLD_BTN : COL(80, 84, 110, 255), 0.46f, maxed ? -1 : IC_COIN) && !maxed) {
            if (locked) { msg("Necesita Repertorio"); sfxPlay(SFX_HURT); }
            else if (can) { gSave.coins -= cost; permSetLv(di, i, lv + 1); saveWrite(); sfxPlay(SFX_LEVEL); }
            else { msg("No tienes suficientes Pokémonedas"); sfxPlay(SFX_HURT); }
        }
        int mx = PERM[i].max, pw = mx > 8 ? 6 : mx > 5 ? 8 : 12, tw = mx * (pw + 2) - 2;
        for (int q = 0; q < mx; q++) {
            float px = 267 - tw / 2.0f + q * (pw + 2);
            C2D_DrawRectSolid(px, y + 35, 0.3f, pw, 6, INK);
            C2D_DrawRectSolid(px + 1, y + 36, 0.35f, pw - 2, 4, q < lv ? COL(255, 210, 63, 255) : COL(46, 60, 110, 255));
        }
    }
    int pages = (NPERM + 2) / 3;
    if (arrowBtn(6, 204, 60, 30, false, gShopPage > 0)) { gShopPage--; sfxPlay(SFX_UI); }
    snprintf(gTmp, sizeof gTmp, "%d/%d", gShopPage + 1, pages);
    text(gTmp, 100, 210, 0.42f, WHITE, true);
    if (arrowBtn(134, 204, 60, 30, true, gShopPage < pages - 1)) { gShopPage++; sfxPlay(SFX_UI); }
    if (button(220, 204, 94, 30, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
    if (gMsgT > 0) text(gMsg, 160, 192, 0.38f, COL(255, 120, 120, 255), true);
}
static void drawShopTop(u64 ms) {
    topBg();
    tileBg();
    int di = upgDex();
    panel(14, 28, 150, 196, WHITE, COL(26, 49, 112, 255));
    sprDraw(DEX_NUM[di], 0, ms, true, 89, 150, nullptr, 2.0f, gSave.shinyOn[di] && gSave.shiny[di]);
    text(pname(di), 89, 170, 0.5f, WHITE, true);
    snprintf(gTmp, sizeof gTmp, "Niveles: %d", pokeLevels(di));
    text(gTmp, 89, 192, 0.38f, COL(170, 200, 255, 255), true);
    text("Mejoras", 280, 4, 0.7f, GOLD, true);
    textWrap("Cada Pokémon tiene sus propias mejoras: sólo cuentan cuando juegas con él. Consigue Pokémonedas jugando y con los duplicados del gacha.", 182, 40, 206, 0.42f, WHITE);
    if (upgDex() != partner()) textWrap("Para jugar con él, elígelo como compañero en «Pokémon».", 182, 140, 206, 0.38f, COL(255, 220, 120, 255));
}

// ---------------------------------------------------------------- gacha
static u32 rarCol(int r) { return rarityColor(r); }
static void drawGacha() {
    bgFill();
    for (int g = 1; g <= 9; g++) {
        static const char* ab[9] = {"Kan", "Joh", "Hoe", "Sin", "Tes", "Kal", "Alo", "Gal", "Pal"};
        if (button(4 + (g - 1) * 34, 2, 32, 20, ab[g - 1], g == gGen ? GOLD_BTN : EDGE, 0.34f) && g != gGen && !slotBusy()) { gGen = g; sfxPlay(SFX_UI); }
    }
    // tickets que tienes
    panel(6, 26, 308, 24, EDGE, COL(20, 36, 84, 255));
    currencyBar(38);
    snprintf(gTmp, sizeof gTmp, "%s", GACHA_GEN_NAMES[gGen - 1]);
    text(gTmp, 284, 30, 0.38f, GOLD, true);
    // probabilidades
    panel(6, 54, 308, 88, WHITE, COL(26, 49, 112, 255));
    static const char* rn[6] = {"", "Común", "Poco común", "Raro", "Épico", "Legendario"};
    static const u8 BALLS[6] = {0, IC_BALL, IC_BALL2, IC_BALL3, IC_BALLLUX, IC_BALL4};
    for (int r = 5; r >= 1; r--) {
        float y = 58 + (5 - r) * 13;
        icon(BALLS[r], 12, y - 2, 0.5f);
        text(rn[r], 32, y - 3, 0.36f, rarCol(r));
        snprintf(gTmp, sizeof gTmp, "%.1f%%", GACHA_RATES[r - 1]);
        text(gTmp, 190, y - 3, 0.36f, rarCol(r), true);
    }
    icon(IC_SHINY, 12, 58 + 65 - 2, 0.5f);
    text("Shiny", 32, 58 + 65 - 3, 0.36f, COL(255, 130, 130, 255));
    snprintf(gTmp, sizeof gTmp, "%.0f%%", SHINY_RATE);
    text(gTmp, 190, 58 + 65 - 3, 0.36f, COL(255, 130, 130, 255), true);
    int own = 0, tot = 0;
    for (int i = 0; i < DEX_N; i++) if (DEX[i].gen == gGen) { tot++; if (gSave.owned[i]) own++; }
    text("Poseídos", 252, 62, 0.4f, COL(170, 200, 255, 255), true);
    snprintf(gTmp, sizeof gTmp, "%d/%d", own, tot);
    text(gTmp, 252, 78, 0.5f, WHITE, true);
    bool ok1 = gSave.t1 >= 1, ok10 = gSave.t1 >= 10, okP = gSave.t10 >= 1;
    bool idle = !slotBusy();
    u32 off = COL(70, 60, 90, 255);
    if (button(6, 148, 100, 38, "Tirar ×1", ok1 ? COL(150, 80, 200, 255) : off, 0.4f, IC_TICKET) && idle) {
        if (ok1) { sprFreeAll(); gNPulls = gachaPull(gGen, 1, gPulls); slotStart(gPulls, gNPulls); sfxPlay(SFX_GACHA); } else { msg("Sin tickets"); sfxPlay(SFX_HURT); }
    }
    if (button(110, 148, 100, 38, "Tirar ×10", ok10 ? COL(200, 90, 150, 255) : off, 0.4f, IC_TICKET) && idle) {
        if (ok10) { sprFreeAll(); gNPulls = gachaPull(gGen, 10, gPulls, false); slotStart(gPulls, gNPulls); sfxPlay(SFX_GACHA); } else { msg("Necesitas 10 tickets"); sfxPlay(SFX_HURT); }
    }
    if (button(214, 148, 100, 38, "Tirar ×10", okP ? COL(130, 70, 210, 255) : off, 0.4f, IC_TICKET10) && idle) {
        if (okP) { sprFreeAll(); gNPulls = gachaPull(gGen, 10, gPulls, true); slotStart(gPulls, gNPulls); sfxPlay(SFX_GACHA); } else { msg("Sin tickets ×10"); sfxPlay(SFX_HURT); }
    }
    text("1 ticket", 56, 187, 0.27f, COL(170, 200, 255, 255), true);
    text("10 tickets", 160, 187, 0.27f, COL(170, 200, 255, 255), true);
    text("1 ticket ×10", 264, 187, 0.27f, COL(220, 170, 255, 255), true);
    if (gMsgT > 0) text(gMsg, 160, 196, 0.38f, COL(255, 120, 120, 255), true);
    if (slotBusy()) { if (button(100, 210, 120, 26, "Saltar", GOLD_BTN, 0.5f)) slotSkip(); }
    else if (button(100, 210, 120, 26, "Volver", COL(180, 80, 80, 255), 0.5f)) { gState = ST_MENU; slotStart(nullptr, 0); sprFreeAll(); }
}

// ---------------------------------------------------------------- misiones
static void drawMission(float y, MSlot& m, bool weekly) {
    int goal = missionGoal(m, weekly);
    bool done = missionDone(m, weekly);
    panel(6, y, 308, 33, m.claimed ? COL(90, 200, 120, 255) : done ? GOLD : EDGE, COL(26, 49, 112, 255));
    char b[96];
    missionText(m, weekly, b, sizeof b);
    textWrap(b, 12, y + 3, 215, 0.34f, WHITE);
    float frac = goal > 0 ? (float)m.prog / goal : 0;
    C2D_DrawRectSolid(12, y + 24, 0.3f, 150, 5, COL(10, 20, 48, 255));
    C2D_DrawRectSolid(12, y + 24, 0.35f, 150 * clampf(frac, 0, 1), 5, done ? COL(120, 255, 140, 255) : COL(80, 160, 255, 255));
    snprintf(b, sizeof b, "%d/%d", m.prog, goal);
    text(b, 170, y + 19, 0.32f, WHITE);
    int t1, t10, coins;
    missionReward(m, weekly, &t1, &t10, &coins);
    if (m.claimed) text("✔", 270, y + 4, 0.8f, COL(120, 255, 160, 255), true);
    else if (done) {
        if (button(226, y + 3, 80, 26, "Cobrar", GOLD_BTN, 0.45f) && missionClaim(m, weekly)) { sfxPlay(SFX_LEVEL); }
    } else {
        if (t10) snprintf(b, sizeof b, "+1 ×10 · %d", coins); else snprintf(b, sizeof b, "+%d tickets · %d", t1, coins);
        text(b, 266, y + 8, 0.32f, COL(255, 220, 120, 255), true);
    }
}
static void drawMissions() {
    bgFill();
    headerBar("Misiones", IC_MEDAL3);
    text("Diarias", 8, 25, 0.38f, GOLD);
    for (int i = 0; i < 3; i++) drawMission(40 + i * 38, gSave.md[i], false);
    text("Semanales", 8, 153, 0.38f, GOLD);
    for (int i = 0; i < 2; i++) drawMission(168 + i * 33, gSave.mw[i], true);
    if (button(240, 212, 76, 24, "Volver", COL(180, 80, 80, 255), 0.45f)) gState = ST_MENU;
}
static void drawMissionsTop() {
    topBg();
    tileBg();
    text("Misiones", 200, 6, 0.9f, GOLD, true);
    textWrap("Las misiones diarias se renuevan cada día y las semanales cada lunes. El progreso se cuenta al terminar cada partida.", 40, 70, 320, 0.45f, WHITE);
    int done = 0;
    for (int i = 0; i < 3; i++) done += gSave.md[i].claimed;
    snprintf(gTmp, sizeof gTmp, "Diarias cobradas hoy: %d/3", done);
    text(gTmp, 200, 160, 0.5f, COL(120, 255, 160, 255), true);
}
// ---------------------------------------------------------------- vínculo / fusión
static void coopSend(u16 cmd);
static void drawBond() {
    bgFill();
    int need = playBondNeed();
    text("¡Vínculo!", 160, 0, 0.7f, COL(255, 140, 220, 255), true);
    snprintf(gTmp, sizeof gTmp, need == 1 ? "Elige 1 movimiento para unirlo al grupo" : "Elige 2 movimientos para fusionarlos");
    text(gTmp, 160, 28, 0.4f, WHITE, true);
    int sel = 0;
    for (int i = 0; i < 4; i++) {
        float x = 8 + (i % 2) * 154, y = 50 + (i / 2) * 56;
        bool has = gMoves[i].id >= 0, loose = playBondLoose(i);
        if (!has) { panel(x, y, 150, 52, EDGE, COL(20, 32, 70, 255)); continue; }
        if (!loose) gBondSel[i] = false;
        if (loose && tapIn(x, y, 150, 52)) {
            if (gBondSel[i]) gBondSel[i] = false;
            else { int c = 0; for (int k = 0; k < 4; k++) c += gBondSel[k]; if (c < need) gBondSel[i] = true; }
            sfxPlay(SFX_UI);
        }
        if (gBondSel[i]) sel++;
        u32 edge = gBondSel[i] ? GOLD : (loose ? WHITE : COL(255, 120, 200, 255));
        panel(x, y, 150, 52, edge, loose ? typeColorDark(MOVES[gMoves[i].id].type) : COL(40, 40, 70, 255));
        text(BTN_NAMES[i], x + 6, y + 2, 0.6f, typeColor(MOVES[gMoves[i].id].type));
        textWrap(moveName(gMoves[i]), x + 34, y + 6, 112, 0.42f, loose ? WHITE : COL(150, 150, 180, 255));
        if (!loose) text("+", x + 134, y + 30, 0.5f, COL(255, 140, 220, 255));
    }
    bool ok = sel == need;
    if (button(8, 170, 150, 36, "Fusionar", ok ? COL(60, 170, 80, 255) : COL(60, 60, 80, 255), 0.55f) && ok) {
        int b[2], n = 0;
        for (int i = 0; i < 4; i++) if (gBondSel[i] && n < 2) b[n++] = i;
        if (gCoop) {
            int mask = 0; for (int i = 0; i < n; i++) mask |= 1 << b[i];
            for (int i = 0; i < 4; i++) gBondSel[i] = false;
            coopSend(0x2000 | mask);
            return;
        }
        playBondApply(b, n);
        for (int i = 0; i < 4; i++) gBondSel[i] = false;
        gState = ST_PLAY;
    }
    if (button(162, 170, 150, 36, "Más tarde", COL(180, 80, 80, 255), 0.5f)) {
        for (int i = 0; i < 4; i++) gBondSel[i] = false;
        if (gCoop) { coopSend(0x2000); return; }
        playBondSkip();
        gState = ST_PLAY;
    }
}

// ---------------------------------------------------------------- objeto equipable
static void drawItem() {
    bgFill();
    text("¡Objeto nuevo!", 160, 0, 0.7f, COL(255, 140, 220, 255), true);
    text("Solo puedes llevar uno. ¿Cuál te quedas?", 160, 28, 0.4f, WHITE, true);
    int cur = playItem(), nw = playItemNew();
    if (cur < 0 || nw < 0) { playItemChoose(false); gState = ST_PLAY; return; }
    const int ids[2] = {cur, nw};
    for (int k = 0; k < 2; k++) {
        float x = 8 + k * 154;
        panel(x, 50, 150, 110, k ? GOLD : EDGE, COL(20, 32, 70, 255));
        text(k ? "Nuevo" : "Equipado", x + 75, 54, 0.4f, k ? GOLD : COL(150, 170, 220, 255), true);
        textWrap(itemName(ids[k]), x + 8, 74, 134, 0.5f, WHITE);
        textWrap(itemDesc(ids[k]), x + 8, 100, 134, 0.36f, COL(170, 200, 255, 255));
        if (tapIn(x, 50, 150, 110)) { playItemChoose(k == 1); sfxPlay(SFX_UI); gState = ST_PLAY; return; }
    }
    text("Toca el que quieras llevar", 160, 180, 0.4f, COL(150, 170, 220, 255), true);
}

// ---------------------------------------------------------------- cooperativo local
static void coopCancel() {
    coopLeave(); coopClose();
    gCoop = false; gJoining = false;
    gState = ST_MENU; sprFreeAll(); tilesFree(); gTileBgOk = false;
    musicPlay(MUS_MENU);
}
static void drawCoopLobby() {
    bgFill();
    text("Cooperativo local · 2 jugadores", 160, 6, 0.5f, GOLD, true);
    int mode = coopMode();
    if (mode == CN_OFF && !gJoining) {
        if (button(40, 40, 240, 48, "Crear sala", COL(60, 170, 80, 255), 0.7f)) { if (coopHost()) sfxPlay(SFX_UI); else msg("No se pudo crear la sala"); }
        if (button(40, 98, 240, 48, "Unirse a una sala", EDGE, 0.7f)) { gJoining = true; sfxPlay(SFX_UI); }
        text("Las dos consolas, con la misma versión del juego,", 160, 156, 0.36f, COL(170, 195, 245, 255), true);
        text("cerca una de otra. Sin internet ni servidores.", 160, 172, 0.36f, COL(170, 195, 245, 255), true);
    } else if (mode == CN_HOST) {
        text("Sala creada", 160, 60, 0.7f, WHITE, true);
        text("Esperando a tu amigo… (que pulse «Unirse»)", 160, 100, 0.42f, COL(170, 195, 245, 255), true);
    } else {
        text("Buscando sala…", 160, 70, 0.7f, WHITE, true);
        text("El anfitrión debe pulsar «Crear sala»", 160, 110, 0.42f, COL(170, 195, 245, 255), true);
    }
    if (button(80, 198, 160, 30, "Atrás", COL(160, 80, 80, 255), 0.55f)) { coopClose(); gJoining = false; gState = ST_MENU; sfxPlay(SFX_UI); }
}
static void drawCoopWait() {
    bgFill();
    if (gCoopErr == 1) text("Versiones del juego distintas", 160, 80, 0.55f, COL(255, 120, 120, 255), true);
    else if (gCoopErr == 2) text("Conexión perdida", 160, 80, 0.6f, COL(255, 120, 120, 255), true);
    else {
        text("Conectado", 160, 60, 0.7f, COL(120, 255, 140, 255), true);
        text("Esperando al compañero…", 160, 100, 0.5f, WHITE, true);
    }
    if (button(80, 180, 160, 36, "Cancelar", COL(160, 80, 80, 255), 0.6f)) coopCancel();
}
static void coopSend(u16 cmd) { coopQueueCmd(cmd); sfxPlay(SFX_LEVEL); gCoopCards = false; }
static void drawCoopCards() {
    bgFill();
    snprintf(gTmp, sizeof gTmp, "¡Nivel! Elige una mejora");
    text(gTmp, 160, 0, 0.6f, COL(255, 230, 120, 255), true);
    for (int i = 0; i < gCards.n; i++) {
        float y = 24 + i * 62;
        panel(8, y, 304, 58, gCards.c[i].col | 0xFF000000u);
        text(gCards.c[i].title, 18, y + 3, 0.5f, WHITE);
        textWrap(gCards.c[i].desc, 18, y + 26, 286, 0.38f, COL(170, 200, 255, 255));
        if (tapIn(8, y, 304, 58)) { coopSend(0x8000 | (gCards.c[i].kind & 3) << 8 | (gCards.c[i].arg & 0xff)); return; }
    }
    snprintf(gTmp, sizeof gTmp, "Cambiar cartas (%d)", playRerolls());
    if (button(60, 212, 200, 24, gTmp, playRerolls() > 0 ? EDGE : COL(60, 60, 80, 255), 0.45f) && playRerolls() > 0) { playReroll(gCards); sfxPlay(SFX_UI); }
}
static void drawCoopItem() {
    bgFill();
    text("¡Objeto nuevo!", 160, 0, 0.7f, COL(255, 140, 220, 255), true);
    text("Solo puedes llevar uno. ¿Cuál te quedas?", 160, 28, 0.4f, WHITE, true);
    const int ids[2] = {playItem(), playItemNew()};
    for (int k = 0; k < 2; k++) {
        float x = 8 + k * 154;
        panel(x, 50, 150, 110, k ? GOLD : EDGE, COL(20, 32, 70, 255));
        text(k ? "Nuevo" : "Equipado", x + 75, 54, 0.4f, k ? GOLD : COL(150, 170, 220, 255), true);
        textWrap(itemName(ids[k]), x + 8, 74, 134, 0.5f, WHITE);
        textWrap(itemDesc(ids[k]), x + 8, 100, 134, 0.36f, COL(170, 200, 255, 255));
        if (tapIn(x, 50, 150, 110)) { coopSend(0x4000 | k); return; }
    }
    text("Toca el que quieras llevar", 160, 180, 0.4f, COL(150, 170, 220, 255), true);
}
// ¿qué debe mostrarse en la pantalla inferior? 0 nada · 1 cartas · 2 objeto · 3 vínculo
static int coopOverlay() {
    if (coopInFlight() > 0) return 0;
    if (playCoopBond() & 1) return 3;
    if (playItemNew() >= 0) return 2;
    if (playCoopPending() > 0 && !playCoopDead()) return 1;
    return 0;
}

// ---------------------------------------------------------------- logros
static void drawAch() {
    bgFill();
    static const char* ab[6] = {"Col", "Sup", "Com", "Grie", "Leg", "Otr"};
    for (int c = 0; c < 6; c++)
        if (button(4 + c * 52, 2, 50, 20, ab[c], c == gAchCat ? GOLD_BTN : EDGE, 0.36f) && c != gAchCat) { gAchCat = c; gAchPage = 0; sfxPlay(SFX_UI); }
    static int list[256];
    int n = achInCat(gAchCat, list, 256);
    int pages = (n + 3) / 4;
    if (gAchPage >= pages) gAchPage = pages - 1;
    if (gAchPage < 0) gAchPage = 0;
    static const u32 MED[4] = {0, COL(205, 127, 50, 255), COL(200, 205, 215, 255), COL(255, 210, 63, 255)};
    for (int k = 0; k < 4; k++) {
        int idx = gAchPage * 4 + k;
        if (idx >= n) break;
        int i = list[idx], tier; long val, goal; bool done;
        char nm[48], ds[96];
        achInfo(i, nm, ds, sizeof nm, &tier, &val, &goal, &done);
        float y = 26 + k * 38;
        panel(6, y, 308, 35, done ? COL(90, 200, 120, 255) : EDGE);
        icon(tier == 1 ? IC_MEDAL1 : tier == 2 ? IC_MEDAL2 : IC_MEDAL3, 4, y + 1, 0.75f, done ? 0xFFFFFFFF : COL(150, 160, 190, 255));
        text(nm, 38, y, 0.42f, WHITE);
        textWrap(ds, 38, y + 14, 220, 0.3f, COL(170, 200, 255, 255));
        if (done) text("✓", 290, y + 2, 0.8f, COL(120, 255, 160, 255), true);
        else {
            C2D_DrawRectSolid(38, y + 29, 0.6f, 200, 4, COL(0, 0, 0, 160));
            C2D_DrawRectSolid(38, y + 29, 0.65f, 200 * clampf(goal > 0 ? (float)val / goal : 0, 0, 1), 4, MED[tier]);
            snprintf(gTmp, sizeof gTmp, "%ld/%ld", val, goal);
            text(gTmp, 306, y + 20, 0.32f, WHITE, true);
        }
    }
    if (pages > 1) {
        if (arrowBtn(6, 182, 60, 22, false)) { gAchPage = (gAchPage + pages - 1) % pages; sfxPlay(SFX_UI); }
        if (arrowBtn(254, 182, 60, 22, true)) { gAchPage = (gAchPage + 1) % pages; sfxPlay(SFX_UI); }
        snprintf(gTmp, sizeof gTmp, "%d/%d", gAchPage + 1, pages);
        text(gTmp, 160, 184, 0.45f, WHITE, true);
    }
    if (button(100, 212, 120, 24, "Volver", COL(180, 80, 80, 255), 0.5f)) gState = ST_MENU;
}
static void drawAchTop() {
    topBg();
    tileBg();
    text("Logros", 200, 6, 0.9f, GOLD, true);
    snprintf(gTmp, sizeof gTmp, "Conseguidos: %d/%d", achDoneCount(), achCount());
    text(gTmp, 200, 90, 0.6f, COL(120, 255, 160, 255), true);
    text("Los premios se cobran solos al cumplirlos.", 200, 130, 0.42f, WHITE, true);
}
static void drawGachaTop(u64 ms) {
    slotDraw(ms);
}

// ---------------------------------------------------------------- vetar movimientos
static void drawBan() {
    bgFill();
    int used = 0;
    for (int i = 0; i < NMOVES; i++) used += gSave.bannedMove[i];
    snprintf(gTmp, sizeof gTmp, "Vetar movimientos %d/%d", used, permLv(PU_BAN));
    headerBar(gTmp, IC_BAN);
    int pages = (NMOVES + 11) / 12;
    for (int k = 0; k < 12; k++) {
        int m = gBanPage * 12 + k;
        if (m >= NMOVES) break;
        float x = 6 + (k % 2) * 158, y = 30 + (k / 2) * 28;
        panel(x, y, 154, 26, gSave.bannedMove[m] ? COL(230, 60, 60, 255) : typeColor(MOVES[m].type));
        text(MOVES[m].name, x + 6, y + 2, 0.4f, WHITE);
        if (gSave.bannedMove[m]) icon(IC_BAN, x + 126, y - 2, 0.75f);
        if (tapIn(x, y, 154, 26)) {
            if (gSave.bannedMove[m]) gSave.bannedMove[m] = 0;
            else if (used < permLv(PU_BAN)) gSave.bannedMove[m] = 1;
            else msg("Sin vetos libres");
            saveWrite();
        }
    }
    if (arrowBtn(6, 206, 50, 28, false, gBanPage > 0)) { gBanPage--; sfxPlay(SFX_UI); }
    if (arrowBtn(60, 206, 50, 28, true, gBanPage < pages - 1)) { gBanPage++; sfxPlay(SFX_UI); }
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
    iconsLoad();
    saveLoad();
    textSetLang();
    missionsRefresh();
    audioInit();
    musicPlay(MUS_MENU);
    gSel = gSave.lastChar >= 0 && gSave.lastChar < DEX_N ? gSave.lastChar : 0;
    if (!gSave.langSet) gState = ST_LANG;

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
        {
            static int prevSt = -1;
            if (prevSt != (int)gState) { gFocIdx = -1; gFocShow = false; prevSt = (int)gState; }
            gFocMs = now;
            gFocOn = !(gState == ST_PLAY && !(gCoop && coopOverlay()));
            if (gTap) gFocShow = false;
            bool padKeys = gState == ST_LOADOUT || gState == ST_PAUSE;
            if (gFocOn) focusMove(down);
            gFocAct = gFocOn && gFocShow && (down & (padKeys ? KEY_SELECT : KEY_A));
            gBackReq = gFocOn && !padKeys && (down & KEY_B);
            gFocN = 0;
            gBotScene = false;
        }

        if (gState == ST_MENU) {
            if (down & KEY_START) quit = true;
            if (down & KEY_L) gSave.vol = clampf(gSave.vol - 0.1f, 0, 1);
            if (down & KEY_R) gSave.vol = clampf(gSave.vol + 0.1f, 0, 1);
        }
        if (gState == ST_PLAY && !gCoop && (down & KEY_START)) { gState = ST_PAUSE; gAfterPause = true; gSelBtn = 3; gSelMove = -1; gJoy = false; }
        else if (gState == ST_PAUSE && (down & KEY_START)) { gState = ST_PLAY; gAfterPause = false; }
        if (gState == ST_DEX) { if (down & KEY_R) gDexTop = 1; if (down & KEY_L) gDexTop = 0; }
        if (gState == ST_LOADOUT || gState == ST_PAUSE)
            for (int i = 0; i < 4; i++) if (down & BTN_KEYS[i]) {
                if (gSelMove >= 0 && gSelMove != i) { playSwapSlots(gSelMove, i); if (gState == ST_LOADOUT) { int t = gOrder[gSelMove]; gOrder[gSelMove] = gOrder[i]; gOrder[i] = t; } gSelMove = -1; }
                else gSelMove = gSelMove == i ? -1 : i;
                gSelBtn = i;
            }

        if (gState == ST_COOP && coopMode() != CN_OFF && coopLinked()) { gCoop = true; gJoining = false; startRun(); }
        if (gState == ST_COOPWAIT && !gCoopErr) {
            int r = coopHandshake(&gCoopMe, gCH, &gCoopSeed);
            if (r == 1) gState = ST_LOADING;
            else if (r < 0) gCoopErr = 1;
            else if (!coopLinked()) gCoopErr = 2;
        }

        if (gState == ST_PLAY && gCoop) {
            int ov = coopOverlay();
            if (ov == 1 && !gCoopCards) { playBuildCards(gCards); gCoopCards = true; }
            if (ov != 1) gCoopCards = false;
            int jx = 0, jy = 0;
            bool ts = gTouching;
            if (ov) { gTouching = false; gJoy = false; }
            readJoy(jx, jy, held);
            gTouching = ts;
            gCoopBtn |= playCoopTakeBtn();
            for (int i = 0; i < 4; i++) if (down & BTN_KEYS[i]) gCoopBtn |= 1 << i;
            gAcc = fminf(gAcc + dt, 0.1f);
            const float TICK = 1.0f / 30;
            bool stalled = false;
            for (int steps = 0; gAcc >= TICK && steps < 2 && playState() == PS_RUN; steps++) {
                int t = coopExec();
                while (coopSched() <= t + coopDelay()) { coopPushLocal((s8)jx, (s8)jy, gCoopBtn); gCoopBtn = 0; }
                if (!coopReady(t)) { stalled = true; break; }
                CoopIn in[2];
                coopInputs(t, in);
                playCoopTick(TICK, in);
                coopDone(t, t % 60 == 0 ? playCoopChecksum() : 0);
                gAcc -= TICK;
            }
            gStall = stalled ? gStall + dt : 0;
            playCoopFrame(dt);
            int st = coopPump();
            if (st) { gCoopEnd = st; finishRun(); coopLeave(); gState = ST_OVER; }
            else if (playState() == PS_OVER || playState() == PS_WIN) { finishRun(); coopLeave(); gState = ST_OVER; }
        } else if (gState == ST_PLAY) {
            int jx = 0, jy = 0;
            readJoy(jx, jy, held);
            playUpdate(dt, down, held, jx, jy);
            if (playState() == PS_LEVELUP) { playBuildCards(gCards); gState = ST_LEVELUP; gJoy = false; }
            else if (playState() == PS_BOND) { gState = ST_BOND; gJoy = false; for (int i = 0; i < 4; i++) gBondSel[i] = false; }
            else if (playState() == PS_ITEM) { gState = ST_ITEM; gJoy = false; }
            else if (playState() == PS_OVER || playState() == PS_WIN) { finishRun(); gState = ST_OVER; }
        }
        audioUpdate();
        if (gState == ST_GACHA) slotUpdate(dt);

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        textFrame();
        C2D_TargetClear(top, COL(0, 0, 0, 255));
        C2D_TargetClear(bot, COL(0, 0, 0, 255));
        C2D_SceneBegin(top);
        switch (gState) {
            case ST_MENU: drawMenuTop(now); break;
            case ST_DEX: drawDexTop(now); break;
            case ST_MISSIONS: drawMissionsTop(); break;
            case ST_STARTMOVE: drawStartTop(); break;
            case ST_LOADOUT: case ST_PAUSE: drawLoadoutTop(now); break;
            case ST_SHOP: drawShopTop(now); break;
            case ST_KECLEON: drawKecleonTop(); break;
            case ST_GACHA: drawGachaTop(now); break;
            case ST_BAN: topBg(); text("Elige los movimientos que no quieres ver", 200, 100, 0.5f, WHITE, true); break;
            case ST_LANG: topBg(); tileBg(); logo(200, 70, 1.3f); break;
            case ST_LOADING: topBg(); text("Cargando…", 200, 100, 0.8f, WHITE, true); break;
            case ST_PLAY: case ST_LEVELUP: case ST_BOND: case ST_ITEM: playDraw(now);
                if (gCoop && gState == ST_PLAY && gStall > 0.4f) text("Esperando al compañero…", 200, 10, 0.5f, COL(255, 220, 90, 255), true);
                else if (gCoop && gState == ST_PLAY && playCoopBond()) text("Vínculo: partida en pausa", 200, 10, 0.5f, COL(255, 160, 220, 255), true);
                break;
            case ST_COOP: case ST_COOPWAIT: topBg(); tileBg(); logo(200, 70, 1.3f); break;
            case ST_ACH: drawAchTop(); break;
            case ST_OVER: topBg(); text(gRun.won ? "¡Victoria!" : "Fin de la partida", 200, 100, 0.9f, WHITE, true); break;
        }
        C2D_SceneBegin(bot);
        gBotScene = true;
        switch (gState) {
            case ST_MENU: drawMenu(); break;
            case ST_DEX: drawDex(now); break;
            case ST_MISSIONS: drawMissions(); break;
            case ST_STARTMOVE: drawStartMove(); break;
            case ST_LOADOUT: case ST_PAUSE: drawLoadoutBottom(); break;
            case ST_SHOP: drawShop(); break;
            case ST_KECLEON: drawKecleon(); break;
            case ST_GACHA: drawGacha(); break;
            case ST_BAN: drawBan(); break;
            case ST_LANG: drawLang(); break;
            case ST_LOADING: bgFill(); text("Cargando…", 160, 100, 0.8f, WHITE, true); break;
            case ST_PLAY: {
                int ov = gCoop ? coopOverlay() : 0;
                if (ov == 1) drawCoopCards(); else if (ov == 2) drawCoopItem(); else if (ov == 3) drawBond();
                else { drawPlayBottom(); if (gCoop && (playCoopBond() & 2)) text("Vínculo: esperando al compañero…", 160, 70, 0.45f, COL(255, 220, 90, 255), true); }
                break;
            }
            case ST_COOP: drawCoopLobby(); break;
            case ST_COOPWAIT: drawCoopWait(); break;
            case ST_LEVELUP: drawLevelUp(); break;
            case ST_BOND: drawBond(); break;
            case ST_ITEM: drawItem(); break;
            case ST_ACH: drawAch(); break;
            case ST_OVER: drawOver(); break;
        }
        C3D_FrameEnd(0);
        gBackReq = false;
        memcpy(gFocPrev, gFoc, sizeof(FocR) * gFocN);
        gFocPrevN = gFocN;
        if (gFocIdx >= gFocN) gFocIdx = gFocN - 1;

        if (gState == ST_LOADING) { doLoadRun(); last = osGetTime(); }
        if (gState == ST_COOP && gJoining && coopMode() == CN_OFF) { coopScanStep(); last = osGetTime(); }
    }
    coopClose();
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
