#include "uz_fcs_mpc_3phase_spmsm_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_fcs_mpc_3phase_spmsm_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

/*
void uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(uint32_t base_address, float u_dc_link)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + u_dc_link_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, u_dc_link, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(uint32_t base_address, float SampleTime)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 20,
        .integer_bits = 4,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + SampleTime_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, SampleTime, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + Rs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, Rs, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_Ld(uint32_t base_address, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits =20,
        .integer_bits = 4,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + Ld_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, Ld, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_Lq(uint32_t base_address, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 20,
        .integer_bits = 4,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + Lq_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, Lq, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    uz_fixedpoint_axi_write(base_address + psiPM_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, psiPM, fixedpoint_definition);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(uint32_t base_address, int32_t pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_int32(base_address + pole_pairs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core, pole_pairs);
}
*/

void uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(uint32_t base_address, float u_dc_link)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + u_dc_link_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, u_dc_link);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(uint32_t base_address, float SampleTime)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + SampleTime_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, SampleTime);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Rs_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, Rs);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_reciprocal_Ls(uint32_t base_address, float Ld, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float reciprocal_Ls = 1.0f/((Ld+Lq)*0.5f);
    uz_axi_write_float(base_address + reciprocal_Ls_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, reciprocal_Ls);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + psiPM_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, psiPM);
}

void uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(uint32_t base_address, int32_t pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_int32(base_address + pole_pairs_AXI_Data_Test_FCS_MPC_3Phase_SPMSM_IP_Core, pole_pairs);
}


