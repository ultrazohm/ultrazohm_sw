#ifdef TEST
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_resolver_pos_mt_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x0000000F // random hex value that represents a fictional base address
#include "unity.h"

#include "uz_resolver_pos_mt_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_resolver_pos_mt_hw_write_reset(void)
{
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + reset_Data_uz_resolver_pos_mt, true);
    uz_resolver_pos_mt_hw_write_reset(TEST_BASE_ADDRESS, true);
}

void test_uz_resolver_pos_mt_hw_write_reset_with_zero_base_address(void)
{
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_write_reset(0, true));
}

void test_uz_resolver_pos_mt_hw_write_load_position(void)
{
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + load_position_Data_uz_resolver_pos_mt, true);
    uz_resolver_pos_mt_hw_write_load_position(TEST_BASE_ADDRESS, true);
}

void test_uz_resolver_pos_mt_hw_write_load_position_with_zero_base_address(void)
{
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_write_load_position(0, true));
}

void test_uz_resolver_pos_mt_hw_write_pos_mt_preset(void)
{
    int64_t preset = (int64_t)0x12345678ABCDEF01; // hi = 0x12345678, lo = 0xABCDEF01
    // data low word, then data high word, then strobe pulse true->false (order is enforced by CMock)
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + pos_mt_preset_Data_uz_resolver_pos_mt, 0xABCDEF01U);
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + pos_mt_preset_Data_hi_uz_resolver_pos_mt, 0x12345678U);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + pos_mt_preset_Strobe_uz_resolver_pos_mt, true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + pos_mt_preset_Strobe_uz_resolver_pos_mt, false);
    uz_resolver_pos_mt_hw_write_pos_mt_preset(TEST_BASE_ADDRESS, preset);
}

void test_uz_resolver_pos_mt_hw_write_pos_mt_preset_with_zero_base_address(void)
{
    uz_axi_write_uint32_Ignore();
    uz_axi_write_bool_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_write_pos_mt_preset(0, 42));
}

void test_uz_resolver_pos_mt_hw_read_turns_cnt(void)
{
    int32_t turns = -3;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + turns_cnt_Data_uz_resolver_pos_mt, -3);
    int32_t turns_return = uz_resolver_pos_mt_hw_read_turns_cnt(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(turns, turns_return);
}

void test_uz_resolver_pos_mt_hw_read_turns_cnt_with_zero_base_address(void)
{
    uz_axi_read_int32_IgnoreAndReturn(0);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_read_turns_cnt(0));
}

void test_uz_resolver_pos_mt_hw_read_multiturn_position(void)
{
    // strobe pulse true->false first, then low word, then high word (order enforced by CMock)
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + multiturn_position_Strobe_uz_resolver_pos_mt, true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + multiturn_position_Strobe_uz_resolver_pos_mt, false);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + multiturn_position_Data_uz_resolver_pos_mt, 0xABCDEF01U);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + multiturn_position_Data_hi_uz_resolver_pos_mt, 0x12345678U);
    int64_t pos = uz_resolver_pos_mt_hw_read_multiturn_position(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT64((int64_t)0x12345678ABCDEF01, pos);
}

void test_uz_resolver_pos_mt_hw_read_multiturn_position_negative(void)
{
    // 0xFFFFFFFFFFFFFFFF == -1
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + multiturn_position_Strobe_uz_resolver_pos_mt, true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + multiturn_position_Strobe_uz_resolver_pos_mt, false);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + multiturn_position_Data_uz_resolver_pos_mt, 0xFFFFFFFFU);
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + multiturn_position_Data_hi_uz_resolver_pos_mt, 0xFFFFFFFFU);
    int64_t pos = uz_resolver_pos_mt_hw_read_multiturn_position(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT64((int64_t)-1, pos);
}

void test_uz_resolver_pos_mt_hw_read_multiturn_position_with_zero_base_address(void)
{
    uz_axi_write_bool_Ignore();
    uz_axi_read_uint32_IgnoreAndReturn(0);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_read_multiturn_position(0));
}

void test_uz_resolver_pos_mt_hw_read_pos_mt_valid(void)
{
    uz_axi_read_bool_ExpectAndReturn(TEST_BASE_ADDRESS + pos_mt_valid_Data_uz_resolver_pos_mt, true);
    bool valid = uz_resolver_pos_mt_hw_read_pos_mt_valid(TEST_BASE_ADDRESS);
    TEST_ASSERT_TRUE(valid);
}

void test_uz_resolver_pos_mt_hw_read_pos_mt_valid_with_zero_base_address(void)
{
    uz_axi_read_bool_IgnoreAndReturn(true);
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_hw_read_pos_mt_valid(0));
}
#endif // TEST
