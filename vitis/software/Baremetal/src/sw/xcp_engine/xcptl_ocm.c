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
|   DAQ rasters offered to the master (hedrive parity, see kXcpR5Slice below):
|   DAQ_R5 at the control-ISR rate plus the derived time slices daq_1ms,
|   daq_10ms, daq_100ms and daq_1s (hedrive names, as configured in the CANape
|   project). Event channel numbers are the creation order 0..4 and are
|   hardcoded in the A2L (CANape/UZ_XCP/uz.A2L) — keep both sides in sync.
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
|   twice). DAQ frames stream through the chain, which stays in place until
|   the A53 acknowledges it (xcp_r5_out_held): a late, torn or skipped IPI
|   read costs one sweep of latency, not the data. A sweep whose chain fills
|   up holds the rest of the backlog in the queue (xcp_r5_tx_held). Backlog
|   becomes latency, not loss, until the queue itself overflows
|   (xcp_r5_queue_lost) - the one place ECU-side DAQ loss is counted.
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
#include "xcp_cfg.h" /* XCP_ADDR_EXT_ABS / XCP_ADDR_EXT_PTR */
#include "ocm_xcp_fifo.h"
#include "xcp_r5.h" /* XCP_R5_READ_ONLY */
#include "../../include/isr.h" /* UZ_PWM_FREQUENCY, Interrupt_ISR_freq_factor */
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
 * at a time, acknowledged by the A53, i.e. one response per sweep). A command
 * batch (generation) may carry more frames than this - CANape block mode,
 * a pipelining master - so xcp_r5_poll stops executing when the FIFO is full
 * and resumes the SAME generation at the next frame in a later sweep; the
 * depth only sets how far it runs ahead of the mailbox. */
#define XCP_R5_CTO_PENDING_DEPTH 4u

/* XCP_OUT consumption handshake: sweeps a non-empty chain is kept in place
 * waiting for the A53 acknowledge before it is overwritten anyway
 * (xcp_r5_out_overwritten). The bound only matters when the gateway is not
 * running at all; 50 sweeps = 5 ms is far beyond any IPI latency seen on
 * hardware (worst case in the 1 h soak: a few hundred us) and beyond what
 * the 32 KB queue bridges at high DAQ rates anyway. */
#define XCP_R5_OUT_HOLD_MAX_SWEEPS 50u

/* Control-ISR rate = the base DAQ raster. Same expression main.c uses for
 * Global_Data.av.isr_samplerate_s, so it follows UZ_PWM_FREQUENCY, the trigger
 * source and the ADC-to-ISR ratio automatically. */
#define XCP_R5_ISR_FREQ_HZ                                                     \
    ((uint32_t)((UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor) /               \
                INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE))

/* Base event period in ns, reported to the master via GET_DAQ_EVENT_INFO
 * (0 = "sporadic or unknown", the sane answer for a misconfigured 0 Hz ISR). */
#define XCP_R5_ISR_PERIOD_NS ((XCP_R5_ISR_FREQ_HZ) > 0u ? (1000000000u / (XCP_R5_ISR_FREQ_HZ)) : 0u)

/* Control cycles per millisecond, the divider base of the named time slices.
 * Clamped to >= 1 so an ISR slower than 1 kHz yields slow-but-sane rasters
 * instead of one that fires every cycle. Note the rasters drift when the ISR
 * rate is not an integer multiple of 1 kHz (e.g. at 12.5 kHz "1 ms" becomes
 * 12 cycles = 0.96 ms); the timestamp CANape sees is always the true one. */
#define XCP_R5_CYCLES_PER_MS (((XCP_R5_ISR_FREQ_HZ) / 1000u) > 0u ? ((XCP_R5_ISR_FREQ_HZ) / 1000u) : 1u)

/* Named DAQ time slices, ported from the hedrive project: slow signals get a
 * slow raster instead of riding the control-ISR rate (which is what actually
 * costs OCM/UDP bandwidth). Derived from the base event by integer division.
 * Event channel = index + 1 (channel 0 is DAQ_R5), enforced in xcp_r5_init. */
#define XCP_R5_SLICE_COUNT 4u

static const struct {
    const char *name;       /* A2L EVENT name */
    uint32_t cycle_time_ns; /* nominal period, for GET_DAQ_EVENT_INFO */
    uint32_t divider;       /* control cycles per raster tick */
} kXcpR5Slice[XCP_R5_SLICE_COUNT] = {
    {"daq_1ms", 1000000u, 1u * XCP_R5_CYCLES_PER_MS},
    {"daq_10ms", 10000000u, 10u * XCP_R5_CYCLES_PER_MS},
    {"daq_100ms", 100000000u, 100u * XCP_R5_CYCLES_PER_MS},
    {"daq_1s", 1000000000u, 1000u * XCP_R5_CYCLES_PER_MS},
};

/* DAQ event handles (created in xcp_r5_init, triggered in xcp_r5_event):
 * xcp_r5_daq_event is the base raster, xcp_r5_daq_slice_event[] the named
 * time slices in kXcpR5Slice order. */
uint16_t xcp_r5_daq_event = 0u;
uint16_t xcp_r5_daq_slice_event[XCP_R5_SLICE_COUNT] = {0u};

/* Slice down-counters, staggered so the slices never all fire in the same
 * control cycle (bounds the DAQ payload one ISR run can produce). */
static uint32_t gSliceCnt[XCP_R5_SLICE_COUNT] = {0u, 1u, 2u, 3u};

/* Diagnostics (inspect via JTAG or XCP SHORT_UPLOAD):
 *   xcp_r5_init_result      0 = ok, negative = init failed (engine disabled)
 *   xcp_r5_cycle_count      increments each control cycle -> liveness probe
 *   xcp_r5_tx_oversize_drop popped segment > 255 B (must stay 0; cfg bounds it)
 *   xcp_r5_cto_sent         CTO responses handed to the OCM mailbox
 *   xcp_r5_cto_dropped      pending-CTO FIFO overflow -> response lost (bug!)
 *   xcp_r5_cmd_oversize_drop TL frame with dlc > XCPTL_MAX_CTO_SIZE refused
 *                           before XcpCommand (the engine asserts cmdLen <=
 *                           MAX_CTO, i.e. abort() on the control core). The
 *                           A53 gateway filters these too, so non-zero here
 *                           means a gateway bug or a hostile master.
 *   xcp_r5_in_generations   command batches executed (generation handshake)
 *   xcp_r5_in_resumed       sweeps that suspended a command batch because the
 *                           pending-CTO FIFO was full (resumed next sweep;
 *                           no response is lost - only latency for bursts)
 *   xcp_r5_queue_lost       queue32 overflow between sweeps -> DAQ frames
 *                           lost at the source (raise QUEUE_SIZE or sweep
 *                           more often if this climbs)
 *   xcp_r5_tx_held          sweeps that filled the XCP_OUT chain with
 *                           backlog left over; the next segment stayed in
 *                           the queue and went out first in the next sweep
 *                           (backlog, not loss). Climbing steadily = DAQ
 *                           production exceeds the ~31 KB per sweep the
 *                           window can carry; expect xcp_r5_queue_lost next.
 *   xcp_r5_out_held         sweeps that kept the previous XCP_OUT chain in
 *                           place because the A53 had not acknowledged it
 *                           yet (late / torn / skipped IPI read). Latency,
 *                           not loss; a few per million sweeps is normal.
 *   xcp_r5_out_overwritten  chains overwritten unacknowledged after
 *                           XCP_R5_OUT_HOLD_MAX_SWEEPS (gateway not running
 *                           or stalled for milliseconds) -> DAQ data lost.
 *                           Must stay 0 while a master is connected.
 *   xcp_r5_write_denied     DOWNLOAD/SHORT_DOWNLOAD refused by the write
 *                           gate (target outside the data sections, or a
 *                           measurement-only build); the master gets
 *                           ERR_WRITE_PROTECTED
 *   xcp_r5_sweep_count      main-loop sweeps executed -> liveness probe
 *   xcp_r5_sweep_gap_max_us worst observed inter-sweep gap. THE main-loop
 *                           health number: ~SWEEP_PERIOD = loop plenty fast;
 *                           >> SWEEP_PERIOD = something in the main loop
 *                           blocks (throughput caps at ~31 KB per gap;
 *                           the 32 KB queue rides out gaps <= 0.8 ms at the
 *                           320 Mbit/s worst case). Reset via debugger. */
volatile int32_t  xcp_r5_init_result = 0x7FFFFFFF; /* "init not run yet" */
volatile uint32_t xcp_r5_cycle_count = 0u;
volatile uint32_t xcp_r5_tx_oversize_drop = 0u;
volatile uint32_t xcp_r5_cto_sent = 0u;
volatile uint32_t xcp_r5_cto_dropped = 0u;
volatile uint32_t xcp_r5_cmd_oversize_drop = 0u;
volatile uint32_t xcp_r5_in_generations = 0u;
volatile uint32_t xcp_r5_in_resumed = 0u;
volatile uint32_t xcp_r5_queue_lost = 0u;
volatile uint32_t xcp_r5_tx_held = 0u;
volatile uint32_t xcp_r5_out_held = 0u;
volatile uint32_t xcp_r5_out_overwritten = 0u;
volatile uint32_t xcp_r5_write_denied = 0u;
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

/* Resume cursor for a generation that could not be finished in one sweep
 * (pending-CTO FIFO full): generation, record index and byte offset of the
 * next frame to execute. Valid because the A53 re-offers identical bytes
 * until the generation is acknowledged. */
static uint32_t gInCurGen = 0u;
static uint16_t gInCurRec = 0u;
static uint16_t gInCurOff = 0u;

/* XCP_OUT consumption handshake state (sweep context only): the chain
 * published by the last non-keep sweep carried data and is not acknowledged
 * yet / number of sweeps it has been kept in place so far. */
static int      gOutPending = 0;
static uint32_t gOutHoldSweeps = 0u;

/* Memory access gate for SHORT_UPLOAD/UPLOAD/DOWNLOAD/BUILD_CHECKSUM/DAQ
 * entries: without it the engine memcpy()s ANY 32-bit address the master
 * sends -> a stray address (e.g. an A53 symbol) raises an R5 data abort inside
 * ISR_Control and kills the motor control. Allow only memory the R5 actually
 * maps (cf. lscript.ld). Called at SET_MTA (size 0), at START_STOP_SYNCH for
 * every DAQ entry, and - XCP_ENABLE_MTA_RANGE_CHECK, xcplib_r5_cfg.h - on
 * every XcpReadMta/XcpWriteMta access with its real size, so the MTA
 * auto-increment cannot walk out of the allowed regions. */
static uint8_t xcp_r5_check_memory(uint8_t ext, uint32_t addr, uint8_t size) {
    /* Only absolute addressing maps to R5 memory: ext 0 (ABS, the A2L's mode;
     * DAQ entries are checked with it at START_STOP_SYNCH) and 0xFE (PTR, what
     * SET_MTA converts ABS into before the engine asks). Every other extension
     * (APP 1, DYN 2..15) must be refused HERE for DAQ entries: the engine would
     * otherwise start the list and index its 2-entry base-pointer array with
     * the extension inside ISR_Control (out-of-bounds read -> garbage source
     * pointer -> data abort in the control ISR). */
    if (ext != XCP_ADDR_EXT_ABS && ext != XCP_ADDR_EXT_PTR) {
        return CRC_ACCESS_DENIED;
    }
    const uint64_t a = addr;
    const uint64_t end = a + size; /* u64: no wrap at the top of OCM */
    if (end <= 0x00010000u) return CRC_CMD_OK;                        /* ATCM  */
    if (a >= 0x00020000u && end <= 0x00030000u) return CRC_CMD_OK;    /* BTCM  */
    if (a >= 0x40000000u && end <= 0x47FF0000u) return CRC_CMD_OK;    /* DDR   */
    if (a >= 0xFFFC0000u && end <= 0x100000000ull) return CRC_CMD_OK; /* OCM   */
    return CRC_ACCESS_DENIED;
}

/* Write gate for DOWNLOAD / SHORT_DOWNLOAD (XCP_MTA_WRITE_CHECK,
 * xcplib_r5_cfg.h): called by XcpWriteMta for every write, after the range
 * check above has accepted the address. Readable is not writable: the R5's
 * code and constants sit in the same DDR region as its variables, the
 * exception vectors in the ATCM, and the OCM carries the exchange with the
 * A53 - a calibration write with a stale A2L address into any of those takes
 * down the control core. Only the data sections are writable (linker
 * symbols from lscript.ld), which is where every calibratable global lives;
 * stacks and heap are not. */
extern uint8_t __data_start[], __data_end[];
extern uint8_t __sdata_start[], __sdata_end[];
extern uint8_t __sbss_start[], __sbss_end[];
extern uint8_t __bss_start__[], __bss_end__[];

uint8_t xcp_r5_check_write(uint32_t addr, uint8_t size) {
#if XCP_R5_READ_ONLY
    (void)addr;
    (void)size;
    xcp_r5_write_denied++;
    return CRC_WRITE_PROTECTED;
#else
    static const struct {
        const uint8_t *start;
        const uint8_t *end;
    } kWritable[] = {
        {__data_start, __data_end},
        {__sdata_start, __sdata_end},
        {__sbss_start, __sbss_end},
        {__bss_start__, __bss_end__},
    };
    const uintptr_t a = (uintptr_t)addr;
    const uintptr_t e = a + size; /* no wrap: the range check passed first */
    for (uint32_t i = 0u; i < (sizeof(kWritable) / sizeof(kWritable[0])); i++) {
        if (a >= (uintptr_t)kWritable[i].start && e <= (uintptr_t)kWritable[i].end) {
            return CRC_CMD_OK;
        }
    }
    xcp_r5_write_denied++;
    return CRC_WRITE_PROTECTED;
#endif
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

/* Segment popped from the queue but not yet written: the XCP_OUT chain was
 * full. It stays popped (queue32 advances its read index only on
 * queueRelease, and the engine never clears the queue behind the transport)
 * and goes out first in the next sweep. Only touched from the sweep context. */
static tQueueBuffer gTxHeld;
static int gTxHeldValid = 0;

/* Drain the DAQ transmit queue into the XCP_OUT chain. Mirrors
 * XcpTlHandleTransmitQueue (queue32 path). A full chain does NOT drop: the
 * segment is held for the next sweep (xcp_r5_tx_held), so the 32 KB queue
 * really bridges a slow main-loop iteration instead of converting backlog
 * into loss. Loss happens only when the queue itself overflows
 * (xcp_r5_queue_lost) or XCP_OUT is capped per sweep for good.
 * NO lock around the OCM memcpy/cache-flush: queuePop/queueRelease take
 * queue32's internal (short) critical sections; holding an IRQ-disabling
 * lock across the 252-byte copy would jitter the control ISR. */
void xcp_r5_tx_pump(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    for (;;) {
        if (!gTxHeldValid) {
            uint32_t lost = 0u;
            /* flush=true: hand out the current partially-filled segment too. With
             * flush=false, queue32's queuePop never returns a lone open segment,
             * so DAQ data would sit in the queue until a full segment accumulates. */
            gTxHeld = queuePop(gQueue, true /*accumulate*/, true /*flush*/, &lost);
            if (lost > 0u) {
                xcp_r5_queue_lost += lost; /* ISR produced faster than the sweep drained */
            }
            if (gTxHeld.size == 0u) {
                break; /* queue empty */
            }
            gTxHeldValid = 1;
        }
        uint16_t l = gTxHeld.size;
        if (l <= 0xFFu) {
            if (!ocm_xcp_fifo_write_fits((uint8_t)l, gTxHeld.buffer)) {
                xcp_r5_tx_held++; /* chain full: keep the segment, retry next sweep */
                break;
            }
            (void)ocm_xcp_fifo_write((uint8_t)l, gTxHeld.buffer); /* cannot fail now */
        } else {
            /* Impossible with XCPTL_MAX_SEGMENT_SIZE 252, but never truncate. */
            xcp_r5_tx_oversize_drop++;
        }
        queueRelease(gQueue, &gTxHeld);
        gTxHeldValid = 0;
    }
}

bool XcpTlWaitForTransmitQueueEmpty(uint16_t timeout_ms) {
    (void)timeout_ms;
    xcp_r5_tx_pump();
    return true;
}

/* --- R5 driving API ------------------------------------------------------- */

/* Sample DAQ. Call from ISR_Control. Thin: XcpEvent pushes to the queue; the
 * OCM write happens in xcp_r5_poll(). An event with no running DAQ list costs
 * only the isStarted()/isDaqRunning() checks, so the unused rasters are free. */
void xcp_r5_event(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    xcp_r5_cycle_count++;
    XcpEvent(xcp_r5_daq_event);

    /* Named time slices derived from the control-ISR rate. */
    for (uint32_t i = 0u; i < XCP_R5_SLICE_COUNT; i++) {
        if (++gSliceCnt[i] >= kXcpR5Slice[i].divider) {
            gSliceCnt[i] = 0u;
            XcpEvent(xcp_r5_daq_slice_event[i]);
        }
    }
}

/* One full exchange sweep (MAIN-LOOP context; use xcp_r5_background() for
 * pacing): refresh XCP_IN, open the XCP_OUT seqlock (keeping an
 * unacknowledged DAQ chain in place), execute a NEW command-batch generation
 * from XCP_IN -> XcpCommand (responses go to the CTO pending FIFO),
 * acknowledge the generation, pump the mailbox, drain the DAQ queue ->
 * XCP_OUT chain, then publish the cycle (flush + even seqlock). The caller
 * signals the A53 (IPI) after this returns. */
void xcp_r5_poll(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    ocm_xcp_fifo_cache_invalidate_before_read(); /* fresh XCP_IN: acks, in_gen, commands */

    /* Consumption handshake: a chain that carried data stays in place until
     * the A53 acknowledges it; this sweep then only updates the header
     * (commands, mailbox) and leaves the DAQ backlog in the queue. */
    int keep = 0;
    if (gOutPending) {
        if (ocm_xcp_out_chain_acked()) {
            gOutPending = 0;
            gOutHoldSweeps = 0u;
        } else if (gOutHoldSweeps < XCP_R5_OUT_HOLD_MAX_SWEEPS) {
            gOutHoldSweeps++;
            xcp_r5_out_held++;
            keep = 1;
        } else {
            xcp_r5_out_overwritten++; /* gateway gone or stalled: give up on that chain */
            gOutPending = 0;
            gOutHoldSweeps = 0u;
        }
    }
    if (keep) {
        ocm_xcp_fifo_prepare_write_keep(); /* seqlock -> odd; chain untouched */
    } else {
        ocm_xcp_fifo_prepare_write(); /* seqlock -> odd; chain rewound */
    }

    /* Commands: process a batch only when its generation is new. The A53
     * publishes the generation after the chain bytes, so a new value here
     * implies a complete chain; an unchanged value means either nothing new
     * or a batch already executed (never run a generation twice). The A53
     * re-offers identical batch bytes every IPI until acknowledged, so a
     * command can no longer be lost to IPI/cycle overlap (the hedrive T8
     * pcap-proven session killer). */
    uint32_t in_gen = ocm_xcp_in_gen_read();
    if (in_gen != gInGenDone) {
        if (in_gen != gInCurGen) {
            gInCurGen = in_gen; /* new batch: start at its first frame */
            gInCurRec = 0u;
            gInCurOff = 0u;
        }
        int complete = 1;
        uint16_t rec = 0u;
        ocm_xcp_fifo_prepare_read();
        uint8_t len;
        uint8_t *data;
        while (ocm_xcp_fifo_read(&len, &data)) {
            /* One record = one UDP datagram, which may carry SEVERAL
             * concatenated TL frames ([dlc][ctr][packet])+ (e.g. CANape
             * block-mode command bursts). */
            uint16_t off = 0u;
            if (rec < gInCurRec) {
                rec++;
                continue; /* executed in an earlier sweep of this generation */
            }
            if (rec == gInCurRec) {
                off = gInCurOff; /* resume inside the record */
            }
            while ((uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE) <= (uint16_t)len) {
                uint16_t dlc = (uint16_t)(data[off] | ((uint16_t)data[off + 1] << 8));
                if (dlc == 0u ||
                    (uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc) > (uint16_t)len) {
                    break; /* padding or malformed frame: stop parsing this record */
                }
                if (gCtoPendingCount >= XCP_R5_CTO_PENDING_DEPTH) {
                    /* No room for another response: suspend the batch here
                     * and resume at this frame next sweep (one mailbox ack per
                     * sweep frees one slot). Nothing is acknowledged yet, so
                     * the A53 keeps offering the same bytes. */
                    gInCurRec = rec;
                    gInCurOff = off;
                    complete = 0;
                    xcp_r5_in_resumed++;
                    break;
                }
                if (dlc > XCPTL_MAX_CTO_SIZE) {
                    /* Transport-layer contract (upstream xcpethtl.c does the
                     * same): the engine asserts cmdLen <= XCPTL_MAX_CTO_SIZE
                     * and a bigger frame would abort() the control core. */
                    xcp_r5_cmd_oversize_drop++;
                } else {
                    XcpCommand((const uint32_t *)(const void *)(data + off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE),
                               (uint8_t)dlc);
                }
                off = (uint16_t)(off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc);
            }
            if (!complete) {
                break;
            }
            rec++;
        }
        if (complete) {
            gInGenDone = in_gen;
            xcp_r5_in_generations++;
        }
    }
    ocm_xcp_in_consumed_write(gInGenDone);

    /* After command processing: a response generated this cycle can ride the
     * mailbox in this same cycle (if it is free). */
    xcp_r5_pump_cto();

    if (!keep) {
        xcp_r5_tx_pump();
        /* Covers segments written from within XcpCommand too
         * (XcpTlWaitForTransmitQueueEmpty). */
        gOutPending = ocm_xcp_fifo_chain_nonempty();
    }

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
    xcp_r5_daq_event = (uint16_t)XcpCreateEvent("DAQ_R5", XCP_R5_ISR_PERIOD_NS, 0u);
    if (xcp_r5_daq_event == 0xFFFFu) { /* XCP_UNDEFINED_EVENT_ID */
        gQueue = NULL; /* keep the ISR hooks inert */
        xcp_r5_init_result = -3;
        return -3;
    }
    /* Named time slices, created in A2L channel order. A shifted channel
     * number would silently move every signal to the wrong raster, so a
     * mismatch disables the engine instead (the A2L numbers are static). */
    for (uint32_t i = 0u; i < XCP_R5_SLICE_COUNT; i++) {
        xcp_r5_daq_slice_event[i] =
            (uint16_t)XcpCreateEvent(kXcpR5Slice[i].name, kXcpR5Slice[i].cycle_time_ns, 0u);
        if (xcp_r5_daq_slice_event[i] != (uint16_t)(xcp_r5_daq_event + 1u + i)) {
            gQueue = NULL; /* keep the ISR hooks inert */
            xcp_r5_init_result = -4;
            return -4;
        }
    }
    xcp_r5_init_result = 0;
    return 0;
}
