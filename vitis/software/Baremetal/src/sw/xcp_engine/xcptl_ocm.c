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
|     xcp_r5_init()       once at startup (after uz_SystemTime is up)
|     xcp_r5_event()      from ISR_Control: sample DAQ (thin; just XcpEvent)
|     xcp_r5_background() from the MAIN LOOP: paced command + DAQ sweep;
|                         caller fires the IPI when it returns 1
|
|   Context split (required for high control rates, e.g. a future 100 kHz
|   ISR): only the DAQ sampling copy (XcpEvent -> queue32) runs in the ISR;
|   everything else — command processing, queue drain, OCM writes, cache
|   maintenance — runs from the main loop at XCP_R5_SWEEP_PERIOD_US pace.
|   queue32 is the ISR/main-loop boundary (internally locked with SHORT
|   critical sections only; the bulk memcpys happen outside its lock, so the
|   main loop never blocks the control ISR for more than pointer arithmetic).
|
|   Delivery guarantees (ported from the hedrive hardware campaign, see
|   ocm_xcp_fifo.c): command responses go through the acknowledged CTO
|   mailbox (never lost to a cycle rewrite); commands are executed once per
|   A53-published generation (never lost to a missed cycle, never executed
|   twice). DAQ frames stream through the per-cycle chain; a missed cycle is
|   a counted measurement gap.
|
|   TL wire frame = [dlc:u16 LE][ctr:u16 LE][packet ...]  (XCPTL header = 4B),
|   exactly the XCP-on-UDP datagram payload the A53 gateway forwards. The
|   transport CTR stamped here is provisional: the A53 — the actual UDP
|   transport endpoint — re-stamps it at transmission time in transmission
|   order (frames are reordered by the mailbox path and dropped on overflow;
|   a producer-side counter would show gaps/reordering to the master).
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

/* DAQ queue between the ISR (producer, XcpEvent) and the main-loop sweep
 * (consumer). Must hold one sweep period of DAQ production:
 * event_rate x payload/cycle x SWEEP_PERIOD. 32 KB covers e.g. 100 kHz x
 * 2 kB/ms at the 100 us sweep with 15x headroom at today's 10 kHz rates. */
#define XCP_R5_QUEUE_SIZE_BYTES (32u * 1024u)

/* Main-loop sweep pacing: one OCM exchange (commands + DAQ drain + IPI) per
 * period. 100 us = the exchange cadence validated by the 1 h soak; the IPI
 * rate to the A53 stays what it was when the sweep lived in the 10 kHz ISR. */
#define XCP_R5_SWEEP_PERIOD_US 100u

extern uint64_t uz_SystemTime_GetUptimeInUs(void);

/* Framed CRM messages must fit the OCM mailbox slot. */
#if (XCPTL_MAX_CTO_SIZE + XCPTL_TRANSPORT_LAYER_HEADER_SIZE) > 256
#error "XCPTL_MAX_CTO_SIZE + header exceeds OCM_XCP_CTO_SLOT_LEN"
#endif

/* Pending CTO responses waiting for the OCM mailbox (one in-flight response
 * at a time, acknowledged by the A53). Request/response is serialized by the
 * master, so depth > 1 is only used by bursts XCPlite produces itself. */
#define XCP_R5_CTO_PENDING_DEPTH 4u

/* DAQ event handle (created in xcp_r5_init, triggered in xcp_r5_event). */
uint16_t xcp_r5_daq_event = 0u;

/* Diagnostics (inspect via JTAG or XCP SHORT_UPLOAD):
 *   xcp_r5_init_result      0 = ok, negative = init failed (engine disabled)
 *   xcp_r5_cycle_count      increments each control cycle -> liveness probe
 *   xcp_r5_tx_oversize_drop popped segment > 255 B (must stay 0; cfg bounds it)
 *   xcp_r5_cto_sent         CTO responses handed to the OCM mailbox
 *   xcp_r5_cto_dropped      pending-CTO FIFO overflow -> response lost (bug!)
 *   xcp_r5_in_generations   command batches executed (generation handshake)
 *   xcp_r5_queue_lost       queue32 overflow between sweeps -> DAQ frames
 *                           lost at the source (raise QUEUE_SIZE or sweep
 *                           more often if this climbs)
 *   xcp_r5_sweep_count      main-loop sweeps executed -> liveness probe
 *   xcp_r5_sweep_gap_max_us worst observed inter-sweep gap. THE main-loop
 *                           health number: ~SWEEP_PERIOD = loop plenty fast;
 *                           >> SWEEP_PERIOD = something in the main loop
 *                           blocks (throughput caps at ~6.8 KB per gap;
 *                           the 32 KB queue rides out gaps <= 0.8 ms at the
 *                           320 Mbit/s worst case). Reset via debugger. */
volatile int32_t  xcp_r5_init_result = 0x7FFFFFFF; /* "init not run yet" */
volatile uint32_t xcp_r5_cycle_count = 0u;
volatile uint32_t xcp_r5_tx_oversize_drop = 0u;
volatile uint32_t xcp_r5_cto_sent = 0u;
volatile uint32_t xcp_r5_cto_dropped = 0u;
volatile uint32_t xcp_r5_in_generations = 0u;
volatile uint32_t xcp_r5_queue_lost = 0u;
volatile uint32_t xcp_r5_sweep_count = 0u;
volatile uint32_t xcp_r5_sweep_gap_max_us = 0u;

/* The transport-layer counter is stamped by queuePop()/XcpTlSendCrm(), both
 * of which run only in the main-loop sweep context (XcpCommand executes in
 * the sweep) — no lock needed. The A53 re-stamps the wire CTR anyway. */
static uint16_t     gCtr   = 0u;
static tQueueHandle gQueue = NULL;

/* CTO responses parked here until the OCM mailbox is free (previous response
 * acknowledged by the A53). Only touched from the xcp_r5_poll() context. */
static struct {
    uint8_t len;
    uint8_t data[OCM_XCP_CTO_SLOT_LEN];
} gCtoPending[XCP_R5_CTO_PENDING_DEPTH];
static uint8_t gCtoPendingHead = 0u;  /* next entry to hand to the mailbox */
static uint8_t gCtoPendingCount = 0u;

/* Last XCP_IN command-batch generation processed. Each generation is executed
 * exactly once, no matter how many IPI cycles the A53 keeps offering it
 * (rewrite-until-acked; see ocm_xcp_fifo.c). */
static uint32_t gInGenDone = 0u;

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

/* Command response: frame it and park it for the guaranteed-delivery CTO
 * mailbox (a response lost to a cycle rewrite = master timeout = dead
 * session; hedrive T8). Called from within XcpCommand(), i.e. inside the
 * main-loop sweep — single context, no lock. */
void XcpTlSendCrm(const uint8_t *data, uint8_t size) {
    if (gCtoPendingCount < XCP_R5_CTO_PENDING_DEPTH) {
        uint8_t slot = (uint8_t)((gCtoPendingHead + gCtoPendingCount) % XCP_R5_CTO_PENDING_DEPTH);
        uint8_t *buf = gCtoPending[slot].data;
        buf[0] = (uint8_t)(size & 0xFF);
        buf[1] = (uint8_t)(size >> 8);
        buf[2] = (uint8_t)(gCtr & 0xFF); /* provisional; A53 re-stamps on TX */
        buf[3] = (uint8_t)(gCtr >> 8);
        gCtr++;
        memcpy(&buf[XCPTL_TRANSPORT_LAYER_HEADER_SIZE], data, size);
        gCtoPending[slot].len = (uint8_t)(size + XCPTL_TRANSPORT_LAYER_HEADER_SIZE);
        gCtoPendingCount++;
    } else {
        xcp_r5_cto_dropped++; /* should never happen: request/response serialized */
    }
}

/* Hand the oldest pending CTO to the OCM mailbox once the A53 has
 * acknowledged the previous one. Must run between prepare_write() and
 * cache_flush_after_write(); relies on cache_invalidate_before_read() having
 * refreshed the ack word this cycle. */
static void xcp_r5_pump_cto(void) {
    if (gCtoPendingCount == 0u) {
        return;
    }
    if (!ocm_xcp_cto_mailbox_free()) {
        return; /* previous response not consumed yet; retry next cycle */
    }
    if (ocm_xcp_cto_write(gCtoPending[gCtoPendingHead].len, gCtoPending[gCtoPendingHead].data)) {
        xcp_r5_cto_sent++;
    }
    gCtoPendingHead = (uint8_t)((gCtoPendingHead + 1u) % XCP_R5_CTO_PENDING_DEPTH);
    gCtoPendingCount--;
}

/* Drain the DAQ transmit queue into the XCP_OUT chain. Mirrors
 * XcpTlHandleTransmitQueue (queue32 path). A full chain drops the segment
 * (counted in ocm_xcp_w_dropped) — a DAQ gap, not a session risk.
 * NO lock around the OCM memcpy/cache-flush: queuePop/queueRelease take
 * queue32's internal (short) critical sections; holding an IRQ-disabling
 * lock across the 252-byte copy would jitter the control ISR. */
void xcp_r5_tx_pump(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    for (;;) {
        uint32_t lost = 0u;
        /* flush=true: hand out the current partially-filled segment too. With
         * flush=false, queue32's queuePop never returns a lone open segment,
         * so DAQ data would sit in the queue until a full segment accumulates. */
        tQueueBuffer qb = queuePop(gQueue, true /*accumulate*/, true /*flush*/, &lost);
        if (lost > 0u) {
            xcp_r5_queue_lost += lost; /* ISR produced faster than the sweep drained */
        }
        uint16_t l = qb.size;
        if (l == 0u) {
            break; /* queue empty */
        }
        if (l <= 0xFFu) {
            (void)ocm_xcp_fifo_write((uint8_t)l, qb.buffer);
        } else {
            /* Impossible with XCPTL_MAX_SEGMENT_SIZE 252, but never truncate. */
            xcp_r5_tx_oversize_drop++;
        }
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
 * OCM write happens in xcp_r5_poll(). */
void xcp_r5_event(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    xcp_r5_cycle_count++;
    XcpEvent(xcp_r5_daq_event);
}

/* One full exchange sweep (MAIN-LOOP context; use xcp_r5_background() for
 * pacing): open the XCP_OUT seqlock, execute a NEW command-batch generation
 * from XCP_IN -> XcpCommand (responses go to the CTO pending FIFO),
 * acknowledge the generation, pump the mailbox, drain the DAQ queue ->
 * XCP_OUT chain, then publish the cycle (flush + even seqlock). The caller
 * signals the A53 (IPI) after this returns. */
void xcp_r5_poll(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    ocm_xcp_fifo_prepare_write(); /* seqlock -> odd; chain rewound */

    ocm_xcp_fifo_cache_invalidate_before_read();

    /* Commands: process a batch only when its generation is new. The A53
     * publishes the generation after the chain bytes, so a new value here
     * implies a complete chain; an unchanged value means either nothing new
     * or a batch already executed (never run a generation twice). The A53
     * re-offers identical batch bytes every IPI until acknowledged, so a
     * command can no longer be lost to IPI/cycle overlap (the hedrive T8
     * pcap-proven session killer). */
    uint32_t in_gen = ocm_xcp_in_gen_read();
    if (in_gen != gInGenDone) {
        ocm_xcp_fifo_prepare_read();
        uint8_t len;
        uint8_t *data;
        while (ocm_xcp_fifo_read(&len, &data)) {
            /* One record = one UDP datagram, which may carry SEVERAL
             * concatenated TL frames ([dlc][ctr][packet])+ (e.g. CANape
             * block-mode command bursts). */
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
        gInGenDone = in_gen;
        xcp_r5_in_generations++;
    }
    ocm_xcp_in_consumed_write(gInGenDone);

    /* After command processing: a response generated this cycle can ride the
     * mailbox in this same cycle (if it is free). */
    xcp_r5_pump_cto();

    xcp_r5_tx_pump();

    ocm_xcp_fifo_cache_flush_after_write(); /* chain, then header + even seq */
}

/* Paced sweep driver. Call from the MAIN LOOP every iteration; it runs one
 * xcp_r5_poll() sweep per XCP_R5_SWEEP_PERIOD_US and returns 1 when it did —
 * the caller must then trigger the IPI to the A53 gateway. Keeping the sweep
 * out of ISR_Control removes the whole XCP exchange cost (~10 us base +
 * ~10 us/KB, measured 2026-07-11) from the control ISR; only the XcpEvent
 * sampling copy remains there. */
int xcp_r5_background(void) {
    static uint32_t last_sweep_us = 0u;
    static int first_sweep = 1;
    if (gQueue == NULL) {
        return 0; /* init failed or not run: engine disabled */
    }
    uint32_t now_us = (uint32_t)uz_SystemTime_GetUptimeInUs();
    uint32_t gap_us = (uint32_t)(now_us - last_sweep_us);
    if (gap_us < XCP_R5_SWEEP_PERIOD_US) {
        return 0;
    }
    if (first_sweep) {
        first_sweep = 0; /* boot-to-first-sweep gap is not a loop-health signal */
    } else if (gap_us > xcp_r5_sweep_gap_max_us) {
        xcp_r5_sweep_gap_max_us = gap_us;
    }
    last_sweep_us = now_us;
    xcp_r5_poll();
    xcp_r5_sweep_count++;
    return 1;
}

/* One-time init. Base addr 0 => XCP address == pointer => arbitrary R5
 * addressing (the point of Option Z). Returns 0 on success. */
int xcp_r5_init(const char *name, const char *epk) {
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
