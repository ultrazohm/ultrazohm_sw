/*----------------------------------------------------------------------------
| ocm_xcp_fifo.h
|   Option Z — OCM exchange between the R5 (XCPlite engine) and the A53
|   (Ethernet gateway). One shared implementation for both cores; the side is
|   selected by the ARMR5 compiler define (R5) vs. its absence (A53).
|
|   Sweep model (per exchange cycle, coordinated by the existing IPI):
|     writer:  prepare_write() -> write()* -> cache_flush_after_write()
|     reader:  cache_invalidate_before_read() -> prepare_read() -> read()*
|
|   On top of the sweep model, three mechanisms from the hedrive hardware
|   campaign (uz_sw_xcp_hedrive_andi, XCP_BOTTLENECK_ANALYSIS.md T8) make the
|   exchange safe:
|     1. a seqlock on the XCP_OUT header (A53 discards torn header copies),
|     2. a CTO mailbox with acknowledge (command responses survive cycle
|        rewrites; a lost response kills the XCP session),
|     3. a generation handshake on XCP_IN (commands are re-offered until the
|        R5 acknowledges execution; a lost command kills the session too),
|   plus one of our own:
|     4. a consumption handshake on the XCP_OUT chain (the R5 keeps a DAQ
|        chain in place until the A53 acknowledges it, so a late, torn or
|        skipped IPI read delays measurement data instead of losing it),
|     5. chain validation by its own sequence number instead of the seqlock
|        (chain_seq is 0 while the chain is rewritten and published only
|        after the chain bytes), so a slow read of a KEPT chain stays valid.
|
|   Adapted from uz_sw_xcp_hedrive_andi RPU_APU_exchange (Jens Wenzl, 2023),
|   which is hardware-proven. UltraZohm.
 ----------------------------------------------------------------------------*/
#ifndef OCM_XCP_FIFO_H_
#define OCM_XCP_FIFO_H_

#include <stdint.h>

/* Maximum framed CTO message the mailbox slot holds: 4-byte transport header
 * + XCPTL_MAX_CTO_SIZE (248) payload, rounded to whole A53 cache lines. */
#define OCM_XCP_CTO_SLOT_LEN 256u

/* Largest chain record (length word excluded). A record is one R5 queue
 * segment (XCPTL_MAX_SEGMENT_SIZE, xcplib_r5_cfg.h) and becomes one UDP
 * datagram of the gateway, so 1400 keeps the datagram plus UDP/IP headers
 * below a 1500-byte MTU. The chain length word was always 32 bit; until
 * 2026-11-17 the API limited records to 255 bytes. */
#define OCM_XCP_RECORD_MAX 1400u

/* Usable command-chain bytes in XCP_IN (region minus its 128-byte header);
 * consistency-checked against the layout in ocm_xcp_fifo.c. The A53 sizes
 * its rewrite-until-acked command batch from this. */
#define OCM_XCP_IN_CHAIN_LEN 896u

/* A53 gateway diagnostics mirror: spare words of the XCP_IN header (from
 * byte 8, OCM_XCP_IN_DIAG_COUNT x u32; room up to byte 123, now used up) carry the
 * gateway's own counters, rewritten every
 * IPI cycle and published with the header flush. They are not part of the
 * handshake and the R5 never writes them, so the XCP master can read them by
 * absolute address through the R5 engine (OCM is in the R5 allow-list) -
 * before they were JTAG-only. Fixed OCM addresses = independent of any
 * build. The slot table is mirrored in CANape/UZ_XCP/uz.A2L (xcp_gw_*),
 * tools/xcp_test/gen_a2l.py and tools/xcp_test/xcp_poll.py: keep in sync. */
#define OCM_XCP_IN_DIAG_ADDR  0xFFFFC008u
#define OCM_XCP_IN_DIAG_COUNT 27u
enum ocm_xcp_in_diag_slot {
    OCM_XCP_DIAG_GW_OCM_SKIPPED_WRITING = 0, /* header copy skipped/torn, retried  */
    OCM_XCP_DIAG_GW_OCM_TORN,                /* DAQ chain rewritten mid-read       */
    OCM_XCP_DIAG_GW_OCM_CYCLES_MISSED,       /* R5 cycles no IPI read              */
    OCM_XCP_DIAG_GW_OCM_CAPPED,              /* per-IPI drain cap hit              */
    OCM_XCP_DIAG_GW_TXQ_DROPPED,             /* DAQ queue full -> record dropped   */
    OCM_XCP_DIAG_GW_CTOQ_DROPPED,            /* CTO queue full -> frame dropped    */
    OCM_XCP_DIAG_GW_IN_BATCHES_SENT,         /* command generations offered        */
    OCM_XCP_DIAG_GW_IN_RETRY_CYCLES,         /* IPIs re-offering an unacked batch  */
    OCM_XCP_DIAG_GW_TX_MALFORMED_DROP,       /* TL walk failed on TX               */
    OCM_XCP_DIAG_GW_RX_MALFORMED_DROP,       /* TL walk failed on RX               */
    OCM_XCP_DIAG_GW_SENDTO_ERR,              /* transient lwip_sendto failures     */
    OCM_XCP_DIAG_GW_SENDTO_DROP,             /* batch dropped after retries        */
    OCM_XCP_DIAG_GW_IPI_COUNT,               /* IPIs handled (A53 liveness)        */
    OCM_XCP_DIAG_GW_TXQ_LEVEL,               /* DAQ queue fill (gauge, not count)  */
    OCM_XCP_DIAG_GW_MASTER_LOST,             /* sessions closed by the gateway     */
    /* A53 time profile (XCP_GW_PROFILE, xcp_gateway_a53.h; 0 when off):
     * microsecond sums of the A53 system counter that wrap after ~71 min -
     * the master uses differences over a run. Read by
     * tools/xcp_test/xcp_poll.py --stress only, not part of the A2L. */
    OCM_XCP_DIAG_GW_PROF_NOW_US,             /* A53 time base                      */
    OCM_XCP_DIAG_GW_PROF_IDLE_US,            /* CPU time left to the idle probe    */
    OCM_XCP_DIAG_GW_PROF_IPI_US,             /* in the IPI hook (both phases)      */
    OCM_XCP_DIAG_GW_PROF_IPI_MAX_US,         /* longest IPI hook, last full second */
    OCM_XCP_DIAG_GW_PROF_CHAIN_US,           /* DAQ chain OCM -> staging copy      */
    OCM_XCP_DIAG_GW_PROF_ENQ_US,             /* staging -> queues (FromISR copies) */
    OCM_XCP_DIAG_GW_PROF_RECORDS,            /* chain records staged (count)       */
    OCM_XCP_DIAG_GW_PROF_TX_US,              /* tx task: batching + sendto         */
    OCM_XCP_DIAG_GW_PROF_SENDTO_US,          /* inside lwip_sendto                 */
    OCM_XCP_DIAG_GW_PROF_SENDTO_N,           /* lwip_sendto calls (count)          */
    OCM_XCP_DIAG_GW_PROF_TX_KB,              /* datagram bytes handed to lwIP, KiB */
    OCM_XCP_DIAG_GW_PROF_SENDTO_MAX_US,      /* longest sendto, last full second   */
};

void ocm_xcp_fifo_init(void);
void ocm_xcp_fifo_prepare_read(void);
void ocm_xcp_fifo_prepare_write(void);
void ocm_xcp_fifo_cache_invalidate_before_read(void);
void ocm_xcp_fifo_cache_flush_after_write(void);

/* Append one framed message to the write region's chain.
 * Returns 1 if written, 0 if the region is full (caller drops/retries). */
int ocm_xcp_fifo_write(uint16_t len, const uint8_t *data);

/* Return 1 if ocm_xcp_fifo_write(len, data) would succeed right now. No side
 * effects (ocm_xcp_w_dropped is not counted): lets a writer hold a message
 * back for the next cycle instead of dropping it. */
int ocm_xcp_fifo_write_fits(uint16_t len, const uint8_t *data);

/* Return 1 and point *data_p at the next message (length in *len, at most
 * OCM_XCP_RECORD_MAX), or 0 at the end of the chain / on a corrupt length /
 * at the region end. */
int ocm_xcp_fifo_read(uint16_t *len, uint8_t **data_p);

#ifdef ARMR5
/* --- R5 side: chain consumption handshake ---------------------------------- */
/* 1 = the A53 has acknowledged the chain published by the last
 * prepare_write() (fresh after cache_invalidate_before_read()). */
int ocm_xcp_out_chain_acked(void);
/* Open a cycle WITHOUT rewinding the chain: the previous, not yet
 * acknowledged chain stays in place byte for byte and nothing can be
 * appended (ocm_xcp_fifo_write() fails). Header words (mailbox, in_consumed)
 * may still change; finish with cache_flush_after_write() as usual. */
void ocm_xcp_fifo_prepare_write_keep(void);
/* 1 = at least one message was written to the chain since prepare_write(). */
int ocm_xcp_fifo_chain_nonempty(void);

/* --- R5 side: CTO mailbox write + command generations --------------------- */
/* 1 = the previously parked CTO has been acknowledged by the A53. Relies on
 * cache_invalidate_before_read() having refreshed XCP_IN this cycle. */
int ocm_xcp_cto_mailbox_free(void);
/* Park one framed CTO message; call between prepare_write() and
 * cache_flush_after_write() and only when the mailbox is free. The content
 * persists across cycle rewrites until acknowledged. */
int ocm_xcp_cto_write(uint8_t len, const uint8_t *data);
/* Current command-batch generation published by the A53 (fresh after
 * cache_invalidate_before_read()); process each value exactly once. */
uint32_t ocm_xcp_in_gen_read(void);
/* Acknowledge the processed command-batch generation (write phase). */
void ocm_xcp_in_consumed_write(uint32_t gen);
#else
/* --- A53 side: seqlock + CTO mailbox read + command generations ----------- */
/* Sample the XCP_OUT cycle sequence. Odd = R5 is currently rewriting the
 * region; skip this IPI cycle. */
uint32_t ocm_xcp_out_seq_read(void);
/* Re-sample after reading; 0 means the R5 rewrote the region mid-read and
 * everything read since out_seq_read() must be discarded (torn). */
int ocm_xcp_out_seq_unchanged(uint32_t seq_begin);
/* Copy the current mailbox frame (if any) and its sequence into dst (must
 * hold OCM_XCP_CTO_SLOT_LEN bytes). Only trustworthy under a passing
 * out_seq_read()/out_seq_unchanged() pair. */
int ocm_xcp_cto_read(uint8_t *len, uint8_t *dst, uint32_t *seq);
/* Publish the last consumed mailbox sequence (write phase). */
void ocm_xcp_cto_ack_write(uint32_t seq);
/* Publish the command-batch generation (write phase; chain must already be
 * written — the flush order makes the chain visible first). */
void ocm_xcp_in_gen_publish(uint32_t gen);

/* A53 only: store one mirrored gateway counter (slot from enum
 * ocm_xcp_in_diag_slot); published by the header flush of
 * ocm_xcp_fifo_cache_flush_after_write(). */
void ocm_xcp_in_diag_write(uint32_t slot, uint32_t value);
/* Last command-batch generation processed by the R5. Only valid under a
 * passing out_seq_read()/out_seq_unchanged() pair. */
uint32_t ocm_xcp_in_consumed_read(void);
/* Sequence of the chain currently in XCP_OUT, from the control line that
 * out_seq_read() refreshed. 0 = no valid chain (being rewritten). The R5
 * publishes a non-zero value only after the chain bytes, so the chain does
 * NOT need the seqlock: read chain_seq, the chain, then confirm with
 * out_chain_unchanged(). A chain whose sequence was already consumed must
 * not be forwarded again. */
uint32_t ocm_xcp_out_chain_seq_read(void);
/* Refresh the control line and return 1 if chain_seq is still the non-zero
 * value read before the chain: then everything read from the chain since is
 * consistent, even if the R5 swept (and updated header words) meanwhile. */
int ocm_xcp_out_chain_unchanged(uint32_t chain_seq);
/* Publish the last consumed chain sequence (write phase); the R5 keeps a
 * non-empty chain in place until it sees its sequence here. */
void ocm_xcp_out_ack_write(uint32_t chain_seq);
#endif

#endif /* OCM_XCP_FIFO_H_ */
