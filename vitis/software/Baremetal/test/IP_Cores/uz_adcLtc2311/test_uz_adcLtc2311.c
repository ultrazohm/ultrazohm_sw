#ifdef TEST

#include "unity.h"
#include "uz_adcLtc2311.h"
#include "test_assert_with_exception.h"
#include "uz_adcLtc2311.h"
#include "mock_uz_adcLtc2311_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

struct uz_adcLtc2311_base_config config ={
    .base_address=TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
};


void setUp(void)
{
}

void tearDown(void)
{
}

// test init function

void test_uz_adcLtc2311_test_init_(void)
{
    uz_adcLtc2311* test_instance= uz_adcLtc2311_init(config);
}

#endif // TEST