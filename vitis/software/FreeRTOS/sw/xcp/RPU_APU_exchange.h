/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Data exchange between RPU and APU
 */

#ifndef RPU_APU_EXCHANGE_H_
#define RPU_APU_EXCHANGE_H_

typedef enum {
	rapu_exchange_write_apu,
	rapu_exchange_write_rpu,
	rapu_exchange_read_apu,
	rapu_exchange_read_rpu,
} rapu_exchange_t;

void rpu_apu_exchange_init(void);
void rpu_apu_exchange_reset(rapu_exchange_t rapu);
void rpu_apu_exchange_writeOCM(rapu_exchange_t rapu, uint8_t len, uint8_t *data);
int rpu_apu_exchange_readOCM(rapu_exchange_t rapu, uint8_t *len, uint8_t **data_p);

#endif /* RPU_APU_EXCHANGE_H_ */
