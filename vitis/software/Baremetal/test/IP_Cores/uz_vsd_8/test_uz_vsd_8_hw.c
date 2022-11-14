#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_vsd_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_vsd_8_hwAdresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_vsd_8_hw_set_thetaOffset(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_offset = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_el_offset_AXI_Data_parallel_8_sim_vsd_and_park,theta_offset,def);
    uz_vsd_8_hw_set_thetaOffset(TEST_BASE_ADDRESS,theta_offset);
}

void test_uz_vsd_8_hw_set_thetaOffset_fail_due_to_zero_base_address(void){
    float thetaOffset = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_vsd_8_hw_set_thetaOffset(0,thetaOffset));
}

void test_uz_vsd_8_hw_get_i_a1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_a1_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_a1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_8_hw_get_i_b1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_b1_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_b1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_8_hw_get_i_c1(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_c1_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_c1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_8_hw_get_i_a2(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_a2_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_a2(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_8_hw_get_i_b2(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_b2_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_b2(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_8_hw_get_i_c2(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_c2_axi_Data_parallel_8_sim_vsd_and_park,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_8_hw_get_i_c2(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}


#endif // TEST
