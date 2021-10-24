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

void test_uz_dq_transformation_hw_write_thetaOffset(void)
{
    float thetaOffset = 1.35f;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset,20);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+theta_offset_AXI_Data_Trans_123_dq_V12_ip, thetaOffset_int);
    uz_dqTransformation_hw_write_thetaOffset(TEST_BASE_ADDRESS,thetaOffset);
}

void test_uz_dq_transformation_hw_write_thetaOffset_fail_due_to_big_input_value(void)
{
    float thetaOffset = 9.0f;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset,20);
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_write_thetaOffset(TEST_BASE_ADDRESS,thetaOffset));
}

void test_uz_dq_transformation_hw_write_thetaOffset_fail_due_to_zero_base_address(void)
{
    float thetaOffset = 5.0f;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset,20);
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_write_thetaOffset(0,thetaOffset));
}

void test_uz_dq_Transformation_hw_read_id(void){
    float id_expected=31.1f;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+id_AXI_Data_Trans_123_dq_V12_ip,uz_convert_float_to_unsigned_fixed(id_expected,11));
    float id_returned=uz_dqTransformation_hw_read_id(TEST_BASE_ADDRESS);
    TEST_ASSERT_FLOAT_WITHIN(1e-3,id_expected,id_returned);
}

void test_uz_dq_Transformation_hw_read_id_fail_due_to_zero_base_address(void){
    TEST_ASSERT_FAIL_ASSERT(uz_dqTransformation_hw_read_id(0));
}

#endif // TEST
