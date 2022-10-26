#include "uz_phase_voltages_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_phase_voltages_hwAdresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_phase_voltages_8_set_theta_el_offset(uint32_t base_address, float theta_el_offset)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + theta_el_offset_AXI_Data_parallel_8_phase_voltages, theta_el_offset);
}

void uz_phase_voltages_8_set_u_dc_link_voltage(uint32_t base_address, float u_dc_link_voltage)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + u_dc_link_voltage_AXI_Data_parallel_8_phase_voltages, u_dc_link_voltage);
}