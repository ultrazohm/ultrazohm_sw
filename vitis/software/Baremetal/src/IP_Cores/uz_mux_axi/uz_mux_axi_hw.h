#ifndef UZ_MUX_AXI_HW_H
#define UZ_MUX_AXI_HW_H
#include <stdint.h>

#define UZ_MUX_AXI_HW_MAX_DELAY_CYCLES 1023U // Maximum number of delay cycles is based on the bit-width of the hardware counter which is 10.

void uz_mux_axi_hw_enable_IP_core(uint32_t base_address);
void uz_mux_axi_hw_set_mux(uint32_t base_address, uint32_t mux_selection);
void uz_mux_axi_hw_set_n_th_interrupt(uint32_t base_address, uint32_t n_th_interrupt);
void uz_mux_axi_hw_set_delay_adc_trigger_in_clk_cycles(uint32_t base_address, uint32_t delay_adc_trigger_in_clk_cycles);

#endif // UZ_MUX_AXI_HW_H
