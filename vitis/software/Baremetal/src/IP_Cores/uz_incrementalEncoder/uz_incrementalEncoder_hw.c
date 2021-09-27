#include "uz_incrementalEncoder_hw.h"
#include "IncreEncoder_V24_ip_addr.h"

void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, float timer_ms){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(timer_ms > 0.0f);
    uz_assert(timer_ms < 1.0f); // data type of pi2inc in ip-core is ufix32_en32, thus maximum is 0.9999...
    uz_axi_write_uint32(base_address+Timer_FPGA_ms_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_unsigned_fixed(timer_ms,32) ); // Data type is ufix24_En24
}


void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, float pi2_inc){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(pi2_inc > 0.0f);
    uz_assert(pi2_inc < 1.0f); // data type of pi2inc in ip-core is ufix24_en24, thus maximum is 0.9999...
    uz_axi_write_uint32(base_address+PI2_Inc_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_unsigned_fixed(pi2_inc,24));
}


void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(increments_per_turn < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
    uz_axi_write_uint32(base_address+IncPerTurn_mech_AXI4_Data_IncreEncoder_V24_ip,increments_per_turn);
}

void uz_incrementalEncoder_hw_set_increments_per_turn_electric(uint32_t base_address, uint32_t increments_per_turn){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(increments_per_turn < UINT16_MAX); // Data type in IP-Core is uint16_t, thus increments_per_turn has to be smaller than that
    uz_axi_write_uint32(base_address+IncPerTurn_elek_AXI4_Data_IncreEncoder_V24_ip,increments_per_turn);
}

void uz_incrementalEncoder_hw_set_omegaPerOverSample(uint32_t base_address,float omega_per_over_sampl){
    uz_assert_not_zero_uint32(base_address);
    uz_assert(omega_per_over_sampl < 4095.0f);
    uz_assert(omega_per_over_sampl > -4095.0f); // make sure omega_per_oversampl fits data type sfix_24_en11
    uz_axi_write_int32(base_address+OmegaPerOverSampl_AXI4_Data_IncreEncoder_V24_ip,uz_convert_float_to_sfixed(omega_per_over_sampl,11));
}

float uz_incrementalEncoder_hw_get_omega(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+omega_AXI4_Data_IncreEncoder_V24_ip);
    return uz_convert_sfixed_to_float(tmp,11);
}

float uz_incrementalEncoder_hw_get_direction(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp=uz_axi_read_int32(base_address+direction_AXI4_Data_IncreEncoder_V24_ip);
    return uz_convert_sfixed_to_float(tmp,11);
}

float uz_incrementalEncoder_hw_get_theta_electric(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    int32_t tmp= uz_axi_read_int32(base_address+theta_el_AXI4_Data_IncreEncoder_V24_ip);
    return uz_convert_sfixed_to_float(tmp,20);
}

uint32_t uz_incrementalEncoder_hw_get_position(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+position_AXI4_Data_IncreEncoder_V24_ip);
}

uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address+countPerPeriod_AXI4_Data_IncreEncoder_V24_ip);
}
