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
|     xcp_r5_background() from the MAIN LOOP: polls XCP_IN, runs command and
|                         DAQ exchanges when due; caller fires the IPI when
|                         it returns 1
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
|   maintenance — runs from the main loop (xcp_r5_background() pacing).
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

/* DAQ queue between the ISR (producer, XcpEvent) and the main-loop DAQ
 * exchanges (consumer), in segments of up to XCPTL_MAX_SEGMENT_SIZE. It must
 * hold what the control ISR produces while one DAQ exchange waits for the
 * A53's acknowledge plus a margin for A53 hiccups: 128 KB = ~93 segments =
 * ~3 ms at 40 MB/s (1 KB per cycle at 40 kHz). Was 32 KB (~0.8 ms at that
 * rate), sized for 10 kHz. Lives on the heap (lscript.ld _HEAP_SIZE). */
#define XCP_R5_QUEUE_SIZE_BYTES (128u * 1024u)

#include "xparameters.h" /* XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ */
#include "../../uz/uz_SystemTime/uz_SystemTime.h" /* uz_SystemTime_GetInterruptCounter, _GetIsrStartTicks */
#include "../../include/isr_diag.h" /* UZ_ISR_DIAG: split of xcp_r5_event(), main-loop phase */

/* Time base of the main-loop pacing: the control ISRs counted by
 * uz_SystemTime (uz_SystemTime_ISR_Tic(), the first call in ISR_Control).
 * The main loop runs only between two ISRs, so a changed count means that a
 * control ISR has run since the count was last read. Only the low word
 * is used: one 32-bit load cannot tear against the ISR's 64-bit increment,
 * and differences modulo 2^32 stay valid (the count wraps after ~30 h at
 * 40 kHz). */
static inline uint32_t xcp_r5_isr_count(void) {
    return (uint32_t)uz_SystemTime_GetInterruptCounter();
}

#if XCP_R5_PROFILE
/* R5 CPU cycle counter (PMU PMCCNTR): the time base of the profile, which
 * needs sub-microsecond resolution; the pacing does not use it. Enabled by
 * xcp_r5_init(); it wraps every ~8.6 s at 500 MHz, so only differences of a
 * few milliseconds are used. */
#define XCP_R5_CYC_PER_US (XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ / 1000000u)

static inline uint32_t xcp_r5_cycles(void) {
    uint32_t v;
    __asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(v));
    return v;
}

static void xcp_r5_cycles_enable(void) {
    uint32_t pmcr;
    __asm volatile("mrc p15, 0, %0, c9, c12, 0" : "=r"(pmcr));
    pmcr |= 1u;         /* E: counters on */
    pmcr &= ~(1u << 3); /* D: count every cycle, not every 64th */
    __asm volatile("mcr p15, 0, %0, c9, c12, 0" ::"r"(pmcr));
    __asm volatile("mcr p15, 0, %0, c9, c12, 1" ::"r"(1u << 31)); /* PMCNTENSET: cycle counter */
}

volatile xcp_r5_prof_t xcp_r5_prof = {.version = 2u, .cpu_hz = XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ};
/* The layout is read by tools/xcp_test/xcp_poll.py (PROF_FMT): keep both in sync. */
_Static_assert(sizeof(xcp_r5_prof_t) == 160u, "xcp_r5_prof_t layout changed");
_Static_assert(__builtin_offsetof(xcp_r5_prof_t, elapsed_cyc) == 40u, "xcp_r5_prof_t layout changed");
_Static_assert(__builtin_offsetof(xcp_r5_prof_t, ack_wait_us) == 136u, "xcp_r5_prof_t layout changed");

/* Written by the control ISR (xcp_r5_event), 32-bit and wrapping; the main
 * loop folds the differences into the 64-bit sums of xcp_r5_prof. */
static volatile uint32_t gProfIsrNs = 0u;    /* run time of every ISR_Control [ns] */
static volatile uint32_t gProfEventCyc = 0u; /* cycles spent in xcp_r5_event()     */
static volatile uint32_t gProfEventCalls = 0u;
static volatile uint32_t gProfEventMax = 0u;
/* Main loop only. */
static uint32_t gProfIsrNsFold = 0u;
static uint32_t gProfEventCycFold = 0u;
static uint32_t gProfEventCallsFold = 0u;
static uint32_t gProfLastStart = 0u;
static int gProfHaveLast = 0;
static uint32_t gProfChainBytes = 0u; /* chain bytes written in the current exchange */
static uint32_t gProfOutSentCyc = 0u; /* DAQ chain published at, for ack_wait_us    */
#endif

/* Framed CRM messages must fit the OCM mailbox slot. */
#if (XCPTL_MAX_CTO_SIZE + XCPTL_TRANSPORT_LAYER_HEADER_SIZE) > 256
#error "XCPTL_MAX_CTO_SIZE + header exceeds OCM_XCP_CTO_SLOT_LEN"
#endif
/* A popped queue segment is written as one OCM record. */
#if XCPTL_MAX_SEGMENT_SIZE > OCM_XCP_RECORD_MAX
#error "XCPTL_MAX_SEGMENT_SIZE exceeds OCM_XCP_RECORD_MAX (ocm_xcp_fifo.h)"
#endif

/* Pending CTO responses waiting for the OCM mailbox (one in-flight response
 * at a time, acknowledged by the A53, i.e. one response per sweep). A command
 * batch (generation) may carry more frames than this - CANape block mode,
 * a pipelining master - so xcp_r5_poll stops executing when the FIFO is full
 * and resumes the SAME generation at the next frame in a later sweep; the
 * depth only sets how far it runs ahead of the mailbox. */
#define XCP_R5_CTO_PENDING_DEPTH 4u

/* Main-loop pacing (xcp_r5_background). Commands and DAQ are decoupled
 * (2026-11-18): the R5 looks at the XCP_IN header on every main-loop pass,
 * but exchanges data with the A53 at most once per control period: after an
 * exchange, the next one waits for the next control ISR (xcp_r5_isr_count).
 * That also bounds the IPIs to one per period. A new command generation or a
 * response waiting for the mailbox gets a header-only exchange at once. A
 * DAQ exchange rewrites the XCP_OUT chain only after the A53 has
 * acknowledged the previous chain, and then as soon as the oldest waiting
 * DAQ data is XCP_R5_DAQ_INTERVAL_US old or XCP_R5_DAQ_TRIGGER_SEGMENTS
 * queue segments are waiting. Without any exchange for
 * XCP_R5_DAQ_INTERVAL_US, a header-only heartbeat follows (it repeats a
 * header copy the A53 had to skip and keeps the gateway counter mirror
 * fresh). The times are counted in whole control periods.
 * Until 2026-11-18 the time base was the CPU cycle counter, with a look at
 * most every 5 us. At 40 kHz the main loop only runs in the ~8 us between two
 * control ISRs, so that came to one or two looks per gap (40,700 looks/s at
 * 500 B/cycle, 21,200/s at 900 B/cycle, where a DAQ copy spans about three
 * periods). Looking only once per period instead was tried the same day and
 * cost commands 5-40 us at 40 kHz, because a command that lands after the
 * one look waits for the next period (and would wait up to 100 us at 10 kHz).
 * Before 2026-11-18, one sweep on a fixed 100 us grid did everything:
 * commands waited for the next sweep, and a chain acknowledged a few
 * microseconds after the next sweep had started was kept for a whole further
 * period. From ~1000 B/cycle at 40 kHz that cascaded into full 31 KB chains
 * and queue overflow while the A53 still idled 40-57 % (bench 2026-11-17).
 * A look itself is cheap (four cache lines). */
#ifndef XCP_R5_DAQ_INTERVAL_US
#define XCP_R5_DAQ_INTERVAL_US 1000u
#endif
/* The trigger level sets the size of a DAQ exchange under load, and with it
 * how long a command waits behind a running copy and how many datagrams the
 * A53 then sends in one burst. Bench 2026-11-18 at 900 B/cycle, 40 kHz, with
 * the gateway letting commands through during a burst (xcp_gateway_a53.c):
 *   8 segments: 184 us per DAQ exchange, back-to-back commands 317 us median
 *   4 segments:  74 us,                  252 us
 *   2 segments:  40 us,                  193 us, but 14,500 instead of
 *               6,800 IPIs/s and 34 instead of 37 % A53 idle time.
 * Smaller chains also copy cheaper per KB (the data is younger, still in the
 * cache); the R5's share of time in exchanges stayed at 17-19 % for all
 * three. At low rates the interval decides, not the trigger. */
#ifndef XCP_R5_DAQ_TRIGGER_SEGMENTS
#define XCP_R5_DAQ_TRIGGER_SEGMENTS 4u
#endif

/* XCP_OUT consumption handshake: how long a non-empty chain waits for the
 * A53 acknowledge before it is overwritten anyway (xcp_r5_out_overwritten).
 * Only matters when the gateway is not running at all; the acknowledge takes
 * tens of microseconds on hardware. */
#define XCP_R5_OUT_HOLD_MAX_US 5000u

/* Control-ISR rate = the base DAQ raster. Same expression main.c uses for
 * Global_Data.av.isr_samplerate_s, so it follows UZ_PWM_FREQUENCY, the trigger
 * source and the ADC-to-ISR ratio automatically. */
#define XCP_R5_ISR_FREQ_HZ                                                     \
    ((uint32_t)((UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor) /               \
                INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE))

/* Base event period in ns, reported to the master via GET_DAQ_EVENT_INFO
 * (0 = "sporadic or unknown", the sane answer for a misconfigured 0 Hz ISR). */
#define XCP_R5_ISR_PERIOD_NS ((XCP_R5_ISR_FREQ_HZ) > 0u ? (1000000000u / (XCP_R5_ISR_FREQ_HZ)) : 0u)

/* A pacing time in whole control periods: rounded up, at least one. */
#define XCP_R5_PERIODS_CEIL(us) (((uint64_t)(us) * (XCP_R5_ISR_FREQ_HZ) + 999999u) / 1000000u)
#define XCP_R5_US_TO_PERIODS(us) \
    (XCP_R5_PERIODS_CEIL(us) > 0u ? (uint32_t)XCP_R5_PERIODS_CEIL(us) : 1u)

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
 *   xcp_r5_tx_oversize_drop popped segment > OCM_XCP_RECORD_MAX (must stay 0;
 *                           the cfg and the #if above bound it)
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
 *   xcp_r5_queue_lost       queue32 overflow -> DAQ frames lost at the
 *                           source (more DAQ data than the exchanges can
 *                           carry, or the main loop is blocked)
 *   xcp_r5_tx_held          DAQ exchanges that filled the XCP_OUT chain
 *                           with backlog left over (or a segment popped in a
 *                           header-only exchange); it stayed popped and went
 *                           out first in the next DAQ exchange (backlog, not
 *                           loss). Climbing steadily = DAQ production exceeds
 *                           the ~31 KB per exchange the window can carry.
 *   xcp_r5_out_held         DAQ exchanges that were due while the A53 had
 *                           not acknowledged the previous chain yet (once
 *                           per chain). Latency, not loss.
 *   xcp_r5_out_overwritten  chains overwritten unacknowledged after
 *                           XCP_R5_OUT_HOLD_MAX_US (gateway not running or
 *                           stalled for milliseconds) -> DAQ data lost.
 *                           Must stay 0 while a master is connected.
 *   xcp_r5_write_denied     DOWNLOAD/SHORT_DOWNLOAD refused by the write
 *                           gate (target outside the data sections, or a
 *                           measurement-only build); the master gets
 *                           ERR_WRITE_PROTECTED
 *   xcp_r5_sweep_count      exchanges executed (DAQ, command/response and
 *                           heartbeat) -> liveness probe
 *   xcp_r5_sweep_gap_max_us worst gap between two xcp_r5_background() calls,
 *                           counted in whole control periods (25 us steps
 *                           at 40 kHz). THE main-loop health number: a few
 *                           periods = fine (a DAQ copy at 900 B/cycle spans
 *                           ~3); much more = something in the main loop
 *                           blocks (commands wait that long; the 128 KB
 *                           queue rides out ~3 ms at 40 MB/s).
 *                           Includes the exchanges themselves. Reset via
 *                           debugger. */
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

/* Pacing state (main-loop context only, in control periods). */
static int      gOutPending = 0;        /* DAQ chain published, not acknowledged */
static uint32_t gOutSentIsr = 0u;       /* ... published at (the IPI)            */
static int      gOutWaitCounted = 0;    /* xcp_r5_out_held counted for it        */
static uint32_t gDaqAgeIsr = 0u;        /* queue last empty / last DAQ exchange  */
static uint32_t gLastExchangeIsr = 0u;  /* end of the last exchange (heartbeat)  */

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
        if (l <= OCM_XCP_RECORD_MAX) {
            if (!ocm_xcp_fifo_write_fits(l, gTxHeld.buffer)) {
                xcp_r5_tx_held++; /* chain full: keep the segment, retry next sweep */
                break;
            }
            (void)ocm_xcp_fifo_write(l, gTxHeld.buffer); /* cannot fail now */
#if XCP_R5_PROFILE
            gProfChainBytes += 4u + (uint32_t)l; /* length word + record */
#endif
        } else {
            /* Impossible (segment <= OCM_XCP_RECORD_MAX, #if above), but never truncate. */
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
#if XCP_R5_PROFILE
    const uint32_t c0 = xcp_r5_cycles();
#endif
    xcp_r5_cycle_count++;
    /* Every sample of this control cycle carries the cycle's start: the timer
     * value uz_SystemTime_ISR_Tic() latched at ISR entry (10 ns ticks, the DAQ
     * clock of xcplib_r5_cfg.h), not the time this call happens to run. */
    const uint64_t cycle_start = uz_SystemTime_GetIsrStartTicks();
#if UZ_ISR_DIAG
    const uint32_t diag_c0 = uz_isr_diag_cycles();
#endif
    XcpEventAt(xcp_r5_daq_event, cycle_start);
#if UZ_ISR_DIAG
    const uint32_t diag_c1 = uz_isr_diag_cycles();
#endif

    /* Named time slices derived from the control-ISR rate. */
    for (uint32_t i = 0u; i < XCP_R5_SLICE_COUNT; i++) {
        if (++gSliceCnt[i] >= kXcpR5Slice[i].divider) {
            gSliceCnt[i] = 0u;
            XcpEventAt(xcp_r5_daq_slice_event[i], cycle_start);
        }
    }
#if UZ_ISR_DIAG
    uz_isr_diag_xcp_base = diag_c1 - diag_c0;
    uz_isr_diag_xcp_slices = uz_isr_diag_cycles() - diag_c1;
#endif
#if XCP_R5_PROFILE
    {
        const uint32_t d = xcp_r5_cycles() - c0;
        gProfEventCyc += d;
        gProfEventCalls++;
        if (d > gProfEventMax) {
            gProfEventMax = d;
        }
        /* Run time of the previous ISR_Control (uz_SystemTime Tic/Toc): the
         * main loop subtracts it from the phases it interrupted. */
        gProfIsrNs += (uint32_t)(uz_SystemTime_GetIsrExectionTimeInUs() * 1000.0f);
    }
#endif
}

#if XCP_R5_PROFILE
/* Phase stamps of one exchange: cycle counter and ISR time sum. */
#define XCP_R5_PROF_MARK(i)        \
    do {                           \
        pc[i] = xcp_r5_cycles();   \
        pi[i] = gProfIsrNs;        \
    } while (0)

static void xcp_r5_prof_account(const uint32_t *pc, const uint32_t *pi, int keep) {
    volatile xcp_r5_prof_t *p = &xcp_r5_prof;
    if (p->reset != 0u) {
        /* Requested by the master (DOWNLOAD, runs in this context): restart
         * all sums with the next exchange. */
        p->reset = 0u;
        p->exchanges = 0u;
        p->keeps = 0u;
        p->event_calls = 0u;
        p->event_cyc_max = 0u;
        p->copy_cyc_max = 0u;
        p->flush_cyc_max = 0u;
        p->total_cyc_max = 0u;
        p->elapsed_cyc = 0u;
        p->chain_bytes = 0u;
        p->cyc_refresh = 0u;
        p->cyc_commands = 0u;
        p->cyc_copy = 0u;
        p->cyc_flush = 0u;
        p->cyc_total = 0u;
        p->isr_ns_copy = 0u;
        p->isr_ns_flush = 0u;
        p->isr_ns_total = 0u;
        p->isr_ns_all = 0u;
        p->event_cyc = 0u;
        p->ack_wait_us = 0u;
        p->ack_n = 0u;
        p->ack_wait_max_us = 0u;
        p->daq_waits = 0u;
        p->polls = 0u;
        gProfEventMax = 0u;
        gProfIsrNsFold = gProfIsrNs;
        gProfEventCycFold = gProfEventCyc;
        gProfEventCallsFold = gProfEventCalls;
        gProfHaveLast = 0;
        gProfChainBytes = 0u;
        return;
    }
    const uint32_t copy = pc[3] - pc[2];
    const uint32_t flush = pc[4] - pc[3];
    const uint32_t total = pc[4] - pc[0];
    p->exchanges++;
    if (keep) {
        p->keeps++;
    }
    if (gProfHaveLast) {
        p->elapsed_cyc += (uint32_t)(pc[0] - gProfLastStart);
    }
    gProfLastStart = pc[0];
    gProfHaveLast = 1;
    p->chain_bytes += gProfChainBytes;
    gProfChainBytes = 0u;
    p->cyc_refresh += (uint32_t)(pc[1] - pc[0]);
    p->cyc_commands += (uint32_t)(pc[2] - pc[1]);
    p->cyc_copy += copy;
    p->cyc_flush += flush;
    p->cyc_total += total;
    p->isr_ns_copy += (uint32_t)(pi[3] - pi[2]);
    p->isr_ns_flush += (uint32_t)(pi[4] - pi[3]);
    p->isr_ns_total += (uint32_t)(pi[4] - pi[0]);
    if (copy > p->copy_cyc_max) {
        p->copy_cyc_max = copy;
    }
    if (flush > p->flush_cyc_max) {
        p->flush_cyc_max = flush;
    }
    if (total > p->total_cyc_max) {
        p->total_cyc_max = total;
    }
    {
        const uint32_t v = gProfIsrNs;
        p->isr_ns_all += (uint32_t)(v - gProfIsrNsFold);
        gProfIsrNsFold = v;
    }
    {
        const uint32_t v = gProfEventCyc;
        p->event_cyc += (uint32_t)(v - gProfEventCycFold);
        gProfEventCycFold = v;
    }
    {
        const uint32_t v = gProfEventCalls;
        p->event_calls += (uint32_t)(v - gProfEventCallsFold);
        gProfEventCallsFold = v;
    }
    p->event_cyc_max = gProfEventMax;
}

/* One DAQ chain acknowledged: wait from its publication (the IPI). */
static void xcp_r5_prof_ack(uint32_t us) {
    volatile xcp_r5_prof_t *p = &xcp_r5_prof;
    p->ack_wait_us += us;
    p->ack_n++;
    if (us > p->ack_wait_max_us) {
        p->ack_wait_max_us = us;
    }
}
#endif

/* One exchange, MAIN-LOOP context (xcp_r5_background() decides when): open
 * the XCP_OUT seqlock, execute a NEW command-batch generation from XCP_IN ->
 * XcpCommand (responses go to the CTO pending FIFO), acknowledge it, pump the
 * response mailbox and - in a DAQ exchange only - rewrite the XCP_OUT chain
 * from the DAQ queue; then publish (flush + even seqlock). A header-only
 * exchange leaves the chain and chain_seq untouched, so it may run while the
 * A53 has not acknowledged (or still reads) the chain. Needs a fresh XCP_IN
 * header (ocm_xcp_in_refresh_header()); the caller signals the A53 (IPI). */
static void xcp_r5_exchange(int daq) {
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_COMMANDS);
#if XCP_R5_PROFILE
    uint32_t pc[5];
    uint32_t pi[5];
    XCP_R5_PROF_MARK(0);
#endif
    /* A new command generation needs its chain bytes as well. */
    const uint32_t in_gen = ocm_xcp_in_gen_read();
    if (in_gen != gInGenDone) {
        ocm_xcp_fifo_cache_invalidate_before_read();
    }
#if XCP_R5_PROFILE
    XCP_R5_PROF_MARK(1);
#endif
    if (daq) {
        ocm_xcp_fifo_prepare_write(); /* seqlock -> odd; chain rewound, chain_seq 0 */
    } else {
        ocm_xcp_fifo_prepare_write_keep(); /* seqlock -> odd; chain untouched */
    }

    /* Commands: process a batch only when its generation is new. The A53
     * publishes the generation after the chain bytes, so a new value here
     * implies a complete chain; an unchanged value means either nothing new
     * or a batch already executed (never run a generation twice). The A53
     * re-offers identical batch bytes every IPI until acknowledged, so a
     * command can no longer be lost to IPI/cycle overlap (the hedrive T8
     * pcap-proven session killer). */
    if (in_gen != gInGenDone) {
        if (in_gen != gInCurGen) {
            gInCurGen = in_gen; /* new batch: start at its first frame */
            gInCurRec = 0u;
            gInCurOff = 0u;
        }
        int complete = 1;
        uint16_t rec = 0u;
        ocm_xcp_fifo_prepare_read();
        uint16_t len;
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

    /* After command processing: a response generated now can ride the
     * mailbox in this same exchange (if it is free). */
    xcp_r5_pump_cto();
#if XCP_R5_PROFILE
    XCP_R5_PROF_MARK(2);
#endif

    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_COPY);
    if (daq) {
        xcp_r5_tx_pump();
        /* Covers segments written from within XcpCommand too
         * (XcpTlWaitForTransmitQueueEmpty). */
        gOutPending = ocm_xcp_fifo_chain_nonempty();
    }
#if XCP_R5_PROFILE
    XCP_R5_PROF_MARK(3);
#endif

    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_FLUSH);
    ocm_xcp_fifo_cache_flush_after_write(); /* chain, then header + even seq */
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_PACING);
#if XCP_R5_PROFILE
    XCP_R5_PROF_MARK(4);
    xcp_r5_prof_account(pc, pi, !daq);
#endif
}

/* One unpaced exchange: commands, and DAQ if the previous chain is
 * acknowledged. For special cases; the main loop uses xcp_r5_background().
 * The caller triggers the IPI afterwards. */
void xcp_r5_poll(void) {
    if (gQueue == NULL) {
        return; /* init failed or not run: engine disabled */
    }
    ocm_xcp_in_refresh_header();
    const int daq = !gOutPending || ocm_xcp_out_chain_acked();
    xcp_r5_exchange(daq);
    gLastExchangeIsr = xcp_r5_isr_count();
    if (daq) {
        gDaqAgeIsr = gLastExchangeIsr;
        gOutSentIsr = gLastExchangeIsr;
        gOutWaitCounted = 0;
#if XCP_R5_PROFILE
        gProfOutSentCyc = xcp_r5_cycles();
#endif
    }
}

/* Paced driver. Call from the MAIN LOOP every iteration; returns 1 when it
 * ran an exchange - the caller must then trigger the IPI to the A53 gateway.
 * Unless an exchange already ran in the current control period, it
 * refreshes the XCP_IN header and decides (see the pacing notes above):
 * commands and responses at once, DAQ once the last chain is acknowledged
 * and the interval or the trigger level is reached, a heartbeat after a
 * quiet interval. Keeping the exchanges out of ISR_Control removes their
 * cost (~10 us base + ~10 us/KB, measured 2026-07-11) from the control ISR;
 * only the XcpEvent sampling copy remains there. */
static int xcp_r5_background_sweep(void);

int xcp_r5_background(void) {
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_PACING);
    const int r = xcp_r5_background_sweep();
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_OTHER);
    return r;
}

static int xcp_r5_background_sweep(void) {
    static uint32_t last_call_isr = 0u;
    static int first_call = 1;
    if (gQueue == NULL) {
        return 0; /* init failed or not run: engine disabled */
    }
    const uint32_t now = xcp_r5_isr_count();
    if (first_call) {
        first_call = 0; /* boot-to-first-call gap is not a loop-health signal */
        gDaqAgeIsr = now;
        gLastExchangeIsr = now;
    } else {
        const uint32_t gap_us = (uint32_t)(now - last_call_isr) * (XCP_R5_ISR_PERIOD_NS / 1000u);
        if (gap_us > xcp_r5_sweep_gap_max_us) {
            xcp_r5_sweep_gap_max_us = gap_us;
        }
    }
    last_call_isr = now;
    if (now == gLastExchangeIsr) {
        return 0; /* at most one exchange (IPI) per control period */
    }
    ocm_xcp_in_refresh_header(); /* cto_ack, in_gen, out_ack */
#if XCP_R5_PROFILE
    xcp_r5_prof.polls++;
#endif

    /* DAQ chain consumption handshake. */
    if (gOutPending) {
        if (ocm_xcp_out_chain_acked()) {
            gOutPending = 0;
#if XCP_R5_PROFILE
            xcp_r5_prof_ack((xcp_r5_cycles() - gProfOutSentCyc) / XCP_R5_CYC_PER_US);
#endif
        } else if ((uint32_t)(now - gOutSentIsr) >= XCP_R5_US_TO_PERIODS(XCP_R5_OUT_HOLD_MAX_US)) {
            xcp_r5_out_overwritten++; /* gateway gone or stalled: give up on that chain */
            gOutPending = 0;
        }
    }

    /* Commands and responses go at once. */
    const int cmd = (ocm_xcp_in_gen_read() != gInGenDone) && (gCtoPendingCount < XCP_R5_CTO_PENDING_DEPTH);
    const int cto = (gCtoPendingCount != 0u) && ocm_xcp_cto_mailbox_free();

    /* DAQ once the waiting data is old enough or plenty, and only on an
     * acknowledged chain. gDaqAgeIsr follows "now" while nothing waits, so
     * the interval is the age of the oldest waiting data. */
    const uint32_t interval = XCP_R5_US_TO_PERIODS(XCP_R5_DAQ_INTERVAL_US);
    const uint32_t level = queueLevel(gQueue, NULL);
    int daq = 0;
    if (!gTxHeldValid && level == 0u) {
        gDaqAgeIsr = now;
    } else if (gTxHeldValid || level >= XCP_R5_DAQ_TRIGGER_SEGMENTS ||
               (uint32_t)(now - gDaqAgeIsr) >= interval) {
        if (!gOutPending) {
            daq = 1;
        } else if (!gOutWaitCounted) {
            gOutWaitCounted = 1;
            xcp_r5_out_held++; /* due, but the last chain is not acknowledged yet */
#if XCP_R5_PROFILE
            xcp_r5_prof.daq_waits++;
#endif
        }
    }
    const int beat = (uint32_t)(now - gLastExchangeIsr) >= interval;
    if (!cmd && !cto && !daq && !beat) {
        return 0;
    }
    if (cmd) {
        /* Commands get a quick header-only exchange; DAQ follows in the next
         * control period.
         * A DAQ exchange that is already copying is NOT cut short for a
         * command: the cut chain would need its own acknowledge before the
         * rest could follow, ~50 us of DAQ dead time per command, and with
         * back-to-back commands at 1000 B/cycle that pushed the R5 into
         * overload (23 % of the DAQ data lost, bench 2026-11-17). A command
         * waits for the running copy instead (at most one chain). */
        daq = 0;
    }
    xcp_r5_exchange(daq);
    gLastExchangeIsr = xcp_r5_isr_count();
    if (daq) {
        gDaqAgeIsr = gLastExchangeIsr;
        gOutSentIsr = gLastExchangeIsr; /* the acknowledge wait starts with the IPI */
        gOutWaitCounted = 0;
#if XCP_R5_PROFILE
        gProfOutSentCyc = xcp_r5_cycles();
#endif
    }
    xcp_r5_sweep_count++;
    return 1;
}

/* One-time init. Base addr 0 => XCP address == pointer => arbitrary R5
 * addressing (the point of Option Z). Returns 0 on success. */
int xcp_r5_init(const char *name, const char *epk) {
#if XCP_R5_PROFILE
    xcp_r5_cycles_enable(); /* profile time base */
#endif
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
