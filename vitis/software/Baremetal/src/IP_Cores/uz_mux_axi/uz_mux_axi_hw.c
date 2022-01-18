#include "uz_mux_axi_hw.h"
#include "uz_mux_axi_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void  uz_mux_axi_hw_enable_IP_core(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + IPCore_Enable_mux_axi_ip, 1);
}

void uz_mux_axi_hw_set_mux(uint32_t base_address, uint32_t mux_selection) {
    uz_assert_not_zero(base_address);
    uz_assert(mux_selection<7);
    uz_axi_write_uint32(base_address + select_AXI_Data_mux_axi_ip, mux_selection);
}

void uz_mux_axi_hw_set_n_th_interrupt(uint32_t base_address, uint32_t n_th_interrupt) {
    uz_assert_not_zero(base_address);
    uz_assert(n_th_interrupt>0);
    uz_axi_write_uint32(base_address + select_n_th_adc_interrupt_Data_mux_axi_ip , n_th_interrupt);
}
