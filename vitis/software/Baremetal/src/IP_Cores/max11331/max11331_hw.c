#include "max11331_hw.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

// from : ADC_MAX11331_AXI_mWriteReg(self->AXI_BASEADDR, MAX11331_ADC_SELECTOR_OFFSET, self->ADC_select);
void uz_max11_write_adc_selector(uint32_t base_address, uint32_t adc_select){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+MAX11331_ADC_SELECTOR_OFFSET,adc_select);
}

// from: ADC_MAX11331_AXI_mWriteReg(self->AXI_BASEADDR, MAX11331_CLK_DIVISION_OFFSET, self->f_clk);
void uz_max11_write_clk_divider(uint32_t base_address, SCLK_freq_t frq){
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address+MAX11331_CLK_DIVISION_OFFSET,frq);
}
