#include "uz_delay_compensation_fcs_mpc_6phase_pmsm_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_delay_compensation_fcs_mpc_6phase_pmsm_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + psiPM_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, psiPM);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq(uint32_t base_address, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Lq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, Lq);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Ld(uint32_t base_address, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Ld_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, Ld);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Rs_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, Rs);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float(base_address + SampleTime_div_Ld_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, SampleTime_div_Ld);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_pole_pairs(uint32_t base_address, float pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + pole_pairs_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, pole_pairs);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float(base_address + SampleTime_div_Lq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, SampleTime_div_Lq);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float(base_address + SampleTime_div_Lx_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, SampleTime_div_Lx);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float(base_address + SampleTime_div_Ly_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, SampleTime_div_Ly);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ud(uint32_t base_address, float last_applied_optimal_voltage_ud)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + last_applied_optimal_voltage_ud_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, last_applied_optimal_voltage_ud, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uq(uint32_t base_address, float last_applied_optimal_voltage_uq)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + last_applied_optimal_volatge_uq_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, last_applied_optimal_voltage_uq, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_ux(uint32_t base_address, float last_applied_optimal_voltage_ux)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + last_applied_optimal_voltage_ux_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, last_applied_optimal_voltage_ux, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_last_applied_optimal_voltage_uy(uint32_t base_address, float last_applied_optimal_voltage_uy)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + last_applied_optimal_voltage_uy_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, last_applied_optimal_voltage_uy, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_id_measured(uint32_t base_address, float id_measured)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + id_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, id_measured, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iq_measured(uint32_t base_address, float iq_measured)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + iq_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, iq_measured, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_ix_measured(uint32_t base_address, float ix_measured)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + ix_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, ix_measured, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_iy_measured(uint32_t base_address, float iy_measured)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + iy_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, iy_measured, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_omega_m_measured(uint32_t base_address, float omega_m_measured)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 13};
    uz_fixedpoint_axi_write(base_address + omega_m_measured_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, omega_m_measured, fixedpoint_definition);
}

void uz_delay_compensation_fcs_mpc_6phase_pmsm_set_use_AXI(uint32_t base_address, _Bool use_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + use_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, use_AXI);
}

float uz_delay_compensation_fcs_mpc_6phase_pmsm_get_id_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + id_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, fixedpoint_definition);
}

float uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iq_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + iq_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, fixedpoint_definition);
}

float uz_delay_compensation_fcs_mpc_6phase_pmsm_get_ix_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + ix_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, fixedpoint_definition);
}

float uz_delay_compensation_fcs_mpc_6phase_pmsm_get_iy_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + iy_k_1_AXI_Data_Delay_compensation_FCS_MPC_6Phase_PMSM, fixedpoint_definition);
}