#pragma once
#include <stdint.h>

// Base addresses (in decimal? Not sure)
#define MAX11331_ADC_SELECTOR_OFFSET 		32
#define MAX11331_CLK_DIVISION_OFFSET 		36

typedef enum SCLK_freq_t {f_50MHz=0x01,f_25MHz=0x02, f_16_67MHz=0x03,f_12_5MHz=0x04,f_6_25MHz=0x08,f_test=0x0C} SCLK_freq_t;

void uz_max11_write_adc_selector(uint32_t base_address, uint32_t adc_select);
void uz_max11_write_clk_divider(uint32_t base_address, SCLK_freq_t frq);
