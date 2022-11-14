#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_delay_compensation_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_delay_compensation_8_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_delay_compensation_8_set_psiPM(void){
    float psiPM = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+psiPM_AXI_Data_parallel_8_sim_delay_compensation,psiPM);
    uz_delay_compensation_8_set_psiPM(TEST_BASE_ADDRESS,psiPM);
}

void test_uz_delay_compensation_8_set_psiPM_fail_due_to_zero_base_address(void){
    float psiPM = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_psiPM(0,psiPM));
}

void test_uz_delay_compensation_8_set_Lq(void){
    float Lq = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Lq_AXI_Data_parallel_8_sim_delay_compensation,Lq);
    uz_delay_compensation_8_set_Lq(TEST_BASE_ADDRESS,Lq);
}

void test_uz_delay_compensation_fcs_mpc_6phase_pmsm_set_Lq_fail_due_to_zero_base_address(void){
    float Lq = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_Lq(0,Lq));
}

void test_uz_delay_compensation_8_set_Ld(void){
    float Ld = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Ld_AXI_Data_parallel_8_sim_delay_compensation,Ld);
    uz_delay_compensation_8_set_Ld(TEST_BASE_ADDRESS,Ld);
}

void test_uz_delay_compensation_8_set_Ld_fail_due_to_zero_base_address(void){
    float Ld = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_Ld(0,Ld));
}

void test_uz_delay_compensation_8_set_Rs(void){
    float Rs = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Rs_AXI_Data_parallel_8_sim_delay_compensation,Rs);
    uz_delay_compensation_8_set_Rs(TEST_BASE_ADDRESS,Rs);
}

void test_uz_delay_compensation_8_set_Rs_fail_due_to_zero_base_address(void){
    float Rs = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_Rs(0,Rs));
}

void test_uz_delay_compensation_8_set_SampleTime_div_Ld(void){
   float SampleTime = 0.03f;
   float Ld = 0.02f;
   float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Ld_AXI_Data_parallel_8_sim_delay_compensation,SampleTime_div_Ld);
    uz_delay_compensation_8_set_SampleTime_div_Ld(TEST_BASE_ADDRESS, SampleTime, Ld);
}

void test_uz_delay_compensation_8_set_SampleTime_div_Ld_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Ld = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_SampleTime_div_Ld(0,SampleTime,Ld));
}

void test_uz_delay_compensation_8_set_pole_pairs(void){
    float pole_pairs = 3.00f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+pole_pairs_AXI_Data_parallel_8_sim_delay_compensation,pole_pairs);
    uz_delay_compensation_8_set_pole_pairs(TEST_BASE_ADDRESS,pole_pairs);
}

void test_uz_delay_compensation_8_set_pole_pairs_fail_due_to_zero_base_address(void){
    float pole_pairs = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_pole_pairs(0,pole_pairs));
}

void test_uz_delay_compensation_8_set_SampleTime_div_Lq(void){
   float SampleTime = 0.03f;
   float Lq = 0.02f;
   float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Lq_AXI_Data_parallel_8_sim_delay_compensation,SampleTime_div_Lq);
    uz_delay_compensation_8_set_SampleTime_div_Lq(TEST_BASE_ADDRESS, SampleTime, Lq);
}

void test_uz_delay_compensation_8_set_SampleTime_div_Lq_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Lq = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_SampleTime_div_Lq(0,SampleTime,Lq));
}

void test_uz_delay_compensation_8_set_SampleTime_div_Lx(void){
   float SampleTime = 0.03f;
   float Lx = 0.02f;
   float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Lx_AXI_Data_parallel_8_sim_delay_compensation,SampleTime_div_Lx);
    uz_delay_compensation_8_set_SampleTime_div_Lx(TEST_BASE_ADDRESS, SampleTime, Lx);
}

void test_uz_delay_compensation_8_set_SampleTime_div_Lx_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Lx = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_SampleTime_div_Lx(0,SampleTime,Lx));
}

void test_uz_delay_compensation_8_set_SampleTime_div_Ly(void){
   float SampleTime = 0.03f;
   float Ly = 0.02f;
   float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Ly_AXI_Data_parallel_8_sim_delay_compensation,SampleTime_div_Ly);
    uz_delay_compensation_8_set_SampleTime_div_Ly(TEST_BASE_ADDRESS, SampleTime, Ly);
}

void test_uz_delay_compensation_8_set_SampleTime_div_Ly_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Ly = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_delay_compensation_8_set_SampleTime_div_Ly(0,SampleTime,Ly));
}
/*
void test_uz_delay_compensation_8_get_id_k_1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+id_k_1_AXI_Data_parallel_8_delay_compensation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_delay_compensation_8_get_id_k_1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_delay_compensation_8_get_iq_k_1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+iq_k_1_AXI_Data_parallel_8_delay_compensation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_delay_compensation_8_get_iq_k_1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_delay_compensation_8_get_ix_k_1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+ix_k_1_AXI_Data_parallel_8_delay_compensation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_delay_compensation_8_get_ix_k_1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_delay_compensation_8_get_iy_k_1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+iy_k_1_AXI_Data_parallel_8_delay_compensation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_delay_compensation_8_get_iy_k_1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}
*/
#endif // TEST
