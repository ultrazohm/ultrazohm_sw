/*----------------------------------------------------------------------------
| xcptl_ocm.c
|   XCP transport layer over the OCM FIFO for the bare-metal R5 (Option Z).
|   Replaces xcpethtl.c (sockets) on the R5: the A53 gateway ferries XCP-on-
|   Ethernet TL frames between UDP and the OCM FIFO; here we move them between
|   the OCM FIFO and the XCPlite protocol engine.
|
|   Engine-facing symbols required by xcplite.c:
|     XcpTlGetCtr / XcpTlSendCrm / XcpTlWaitForTransmitQueueEmpty
|   Plus the R5 driving API: xcp_r5_init / xcp_r5_rx_pump / xcp_r5_tx_pump.
|
|   TL wire frame = [dlc:u16 LE][ctr:u16 LE][packet ...]  (XCPTL header = 4B).
|
|   Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "xcplite.h"
#include "xcptl.h"
#include "queue.h"
#include "platform.h"
#include "xcptl_cfg.h"
#include <string.h>
#include <stdint.h>

#define XCP_R5_QUEUE_SIZE_BYTES (8u * 1024u)

/* Abstract OCM FIFO — implemented by the ported hedrive RPU_APU_exchange in the
 * Z2 integration step (shared/RPU_APU_exchange_impl.c). One TL frame per call. */
extern void ocm_xcp_init(void);
extern bool ocm_xcp_read_cmd(uint8_t *out_len, const uint8_t **out_frame); /* A53->R5 */
extern bool ocm_xcp_write_rsp(const uint8_t *frame, uint16_t len);         /* R5->A53 */

static MUTEX        gCtrMutex;
static uint16_t     gCtr   = 0u;
static tQueueHandle gQueue = NULL;

/* --- engine-facing transport API ----------------------------------------- */

uint16_t XcpTlGetCtr(void) { return gCtr++; }

void XcpTlSendCrm(const uint8_t *data, uint8_t size) {
    uint8_t buf[XCPTL_TRANSPORT_LAYER_HEADER_SIZE + XCPTL_MAX_CTO_SIZE];
    mutexLock(&gCtrMutex);
    buf[0] = (uint8_t)(size & 0xFF);
    buf[1] = (uint8_t)(size >> 8);
    buf[2] = (uint8_t)(gCtr & 0xFF);
    buf[3] = (uint8_t)(gCtr >> 8);
    gCtr++;
    memcpy(&buf[XCPTL_TRANSPORT_LAYER_HEADER_SIZE], data, size);
    (void)ocm_xcp_write_rsp(buf, (uint16_t)(size + XCPTL_TRANSPORT_LAYER_HEADER_SIZE));
    mutexUnlock(&gCtrMutex);
}

/* Drain the DAQ/CRM transmit queue into the OCM FIFO. Called from the R5 main
 * loop and from XcpTlWaitForTransmitQueueEmpty. queuePop() stamps the TL ctr
 * via XcpTlGetCtr() (see queue.h). */
void xcp_r5_tx_pump(void) {
    for (;;) {
        uint32_t lost = 0u;
        tQueueBuffer b = queuePop(gQueue, true /*accumulate*/, false /*priority*/, &lost);
        if (b.size == 0u) {
            break;
        }
        (void)ocm_xcp_write_rsp(b.buffer, b.size);
        queueRelease(gQueue, &b);
    }
}

bool XcpTlWaitForTransmitQueueEmpty(uint16_t timeout_ms) {
    (void)timeout_ms;
    xcp_r5_tx_pump();
    return true;
}

/* Pull pending XCP commands from the OCM FIFO and hand them to the engine. */
void xcp_r5_rx_pump(void) {
    const uint8_t *frame;
    uint8_t len;
    while (ocm_xcp_read_cmd(&len, &frame)) {
        uint16_t dlc = (uint16_t)(frame[0] | ((uint16_t)frame[1] << 8));
        XcpCommand((const uint32_t *)(const void *)(frame + XCPTL_TRANSPORT_LAYER_HEADER_SIZE),
                   (uint8_t)dlc);
    }
}

/* One-time init: queue + engine + OCM FIFO. Base addr 0 => XCP address ==
 * pointer => arbitrary R5 addressing (the whole point of Option Z). */
int xcp_r5_init(const char *name, const char *epk) {
    mutexInit(&gCtrMutex, false, 0u);
    gCtr = 0u;
    gQueue = queueInit((size_t)XCP_R5_QUEUE_SIZE_BYTES);
    if (gQueue == NULL) {
        return -1;
    }
    ocm_xcp_init();
    ApplXcpSetBaseAddr((const uint8_t *)0);
    if (!XcpInit(name, epk, XCP_MODE_LOCAL)) {
        return -2;
    }
    XcpStart(gQueue, false);
    return 0;
}
