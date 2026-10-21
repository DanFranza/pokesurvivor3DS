// Cooperativo local 3DS ↔ 3DS (red inalámbrica local UDS, sin servidores).
// Las dos consolas ejecutan la misma simulación y sólo se intercambian las entradas (lockstep).
#include "game.h"
#include <malloc.h>

#define WLANID  0x50534D32u
#define CHAN    1
#define DELAY   3                         // ticks de retardo de entrada
#define RING    256
#define PROTO   (0x50530100u ^ (u32)DEX_N ^ ((u32)NMOVES << 16))

enum { PK_INPUT = 1, PK_HELLO = 2, PK_BYE = 3, PK_START = 4 };
static const char PASS[] = "PokeSurvivor3DS";

static bool gOpen, gIsHost, gLinkOk;
static int gMode = CN_OFF;
static udsBindContext gBind;
static udsNetworkStruct gNet;
static u16 gPeer;
static u64 gLastRx, gLastTx, gLastLink;

// handshake
static CoopHello gMyHello, gPeerHello;
static bool gHavePeer, gPeerGot, gSeedRx, gSeedSet, gBadProto;
static u32 gSeed;

// partida
static int gMe, gExec, gSched, gNeed, gPeerNeed;
static CoopIn gIn[2][RING];
static int gTickOf[2][RING];
static struct { int t; u32 v; } gChk[8];
static int gLastChkT = -1; static u32 gLastChkV;
static bool gDesync, gPeerLeft, gPeerIn;
static u16 gCmdQ[8]; static int gCmdN, gInFlight;

bool coopOpen() {
    if (gOpen) return true;
    if (R_FAILED(udsInit(0x3000, nullptr))) return false;
    gOpen = true; gMode = CN_OFF;
    return true;
}
void coopStop() {
    if (!gOpen) return;
    if (gMode == CN_HOST) udsDestroyNetwork();
    else if (gMode != CN_OFF) udsDisconnectNetwork();
    if (gMode == CN_HOST || gMode != CN_OFF) udsUnbind(&gBind);
    gMode = CN_OFF; gLinkOk = false;
}
void coopClose() {
    if (!gOpen) return;
    coopStop();
    udsExit();
    gOpen = false;
}
bool coopHost() {
    if (!gOpen) return false;
    udsGenerateDefaultNetworkStruct(&gNet, WLANID, 0, 2);
    if (R_FAILED(udsCreateNetwork(&gNet, PASS, sizeof PASS, &gBind, CHAN, UDS_DEFAULT_RECVBUFSIZE))) return false;
    gMode = CN_HOST; gIsHost = true; gPeer = 2; gLastLink = osGetTime();
    return true;
}
void coopScanStep() {
    if (!gOpen || gMode != CN_OFF) return;
    static u8 buf[0x4000] __attribute__((aligned(4)));
    udsNetworkScanInfo* nets = nullptr; size_t total = 0;
    Result r = udsScanBeacons(buf, sizeof buf, &nets, &total, WLANID, 0, nullptr, false);
    if (R_SUCCEEDED(r) && nets && total > 0) {
        r = udsConnectNetwork(&nets[0].network, PASS, sizeof PASS, &gBind, UDS_BROADCAST_NETWORKNODEID, UDSCONTYPE_Client, CHAN, UDS_DEFAULT_RECVBUFSIZE);
        if (R_SUCCEEDED(r)) { gMode = CN_SCAN; gIsHost = false; gPeer = 1; gLastLink = osGetTime(); }
    }
    if (nets) free(nets);
}
int coopMode() { return gMode; }
bool coopIsHost() { return gIsHost; }
bool coopLinked() {
    if (!gOpen || gMode == CN_OFF) return false;
    udsConnectionStatus st;
    if (R_FAILED(udsGetConnectionStatus(&st))) return false;
    return st.total_nodes >= 2;
}

// ---------------------------------------------------------------- paquetes
static void sendPkt(const void* b, size_t n) { udsSendTo(gPeer, CHAN, UDS_SENDFLAG_Default, b, n); }
static void put32(u8*& p, u32 v) { memcpy(p, &v, 4); p += 4; }
static u32 get32(const u8*& p) { u32 v; memcpy(&v, p, 4); p += 4; return v; }

static void sendHello() {
    u8 b[64]; u8* p = b;
    *p++ = PK_HELLO; put32(p, PROTO); *p++ = gHavePeer ? 1 : 0;
    memcpy(p, &gMyHello, sizeof gMyHello); p += sizeof gMyHello;
    sendPkt(b, p - b);
}
static void sendStart() { u8 b[8]; u8* p = b; *p++ = PK_START; put32(p, gSeed); sendPkt(b, p - b); }
static void sendBye() { u8 b = PK_BYE; for (int i = 0; i < 3; i++) sendPkt(&b, 1); }
static void sendInput() {
    u8 b[256]; u8* p = b;
    int first = gPeerNeed, cnt = gSched - first;
    if (cnt < 0) cnt = 0;
    if (cnt > 24) cnt = 24;
    *p++ = PK_INPUT; put32(p, (u32)gNeed); put32(p, (u32)first); *p++ = (u8)cnt;
    put32(p, (u32)gLastChkT); put32(p, gLastChkV);
    for (int k = 0; k < cnt; k++) {
        const CoopIn& c = gIn[gMe][(first + k) % RING];
        *p++ = (u8)c.jx; *p++ = (u8)c.jy; *p++ = c.btn; memcpy(p, &c.cmd, 2); p += 2;
    }
    sendPkt(b, p - b);
}

static void onInput(const u8* p, size_t n) {
    if (n < 18) return;
    const u8* e = p + n; p++;
    int need = (int)get32(p), first = (int)get32(p), cnt = *p++;
    int ct = (int)get32(p); u32 cv = get32(p);
    if (e - p < cnt * 5) return;
    if (need > gPeerNeed) gPeerNeed = need;
    int peer = gMe ^ 1;
    for (int k = 0; k < cnt; k++) {
        CoopIn c; c.jx = (s8)p[0]; c.jy = (s8)p[1]; c.btn = p[2]; memcpy(&c.cmd, p + 3, 2); p += 5;
        int t = first + k;
        if (t < gExec || t >= gExec + 128) continue;
        gIn[peer][t % RING] = c; gTickOf[peer][t % RING] = t;
    }
    while (gTickOf[peer][gNeed % RING] == gNeed) gNeed++;
    gPeerIn = true;
    if (ct >= 0 && gChk[(ct / 60) % 8].t == ct && gChk[(ct / 60) % 8].v != cv) gDesync = true;
}
static void recvAll() {
    if (!gOpen || gMode == CN_OFF) return;
    static u8 buf[UDS_DATAFRAME_MAXSIZE];
    for (int guard = 0; guard < 40; guard++) {
        if (!udsWaitDataAvailable(&gBind, false, false)) break;
        size_t got = 0; u16 src = 0;
        if (R_FAILED(udsPullPacket(&gBind, buf, sizeof buf, &got, &src)) || got == 0) break;
        gLastRx = osGetTime();
        const u8* p = buf + 1;
        switch (buf[0]) {
            case PK_HELLO:
                if (got >= 6 + sizeof(CoopHello)) {
                    u32 pr = get32(p); u8 fl = *p++;
                    if (pr != PROTO) { gBadProto = true; break; }
                    memcpy(&gPeerHello, p, sizeof gPeerHello);
                    gHavePeer = true; gPeerGot = fl & 1;
                }
                break;
            case PK_START: if (got >= 5) { gSeed = get32(p); gSeedRx = true; } break;
            case PK_INPUT: onInput(buf, got); break;
            case PK_BYE: gPeerLeft = true; break;
        }
    }
}

// ---------------------------------------------------------------- acuerdo previo
void coopHelloSet(const CoopHello& h) {
    gMyHello = h;
    gHavePeer = gPeerGot = gSeedRx = gSeedSet = gBadProto = gPeerLeft = false;
    gLastRx = gLastTx = osGetTime();
}
// 0 = esperando · 1 = listo para empezar · -1 = versiones distintas
int coopHandshake(int* me, CoopHello* h2, u32* seed) {
    recvAll();
    if (gBadProto) return -1;
    u64 now = osGetTime();
    if (now - gLastTx >= 120) {
        gLastTx = now;
        sendHello();
        if (gIsHost && gHavePeer && gPeerGot) {
            if (!gSeedSet) { gSeed = (u32)(now * 2654435761u) ^ rnd(); if (!gSeed) gSeed = 1; gSeedSet = true; }
            sendStart();
        }
    }
    bool ready = gIsHost ? (gSeedSet && gHavePeer && gPeerGot) : (gSeedRx && gHavePeer);
    if (!ready) return 0;
    *me = gIsHost ? 0 : 1;
    h2[*me] = gMyHello; h2[*me ^ 1] = gPeerHello;
    *seed = gSeed;
    return 1;
}
bool coopPeerLeft() { return gPeerLeft; }

// ---------------------------------------------------------------- partida
void coopRunBegin(int me) {
    gMe = me; gExec = 0; gSched = gNeed = gPeerNeed = DELAY;
    memset(gIn, 0, sizeof gIn);
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < RING; i++) gTickOf[p][i] = -1;
        for (int t = 0; t < DELAY; t++) gTickOf[p][t] = t;
    }
    for (int i = 0; i < 8; i++) gChk[i].t = -1;
    gLastChkT = -1; gLastChkV = 0; gDesync = gPeerLeft = gPeerIn = false;
    gCmdN = gInFlight = 0;
    gLastRx = osGetTime(); gLastTx = 0; gLastLink = gLastRx;
}
void coopQueueCmd(u16 c) { if (gCmdN < 8) { gCmdQ[gCmdN++] = c; gInFlight++; } }
int coopInFlight() { return gInFlight; }
int coopExec() { return gExec; }
// entrada local para el siguiente tick aún sin programar
void coopPushLocal(s8 jx, s8 jy, u8 btn) {
    CoopIn c; c.jx = jx; c.jy = jy; c.btn = btn; c.cmd = 0;
    if (gCmdN > 0) { c.cmd = gCmdQ[0]; for (int i = 1; i < gCmdN; i++) gCmdQ[i - 1] = gCmdQ[i]; gCmdN--; }
    gIn[gMe][gSched % RING] = c; gTickOf[gMe][gSched % RING] = gSched;
    gSched++;
}
int coopSched() { return gSched; }
int coopDelay() { return DELAY; }
bool coopReady(int t) { return gTickOf[gMe ^ 1][t % RING] == t && gTickOf[gMe][t % RING] == t; }
void coopInputs(int t, CoopIn* out) { out[0] = gIn[0][t % RING]; out[1] = gIn[1][t % RING]; }
void coopDone(int t, u32 chk) {
    if (gIn[gMe][t % RING].cmd && gInFlight > 0) gInFlight--;
    if (t % 60 == 0) { gChk[(t / 60) % 8].t = t; gChk[(t / 60) % 8].v = chk; gLastChkT = t; gLastChkV = chk; }
    gExec = t + 1;
}
// envío periódico + estado: 0 bien · 1 compañero salió · 2 desincronizado · 3 sin conexión
int coopPump() {
    recvAll();
    u64 now = osGetTime();
    if (gPeerLeft) return 1;
    if (gDesync) return 2;
    if (now - gLastRx > 6000) return 3;
    if (now - gLastLink > 1000) { gLastLink = now; if (!coopLinked()) return 3; }
    if (gIsHost && !gPeerIn && now - gLastTx >= 150) { gLastTx = now; sendStart(); }
    sendInput();
    return 0;
}
void coopLeave() { if (gOpen && gMode != CN_OFF) sendBye(); }
