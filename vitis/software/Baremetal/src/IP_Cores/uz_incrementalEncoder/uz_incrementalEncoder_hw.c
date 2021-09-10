#include "uz_incrementalEncoder_hw.h"
#include "IncreEncoder_V24_ip_addr.h"

void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, uint32_t timer_ms){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip,timer_ms);
}


void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, uint32_t pi2_inc){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip,pi2_inc);
}


void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip,increments_per_turn);
}

void uz_incrementalEncoder_hw_set_increments_per_turn_electric(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip,increments_per_turn);
}

void uz_incrementalEncoder_hw_set_omegaPerOverSampl(uint32_t base_address,uint32_t omega_per_over_sampl){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address+OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip,omega_per_over_sampl);
}

uint32_t uz_incrementalEncoder_hw_get_omega(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+omega_AXI4_Data_IncreEncoder_V24_ip);
}

uint32_t uz_incrementalEncoder_hw_get_direction(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+direction_AXI4_Data_IncreEncoder_V24_ip);
}

uint32_t uz_incrementalEncoder_hw_get_theta_electric(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+theta_el_AXI4_Data_IncreEncoder_V24_ip);
}

uint32_t uz_incrementalEncoder_hw_get_position(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+position_AXI4_Data_IncreEncoder_V24_ip);
}

uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+countPerPeriod_AXI4_Data_IncreEncoder_V24_ip);
}
