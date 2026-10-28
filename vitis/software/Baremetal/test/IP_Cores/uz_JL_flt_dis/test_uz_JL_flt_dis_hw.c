#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_JL_flt_dis_hw.h"
#include "uz_JL_flt_dis_hwAddresses.h"

#define BASE_ADDRESS 0x0000000FU // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_JL_flt_dis_hw_write_FLT_PS(void)
{
    bool test_val = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + FLT_PS_Data_uz_JL_flt_ip, test_val);
    uz_JL_flt_dis_hw_write_FLT_PS(BASE_ADDRESS, test_val);
}

void test_uz_JL_flt_dis_hw_fail_assert_write_FLT_PS_zero_baseaddress(void)
{
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_hw_write_FLT_PS(0U, true));
}

void test_uz_JL_flt_dis_hw_write_FLT_RST(void)
{
    bool test_val = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + FLT_RST_Data_uz_JL_flt_ip, test_val);
    uz_JL_flt_dis_hw_write_FLT_RST(BASE_ADDRESS, test_val);
}

void test_uz_JL_flt_dis_hw_fail_assert_write_FLT_RST_zero_baseaddress(void)
{
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_hw_write_FLT_RST(0U, true));
}

void test_uz_JL_flt_dis_hw_write_use_flt_dis(void)
{
    bool test_val = true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + use_flt_dis_Data_uz_JL_flt_ip, test_val);
    uz_JL_flt_dis_hw_write_use_flt_dis(BASE_ADDRESS, test_val);
}

void test_uz_JL_flt_dis_hw_fail_assert_write_use_flt_dis_zero_baseaddress(void)
{
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_hw_write_use_flt_dis(0U, true));
}

void test_uz_JL_flt_dis_hw_read_FLT_ps(void)
{
    uint32_t expect_val = 0x5U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + FLT_ps_Data_uz_JL_flt_ip, expect_val);
    uint32_t val_read = uz_JL_flt_dis_hw_read_FLT_ps(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expect_val, val_read);
}

void test_uz_JL_flt_dis_hw_fail_assert_read_FLT_ps_zero_baseaddress(void)
{
    uz_axi_read_uint32_IgnoreAndReturn(0U);
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_hw_read_FLT_ps(0U));
}

#endif // TEST
