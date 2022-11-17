#ifdef TEST

#include "unity.h"

#include "uz_switching_states_6Phase_8.h"
#include "test_assert_with_exception.h"
#include "mock_uz_switching_states_6Phase_8_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_switching_states_6Phase_8_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
};

void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
}

void tearDown(void)
{
}

void test_uz_switching_states_6Phase_8_init_test(void)
{
    uz_switching_states_6Phase_8_init(config);
}

void test_uz_switching_states_6Phase_8_read_Index_in(void){

    uz_switching_states_6Phase_8_t* test_instance = uz_switching_states_6Phase_8_init(config);

    int32_t Index_in_expect = 3;
    uz_switching_states_6Phase_8_get_min_Index__ExpectAndReturn(config.base_address, Index_in_expect);
    int32_t Index_in = uz_switching_states_6Phase_8_read_Index_in(test_instance);
    TEST_ASSERT_EQUAL_INT(Index_in, Index_in_expect);
}

#endif // TEST
