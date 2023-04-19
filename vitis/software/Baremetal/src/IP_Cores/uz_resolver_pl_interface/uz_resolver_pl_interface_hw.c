#include "uz_resolver_pl_interface_hw.h"
#include "uz_resolver_pl_interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_math_constants.h"

void uz_resolver_pl_interface_hw_write_resolver_polepairs(uint32_t base_address, int32_t resolver_polepairs) {
    uz_assert_not_zero(base_address);
    uz_assert(resolver_polepairs>0);
    uz_axi_write_int32(base_address + resolver_polepairs_AXI_Data_uz_resolver_mech_rev_calc, resolver_polepairs);
}

void uz_resolver_pl_interface_hw_write_cnt_reset(uint32_t base_address, bool reset) {
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + cnt_reset_AXI_Data_uz_resolver_mech_rev_calc, reset);
}

void uz_resolver_pl_interface_hw_write_position_intmax(uint32_t base_address, int32_t intmax) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + position_intmax_AXI_Data_uz_resolver_mech_rev_calc , intmax);
}

void uz_resolver_pl_interface_hw_write_machine_polepairs(uint32_t base_address, int32_t machine_polepairs) {
    uz_assert_not_zero(base_address);
    uz_assert(machine_polepairs>0);
    uz_axi_write_int32(base_address + machine_polepairs_AXI_Data_uz_resolver_mech_rev_calc, machine_polepairs);
}

void uz_resolver_pl_interface_hw_write_bitToRPS_factor(uint32_t base_address, float bitToRPS_factor) {
    uz_assert_not_zero(base_address);
    uz_assert(bitToRPS_factor>0.0f);
    uz_axi_write_float(base_address + bitToRPS_Factor_AXI_Data_uz_resolver_mech_rev_calc, bitToRPS_factor);
}

void uz_resolver_pl_interface_hw_write_theta_m_offset_rad(uint32_t base_address, float theta_m_offset_rad) {
    uz_assert_not_zero(base_address);
    uz_assert(theta_m_offset_rad <= 0.0f);
    uz_assert(theta_m_offset_rad >= (-2.0f*UZ_PIf));
    uz_axi_write_float(base_address + theta_el_offset_AXI_Data_uz_resolver_mech_rev_calc, theta_m_offset_rad);
}