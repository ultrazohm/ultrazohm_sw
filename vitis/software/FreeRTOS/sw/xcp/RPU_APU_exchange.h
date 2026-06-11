/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 */

#ifndef RPU_APU_EXCHANGE_H_
#define RPU_APU_EXCHANGE_H_

void rpu_apu_exchange_init(void);
void rpu_apu_exchange_prepare_read(void);
void rpu_apu_exchange_prepare_write(void);
void rpu_apu_exchange_cache_invalidate_before_read(void);
void rpu_apu_exchange_cache_flush_after_write(void);
/* Returns 1 if the message was written, 0 if the OCM write region is full
 * (caller should retry the message in the next exchange cycle). */
int rpu_apu_exchange_writeOCM(uint8_t len, uint8_t *data);
int rpu_apu_exchange_readOCM(uint8_t *len, uint8_t **data_p);

#endif /* RPU_APU_EXCHANGE_H_ */
