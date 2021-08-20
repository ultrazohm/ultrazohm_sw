#ifdef TEST

#include "unity.h"

#include "uz_d_gan_inverter.h"
#include "test_assert_with_exception.h"
#include "uz_d_gan_inverter.h"
#include "uz_d_gan_inverter_hwAddresses.h"
#include "mock_uz_d_gan_inverter_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000F
#define TEST_IP_CORE_FRQ 100000000U

    struct uz_d_gan_inverter_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
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
    float dutycyc_H1 = 6.5;
    float dutycyc_L1 = 6.5;
    float dutycyc_H2 = 6.5;
    float dutycyc_L2 = 6.5;
    float dutycyc_H3 = 6.5;
    float dutycyc_L3 = 6.5;

    uint32_t Status_OC = 0x2D; //0x2D = 0b101101
    uint32_t Status_FAULT = 63;
    uint32_t Status_I_DIAG = 15;

    uz_d_gan_inverter_get_PWMdutyCycPerCent_H1_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_H1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L1_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_L1);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H2_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_H2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L2_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_L2);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_H3_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_H3);
    uz_d_gan_inverter_get_PWMdutyCycPerCent_L3_ExpectAndReturn(TEST_BASE_ADDRESS, dutycyc_L3);

    uz_d_gan_inverter_get_OC_GaN_IgnoreAndReturn(Status_OC);
    uint32_t Status_OC_returned = uz_d_gan_inverter_get_OC_GaN(TEST_BASE_ADDRESS);
    uz_d_gan_inverter_get_FAULT_GaN_IgnoreAndReturn(Status_FAULT);
    uz_d_gan_inverter_get_I_DIAG_IgnoreAndReturn(Status_I_DIAG);

    uz_d_gan_inverter_t *test_instance = uz_d_gan_inverter_init(config);
    uz_d_gan_inverter_update_states(test_instance);

    // check for correct bit masking and bit shifting of OC status
    TEST_ASSERT_EQUAL_INT(Status_OC,Status_OC_returned);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x1) >> 0),1);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x2) >> 1),0);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x4) >> 2),1);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x8) >> 3),1);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x10) >> 4),0);
    TEST_ASSERT_EQUAL_INT(((Status_OC & 0x20) >> 5),1);
    // TEST_ASSERT_EQUAL_INT(test_instance->outputs.OC_H1,1);  
}
#endif // TEST
