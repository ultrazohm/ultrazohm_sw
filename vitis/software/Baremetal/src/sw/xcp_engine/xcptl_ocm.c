/*----------------------------------------------------------------------------
| xcptl_ocm.c
|   XCP transport layer over the OCM FIFO for the bare-metal R5 (Option Z).
|   Replaces xcpethtl.c (sockets): the A53 gateway ferries XCP-on-Ethernet TL
|   frames between UDP and the OCM FIFO; here we move them between the OCM FIFO
|   and the XCPlite protocol engine.
|
|   Engine-facing symbols required by xcplite.c:
|     XcpTlGetCtr / XcpTlSendCrm / XcpTlWaitForTransmitQueueEmpty
|   R5 driving API (call from the Baremetal app):
|     xcp_r5_init()   once at startup (after uz_SystemTime is up)
|     xcp_r5_event()  from ISR_Control: sample DAQ (thin; just XcpEvent)
|     xcp_r5_poll()   from the main loop / per control cycle: command + DAQ sweep
|
|   TL wire frame = [dlc:u16 LE][ctr:u16 LE][packet ...]  (XCPTL header = 4B),
|   exactly the XCP-on-UDP datagram payload the A53 gateway forwards verbatim.
|
|   Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "xcplite.h"
#include "xcptl.h"
#include "queue.h"
#include "platform.h"
#include "xcptl_cfg.h"
#include "ocm_xcp_fifo.h"
#include <string.h>
#include <stdint.h>

#define XCP_R5_QUEUE_SIZE_BYTES (8u * 1024u)

/* DAQ event handle (created in xcp_r5_init, triggered in xcp_r5_event). */
uint16_t xcp_r5_daq_event = 0u;

/* Diagnostics (inspect via JTAG or XCP SHORT_UPLOAD):
 *   xcp_r5_init_result      0 = ok, negative = init failed (engine disabled)
 *   xcp_r5_cycle_count      increments each control cycle -> liveness probe
 *   xcp_r5_tx_oversize_drop popped segment > 255 B (must stay 0; cfg bounds it) */
volatile int32_t  xcp_r5_init_result = 0x7FFFFFFF; /* "init not run yet" */
volatile uint32_t xcp_r5_cycle_count = 0u;
volatile uint32_t xcp_r5_tx_oversize_drop = 0u;

static MUTEX        gCtrMutex;
static uint16_t     gCtr   = 0u;
static tQueueHandle gQueue = NULL;

/* Memory access gate for SHORT_UPLOAD/UPLOAD/DOWNLOAD/DAQ entries: without it
 * the engine memcpy()s ANY 32-bit address the master sends -> a stray address
 * (e.g. an A53 symbol) raises an R5 data abort inside ISR_Control and kills
 * the motor control. Allow only memory the R5 actually maps (cf. lscript.ld). */
static uint8_t xcp_r5_check_memory(uint8_t ext, uint32_t addr, uint8_t size) {
    (void)ext; /* only ABS (0x00) reaches the engine's direct memory path */
    const uint64_t a = addr;
    const uint64_t end = a + size; /* u64: no wrap at the top of OCM */
    if (end <= 0x00010000u) return CRC_CMD_OK;                        /* ATCM  */
    if (a >= 0x00020000u && end <= 0x00030000u) return CRC_CMD_OK;    /* BTCM  */
    if (a >= 0x40000000u && end <= 0x47FF0000u) return CRC_CMD_OK;    /* DDR   */
    if (a >= 0xFFFC0000u && end <= 0x100000000ull) return CRC_CMD_OK; /* OCM   */
    return CRC_ACCESS_DENIED;
}

/* --- engine-facing transport API ----------------------------------------- */

uint16_t XcpTlGetCtr(void) { return gCtr++; }

/* Command response: frame it and append to XCP_OUT. Called from within
 * XcpCommand(), i.e. inside the xcp_r5_poll() sweep after prepare_write(). */
void XcpTlSendCrm(const uint8_t *data, uint8_t size) {
    uint8_t buf[XCPTL_TRANSPORT_LAYER_HEADER_SIZE + XCPTL_MAX_CTO_SIZE];
    mutexLock(&gCtrMutex);
    buf[0] = (uint8_t)(size & 0xFF);
    buf[1] = (uint8_t)(size >> 8);
    buf[2] = (uint8_t)(gCtr & 0xFF);
    buf[3] = (uint8_t)(gCtr >> 8);
    gCtr++;
    memcpy(&buf[XCPTL_TRANSPORT_LAYER_HEADER_SIZE], data, size);
    (void)ocm_xcp_fifo_write((uint8_t)(size + XCPTL_TRANSPORT_LAYER_HEADER_SIZE), buf);
    mutexUnlock(&gCtrMutex);
}

/* Drain the DAQ/CRM transmit queue into XCP_OUT. Mirrors
 * XcpTlHandleTransmitQueue (queue32 path): the ctr mutex keeps the TL counter
 * consistent across response and DAQ packets; queuePop() stamps the ctr. */
void xcp_r5_tx_pump(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    for (;;) {
        mutexLock(&gCtrMutex);
        uint32_t lost = 0u;
        /* flush=true: hand out the current partially-filled segment too. With
         * flush=false, queue32's queuePop never returns a lone open segment,
         * so DAQ data would sit in the queue until a full segment accumulates. */
        tQueueBuffer qb = queuePop(gQueue, true /*accumulate*/, true /*flush*/, &lost);
        if (lost > 0u) {
            gCtr += (uint16_t)lost; /* account for dropped packets in the counter */
        }
        uint16_t l = qb.size;
        if (l == 0u) {
            mutexUnlock(&gCtrMutex);
            break; /* queue empty */
        }
        if (l <= 0xFFu) {
            (void)ocm_xcp_fifo_write((uint8_t)l, qb.buffer);
        } else {
            /* Impossible with XCPTL_MAX_SEGMENT_SIZE 252, but never truncate. */
            xcp_r5_tx_oversize_drop++;
        }
        mutexUnlock(&gCtrMutex);
        queueRelease(gQueue, &qb);
    }
}

bool XcpTlWaitForTransmitQueueEmpty(uint16_t timeout_ms) {
    (void)timeout_ms;
    xcp_r5_tx_pump();
    return true;
}

/* --- R5 driving API ------------------------------------------------------- */

/* Sample DAQ. Call from ISR_Control. Thin: XcpEvent pushes to the queue; the
 * OCM write happens in xcp_r5_poll() on the main loop, off the ISR. */
void xcp_r5_event(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    xcp_r5_cycle_count++;
    XcpEvent(xcp_r5_daq_event);
}

/* One full exchange sweep. Call once per control cycle on the main loop (not in
 * the ISR): prepare XCP_OUT, read commands from XCP_IN -> XcpCommand (responses
 * append to XCP_OUT), drain the DAQ queue -> XCP_OUT, flush. The caller signals
 * the A53 (IPI) after this returns. */
void xcp_r5_poll(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    ocm_xcp_fifo_prepare_write();

    ocm_xcp_fifo_cache_invalidate_before_read();
    ocm_xcp_fifo_prepare_read();
    uint8_t len;
    uint8_t *data;
    while (ocm_xcp_fifo_read(&len, &data)) {
        /* One record = one UDP datagram, which may carry SEVERAL concatenated
         * TL frames ([dlc][ctr][packet])+ (e.g. CANape block-mode commands). */
        uint16_t off = 0u;
        while ((uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE) <= (uint16_t)len) {
            uint16_t dlc = (uint16_t)(data[off] | ((uint16_t)data[off + 1] << 8));
            if (dlc == 0u ||
                (uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc) > (uint16_t)len) {
                break; /* padding or malformed frame: stop parsing this record */
            }
            XcpCommand((const uint32_t *)(const void *)(data + off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE),
                       (uint8_t)dlc);
            off = (uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc);
        }
    }
    /* Zero the chain head we just consumed: if the A53's IPI handling slips
     * past one control cycle, we must not re-execute the same commands. */
    ocm_xcp_fifo_consume_read();

    xcp_r5_tx_pump();

    ocm_xcp_fifo_cache_flush_after_write();
}

/* One-time init. Base addr 0 => XCP address == pointer => arbitrary R5
 * addressing (the point of Option Z). Returns 0 on success. */
int xcp_r5_init(const char *name, const char *epk) {
    mutexInit(&gCtrMutex, false, 0u);
    gCtr = 0u;
    gQueue = queueInit((size_t)XCP_R5_QUEUE_SIZE_BYTES);
    if (gQueue == NULL) {
        xcp_r5_init_result = -1;
        return -1;
    }
    ocm_xcp_fifo_init();
    ApplXcpSetBaseAddr((const uint8_t *)0);
    ApplXcpRegisterCheckCallback(xcp_r5_check_memory);
    if (!XcpInit(name, epk, XCP_MODE_LOCAL)) {
        gQueue = NULL; /* keep the ISR hooks inert */
        xcp_r5_init_result = -2;
        return -2;
    }
    XcpStart(gQueue, false);
    xcp_r5_daq_event = (uint16_t)XcpCreateEvent("DAQ_R5", 1000000u, 0u);
    if (xcp_r5_daq_event == 0xFFFFu) { /* XCP_UNDEFINED_EVENT_ID */
        gQueue = NULL; /* keep the ISR hooks inert */
        xcp_r5_init_result = -3;
        return -3;
    }
    xcp_r5_init_result = 0;
    return 0;
}
