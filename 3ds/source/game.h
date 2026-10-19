// PokéSurvivor 3DS — declaraciones compartidas entre módulos.
#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <initializer_list>
#include <string.h>

#include "gamedata.h"
#include "spritemeta.h"
#include "tiles.h"

#define COL(r, g, b, a) C2D_Color32(r, g, b, a)
static const float TOP_W = 400, TOP_H = 240;
static const float WIN_TIME = 900;          // sobrevivir 15 min = victoria

// ---------- util (core.cpp) ----------
u32 rnd();
float frand();
float frange(float a, float b);
static inline float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
static inline bool inRect(float px, float py, float x, float y, float w, float h) { return px >= x && px <= x + w && py >= y && py <= y + h; }
u32 hash2(int x, int y, int s);               // hash determinista
u32 typeColor(int t, int a = 255);
u32 typeColorDark(int t, int a = 255);
u32 typeColorLight(int t, int a = 255);

// ---------- texto ----------
void textInit();
void textFrame();
void text(const char* s, float x, float y, float sc, u32 col, bool center = false);
void textWrap(const char* s, float x, float y, float w, float sc, u32 col);

// ---------- iconos pixel art (include/icons.h generado) ----------
#include "icons.h"
void iconsLoad();
void icon(int ic, float x, float y, float sc = 0.5f, u32 tint = 0xFFFFFFFF);   // sc 0.5 = 16 px

// ---------- idioma (core.cpp + include/lang.h generado) ----------
enum { LANG_ES, LANG_EN, LANG_FR, LANG_N };
const char* pname(int di);                      // nombre del Pokémon (fila de DEX) en el idioma activo
const char* T(const char* es);                  // traduce un texto en español al idioma activo (si no lo conoce, lo devuelve igual)
const char* typeName(int t);
const char* const LANG_NAMES[LANG_N] = {"Español", "English", "Français"};
// Todo formato de snprintf pasa por T(): las cadenas de printf se traducen solas.
#define snprintf(b, n, f, ...) snprintf(b, n, T(f), ##__VA_ARGS__)

// ---------- sprites (core.cpp) ----------
void sprLoad(int dexNum);                       // lo carga si no está
void sprFreeAll();
bool sprHas(int dexNum);
bool sprHasShiny(int dexNum);
void sprDraw(int dexNum, int dir, u64 ms, bool moving, float x, float y, const C2D_ImageTint* tint, float sc, bool shiny = false);
int dexIndexOf(int dexNum);                     // fila en DEX[] o -1

// ---------- tilesets (core.cpp) ----------
void tilesLoad(int set);
void tilesFree();
void tileDraw(const TCell& c, float x, float y, float z, const C2D_ImageTint* tint = nullptr, float sc = 1.0f);

// ---------- guardado y progreso permanente (core.cpp) ----------
struct MSlot { u8 def, tier, param, claimed; int prog; };   // una misión activa (def = índice en las plantillas)
struct Save {
    u32 magic;
    int coins, t1, t10, best, bestLevel, runs, kills;
    u8 perm[NPERM];
    u8 owned[DEX_N];
    u8 bannedMove[NMOVES];
    int pity[10];
    int lastChar;
    u8 startMove[DEX_N];                        // movimiento inicial elegido por Pokémon (0 = el de siempre)
    float vol;
    u8 lang, langSet;                           // idioma elegido (LANG_*) y si ya se eligió
    u8 shiny[DEX_N];                            // shinies conseguidos
    u8 shinyOn[DEX_N];                          // 1 = usa su versión shiny
    int dayKey, weekKey;                        // misiones: día / semana de la última renovación
    MSlot md[3], mw[2];                         // misiones diarias y semanales
    u8 ach[256];                                // logros ya conseguidos
    u8 legends[DEX_N];                          // legendarios vencidos en una grieta
    int stat[8];                                // SB_*: estadísticas para los logros
    u8 items[16];                               // objetos equipables encontrados
    u8 pupg[DEX_N][NPERM];                      // mejoras de CADA Pokémon (perm[] es el formato antiguo)
    u8 pupgMig;                                 // 1 = perm[] ya pasado al compañero
};
enum { SB_BOSS, SB_EVO, SB_RIFT, SB_PULLS, SB_MIS, SB_JUDGE, SB_JBEST };
extern Save gSave;
void saveLoad();
void saveWrite();
int permCost(int id, int lvl);
float permFloat(int id);                        // helper de lectura de niveles
int permLv(int id);                             // nivel de una mejora del compañero actual (lastChar)
static inline int permLvOf(int di, int id) { return gSave.pupg[di][id]; }
enum { PU_HP, PU_ATK, PU_SPD, PU_CD, PU_DEF, PU_REGEN, PU_MAGNET, PU_XP, PU_COINS, PU_MOVES, PU_CRIT, PU_REROLL, PU_BAN, PU_START };

// ---------- gacha (core.cpp) ----------
struct PullResult { int dex; int rarity; bool isNew; int refund; bool shiny; };
int gachaPull(int gen, int n, PullResult* out, bool useT10 = false);   // devuelve nº de tiradas hechas (0 si no hay tickets)
extern const float GACHA_RATES[5];                // % por rareza 1..5
#define SHINY_RATE 1.0f                           // % de shiny por tirada

// ---------- misiones (missions.cpp) ----------
struct MissionRun { int kills, bosses, chests, evolves, rifts, coins, level, ct1, ct2; float minutes; int killsByType[18]; };
void missionsRefresh();                           // renueva las del día / semana si toca
void missionsReport(const MissionRun& r);         // fin de partida: hace avanzar el progreso
void missionText(const MSlot& m, bool weekly, char* out, int n);
int missionGoal(const MSlot& m, bool weekly);
void missionReward(const MSlot& m, bool weekly, int* t1, int* t10, int* coins);
bool missionDone(const MSlot& m, bool weekly);
bool missionClaim(MSlot& m, bool weekly);         // cobra el premio si está completada

// ---------- logros (achv.cpp) ----------
int achCount();                                   // total de logros
int achCats();
const char* achCatName(int c);
int achInCat(int c, int* out, int max);           // índices de los logros de la categoría
void achInfo(int i, char* name, char* desc, int n, int* tier, long* val, long* goal, bool* done);
void achReward(int i, int* t1, int* t10, int* coins);
int achCheck();                                   // concede los que toquen; devuelve cuántos nuevos (el último en achLast)
extern int achLast;
int achDoneCount();

// ---------- máquina tragaperras del gacha (slots.cpp) ----------
void slotStart(const PullResult* r, int n);
bool slotBusy();
void slotUpdate(float dt);
void slotDraw(u64 ms);                            // pantalla superior
void slotSkip();
u32 rarityColor(int r);
extern const char* GACHA_GEN_NAMES[9];

// ---------- audio (audio.cpp) ----------
void audioInit();
void audioExit();
void audioUpdate();
void musicPlay(int song);                       // -1 para parar
void sfxPlay(int id);
enum { MUS_MENU, MUS_BATTLE, MUS_BOSS, MUS_N };
enum { SFX_HIT, SFX_KILL, SFX_PICK, SFX_LEVEL, SFX_HURT, SFX_SHOOT, SFX_BOOM, SFX_BOSS, SFX_UI, SFX_GACHA, SFX_RARE, SFX_OVER, SFX_BEAM, SFX_N };

// ---------- mundo (play.cpp) ----------
enum PlayState { PS_RUN, PS_LEVELUP, PS_OVER, PS_WIN, PS_BOND, PS_ITEM };
struct MoveInst {
    short id;                                    // índice en MOVES
    u8 lvl, grp;                                 // grp: grupo fusionado (los del mismo grupo se lanzan a la vez)
    float cd;                                    // cuenta atrás
    float v[NK_];                                // valores con mejoras aplicadas
    float dealt;
};
void moveRecompute(MoveInst& m);
float typeMult(int atkType, int t1, int t2);
const char* effLabel(float m);

struct Card {
    int kind;                                    // 0 mov. nuevo, 1 sube mov., 2 estadística
    int arg;                                     // índice de movimiento / id de estadística
    char title[48], desc[96];
    u32 col;
};
struct CardSet { Card c[3]; int n; };

void playReset(int charIdx, const int* startMoves, int nStart);

// ---------- cooperativo local (play.cpp + coop.cpp) ----------
struct CoopIn { s8 jx, jy; u8 btn; u16 cmd; };    // entrada de un jugador en un paso; cmd: 0x8000|kind<<8|arg (carta) · 0x4000|toma (objeto)
struct CoopHello { s16 di; u8 shiny, nStart; s16 start[2]; u8 perm[NPERM]; };
void playResetCoop(int me, const CoopHello* h, u32 seed);
void playCoopTick(float dt, const CoopIn* in);   // paso fijo (1/30 s), idéntico en las dos consolas
void playCoopFrame(float dt);                    // efectos visuales (por fotograma)
u8 playCoopTakeBtn();                            // toques en X/Y/B/A pendientes
u32 playCoopChecksum();
int playCoopPending();                           // niveles por elegir del jugador local
int playCoopBond();                              // vínculo por decidir: 1 = yo · 2 = el compañero
bool playCoopDead();
void playCoopPartner(float* x, float* y, float* hpFrac, bool* dead);
int playCoopPartnerDi();
bool playCoopActive();
u32 rngGet();
void rngSet(u32 s);
enum { CN_OFF = 0, CN_HOST, CN_SCAN };
bool coopOpen(); void coopStop(); void coopClose();
bool coopHost(); void coopScanStep(); int coopMode(); bool coopIsHost(); bool coopLinked();
void coopHelloSet(const CoopHello& h);
int coopHandshake(int* me, CoopHello* h2, u32* seed);   // 0 espera · 1 listo · -1 versión distinta
bool coopPeerLeft();
void coopRunBegin(int me);
void coopQueueCmd(u16 c); int coopInFlight(); int coopExec();
void coopPushLocal(s8 jx, s8 jy, u8 btn);
int coopSched(); int coopDelay(); bool coopReady(int t);
void coopInputs(int t, CoopIn* out); void coopDone(int t, u32 chk);
int coopPump();                                  // 0 bien · 1 salió · 2 desincronizado · 3 sin conexión
void coopLeave();
void playUpdate(float dt, u32 down, u32 held, int jx, int jy);
void playDraw(u64 ms);                          // pantalla superior
void playPreloadSprites();
PlayState playState();
void playSetState(PlayState s);
void playBuildCards(CardSet& cs);
void playApplyCard(const Card& c);
bool playReroll(CardSet& cs);                    // true si quedaban cambios
int playRerolls();
extern int gSlotMove[4];                         // MoveInst del jugador en cada botón (-1 = vacío)
extern MoveInst* gMovesL;                        // movimientos del jugador de esta consola
#define gMoves gMovesL
extern int gNMoves;
bool playIsActive(int b);                        // ¿se lanza este botón? (el grupo activo)
int playGrp(int b);
int playGroupSize(int b);
int playBonds();
int playBondNeed();                              // 0 nada · 1 añadir a un grupo · 2 unir dos sueltos
bool playBondLoose(int b);
void playBondApply(const int* btns, int n);
void playBondSkip();
int playWeather(float* left);                    // 0 ninguno; 1 sol 2 lluvia 3 arena 4 nieve 5 niebla
const char* weatherName(int k);
u32 weatherColor(int k);
struct RunStats { float time; int kills, level, bosses, coins, t1, t10, jdowns; bool won; };
// objetos equipables (uno por partida)
int itemCount();
const char* itemName(int i);
const char* itemDesc(int i);
int playItem();                                   // equipado (-1 = ninguno)
int playItemNew();                                // el que se acaba de encontrar (al elegir)
void playItemChoose(bool takeNew);
RunStats playStats();
MissionRun playMissionStats();
void playHud(u64 ms);                            // datos para la pantalla inferior
float playHpFrac();
float playXpFrac();
int playLevel();
float playTime();
int playKills();
int playCoins();
int playCharIdx();
void playFireButton(int b);
float playCdFrac(int b);
void playSwapSlots(int a, int b);
bool playHasItem();
int playItem();
