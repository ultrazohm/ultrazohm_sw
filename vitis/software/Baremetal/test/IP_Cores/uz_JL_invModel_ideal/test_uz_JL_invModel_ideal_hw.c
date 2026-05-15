
#ifdef TEST

#include "unity.h"
#include "uz_JL_invModel_ideal_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h"
#include "../../src/IP_Cores/uz_JL_invModel_ideal/uz_JL_invModel_ideal_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#define IP_FRQ 1000000000U;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_JL_invModel_ideal_hw_write_Udc(void){
    float Udc=570.57f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+Bus_Conf_Inv_Udc_Data_uz_JL_invModel_ideal,Udc);
    uz_JL_invModel_ideal_hw_write_Udc(TEST_BASE_ADDRESS,Udc);
}

void test_uz_JL_invModel_ideal_hw_read_out_Ua(void){
    float return_output=1.3f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+InvOut_PS_Data_uz_JL_invModel_ideal,return_output);
    float output=uz_JL_invModel_ideal_hw_read_out_Ua(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(return_output,output);
}

void test_uz_JL_invModel_ideal_hw_fail_assert_read_out_Ua_without_baseaddress(void){
    uz_axi_read_float_IgnoreAndReturn(0.0f);
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_ideal_hw_read_out_Ua(0U));
}

void test_uz_JL_invModel_ideal_hw_read_out_Ub(void){
    float return_output=1.3f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+InvOut_PS_Data_uz_JL_invModel_ideal + 0x004,return_output);
    float output=uz_JL_invModel_ideal_hw_read_out_Ub(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(return_output,output);
}

void test_uz_JL_invModel_ideal_hw_fail_assert_read_out_Ub_without_baseaddress(void){
    uz_axi_read_float_IgnoreAndReturn(0.0f);
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_ideal_hw_read_out_Ub(0U));
}

void test_uz_JL_invModel_ideal_hw_read_out_Uc(void){
    float return_output=1.3f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS+InvOut_PS_Data_uz_JL_invModel_ideal + 0x008,return_output);
    float output=uz_JL_invModel_ideal_hw_read_out_Uc(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(return_output,output);
}

void test_uz_JL_invModel_ideal_hw_fail_assert_read_out_Uc_without_baseaddress(void){
    uz_axi_read_float_IgnoreAndReturn(0.0f);
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_ideal_hw_read_out_Uc(0U));
}

void test_uz_JL_invModel_ideal_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+InvOut_PS_Strobe_uz_JL_invModel_ideal,true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+InvOut_PS_Strobe_uz_JL_invModel_ideal,false);
    uz_JL_invModel_ideal_hw_trigger_output_strobe(TEST_BASE_ADDRESS);
}


#endif // TEST
