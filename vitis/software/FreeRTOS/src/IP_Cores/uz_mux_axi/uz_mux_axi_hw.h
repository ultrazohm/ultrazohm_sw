#ifndef UZ_MUX_AXI_HW_H
#define UZ_MUX_AXI_HW_H
#include <stdint.h>
void uz_mux_axi_hw_enable_IP_core(uint32_t base_address);
void uz_mux_axi_hw_set_mux(uint32_t base_address, uint32_t mux_selection);
void uz_mux_axi_hw_set_n_th_interrupt(uint32_t base_address, uint32_t n_th_interrupt);

#endif // UZ_MUX_AXI_HW_H
