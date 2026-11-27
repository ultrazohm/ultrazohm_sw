/*----------------------------------------------------------------------------
| xcp_gateway_a53.c
|   Option Z — A53 (FreeRTOS/lwIP) Ethernet gateway for the R5 XCPlite engine.
|   The A53 is a dumb pipe: it moves XCP-on-UDP messages between CANape and
|   the OCM rings (shared/ocm_xcp_ring.h); the XCP slave logic lives on the
|   R5 (arbitrary addressing).
|
|   Data path:
|     CANape --UDP--> rx_task --CMD ring--> R5 main loop: XcpCommand
|     R5 XcpCommand --RSP ring--+
|     R5 XcpEvent ----DAQ ring--+--> IPI ISR --queues--> tx_task --UDP--> CANape
|
|   Every ring has one producer and one consumer, and every record is written
|   once and read once: a command or a response can neither be lost nor
|   executed twice, and DAQ data waits in the ring until it is read (the R5
|   counts what does not fit, xcp_r5_queue_lost). This replaces the seqlock,
|   CTO mailbox, command generations and chain acknowledge of the former
|   XCP_OUT/XCP_IN exchange (ocm_xcp_fifo.c, hedrive T8).
|
|   Rules kept from the hedrive hardware campaign
|   (XCP_BOTTLENECK_ANALYSIS.md):
|   - F1: the IPI ISR touches ONLY OCM + FreeRTOS queues (…FromISR). Sockets
|     live in the tasks; never block/delay/print in ISR context.
|   - T1: responses take a dedicated queue; they jump the DAQ backlog and
|     are never tail-dropped with it (a lost/late response kills the session).
|   - T3: the transport-layer counter (CTR) is owned HERE, stamped at
|     transmission time in transmission order — reordering (response bypass)
|     and tail-drops are invisible to the master.
|   - B1: messages are batched into one UDP datagram per sendto() (XCP-on-UDP
|     allows several TL messages per datagram) — socket calls are the
|     throughput limiter, not bytes.
|   - B5 (final form): the DAQ queue is a deep burst absorber with tail-drop
|     on overflow; no purge (a purge once wiped a parked response).
|
|   Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"   /* sys_thread_new */
#include "xcp_gateway_a53.h"
#include "ocm_xcp_ring.h"
#include <string.h>
#include <stdint.h>
#if XCP_GW_PROFILE
#include "xparameters.h" /* XPAR_CPU_CORTEXA53_0_TIMESTAMP_CLK_FREQ */
#endif
#include "xil_printf.h"
#include "xlwipconfig.h" /* XLWIP_CONFIG_N_TX_DESC */

#define XCP_TL_HEADER_LEN    4    /* [dlc:u16][ctr:u16]                          */
#define XCP_GW_CC_CONNECT    0xFFu /* command codes the gateway reports */
#define XCP_GW_CC_DISCONNECT 0xFEu
/* Largest XCP command the R5 engine accepts (XCPTL_MAX_CTO_SIZE, set by
 * xcplib_r5_cfg.h). The engine asserts on anything bigger, so a datagram
 * carrying such a frame is refused here already (see xcp_gw_rx_frames_valid). */
#define XCP_GW_MAX_CTO_SIZE  248u

/* TX batching: pack TL messages into one UDP datagram (several XCP messages
 * per datagram are standard XCP-on-Ethernet; XCPlite's own PC transport does
 * the same). 1400 stays below the 1472 that a 1500-byte MTU allows without
 * IP fragmentation. The IPI ISR packs DAQ messages into segments of this
 * size already, so a queued DAQ item is a ready datagram. The R5 engine's
 * XCPTL_MAX_SEGMENT_SIZE (xcplib_r5_cfg.h) carries the same value.
 * Why not 1472 (measured 2026-11-27, 40 kHz, one stress list): the A53
 * sends ~60-70k datagrams/s at most, so one datagram per control cycle
 * passes and two do not, and with MAX_DTO 1024 the segment size decides
 * whether a full DTO and the rest of its cycle share one. 1400: clean up to
 * 1350 B/cycle (432 Mbit/s). 1472: clean up to 1450 B/cycle (464 Mbit/s),
 * but lwip_sendto took 13 us per datagram from 1464 bytes on instead of
 * 5.9 us up to 1456 bytes (cause not found), so every full datagram costs
 * the A53 twice as much: 7 % idle instead of 34 %. */
#define XCP_GW_BATCH_BUF_SIZE 1400
#define XCP_GW_FRAME_MAX      XCP_GW_BATCH_BUF_SIZE
#if (XCP_TL_HEADER_LEN + OCM_XCP_DAQ_MAX_LEN) > XCP_GW_FRAME_MAX
#error "a datagram must hold the largest DTO"
#endif
#if OCM_XCP_CMD_MAX_LEN < XCP_GW_FRAME_MAX
#error "the CMD ring must hold a whole received datagram"
#endif

/* DAQ queue: deep on purpose — it is the burst absorber between the OCM
 * drain in the IPI ISR and the UDP send rate, and measurement gaps hurt more
 * than backlog latency. The OCM DAQ ring itself covers only ~3 ms at
 * 900 B/cycle (40 kHz), this queue covers seconds: hedrive's rig saw ~2 s
 * host receive pauses every few minutes that a 140 ms queue could not
 * absorb. Items are fixed-size (XCP_GW_FRAME_MAX): 65536 x ~1.4 KB ≈ 92 MB
 * of the 200 MB FreeRTOS heap, ≈ 2 s at 320 Mbit/s. The queue runs empty in
 * steady state, so normal latency is unaffected. NOTE: UDP has no
 * backpressure — this queue covers ECU-side stalls (lwIP pbuf/ARP, task
 * starvation); PC-side receive pauses must be absorbed by the receiver's
 * socket buffer (xcp_poll.py sets 32 MB).
 * Overflow policy: tail-drop + count, never purge, never block from the ISR. */
#define XCP_GW_TXQ_DEPTH     65536
/* Dedicated queue for responses and events (RES/ERR/EV/SERV): they must never
 * wait behind — or be dropped with — the DAQ backlog (hedrive T1). */
#define XCP_GW_CTOQ_DEPTH    16

/* Bound the IPI-ISR time: DAQ bytes taken from the ring per interrupt. The
 * R5 signals every XCP_R5_DAQ_NOTIFY_BYTES (4 KB), so the cap only bites
 * when the A53 fell behind; the rest goes with the next IPI (at the latest
 * 1 ms later) and the ring keeps it meanwhile. */
#define XCP_GW_DRAIN_MAX_BYTES (32u * 1024u)

/* Transmit buffers: one per datagram, from a ring longer than the GEM's
 * TX descriptor ring. lwip_sendto() does not copy the payload
 * (LWIP_NETIF_TX_SINGLE_PBUF 0: netbuf_ref), and the GEM driver points its
 * DMA descriptor at it (emacps_sgsend). The DMA reads the buffer when the
 * frame reaches the head of the TX ring, which can be long after
 * lwip_sendto() returned, for example while the link partner pauses the
 * GEM. A single reused buffer then sent the content of a later datagram in
 * all queued frames: repeated datagrams and lost ones on the wire, with
 * valid checksums (TX checksum offload). CANape reported "invalid counter",
 * backward timestamps, and a command timeout when a response was
 * overwritten (bench 2026-11-23). A queued datagram holds at least one TX
 * descriptor until its transmission completed, so with more buffers than
 * descriptors a buffer comes round again only when its datagram is gone. */
#ifndef XLWIP_CONFIG_N_TX_DESC
#error "xlwipconfig.h must define XLWIP_CONFIG_N_TX_DESC"
#endif
#define XCP_GW_TX_BUFS (XLWIP_CONFIG_N_TX_DESC + 1)

/* Bounded send retry (hedrive "bounded sends", UDP flavor): lwip_sendto()
 * fails transiently under burst load (pbuf/TX-BD exhaustion at 40k
 * datagrams/s — every wire-loss frame of the first 320 Mbit/s hardware run
 * traced to exactly these failures). The batch is already CTR-stamped, so
 * dropping it tears a gap into the wire counter; the GEM TX ring drains by
 * hardware in <1 ms, so waiting one tick (10 ms @ 100 Hz) converts the loss
 * into latency the deep queue absorbs. Bounded so a persistent failure
 * (master gone, no route) cannot wedge the task: worst ~50 ms, then drop. */
#define XCP_GW_SEND_RETRY_MAX 5

/* One queued item: TL messages ([dlc][ctr][packet])+ for one datagram. */
typedef struct {
    uint16_t len;
    uint8_t  data[XCP_GW_FRAME_MAX];
} xcp_gw_frame_t;

static QueueHandle_t gTxQueue    = NULL;     /* R5 -> CANape (DAQ segments)     */
static QueueHandle_t gTxCtoQueue = NULL;     /* R5 -> CANape (responses/events) */
/* "Frames queued" signal from the IPI ISR to the tx task. A binary semaphore
 * is enough: the task drains both queues completely after every take, and a
 * give that arrives while it is busy just makes the next take return at
 * once. Without it the task could only block on the DAQ queue, so a command
 * response arriving on an idle link waited out that timeout. */
static SemaphoreHandle_t gTxSignal = NULL;
static int           gSock      = -1;

/* The rings, A53 side (consumer of DAQ and RSP, producer of CMD). */
static uz_ocm_ring_t gDaq;
static uz_ocm_ring_t gRsp;
static uz_ocm_ring_t gCmd;

/* The IPI ISR is registered by initialize_ipi_runtime() long before this
 * gateway is initialised (network-up/DHCP). Guard the ISR path until init
 * completed. */
static volatile int gGwReady = 0;

static struct sockaddr_in gMaster;           /* last master (CANape) endpoint   */
static volatile int       gMasterValid = 0;
static volatile uint32_t  gMasterGen = 0;    /* bumped on endpoint change       */
static volatile TickType_t gMasterLastRxTick = 0; /* last valid datagram from the master */

/* Diagnostics (inspect via debugger; mirrored to the master, see below):
 *   xcp_gw_ring_bad            DAQ/RSP ring resynchronisations after corrupt
 *                              data (must stay 0)
 *   xcp_gw_daq_level_max       fullest the DAQ ring was at a drain, bytes (of
 *                              OCM_XCP_DAQ_DATA_LEN): how close the R5 came
 *                              to xcp_r5_queue_lost
 *   xcp_gw_cmd_dropped         command datagram dropped, CMD ring full (the
 *                              R5 main loop does not take commands; the
 *                              master retries)
 *   xcp_gw_drain_capped        IPIs that left DAQ data in the ring because of
 *                              XCP_GW_DRAIN_MAX_BYTES (latency, not loss)
 *   xcp_gw_txq_dropped         DAQ queue full -> segment tail-dropped
 *   xcp_gw_ctoq_dropped        CTO queue full -> response dropped (must stay 0)
 *   xcp_gw_cmd_records         command datagrams handed to the R5
 *   xcp_gw_daq_records         DTOs taken from the DAQ ring
 *   xcp_gw_tx_malformed_drop   segment failed the TL-frame walk on TX (must stay 0)
 *   xcp_gw_rx_malformed_drop   datagram failed the TL-frame walk on RX (bad
 *                              dlc chain or a frame > XCP_GW_MAX_CTO_SIZE) and
 *                              was not forwarded to the R5. CANape never sends
 *                              these; non-zero = port scanner / broken client.
 *   xcp_gw_sendto_err          transient lwip_sendto() failures (pbuf/TX-BD
 *                              exhaustion under burst load). Retried, so err
 *                              alone is pressure, not loss.
 *   xcp_gw_sendto_drop         batch still failing after the bounded retries —
 *                              the batch was already CTR-stamped, so each one
 *                              is a wire counter gap and the ONLY ECU-side
 *                              source of them. Must stay 0.
 *   xcp_gw_ipi_count           IPIs handled (A53-side liveness)
 *   xcp_gw_master_lost         sessions closed by the gateway because the
 *                              master became unreachable (see
 *                              xcp_gateway_a53.h, master supervision)
 *   All of the above are mirrored every IPI to fixed OCM addresses
 *   (ocm_xcp_ring.h, OCM_XCP_GW_DIAG_ADDR) together with the DAQ queue fill
 *   level, so CANape (uz.A2L xcp_gw_*) and xcp_poll.py --stress can read
 *   them over XCP. */
volatile uint32_t xcp_gw_ring_bad = 0;
volatile uint32_t xcp_gw_daq_level_max = 0;
volatile uint32_t xcp_gw_cmd_dropped = 0;
volatile uint32_t xcp_gw_drain_capped = 0;
volatile uint32_t xcp_gw_txq_dropped = 0;
volatile uint32_t xcp_gw_ctoq_dropped = 0;
volatile uint32_t xcp_gw_cmd_records = 0;
volatile uint32_t xcp_gw_daq_records = 0;
volatile uint32_t xcp_gw_tx_malformed_drop = 0;
volatile uint32_t xcp_gw_rx_malformed_drop = 0;
volatile uint32_t xcp_gw_ipi_count = 0;
volatile uint32_t xcp_gw_sendto_err = 0;
volatile uint32_t xcp_gw_sendto_drop = 0;
volatile uint32_t xcp_gw_master_lost = 0;

#if XCP_GW_PROFILE
/* A53 time profile (XCP_GW_PROFILE, xcp_gateway_a53.h). Time base: the system
 * counter CNTPCT_EL0 (33.3 MHz here, 30 ns), the same in every task and ISR.
 * Sums in counter ticks with one writer each - 64-bit loads and stores are
 * single-copy atomic on AArch64, so the IPI ISR may mirror what a task
 * writes. Converted to microseconds only for the mirror. */
#define XCP_GW_PROF_HZ ((uint64_t)XPAR_CPU_CORTEXA53_0_TIMESTAMP_CLK_FREQ)
/* us = ticks * 1e6 / HZ in 32.32 fixed point: no division per IPI. */
#define XCP_GW_PROF_US_PER_TICK_Q32 ((uint64_t)((1000000ull << 32) / XCP_GW_PROF_HZ))
/* Idle probe: a gap of more than ~1 us between two counter reads means the
 * probe was preempted; such a gap is not idle time. */
#define XCP_GW_PROF_IDLE_GAP_TICKS (XCP_GW_PROF_HZ / 1000000u + 1u)

static inline uint64_t xcp_gw_ticks(void) {
    uint64_t v;
    __asm volatile("isb\n\tmrs %0, cntpct_el0" : "=r"(v)::"memory");
    return v;
}

static inline uint32_t xcp_gw_ticks_to_us(uint64_t t) {
    return (uint32_t)(((__uint128_t)t * XCP_GW_PROF_US_PER_TICK_Q32) >> 32);
}

/* Maximum per one-second window; the mirror shows the last full window (a
 * running maximum could only grow, and the master cannot reset it). */
typedef struct {
    uint64_t win_start;
    uint64_t cur;
    volatile uint64_t last;
} xcp_gw_prof_max_t;

static void xcp_gw_prof_max_update(xcp_gw_prof_max_t *m, uint64_t now, uint64_t d) {
    if ((now - m->win_start) >= XCP_GW_PROF_HZ) {
        m->last = m->cur;
        m->cur = 0u;
        m->win_start = now;
    }
    if (d > m->cur) {
        m->cur = d;
    }
}

static volatile uint64_t gProfIdle = 0u;     /* writer: idle probe task */
static volatile uint64_t gProfIpi = 0u;      /* writer: IPI ISR         */
static volatile uint64_t gProfChain = 0u;    /* writer: IPI ISR         */
static volatile uint64_t gProfEnq = 0u;      /* writer: IPI ISR         */
static volatile uint32_t gProfRecords = 0u;  /* writer: IPI ISR         */
static xcp_gw_prof_max_t gProfIpiMax;        /* writer: IPI ISR         */
static volatile uint64_t gProfTx = 0u;       /* writer: tx task         */
static volatile uint64_t gProfSendto = 0u;   /* writer: tx task         */
static volatile uint32_t gProfSendtoN = 0u;  /* writer: tx task         */
static volatile uint64_t gProfTxBytes = 0u;  /* writer: tx task         */
static xcp_gw_prof_max_t gProfSendtoMax;     /* writer: tx task         */

/* Idle probe at the idle priority (the FreeRTOS idle task yields to it,
 * configIDLE_SHOULD_YIELD): it runs only when no task and no interrupt wants
 * the CPU and sums the time between back-to-back counter reads. */
static void xcp_gw_idle_probe_task(void *arg) {
    (void)arg;
    uint64_t last = xcp_gw_ticks();
    for (;;) {
        const uint64_t now = xcp_gw_ticks();
        const uint64_t d = now - last;
        if (d <= XCP_GW_PROF_IDLE_GAP_TICKS) {
            gProfIdle += d;
        }
        last = now;
    }
}
#endif

/*--------------------------------------------------------------------------
 * IPI ISR: responses and DAQ from the rings into the queues.
 * All buffers static: this runs only in the (non-reentrant) IPI ISR, and a
 * segment is too big for an ISR stack frame.
 *------------------------------------------------------------------------*/
static xcp_gw_frame_t gIsrFrame; /* response being queued */
static xcp_gw_frame_t gIsrSeg;   /* DAQ segment being packed */

/* Copy one ring record (header + payload = one TL message) to dst. */
static inline uint16_t xcp_gw_copy_msg(uint8_t *dst, const uint8_t *rec, uint16_t len) {
    const uint16_t n = (uint16_t)(XCP_TL_HEADER_LEN + len);
    memcpy(dst, rec, n);
    return n;
}

static int xcp_gw_queue_seg(BaseType_t *woken) {
    int enqueued = 0;
    if (gIsrSeg.len != 0u && gMasterValid) { /* no consumer yet: drop */
        if (xQueueSendToBackFromISR(gTxQueue, &gIsrSeg, woken) == pdTRUE) {
            enqueued = 1;
        } else {
            /* DAQ queue full: the UDP drain has stalled for longer than the
             * queue depth covers. Tail-drop and count. Never block, delay or
             * print here — ISR context (hedrive F1). */
            xcp_gw_txq_dropped++;
        }
#if XCP_GW_PROFILE
        gProfRecords++;
#endif
    }
    gIsrSeg.len = 0u;
    return enqueued;
}

/* Responses first, every one as its own queue item (the tx task batches). */
static int xcp_gw_drain_rsp(BaseType_t *woken) {
    int enqueued = 0;
    if (uz_ocm_ring_poll(&gRsp) == 0u) {
        return 0;
    }
    const uint8_t *rec;
    uint16_t len, aux;
    while ((rec = uz_ocm_ring_next(&gRsp, &len, &aux)) != NULL) {
        gIsrFrame.len = xcp_gw_copy_msg(gIsrFrame.data, rec, len);
        if (xQueueSendToBackFromISR(gTxCtoQueue, &gIsrFrame, woken) == pdTRUE) {
            enqueued = 1;
        } else {
            xcp_gw_ctoq_dropped++;
        }
    }
    uz_ocm_ring_release(&gRsp);
    return enqueued;
}

/* DAQ: pack consecutive DTOs into datagram-sized segments. */
static int xcp_gw_drain_daq(BaseType_t *woken) {
    int enqueued = 0;
    const uint32_t avail = uz_ocm_ring_poll(&gDaq);
    if (avail == 0u) {
        return 0;
    }
    if (avail > xcp_gw_daq_level_max) {
        xcp_gw_daq_level_max = avail;
    }
#if XCP_GW_PROFILE
    const uint64_t tc0 = xcp_gw_ticks();
    uint64_t tenq = 0u;
#endif
    uint32_t taken = 0u;
    const uint8_t *rec;
    uint16_t len, aux;
    gIsrSeg.len = 0u;
    while (taken < XCP_GW_DRAIN_MAX_BYTES && (rec = uz_ocm_ring_next(&gDaq, &len, &aux)) != NULL) {
        const uint16_t n = (uint16_t)(XCP_TL_HEADER_LEN + len);
        if ((uint32_t)gIsrSeg.len + n > XCP_GW_FRAME_MAX) {
#if XCP_GW_PROFILE
            const uint64_t te0 = xcp_gw_ticks();
#endif
            enqueued |= xcp_gw_queue_seg(woken);
#if XCP_GW_PROFILE
            tenq += xcp_gw_ticks() - te0;
#endif
        }
        gIsrSeg.len = (uint16_t)(gIsrSeg.len + xcp_gw_copy_msg(&gIsrSeg.data[gIsrSeg.len], rec, len));
        taken += (uint32_t)UZ_OCM_RING_HDR + UZ_OCM_RING_PAD4(len);
        xcp_gw_daq_records++;
    }
    if (taken >= XCP_GW_DRAIN_MAX_BYTES && gDaq.r != gDaq.w_seen) {
        xcp_gw_drain_capped++;
    }
#if XCP_GW_PROFILE
    const uint64_t te0 = xcp_gw_ticks();
#endif
    enqueued |= xcp_gw_queue_seg(woken); /* the last, partly filled segment */
    uz_ocm_ring_release(&gDaq);
#if XCP_GW_PROFILE
    const uint64_t te1 = xcp_gw_ticks();
    tenq += te1 - te0;
    gProfEnq += tenq;
    gProfChain += (te1 - tc0) - tenq;
#endif
    return enqueued;
}

/* Mirror the gateway counters to their fixed OCM addresses (ocm_xcp_ring.h)
 * so the XCP master can read them by absolute address. */
static void xcp_gw_publish_diag(void) {
    volatile uint32_t *const d = (volatile uint32_t *)(uintptr_t)OCM_XCP_GW_DIAG_ADDR;
    xcp_gw_ring_bad = gDaq.bad + gRsp.bad;
    d[OCM_XCP_DIAG_GW_RING_BAD] = xcp_gw_ring_bad;
    d[OCM_XCP_DIAG_GW_DAQ_LEVEL_MAX] = xcp_gw_daq_level_max;
    d[OCM_XCP_DIAG_GW_CMD_DROPPED] = xcp_gw_cmd_dropped;
    d[OCM_XCP_DIAG_GW_DRAIN_CAPPED] = xcp_gw_drain_capped;
    d[OCM_XCP_DIAG_GW_TXQ_DROPPED] = xcp_gw_txq_dropped;
    d[OCM_XCP_DIAG_GW_CTOQ_DROPPED] = xcp_gw_ctoq_dropped;
    d[OCM_XCP_DIAG_GW_CMD_RECORDS] = xcp_gw_cmd_records;
    d[OCM_XCP_DIAG_GW_DAQ_RECORDS] = xcp_gw_daq_records;
    d[OCM_XCP_DIAG_GW_TX_MALFORMED_DROP] = xcp_gw_tx_malformed_drop;
    d[OCM_XCP_DIAG_GW_RX_MALFORMED_DROP] = xcp_gw_rx_malformed_drop;
    d[OCM_XCP_DIAG_GW_SENDTO_ERR] = xcp_gw_sendto_err;
    d[OCM_XCP_DIAG_GW_SENDTO_DROP] = xcp_gw_sendto_drop;
    d[OCM_XCP_DIAG_GW_IPI_COUNT] = xcp_gw_ipi_count;
    d[OCM_XCP_DIAG_GW_TXQ_LEVEL] = (uint32_t)uxQueueMessagesWaitingFromISR(gTxQueue);
    d[OCM_XCP_DIAG_GW_MASTER_LOST] = xcp_gw_master_lost;
#if XCP_GW_PROFILE
    d[OCM_XCP_DIAG_GW_PROF_NOW_US] = xcp_gw_ticks_to_us(xcp_gw_ticks());
    d[OCM_XCP_DIAG_GW_PROF_IDLE_US] = xcp_gw_ticks_to_us(gProfIdle);
    d[OCM_XCP_DIAG_GW_PROF_IPI_US] = xcp_gw_ticks_to_us(gProfIpi);
    d[OCM_XCP_DIAG_GW_PROF_IPI_MAX_US] = xcp_gw_ticks_to_us(gProfIpiMax.last);
    d[OCM_XCP_DIAG_GW_PROF_CHAIN_US] = xcp_gw_ticks_to_us(gProfChain);
    d[OCM_XCP_DIAG_GW_PROF_ENQ_US] = xcp_gw_ticks_to_us(gProfEnq);
    d[OCM_XCP_DIAG_GW_PROF_RECORDS] = gProfRecords;
    d[OCM_XCP_DIAG_GW_PROF_TX_US] = xcp_gw_ticks_to_us(gProfTx);
    d[OCM_XCP_DIAG_GW_PROF_SENDTO_US] = xcp_gw_ticks_to_us(gProfSendto);
    d[OCM_XCP_DIAG_GW_PROF_SENDTO_N] = gProfSendtoN;
    d[OCM_XCP_DIAG_GW_PROF_TX_KB] = (uint32_t)(gProfTxBytes >> 10);
    d[OCM_XCP_DIAG_GW_PROF_SENDTO_MAX_US] = xcp_gw_ticks_to_us(gProfSendtoMax.last);
#endif
    uz_ocm_ring_clean(d, 4u * OCM_XCP_GW_DIAG_COUNT);
}

/*--------------------------------------------------------------------------
 * IPI ISR hook — call from APU_IPI_ISR under the Option Z gateway mode.
 * Runs in ISR context: OCM + queue (FromISR) only, no sockets.
 *------------------------------------------------------------------------*/
void xcp_gateway_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken) {
    if (!gGwReady) {
        return; /* pre-init IPI (R5 boots first); isr.c still clears the status */
    }
#if XCP_GW_PROFILE
    const uint64_t t0 = xcp_gw_ticks();
#endif
    xcp_gw_ipi_count++;
    int enqueued = xcp_gw_drain_rsp(pxHigherPriorityTaskWoken);
    enqueued |= xcp_gw_drain_daq(pxHigherPriorityTaskWoken);
    if (enqueued) {
        (void)xSemaphoreGiveFromISR(gTxSignal, pxHigherPriorityTaskWoken); /* wake the tx task */
    }
    xcp_gw_publish_diag();
#if XCP_GW_PROFILE
    const uint64_t t1 = xcp_gw_ticks();
    gProfIpi += t1 - t0;
    xcp_gw_prof_max_update(&gProfIpiMax, t1, t1 - t0);
#endif
}

/* Hand one command datagram to the R5 (CMD ring). Task context; the
 * critical section keeps the rx and tx tasks (both may write) and the IPI
 * ISR out. Returns 0 when the ring is full. */
static int xcp_gw_cmd_write(const uint8_t *d, uint16_t n) {
    int ok = 0;
    taskENTER_CRITICAL();
    uint8_t *p = uz_ocm_ring_reserve(&gCmd, n, 0u);
    if (p != NULL) {
        memcpy(p, d, n);
        (void)uz_ocm_ring_publish(&gCmd);
        xcp_gw_cmd_records++;
        ok = 1;
    } else {
        xcp_gw_cmd_dropped++;
    }
    taskEXIT_CRITICAL();
    return ok;
}

/* Session change (rx task): responses still in the RSP ring belong to the
 * previous master - drop them so the new session does not see an answer to
 * a command it never sent. The critical section keeps the IPI ISR (the
 * other consumer of the same ring state) out. */
static void xcp_gw_drop_stale_responses(void) {
    taskENTER_CRITICAL();
    if (uz_ocm_ring_poll(&gRsp) != 0u) {
        uint16_t len, aux;
        while (uz_ocm_ring_next(&gRsp, &len, &aux) != NULL) {
        }
        uz_ocm_ring_release(&gRsp);
    }
    taskEXIT_CRITICAL();
}

/*--------------------------------------------------------------------------
 * RX task: receive XCP-on-UDP datagrams from CANape, remember the master
 * endpoint and hand the datagram to the R5 at once (CMD ring; the R5 main
 * loop looks at it on every pass).
 *------------------------------------------------------------------------*/
/* Walk the packed TL frames of a received datagram: every frame must have
 * 1 <= dlc <= XCP_GW_MAX_CTO_SIZE and the chain must end exactly at the
 * datagram end (the same strictness as the TX restamp walk). The R5 parser
 * checks the bound again - this keeps junk out of the CMD ring and from
 * hijacking the master endpoint. */
static int xcp_gw_rx_frames_valid(const uint8_t *d, uint16_t n) {
    uint16_t off = 0;
    while ((uint16_t)(off + XCP_TL_HEADER_LEN) <= n) {
        uint16_t dlc = (uint16_t)(d[off] | ((uint16_t)d[off + 1] << 8));
        if (dlc == 0u || dlc > XCP_GW_MAX_CTO_SIZE || (uint32_t)off + XCP_TL_HEADER_LEN + dlc > n) {
            return 0;
        }
        off = (uint16_t)(off + XCP_TL_HEADER_LEN + dlc);
    }
    return off == n;
}

/* Session lines on the serial console: CONNECT and DISCONNECT from the
 * master, and a session the gateway closes itself (master supervision).
 * Task context only, never inside a critical section. A CONNECT or
 * DISCONNECT line fits the 64-byte UART TX FIFO, so the rx task does not
 * wait for the wire; the longer supervision line waits ~2 ms in the tx task,
 * once per closed session. */
#define XCP_GW_SEEN_CONNECT    1u
#define XCP_GW_SEEN_DISCONNECT 2u

/* Command codes of a datagram already checked by xcp_gw_rx_frames_valid(). */
static unsigned xcp_gw_rx_session_cmds(const uint8_t *d, uint16_t n) {
    unsigned seen = 0u;
    uint16_t off = 0;
    while ((uint16_t)(off + XCP_TL_HEADER_LEN) < n) {
        const uint16_t dlc = (uint16_t)(d[off] | ((uint16_t)d[off + 1] << 8));
        const uint8_t cmd = d[off + XCP_TL_HEADER_LEN];
        if (cmd == XCP_GW_CC_CONNECT) {
            seen |= XCP_GW_SEEN_CONNECT;
        } else if (cmd == XCP_GW_CC_DISCONNECT) {
            seen |= XCP_GW_SEEN_DISCONNECT;
        }
        off = (uint16_t)(off + XCP_TL_HEADER_LEN + dlc);
    }
    return seen;
}

static void xcp_gw_print_master(const char *what, const struct sockaddr_in *m) {
    const uint8_t *ip = (const uint8_t *)&m->sin_addr.s_addr; /* network order = a.b.c.d */
    xil_printf("APU: XCP %s %d.%d.%d.%d:%d\r\n", what, ip[0], ip[1], ip[2], ip[3],
               (int)lwip_ntohs(m->sin_port));
}

static void xcp_gw_rx_task(void *arg) {
    (void)arg;
    static uint8_t dgram[XCP_GW_FRAME_MAX]; /* only this task uses it */
    struct sockaddr_in src;
    socklen_t slen;
    for (;;) {
        slen = sizeof(src);
        int n = lwip_recvfrom(gSock, dgram, sizeof(dgram), 0, (struct sockaddr *)&src, &slen);
        if (n <= 0) {
            continue;
        }
        if (!xcp_gw_rx_frames_valid(dgram, (uint16_t)n)) {
            xcp_gw_rx_malformed_drop++; /* before master adoption: junk must not start a session */
            continue;
        }
        if (!gMasterValid ||
            src.sin_addr.s_addr != gMaster.sin_addr.s_addr ||
            src.sin_port != gMaster.sin_port) {
            /* New master endpoint = new session: fresh CTR sequence and no
             * stale DAQ backlog (tx task), no stale response (dropped here,
             * before the new master's first command reaches the R5).
             * Critical section: the tx task copies gMaster. */
            taskENTER_CRITICAL();
            gMaster = src;
            gMasterValid = 1;
            gMasterGen++;
            taskEXIT_CRITICAL();
            xcp_gw_drop_stale_responses();
        }
        gMasterLastRxTick = xTaskGetTickCount(); /* master supervision: it is alive */
        const unsigned seen = xcp_gw_rx_session_cmds(dgram, (uint16_t)n);
        (void)xcp_gw_cmd_write(dgram, (uint16_t)n); /* full: dropped, the master retries */
        /* Printed after the hand-over, so the command does not wait for it.
         * Whether the R5 accepts the CONNECT shows on the master's side. */
        if (seen & XCP_GW_SEEN_CONNECT) {
            xcp_gw_print_master("CONNECT from", &src);
        }
        if (seen & XCP_GW_SEEN_DISCONNECT) {
            xcp_gw_print_master("DISCONNECT from", &src);
        }
    }
}

/*--------------------------------------------------------------------------
 * TX task: batch the queued messages into one UDP datagram and send it to
 * CANape. Responses first (they jump the DAQ backlog, hedrive T1); the
 * transport CTR is stamped here, at transmission time, in transmission
 * order (hedrive T3 — a producer-side counter becomes wrong on reordering
 * and drops, and CANape reports "Ungueltiger Zaehler").
 *------------------------------------------------------------------------*/
static uint16_t gTxCtr = 0;

/* Walk the packed TL frames of one item and stamp the transmission-order
 * counter into each. Returns 0 (and counts) if the structure is malformed —
 * impossible unless memory corrupts. */
static int xcp_gw_restamp_ctr(xcp_gw_frame_t *f) {
    uint16_t off = 0;
    while ((uint16_t)(off + XCP_TL_HEADER_LEN) <= f->len) {
        uint16_t dlc = (uint16_t)(f->data[off] | ((uint16_t)f->data[off + 1] << 8));
        if (dlc == 0u || (uint32_t)off + XCP_TL_HEADER_LEN + dlc > f->len) {
            xcp_gw_tx_malformed_drop++;
            return 0;
        }
        f->data[off + 2] = (uint8_t)(gTxCtr & 0xFF);
        f->data[off + 3] = (uint8_t)(gTxCtr >> 8);
        gTxCtr++;
        off = (uint16_t)(off + XCP_TL_HEADER_LEN + dlc);
    }
    if (off != f->len) {
        xcp_gw_tx_malformed_drop++;
        return 0;
    }
    return 1;
}

/* Master supervision (see xcp_gateway_a53.h): close the session from the
 * gateway side. The R5 engine is told with a regular XCP DISCONNECT through
 * the CMD ring; it stops DAQ and answers, and that answer is discarded here
 * because the endpoint is forgotten first. Task context only (tx task). */
static void xcp_gw_master_lost_disconnect(const char *why) {
    static const uint8_t disconnect[XCP_TL_HEADER_LEN + 1] = {0x01, 0x00, 0x00, 0x00, XCP_GW_CC_DISCONNECT};
    struct sockaddr_in master;
    taskENTER_CRITICAL();
    master = gMaster;
    gMasterValid = 0; /* ISR drops DAQ, tx task sends nothing */
    taskEXIT_CRITICAL();
    xcp_gw_master_lost++;
    (void)xcp_gw_cmd_write(disconnect, (uint16_t)sizeof(disconnect));
    xQueueReset(gTxQueue); /* the backlog has no receiver any more */
    xcp_gw_print_master(why, &master);
}

static void xcp_gw_tx_task(void *arg) {
    (void)arg;
    static xcp_gw_frame_t f;                       /* only this task uses them */
    static uint8_t tx_bufs[XCP_GW_TX_BUFS][XCP_GW_BATCH_BUF_SIZE];
    uint32_t tx_buf = 0;                           /* next free transmit buffer */
    uint32_t my_master_gen = 0;
    uint32_t send_fail_run = 0;                    /* consecutive dropped datagrams */

    for (;;) {
        if (my_master_gen != gMasterGen) {
            /* New session: the queued DAQ backlog belongs to the old one.
             * (CTO queue is NOT reset: it may already hold the response to
             * the new master's first command.) */
            my_master_gen = gMasterGen;
            xQueueReset(gTxQueue);
            gTxCtr = 0;
            send_fail_run = 0;
        }

        uint8_t *const batch = tx_bufs[tx_buf];
        uint32_t fill = 0;
#if XCP_GW_PROFILE
        const uint64_t tb0 = xcp_gw_ticks();
#endif

        /* Take pending responses first (they jump the DAQ backlog). With both
         * queues empty, block on the ISR's "frames queued" signal so a
         * response on an idle link goes out at once; the 20 ms fallback only
         * keeps the master-change check above alive. */
        if (xQueueReceive(gTxCtoQueue, &f, 0) != pdTRUE && xQueueReceive(gTxQueue, &f, 0) != pdTRUE) {
            (void)xSemaphoreTake(gTxSignal, pdMS_TO_TICKS(20));
            continue;
        }
        if (xcp_gw_restamp_ctr(&f)) {
            memcpy(&batch[fill], f.data, f.len);
            fill += f.len;
        }

        /* Top up the datagram without blocking: responses keep priority. */
        for (;;) {
            QueueHandle_t q = NULL;
            if (xQueuePeek(gTxCtoQueue, &f, 0) == pdTRUE) {
                q = gTxCtoQueue;
            } else if (xQueuePeek(gTxQueue, &f, 0) == pdTRUE) {
                q = gTxQueue;
            } else {
                break;
            }
            if (fill + f.len > XCP_GW_BATCH_BUF_SIZE) {
                break; /* datagram full; the rest goes into the next one */
            }
            (void)xQueueReceive(q, &f, 0); /* single consumer: same item as peeked */
            if (xcp_gw_restamp_ctr(&f)) {
                memcpy(&batch[fill], f.data, f.len);
                fill += f.len;
            }
        }

        if (fill == 0u || !gMasterValid) {
            continue; /* nothing valid to send / no master yet (DAQ before CONNECT) */
        }
        struct sockaddr_in dst;
        taskENTER_CRITICAL();
        dst = gMaster; /* consistent copy vs. a concurrent endpoint change */
        taskEXIT_CRITICAL();
        int sent = -1;
#if XCP_GW_PROFILE
        gProfTx += xcp_gw_ticks() - tb0; /* batching; the sends are added below */
#endif
        for (int attempt = 0; attempt <= XCP_GW_SEND_RETRY_MAX; attempt++) {
            if (attempt != 0) {
                vTaskDelay(1); /* one tick: GEM drains its TX ring by hardware */
            }
#if XCP_GW_PROFILE
            const uint64_t ts0 = xcp_gw_ticks();
#endif
            sent = lwip_sendto(gSock, batch, fill, 0, (struct sockaddr *)&dst, sizeof(dst));
#if XCP_GW_PROFILE
            const uint64_t ts1 = xcp_gw_ticks();
            gProfSendto += ts1 - ts0;
            gProfTx += ts1 - ts0;
            gProfSendtoN++;
            xcp_gw_prof_max_update(&gProfSendtoMax, ts1, ts1 - ts0);
            if (sent >= 0) {
                gProfTxBytes += fill;
            }
#endif
            if (sent >= 0) {
                break;
            }
            xcp_gw_sendto_err++;
        }
        if (sent < 0) {
            xcp_gw_sendto_drop++; /* stamped frames lost -> wire CTR gap */
            send_fail_run++;
        } else {
            /* Queued: the DMA may read this buffer until the frame is sent.
             * A failed send left no descriptor on it, so it is reused. */
            tx_buf = (tx_buf + 1u) % XCP_GW_TX_BUFS;
            send_fail_run = 0;
        }
        /* Master supervision: nothing has been sendable for a while, or (if
         * enabled) the master has been silent too long while we stream. */
        const char *lost = NULL;
        if (send_fail_run >= (uint32_t)XCP_GATEWAY_SEND_FAIL_LIMIT) {
            lost = "session closed, sends to the master keep failing:";
        }
#if XCP_GATEWAY_MASTER_TIMEOUT_MS > 0
        if ((TickType_t)(xTaskGetTickCount() - gMasterLastRxTick) > pdMS_TO_TICKS(XCP_GATEWAY_MASTER_TIMEOUT_MS)) {
            lost = "session closed, master silent too long:";
        }
#endif
        if (lost != NULL && gMasterValid) {
            send_fail_run = 0;
            xcp_gw_master_lost_disconnect(lost);
        }
        /* Let lwIP's tcpip thread and the rx task run between datagrams.
         * They run at this task's priority, FreeRTOS does not preempt between
         * equal priorities, and with LWIP_TCPIP_CORE_LOCKING lwip_sendto
         * never blocks: without the yield, a command arriving during a burst
         * of DAQ datagrams waited in lwIP's mailbox until the whole burst was
         * sent. Bench 2026-11-18, 900 B/cycle, 13-datagram bursts: commands
         * back to back 583 us median at equal priority, 317 us with this task
         * one priority lower. The yield does the same (4-segment trigger: 252
         * vs 251 us) for about 2 % of the A53, and keeps this task above the
         * application's priority-1 tasks (polled I2C, CAN), next to which the
         * lower priority showed rare delays of 5-29 ms. */
        taskYIELD();
    }
}

/*--------------------------------------------------------------------------
 * Init: UDP socket on XCP_GATEWAY_UDP_PORT, the queues, the rings and the
 * tasks. Call once the lwIP interface is up (like the JavaScope server).
 * Returns 0 on success.
 *------------------------------------------------------------------------*/
int xcp_gateway_a53_init(uint32_t thread_stack, uint32_t thread_prio) {
    gTxQueue = xQueueCreate(XCP_GW_TXQ_DEPTH, sizeof(xcp_gw_frame_t));
    gTxCtoQueue = xQueueCreate(XCP_GW_CTOQ_DEPTH, sizeof(xcp_gw_frame_t));
    gTxSignal = xSemaphoreCreateBinary();
    if (gTxQueue == NULL || gTxCtoQueue == NULL || gTxSignal == NULL) {
        return -1;
    }

    gSock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (gSock < 0) {
        return -2;
    }
    struct sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_port = lwip_htons(XCP_GATEWAY_UDP_PORT);
    a.sin_addr.s_addr = lwip_htonl(INADDR_ANY);
    if (lwip_bind(gSock, (struct sockaddr *)&a, sizeof(a)) < 0) {
        lwip_close(gSock);
        gSock = -1;
        return -3;
    }

    /* Rings: start empty from wherever the R5 stands (uz_ocm_ring.h). */
    ocm_xcp_ring_setup(&gDaq, &gRsp, &gCmd);
    uz_ocm_ring_consumer_init(&gDaq);
    uz_ocm_ring_consumer_init(&gRsp);
    uz_ocm_ring_producer_init(&gCmd);

    if (sys_thread_new("xcp_gw_rx", xcp_gw_rx_task, NULL, thread_stack, thread_prio) == NULL) {
        return -4;
    }
    if (sys_thread_new("xcp_gw_tx", xcp_gw_tx_task, NULL, thread_stack, thread_prio) == NULL) {
        return -5;
    }
#if XCP_GW_PROFILE
    gProfIpiMax.win_start = xcp_gw_ticks();
    gProfSendtoMax.win_start = gProfIpiMax.win_start;
    /* Diagnostics only: without the probe the profile just shows no idle time. */
    (void)xTaskCreate(xcp_gw_idle_probe_task, "xcp_gw_idle", configMINIMAL_STACK_SIZE, NULL,
                      tskIDLE_PRIORITY, NULL);
#endif
    gGwReady = 1; /* from here on the IPI ISR may touch the queues and rings */
    return 0;
}
