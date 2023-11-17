#ifdef TEST

#include "unity.h"

#include "uz_EnDat.h"
#include "test_assert_with_exception.h"
#include "mock_uz_EnDat_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_EnDat_fail_assert_if_base_address_is_zero(void)
{
    struct uz_EnDat_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_init(config) );
}

#endif // TEST
