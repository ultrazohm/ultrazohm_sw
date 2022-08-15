#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_vsd_and_park_transformation_6phase_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_vsd_and_park_transformation_6phase_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_offset = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_el_offset__Data_VSD_and_Park_transformation,theta_offset,def);
    uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset(TEST_BASE_ADDRESS,theta_offset);
}

void test_uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset_fail_due_to_zero_base_address(void){
    float thetaOffset = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset(0,thetaOffset));
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_alpha(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_alpha_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_alpha(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_beta(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_beta_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_beta(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_d(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_d_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_d(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_q(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_q_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_q(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_x(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_x_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_x(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_y(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_y_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_y(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_0_plus(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_0_plus_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_0_plus(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_vsd_and_park_transformation_6phase_hw_get_i_0_minus(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_0_minus_axi_Data_VSD_and_Park_transformation,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_vsd_and_park_transformation_6phase_hw_get_i_0_minus(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
