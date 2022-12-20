#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset(uint32_t base_address, float theta_el_offset)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + theta_el_offset_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, theta_el_offset);
}

void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage(uint32_t base_address, float u_dc_link_voltage)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + u_dc_link_voltage_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, u_dc_link_voltage);
}

void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI(uint32_t base_address, _Bool use_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + use_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, use_AXI);
}

void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI(uint32_t base_address, float theta_el_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 20,
        .integer_bits = 4};
    uz_fixedpoint_axi_write(base_address + theta_el_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, theta_el_AXI, fixedpoint_definition);
}

void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI(uint32_t base_address, int32_t Index_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // int32
     uz_axi_write_int32(base_address + Index_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, Index_AXI);
}

float uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_d_voltage_per_switching_state(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + d_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, fixedpoint_definition);
}

float uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_q_voltage_per_switching_state(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + q_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, fixedpoint_definition);
}

float uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_x_voltage_per_switching_state(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + x_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, fixedpoint_definition);
}

float uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_y_voltage_per_switching_state(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + y_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase, fixedpoint_definition);
}