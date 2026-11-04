#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_flt_dis_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_flt_dis.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U
#define ISR_FRQ 10000U
#define WD_PERIODS 10U
#define EXPECTED_MAX_CNTS ((IP_FRQ / ISR_FRQ) * WD_PERIODS) // 100000

struct uz_JL_flt_dis_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .use_flt_dis = false,
    .isr_frequency_Hz = ISR_FRQ,
    .watchdog_timeout_ISR_periods = WD_PERIODS,
    .disable_watchdog = false,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_core_frequency_Hz = IP_FRQ;
    config.use_flt_dis = false;
    config.isr_frequency_Hz = ISR_FRQ;
    config.watchdog_timeout_ISR_periods = WD_PERIODS;
    config.disable_watchdog = false;
}

void tearDown(void)
{
}

// Expect the hw writes performed by uz_JL_flt_dis_init in order.
static void expect_init(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_hw_write_Watchdog_Periods_Max_Cnts_Expect(BASE_ADDRESS, EXPECTED_MAX_CNTS);
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, config.disable_watchdog);
}

void test_uz_JL_flt_dis_correct_init(void)
{
    expect_init();
    uz_JL_flt_dis_t *test_instance = uz_JL_flt_dis_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_flt_dis_init_fail_assert_zero_baseaddress(void)
{
    config.base_address = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_init(config));
    config.base_address = BASE_ADDRESS;
}

void test_uz_JL_flt_dis_init_fail_assert_zero_frq(void)
{
    config.ip_core_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_init(config));
    config.ip_core_frequency_Hz = IP_FRQ;
}

void test_uz_JL_flt_dis_init_fail_assert_zero_isr_frq(void)
{
    config.isr_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_init(config));
    config.isr_frequency_Hz = ISR_FRQ;
}

void test_uz_JL_flt_dis_init_fail_assert_zero_watchdog_periods(void)
{
    config.watchdog_timeout_ISR_periods = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_init(config));
    config.watchdog_timeout_ISR_periods = WD_PERIODS;
}

void test_uz_JL_flt_dis_init_fail_assert_max_cnts_too_large(void)
{
    // (IP_FRQ / ISR_FRQ) * N = 10000 * N; N = 200 -> 2000000 > 0xFFFFF (1048575)
    config.watchdog_timeout_ISR_periods = 200U;
    TEST_ASSERT_FAIL_ASSERT(uz_JL_flt_dis_init(config));
    config.watchdog_timeout_ISR_periods = WD_PERIODS;
}

void test_uz_JL_flt_dis_init_disabled_watchdog(void)
{
    config.disable_watchdog = true; // Watchdog_Rst held high at init
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_hw_write_Watchdog_Periods_Max_Cnts_Expect(BASE_ADDRESS, EXPECTED_MAX_CNTS);
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_JL_flt_dis_set_FLT_PS(void)
{
    expect_init();
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    bool input = true;
    uz_JL_flt_dis_hw_write_FLT_PS_Expect(BASE_ADDRESS, input);
    uz_JL_flt_dis_set_FLT_PS(instance, input);
}

void test_uz_JL_flt_dis_set_use_flt_dis(void)
{
    expect_init();
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    bool input = true;
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, input);
    uz_JL_flt_dis_set_use_flt_dis(instance, input);
}

void test_uz_JL_flt_dis_reset_fault(void)
{
    expect_init();
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    uz_JL_flt_dis_hw_write_FLT_RST_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_hw_write_FLT_RST_Expect(BASE_ADDRESS, false);
    uz_JL_flt_dis_reset_fault(instance);
}

void test_uz_JL_flt_dis_get_fault(void)
{
    expect_init();
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    uint32_t raw_fault = (uint32_t)UZ_JL_FLT_DIS_FAULT_FLT_1;
    uz_JL_flt_dis_hw_read_FLT_ps_ExpectAndReturn(BASE_ADDRESS, raw_fault);
    enum uz_JL_flt_dis_fault fault = uz_JL_flt_dis_get_fault(instance);
    TEST_ASSERT_EQUAL(UZ_JL_FLT_DIS_FAULT_FLT_1, fault);
}

void test_uz_JL_flt_dis_watchdog_trigger_toggles(void)
{
    expect_init();
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    // Each call toggles the internally tracked state, starting from false.
    uz_JL_flt_dis_hw_write_Watchdog_trig_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_watchdog_trigger(instance);

    uz_JL_flt_dis_hw_write_Watchdog_trig_Expect(BASE_ADDRESS, false);
    uz_JL_flt_dis_watchdog_trigger(instance);

    uz_JL_flt_dis_hw_write_Watchdog_trig_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_watchdog_trigger(instance);
}

void test_uz_JL_flt_dis_watchdog_reset_pulse_active(void)
{
    expect_init(); // disable_watchdog == false
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    // Pulse high, then return to resting state (false, because watchdog is armed).
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, false);
    uz_JL_flt_dis_watchdog_reset(instance);
}

void test_uz_JL_flt_dis_watchdog_reset_keeps_disabled(void)
{
    config.disable_watchdog = true;
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_hw_write_Watchdog_Periods_Max_Cnts_Expect(BASE_ADDRESS, EXPECTED_MAX_CNTS);
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    // A reset on a config-disabled watchdog must return Watchdog_Rst to high, not re-arm it.
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_hw_write_Watchdog_Rst_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_watchdog_reset(instance);
}

#endif // TEST
