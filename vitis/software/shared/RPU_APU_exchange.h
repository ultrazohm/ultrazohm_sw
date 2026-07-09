/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 *
 * Single shared header for both processors (R5 Baremetal and A53 FreeRTOS),
 * resolved via the vitis/software/shared include path. The implementation
 * lives in RPU_APU_exchange_impl.c (same directory), compiled once per
 * application through a thin stub.
 */

#ifndef RPU_APU_EXCHANGE_H_
#define RPU_APU_EXCHANGE_H_

#include <stdint.h>

/* Maximum framed CTO message the mailbox can hold (4-byte transport header
 * + kXcpMaxCTO payload fits; see RPU_APU_exchange_impl.c). */
#define RPU_APU_EXCHANGE_CTO_SLOT_LEN	40

/* Usable command-chain bytes in XCP_IN (region minus its 64-byte header);
 * consistency-checked against the layout in RPU_APU_exchange_impl.c. */
#define RPU_APU_EXCHANGE_IN_CHAIN_LEN	192

void rpu_apu_exchange_init(void);
void rpu_apu_exchange_prepare_read(void);
void rpu_apu_exchange_prepare_write(void);
void rpu_apu_exchange_cache_invalidate_before_read(void);
void rpu_apu_exchange_cache_flush_after_write(void);
/* Returns 1 if the message was written, 0 if the OCM write region is full
 * (caller drops the message or retries it in the next exchange cycle). */
int rpu_apu_exchange_writeOCM(uint8_t len, uint8_t *data);
/* Returns 1 and points *data_p at the next message (length in *len), or 0 at
 * the end of the chain, on a corrupt length, or at the region end. */
int rpu_apu_exchange_readOCM(uint8_t *len, uint8_t **data_p);

#ifndef ARMR5
/* --- A53 (APU) side: seqlock + CTO mailbox read + command generations --- */
/* Sample the XCP_OUT cycle sequence. Odd = R5 is currently rewriting the
 * region; skip this IPI cycle. */
uint32_t rpu_apu_exchange_out_seq_read(void);
/* Re-sample after reading; 0 means the R5 rewrote the region mid-read and
 * everything read since out_seq_read() must be discarded (torn). */
int rpu_apu_exchange_out_seq_unchanged(uint32_t seq_begin);
/* Copy the current mailbox frame (if any) and its sequence. Only valid under
 * a passing seqlock check. */
int rpu_apu_exchange_read_cto(uint8_t *len, uint8_t *dst, uint32_t *seq);
/* Publish the last consumed mailbox sequence (write phase). */
void rpu_apu_exchange_write_cto_ack(uint32_t seq);
/* Publish the command-batch generation (write phase; chain must already be
 * written -- the flush order makes the chain visible first). */
void rpu_apu_exchange_publish_in_seq(uint32_t seq);
/* Last command-batch generation processed by the R5. Only valid under a
 * passing out_seq_read()/out_seq_unchanged() pair. */
uint32_t rpu_apu_exchange_read_in_consumed(void);
#else
/* --- R5 (RPU) side: CTO mailbox write + command generations --- */
/* 1 = the previously parked CTO has been acknowledged by the A53. */
int rpu_apu_exchange_cto_mailbox_free(void);
/* Park one framed CTO message; call between prepare_write() and
 * cache_flush_after_write() and only when the mailbox is free. */
int rpu_apu_exchange_write_cto(uint8_t len, const uint8_t *data);
/* Current command-batch generation from the A53 (fresh after
 * cache_invalidate_before_read()); process each value exactly once. */
uint32_t rpu_apu_exchange_in_seq_read(void);
/* Acknowledge the processed command-batch generation (write phase). */
void rpu_apu_exchange_write_in_consumed(uint32_t seq);
#endif

#endif /* RPU_APU_EXCHANGE_H_ */
