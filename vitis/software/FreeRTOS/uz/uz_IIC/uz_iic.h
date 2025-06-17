#ifndef UZ_IIC_H
#define UZ_IIC_H

#include <stdint.h>

typedef struct uz_iic_ {
	uint8_t businst;
	_Bool is_ready;
	uint8_t devaddr;
} uz_iic;

void uz_iic_initbus(uint8_t businst, uintptr_t xlnx_baseaddress, uint16_t xlnx_deviceid, uint32_t xlnx_inputclock_hz, int busfreq_khz);
void uz_iic_initdev(uz_iic *self, uint8_t businst, uint8_t devaddr);
int uz_iic_write_reg16(struct uz_iic_ *self, uint8_t regaddr, uint16_t data);
int uz_iic_write_raw(struct uz_iic_ *self, uint8_t* data, int32_t cnt);
int uz_iic_a8read_data(struct uz_iic_ *self, uint8_t regaddr, uint8_t*, int32_t cnt);
int uz_iic_a16read_data(struct uz_iic_ *self, uint16_t regaddr, uint8_t*, int32_t cnt);

#endif
