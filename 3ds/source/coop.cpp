// Cooperativo local 3DS ↔ 3DS (red inalámbrica local UDS, sin servidores).
// Las dos consolas ejecutan la misma simulación y sólo se intercambian las entradas (lockstep).
#include "game.h"
#include <malloc.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>

#define WLANID  0x50534D32u
#define CHAN    1
#define DELAY   3                         // ticks de retardo de entrada
#define RING    256
#define PROTO   (0x50530300u ^ (u32)DEX_N ^ ((u32)NMOVES << 16))

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

// El servidor empareja dos clientes y reenvía los paquetes con longitud de 2 bytes.
static bool gRemote, gRemoteReady, gRemoteBad, gRemoteConnecting;
static int gRemoteFd = -1;
static u8 gRemoteRx[16384], gRemoteTx[16384];
static size_t gRxN, gTxN;
static u64 gConnectAt;
static char gRoomCode[7], gPeerNick[13];
static int gRemoteError;
static void remotePoll() {
    if (!gRemote || gRemoteBad || gRemoteFd < 0) return;
    if (gRemoteConnecting) {
        pollfd p = {gRemoteFd, POLLOUT, 0};
        int r = poll(&p, 1, 0);
        if (r <= 0) { if (osGetTime() - gConnectAt > 8000) gRemoteBad = true; return; }
        int err = 0; socklen_t len = sizeof err;
        if (getsockopt(gRemoteFd, SOL_SOCKET, SO_ERROR, &err, &len) < 0 || err) { gRemoteBad = true; return; }
        gRemoteConnecting = false;
    }
    while (gTxN) {
        ssize_t n = send(gRemoteFd, gRemoteTx, gTxN, 0);
        if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) break;
        if (n <= 0) { gRemoteBad = true; return; }
        memmove(gRemoteTx, gRemoteTx + n, gTxN - n); gTxN -= n;
    }
    bool closed = false;
    while (gRxN < sizeof gRemoteRx) {
        ssize_t n = recv(gRemoteFd, gRemoteRx + gRxN, sizeof gRemoteRx - gRxN, 0);
        if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) break;
        if (n <= 0) { closed = true; break; }
        gRxN += n;
    }
    while (!gRemoteReady) {
        size_t end = 0; while (end < gRxN && gRemoteRx[end] != '\n') end++;
        if (end == gRxN) { if (gRxN > 80) gRemoteBad = true; break; }
        char line[82]; if (end >= sizeof line) { gRemoteBad = true; break; }
        memcpy(line, gRemoteRx, end); line[end] = 0;
        memmove(gRemoteRx, gRemoteRx + end + 1, gRxN - end - 1); gRxN -= end + 1;
        if (!strncmp(line, "ROOM ", 5) && strlen(line + 5) == 6) snprintf(gRoomCode, sizeof gRoomCode, "%s", line + 5);
        else if (!strncmp(line, "PAIR", 4) && (line[4] == '0' || line[4] == '1') && line[5] == ' ' && line[6]) {
            gIsHost = line[4] == '0'; snprintf(gPeerNick, sizeof gPeerNick, "%.12s", line + 6); gRemoteReady = true;
        } else if (!strcmp(line, "ERR ROOM")) { gRemoteError = 1; gRemoteBad = true; }
        else if (!strcmp(line, "ERR VERSION")) { gRemoteError = 2; gRemoteBad = true; }
        else { gRemoteError = 3; gRemoteBad = true; }
    }
    if (closed || gRxN == sizeof gRemoteRx) gRemoteBad = true;
}
bool coopOnlineStart(const char* addr, int mode, const char* code, const char* nick) {
    if (!onlineNetInit()) return false;
    char host[48]; snprintf(host, sizeof host, "%s", addr);
    int port = 25570; char* sep = strrchr(host, ':');
    if (sep) { *sep++ = 0; port = atoi(sep); }
    if (!*host || port < 1 || port > 65535) return false;
    char ps[8]; snprintf(ps, sizeof ps, "%d", port);
    addrinfo hint = {}; hint.ai_family = AF_INET; hint.ai_socktype = SOCK_STREAM;
    addrinfo* ai = nullptr;
    if (getaddrinfo(host, ps, &hint, &ai) != 0 || !ai) return false;
    int fd = socket(ai->ai_family, ai->ai_socktype, 0);
    if (fd < 0) { freeaddrinfo(ai); return false; }
    int noDelay = 1; setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &noDelay, sizeof noDelay);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    int r = connect(fd, ai->ai_addr, ai->ai_addrlen); freeaddrinfo(ai);
    if (r < 0 && errno != EINPROGRESS && errno != EAGAIN) { closesocket(fd); return false; }
    gRemoteFd = fd; gRemote = gOpen = true; gRemoteReady = gRemoteBad = false;
    gRemoteConnecting = r < 0; gConnectAt = osGetTime(); gMode = CN_SCAN;
    gRxN = 0; gRoomCode[0] = gPeerNick[0] = 0; gRemoteError = 0;
    const char* kind = mode == 0 ? "CREATE" : mode == 1 ? "JOIN" : "PUBLIC";
    int n = mode == 1 ? snprintf((char*)gRemoteTx, sizeof gRemoteTx, "PLAY %s %08x %s %s\n", kind, (unsigned)PROTO, nick, code)
                      : snprintf((char*)gRemoteTx, sizeof gRemoteTx, "PLAY %s %08x %s\n", kind, (unsigned)PROTO, nick);
    if (n <= 0 || (size_t)n >= sizeof gRemoteTx) { closesocket(fd); gOpen = gRemote = false; gRemoteFd = -1; gMode = CN_OFF; return false; }
    gTxN = (size_t)n;
    return true;
}
const char* coopOnlineCode() { return gRoomCode; }
const char* coopOnlinePeer() { return gPeerNick; }
int coopOnlineError() { return gRemoteError; }
bool coopOnlineActive() { return gRemote; }
bool coopOnlineFailed() { if (gRemote) remotePoll(); return gRemoteBad; }

bool coopOpen() {
    if (gOpen) return true;
    if (R_FAILED(udsInit(0x3000, nullptr))) return false;
    gOpen = true; gMode = CN_OFF;
    return true;
}
void coopStop() {
    if (!gOpen) return;
    if (gRemote) { if (gRemoteFd >= 0) closesocket(gRemoteFd); gRemoteFd = -1; gRemote = gRemoteReady = gRemoteBad = false; gOpen = false; gMode = CN_OFF; return; }
    if (gMode == CN_HOST) udsDestroyNetwork();
    else if (gMode != CN_OFF) udsDisconnectNetwork();
    if (gMode == CN_HOST || gMode != CN_OFF) udsUnbind(&gBind);
    gMode = CN_OFF; gLinkOk = false;
}
void coopClose() {
    if (!gOpen) return;
    bool remote = gRemote;
    coopStop();
    if (!remote) udsExit();
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
    if (gRemote) { remotePoll(); return gRemoteReady && !gRemoteBad; }
    udsConnectionStatus st;
    if (R_FAILED(udsGetConnectionStatus(&st))) return false;
    return st.total_nodes >= 2;
}

// ---------------------------------------------------------------- paquetes
static void sendPkt(const void* b, size_t n) {
    if (!gRemote) { udsSendTo(gPeer, CHAN, UDS_SENDFLAG_Default, b, n); return; }
    if (!gRemoteReady || gRemoteBad || n > 256 || gTxN + n + 2 > sizeof gRemoteTx) { gRemoteBad = true; return; }
    gRemoteTx[gTxN++] = (u8)(n >> 8); gRemoteTx[gTxN++] = (u8)n;
    memcpy(gRemoteTx + gTxN, b, n); gTxN += n;
    remotePoll();
}
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
        size_t got = 0; u16 src = 0;
        if (gRemote) {
            remotePoll(); if (gRemoteBad || gRxN < 2) break;
            got = ((size_t)gRemoteRx[0] << 8) | gRemoteRx[1];
            if (!got || got > sizeof buf) { gRemoteBad = true; break; }
            if (gRxN < got + 2) break;
            memcpy(buf, gRemoteRx + 2, got); memmove(gRemoteRx, gRemoteRx + got + 2, gRxN - got - 2); gRxN -= got + 2;
        } else {
            if (!udsWaitDataAvailable(&gBind, false, false)) break;
            if (R_FAILED(udsPullPacket(&gBind, buf, sizeof buf, &got, &src)) || got == 0) break;
        }
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
