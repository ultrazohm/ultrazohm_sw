/*----------------------------------------------------------------------------
| File:
|   platform_freertos.c
|
| Description:
|   FreeRTOS/lwIP implementation of the platform abstraction layer.
|
|   This file is the AArch64 FreeRTOS replacement for platform.c.
|   platform.c (Linux/Windows/POSIX) is renamed platform.c.linux_EXCLUDED
|   so that Vitis subdir.mk no longer picks it up.
|
|   Implements:
|     - Sleep        : vTaskDelay-based sleepUs / sleepMs
|     - Mutex        : xSemaphoreCreateRecursiveMutex / xSemaphoreTakeRecursive
|     - Memory       : malloc/free wrappers (platformMemAlloc/Free)
|     - Sockets      : lwIP UDP path (OPTION_FREERTOS_LWIP)
|     - Clock        : xTaskGetTickCount-based clock functions
|
|   Ported from XCPlite v2.1.1 (MIT), Vector Informatik GmbH.
|   UltraZohm integration: Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

/* Force FreeRTOS platform path even if the build system does not pass -D_FREE_RTOS.
 * All other translation units must still receive -D_FREE_RTOS (or equivalent) via
 * the compiler command line so that platform.h resolves MUTEX to SemaphoreHandle_t
 * consistently across the whole build. */
#ifndef _FREE_RTOS
#define _FREE_RTOS
#endif

#include "platform.h"   /* pulls in FreeRTOS.h, semphr.h, task.h for _FREE_RTOS */

#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memset, memcpy */
#include <errno.h>      /* errno */

#include "xcplib_cfg.h"
#include "assert.h"
#include "dbg_print.h"


/**************************************************************************/
/* Sleep                                                                   */
/**************************************************************************/

/* Minimum granularity is one tick (1 ms at configTICK_RATE_HZ = 1000).
 * Sub-millisecond requests are rounded up to one tick. */
void sleepUs(uint32_t us) {
    TickType_t ticks = (us * configTICK_RATE_HZ) / 1000000UL;
    vTaskDelay(ticks == 0U ? 1U : ticks);
}

void sleepMs(uint32_t ms) {
    vTaskDelay(pdMS_TO_TICKS(ms == 0U ? 1U : ms));
}


/**************************************************************************/
/* Memory mapping                                                          */
/**************************************************************************/

/* platformMemAlloc / platformMemFree are declared in platform.h without a
 * FreeRTOS guard. On bare-metal FreeRTOS we simply delegate to the heap.
 * OPTION_SHM_MODE is not enabled for this target, so these are never called
 * in practice, but the linker needs definitions to satisfy the declaration. */
void *platformMemAlloc(size_t size) {
    return malloc(size);
}

void platformMemFree(void *ptr, size_t size) {
    (void)size;
    free(ptr);
}


/**************************************************************************/
/* Mutex                                                                   */
/**************************************************************************/

void mutexInit(MUTEX *m, bool recursive, uint32_t spinCount) {
    (void)spinCount;
    *m = recursive ? xSemaphoreCreateRecursiveMutex() : xSemaphoreCreateMutex();
    assert(*m != NULL); /* heap exhausted – increase configTOTAL_HEAP_SIZE */
}

void mutexDestroy(MUTEX *m) {
    if (m != NULL && *m != NULL) {
        vSemaphoreDelete(*m);
        *m = NULL;
    }
}


/**************************************************************************/
/* Sockets (FreeRTOS / lwIP)                                              */
/**************************************************************************/

#if defined(OPTION_ENABLE_TCP) || defined(OPTION_ENABLE_UDP)

#ifdef OPTION_ENABLE_TCP
#error "FreeRTOS TCP socket functions not implemented. Undefine OPTION_ENABLE_TCP for FreeRTOS builds."
#endif

/* Human-readable error string (uses lwIP errno values mapped to POSIX codes) */
const char *socketGetErrorString(int32_t err) {
    return strerror(err);
}

/* socketStartup: lwIP networking is initialised by the application (tcpip_init).
 * Nothing to do here. */
bool socketStartup(void) {
    return true;
}

void socketCleanup(void) {
    /* no-op for lwIP */
}

#if defined(OPTION_FREERTOS_LWIP)

#include "lwip/errno.h"   /* lwIP errno values */
#include "lwip/sockets.h" /* lwip_socket, lwip_bind, lwip_sendto, lwip_recvfrom,
                             lwip_close, lwip_shutdown, lwip_setsockopt */

/* Create a UDP socket */
bool socketOpen(SOCKET_HANDLE *socketp, uint16_t flags) {
    assert(socketp != NULL);
    assert(!(flags & SOCKET_MODE_TCP)); /* TCP not supported on FreeRTOS/lwIP */

    int sock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        DBG_PRINTF_ERROR("socketOpen: lwip_socket failed (errno=%d,%s)\n",
                         errno, socketGetErrorString(errno));
        return false;
    }
    if (flags & SOCKET_MODE_REUSEADDR) {
        int yes = 1;
        if (lwip_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
            DBG_PRINTF_WARNING("socketOpen: SO_REUSEADDR failed (errno=%d,%s)\n",
                               errno, socketGetErrorString(errno));
        }
    }
    *socketp = sock;
    DBG_PRINTF5("socketOpen: lwIP UDP socket %d opened\n", sock);
    return true;
}

/* Bind socket to a local address and port.
 * addr == NULL or addr[0] == 0  →  bind to INADDR_ANY */
bool socketBind(SOCKET_HANDLE socket, const uint8_t *addr, uint16_t port) {
    assert(socket != INVALID_SOCKET_HANDLE);
    struct sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_port   = htons(port);
    if (addr != NULL && addr[0] != 0) {
        a.sin_addr.s_addr = *(const uint32_t *)addr;
    } else {
        a.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    if (lwip_bind(socket, (struct sockaddr *)&a, sizeof(a)) < 0) {
        DBG_PRINTF_ERROR("socketBind: lwip_bind failed (errno=%d,%s) on port %u\n",
                         errno, socketGetErrorString(errno), port);
        return false;
    }
    DBG_PRINTF5("socketBind: bound to port %u\n", port);
    return true;
}

/* Unblock a thread blocked in socketRecvFrom */
bool socketShutdown(SOCKET_HANDLE socket) {
    if (socket != INVALID_SOCKET_HANDLE) {
        lwip_shutdown(socket, SHUT_RDWR);
    }
    return true;
}

/* Close socket and set *socketp to INVALID */
bool socketClose(SOCKET_HANDLE *socketp) {
    assert(socketp != NULL);
    if (*socketp != INVALID_SOCKET_HANDLE) {
        lwip_close(*socketp);
        *socketp = INVALID_SOCKET_HANDLE;
    }
    return true;
}

/* Receive a UDP datagram (blocking).
 * Returns: >0 bytes received, 0 on timeout/EAGAIN, -1 on error */
int16_t socketRecvFrom(SOCKET_HANDLE socket, uint8_t *buffer, uint16_t bufferSize,
                       uint8_t *srcAddr, uint16_t *srcPort, uint64_t *time) {
    assert(socket != INVALID_SOCKET_HANDLE);
    struct sockaddr_in src;
    socklen_t srclen = sizeof(src);
    memset(&src, 0, sizeof(src));

    int16_t n = (int16_t)lwip_recvfrom(socket, buffer, bufferSize, 0,
                                        (struct sockaddr *)&src, &srclen);
    if (n == 0) {
        return 0; /* zero-length datagram or graceful close */
    }
    if (n < 0) {
        int32_t err = errno;
        if (socketTimeout(err)) {
            return 0; /* timeout – caller loops and does background work */
        }
        DBG_PRINTF_ERROR("socketRecvFrom: lwip_recvfrom failed (errno=%d,%s)\n",
                         err, socketGetErrorString(err));
        return -1;
    }
    if (srcAddr != NULL) {
        memcpy(srcAddr, &src.sin_addr.s_addr, 4);
    }
    if (srcPort != NULL) {
        *srcPort = ntohs(src.sin_port);
    }
    if (time != NULL) {
        *time = clockGet(); /* no hardware timestamps; use XCP clock */
    }
    return n;
}

/* Send a UDP datagram to addr:port.
 * Returns: bytes sent, 0 on closed socket, -1 on error */
int16_t socketSendTo(SOCKET_HANDLE socket, const uint8_t *buffer, uint16_t bufferSize,
                     const uint8_t *addr, uint16_t port, uint64_t *time) {
    assert(socket != INVALID_SOCKET_HANDLE);
    assert(addr != NULL);
    struct sockaddr_in dst;
    memset(&dst, 0, sizeof(dst));
    dst.sin_family      = AF_INET;
    dst.sin_port        = htons(port);
    dst.sin_addr.s_addr = *(const uint32_t *)addr;

    if (time != NULL) {
        *time = clockGet(); /* XCP clock at send time */
    }
    int16_t n = (int16_t)lwip_sendto(socket, buffer, bufferSize, 0,
                                      (struct sockaddr *)&dst, sizeof(dst));
    if (n < 0) {
        int32_t err = errno;
        if (socketIsClosed(err)) {
            return 0;
        }
        DBG_PRINTF_ERROR("socketSendTo: lwip_sendto failed (errno=%d,%s)\n",
                         err, socketGetErrorString(err));
        return -1;
    }
    return n;
}

/* Set receive timeout.  timeoutMs == 0 restores infinite blocking. */
bool socketSetTimeout(SOCKET_HANDLE socket, uint32_t timeoutMs) {
    assert(socket != INVALID_SOCKET_HANDLE);
    struct timeval tv;
    tv.tv_sec  = (long)(timeoutMs / 1000U);
    tv.tv_usec = (long)(timeoutMs % 1000U) * 1000L;
    if (lwip_setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        DBG_PRINTF_WARNING("socketSetTimeout: SO_RCVTIMEO failed (errno=%d,%s)\n",
                           errno, socketGetErrorString(errno));
        return false;
    }
    DBG_PRINTF5("socketSetTimeout: set to %u ms\n", timeoutMs);
    return true;
}

/* socketGetMAC: not available on lwIP / bare-metal FreeRTOS.
 * Returns false; callers must check OPTION_ENABLE_GET_LOCAL_ADDR before calling. */
bool socketGetMAC(char *ifname, uint8_t *mac) {
    (void)ifname;
    (void)mac;
    DBG_PRINT_ERROR("socketGetMAC: not implemented on FreeRTOS/lwIP\n");
    return false;
}

#ifdef OPTION_ENABLE_GET_LOCAL_ADDR
/* socketGetLocalAddr stub: returns a zeroed address.
 * On the UltraZohm the IP is assigned by DHCP/static config; callers should
 * use the known board address rather than probing interfaces. */
bool socketGetLocalAddr(uint8_t *mac, uint8_t *addr) {
    if (mac  != NULL) memset(mac,  0, 6);
    if (addr != NULL) memset(addr, 0, 4);
    DBG_PRINT_ERROR("socketGetLocalAddr: not implemented on FreeRTOS/lwIP – returning zeroes\n");
    return false;
}
#endif /* OPTION_ENABLE_GET_LOCAL_ADDR */

#else /* !OPTION_FREERTOS_LWIP — no networking backend configured */

bool socketOpen(SOCKET_HANDLE *socketp, uint16_t flags) {
    (void)socketp; (void)flags;
    DBG_PRINT_ERROR("socketOpen: no FreeRTOS networking backend (define OPTION_FREERTOS_LWIP)\n");
    return false;
}
bool socketBind(SOCKET_HANDLE socket, const uint8_t *addr, uint16_t port) {
    (void)socket; (void)addr; (void)port; return false;
}
bool socketShutdown(SOCKET_HANDLE socket) { (void)socket; return true; }
bool socketClose(SOCKET_HANDLE *socketp) {
    if (socketp) *socketp = INVALID_SOCKET_HANDLE;
    return true;
}
int16_t socketRecvFrom(SOCKET_HANDLE socket, uint8_t *buffer, uint16_t bufferSize,
                       uint8_t *srcAddr, uint16_t *srcPort, uint64_t *time) {
    (void)socket; (void)buffer; (void)bufferSize;
    (void)srcAddr; (void)srcPort; (void)time;
    return -1;
}
int16_t socketSendTo(SOCKET_HANDLE socket, const uint8_t *buffer, uint16_t bufferSize,
                     const uint8_t *addr, uint16_t port, uint64_t *time) {
    (void)socket; (void)buffer; (void)bufferSize;
    (void)addr; (void)port; (void)time;
    return -1;
}
bool socketSetTimeout(SOCKET_HANDLE socket, uint32_t timeoutMs) {
    (void)socket; (void)timeoutMs; return true;
}
bool socketGetMAC(char *ifname, uint8_t *mac) {
    (void)ifname; (void)mac; return false;
}
#ifdef OPTION_ENABLE_GET_LOCAL_ADDR
bool socketGetLocalAddr(uint8_t *mac, uint8_t *addr) {
    if (mac)  memset(mac,  0, 6);
    if (addr) memset(addr, 0, 4);
    return false;
}
#endif

#endif /* OPTION_FREERTOS_LWIP */

#endif /* OPTION_ENABLE_TCP || OPTION_ENABLE_UDP */


/**************************************************************************/
/* Clock                                                                   */
/**************************************************************************/

/* Clock resolution: xTaskGetTickCount() granularity = 1/configTICK_RATE_HZ.
 * Convert tick count to the configured unit (ns or us). */

static volatile uint64_t gClockLast_ = 0;

static inline uint64_t tickToClockUnit_(TickType_t ticks) {
#ifdef OPTION_CLOCK_TICKS_1NS
    return (uint64_t)ticks * (1000000000ULL / configTICK_RATE_HZ);
#else /* OPTION_CLOCK_TICKS_1US */
    return (uint64_t)ticks * (1000000ULL / configTICK_RATE_HZ);
#endif
}

bool clockInit(void) {
    DBG_PRINT3("clockInit: FreeRTOS tick clock\n");
#ifdef OPTION_CLOCK_TICKS_1NS
    DBG_PRINTF3("  tick resolution = %u ns\n",
                (unsigned)(1000000000UL / configTICK_RATE_HZ));
#else
    DBG_PRINTF3("  tick resolution = %u us\n",
                (unsigned)(1000000UL / configTICK_RATE_HZ));
#endif
    gClockLast_ = 0;
    return true;
}

uint64_t clockGet(void) {
    uint64_t t = tickToClockUnit_(xTaskGetTickCount());
    gClockLast_ = t;
    return t;
}

uint64_t clockGetLast(void) {
    return gClockLast_;
}

char *clockGetString(char *s, uint32_t l, uint64_t c) {
    SNPRINTF(s, l, "%gs", (double)c / CLOCK_TICKS_PER_S);
    return s;
}

/* Platform-independent time-offset formatter (declared in platform.h) */
char *clockGetTimeString(char *str, uint32_t l, int64_t t) {
#ifdef OPTION_CLOCK_EPOCH_ARB
    SNPRINTF(str, l, "%gs", (double)t / CLOCK_TICKS_PER_S);
#else
    char sign = '+';
    if (t < 0) { sign = '-'; t = -t; }
    uint64_t s  = (uint64_t)t / CLOCK_TICKS_PER_S;
    uint64_t ns = (uint64_t)t % CLOCK_TICKS_PER_S;
    SNPRINTF(str, l, "%c%" PRIu64 "d%" PRIu64 "h%" PRIu64 "m%" PRIu64 "s+%" PRIu64 "ns",
             sign,
             s / (3600 * 24),
             (s % (3600 * 24)) / 3600,
             ((s % (3600 * 24)) % 3600) / 60,
             ((s % (3600 * 24)) % 3600) % 60,
             ns);
#endif
    return str;
}

uint64_t clockGetMonotonicNs(void) {
    return (uint64_t)xTaskGetTickCount() * (1000000000ULL / configTICK_RATE_HZ);
}

uint64_t clockGetMonotonicUs(void) {
    return (uint64_t)xTaskGetTickCount() * (1000000ULL / configTICK_RATE_HZ);
}

/* On bare-metal FreeRTOS there is no separate real-time clock;
 * map realtime to the monotonic tick clock. */
uint64_t clockGetRealtimeNs(void)  { return clockGetMonotonicNs(); }
uint64_t clockGetRealtimeUs(void)  { return clockGetMonotonicUs(); }

uint64_t clockGetMonotonicNsLast(void) { return gClockLast_; }
uint64_t clockGetMonotonicUsLast(void) { return gClockLast_; }
uint64_t clockGetRealtimeNsLast(void)  { return gClockLast_; }
uint64_t clockGetRealtimeUsLast(void)  { return gClockLast_; }
