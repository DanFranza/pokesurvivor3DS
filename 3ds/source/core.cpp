// Utilidades, sprites, tilesets, guardado y gacha.
#include "game.h"
#include <initializer_list>
#include <sys/stat.h>

// ---------------------------------------------------------------- util
static u32 rngState = 2463534242u;
u32 rnd() { rngState ^= rngState << 13; rngState ^= rngState >> 17; rngState ^= rngState << 5; return rngState; }
u32 rngGet() { return rngState; }
void rngSet(u32 s) { rngState = s ? s : 1; }
float frand() { return (rnd() & 0xFFFFFF) / 16777216.0f; }
float frange(float a, float b) { return a + (b - a) * frand(); }
u32 hash2(int x, int y, int s) {
    u32 h = (u32)x * 374761393u + (u32)y * 668265263u + (u32)s * 2246822519u;
    h = (h ^ (h >> 13)) * 1274126177u;
    return h ^ (h >> 16);
}
static u32 shade(u32 rgb, float k, int a) {
    int r = (rgb >> 16) & 255, g = (rgb >> 8) & 255, b = rgb & 255;
    if (k < 1) { r = (int)(r * k); g = (int)(g * k); b = (int)(b * k); }
    else { float t = k - 1; r += (int)((255 - r) * t); g += (int)((255 - g) * t); b += (int)((255 - b) * t); }
    return COL(r, g, b, a);
}
u32 typeColor(int t, int a) { return shade(TYPE_RGB[t], 1.0f, a); }
u32 typeColorDark(int t, int a) { return shade(TYPE_RGB[t], 0.55f, a); }
u32 typeColorLight(int t, int a) { return shade(TYPE_RGB[t], 1.55f, a); }

// ---------------------------------------------------------------- idioma
#include "lang.h"
extern Save gSave;
#include "pkname.h"
#undef snprintf
const char* pname(int di) {
    if (di < 0 || di >= DEX_N || gSave.lang == LANG_ES) return di >= 0 && di < DEX_N ? DEX[di].name : "";
    const char* r = PK_NAMES[di][gSave.lang - 1];
    return *r ? r : DEX[di].name;
}
const char* T(const char* es) {
    if (!es || gSave.lang == LANG_ES || !*es) return es;
    int lo = 0, hi = LANG_N_STR - 1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        int c = strcmp(es, LANG_STR[mid].es);
        if (c == 0) { const char* r = LANG_STR[mid].tr[gSave.lang - 1]; return *r ? r : es; }
        if (c < 0) hi = mid - 1; else lo = mid + 1;
    }
    return es;
}
const char* typeName(int t) {
    static const char* N[18] = {"Normal", "Fuego", "Agua", "Eléctrico", "Planta", "Hielo", "Lucha", "Veneno", "Tierra", "Volador", "Psíquico", "Bicho", "Roca", "Fantasma", "Dragón", "Siniestro", "Acero", "Hada"};
    return t >= 0 && t < 18 ? T(N[t]) : "";
}

// ---------------------------------------------------------------- texto
static C2D_TextBuf gTxt;
static C2D_Font gFont;
void textInit() {
    gTxt = C2D_TextBufNew(8192);
    gFont = C2D_FontLoad("romfs:/pixel.bcfnt");   // Pixelify Sans, la misma tipografía de la versión web
}
void textFrame() { C2D_TextBufClear(gTxt); }
void text(const char* s, float x, float y, float sc, u32 col, bool center) {
    C2D_Text t;
    C2D_TextFontParse(&t, gFont, gTxt, T(s));
    C2D_TextOptimize(&t);
    if (center) { float w, h; C2D_TextGetDimensions(&t, sc, sc, &w, &h); x -= w / 2; }
    C2D_DrawText(&t, C2D_WithColor, floorf(x), floorf(y), 0.9f, sc, sc, col);
}
float textH(const char* s, float sc) {
    C2D_Text t; C2D_TextFontParse(&t, gFont, gTxt, T(s)); float w, h; C2D_TextGetDimensions(&t, sc, sc, &w, &h); return h;
}
void textWrap(const char* s, float x, float y, float w, float sc, u32 col) {
    C2D_Text t;
    C2D_TextFontParse(&t, gFont, gTxt, T(s));
    C2D_TextOptimize(&t);
    C2D_DrawText(&t, C2D_WithColor | C2D_WordWrap, floorf(x), floorf(y), 0.9f, sc, sc, col, w);
}

// ---------------------------------------------------------------- sprites
static C2D_SpriteSheet gSheets[POKE_MAX], gSheetsS[POKE_MAX];
static int gDexIdx[POKE_MAX];
static bool gIdxReady;
static void buildIdx() {
    for (int i = 0; i < POKE_MAX; i++) gDexIdx[i] = -1;
    for (int i = 0; i < DEX_N; i++) gDexIdx[DEX_NUM[i]] = i;
    gIdxReady = true;
}
int dexIndexOf(int d) { if (!gIdxReady) buildIdx(); return d >= 0 && d < POKE_MAX ? gDexIdx[d] : -1; }
bool sprHas(int d) { return d > 0 && d < POKE_MAX && POKE_SPR[d].w > 0; }
bool sprHasShiny(int d) { return sprHas(d) && POKE_SPR[d].sh; }
void sprLoad(int d) {
    if (!sprHas(d) || gSheets[d]) return;
    char p[48]; snprintf(p, sizeof p, "romfs:/gfx/p%04d.t3x", d);
    gSheets[d] = C2D_SpriteSheetLoad(p);
}
static void sprLoadShiny(int d) {
    if (!sprHasShiny(d) || gSheetsS[d]) return;
    char p[48]; snprintf(p, sizeof p, "romfs:/gfx/p%04ds.t3x", d);
    gSheetsS[d] = C2D_SpriteSheetLoad(p);
}
void sprFreeAll() {
    for (int i = 0; i < POKE_MAX; i++) {
        if (gSheets[i]) { C2D_SpriteSheetFree(gSheets[i]); gSheets[i] = nullptr; }
        if (gSheetsS[i]) { C2D_SpriteSheetFree(gSheetsS[i]); gSheetsS[i] = nullptr; }
    }
}
void sprDraw(int d, int dir, u64 ms, bool moving, float x, float y, const C2D_ImageTint* tint, float sc, bool shiny) {
    if (!sprHas(d)) return;
    C2D_SpriteSheet sh;
    if (shiny && sprHasShiny(d)) { if (!gSheetsS[d]) sprLoadShiny(d); sh = gSheetsS[d]; }
    else { if (!gSheets[d]) sprLoad(d); sh = gSheets[d]; }
    if (!sh) return;
    const PokeSpr& s = POKE_SPR[d];
    int f = (moving && s.n > 1) ? (int)((ms / (u64)(s.ms > 0 ? s.ms : 100)) % s.n) : 0;
    C2D_Image img = C2D_SpriteSheetGetImage(sh, 0);
    Tex3DS_SubTexture st;
    st.width = s.w; st.height = s.h;
    st.left = (float)(f * s.w) / s.tw;
    st.right = (float)(f * s.w + s.w) / s.tw;
    st.top = 1.0f - (float)(dir * s.h) / s.th;
    st.bottom = 1.0f - (float)(dir * s.h + s.h) / s.th;
    img.subtex = &st;
    C2D_DrawImageAt(img, floorf(x - s.ax * sc), floorf(y - s.ay * sc), 0.5f, tint, sc, sc);
}

// ---------------------------------------------------------------- tilesets
static C2D_SpriteSheet gTiles;
void tilesLoad(int set) {
    tilesFree();
    char p[40]; snprintf(p, sizeof p, "romfs:/gfx/tiles%02d.t3x", set);
    gTiles = C2D_SpriteSheetLoad(p);
}
void tilesFree() { if (gTiles) { C2D_SpriteSheetFree(gTiles); gTiles = nullptr; } }
void tileDraw(const TCell& c, float x, float y, float z, const C2D_ImageTint* tint, float sc) {
    if (!gTiles || c.w <= 0) return;
    C2D_Image img = C2D_SpriteSheetGetImage(gTiles, 0);
    Tex3DS_SubTexture st;
    st.width = c.w; st.height = c.h;
    st.left = c.x / 256.0f; st.right = (c.x + c.w) / 256.0f;
    st.top = 1.0f - c.y / 256.0f; st.bottom = 1.0f - (c.y + c.h) / 256.0f;
    img.subtex = &st;
    C2D_DrawImageAt(img, floorf(x), floorf(y), z, tint, sc, sc);
}

// ---------------------------------------------------------------- iconos
static C2D_SpriteSheet gIcons;
void iconsLoad() {
    gIcons = C2D_SpriteSheetLoad("romfs:/gfx/icons.t3x");
    if (gIcons) { C2D_Image im = C2D_SpriteSheetGetImage(gIcons, 0); C3D_TexSetFilter(im.tex, GPU_NEAREST, GPU_NEAREST); }
}
// sc = 1 → celda de 32 px (cada píxel del arte, 2 px de pantalla)
void icon(int ic, float x, float y, float sc, u32 tint) {
    if (!gIcons || ic < 0 || ic >= IC_COUNT) return;
    C2D_Image img = C2D_SpriteSheetGetImage(gIcons, 0);
    Tex3DS_SubTexture st;
    int cx = (ic % ICON_COLS) * ICON_CELL, cy = (ic / ICON_COLS) * ICON_CELL;
    st.width = ICON_CELL; st.height = ICON_CELL;
    st.left = cx / 256.0f; st.right = (cx + ICON_CELL) / 256.0f;
    st.top = 1.0f - cy / (float)ICON_TEX_H; st.bottom = 1.0f - (cy + ICON_CELL) / (float)ICON_TEX_H;
    img.subtex = &st;
    C2D_ImageTint t;
    C2D_PlainImageTint(&t, tint, 1.0f);
    C2D_DrawImageAt(img, floorf(x), floorf(y), 0.85f, tint == 0xFFFFFFFF ? nullptr : &t, sc, sc);
}

// ---------------------------------------------------------------- guardado
Save gSave;
#define SAVE_MAGIC 0x50533344u
static const char* SAVE_PATH = "sdmc:/3ds/pokesurvivor3ds.sav";
void saveLoad() {
    memset(&gSave, 0, sizeof gSave);
    FILE* f = fopen(SAVE_PATH, "rb");
    bool ok = false;
    if (f) {   // una partida guardada más corta (versión anterior) sigue valiendo: los campos nuevos quedan a 0
        size_t n = fread(&gSave, 1, sizeof gSave, f);
        ok = n >= offsetof(Save, vol) + sizeof(float) && gSave.magic == SAVE_MAGIC;
        fclose(f);
    }
    if (!ok) {
        memset(&gSave, 0, sizeof gSave);
        gSave.magic = SAVE_MAGIC;
        gSave.vol = 0.7f;
        gSave.t1 = 5;                          // regalo de bienvenida
        for (int i = 0; i < NSTARTERS; i++) gSave.owned[STARTERS_IDX[i]] = 1;
    }
    if (!gSave.pupgMig) {   // las mejoras antiguas eran de toda la cuenta: pasan al compañero actual (como en la web)
        int d = (gSave.lastChar >= 0 && gSave.lastChar < DEX_N && gSave.owned[gSave.lastChar]) ? gSave.lastChar : STARTERS_IDX[0];
        for (int i = 0; i < NPERM; i++) gSave.pupg[d][i] = gSave.perm[i];
        gSave.pupgMig = 1;
    }
    for (int d = 0; d < DEX_N; d++)
        for (int i = 0; i < NPERM; i++) if (gSave.pupg[d][i] > PERM[i].max) gSave.pupg[d][i] = PERM[i].max;
}
int permLv(int id) { int d = gSave.lastChar; return gSave.pupg[(d >= 0 && d < DEX_N) ? d : 0][id]; }
void saveWrite() {
    mkdir("sdmc:/3ds", 0777);
    FILE* f = fopen(SAVE_PATH, "wb");
    if (f) { fwrite(&gSave, sizeof gSave, 1, f); fclose(f); }
}
int permCost(int id, int lvl) { return (int)(floorf(PERM[id].base * powf(PERM[id].grow, (float)lvl) / 10.0f + 0.5f) * 10); }

// ---------------------------------------------------------------- gacha
const char* GACHA_GEN_NAMES[9] = {"Kanto", "Johto", "Hoenn", "Sinnoh", "Teselia", "Kalos", "Alola", "Galar", "Paldea"};
const float GACHA_RATES[5] = {45, 30, 17, 6.5f, 1.5f};
#define RATES GACHA_RATES
static const int REFUND[6] = {0, 15, 30, 60, 120, 300};

static int rollRarity(int min) {
    float total = 0;
    for (int r = min; r <= 5; r++) total += RATES[r - 1];
    float x = frand() * total;
    for (int r = min; r <= 5; r++) { x -= RATES[r - 1]; if (x <= 0) return r; }
    return 5;
}
static int pickInBanner(int gen, int rarity, int* outRarity) {
    static short list[DEX_N];
    for (int d : {0, -1, 1, -2, 2, -3, 3, -4, 4}) {
        int r = rarity + d;
        if (r < 1 || r > 5) continue;
        int n = 0;
        for (int i = 0; i < DEX_N; i++)
            if (DEX[i].gen == gen && DEX[i].rarity == r && sprHas(DEX_NUM[i])) list[n++] = i;
        if (n) { *outRarity = r; return list[rnd() % n]; }
    }
    *outRarity = rarity;
    return STARTERS_IDX[0];
}
int gachaPull(int gen, int n, PullResult* out, bool useT10) {
    if (n == 10 && useT10) { if (gSave.t10 >= 1) gSave.t10--; else return 0; }     // ticket violeta = 10 normales
    else if (n == 10) { if (gSave.t1 >= 10) gSave.t1 -= 10; else return 0; }
    else { if (gSave.t1 < n) return 0; gSave.t1 -= n; }
    int g = gen - 1;
    bool has4 = false;
    for (int i = 0; i < n; i++) {
        gSave.pity[gen]++;
        int want;
        if (gSave.pity[gen] >= 70) want = 5;
        else if (n == 10 && i == n - 1 && !has4) want = rollRarity(4);
        else want = rollRarity(1);
        int rar;
        int idx = pickInBanner(gen, want, &rar);
        if (rar == 5) gSave.pity[gen] = 0;
        if (rar >= 4) has4 = true;
        PullResult& r = out[i];
        r.dex = idx; r.rarity = rar; r.shiny = false;
        // 1% de shiny; si ya lo tienes se busca otro de la misma rareza al que le falte
        if (frand() * 100 < SHINY_RATE && sprHasShiny(DEX_NUM[idx])) {
            r.shiny = true;
            if (gSave.shiny[idx]) {
                static short alt[DEX_N]; int na = 0;
                for (int k = 0; k < DEX_N; k++)
                    if (DEX[k].gen == gen && DEX[k].rarity == rar && !gSave.shiny[k] && sprHasShiny(DEX_NUM[k])) alt[na++] = k;
                if (na) { idx = alt[rnd() % na]; r.dex = idx; }
            }
        }
        r.isNew = !gSave.owned[idx];
        r.refund = 0;
        if (r.isNew) gSave.owned[idx] = 1;
        if (r.shiny) {
            if (gSave.shiny[idx]) r.refund = REFUND[rar] * 3;
            gSave.shiny[idx] = 1;
            r.isNew = r.isNew || r.refund == 0;
        } else if (!r.isNew) r.refund = REFUND[rar];
        gSave.coins += r.refund;
    }
    (void)g;
    gSave.stat[SB_PULLS] += n;
    achCheck();
    saveWrite();
    return n;
}
