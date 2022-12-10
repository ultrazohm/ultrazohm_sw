#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_min_cost_function_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_min_cost_function_8_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}
/*
void test_uz_min_cost_function_8_hw_get_Index_out_AXI(void){
    int32_t expected_return_value = 6;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+Index_AXI_Data_parallel_8_min_cost_function,expected_return_value);
    int32_t actual_return_value = uz_min_cost_function_8_hw_get_Index_out_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_8_hw_get_J_out_AXI(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 9,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+J_AXI_Data_parallel_8_min_cost_function,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_min_cost_function_8_hw_get_J_out_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}


void test_min_cost_function_8_hw_get_Index_in(void){
     int32_t expected_return_value = 3;
     uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+Index_in_AXI_Data_parallel_8_sim_min_cost_function,expected_return_value);
     int32_t actual_return_value = uz_min_cost_function_8_hw_get_Index_in(TEST_BASE_ADDRESS);
     TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}
*/
#endif // TEST
