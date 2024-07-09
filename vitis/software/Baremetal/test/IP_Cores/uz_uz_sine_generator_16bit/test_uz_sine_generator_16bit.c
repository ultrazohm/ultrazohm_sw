#ifdef TEST

#include "unity.h"

#include "uz_sine_generator_16bit.h"
#include "mock_uz_fixedpoint.h"
#include "test_assert_with_exception.h"
#include "mock_uz_sine_generator_16bit_hw.h"
#include "uz_struct_helper.h"

#define TEST_BASE_ADDRESS 0x0000000Fu
#define TEST_IP_CORE_FRQ 100000000u

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_sine_generator_16bit_NeedToImplement(void)
{
    struct uz_sine_generator_16bit_config_t config =
        {
            .base_address = TEST_BASE_ADDRESS,
            .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
            .amplitude = {1, 2, 3, 4, 1.5, 2.5, 3.5, 4.5},
            .phase = {0, 0, 0, 0, 0, 0, 0, 0},
            .frequency = {10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000}};

    uz_sine_generator_16bit_t *test=uz_sine_generator_16bit_init(config);
}

#endif // TEST
