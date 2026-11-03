// Cliente online: una conexión TCP corta por consulta (hilo aparte para no bloquear el juego).
#include "game.h"
#undef snprintf
#include <malloc.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>

OnRow gOnRows[10]; int gOnN, gOnMyRank, gOnTotal;

static bool gSoc; static u32* gSocBuf;
static Thread gTh; static bool gThOn;
static volatile int gSt;                    // 0 libre · 1 en curso · 2 listo · 3 error
static char gHost[48], gReq[192], gRes[1536], gErr[40];

static int waitFd(int fd, short ev, int ms) { pollfd p = {fd, ev, 0}; return poll(&p, 1, ms); }

static void worker(void*) {
    char host[48]; strncpy(host, gHost, sizeof host); host[sizeof host - 1] = 0;
    int port = ONLINE_PORT;
    if (char* c = strrchr(host, ':')) { *c = 0; port = atoi(c + 1); if (port <= 0 || port > 65535) port = ONLINE_PORT; }
    gRes[0] = 0;
    char ps[8]; snprintf(ps, sizeof ps, "%d", port);
    addrinfo hint; memset(&hint, 0, sizeof hint); hint.ai_family = AF_INET; hint.ai_socktype = SOCK_STREAM;
    addrinfo* ai = nullptr;
    if (!*host || getaddrinfo(host, ps, &hint, &ai) != 0 || !ai) { strcpy(gErr, "Servidor no encontrado"); gSt = 3; return; }
    int fd = socket(ai->ai_family, ai->ai_socktype, 0);
    if (fd < 0) { freeaddrinfo(ai); strcpy(gErr, "Sin red"); gSt = 3; return; }
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    int r = connect(fd, ai->ai_addr, ai->ai_addrlen);
    freeaddrinfo(ai);
    if (r < 0 && errno != EINPROGRESS && errno != EAGAIN) { closesocket(fd); strcpy(gErr, "No se pudo conectar"); gSt = 3; return; }
    if (r < 0 && waitFd(fd, POLLOUT, 5000) <= 0) { closesocket(fd); strcpy(gErr, "No se pudo conectar"); gSt = 3; return; }
    size_t sent = 0, len = strlen(gReq);
    while (sent < len) {
        if (waitFd(fd, POLLOUT, 3000) <= 0) break;
        ssize_t n = send(fd, gReq + sent, len - sent, 0);
        if (n <= 0 && errno != EAGAIN) break;
        if (n > 0) sent += n;
    }
    size_t got = 0; u64 t0 = osGetTime();
    while (sent == len && got < sizeof gRes - 1 && osGetTime() - t0 < 6000) {
        if (waitFd(fd, POLLIN, 1000) <= 0) continue;
        ssize_t n = recv(fd, gRes + got, sizeof gRes - 1 - got, 0);
        if (n == 0) break;
        if (n > 0) got += n;
        gRes[got] = 0;
        if (strstr(gRes, "\nEND ") || !strncmp(gRes, "END ", 4) || !strncmp(gRes, "ERR ", 4)) break;
    }
    gRes[got] = 0;
    closesocket(fd);
    if (!got) { strcpy(gErr, "Sin respuesta"); gSt = 3; return; }
    gSt = 2;
}

static void reap() {
    if (gThOn && gSt != 1) { threadJoin(gTh, 1000000000ULL); threadFree(gTh); gThOn = false; }
}
bool onlineBusy() { return gSt == 1; }
int onlineState() { return gSt; }
const char* onlineError() { return gErr; }

bool onlineNetInit() {
    if (gSoc) return true;
    gSocBuf = (u32*)memalign(0x1000, 0x20000);
    if (!gSocBuf) return false;
    if (R_FAILED(socInit(gSocBuf, 0x20000))) { free(gSocBuf); gSocBuf = nullptr; return false; }
    gSoc = true; return true;
}

bool onlineQuery(const char* addr, int cat) {
    if (gSt == 1) return false;
    reap();
    if (!onlineNetInit()) { strcpy(gErr, "Sin red"); gSt = 3; return false; }
    if (!gSave.nick[0]) { strcpy(gErr, "Elige un pseudo"); gSt = 3; return false; }
    strncpy(gHost, addr, sizeof gHost - 1); gHost[sizeof gHost - 1] = 0;
    snprintf(gReq, sizeof gReq, "HELLO 1 %08x %s %d %d %d %u\nTOP %d\n", (unsigned)gSave.seed, gSave.nick,
             gSave.best, gSave.kills, gSave.bestLevel, (unsigned)gSave.wins, cat);
    gSt = 1; gErr[0] = 0;
    gTh = threadCreate(worker, nullptr, 32 * 1024, 0x30, -2, false);
    if (!gTh) { gSt = 3; strcpy(gErr, "Sin red"); return false; }
    gThOn = true;
    return true;
}

bool onlineFinish() {
    if (gSt == 3) { reap(); gSt = 0; return false; }
    if (gSt != 2) return false;
    reap();
    gSt = 0; gOnN = 0; gOnMyRank = gOnTotal = 0;
    bool end = false;
    for (char* line = strtok(gRes, "\n"); line; line = strtok(nullptr, "\n")) {
        if (!strncmp(line, "ERR ", 4)) {
            strcpy(gErr, !strcmp(line + 4, "NAMETAKEN") ? "Pseudo ya usado" : !strcmp(line + 4, "NICK") ? "Pseudo no válido" : !strcmp(line + 4, "FULL") ? "Servidor lleno" : "Servidor incompatible");
            return false;
        }
        if (!strncmp(line, "ROW ", 4) && gOnN < 10) {
            int rk, v; char nk[32];
            if (sscanf(line + 4, "%d %31s %d", &rk, nk, &v) == 3) { strncpy(gOnRows[gOnN].nick, nk, 15); gOnRows[gOnN].nick[15] = 0; gOnRows[gOnN].val = v; gOnN++; }
        } else if (!strncmp(line, "END ", 4)) { sscanf(line + 4, "%d %d", &gOnMyRank, &gOnTotal); end = true; }
    }
    if (!end) strcpy(gErr, "Respuesta no válida");
    return end;
}
void onlineExit() {
    if (gThOn) { threadJoin(gTh, 8000000000ULL); threadFree(gTh); gThOn = false; }
    if (gSoc) { socExit(); free(gSocBuf); gSoc = false; }
}
