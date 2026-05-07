#ifdef TEST

#include "uz_JL_invModel_PT1_hw.h"
#include "unity.h"
#include "test_assert_with_exception.h"
// #include "../../../src/IP_Cores/mock_uz_JL_invModel_PT1_hw.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_AXI.h"
#include "../../src/IP_Cores/uz_JL_invModel_PT1/uz_JL_invModel_PT1_hwAdresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#define IP_FRQ 1000000000U;


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_JL_invMdodel_PT1_hw_write_to_reset(void)
{
    bool reset=true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+InvConf_PT1_reset_Data_uz_JL_Inv_PT1,reset);
    uz_JL_invModel_PT1_hw_write_reset(TEST_BASE_ADDRESS,reset);
}

void test_uz_JL_invMdodel_PT1_hw_fail_assert_write_to_reset_without_baseaddress(void)
{
    bool reset=true;
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_hw_write_reset(0u,reset));
}

void test_uz_JL_invModel_PT1_hw_write_time_constant(void){
    float reciprocal_time_constant=1.0f/5.3f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+InvConf_PT1_Ts_Data_uz_JL_Inv_PT1,reciprocal_time_constant);
    uz_JL_invModel_PT1_hw_write_time_constant(TEST_BASE_ADDRESS,reciprocal_time_constant);
}

void test_uz_JL_invModel_PT1_hw_fail_assert_write_time_constant_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_hw_write_time_constant(0U,1.3f));
}

void test_uz_JL_invModel_PT1_hw_write_gain(void){
    float gain=1.3f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+InvConf_PT1_Gain_Data_uz_JL_Inv_PT1,gain);
    uz_JL_invModel_PT1_hw_write_gain(TEST_BASE_ADDRESS,gain);
}

void test_uz_JL_invModel_PT1_fail_assert_write_gain_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_hw_write_gain(0U,3.2f));
}

void test_uz_JL_invModel_PT1_hw_write_Ualpha(void){
    float input=3.2f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+InvIn_Ualpha_Data_uz_JL_Inv_PT1,input);
    uz_JL_invModel_PT1_hw_write_Ualpha(TEST_BASE_ADDRESS,input);
}

void test_uz_JL_invModel_PT1_fail_assert_write_Ualpha_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_hw_write_Ualpha(0U,3.1f));
}

void test_uz_JL_invModel_PT1_hw_write_Ubeta(void){
    float input=3.2f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+InvIn_Ubeta_Data_uz_JL_Inv_PT1,input);
    uz_JL_invModel_PT1_hw_write_Ubeta(TEST_BASE_ADDRESS,input);
}

void test_uz_JL_invModel_PT1_fail_assert_write_Ubeta_zero_baseaddress(void){
    uz_axi_write_float_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_hw_write_Ubeta(0U,3.1f));
}

#endif // TEST
