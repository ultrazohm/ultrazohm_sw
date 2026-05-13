#ifdef TEST

#include "unity.h"
#include "uz_Deadbeat.h"
#include "mock_uz_Deadbeat_hw.h"
#include "test_assert_with_exception.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000F
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_Deadbeat_step_writes_inputs_and_reads_outputs(void)
{
    struct uz_Deadbeat_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ
    };

    uz_Deadbeat_t* instance = uz_Deadbeat_init(config);

    struct uz_Deadbeat_inputs_t inputs = {
        .id_ref = 1.0f,
        .iq_ref = 2.0f,
        .id = 3.0f,
        .iq = 4.0f,
        .theta = 0.5f,
        .theta_0 = 0.25f,
        .w_e = 10.0f,
        .ua_0_input = 0.1f,
        .ub_0_input = 0.2f,
        .uc_0_input = 0.3f
    };

    uz_Deadbeat_hw_write_id_ref_Expect(TEST_BASE_ADDRESS, 65536);
    uz_Deadbeat_hw_write_iq_ref_Expect(TEST_BASE_ADDRESS, 131072);
    uz_Deadbeat_hw_write_id_Expect(TEST_BASE_ADDRESS, 196608);
    uz_Deadbeat_hw_write_iq_Expect(TEST_BASE_ADDRESS, 262144);

    uz_Deadbeat_hw_write_theta_Expect(TEST_BASE_ADDRESS, 524288);
    uz_Deadbeat_hw_write_theta_0_Expect(TEST_BASE_ADDRESS, 262144);

    uz_Deadbeat_hw_write_w_e_Expect(TEST_BASE_ADDRESS, 2560);

    uz_Deadbeat_hw_write_ua_0_Expect(TEST_BASE_ADDRESS, 6553);
    uz_Deadbeat_hw_write_ub_0_Expect(TEST_BASE_ADDRESS, 13107);
    uz_Deadbeat_hw_write_uc_0_Expect(TEST_BASE_ADDRESS, 19660);

    uz_Deadbeat_hw_read_ua_0_ExpectAndReturn(TEST_BASE_ADDRESS, 32768);
    uz_Deadbeat_hw_read_ub_o_ExpectAndReturn(TEST_BASE_ADDRESS, 65536);
    uz_Deadbeat_hw_read_uc_0_ExpectAndReturn(TEST_BASE_ADDRESS, 98304);

    struct uz_Deadbeat_outputs_t outputs = uz_Deadbeat_step(instance, &inputs);

    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.5f, outputs.ua_0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, outputs.ub_o);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.5f, outputs.uc_0);
}

void test_uz_Deadbeat_init_fails_if_base_address_is_zero(void)
{
    struct uz_Deadbeat_config_t config = {
        .base_address = 0,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ
    };

    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_init(config));
}

void test_uz_Deadbeat_init_fails_if_ip_frequency_is_zero(void)
{
    struct uz_Deadbeat_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = 0
    };

    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_init(config));
}

void test_uz_Deadbeat_step_fails_if_self_is_NULL(void)
{
    struct uz_Deadbeat_inputs_t inputs = {0};

    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_step(NULL, &inputs));
}

void test_uz_Deadbeat_step_fails_if_inputs_is_NULL(void)
{
    struct uz_Deadbeat_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ
    };

    uz_Deadbeat_t* instance = uz_Deadbeat_init(config);

    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_step(instance, NULL));
}

#endif // TEST