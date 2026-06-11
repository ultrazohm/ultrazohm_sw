/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 *
 * NOTE: This file intentionally exists twice -- Baremetal/src/sw/xcp/ (R5)
 * and FreeRTOS/sw/xcp/ (A53). Both copies MUST stay identical: the OCM
 * layout in the .c file is the shared protocol between the two processors.
 */

#ifndef RPU_APU_EXCHANGE_H_
#define RPU_APU_EXCHANGE_H_

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

#endif /* RPU_APU_EXCHANGE_H_ */
