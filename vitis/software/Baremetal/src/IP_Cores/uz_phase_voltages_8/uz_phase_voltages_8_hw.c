#include "uz_phase_voltages_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_phase_voltages_hwAdresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_phase_voltages_8_set_theta_el_offset(uint32_t base_address, float theta_el_offset)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 20,
        .integer_bits = 4};
    uz_fixedpoint_axi_write(base_address + theta_el_offset_AXI_Data_parallel_8_sim_phase_voltages, theta_el_offset,fixedpoint_definition);
}

void uz_phase_voltages_8_set_u_dc_link_voltage(uint32_t base_address, float u_dc_link_voltage)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + u_dc_link_voltage_AXI_Data_parallel_8_sim_phase_voltages, u_dc_link_voltage);
}

int32_t uz_phase_voltages_8_get_Index_in(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    //int32
    return  uz_axi_read_int32(base_address + Index_in_AXI_Data_parallel_8_sim_phase_voltages);
}
/*
void uz_phase_voltages_8_hw_set_done_delay_compensation_AXI(uint32_t base_address, _Bool done_delay_compensation_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + done_delay_compensation_Data_parallel_8_sim_phase_voltages, done_delay_compensation_AXI);
}
*/