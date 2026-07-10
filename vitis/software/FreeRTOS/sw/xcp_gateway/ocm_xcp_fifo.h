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
|   flow-control-free exchange safe:
|     1. a seqlock on XCP_OUT (A53 discards torn reads),
|     2. a CTO mailbox with acknowledge (command responses survive cycle
|        rewrites; a lost response kills the XCP session),
|     3. a generation handshake on XCP_IN (commands are re-offered until the
|        R5 acknowledges execution; a lost command kills the session too).
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

/* Usable command-chain bytes in XCP_IN (region minus its 64-byte header);
 * consistency-checked against the layout in ocm_xcp_fifo.c. The A53 sizes
 * its rewrite-until-acked command batch from this. */
#define OCM_XCP_IN_CHAIN_LEN 960u

void ocm_xcp_fifo_init(void);
void ocm_xcp_fifo_prepare_read(void);
void ocm_xcp_fifo_prepare_write(void);
void ocm_xcp_fifo_cache_invalidate_before_read(void);
void ocm_xcp_fifo_cache_flush_after_write(void);

/* Append one framed message to the write region's chain.
 * Returns 1 if written, 0 if the region is full (caller drops/retries). */
int ocm_xcp_fifo_write(uint8_t len, const uint8_t *data);

/* Return 1 and point *data_p at the next message (length in *len), or 0 at the
 * end of the chain / on a corrupt length / at the region end. */
int ocm_xcp_fifo_read(uint8_t *len, uint8_t **data_p);

#ifdef ARMR5
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
/* Last command-batch generation processed by the R5. Only valid under a
 * passing out_seq_read()/out_seq_unchanged() pair. */
uint32_t ocm_xcp_in_consumed_read(void);
#endif

#endif /* OCM_XCP_FIFO_H_ */
