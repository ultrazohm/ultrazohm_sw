#ifdef TEST

#include "unity.h"

#include "uz_dq_transformation_hw.h"

#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_dq_transformation_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dq_transformation_hw_set_thetaOffset(void){
    int fractionalBits = 20;
    float thetaOffset = 1.35f;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset, fractionalBits);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+theta_offset_AXI_Data_Trans_123_dq_V12_ip, thetaOffset_int);
    uz_dqTransformation_hw_set_thetaOffset(TEST_BASE_ADDRESS,thetaOffset);
}

void test_uz_dq_transformation_hw_set_thetaOffsetFail(void){
    float thetaOffset = 9.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_set_thetaOffset(TEST_BASE_ADDRESS,thetaOffset));
}

void test_uz_dq_transformation_hw_set_thetaOffset_fail_due_to_zero_base_address(void){
    float thetaOffset = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_set_thetaOffset(0,thetaOffset));
}

void test_uz_dqTransformation_hw_get_id(void){
    int fractionalBits = 11;     // sfix18_En11
    float expected_return_value = -1.0;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + id_AXI_Data_Trans_123_dq_V12_ip, uz_convert_float_to_sfixed(expected_return_value, fractionalBits)); 
    float actual_return_value = uz_dqTransformation_hw_get_id(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_dqTransformation_hw_get_iq(void){
    int fractionalBits = 11;     // sfix18_En11
    float expected_return_value = -63.25;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + iq_AXI_Data_Trans_123_dq_V12_ip, uz_convert_float_to_sfixed(expected_return_value, fractionalBits)); 
    float actual_return_value = uz_dqTransformation_hw_get_iq(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_dq_Transformation_hw_read_id_fail_due_to_zero_base_address(void){
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_get_id(0));
}

#endif // TEST
