/*----------------------------------------------------------------------------
| xcptl_ocm.c
|   XCP transport layer over OCM rings for the bare-metal R5 (Option Z).
|   Replaces xcpethtl.c (sockets): the A53 gateway moves XCP-on-Ethernet
|   transport layer messages between UDP and three OCM rings
|   (shared/ocm_xcp_ring.h); this file connects the rings to the XCPlite
|   protocol engine.
|
|   Engine-facing symbols required by xcplite.c:
|     XcpTlGetCtr / XcpTlSendCrm / XcpTlWaitForTransmitQueueEmpty
|     the transmit queue API of queue.h (queueAcquire / queuePush / ...),
|     implemented here on the DAQ ring instead of queue32.c
|   R5 driving API (call from the Baremetal app):
|     xcp_r5_init()       once at startup (after uz_SystemTime is up)
|     xcp_r5_event()      from ISR_Control: sample DAQ, publish, IPI
|     xcp_r5_background() from the MAIN LOOP: execute commands
|
|   Context split:
|     control ISR  XcpEvent writes the DTOs straight into the DAQ ring in
|                  OCM (no intermediate queue, no copy). At the end of
|                  xcp_r5_event() the cycle's records are cleaned from the
|                  D-cache and the write position is published; an IPI
|                  tells the A53 once enough data or old enough data waits.
|     main loop    commands from the CMD ring -> XcpCommand -> responses
|                  into the RSP ring, published with an IPI at once.
|   Each ring has exactly one producer and one consumer, so nothing is
|   locked and nothing is ever written twice: no seqlock, no mailbox, no
|   generation or chain acknowledge (the former ocm_xcp_fifo.c design).
|   The engine has one queue handle; queueAcquire() picks the DAQ ring while
|   xcp_r5_event() runs and the RSP ring otherwise (events and SERV_TEXT
|   from command context), so each ring keeps a single producer.
|
|   DAQ rasters offered to the master (hedrive parity, see kXcpR5Slice below):
|   DAQ_R5 at the control-ISR rate plus the derived time slices daq_1ms,
|   daq_10ms, daq_100ms and daq_1s (hedrive names, as configured in the CANape
|   project). Event channel numbers are the creation order 0..4 and are
|   hardcoded in the A2L (CANape/UZ_XCP/uz.A2L) - keep both sides in sync.
|
|   Loss: a full DAQ ring refuses the DTO (xcp_r5_queue_lost), the only place
|   ECU-side DAQ loss can happen on the R5. A command is executed only when
|   the RSP ring has room for its response, so responses are never dropped.
|
|   TL wire frame = [dlc:u16 LE][ctr:u16 LE][packet ...] (XCPTL header = 4B),
|   exactly the XCP-on-UDP datagram payload the A53 gateway forwards. The
|   A53 stamps the transport counter at transmission time.
|
|   Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "xcplite.h"
#include "xcptl.h"
#include "queue.h"
#include "platform.h"
#include "xcptl_cfg.h"
#include "xcp_cfg.h" /* XCP_ADDR_EXT_ABS / XCP_ADDR_EXT_PTR */
#include "ocm_xcp_ring.h"
#include "xcp_r5.h" /* XCP_R5_READ_ONLY, XCP_R5_PROFILE */
#include "../../include/isr.h" /* UZ_PWM_FREQUENCY, Interrupt_ISR_freq_factor */
#include <string.h>
#include <stdint.h>
#include "xparameters.h" /* XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ, IPI target mask */
#include "xipipsu.h"
#include "../../uz/uz_SystemTime/uz_SystemTime.h" /* uz_SystemTime_GetInterruptCounter, _GetIsrStartTicks */
#include "../../include/isr_diag.h" /* UZ_ISR_DIAG: split of xcp_r5_event(), main-loop phase */

extern XIpiPsu IPI_instance; /* sw/isr.c: one instance for all IPIs */

/* Count of control ISRs (uz_SystemTime_ISR_Tic(), the first call in
 * ISR_Control), low word: one 32-bit load cannot tear against the ISR's
 * 64-bit increment, and differences modulo 2^32 stay valid. */
static inline uint32_t xcp_r5_isr_count(void) {
    return (uint32_t)uz_SystemTime_GetInterruptCounter();
}

/* R5 CPU cycle counter (PMU PMCCNTR, 2 ns at 500 MHz): the profile time
 * base and the timeout of XcpTlWaitForTransmitQueueEmpty. Enabled by
 * xcp_r5_init(); it wraps every ~8.6 s, so only differences are used. */
#define XCP_R5_CYC_PER_US (XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ / 1000000u)

static inline uint32_t xcp_r5_cycles(void) {
    uint32_t v;
    __asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(v)::"memory");
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

#if XCP_R5_PROFILE
volatile xcp_r5_prof_t xcp_r5_prof = {.version = 3u, .cpu_hz = XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ};
/* The layout is read by tools/xcp_test/xcp_poll.py (PROF_FMT): keep both in sync. */
_Static_assert(sizeof(xcp_r5_prof_t) == 88u, "xcp_r5_prof_t layout changed");
_Static_assert(__builtin_offsetof(xcp_r5_prof_t, elapsed_cyc) == 32u, "xcp_r5_prof_t layout changed");
static uint32_t gProfLast = 0u;     /* ISR only: cycle count at the previous xcp_r5_event() */
static uint32_t gProfIpiBase = 0u;  /* ISR only: xcp_r5_daq_ipis at the last reset */
#endif

/* A response must fit the RSP ring's largest record. */
#if XCPTL_MAX_CTO_SIZE > OCM_XCP_RSP_MAX_LEN
#error "XCPTL_MAX_CTO_SIZE exceeds OCM_XCP_RSP_MAX_LEN (ocm_xcp_ring.h)"
#endif
#if XCPTL_MAX_DTO_SIZE > OCM_XCP_DAQ_MAX_LEN
#error "XCPTL_MAX_DTO_SIZE exceeds OCM_XCP_DAQ_MAX_LEN (ocm_xcp_ring.h)"
#endif

/* DAQ notification (IPI from the control ISR). The A53 empties the DAQ ring
 * at every IPI. One IPI per control cycle would cost the A53 an interrupt
 * every 25 us at 40 kHz, so the ISR signals only when
 *   XCP_R5_DAQ_NOTIFY_BYTES have been published since the last IPI (sets
 *   the size of the A53's bursts; 4 KB = about three full datagrams), or
 *   the oldest unsignalled data is XCP_R5_DAQ_NOTIFY_US old (sets the
 *   latency at low data rates; counted in whole control periods).
 * Command responses are signalled at once from the main loop. */
#ifndef XCP_R5_DAQ_NOTIFY_BYTES
#define XCP_R5_DAQ_NOTIFY_BYTES 4096u
#endif
#ifndef XCP_R5_DAQ_NOTIFY_US
#define XCP_R5_DAQ_NOTIFY_US 1000u
#endif

/* Control-ISR rate = the base DAQ raster. Same expression main.c uses for
 * Global_Data.av.isr_samplerate_s, so it follows UZ_PWM_FREQUENCY, the trigger
 * source and the ADC-to-ISR ratio automatically. */
#define XCP_R5_ISR_FREQ_HZ                                                     \
    ((uint32_t)((UZ_PWM_FREQUENCY * Interrupt_ISR_freq_factor) /               \
                INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE))

/* Base event period in ns, reported to the master via GET_DAQ_EVENT_INFO
 * (0 = "sporadic or unknown", the sane answer for a misconfigured 0 Hz ISR). */
#define XCP_R5_ISR_PERIOD_NS ((XCP_R5_ISR_FREQ_HZ) > 0u ? (1000000000u / (XCP_R5_ISR_FREQ_HZ)) : 0u)

/* A time in whole control periods: rounded up, at least one. */
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
 *   xcp_r5_queue_lost       DTOs refused because the DAQ ring was full (the
 *                           A53 did not keep up): DAQ loss at the source
 *   xcp_r5_cto_sent         responses and events written to the RSP ring
 *   xcp_r5_cto_dropped      responses refused by the RSP ring (must stay 0:
 *                           a command runs only when its response fits)
 *   xcp_r5_cmd_records      command datagrams executed
 *   xcp_r5_cmd_waits        main-loop passes that left a command waiting
 *                           because the RSP ring was full (latency, not loss)
 *   xcp_r5_cmd_oversize_drop TL frame with dlc > XCPTL_MAX_CTO_SIZE refused
 *                           before XcpCommand (the engine asserts cmdLen <=
 *                           MAX_CTO, i.e. abort() on the control core). The
 *                           A53 gateway filters these too, so non-zero here
 *                           means a gateway bug or a hostile master.
 *   xcp_r5_cmd_ring_bad     corrupt command records skipped (must stay 0)
 *   xcp_r5_daq_ipis         IPIs from the control ISR (DAQ data waiting)
 *   xcp_r5_rsp_ipis         IPIs from the main loop (responses)
 *   xcp_r5_write_denied     DOWNLOAD/SHORT_DOWNLOAD refused by the write
 *                           gate (target outside the data sections, or a
 *                           measurement-only build); the master gets
 *                           ERR_WRITE_PROTECTED
 *   xcp_r5_sweep_gap_max_us worst gap between two xcp_r5_background() calls,
 *                           counted in whole control periods (25 us steps
 *                           at 40 kHz): how long a command may wait for the
 *                           main loop. Includes the commands themselves.
 *                           Reset via debugger. */
volatile int32_t  xcp_r5_init_result = 0x7FFFFFFF; /* "init not run yet" */
volatile uint32_t xcp_r5_cycle_count = 0u;
volatile uint32_t xcp_r5_queue_lost = 0u;
volatile uint32_t xcp_r5_cto_sent = 0u;
volatile uint32_t xcp_r5_cto_dropped = 0u;
volatile uint32_t xcp_r5_cmd_records = 0u;
volatile uint32_t xcp_r5_cmd_waits = 0u;
volatile uint32_t xcp_r5_cmd_oversize_drop = 0u;
volatile uint32_t xcp_r5_cmd_ring_bad = 0u;
volatile uint32_t xcp_r5_daq_ipis = 0u;
volatile uint32_t xcp_r5_rsp_ipis = 0u;
volatile uint32_t xcp_r5_write_denied = 0u;
volatile uint32_t xcp_r5_sweep_gap_max_us = 0u;

/* The rings (this core's local state; shared parts in OCM). gDaq: producer
 * = control ISR. gRsp: producer = main loop. gCmd: consumer = main loop. */
static uz_ocm_ring_t gDaq;
static uz_ocm_ring_t gRsp;
static uz_ocm_ring_t gCmd;
static int gReady = 0;

/* 1 while xcp_r5_event() runs (control ISR): routes queueAcquire() to the
 * DAQ ring. The main loop never sees 1 - it is interrupted for that time. */
static volatile int gInEvent = 0;

/* DAQ notification state (control ISR only). */
static uint32_t gDaqUnsignalled = 0u;    /* bytes published since the last IPI */
static uint32_t gDaqUnsignalledAge = 0u; /* control cycles the oldest of them waits */

/* Engine transport counter: provisional only, the A53 stamps the wire
 * counter in transmission order. */
static uint16_t gCtr = 0u;

static inline void xcp_r5_ipi(void) {
    (void)XIpiPsu_TriggerIpi(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
}

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

/* 8-byte write (XCP_WRITE64, xcplib_r5_cfg.h). A DOWNLOAD runs in the main
 * loop, and a 64-bit store is two 32-bit accesses on the R5, so the control
 * ISR could read a double or int64 with one half new and one half old. With
 * IRQ and FIQ masked the copy completes before the ISR can run (a few
 * instructions). memcpy because neither pointer is guaranteed to be 8-byte
 * aligned: the command buffer is not, and LDRD/STRD would fault on it. */
void xcp_r5_write64(uint8_t *dst, const uint8_t *src) {
    uint32_t cpsr;
    __asm__ volatile("mrs %0, cpsr\n\tcpsid if" : "=r"(cpsr)::"memory");
    memcpy(dst, src, 8u);
    __asm__ volatile("msr cpsr_c, %0" ::"r"(cpsr) : "memory");
}

/* --- transmit queue API (queue.h) on the OCM rings ------------------------ *
 * Replaces queue32.c. The engine uses only queueAcquire/queuePush (DAQ in
 * XcpEvent, events and SERV_TEXT in command context); queuePop/Peek/Release
 * belong to the consumer, which is the A53 now. */
struct Queue {
    uint32_t unused;
};
static struct Queue gQueueHandle;

tQueueHandle queueInit(size_t queue_buffer_size) {
    (void)queue_buffer_size;
    return &gQueueHandle;
}

tQueueHandle queueInitFromMemory(void *queue_memory, size_t queue_memory_size, bool clear_queue,
                                 uint64_t *out_buffer_size) {
    (void)queue_memory;
    (void)queue_memory_size;
    (void)clear_queue;
    if (out_buffer_size != NULL) {
        *out_buffer_size = 0u;
    }
    return NULL; /* not supported: the rings live at fixed OCM addresses */
}

void queueDeinit(tQueueHandle queue_handle) { (void)queue_handle; }

/* The consumer (A53) owns the read position; the producer cannot drop
 * published data. */
void queueClear(tQueueHandle queue_handle) { (void)queue_handle; }

tQueueBuffer queueAcquire(tQueueHandle queue_handle, uint16_t packet_size) {
    (void)queue_handle;
    tQueueBuffer ret = {.handle = NULL, .buffer = NULL, .size = 0u};
    /* Rounded up like queue32 (XCPTL_PACKET_ALIGNMENT 4): the dlc includes
     * the fill, the next message in a datagram starts aligned. */
    const uint16_t size = (uint16_t)((packet_size + 3u) & ~3u);
    if (gInEvent) {
        uint8_t *p = uz_ocm_ring_reserve(&gDaq, size, 0u);
        if (p == NULL) {
            xcp_r5_queue_lost++;
            return ret;
        }
        ret.handle = &gDaq;
        ret.buffer = p;
        ret.size = size;
    } else {
        uint8_t *p = uz_ocm_ring_reserve(&gRsp, size, 0u);
        if (p == NULL) {
            xcp_r5_cto_dropped++;
            return ret;
        }
        ret.handle = &gRsp;
        ret.buffer = p;
        ret.size = size;
    }
    return ret;
}

/* DAQ records are published by xcp_r5_event() once per control cycle (one
 * cache clean for all DTOs of the cycle); an event from command context
 * goes out at once. */
void queuePush(tQueueHandle queue_handle, const tQueueBuffer *queue_buffer, bool priority) {
    (void)queue_handle;
    (void)priority;
    if (queue_buffer->handle == &gRsp) {
        (void)uz_ocm_ring_publish(&gRsp);
        xcp_r5_cto_sent++;
        xcp_r5_ipi();
        xcp_r5_rsp_ipis++;
    }
}

/* DAQ bytes in the ring as far as the R5 knows (the A53's read position is
 * fetched only when space runs short, so this is an upper bound). */
uint32_t queueLevel(tQueueHandle queue_handle, uint32_t *queue_max_level) {
    (void)queue_handle;
    if (queue_max_level != NULL) {
        *queue_max_level = gDaq.size;
    }
    return gReady ? uz_ocm_ring_level(&gDaq) : 0u;
}

/* --- engine-facing transport API ----------------------------------------- */

uint16_t XcpTlGetCtr(void) { return gCtr++; }

/* Command response (from XcpCommand, main loop): one record in the RSP
 * ring, published and signalled at once. Room for it was checked before the
 * command ran (xcp_r5_background). */
void XcpTlSendCrm(const uint8_t *data, uint8_t size) {
    uint8_t *p = uz_ocm_ring_reserve(&gRsp, size, gCtr++);
    if (p == NULL) {
        xcp_r5_cto_dropped++;
        return;
    }
    memcpy(p, data, size);
    (void)uz_ocm_ring_publish(&gRsp);
    xcp_r5_cto_sent++;
    xcp_r5_ipi();
    xcp_r5_rsp_ipis++;
}

/* Called by the engine before the response to a DAQ stop or DISCONNECT, so
 * the master gets the last DTOs before the response. Everything the ISR
 * reserved is published at the end of its cycle; signal it and wait until
 * the A53 has taken it (it empties the ring at every IPI), bounded by the
 * timeout and by 20 ms (main loop: commands wait meanwhile). */
bool XcpTlWaitForTransmitQueueEmpty(uint16_t timeout_ms) {
    if (!gReady) {
        return true;
    }
    uint32_t ms = timeout_ms < 20u ? timeout_ms : 20u;
    const uint32_t t0 = xcp_r5_cycles();
    xcp_r5_ipi();
    xcp_r5_rsp_ipis++;
    while (!uz_ocm_ring_drained(&gDaq)) {
        if ((xcp_r5_cycles() - t0) >= ms * 1000u * XCP_R5_CYC_PER_US) {
            return false;
        }
    }
    return true;
}

/* --- R5 driving API ------------------------------------------------------- */

/* Sample DAQ. Call from ISR_Control. XcpEvent writes the DTOs of every
 * running DAQ list on the event straight into the DAQ ring; then the cycle's
 * records are cleaned from the cache and published, and the A53 is signalled
 * when XCP_R5_DAQ_NOTIFY_BYTES or XCP_R5_DAQ_NOTIFY_US are reached. An event
 * with no running DAQ list costs only the isStarted()/isDaqRunning() checks,
 * so the unused rasters are free. */
void xcp_r5_event(void) {
    if (!gReady) {
        return; /* init failed or not run: engine disabled */
    }
    const uint32_t c0 = xcp_r5_cycles();
#if XCP_R5_PROFILE
    if (xcp_r5_prof.reset != 0u) {
        xcp_r5_prof.reset = 0u;
        xcp_r5_prof.event_calls = 0u;
        xcp_r5_prof.event_cyc_max = 0u;
        xcp_r5_prof.publish_cyc_max = 0u;
        xcp_r5_prof.ipis = 0u;
        xcp_r5_prof.commands = 0u;
        xcp_r5_prof.elapsed_cyc = 0u;
        xcp_r5_prof.event_cyc = 0u;
        xcp_r5_prof.sample_cyc = 0u;
        xcp_r5_prof.publish_cyc = 0u;
        xcp_r5_prof.daq_bytes = 0u;
        xcp_r5_prof.isr_ns_all = 0u;
        xcp_r5_prof.cmd_cyc = 0u;
        gProfLast = c0;
        gProfIpiBase = xcp_r5_daq_ipis;
    }
#endif
    xcp_r5_cycle_count++;
    /* Every sample of this control cycle carries the cycle's start: the timer
     * value uz_SystemTime_ISR_Tic() latched at ISR entry (10 ns ticks, the DAQ
     * clock of xcplib_r5_cfg.h), not the time this call happens to run. */
    const uint64_t cycle_start = uz_SystemTime_GetIsrStartTicks();
#if UZ_ISR_DIAG
    const uint32_t diag_c0 = uz_isr_diag_cycles();
#endif
    gInEvent = 1;
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
    gInEvent = 0;
#if UZ_ISR_DIAG
    uz_isr_diag_xcp_base = diag_c1 - diag_c0;
    uz_isr_diag_xcp_slices = uz_isr_diag_cycles() - diag_c1;
#endif

    /* Publish the cycle's DTOs and signal the A53 when it is worth it. */
    const uint32_t c1 = xcp_r5_cycles();
    const uint32_t n = uz_ocm_ring_publish(&gDaq);
    const uint32_t c2 = xcp_r5_cycles();
    if (n != 0u) {
        gDaqUnsignalled += n;
    }
    if (gDaqUnsignalled != 0u) {
        gDaqUnsignalledAge++;
        if (gDaqUnsignalled >= XCP_R5_DAQ_NOTIFY_BYTES ||
            gDaqUnsignalledAge >= XCP_R5_US_TO_PERIODS(XCP_R5_DAQ_NOTIFY_US)) {
            xcp_r5_ipi();
            xcp_r5_daq_ipis++;
            gDaqUnsignalled = 0u;
            gDaqUnsignalledAge = 0u;
        }
    }
#if XCP_R5_PROFILE
    {
        const uint32_t c3 = xcp_r5_cycles();
        const uint32_t d = c3 - c0;
        xcp_r5_prof.event_calls++;
        xcp_r5_prof.event_cyc += d;
        if (d > xcp_r5_prof.event_cyc_max) {
            xcp_r5_prof.event_cyc_max = d;
        }
        xcp_r5_prof.sample_cyc += c1 - c0;
        if (n != 0u) {
            const uint32_t p = c2 - c1;
            xcp_r5_prof.publish_cyc += p;
            xcp_r5_prof.daq_bytes += n;
            if (p > xcp_r5_prof.publish_cyc_max) {
                xcp_r5_prof.publish_cyc_max = p;
            }
        }
        xcp_r5_prof.ipis = xcp_r5_daq_ipis - gProfIpiBase;
        xcp_r5_prof.elapsed_cyc += (uint64_t)(c3 - gProfLast); /* differences: no 8.6 s wrap */
        gProfLast = c3;
        /* Run time of the previous ISR_Control (uz_SystemTime Tic/Toc). */
        xcp_r5_prof.isr_ns_all += (uint64_t)(uz_SystemTime_GetIsrExectionTimeInUs() * 1000.0f);
    }
#else
    (void)c0;
    (void)c1;
    (void)c2;
#endif
}

/* Execute commands. Call from the MAIN LOOP every iteration. A command
 * datagram stays in the CMD ring (its space is not released) until all of
 * its frames ran; a frame runs only when the RSP ring has room for two
 * maximal responses, otherwise the datagram waits for the next pass. */
void xcp_r5_background(void) {
    static uint32_t last_call_isr = 0u;
    static int first_call = 1;
    /* Datagram in progress: its bytes stay valid until released. */
    static const uint8_t *rec = NULL;
    static uint16_t rec_len = 0u;
    static uint16_t rec_off = 0u;

    if (!gReady) {
        return; /* init failed or not run: engine disabled */
    }
    const uint32_t now = xcp_r5_isr_count();
    if (first_call) {
        first_call = 0; /* boot-to-first-call gap is not a loop-health signal */
    } else {
        const uint32_t gap_us = (uint32_t)(now - last_call_isr) * (XCP_R5_ISR_PERIOD_NS / 1000u);
        if (gap_us > xcp_r5_sweep_gap_max_us) {
            xcp_r5_sweep_gap_max_us = gap_us;
        }
    }
    if (now != last_call_isr) {
        /* The A53 rewrites its counters at OCM_XCP_GW_DIAG_BASE at every
         * IPI. The master reads them through this core (SHORT_UPLOAD, or DAQ
         * in the control ISR), which would keep serving its cached copy:
         * drop that copy once per control period. Never written here, so
         * invalidating loses nothing. */
        uz_ocm_ring_inval((const volatile void *)(uintptr_t)OCM_XCP_GW_DIAG_BASE,
                          8u + 4u * OCM_XCP_GW_DIAG_COUNT);
    }
    last_call_isr = now;

    if (rec == NULL && uz_ocm_ring_poll(&gCmd) == 0u) {
        return; /* nothing new: one cache line was read */
    }
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_XCP_COMMANDS);
#if XCP_R5_PROFILE
    const uint32_t c0 = xcp_r5_cycles();
#endif
    for (;;) {
        if (rec == NULL) {
            uint16_t aux;
            rec = uz_ocm_ring_next(&gCmd, &rec_len, &aux);
            rec_off = 0u;
            if (rec == NULL) {
                break; /* everything up to the last poll is done */
            }
            rec += UZ_OCM_RING_HDR; /* the datagram */
        }
        /* One record = one UDP datagram, which may carry SEVERAL concatenated
         * TL frames ([dlc][ctr][packet])+ (e.g. CANape block-mode bursts). */
        int waiting = 0;
        while ((uint16_t)(rec_off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE) <= rec_len) {
            const uint16_t dlc = (uint16_t)(rec[rec_off] | ((uint16_t)rec[rec_off + 1] << 8));
            if (dlc == 0u || (uint16_t)(rec_off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc) > rec_len) {
                rec_off = rec_len; /* padding or malformed frame: stop parsing this datagram */
                break;
            }
            if (!uz_ocm_ring_fits(&gRsp, 2u * (XCPTL_TRANSPORT_LAYER_HEADER_SIZE + XCPTL_MAX_CTO_SIZE))) {
                waiting = 1; /* the A53 has not taken the responses yet */
                break;
            }
            if (dlc > XCPTL_MAX_CTO_SIZE) {
                /* Transport-layer contract (upstream xcpethtl.c does the
                 * same): the engine asserts cmdLen <= XCPTL_MAX_CTO_SIZE
                 * and a bigger frame would abort() the control core. */
                xcp_r5_cmd_oversize_drop++;
            } else {
                XcpCommand((const uint32_t *)(const void *)(rec + rec_off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE),
                           (uint8_t)dlc);
#if XCP_R5_PROFILE
                xcp_r5_prof.commands++;
#endif
            }
            rec_off = (uint16_t)(rec_off + XCPTL_TRANSPORT_LAYER_HEADER_SIZE + dlc);
        }
        if (waiting) {
            xcp_r5_cmd_waits++;
            break; /* resume this datagram in the next pass */
        }
        rec = NULL;
        xcp_r5_cmd_records++;
        uz_ocm_ring_release(&gCmd); /* the A53 may reuse the datagram's space */
    }
    xcp_r5_cmd_ring_bad = gCmd.bad;
#if XCP_R5_PROFILE
    xcp_r5_prof.cmd_cyc += (uint64_t)(xcp_r5_cycles() - c0);
#endif
    UZ_ISR_DIAG_MAIN_PHASE(UZ_ISR_DIAG_MAIN_OTHER);
}

/* One-time init. Base addr 0 => XCP address == pointer => arbitrary R5
 * addressing (the point of Option Z). Returns 0 on success. Runs before the
 * control ISR is enabled. */
int xcp_r5_init(const char *name, const char *epk) {
    xcp_r5_cycles_enable();
    gCtr = 0u;
    ocm_xcp_ring_setup(&gDaq, &gRsp, &gCmd);
    uz_ocm_ring_producer_init(&gDaq);
    uz_ocm_ring_producer_init(&gRsp);
    uz_ocm_ring_consumer_init(&gCmd);
    ApplXcpSetBaseAddr((const uint8_t *)0);
    ApplXcpRegisterCheckCallback(xcp_r5_check_memory);
    if (!XcpInit(name, epk, XCP_MODE_LOCAL)) {
        xcp_r5_init_result = -2;
        return -2;
    }
    XcpStart(queueInit(0u), false);
    xcp_r5_daq_event = (uint16_t)XcpCreateEvent("DAQ_R5", XCP_R5_ISR_PERIOD_NS, 0u);
    if (xcp_r5_daq_event == 0xFFFFu) { /* XCP_UNDEFINED_EVENT_ID */
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
            xcp_r5_init_result = -4;
            return -4;
        }
    }
#if XCP_R5_PROFILE
    gProfLast = xcp_r5_cycles();
#endif
    xcp_r5_init_result = 0;
    gReady = 1;
    return 0;
}
