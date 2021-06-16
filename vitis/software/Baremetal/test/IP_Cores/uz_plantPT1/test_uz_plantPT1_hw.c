#ifdef TEST

#include "unity.h"

#include "uz_plantPT1_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_plantPT1_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_plantPT1_hw_write_to_reset(void)
{
    bool reset=true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+reset_Data_uz_plantModel_pt1,reset);
    uz_plantPT1_hw_write_reset(TEST_BASE_ADDRESS,reset);
}

void test_uz_plantPT1_hw_fail_assert_write_to_reset_without_baseaddress(void)
{
    bool reset=true;
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_hw_write_reset(0u,reset));
}

void test_uz_plantPT1_hw_read_output(void){
    float return_output=1.3f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+output_Data_uz_plantModel_pt1,return_output);
    float output=uz_plantPT1_hw_read_output(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(return_output,output);
}

void test_uz_plantPT1_hw_fail_assert_read_output_without_baseaddress(void){
    uz_axi_read_float_IgnoreAndReturn(0.0f);
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_hw_read_output(0U));
}

void test_uz_plantPT1_hw_write_time_constant(void){
    float time_constant=5.3f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+time_constant_Data_uz_plantModel_pt1,time_constant);
    uz_plantPT1_hw_write_time_constant(TEST_BASE_ADDRESS,time_constant);
}

void test_uz_plantPT1_hw_fail_assert_write_time_constant_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_hw_write_time_constant(0U,1.3f));
}

void test_uz_plantPT1_hw_write_gain(void){
    float gain=1.3f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+gain_Data_uz_plantModel_pt1,gain);
    uz_plantPT1_hw_write_gain(TEST_BASE_ADDRESS,gain);
}

void test_uz_plantPT1_fail_assert_write_gain_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_hw_write_gain(0U,3.2f));
}

#endif // TEST
