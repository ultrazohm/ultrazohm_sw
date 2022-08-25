#include "uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Lq(uint32_t base_address, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Lq_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, Lq);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Ld(uint32_t base_address, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Ld_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, Ld);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float(base_address + SampleTime_div_Ld_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, SampleTime_div_Ld);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float(base_address + SampleTime_div_Lq_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, SampleTime_div_Lq);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float(base_address + SampleTime_div_Lx_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, SampleTime_div_Lx);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_pole_pairs(uint32_t base_address, float pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + pole_pairs_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, pole_pairs);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float(base_address + SampleTime_div_Ly_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, SampleTime_div_Ly);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Rs_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, Rs);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + psiPM_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, psiPM);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_ref(uint32_t base_address, float id_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + id_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, id_ref);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_ref(uint32_t base_address, float iq_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + iq_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, iq_ref);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_ref(uint32_t base_address, float ix_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + ix_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, ix_ref);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_ref(uint32_t base_address, float iy_ref)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + iy_ref_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, iy_ref);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_use_AXI(uint32_t base_address, _Bool use_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + use_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, use_AXI);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_id_k_1_AXI(uint32_t base_address, float id_k_1_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + id_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, id_k_1_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iq_k_1_AXI(uint32_t base_address, float iq_k_1_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + iq_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, iq_k_1_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_ix_k_1_AXI(uint32_t base_address, float ix_k_1_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + ix_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, ix_k_1_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_iy_k_1_AXI(uint32_t base_address, float iy_k_1_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + iy_k_1_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, iy_k_1_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_omega_m_measured_AXI(uint32_t base_address, float omega_m_measured_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + omega_m_measured_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, omega_m_measured_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_d_voltage_per_switching_state_AXI(uint32_t base_address, float d_voltage_per_switching_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + d_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, d_voltage_per_switching_state_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_q_voltage_per_switching_state_AXI(uint32_t base_address, float q_voltage_per_switching_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + q_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, q_voltage_per_switching_state_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_x_voltage_per_switching_state_AXI(uint32_t base_address, float x_voltage_per_switching_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + x_voltage_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, x_voltage_per_switching_state_AXI, fixedpoint_definition);
}

void uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_set_y_voltage_per_switching_state_AXI(uint32_t base_address, float y_voltage_per_switching_state_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + y_volatge_per_switching_state_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, y_voltage_per_switching_state_AXI, fixedpoint_definition);
}

float uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_hw_get_J_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix20_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 9,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + J_AXI_Data_Prediction_and_cost_FCS_MPC_6Phase_PMSM, fixedpoint_definition);
}