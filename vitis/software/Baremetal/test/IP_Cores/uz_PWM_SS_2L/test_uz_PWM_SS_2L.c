#ifdef TEST

#include "unity.h"

#include "uz_PWM_SS_2L.h"

#include "test_assert_with_exception.h"
#include "uz_PWM_SS_2L.h"
#include "mock_uz_PWM_SS_2L_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

struct uz_PWM_SS_2L_t {
    bool is_ready;
    struct uz_PWM_SS_2L_config_t config;
};


void test_uz_PWM_SS_2L_set_duty_cycle(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = 0,
        .Tristate_HB2 = 0,
        .Tristate_HB3 = 0,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = 1,
        .CntExtSrc = 0,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };
    uz_PWM_SS_2L_t *instance = uz_PWM_SS_2L_init(config);

    uz_PWM_SS_2L_hw_SetStatus_Expect(instance->config.base_address, instance->config.PWM_en);
    uz_PWM_SS_2L_hw_SetMode_Expect(instance->config.base_address, instance->config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(instance->config.base_address, instance->config.CntExtSrc);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(instance->config.base_address, instance->config.ip_clk_frequency_Hz, instance->config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(instance->config.base_address, instance->config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(instance->config.base_address, instance->config.init_dutyCyc_A, instance->config.init_dutyCyc_B, instance->config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 1, instance->config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 2, instance->config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 3, instance->config.Tristate_HB3);

    uz_PWM_SS_2L_set_config(instance);

    float dutyCyc_A = 0.5;
    float dutyCyc_B = 0.5;   
    float dutyCyc_C = 0.5;
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(instance->config.base_address, dutyCyc_A, dutyCyc_B, dutyCyc_C);
    uz_PWM_SS_2L_set_duty_cycle(instance, dutyCyc_A, dutyCyc_B, dutyCyc_C);
}

void test_uz_PWM_SS_2L_init(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = 0,
        .Tristate_HB2 = 0,
        .Tristate_HB3 = 0,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = 1,
        .CntExtSrc = 0,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };
    uz_PWM_SS_2L_t *instance = uz_PWM_SS_2L_init(config);

    uz_PWM_SS_2L_hw_SetStatus_Expect(instance->config.base_address, instance->config.PWM_en);
    uz_PWM_SS_2L_hw_SetMode_Expect(instance->config.base_address, instance->config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(instance->config.base_address, instance->config.CntExtSrc);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(instance->config.base_address, instance->config.ip_clk_frequency_Hz, instance->config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(instance->config.base_address, instance->config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(instance->config.base_address, instance->config.init_dutyCyc_A, instance->config.init_dutyCyc_B, instance->config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 1, instance->config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 2, instance->config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(instance->config.base_address, 3, instance->config.Tristate_HB3);

    uz_PWM_SS_2L_set_config(instance);
}

void test_uz_PWM_SS_2L_init_with_zero_base_Address(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    config.base_address = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_init(config));
}

void test_uz_PWM_SS_2L_init_with_zero_ip_clk(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    config.ip_clk_frequency_Hz = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_init(config));
}

#endif // TEST
