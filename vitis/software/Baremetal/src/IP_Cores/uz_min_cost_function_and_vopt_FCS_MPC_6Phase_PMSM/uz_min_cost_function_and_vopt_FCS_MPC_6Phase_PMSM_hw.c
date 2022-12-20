#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(uint32_t base_address, _Bool use_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + use_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, use_AXI);
}

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(uint32_t base_address, float J_in_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix20_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 9};
    uz_fixedpoint_axi_write(base_address + J_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, J_in_AXI, fixedpoint_definition);
}

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI(uint32_t base_address, int32_t Index_in_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // int32
     uz_axi_write_int32(base_address + Index_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, Index_in_AXI);
}

void  uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI(uint32_t base_address, float d_phase_voltage_per_switchimng_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + d_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, d_phase_voltage_per_switchimng_state_AXI, fixedpoint_definition);
}

void  uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI(uint32_t base_address, float q_phase_voltage_per_switchimng_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + q_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, q_phase_voltage_per_switchimng_state_AXI, fixedpoint_definition);
}

void  uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI(uint32_t base_address, float x_phase_voltage_per_switchimng_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + x_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, x_phase_voltage_per_switchimng_state_AXI, fixedpoint_definition);
}

void  uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI(uint32_t base_address, float y_phase_voltage_per_switchimng_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + y_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, y_phase_voltage_per_switchimng_state_AXI, fixedpoint_definition);
}

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI(uint32_t base_address, _Bool valid_in_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + valid_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, valid_in_AXI);
}

float uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uy_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + last_applied_optimal_voltage_uy_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, fixedpoint_definition);
}

float uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ux_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + last_applied_optimal_voltage_ux_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, fixedpoint_definition);
}

float uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uq_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + last_applied_optimal_voltage_uq_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, fixedpoint_definition);
}

float uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ud_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + last_applied_optimal_voltage_ud_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, fixedpoint_definition);
}

_Bool uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_done_complete_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
    return uz_axi_read_bool(base_address + done_complete_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase);
}

int32_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_Index_out_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // int32
    return uz_axi_read_int32(base_address + Index_out_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase);
}