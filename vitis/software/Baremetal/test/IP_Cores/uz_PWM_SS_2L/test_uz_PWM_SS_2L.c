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


void test_uz_PWM_SS_2L_set_pwm_mode(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_A, config.init_dutyCyc_B, config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    uint32_t pwm_mode = 2;

    uz_PWM_SS_2L_hw_SetMode_Expect(self->config.base_address, pwm_mode);
    uz_PWM_SS_2L_set_PWM_mode(self, pwm_mode);
}

void test_uz_PWM_SS_2L_set_tristate(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_A, config.init_dutyCyc_B, config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    bool tristate_hb1 = false;
    bool tristate_hb2 = true;
    bool tristate_hb3 = true;

    uz_PWM_SS_2L_hw_SetTristate_Expect(self->config.base_address, 1,tristate_hb1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(self->config.base_address, 2,tristate_hb2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(self->config.base_address, 3,tristate_hb3);
    uz_PWM_SS_2L_set_tristate(self, tristate_hb1, tristate_hb2, tristate_hb3);
}

void test_uz_PWM_SS_2L_set_duty_cycle(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_A, config.init_dutyCyc_B, config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    float dutyCyc_A = 0.5;
    float dutyCyc_B = 0.5;   
    float dutyCyc_C = 0.5;
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(self->config.base_address, dutyCyc_A, dutyCyc_B, dutyCyc_C);
    uz_PWM_SS_2L_set_duty_cycle(self, dutyCyc_A, dutyCyc_B, dutyCyc_C);
}

void test_uz_PWM_SS_2L_init(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01,
        .PWM_freq_Hz = 100e6,
        .PWM_mode = 0,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_A = 0.0,
        .init_dutyCyc_B = 0.0,
        .init_dutyCyc_C = 0.0
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en);
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_A, config.init_dutyCyc_B, config.init_dutyCyc_C);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);

    uz_PWM_SS_2L_init(config); //call without use of return value to avoid compiler warning of unused variable
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
