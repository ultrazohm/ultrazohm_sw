#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_flt_dis_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_flt_dis.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_JL_flt_dis_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .use_flt_dis = false,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_core_frequency_Hz = IP_FRQ;
    config.use_flt_dis = false;
}

void tearDown(void)
{
}

void test_uz_JL_flt_dis_correct_init(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
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

void test_uz_JL_flt_dis_set_FLT_PS(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    bool input = true;
    uz_JL_flt_dis_hw_write_FLT_PS_Expect(BASE_ADDRESS, input);
    uz_JL_flt_dis_set_FLT_PS(instance, input);
}

void test_uz_JL_flt_dis_set_use_flt_dis(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    bool input = true;
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, input);
    uz_JL_flt_dis_set_use_flt_dis(instance, input);
}

void test_uz_JL_flt_dis_reset_fault(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    uz_JL_flt_dis_hw_write_FLT_RST_Expect(BASE_ADDRESS, true);
    uz_JL_flt_dis_hw_write_FLT_RST_Expect(BASE_ADDRESS, false);
    uz_JL_flt_dis_reset_fault(instance);
}

void test_uz_JL_flt_dis_get_fault(void)
{
    uz_JL_flt_dis_hw_write_use_flt_dis_Expect(BASE_ADDRESS, config.use_flt_dis);
    uz_JL_flt_dis_t *instance = uz_JL_flt_dis_init(config);

    uint32_t raw_fault = (uint32_t)UZ_JL_FLT_DIS_FAULT_BIT0;
    uz_JL_flt_dis_hw_read_FLT_ps_ExpectAndReturn(BASE_ADDRESS, raw_fault);
    enum uz_JL_flt_dis_fault fault = uz_JL_flt_dis_get_fault(instance);
    TEST_ASSERT_EQUAL(UZ_JL_FLT_DIS_FAULT_BIT0, fault);
}

#endif // TEST
