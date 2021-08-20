#ifdef TEST

#include "unity.h"

#include "uz_d_gan_inverter.h"
#include "test_assert_with_exception.h"
#include "uz_d_gan_inverter.h"
#include "mock_uz_d_gan_inverter_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

    struct uz_d_gan_inverter_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    };

    struct uz_d_gan_inverter_outputs_t output = {
        .PWMdutyCycPerCent_H1 = 6.5,
        .PWMdutyCycPerCent_L1 = 6.5,
        .PWMdutyCycPerCent_H2 = 6.5,
        .PWMdutyCycPerCent_L2 = 6.5,
        .PWMdutyCycPerCent_H3 = 6.5,
        .PWMdutyCycPerCent_L3 = 6.5,
    };

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_d_gan_inverter_successful_init(void)
{
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_d_gan_inverter_get_temperature_degrees_celsius(void)
{
    float dutycycle_percent = 6.5;
    float temperature_degrees_celsius = 30.6821;
    float temperature_degrees_celsius_readback = uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(dutycycle_percent);
    TEST_ASSERT_EQUAL_FLOAT(temperature_degrees_celsius,temperature_degrees_celsius_readback);
}


void test_uz_d_gan_inverter_update_states(void)
{
    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(config);
    uz_d_gan_inverter_update_states(test_instance);
}
#endif // TEST
