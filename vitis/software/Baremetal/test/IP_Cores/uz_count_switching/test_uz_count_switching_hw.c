#ifdef TEST

#include "unity.h"

#include "uz_count_switching_hw.h"
#include <stdbool.h>
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_count_switching_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address



void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_count_switching_hw_write_to_Reset(void)
{
    bool enable = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+bResetAXI_Data_uz_count_ip,enable);

    uz_count_switching_hw_reset(TEST_BASE_ADDRESS,enable);
}

void test_uz_count_switching_hw_read_from_count_out_0(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_0_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_0(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_1(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_1_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_1(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_2(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_2_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_2(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_3(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_3_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_3(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_4(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_4_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_4(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_5(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_5_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_5(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_6(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_6_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_6(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_7(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_7_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_7(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_8(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_8_AXI_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_8(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

void test_uz_count_switching_hw_read_from_count_out_sum(void)
{
    uint32_t expect_val=4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+count_out_sum_AXI1_Data_uz_count_ip,expect_val);
    uint32_t val_read=uz_count_switching_hw_read_count_sum(TEST_BASE_ADDRESS);
    TEST_ASSERT_UINT32_WITHIN(0,expect_val,val_read);
}

#endif // TEST
