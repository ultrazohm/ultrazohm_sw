#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_fcs_mpc_3phase_spmsm_hw.h"
#include "uz_fcs_mpc_3phase_spmsm_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=7
    };
    float u_dc_link = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+u_dc_link_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,u_dc_link,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(TEST_BASE_ADDRESS,u_dc_link);
}


void test_uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float SampleTime = 2.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+SampleTime_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,SampleTime,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(TEST_BASE_ADDRESS,SampleTime);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_Rs(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=7
    };
    float Rs = 3.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+Rs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,Rs,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_Rs(TEST_BASE_ADDRESS,Rs);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_Ld(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float Ld = 4.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+Ld_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,Ld,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_Ld(TEST_BASE_ADDRESS,Ld);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_Lq(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float Lq = 5.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+Lq_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,Lq,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_Lq(TEST_BASE_ADDRESS,Lq);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=7
    };
    float psiPM = 6.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+psiPM_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,psiPM,def);
    uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(TEST_BASE_ADDRESS,psiPM);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(void){
    int32_t pole_pairs = 4;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+pole_pairs_AXI_Data_FCS_MPC_3Phase_SPMSM_IP_Core,pole_pairs);
    uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(TEST_BASE_ADDRESS,pole_pairs);
}
#endif // TEST
