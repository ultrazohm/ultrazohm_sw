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
|   - T8: reads from XCP_OUT are staged locally and committed only under a
|     passing seqlock check — torn frames never reach the network. Command
|     responses arrive via the acknowledged CTO mailbox (exactly-once).
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
#include "lwip/sockets.h"
#include "lwip/sys.h"   /* sys_thread_new */
#include "ocm_xcp_fifo.h"
#include <string.h>
#include <stdint.h>

#ifndef XCP_GATEWAY_UDP_PORT
#define XCP_GATEWAY_UDP_PORT 5556
#endif
#define XCP_GW_FRAME_MAX     256  /* FIFO records are uint8_t-len capped        */
#define XCP_TL_HEADER_LEN    4    /* [dlc:u16][ctr:u16]                          */
#define XCP_PID_CTO_MIN      0xFCu

/* DAQ (DTO) queue: deep on purpose — it is the burst absorber between the
 * 10–20 kHz OCM drain and the UDP send rate, and measurement gaps hurt more
 * than backlog latency. Sized to bridge multi-second send stalls, matching
 * hedrive's final sizing (its rig saw ~2 s host receive pauses every few
 * minutes that a 140 ms queue could not absorb): 262144 x ~260 B ≈ 68 MB of
 * the 200 MB FreeRTOS heap ≈ 1.5 s of buffering at the 320 Mbit/s stress
 * rate (~3 s at 160 Mbit/s). The queue runs empty in steady state, so normal
 * latency is unaffected. NOTE: UDP has no backpressure — this queue covers
 * ECU-side stalls (lwIP pbuf/ARP, task starvation); PC-side receive pauses
 * must be absorbed by the receiver's socket buffer (xcp_poll.py sets 32 MB).
 * Overflow policy: tail-drop + count, never purge, never block from the ISR. */
#define XCP_GW_TXQ_DEPTH     262144
/* Dedicated queue for CTO frames (RES/ERR/EV/SERV): responses must never
 * wait behind — or be dropped with — the DAQ backlog (hedrive T1). */
#define XCP_GW_CTOQ_DEPTH    16
#define XCP_GW_RXQ_DEPTH     64

/* Bound the IPI-ISR time: max records staged OCM -> queues per interrupt.
 * XCP_OUT holds ~28 max-size records; the cap only bites on many tiny ones. */
#define XCP_GW_DRAIN_MAX_PER_IPI 32

/* Command batch offered to the R5 per generation (bounded by the XCP_IN
 * chain: 3 x (4 + 255) + terminator < OCM_XCP_IN_CHAIN_LEN). */
#define XCP_GW_IN_BATCH_MAX  3

/* TX batching: pack queued TL frames into one UDP datagram (several XCP
 * messages per datagram are standard XCP-on-Ethernet; XCPlite's own PC
 * transport does the same). 1400 keeps datagram + UDP/IP headers under a
 * 1500-byte MTU — no IP fragmentation. */
#define XCP_GW_BATCH_BUF_SIZE 1400

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
static int           gSock      = -1;

/* The IPI ISR is registered by initialize_ipi_runtime() long before this
 * gateway is initialised (network-up/DHCP), while the R5 fires an IPI every
 * control cycle from boot. Guard the ISR path until init completed. */
static volatile int gGwReady = 0;

static struct sockaddr_in gMaster;           /* last master (CANape) endpoint   */
static volatile int       gMasterValid = 0;
static volatile uint32_t  gMasterGen = 0;    /* bumped on endpoint change       */

/* Diagnostics (inspect via debugger; hedrive validation-checklist counters):
 *   xcp_gw_ocm_skipped_writing IPI hit the R5 mid-write (odd seqlock)
 *   xcp_gw_ocm_torn            R5 rewrote XCP_OUT mid-read; cycle discarded
 *   xcp_gw_ocm_cycles_missed   R5 cycles never seen by any IPI read
 *   xcp_gw_ocm_capped          per-IPI drain cap hit with records left over
 *   xcp_gw_txq_dropped         DAQ queue full -> record tail-dropped
 *   xcp_gw_ctoq_dropped        CTO queue full -> frame dropped (must stay 0)
 *   xcp_gw_in_batches_sent     command batches (generations) offered to the R5
 *   xcp_gw_in_retry_cycles     IPIs spent re-offering an unconsumed batch
 *   xcp_gw_tx_malformed_drop   record failed the TL-frame walk on TX (must stay 0)
 *   xcp_gw_sendto_err          transient lwip_sendto() failures (pbuf/TX-BD
 *                              exhaustion under burst load; observed 74x in a
 *                              60 s 320 Mbit/s run). Retried, so err alone is
 *                              pressure, not loss.
 *   xcp_gw_sendto_drop         batch still failing after the bounded retries —
 *                              the batch was already CTR-stamped, so each one
 *                              is a wire counter gap and the ONLY ECU-side
 *                              source of them. Gaps with this at 0 mean the
 *                              loss is wire/PC-side. Must stay 0. */
volatile uint32_t xcp_gw_ocm_skipped_writing = 0;
volatile uint32_t xcp_gw_ocm_torn = 0;
volatile uint32_t xcp_gw_ocm_cycles_missed = 0;
volatile uint32_t xcp_gw_ocm_capped = 0;
volatile uint32_t xcp_gw_txq_dropped = 0;
volatile uint32_t xcp_gw_ctoq_dropped = 0;
volatile uint32_t xcp_gw_in_batches_sent = 0;
volatile uint32_t xcp_gw_in_retry_cycles = 0;
volatile uint32_t xcp_gw_tx_malformed_drop = 0;
volatile uint32_t xcp_gw_sendto_err = 0;
volatile uint32_t xcp_gw_sendto_drop = 0;

/*--------------------------------------------------------------------------
 * IPI ISR — read phase (XCP_OUT -> queues), seqlock-guarded.
 * All buffers static: this runs only in the (non-reentrant) IPI ISR, and the
 * staging area is far too big for an ISR stack frame.
 *------------------------------------------------------------------------*/
static xcp_gw_frame_t gStage[XCP_GW_DRAIN_MAX_PER_IPI];
static xcp_gw_frame_t gStageCto;
static uint32_t gCtoLastSeq = 0;         /* last mailbox seq forwarded (acked)  */
static uint32_t gInConsumed = 0;         /* R5 batch ack, valid under seqlock   */
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
    uint32_t n_staged = 0;
    int      capped = 0;

    /* Seqlock begin: odd = the R5 is rewriting the window right now. */
    uint32_t seq_begin = ocm_xcp_out_seq_read();
    if (seq_begin & 1u) {
        xcp_gw_ocm_skipped_writing++;
        return;
    }

    /* Stage the CTO mailbox (persists across cycles until acked) and the
     * R5's command-batch ack; both live in the seqlock-guarded header. */
    uint32_t in_consumed_snap = ocm_xcp_in_consumed_read();
    if (ocm_xcp_cto_read(&cto_len, gStageCto.data, &cto_seq)) {
        if (cto_seq != gCtoLastSeq) {
            have_cto = 1;
        }
    }

    /* Stage the DAQ message chain. */
    ocm_xcp_fifo_prepare_read();
    for (;;) {
        uint8_t len;
        uint8_t *data;
        if (n_staged >= XCP_GW_DRAIN_MAX_PER_IPI) {
            capped = 1; /* rest of this cycle is lost; R5 rewinds next cycle */
            break;
        }
        if (!ocm_xcp_fifo_read(&len, &data)) {
            break; /* end of chain (or bounds guard tripped) */
        }
        gStage[n_staged].len = len;
        memcpy(gStage[n_staged].data, data, len);
        n_staged++;
    }

    /* Seqlock end: if the R5 started a new cycle while we were reading, every
     * staged byte is potentially a mix of two cycles — discard it all. The
     * data is gone either way (the window is being rewritten); what matters
     * is that torn frames never reach the network (hedrive T8). */
    if (!ocm_xcp_out_seq_unchanged(seq_begin)) {
        xcp_gw_ocm_torn++;
        return;
    }

    /* Committed: the staged data is a consistent snapshot of cycle seq_begin. */
    gInConsumed = in_consumed_snap;
    if (gPrevSeqValid) {
        uint32_t delta = seq_begin - gPrevSeq; /* wrap-safe */
        if (delta > 2u) {
            xcp_gw_ocm_cycles_missed += (delta - 2u) / 2u;
        }
    }
    gPrevSeq = seq_begin;
    gPrevSeqValid = 1;
    if (capped) {
        xcp_gw_ocm_capped++;
    }

    if (gCtoAdoptPending) {
        /* Session change: whatever sits in the mailbox predates it. */
        gCtoLastSeq = cto_seq;
        gCtoAdoptPending = 0;
        have_cto = 0;
    }

    if (have_cto) {
        gCtoLastSeq = cto_seq; /* acked via the write phase this IPI */
        gStageCto.len = cto_len;
        if (xQueueSendToBackFromISR(gTxCtoQueue, &gStageCto, woken) != pdTRUE) {
            xcp_gw_ctoq_dropped++;
        }
    }

    if (!gMasterValid) {
        return; /* no consumer: drop staged DAQ (the CTO ack still advances) */
    }

    for (uint32_t i = 0; i < n_staged; i++) {
        /* Defensive classify by XCP PID: CTO packets that travelled the chain
         * (EV/SERV from the R5 queue) jump the DAQ backlog too. */
        if (gStage[i].len > XCP_TL_HEADER_LEN &&
            gStage[i].data[XCP_TL_HEADER_LEN] >= XCP_PID_CTO_MIN) {
            if (xQueueSendToBackFromISR(gTxCtoQueue, &gStage[i], woken) != pdTRUE) {
                xcp_gw_ctoq_dropped++;
            }
            continue;
        }
        if (xQueueSendToBackFromISR(gTxQueue, &gStage[i], woken) != pdTRUE) {
            /* DAQ queue full: the UDP drain has stalled for longer than the
             * queue depth covers. Tail-drop and count. Never block, delay or
             * print here — ISR context (hedrive F1). */
            xcp_gw_txq_dropped++;
        }
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
        if (!ocm_xcp_fifo_write((uint8_t)gInBatch[i].len, gInBatch[i].data)) {
            break; /* cannot happen (batch sized to the region); defensive */
        }
    }
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
    xcp_gw_read_out_phase(pxHigherPriorityTaskWoken);
    xcp_gw_write_in_phase(pxHigherPriorityTaskWoken);
}

/*--------------------------------------------------------------------------
 * RX task: receive XCP-on-UDP datagrams from CANape, remember the master
 * endpoint, and hand the frame to the IPI ISR via gRxQueue.
 *------------------------------------------------------------------------*/
static void xcp_gw_rx_task(void *arg) {
    (void)arg;
    static xcp_gw_frame_t f; /* only this task uses it */
    struct sockaddr_in src;
    socklen_t slen;
    for (;;) {
        slen = sizeof(src);
        int n = lwip_recvfrom(gSock, f.data, sizeof(f.data), 0, (struct sockaddr *)&src, &slen);
        if (n <= 0 || n > 255) {
            continue; /* FIFO records are u8-length capped; oversize would alias to len 0 */
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

static void xcp_gw_tx_task(void *arg) {
    (void)arg;
    static xcp_gw_frame_t f;                       /* only this task uses them */
    static uint8_t batch[XCP_GW_BATCH_BUF_SIZE];
    uint32_t my_master_gen = 0;

    for (;;) {
        if (my_master_gen != gMasterGen) {
            /* New session: the queued DAQ backlog belongs to the old one.
             * (CTO queue is NOT reset: it may already hold the response to
             * the new master's first command.) */
            my_master_gen = gMasterGen;
            xQueueReset(gTxQueue);
            gTxCtr = 0;
        }

        uint32_t fill = 0;

        /* Block until something is sendable: pending CTOs first, else wait
         * briefly for DAQ so an idle connection still reacts to a CTO or a
         * master change within ~20 ms. */
        if (xQueueReceive(gTxCtoQueue, &f, 0) != pdTRUE) {
            if (xQueueReceive(gTxQueue, &f, pdMS_TO_TICKS(20)) != pdTRUE) {
                continue;
            }
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
        for (int attempt = 0; attempt <= XCP_GW_SEND_RETRY_MAX; attempt++) {
            if (attempt != 0) {
                vTaskDelay(1); /* one tick: GEM drains its TX ring by hardware */
            }
            sent = lwip_sendto(gSock, batch, fill, 0, (struct sockaddr *)&dst, sizeof(dst));
            if (sent >= 0) {
                break;
            }
            xcp_gw_sendto_err++;
        }
        if (sent < 0) {
            xcp_gw_sendto_drop++; /* stamped frames lost -> wire CTR gap */
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
    if (gRxQueue == NULL || gTxQueue == NULL || gTxCtoQueue == NULL) {
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
    gGwReady = 1; /* from here on the IPI ISR may touch the queues/FIFO */
    return 0;
}
