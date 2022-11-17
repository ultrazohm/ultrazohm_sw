#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_prediction_and_cost_function_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_prediction_and_cost_function_8_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_prediction_and_cost_function_8_hw_set_Lq(void){
    float Lq = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Lq_AXI_Data_parallel_8_sim_prediction_and_cost_function,Lq);
    uz_prediction_and_cost_function_8_hw_set_Lq(TEST_BASE_ADDRESS,Lq);
}

void test_uz_prediction_and_cost_function_8_hw_set_Lq_fail_due_to_zero_base_address(void){
    float Lq = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_Lq(0,Lq));
}

void test_uz_prediction_and_cost_function_8_hw_set_Ld(void){
    float Ld = 2.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Ld_AXI_Data_parallel_8_sim_prediction_and_cost_function,Ld);
    uz_prediction_and_cost_function_8_hw_set_Ld(TEST_BASE_ADDRESS,Ld);
}

void test_uz_prediction_and_cost_function_8_hw_set_Ld_fail_due_to_zero_base_address(void){
    float Ld = 5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_Ld(0,Ld));
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(void){
   float SampleTime = 0.03f;
   float Ld = 0.02f;
   float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Ld_AXI_Data_parallel_8_sim_prediction_and_cost_function,SampleTime_div_Ld);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(TEST_BASE_ADDRESS, SampleTime, Ld);
}

void test_uz_prediction_and_cost_function_8_set_SampleTime_div_Ld_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Ld = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ld(0,SampleTime,Ld));
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(void){
   float SampleTime = 0.05f;
   float Lq = 0.06f;
   float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Lq_AXI_Data_parallel_8_sim_prediction_and_cost_function,SampleTime_div_Lq);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(TEST_BASE_ADDRESS, SampleTime, Lq);
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq_fail_due_to_zero_base_address(void){
   float SampleTime = 0.05f;
   float Lq = 0.06f;
   TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lq(0,SampleTime,Lq));
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(void){
   float SampleTime = 0.028f;
   float Lx = 0.012f;
   float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Lx_AXI_Data_parallel_8_sim_prediction_and_cost_function,SampleTime_div_Lx);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(TEST_BASE_ADDRESS, SampleTime, Lx);
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx_fail_due_to_zero_base_address(void){
   float SampleTime = 0.03f;
   float Lx = 0.02f;
   TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Lx(0,SampleTime,Lx));
}

void test_uz_prediction_and_cost_function_8_hw_set_pole_pairs(void){
    float pole_pairs = 3.00f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+pole_pairs_AXI_Data_parallel_8_sim_prediction_and_cost_function,pole_pairs);
    uz_prediction_and_cost_function_8_hw_set_pole_pairs(TEST_BASE_ADDRESS,pole_pairs);
}

void test_uz_prediction_and_cost_function_8_hw_set_pole_pairs_fail_due_to_zero_base_address(void){
    float pole_pairs = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_pole_pairs(0,pole_pairs));
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(void){
   float SampleTime = 0.068f;
   float Ly = 0.032f;
   float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+SampleTime_div_Ly_AXI_Data_parallel_8_sim_prediction_and_cost_function,SampleTime_div_Ly);
    uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(TEST_BASE_ADDRESS, SampleTime, Ly);
}

void test_uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly_fail_due_to_zero_base_address(void){
   float SampleTime = 0.068f;
   float Ly = 0.032f;
   TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_SampleTime_div_Ly(0,SampleTime,Ly));
}

void test_uz_prediction_and_cost_function_8_hw_set_Rs(void){
    float Rs = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Rs_AXI_Data_parallel_8_sim_prediction_and_cost_function,Rs);
    uz_prediction_and_cost_function_8_hw_set_Rs(TEST_BASE_ADDRESS,Rs);
}

void test_uz_prediction_and_cost_function_8_hw_set_Rs_fail_due_to_zero_base_address(void){
    float Rs = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_Rs(0,Rs));
}

void test_uz_prediction_and_cost_function_8_hw_set_psiPM(void){
    float psiPM = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+psiPM_AXI_Data_parallel_8_sim_prediction_and_cost_function,psiPM);
    uz_prediction_and_cost_function_8_hw_set_psiPM(TEST_BASE_ADDRESS,psiPM);
}

void test_uz_prediction_and_cost_function_8_hw_set_psiPM_fail_due_to_zero_base_address(void){
    float psiPM = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_psiPM(0,psiPM));
}

void test_uz_prediction_and_cost_function_8_hw_set_id_ref(void){
    float id_ref = 3.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+id_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function,id_ref);
    uz_prediction_and_cost_function_8_hw_set_id_ref(TEST_BASE_ADDRESS,id_ref);
}

void test_uz_prediction_and_cost_function_8_hw_set_id_ref_fail_due_to_zero_base_address(void){
    float id_ref = 3.35f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_id_ref(0,id_ref));
}

void test_uz_prediction_and_cost_function_8_hw_set_iq_ref(void){
    float iq_ref = 10.0f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+iq_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function,iq_ref);
    uz_prediction_and_cost_function_8_hw_set_iq_ref(TEST_BASE_ADDRESS,iq_ref);
}

void test_uz_prediction_and_cost_function_8_hw_set_iq_ref_fail_due_to_zero_base_address(void){
    float iq_ref = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_iq_ref(0,iq_ref));
}

void test_uz_prediction_and_cost_function_8_hw_set_ix_ref(void){
    float ix_ref = 12.5f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+ix_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function,ix_ref);
    uz_prediction_and_cost_function_8_hw_set_ix_ref(TEST_BASE_ADDRESS,ix_ref);
}

void test_uz_prediction_and_cost_function_8_hw_set_ix_ref_fail_due_to_zero_base_address(void){
    float ix_ref = 12.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_ix_ref(0,ix_ref));
}

void test_uz_prediction_and_cost_function_8_hw_set_iy_ref(void){
    float iy_ref = 6.4f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+iy_ref_AXI_Data_parallel_8_sim_prediction_and_cost_function,iy_ref);
    uz_prediction_and_cost_function_8_hw_set_iy_ref(TEST_BASE_ADDRESS,iy_ref);
}

void test_uz_prediction_and_cost_function_8_hw_set_iy_ref_fail_due_to_zero_base_address(void){
    float iy_ref = 6.4f;
    TEST_ASSERT_FAIL_ASSERT(uz_prediction_and_cost_function_8_hw_set_iy_ref(0,iy_ref));
}

void test_uz_prediction_and_cost_function_8_hw_get_Index(void){
     int32_t expected_return_value = 3;
     uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+Index_AXI_Data_parallel_8_sim_prediction_and_cost_function,expected_return_value);
     int32_t actual_return_value = uz_prediction_and_cost_function_8_hw_get_Index(TEST_BASE_ADDRESS);
     TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
