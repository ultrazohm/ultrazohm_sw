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
    float u_dc_link = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+u_dc_link_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,u_dc_link);
    uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(TEST_BASE_ADDRESS,u_dc_link);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(void){
    float SampleTime = 2.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,SampleTime);
    uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(TEST_BASE_ADDRESS,SampleTime);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_Rs(void){
    float Rs = 3.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Rs_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,Rs);
    uz_fcs_mpc_3phase_spmsm_hw_set_Rs(TEST_BASE_ADDRESS,Rs);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_reciprocal_Ls(void){
   float Ld = 0.03f;
   float Lq = 0.02f;
   float reciprocal_Ls = 1.0f/((Ld+Lq)*0.5f);
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+reciprocal_Ls_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,reciprocal_Ls);
    uz_fcs_mpc_3phase_spmsm_hw_set_reciprocal_Ls(TEST_BASE_ADDRESS, Ld, Lq);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(void){
    float psiPM = 6.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+psiPM_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,psiPM);
    uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(TEST_BASE_ADDRESS,psiPM);
}

void test_uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(void){
    float pole_pairs = 4.0f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+pole_pairs_AXI_Data_FCS_MPC_3Phase_SPMSM_V1,pole_pairs);
    uz_fcs_mpc_3phase_spmsm_hw_set_pole_pairs(TEST_BASE_ADDRESS,pole_pairs);
}

#endif // TEST
