/*----------------------------------------------------------------------------
| xcp_gateway_a53.c
|   Option Z — A53 (FreeRTOS/lwIP) Ethernet gateway for the R5 XCPlite engine.
|   The A53 is a dumb pipe: it ferries XCP-on-UDP datagrams between CANape and
|   the OCM FIFO; the XCP slave logic lives on the R5 (arbitrary addressing).
|
|   Data path (mirrors uz_sw_xcp_hedrive_andi OCM_eth_adapter, but UDP):
|     CANape --UDP--> rx_task --queue--> IPI ISR --> XCP_IN  --> R5 XcpCommand
|     R5 XcpEvent/CRM --> XCP_OUT --> IPI ISR --queue--> tx_task --UDP--> CANape
|
|   Hard-learned rules ported from the hedrive hardware campaign
|   (XCP_BOTTLENECK_ANALYSIS.md):
|   - F1: the IPI ISR touches ONLY OCM + FreeRTOS queues (…FromISR). Sockets
|     live in the tasks; never block/delay/print in ISR context.
|   - T8: reads from XCP_OUT are staged locally and committed only when the
|     content was stable — the header and the CTO mailbox under the seqlock,
|     the DAQ chain by its own sequence number (ocm_xcp_fifo.c, mechanism
|     5) — so torn frames never reach the network. Command responses arrive
|     via the acknowledged CTO mailbox (exactly-once).
|   - T8 addendum: commands are delivered via a generation handshake — the
|     current batch is rewritten into XCP_IN every IPI until the R5
|     acknowledges execution. A command can never be lost to IPI latency.
|   - T1: CTO frames take a dedicated queue; they jump the DAQ backlog and
|     are never tail-dropped with it (a lost/late response kills the session).
|   - T3: the transport-layer counter (CTR) is owned HERE, stamped at
|     transmission time in transmission order — reordering (CTO bypass) and
|     tail-drops are invisible to the master.
|   - B1: frames are batched into one UDP datagram per sendto() (XCP-on-UDP
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
#include "ocm_xcp_fifo.h"
#include <string.h>
#include <stdint.h>
#if XCP_GW_PROFILE
#include "xparameters.h" /* XPAR_CPU_CORTEXA53_0_TIMESTAMP_CLK_FREQ */
#endif

#define XCP_GW_FRAME_MAX     OCM_XCP_RECORD_MAX /* one R5 queue segment = one datagram */
#define XCP_TL_HEADER_LEN    4    /* [dlc:u16][ctr:u16]                          */
#define XCP_PID_CTO_MIN      0xFCu
/* Largest XCP command the R5 engine accepts (XCPTL_MAX_CTO_SIZE, set by
 * xcplib_r5_cfg.h). The engine asserts on anything bigger, so a datagram
 * carrying such a frame is refused here already (see xcp_gw_rx_frames_valid). */
#define XCP_GW_MAX_CTO_SIZE  248u

/* DAQ (DTO) queue: deep on purpose — it is the burst absorber between the
 * 10–20 kHz OCM drain and the UDP send rate, and measurement gaps hurt more
 * than backlog latency. Sized to bridge multi-second send stalls, matching
 * hedrive's final sizing (its rig saw ~2 s host receive pauses every few
 * minutes that a 140 ms queue could not absorb). Items are fixed-size
 * (XCP_GW_FRAME_MAX, one R5 segment of up to 1400 B since 2026-11-17, was
 * 256): 65536 x ~1.4 KB ≈ 92 MB of the 200 MB FreeRTOS heap. Under load the
 * R5 hands out mostly full segments, so that is ≈ 2 s of buffering at
 * 320 Mbit/s; with small records it is fewer seconds. The queue runs empty in steady state, so normal
 * latency is unaffected. NOTE: UDP has no backpressure — this queue covers
 * ECU-side stalls (lwIP pbuf/ARP, task starvation); PC-side receive pauses
 * must be absorbed by the receiver's socket buffer (xcp_poll.py sets 32 MB).
 * Overflow policy: tail-drop + count, never purge, never block from the ISR. */
#define XCP_GW_TXQ_DEPTH     65536
/* Dedicated queue for CTO frames (RES/ERR/EV/SERV): responses must never
 * wait behind — or be dropped with — the DAQ backlog (hedrive T1). */
#define XCP_GW_CTOQ_DEPTH    16
#define XCP_GW_RXQ_DEPTH     64

/* Bound the IPI-ISR time: max records staged OCM -> queues per interrupt.
 * The 32 KB XCP_OUT window holds ~23 max-size records (the R5 queue hands
 * out accumulated segments of up to 1400 B); the cap only bites on many tiny
 * ones. A full window is rare - it means the R5 is working off a backlog. */
#define XCP_GW_DRAIN_MAX_PER_IPI 128

/* Command batch offered to the R5 per generation (bounded by the XCP_IN
 * chain: 3 x (4 + 255) + terminator < OCM_XCP_IN_CHAIN_LEN). */
#define XCP_GW_IN_BATCH_MAX  3

/* TX batching: pack queued TL frames into one UDP datagram (several XCP
 * messages per datagram are standard XCP-on-Ethernet; XCPlite's own PC
 * transport does the same). 1400 keeps datagram + UDP/IP headers under a
 * 1500-byte MTU — no IP fragmentation. */
#define XCP_GW_BATCH_BUF_SIZE 1400
#if XCP_GW_BATCH_BUF_SIZE < XCP_GW_FRAME_MAX
#error "a datagram must hold the largest R5 record"
#endif

/* Bounded send retry (hedrive "bounded sends", UDP flavor): lwip_sendto()
 * fails transiently under burst load (pbuf/TX-BD exhaustion at 40k
 * datagrams/s — every wire-loss frame of the first 320 Mbit/s hardware run
 * traced to exactly these failures). The batch is already CTR-stamped, so
 * dropping it tears a gap into the wire counter; the GEM TX ring drains by
 * hardware in <1 ms, so waiting one tick (10 ms @ 100 Hz) converts the loss
 * into latency the deep queue absorbs. Bounded so a persistent failure
 * (master gone, no route) cannot wedge the task: worst ~50 ms, then drop. */
#define XCP_GW_SEND_RETRY_MAX 5

/* One XCP-on-Ethernet record in transit between a task and the IPI ISR.
 * data may hold SEVERAL concatenated TL frames ([dlc][ctr][packet])+ —
 * queue32 segments on the R5 and CANape command bursts both pack frames. */
typedef struct {
    uint16_t len;
    uint8_t  data[XCP_GW_FRAME_MAX];
} xcp_gw_frame_t;

static QueueHandle_t gRxQueue    = NULL;     /* CANape -> R5 (commands)         */
static QueueHandle_t gTxQueue    = NULL;     /* R5 -> CANape (DAQ)              */
static QueueHandle_t gTxCtoQueue = NULL;     /* R5 -> CANape (responses/events) */
/* "Frames queued" signal from the IPI ISR to the tx task. A binary semaphore
 * is enough: the task drains both queues completely after every take, and a
 * give that arrives while it is busy just makes the next take return at
 * once. Without it the task could only block on the DAQ queue, so a command
 * response arriving on an idle link waited out that timeout (up to two
 * 100 Hz ticks = 10-20 ms per command, i.e. every command of a CANape DAQ
 * setup). */
static SemaphoreHandle_t gTxSignal = NULL;
static int           gSock      = -1;

/* The IPI ISR is registered by initialize_ipi_runtime() long before this
 * gateway is initialised (network-up/DHCP), while the R5 fires an IPI every
 * control cycle from boot. Guard the ISR path until init completed. */
static volatile int gGwReady = 0;

static struct sockaddr_in gMaster;           /* last master (CANape) endpoint   */
static volatile int       gMasterValid = 0;
static volatile uint32_t  gMasterGen = 0;    /* bumped on endpoint change       */
static volatile TickType_t gMasterLastRxTick = 0; /* last valid datagram from the master */

/* Diagnostics (inspect via debugger; hedrive validation-checklist counters):
 *   xcp_gw_ocm_skipped_writing header copy unusable this IPI: the R5 was
 *                              mid-sweep (odd seqlock) or swept during the
 *                              copy. Mailbox and command ack are simply
 *                              taken with the next IPI; the DAQ chain is
 *                              read anyway (validated by chain_seq)
 *   xcp_gw_ocm_torn            DAQ chain rewritten while the A53 read it
 *                              (chain_seq changed); read discarded. Rare:
 *                              the R5 rewrites a non-empty chain only after
 *                              our ack or after the 50-sweep hold timeout
 *   xcp_gw_ocm_cycles_missed   R5 sweeps between two header copies
 *                              (All three are IPI latency indicators only:
 *                              the R5 keeps a DAQ chain in place until it
 *                              is acknowledged - xcp_r5_out_held - so none
 *                              of them loses data.)
 *   xcp_gw_ocm_capped          per-IPI drain cap hit with records left over
 *   xcp_gw_txq_dropped         DAQ queue full -> record tail-dropped
 *   xcp_gw_ctoq_dropped        CTO queue full -> frame dropped (must stay 0)
 *   xcp_gw_in_batches_sent     command batches (generations) offered to the R5
 *   xcp_gw_in_retry_cycles     IPIs spent re-offering an unconsumed batch
 *   xcp_gw_tx_malformed_drop   record failed the TL-frame walk on TX (must stay 0)
 *   xcp_gw_rx_malformed_drop   datagram failed the TL-frame walk on RX (bad
 *                              dlc chain or a frame > XCP_GW_MAX_CTO_SIZE) and
 *                              was not forwarded to the R5. CANape never sends
 *                              these; non-zero = port scanner / broken client.
 *   xcp_gw_sendto_err          transient lwip_sendto() failures (pbuf/TX-BD
 *                              exhaustion under burst load; observed 74x in a
 *                              60 s 320 Mbit/s run). Retried, so err alone is
 *                              pressure, not loss.
 *   xcp_gw_sendto_drop         batch still failing after the bounded retries —
 *                              the batch was already CTR-stamped, so each one
 *                              is a wire counter gap and the ONLY ECU-side
 *                              source of them. Gaps with this at 0 mean the
 *                              loss is wire/PC-side. Must stay 0.
 *   xcp_gw_ipi_count          IPIs handled (A53-side liveness; ~= R5 sweeps)
 *   xcp_gw_master_lost        sessions closed by the gateway because the
 *                              master became unreachable (see
 *                              xcp_gateway_a53.h, master supervision)
 *   All of the above are mirrored every IPI into the XCP_IN header spare
 *   words (ocm_xcp_fifo.h, OCM_XCP_IN_DIAG_ADDR) together with the DAQ queue
 *   fill level, so CANape (uz.A2L xcp_gw_*) and xcp_poll.py --stress can
 *   read them over XCP; the debugger is no longer the only way. */
volatile uint32_t xcp_gw_ocm_skipped_writing = 0;
volatile uint32_t xcp_gw_ocm_torn = 0;
volatile uint32_t xcp_gw_ocm_cycles_missed = 0;
volatile uint32_t xcp_gw_ocm_capped = 0;
volatile uint32_t xcp_gw_txq_dropped = 0;
volatile uint32_t xcp_gw_ctoq_dropped = 0;
volatile uint32_t xcp_gw_in_batches_sent = 0;
volatile uint32_t xcp_gw_in_retry_cycles = 0;
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
 * IPI ISR — read phase (XCP_OUT -> queues): header and CTO mailbox under the
 * seqlock, DAQ chain validated by chain_seq (ocm_xcp_fifo.c, mechanism 5).
 * All buffers static: this runs only in the (non-reentrant) IPI ISR, and the
 * staging area is far too big for an ISR stack frame.
 *------------------------------------------------------------------------*/
static xcp_gw_frame_t gStage[XCP_GW_DRAIN_MAX_PER_IPI];
static xcp_gw_frame_t gStageCto;
static uint32_t gCtoLastSeq = 0;         /* last mailbox seq forwarded (acked)  */
static uint32_t gInConsumed = 0;         /* R5 batch ack, valid under seqlock   */
static uint32_t gOutChainLast = 0;       /* last XCP_OUT chain_seq consumed     */
static uint32_t gPrevSeq = 0;
static int      gPrevSeqValid = 0;
/* Set at init and on master change: adopt the current mailbox seq without
 * forwarding, so a response parked before/during a session change is not
 * replayed into the next session. */
static volatile int gCtoAdoptPending = 1;

static void xcp_gw_read_out_phase(BaseType_t *woken) {
    uint8_t  cto_len = 0;
    uint32_t cto_seq = 0;
    int      have_cto = 0;
    int      header_ok = 0;
    int      chain_ok = 0;
    uint32_t n_staged = 0;
    int      capped = 0;

    /* 1. Header copy under the seqlock: command-batch ack, chain sequence and
     * the CTO mailbox (it persists across sweeps until acknowledged). Short -
     * one control line plus at most one 256-byte frame - so it rarely
     * overlaps an R5 sweep, and if it does it is simply taken next IPI. */
    uint32_t seq_begin = ocm_xcp_out_seq_read(); /* refreshes the control line */
    uint32_t in_consumed_snap = ocm_xcp_in_consumed_read();
    uint32_t chain_seq_snap = ocm_xcp_out_chain_seq_read();
    if ((seq_begin & 1u) == 0u) {
        if (ocm_xcp_cto_read(&cto_len, gStageCto.data, &cto_seq) && cto_seq != gCtoLastSeq) {
            have_cto = 1;
        }
        header_ok = ocm_xcp_out_seq_unchanged(seq_begin);
    }
    if (!header_ok) {
        xcp_gw_ocm_skipped_writing++;
        have_cto = 0;
    }

    /* 2. DAQ chain, once per chain sequence, validated by chain_seq and not
     * by the seqlock (ocm_xcp_fifo.c, mechanism 5): the R5 publishes a
     * non-zero chain_seq only for a complete chain and zeroes it before a
     * rewrite. A sweep that KEEPS an unacknowledged chain bumps the seqlock
     * but not chain_seq, so this read may take longer than a sweep. */
    if (chain_seq_snap != 0u && chain_seq_snap != gOutChainLast) {
#if XCP_GW_PROFILE
        const uint64_t tc0 = xcp_gw_ticks();
#endif
        ocm_xcp_fifo_prepare_read();
        for (;;) {
            uint16_t len;
            uint8_t *data;
            if (n_staged >= XCP_GW_DRAIN_MAX_PER_IPI) {
                capped = 1; /* rest of this chain is lost: it is acknowledged as a whole */
                break;
            }
            if (!ocm_xcp_fifo_read(&len, &data)) {
                break; /* end of chain (or bounds guard tripped) */
            }
            gStage[n_staged].len = len;
            memcpy(gStage[n_staged].data, data, len);
            n_staged++;
        }
        if (ocm_xcp_out_chain_unchanged(chain_seq_snap)) {
            chain_ok = 1;
        } else {
            /* The R5 rewrote the chain meanwhile (empty chain, or its hold
             * timeout ran out): discard; the new chain is read next IPI. */
            xcp_gw_ocm_torn++;
        }
#if XCP_GW_PROFILE
        gProfChain += xcp_gw_ticks() - tc0;
#endif
    }

    /* 3. Commit what was consistent. */
    int enqueued = 0;
    if (header_ok) {
        gInConsumed = in_consumed_snap;
        if (gPrevSeqValid) {
            uint32_t delta = seq_begin - gPrevSeq; /* wrap-safe */
            if (delta > 2u) {
                xcp_gw_ocm_cycles_missed += (delta - 2u) / 2u;
            }
        }
        gPrevSeq = seq_begin;
        gPrevSeqValid = 1;

        if (gCtoAdoptPending) {
            /* Session change: whatever sits in the mailbox predates it. */
            gCtoLastSeq = cto_seq;
            gCtoAdoptPending = 0;
            have_cto = 0;
        }
        if (have_cto) {
            gCtoLastSeq = cto_seq; /* acked via the write phase this IPI */
            gStageCto.len = cto_len;
            if (xQueueSendToBackFromISR(gTxCtoQueue, &gStageCto, woken) == pdTRUE) {
                enqueued = 1;
            } else {
                xcp_gw_ctoq_dropped++;
            }
        }
    }
    if (chain_ok) {
#if XCP_GW_PROFILE
        const uint64_t te0 = xcp_gw_ticks();
        gProfRecords += n_staged;
#endif
        gOutChainLast = chain_seq_snap; /* acknowledged to the R5 by the write phase */
        if (capped) {
            xcp_gw_ocm_capped++;
        }
        if (gMasterValid) { /* no consumer yet: drop staged DAQ (the chain ack still advances) */
            for (uint32_t i = 0; i < n_staged; i++) {
                /* Defensive classify by XCP PID: CTO packets that travelled the chain
                 * (EV/SERV from the R5 queue) jump the DAQ backlog too. */
                if (gStage[i].len > XCP_TL_HEADER_LEN &&
                    gStage[i].data[XCP_TL_HEADER_LEN] >= XCP_PID_CTO_MIN) {
                    if (xQueueSendToBackFromISR(gTxCtoQueue, &gStage[i], woken) == pdTRUE) {
                        enqueued = 1;
                    } else {
                        xcp_gw_ctoq_dropped++;
                    }
                    continue;
                }
                if (xQueueSendToBackFromISR(gTxQueue, &gStage[i], woken) == pdTRUE) {
                    enqueued = 1;
                } else {
                    /* DAQ queue full: the UDP drain has stalled for longer than the
                     * queue depth covers. Tail-drop and count. Never block, delay or
                     * print here — ISR context (hedrive F1). */
                    xcp_gw_txq_dropped++;
                }
            }
        }
#if XCP_GW_PROFILE
        gProfEnq += xcp_gw_ticks() - te0;
#endif
    }
    if (enqueued) {
        (void)xSemaphoreGiveFromISR(gTxSignal, woken); /* wake the tx task (CTO or DAQ) */
    }
}

/*--------------------------------------------------------------------------
 * IPI ISR — write phase (rx queue -> XCP_IN), generation handshake.
 * The in-flight batch is rewritten with IDENTICAL bytes every IPI until the
 * R5 acknowledges the generation, so a torn concurrent read on the R5 still
 * sees consistent content and no command is ever lost (hedrive T8 addendum:
 * "Timeout: Keine Response" with a clean wire capture — commands silently
 * eaten by IPI/cycle overlap).
 *------------------------------------------------------------------------*/
static xcp_gw_frame_t gInBatch[XCP_GW_IN_BATCH_MAX];
static xcp_gw_frame_t gInPeek;
static uint8_t  gInBatchN = 0;
static uint32_t gInGen = 0;              /* generation of the in-flight batch */

static void xcp_gw_write_in_phase(BaseType_t *woken) {
    ocm_xcp_fifo_prepare_write();
    /* Publish the last consumed mailbox sequence every cycle (idempotent);
     * the R5 frees its CTO mailbox when this matches what it parked. */
    ocm_xcp_cto_ack_write(gCtoLastSeq);
    /* Same for the DAQ chain: the R5 rewinds XCP_OUT only after it sees the
     * sequence of the chain we consumed. */
    ocm_xcp_out_ack_write(gOutChainLast);

    /* Current batch processed by the R5? Then it is done for good. */
    if (gInBatchN != 0u && gInConsumed == gInGen) {
        gInBatchN = 0u;
    }

    if (gInBatchN == 0u) {
        /* Build the next batch from the RX queue (bounded by the chain space
         * and the batch array; the rest stays queued for later generations). */
        size_t space = OCM_XCP_IN_CHAIN_LEN - 4u; /* minus terminator */
        while (gInBatchN < XCP_GW_IN_BATCH_MAX) {
            if (xQueuePeekFromISR(gRxQueue, &gInPeek) != pdTRUE) {
                break;
            }
            if (gInPeek.len == 0u || gInPeek.len > 255u) {
                /* Corrupt entry: consume and drop — leaving it queued would
                 * head-of-line block all future commands forever. */
                (void)xQueueReceiveFromISR(gRxQueue, &gInPeek, woken);
                continue;
            }
            if ((size_t)(4u + gInPeek.len) > space) {
                break; /* batch full; remaining commands go into the next one */
            }
            space -= (size_t)(4u + gInPeek.len);
            gInBatch[gInBatchN] = gInPeek;
            gInBatchN++;
            (void)xQueueReceiveFromISR(gRxQueue, &gInPeek, woken);
        }
        if (gInBatchN != 0u) {
            gInGen++;
            if (gInGen == 0u) {
                gInGen = 1u; /* 0 is reserved for "no batch ever" */
            }
            xcp_gw_in_batches_sent++;
        }
    } else {
        xcp_gw_in_retry_cycles++;
    }

    /* (Re)write the in-flight batch — identical bytes every IPI until acked. */
    for (uint8_t i = 0; i < gInBatchN; i++) {
        if (!ocm_xcp_fifo_write(gInBatch[i].len, gInBatch[i].data)) {
            break; /* cannot happen (batch sized to the region); defensive */
        }
    }
    /* Mirror the gateway counters into the XCP_IN header spare words so the
     * XCP master can read them by absolute address (ocm_xcp_fifo.h). 14 plain
     * stores per IPI; they ride the header flush below. */
    xcp_gw_ipi_count++;
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_OCM_SKIPPED_WRITING, xcp_gw_ocm_skipped_writing);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_OCM_TORN, xcp_gw_ocm_torn);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_OCM_CYCLES_MISSED, xcp_gw_ocm_cycles_missed);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_OCM_CAPPED, xcp_gw_ocm_capped);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_TXQ_DROPPED, xcp_gw_txq_dropped);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_CTOQ_DROPPED, xcp_gw_ctoq_dropped);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_IN_BATCHES_SENT, xcp_gw_in_batches_sent);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_IN_RETRY_CYCLES, xcp_gw_in_retry_cycles);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_TX_MALFORMED_DROP, xcp_gw_tx_malformed_drop);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_RX_MALFORMED_DROP, xcp_gw_rx_malformed_drop);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_SENDTO_ERR, xcp_gw_sendto_err);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_SENDTO_DROP, xcp_gw_sendto_drop);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_IPI_COUNT, xcp_gw_ipi_count);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_TXQ_LEVEL, (uint32_t)uxQueueMessagesWaitingFromISR(gTxQueue));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_MASTER_LOST, xcp_gw_master_lost);
#if XCP_GW_PROFILE
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_NOW_US, xcp_gw_ticks_to_us(xcp_gw_ticks()));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_IDLE_US, xcp_gw_ticks_to_us(gProfIdle));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_IPI_US, xcp_gw_ticks_to_us(gProfIpi));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_IPI_MAX_US, xcp_gw_ticks_to_us(gProfIpiMax.last));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_CHAIN_US, xcp_gw_ticks_to_us(gProfChain));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_ENQ_US, xcp_gw_ticks_to_us(gProfEnq));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_RECORDS, gProfRecords);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_TX_US, xcp_gw_ticks_to_us(gProfTx));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_SENDTO_US, xcp_gw_ticks_to_us(gProfSendto));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_SENDTO_N, gProfSendtoN);
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_TX_KB, (uint32_t)(gProfTxBytes >> 10));
    ocm_xcp_in_diag_write(OCM_XCP_DIAG_GW_PROF_SENDTO_MAX_US, xcp_gw_ticks_to_us(gProfSendtoMax.last));
#endif
    ocm_xcp_in_gen_publish(gInGen);
    ocm_xcp_fifo_cache_flush_after_write(); /* chain first, then header */
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
    xcp_gw_read_out_phase(pxHigherPriorityTaskWoken);
    xcp_gw_write_in_phase(pxHigherPriorityTaskWoken);
#if XCP_GW_PROFILE
    const uint64_t t1 = xcp_gw_ticks();
    gProfIpi += t1 - t0;
    xcp_gw_prof_max_update(&gProfIpiMax, t1, t1 - t0);
#endif
}

/*--------------------------------------------------------------------------
 * RX task: receive XCP-on-UDP datagrams from CANape, remember the master
 * endpoint, and hand the frame to the IPI ISR via gRxQueue.
 *------------------------------------------------------------------------*/
/* Walk the packed TL frames of a received datagram: every frame must have
 * 1 <= dlc <= XCP_GW_MAX_CTO_SIZE and the chain must end exactly at the
 * datagram end (the same strictness as the TX restamp walk). The R5 parser
 * checks the bound again - this keeps junk from occupying a command
 * generation and from hijacking the master endpoint. */
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

static void xcp_gw_rx_task(void *arg) {
    (void)arg;
    static xcp_gw_frame_t f; /* only this task uses it */
    struct sockaddr_in src;
    socklen_t slen;
    for (;;) {
        slen = sizeof(src);
        int n = lwip_recvfrom(gSock, f.data, sizeof(f.data), 0, (struct sockaddr *)&src, &slen);
        if (n <= 0 || n > 255) {
            continue; /* command datagrams: XCP_IN batches are sized for <= 255 B records */
        }
        if (!xcp_gw_rx_frames_valid(f.data, (uint16_t)n)) {
            xcp_gw_rx_malformed_drop++; /* before master adoption: junk must not start a session */
            continue;
        }
        if (!gMasterValid ||
            src.sin_addr.s_addr != gMaster.sin_addr.s_addr ||
            src.sin_port != gMaster.sin_port) {
            /* New master endpoint = new session: fresh CTR sequence, drop the
             * stale DAQ backlog (tx task), swallow a stale parked response
             * (ISR adopt). Critical section: the tx task copies gMaster. */
            taskENTER_CRITICAL();
            gMaster = src;
            gMasterValid = 1;
            gMasterGen++;
            gCtoAdoptPending = 1;
            taskEXIT_CRITICAL();
        }
        gMasterLastRxTick = xTaskGetTickCount(); /* master supervision: it is alive */
        f.len = (uint16_t)n;
        (void)xQueueSendToBack(gRxQueue, &f, 0); /* drop if full; master retries */
    }
}

/*--------------------------------------------------------------------------
 * TX task: batch frames produced by the IPI ISR into one UDP datagram and
 * send it to CANape. CTO frames first (they jump the DAQ backlog, hedrive
 * T1); the transport CTR is stamped here, at transmission time, in
 * transmission order (hedrive T3 — the R5's producer-side counter becomes
 * wrong on reordering/drops and CANape reports "Ungueltiger Zaehler").
 *------------------------------------------------------------------------*/
static uint16_t gTxCtr = 0;

/* Walk the packed TL frames of one record and stamp the transmission-order
 * counter into each. Returns 0 (and counts) if the structure is malformed —
 * the seqlock upstream makes that impossible unless memory corrupts. */
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
 * the command path (generation handshake = guaranteed delivery); it stops
 * DAQ and answers, and that answer is discarded here because the endpoint
 * is forgotten first. Task context only (tx task). */
static void xcp_gw_master_lost_disconnect(void) {
    static const xcp_gw_frame_t disconnect = {
        .len = XCP_TL_HEADER_LEN + 1,
        .data = {0x01, 0x00, 0x00, 0x00, 0xFE}, /* [dlc=1][ctr=0][DISCONNECT] */
    };
    taskENTER_CRITICAL();
    gMasterValid = 0; /* ISR drops staged DAQ, tx task sends nothing */
    taskEXIT_CRITICAL();
    xcp_gw_master_lost++;
    (void)xQueueSendToBack(gRxQueue, &disconnect, pdMS_TO_TICKS(100));
    xQueueReset(gTxQueue); /* the backlog has no receiver any more */
}

static void xcp_gw_tx_task(void *arg) {
    (void)arg;
    static xcp_gw_frame_t f;                       /* only this task uses them */
    static uint8_t batch[XCP_GW_BATCH_BUF_SIZE];
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

        uint32_t fill = 0;
#if XCP_GW_PROFILE
        const uint64_t tb0 = xcp_gw_ticks();
#endif

        /* Take pending CTOs first (they jump the DAQ backlog). With both queues
         * empty, block on the ISR's "frames queued" signal so a response on an
         * idle link goes out at once; the 20 ms fallback only keeps the
         * master-change check above alive. */
        if (xQueueReceive(gTxCtoQueue, &f, 0) != pdTRUE && xQueueReceive(gTxQueue, &f, 0) != pdTRUE) {
            (void)xSemaphoreTake(gTxSignal, pdMS_TO_TICKS(20));
            continue;
        }
        if (xcp_gw_restamp_ctr(&f)) {
            memcpy(&batch[fill], f.data, f.len);
            fill += f.len;
        }

        /* Top up the datagram without blocking: CTOs keep priority. */
        for (;;) {
            QueueHandle_t q = NULL;
            if (xQueuePeek(gTxCtoQueue, &f, 0) == pdTRUE) {
                q = gTxCtoQueue;
            } else if (xQueuePeek(gTxQueue, &f, 0) == pdTRUE) {
                q = gTxQueue;
            } else {
                break;
            }
            if (fill + f.len > sizeof(batch)) {
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
            send_fail_run = 0;
        }
        /* Master supervision: nothing has been sendable for a while, or (if
         * enabled) the master has been silent too long while we stream. */
        int lost = (send_fail_run >= (uint32_t)XCP_GATEWAY_SEND_FAIL_LIMIT);
#if XCP_GATEWAY_MASTER_TIMEOUT_MS > 0
        if ((TickType_t)(xTaskGetTickCount() - gMasterLastRxTick) > pdMS_TO_TICKS(XCP_GATEWAY_MASTER_TIMEOUT_MS)) {
            lost = 1;
        }
#endif
        if (lost && gMasterValid) {
            send_fail_run = 0;
            xcp_gw_master_lost_disconnect();
        }
    }
}

/*--------------------------------------------------------------------------
 * Init: UDP socket on XCP_GATEWAY_UDP_PORT, the three queues, and the tasks.
 * Call once the lwIP interface is up (like the JavaScope/XCPlite server).
 * Returns 0 on success.
 *------------------------------------------------------------------------*/
int xcp_gateway_a53_init(uint32_t thread_stack, uint32_t thread_prio) {
    gRxQueue = xQueueCreate(XCP_GW_RXQ_DEPTH, sizeof(xcp_gw_frame_t));
    gTxQueue = xQueueCreate(XCP_GW_TXQ_DEPTH, sizeof(xcp_gw_frame_t));
    gTxCtoQueue = xQueueCreate(XCP_GW_CTOQ_DEPTH, sizeof(xcp_gw_frame_t));
    gTxSignal = xSemaphoreCreateBinary();
    if (gRxQueue == NULL || gTxQueue == NULL || gTxCtoQueue == NULL || gTxSignal == NULL) {
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

    ocm_xcp_fifo_init(); /* A53 initialises XCP_OUT (the region it reads)       */

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
    gGwReady = 1; /* from here on the IPI ISR may touch the queues/FIFO */
    return 0;
}
