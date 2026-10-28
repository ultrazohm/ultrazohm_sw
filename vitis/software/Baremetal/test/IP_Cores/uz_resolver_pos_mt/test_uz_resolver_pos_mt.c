#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_resolver_pos_mt.h"
#include "mock_uz_resolver_pos_mt_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

static struct uz_resolver_pos_mt_config_t get_valid_config(void)
{
    struct uz_resolver_pos_mt_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    };
    return (config);
}

void test_uz_resolver_pos_mt_init(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    uz_resolver_pos_mt_t *instance = uz_resolver_pos_mt_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_resolver_pos_mt_init_without_base_address(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    config.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_init(config));
}

void test_uz_resolver_pos_mt_init_without_clk_frequency(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    config.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_init(config));
}

void test_uz_resolver_pos_mt_get_outputs_decomposition(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    uz_resolver_pos_mt_t *instance = uz_resolver_pos_mt_init(config);

    // turns=-1, singleturn=65500 => multiturn = -1*65536 + 65500 = -36
    int64_t multiturn = (int64_t)-36;
    uz_resolver_pos_mt_hw_read_multiturn_position_ExpectAndReturn(TEST_BASE_ADDRESS, multiturn);
    uz_resolver_pos_mt_hw_read_turns_cnt_ExpectAndReturn(TEST_BASE_ADDRESS, -1);
    uz_resolver_pos_mt_hw_read_pos_mt_valid_ExpectAndReturn(TEST_BASE_ADDRESS, true);

    struct uz_resolver_pos_mt_outputs_t outputs = uz_resolver_pos_mt_get_outputs(instance);
    TEST_ASSERT_EQUAL_INT64(multiturn, outputs.multiturn_position);
    TEST_ASSERT_EQUAL_INT32(-1, outputs.turns_cnt);
    TEST_ASSERT_TRUE(outputs.pos_mt_valid);
    TEST_ASSERT_EQUAL_INT32(-1, outputs.turns);
    TEST_ASSERT_EQUAL_UINT16(65500U, outputs.singleturn_raw);
}

void test_uz_resolver_pos_mt_get_outputs_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_get_outputs(NULL));
}

void test_uz_resolver_pos_mt_reset(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    uz_resolver_pos_mt_t *instance = uz_resolver_pos_mt_init(config);

    uz_resolver_pos_mt_hw_write_reset_Expect(TEST_BASE_ADDRESS, true);
    uz_resolver_pos_mt_hw_write_reset_Expect(TEST_BASE_ADDRESS, false);
    uz_resolver_pos_mt_reset(instance);
}

void test_uz_resolver_pos_mt_reset_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_reset(NULL));
}

void test_uz_resolver_pos_mt_load_preset(void)
{
    struct uz_resolver_pos_mt_config_t config = get_valid_config();
    uz_resolver_pos_mt_t *instance = uz_resolver_pos_mt_init(config);

    int64_t preset = (int64_t)196608; // 3 turns * 65536
    uz_resolver_pos_mt_hw_write_pos_mt_preset_Expect(TEST_BASE_ADDRESS, preset);
    uz_resolver_pos_mt_hw_write_load_position_Expect(TEST_BASE_ADDRESS, true);
    uz_resolver_pos_mt_hw_write_load_position_Expect(TEST_BASE_ADDRESS, false);
    uz_resolver_pos_mt_load_preset(instance, preset);
}

void test_uz_resolver_pos_mt_load_preset_with_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolver_pos_mt_load_preset(NULL, 0));
}
#endif // TEST
