#ifndef UZ_ADCMAX11331_HW_H
#define UZ_ADCMAX11331_HW_H


// includes

#include <stdint.h>
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

// function declarations

void uz_adcMax11331_hw_write_spi_cfgr(uint32_t base_address,uint32_t value);
void uz_adcMax11331_hw_write_master_channel(uint32_t base_address,uint32_t value);

uint32_t uz_adcMax11331_hw_read_spi_cfgr(uint32_t base_address);
uint32_t uz_adcMax11331_hw_read_master_channel(uint32_t base_address);


#endif // UZ_ADCMAX11331_HW_H
