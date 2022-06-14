#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_123_alphabeta_dq_transformation_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_123_alphabeta_dq_transformation_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_123_alphabeta_dq_transformation_hw_set_thetaOffset(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_offset = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_offset_AXI_Data_Trans_123_alphabeta_dq_V12_ip,theta_offset,def);
    uz_123_alphabeta_dqTransformation_hw_set_thetaOffset(TEST_BASE_ADDRESS,theta_offset);
}

void test_uz_123_alphabeta_dq_transformation_hw_set_thetaOffset_fail_due_to_zero_base_address(void){
    float thetaOffset = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_123_alphabeta_dqTransformation_hw_set_thetaOffset(0,thetaOffset));
}

void test_uz_123_alphabeta_dqTransformation_hw_get_id(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+id_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_id(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_123_alphabeta_uz_dqTransformation_hw_get_iq(void){
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+iq_AXI_Data_Trans_123_alphabeta_dq_V12_ip, fixedpoint_definition, expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_iq(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_123_alphabeta_dq_Transformation_hw_read_id_fail_due_to_zero_base_address(void){
    TEST_ASSERT_FAIL_ASSERT(uz_123_alphabeta_dqTransformation_hw_get_id(0U));
}

void test_uz_123_alphabeta_dqTransformation_hw_get_i1(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i1_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_i1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_123_alphabeta_dqTransformation_hw_get_i2(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i2_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_i2(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_123_alphabeta_dqTransformation_hw_get_i3(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i3_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_i3(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_123_alphabeta_dqTransformation_hw_get_ialpha(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -93.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+ialpha_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_ialpha(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_123_alphabeta_dqTransformation_hw_get_ibeta(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -93.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+ibeta_AXI_Data_Trans_123_alphabeta_dq_V12_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_123_alphabeta_dqTransformation_hw_get_ibeta(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
