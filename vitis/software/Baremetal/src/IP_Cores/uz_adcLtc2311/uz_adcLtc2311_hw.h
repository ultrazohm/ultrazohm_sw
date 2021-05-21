#ifndef UZ_ADCLTC2311_HW_H
#define UZ_ADCLTC2311_HW_H

// includes

#include <stdint.h>

// function declarations

void uz_adcLtc2311_hw_write_cr(uint32_t base_address,uint32_t value);
void uz_adcLtc2311_hw_write_spi_cr(uint32_t base_address,uint32_t value);
void uz_adcLtc2311_hw_write_spi_cfgr(uint32_t base_address,uint32_t value);
void uz_adcLtc2311_hw_write_master_channel(uint32_t base_address,uint32_t value);
void uz_adcLtc2311_hw_write_channel(uint32_t base_address,uint32_t value);
void uz_adcLtc2311_hw_write_conversion_value(uint32_t base_address,int32_t value);

uint32_t uz_adcLtc2311_hw_read_cr(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_spi_cr(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_spi_cfgr(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_master_channel(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_channel(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_master_finish(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_master_si_finish(uint32_t base_address);
uint32_t uz_adcLtc2311_hw_read_master_busy(uint32_t base_address);
int32_t uz_adcLtc2311_hw_read_conversion_value(uint32_t base_address);


#endif // UZ_ADCLTC2311_HW_H
