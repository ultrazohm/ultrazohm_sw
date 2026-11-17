/*----------------------------------------------------------------------------
| ocm_xcp_fifo.c
|   Option Z — OCM exchange between the R5 (XCPlite engine) and the A53
|   (gateway). ONE shared implementation; the side is chosen by the ARMR5
|   define. The OCM layout below is the protocol between the two cores:
|   when it changes, rebuild BOTH applications.
|
|   The R5 rewrites XCP_OUT every exchange sweep and the A53 reads it from
|   its IPI ISR. Whenever the A53 is late (IPI latency under network load),
|   the R5 touches the region mid-read. Three mechanisms, ported from the
|   hedrive hardware campaign (XCP_BOTTLENECK_ANALYSIS.md T8 + pcap
|   addendum), make that safe; a fourth and a fifth (ours) make the DAQ chain
|   lossless and its reads robust under load:
|
|   1. A seqlock on the XCP_OUT header: the R5 increments cycle_seq to an ODD
|      value (flushed) before touching the region and to an EVEN value
|      (flushed last, after the payload flush) when the sweep is complete.
|      The A53 copies the header words and the CTO mailbox between two
|      samples of the sequence; a mismatch or an odd value means the copy
|      raced the writer, and it is retried with the next IPI. The DAQ chain
|      is validated separately (5), so torn frames still never reach the
|      network.
|
|   2. A CTO mailbox with an acknowledge: command responses (RES/ERR/EV/SERV)
|      must NEVER be lost — a lost response kills the XCP session (master
|      request timeout). The response is parked in a dedicated slot with its
|      own sequence number and stays there, surviving any number of cycle
|      rewrites, until the A53 acknowledges the sequence through the XCP_IN
|      header. Delivery is exactly-once: the A53 forwards a mailbox frame only
|      when its sequence changes.
|
|   3. A generation handshake on XCP_IN (commands, A53 -> R5): the A53 keeps
|      the current command batch IN PLACE and rewrites it every IPI cycle,
|      publishing a generation number (in_gen) AFTER the chain bytes. The R5
|      processes a generation exactly once (in_gen != last processed) and
|      acknowledges it through in_consumed in the XCP_OUT header; only then
|      does the A53 build the next batch. A command can therefore never be
|      lost to a missed cycle (observed in hedrive as CANape "Timeout: Keine
|      Response" with a perfectly clean wire capture) nor executed twice.
|
|   4. A consumption handshake on the XCP_OUT chain (DAQ, R5 -> A53): every
|      time the R5 rewinds the chain it bumps chain_seq; the A53 forwards a
|      chain only when its sequence is new and publishes the sequence it has
|      consumed as out_ack in the XCP_IN header. The R5 keeps a NON-EMPTY
|      chain in place (header words still update under the seqlock) until
|      it is acknowledged, so an IPI read that came late, was torn or hit an
|      odd seqlock is simply repeated with the next IPI: the DAQ backlog
|      waits in the R5 queue instead of being overwritten. Since 2026-11-18
|      the R5 does not even open a DAQ exchange before the acknowledge
|      (header-only exchanges for commands keep the chain); the hold is
|      bounded by the caller (xcptl_ocm.c) so a dead gateway cannot stall the
|      R5.
|
|   5. Chain validation by chain_seq instead of the seqlock (2026-11-17):
|      before it touches any chain byte, the R5 sets chain_seq to 0 together
|      with the odd cycle_seq (same control line, one flush), and it
|      publishes the new chain_seq only after the chain bytes are flushed. A
|      non-zero chain_seq therefore always describes a complete chain in the
|      OCM - even if a dirty cache line is evicted early. The A53 reads
|      chain_seq, the chain and chain_seq again; the same non-zero value
|      proves a consistent read. A sweep that only KEEPS the chain (4) bumps
|      cycle_seq for its header words but leaves chain_seq and the chain
|      alone, so a read of a kept chain that takes longer than a sweep is no
|      longer thrown away. Before, under load about half of all A53 reads
|      were discarded that way and the throughput collapsed (bench at 40 kHz
|      control rate, 2026-11-17).
|
|   XCP_OUT layout (R5 writes, A53 reads):
|     +0    u32 cycle_seq    seqlock (odd = write in progress)
|     +4    u32 cto_seq      mailbox sequence, 0 = never used
|     +8    u32 cto_len      framed length of the mailbox message
|     +12   u32 in_consumed  last XCP_IN generation processed by the R5
|     +16   u32 chain_seq    sequence of the chain content (4 and 5);
|                            0 = no valid chain (being rewritten)
|     +64   u8  cto_frame[OCM_XCP_CTO_SLOT_LEN]   (own cache lines)
|     +320  message chain (see below)
|
|   XCP_IN layout (A53 writes, R5 reads):
|     +0    u32 cto_ack      last mailbox sequence consumed by the A53
|     +4    u32 in_gen       command-batch generation, 0 = none;
|                            published AFTER the chain bytes
|     +8    u32 diag[]       A53 gateway counter mirror (slot table in
|                            ocm_xcp_fifo.h); rewritten every IPI, read by
|                            the XCP master by absolute address
|     +124  u32 out_ack      last XCP_OUT chain_seq consumed by the A53
|     +128  message chain
|
|   Message chain format (unchanged from the original FIFO):
|     [0..3]   message length (u32)
|     [4..]    payload (XCP-on-Ethernet TL frame(s): [dlc:u16][ctr:u16][pkt])
|     [..]     trailing u32 = 0  (end-of-chain; overwritten by the next msg)
|
|   Adapted from uz_sw_xcp_hedrive_andi RPU_APU_exchange (Jens Wenzl, 2023),
|   hardware-proven incl. the seqlock/mailbox/generation fixes from its
|   bottleneck analysis. UltraZohm, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "ocm_xcp_fifo.h"
#include <stddef.h>
#include <string.h>
#include "xil_cache.h"

#ifdef ARMR5
#define OCM_XCP_RPU
#else
#define OCM_XCP_APU
#endif

/* OCM regions in bank 3 (0xFFFF0000, 64 KB). JavaScope, which is off under
 * XCP, only uses the first bytes of the bank (its data struct and the boot
 * version words), so the rest is free:
 *   0xFFFF4000  XCP_OUT (R5 -> A53): DAQ + command responses, 32 KB
 *   0xFFFFC000  XCP_IN  (A53 -> R5): commands, 1 KB (address is fixed in the
 *               A2L through the gateway counter mirror - do not move)
 * XCP_OUT was 7.5 KB at 0xFFFFE000 until 2026-11: with the consumption
 * handshake a held sweep leaves a backlog in the R5 queue, and the window
 * size is what bounds how fast one sweep can work that backlog off. */
#define XCP_OUT_ADDR 0xFFFF4000u
#define XCP_OUT_LEN  0x8000u
#define XCP_IN_ADDR  0xFFFFC000u
#define XCP_IN_LEN   1024u
#if (XCP_OUT_ADDR + XCP_OUT_LEN) > XCP_IN_ADDR
#error "XCP_OUT overlaps XCP_IN"
#endif

/* Header in front of each message chain. The control words live in the first
 * 64 bytes (one A53 cache line), so they never share a line with chain bytes:
 * that separation is what makes the publish-after-payload flush order real.
 * The XCP_OUT mailbox frame slot is too big for the control line (XCPlite CRM
 * frames are up to 4+248 bytes) and occupies its own lines behind it. */
#define XCP_OUT_HDR_CTRL_LEN 64u
#define XCP_OUT_HDR_LEN      (XCP_OUT_HDR_CTRL_LEN + OCM_XCP_CTO_SLOT_LEN)
#define XCP_IN_HDR_LEN       128u

#define XCP_OUT_CHAIN_ADDR (XCP_OUT_ADDR + XCP_OUT_HDR_LEN)
#define XCP_IN_CHAIN_ADDR  (XCP_IN_ADDR + XCP_IN_HDR_LEN)

#define XCP_OUT_CYCLE_SEQ_P   ((volatile uint32_t *)(XCP_OUT_ADDR + 0u))
#define XCP_OUT_CTO_SEQ_P     ((volatile uint32_t *)(XCP_OUT_ADDR + 4u))
#define XCP_OUT_CTO_LEN_P     ((volatile uint32_t *)(XCP_OUT_ADDR + 8u))
#define XCP_OUT_IN_CONSUMED_P ((volatile uint32_t *)(XCP_OUT_ADDR + 12u))
#define XCP_OUT_CHAIN_SEQ_P   ((volatile uint32_t *)(XCP_OUT_ADDR + 16u))
/* cycle_seq .. chain_seq: inside the first cache line on both cores
 * (R5 32 B, A53 64 B), so one flush / invalidate covers all of them. */
#define XCP_OUT_SEQ_WORDS_LEN 20u
#define XCP_OUT_CTO_FRAME_ADDR (XCP_OUT_ADDR + XCP_OUT_HDR_CTRL_LEN)
#define XCP_IN_CTO_ACK_P      ((volatile uint32_t *)(XCP_IN_ADDR + 0u))
#define XCP_IN_GEN_P          ((volatile uint32_t *)(XCP_IN_ADDR + 4u))
#define XCP_IN_DIAG_P(i)      ((volatile uint32_t *)(uintptr_t)(XCP_IN_ADDR + 8u + 4u * (i)))
#define XCP_IN_OUT_ACK_P      ((volatile uint32_t *)(XCP_IN_ADDR + XCP_IN_HDR_LEN - 4u))

/* The mailbox slot address laundered through a volatile: memcpy() to/from a
 * literal address makes GCC treat it as a zero-size object (-Warray-bounds). */
static volatile size_t cto_frame_addr = XCP_OUT_CTO_FRAME_ADDR;

#if (XCP_IN_LEN - XCP_IN_HDR_LEN) != OCM_XCP_IN_CHAIN_LEN
#error "OCM_XCP_IN_CHAIN_LEN out of sync with the XCP_IN layout"
#endif
#if (OCM_XCP_IN_DIAG_ADDR != (XCP_IN_ADDR + 8u)) || ((8u + 4u * OCM_XCP_IN_DIAG_COUNT) > (XCP_IN_HDR_LEN - 4u))
#error "OCM_XCP_IN_DIAG_* out of sync with the XCP_IN header layout"
#endif

/* R5 write side reserves the tail of XCP_OUT for CTO frames (XCP PID >= 0xFC:
 * RES/ERR/EV/SERV) so a DAQ burst can never starve a command response in the
 * chain. With the mailbox, command responses normally bypass the chain
 * entirely; the reserve stays as a second line of defense for queued CTO
 * packets (EV/SERV). Must hold one max-size record: 4 + (4+248) + 4 = 260. */
#ifdef OCM_XCP_RPU
#define XCP_WRITE_CTO_RESERVE 512u
#else
#define XCP_WRITE_CTO_RESERVE 0u
#endif

/* R5: largest piece of the chain flushed with interrupts masked (see
 * ocm_xcp_fifo_cache_flush_after_write). A multiple of the 32-byte line. */
#define XCP_OUT_FLUSH_CHUNK 1024u

#define XCP_FRAME_PID_OFFSET 4u   /* [0..1] len, [2..3] ctr, [4] = XCP PID */
#define XCP_FRAME_PID_CTO_MIN 0xFCu

static volatile size_t addr_w = 0;
static volatile size_t addr_w_start = 0;
static volatile size_t addr_w_end = 0;
static volatile size_t addr_r = 0;
static volatile size_t addr_r_end = 0;

#ifdef OCM_XCP_RPU
/* Writer-side shadows of the XCP_OUT sequence words (the R5 owns them and
 * never needs to read them back from the OCM). */
static uint32_t cycle_seq_shadow = 0;
static uint32_t cto_seq_shadow = 0;
static uint32_t chain_seq_shadow = 0;
/* A rewritten chain's new sequence waits for the chain flush (mechanism 5). */
static int chain_seq_publish = 0;
#endif

volatile uint32_t ocm_xcp_w_dropped = 0;   /* write region full -> dropped     */
volatile uint32_t ocm_xcp_r_overrun = 0;   /* read chain corrupt / past region */

void ocm_xcp_fifo_init(void) {
    /* The core that READS a region initialises it. */
#ifdef OCM_XCP_RPU
    *XCP_IN_CTO_ACK_P = 0u;
    *XCP_IN_GEN_P = 0u;
    *XCP_IN_OUT_ACK_P = 0u;
    *(volatile uint32_t *)XCP_IN_CHAIN_ADDR = 0u;
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#else
    *XCP_OUT_CYCLE_SEQ_P = 0u;
    *XCP_OUT_CTO_SEQ_P = 0u;
    *XCP_OUT_CTO_LEN_P = 0u;
    *XCP_OUT_IN_CONSUMED_P = 0u;
    *XCP_OUT_CHAIN_SEQ_P = 0u;
    *(volatile uint32_t *)XCP_OUT_CHAIN_ADDR = 0u;
    Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_LEN);
#endif
}

void ocm_xcp_fifo_cache_invalidate_before_read(void) {
#ifdef OCM_XCP_RPU
    /* XCP_IN is small: refresh it in one go. Covers the cto_ack word read by
     * ocm_xcp_cto_mailbox_free() and the in_gen word read by
     * ocm_xcp_in_gen_read(). (The R5 never dirties these lines after init,
     * so flush = clean + invalidate behaves as an invalidate.) */
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_LEN);
#endif
    /* APU: intentionally empty — XCP_OUT is several KB and this runs in the
     * IPI ISR at the control rate. ocm_xcp_fifo_read() invalidates lazily per
     * message; the control line is invalidated by ocm_xcp_out_seq_read(). */
}

void ocm_xcp_fifo_cache_flush_after_write(void) {
#ifdef OCM_XCP_RPU
    /* Publish order matters: payload first, sequence word last. A reader that
     * sees the new (even) cycle_seq must also see the chain content it
     * describes; flushing the header before the chain would break that.
     * The chain is flushed in 1 KB pieces: Xil_DCacheFlushRange() masks
     * IRQ/FIQ for the whole range it is given, and this runs in the main
     * loop underneath the control ISR - one 32 KB call would hold the ISR
     * off for the entire window. */
    {
        size_t a = addr_w_start;
        const size_t end = addr_w + 4u;
        while (a < end) {
            size_t n = end - a;
            if (n > XCP_OUT_FLUSH_CHUNK) {
                n = XCP_OUT_FLUSH_CHUNK;
            }
            Xil_DCacheFlushRange(a, n);
            a += n;
        }
    }
    if (chain_seq_publish) {
        /* The chain bytes are in the OCM (the flush above ends with a DSB):
         * only now may the chain become valid. */
        *XCP_OUT_CHAIN_SEQ_P = chain_seq_shadow;
        chain_seq_publish = 0;
    }
    cycle_seq_shadow++; /* even: cycle content is complete */
    *XCP_OUT_CYCLE_SEQ_P = cycle_seq_shadow;
    Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_HDR_CTRL_LEN);
#else
    /* Publish order matters here too: chain bytes first, header (with the
     * in_gen generation word) last. The R5 accepting a new generation must
     * imply the chain content it describes is complete in the OCM. */
    Xil_DCacheFlushRange(addr_w_start, (addr_w + 4u) - addr_w_start);
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_HDR_LEN);
#endif
}

void ocm_xcp_fifo_prepare_read(void) {
#ifdef OCM_XCP_RPU
    addr_r = XCP_IN_CHAIN_ADDR;
    addr_r_end = XCP_IN_ADDR + XCP_IN_LEN;
#else
    addr_r = XCP_OUT_CHAIN_ADDR;
    addr_r_end = XCP_OUT_ADDR + XCP_OUT_LEN;
#endif
}

void ocm_xcp_fifo_prepare_write(void) {
#ifdef OCM_XCP_RPU
    /* Seqlock write-begin: publish an ODD sequence before touching the
     * region, so a concurrently reading A53 knows the header is in flux.
     * The chain is rewritten as well: chain_seq 0 = "no valid chain". Both
     * words sit in the first control line, so this one flush publishes both
     * BEFORE any chain byte changes (mechanism 5). */
    cycle_seq_shadow++;
    *XCP_OUT_CYCLE_SEQ_P = cycle_seq_shadow;
    *XCP_OUT_CHAIN_SEQ_P = 0u;
    Xil_DCacheFlushRange(XCP_OUT_ADDR, XCP_OUT_SEQ_WORDS_LEN);

    addr_w = XCP_OUT_CHAIN_ADDR;
    addr_w_start = XCP_OUT_CHAIN_ADDR; /* header is flushed separately (last) */
    addr_w_end = XCP_OUT_ADDR + XCP_OUT_LEN;
    /* New chain content: new sequence (0 is reserved for "no valid chain").
     * Written to the OCM by cache_flush_after_write() only after the chain
     * bytes are flushed - never earlier, not even by a cache eviction. */
    chain_seq_shadow++;
    if (chain_seq_shadow == 0u) {
        chain_seq_shadow = 1u;
    }
    chain_seq_publish = 1;
#else
    addr_w = XCP_IN_CHAIN_ADDR;
    addr_w_start = XCP_IN_CHAIN_ADDR;  /* header is flushed separately (last) */
    addr_w_end = XCP_IN_ADDR + XCP_IN_LEN;
#endif
    *(volatile uint32_t *)addr_w = 0u;
}

#ifdef OCM_XCP_RPU
/* Open a cycle but keep the unacknowledged chain exactly as it is: only the
 * seqlock goes odd. addr_w still points at the chain terminator; start and
 * end are pulled onto it so nothing can be appended (an append could race
 * the A53 between its read and its acknowledge and would be lost) and the
 * closing chain flush shrinks to the terminator word. */
void ocm_xcp_fifo_prepare_write_keep(void) {
    if (addr_w == 0u) {
        ocm_xcp_fifo_prepare_write(); /* no chain written yet: nothing to keep */
        return;
    }
    cycle_seq_shadow++;
    *XCP_OUT_CYCLE_SEQ_P = cycle_seq_shadow;
    Xil_DCacheFlushRange(XCP_OUT_ADDR, 4u);
    addr_w_start = addr_w;
    addr_w_end = addr_w;
}

int ocm_xcp_fifo_chain_nonempty(void) {
    return addr_w != addr_w_start;
}

int ocm_xcp_out_chain_acked(void) {
    return (*XCP_IN_OUT_ACK_P == chain_seq_shadow);
}

void ocm_xcp_in_refresh_header(void) {
    /* The R5 never dirties XCP_IN after init: flush = invalidate here. */
    Xil_DCacheFlushRange(XCP_IN_ADDR, XCP_IN_HDR_LEN);
}
#endif /* OCM_XCP_RPU */

int ocm_xcp_fifo_write_fits(uint16_t len, const uint8_t *data) {
    size_t limit = addr_w_end;

    /* DAQ (DTO) frames must leave the CTO reserve free; CTO frames may use it.
     * Frames too short to carry a PID are treated as DAQ. */
    if ((len <= XCP_FRAME_PID_OFFSET) || (data[XCP_FRAME_PID_OFFSET] < XCP_FRAME_PID_CTO_MIN)) {
        limit -= XCP_WRITE_CTO_RESERVE;
    }

    if ((len == 0u) || (len > OCM_XCP_RECORD_MAX)) {
        return 0; /* the reader would reject it as corrupt */
    }
    /* Need 4 (len) + len (payload) + 4 (terminator). In a keep cycle
     * (prepare_write_keep) addr_w_end == addr_w, so this is always false. */
    return (addr_w + 4u + (size_t)len + 4u) <= limit;
}

int ocm_xcp_fifo_write(uint16_t len, const uint8_t *data) {
    uint8_t *dst_p = (uint8_t *)(addr_w);

    if (!ocm_xcp_fifo_write_fits(len, data)) {
        ocm_xcp_w_dropped++;
        return 0;
    }

    *(volatile uint32_t *)dst_p = len;
    dst_p += 4;
    memcpy(dst_p, data, len);
    dst_p += len;
    *(volatile uint32_t *)dst_p = 0u; /* new end-of-chain marker */

    addr_w = (size_t)dst_p;
    return 1;
}

int ocm_xcp_fifo_read(uint16_t *len, uint8_t **data_p) {
    uint8_t *src_p = (uint8_t *)(addr_r);
    uint32_t msg_len;

    if (((size_t)src_p + 4u) > addr_r_end) {
        ocm_xcp_r_overrun++;
        return 0;
    }
#ifdef OCM_XCP_APU
    /* Lazy invalidate: the A53 never dirties XCP_OUT lines, so invalidating
     * only the message actually being read is safe and cheap. */
    Xil_DCacheInvalidateRange((size_t)src_p, 4u);
#endif
    msg_len = *(volatile uint32_t *)src_p;

    if (msg_len == 0u) {
        return 0; /* end of chain */
    }
    if ((msg_len > OCM_XCP_RECORD_MAX) || (((size_t)src_p + 4u + msg_len) > addr_r_end)) {
        ocm_xcp_r_overrun++;
        return 0;
    }
#ifdef OCM_XCP_APU
    Xil_DCacheInvalidateRange((size_t)src_p + 4u, msg_len);
#endif

    *len = (uint16_t)msg_len;
    src_p += 4;
    *data_p = src_p;
    src_p += msg_len;
    addr_r = (size_t)src_p;
    return 1;
}

/*-------------------------------------------------------------------
 * R5 side: CTO mailbox write + command generations
 *-----------------------------------------------------------------*/
#ifdef OCM_XCP_RPU
/* The mailbox is free once the A53 has acknowledged the last sequence. */
int ocm_xcp_cto_mailbox_free(void) {
    return (*XCP_IN_CTO_ACK_P == cto_seq_shadow);
}

/* Park one framed CTO message. The slot lines are flushed here; the control
 * words (cto_seq/cto_len) travel with the header flush at the end of the
 * cycle, so the A53 only sees the new sequence together with a complete
 * frame — and only under a passing seqlock check. */
int ocm_xcp_cto_write(uint8_t len, const uint8_t *data) {
    /* len is u8 (<= 255) and the slot holds 256: a framed CRM always fits. */
    if (len == 0u) {
        return 0;
    }
    memcpy((void *)cto_frame_addr, data, len);
    Xil_DCacheFlushRange(XCP_OUT_CTO_FRAME_ADDR, len);
    *XCP_OUT_CTO_LEN_P = len;
    cto_seq_shadow++;
    if (cto_seq_shadow == 0u) {
        cto_seq_shadow = 1u; /* 0 is reserved for "never used" */
    }
    *XCP_OUT_CTO_SEQ_P = cto_seq_shadow;
    return 1;
}

/* Current command-batch generation published by the A53. The A53 publishes
 * the generation only after the chain bytes are in the OCM, so a new value
 * here implies a complete, readable command chain. */
uint32_t ocm_xcp_in_gen_read(void) {
    return *XCP_IN_GEN_P;
}

/* Acknowledge a processed command-batch generation. Lands in the XCP_OUT
 * header, published by the header flush in cache_flush_after_write(). */
void ocm_xcp_in_consumed_write(uint32_t gen) {
    *XCP_OUT_IN_CONSUMED_P = gen;
}
#endif /* OCM_XCP_RPU */

/*-------------------------------------------------------------------
 * A53 side: seqlock + CTO mailbox read + command generations
 *-----------------------------------------------------------------*/
#ifdef OCM_XCP_APU
uint32_t ocm_xcp_out_seq_read(void) {
    /* Invalidating the control-line start refreshes the whole 64-byte line
     * (cycle_seq, cto_seq, cto_len, in_consumed). */
    Xil_DCacheInvalidateRange(XCP_OUT_ADDR, 4u);
    return *XCP_OUT_CYCLE_SEQ_P;
}

int ocm_xcp_out_seq_unchanged(uint32_t seq_begin) {
    Xil_DCacheInvalidateRange(XCP_OUT_ADDR, 4u);
    return (*XCP_OUT_CYCLE_SEQ_P == seq_begin);
}

/* Copy the mailbox frame. Returns 1 if the slot holds a plausible frame
 * (nonzero seq, valid length), 0 otherwise. Must be called between
 * out_seq_read() and out_seq_unchanged(); the copy is only trustworthy if
 * the surrounding seqlock check passes. */
int ocm_xcp_cto_read(uint8_t *len, uint8_t *dst, uint32_t *seq) {
    uint32_t s = *XCP_OUT_CTO_SEQ_P;
    uint32_t l = *XCP_OUT_CTO_LEN_P;

    if ((s == 0u) || (l == 0u) || (l > OCM_XCP_CTO_SLOT_LEN)) {
        return 0;
    }
    Xil_DCacheInvalidateRange(XCP_OUT_CTO_FRAME_ADDR, l);
    memcpy(dst, (const void *)cto_frame_addr, l);
    *len = (uint8_t)l;
    *seq = s;
    return 1;
}

/* Publish the last consumed mailbox sequence. Written into the XCP_IN header
 * during the write phase; reaches the OCM with cache_flush_after_write(). */
void ocm_xcp_cto_ack_write(uint32_t seq) {
    *XCP_IN_CTO_ACK_P = seq;
}

/* Publish the command-batch generation. Written during the write phase; the
 * split flush in cache_flush_after_write() guarantees the chain bytes reach
 * the OCM before this word does (publish-after-payload). */
void ocm_xcp_in_gen_publish(uint32_t gen) {
    *XCP_IN_GEN_P = gen;
}

/* Mirror one A53 gateway counter into the XCP_IN header spare words (slot
 * table in ocm_xcp_fifo.h). Travels with the header flush, like in_gen. */
void ocm_xcp_in_diag_write(uint32_t slot, uint32_t value) {
    if (slot < OCM_XCP_IN_DIAG_COUNT) {
        *XCP_IN_DIAG_P(slot) = value;
    }
}

/* Last XCP_IN generation the R5 has processed. Lives in the XCP_OUT control
 * line: only valid between out_seq_read() and a passing out_seq_unchanged(). */
uint32_t ocm_xcp_in_consumed_read(void) {
    return *XCP_OUT_IN_CONSUMED_P;
}

/* Mailbox sequence from the control line out_seq_read() has just refreshed. */
uint32_t ocm_xcp_out_cto_seq_read(void) {
    return *XCP_OUT_CTO_SEQ_P;
}

/* Sequence of the chain content, from the control line out_seq_read() has
 * just refreshed. 0 = being rewritten. Validated by out_chain_unchanged(),
 * not by the seqlock (mechanism 5). */
uint32_t ocm_xcp_out_chain_seq_read(void) {
    return *XCP_OUT_CHAIN_SEQ_P;
}

/* Re-check after the chain read. The invalidate ends with a DSB, so all chain
 * loads before it have completed. */
int ocm_xcp_out_chain_unchanged(uint32_t chain_seq) {
    Xil_DCacheInvalidateRange(XCP_OUT_ADDR, XCP_OUT_SEQ_WORDS_LEN);
    return (chain_seq != 0u) && (*XCP_OUT_CHAIN_SEQ_P == chain_seq);
}

/* Publish the last consumed chain sequence. Written during the write phase;
 * reaches the OCM with the header flush of cache_flush_after_write(). */
void ocm_xcp_out_ack_write(uint32_t chain_seq) {
    *XCP_IN_OUT_ACK_P = chain_seq;
}
#endif /* OCM_XCP_APU */
