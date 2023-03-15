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
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
        .triangle_shift_HB1 = 0.5f,
        .triangle_shift_HB2 = 0.5f,
        .triangle_shift_HB3 = 0.5f
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_HB1, config.init_dutyCyc_HB2, config.init_dutyCyc_HB3);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, config.triangle_shift_HB1, config.triangle_shift_HB2, config.triangle_shift_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    enum uz_PWM_SS_2L_PWM_mode pwm_mode = direct_control_via_FPGA;

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
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
        .triangle_shift_HB1 = 0.5f,
        .triangle_shift_HB2 = 0.5f,
        .triangle_shift_HB3 = 0.5f
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_HB1, config.init_dutyCyc_HB2, config.init_dutyCyc_HB3);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, config.triangle_shift_HB1, config.triangle_shift_HB2, config.triangle_shift_HB3);

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
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
        .triangle_shift_HB1 = 0.5f,
        .triangle_shift_HB2 = 0.5f,
        .triangle_shift_HB3 = 0.5f
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_HB1, config.init_dutyCyc_HB2, config.init_dutyCyc_HB3);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, config.triangle_shift_HB1, config.triangle_shift_HB2, config.triangle_shift_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    float dutyCyc_HB1 = 0.5f;
    float dutyCyc_HB2 = 0.5f;   
    float dutyCyc_HB3 = 0.5f;
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(self->config.base_address, dutyCyc_HB1, dutyCyc_HB2, dutyCyc_HB3);
    uz_PWM_SS_2L_set_duty_cycle(self, dutyCyc_HB1, dutyCyc_HB2, dutyCyc_HB3);
}

void test_uz_PWM_SS_2L_init(void)
{
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
        .triangle_shift_HB1 = 0.5f,
        .triangle_shift_HB2 = 0.5f,
        .triangle_shift_HB3 = 0.5f
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en);
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_HB1, config.init_dutyCyc_HB2, config.init_dutyCyc_HB3);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, config.triangle_shift_HB1, config.triangle_shift_HB2, config.triangle_shift_HB3);

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

void test_uz_PWM_SS_2L_set_triangle_shift_assert_NULL(void) {
    float triangle_shift_HB1 = 0.5f;
    float triangle_shift_HB2 = 0.5f;
    float triangle_shift_HB3 = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_SS_2L_set_triangle_shift(NULL,triangle_shift_HB1,triangle_shift_HB2,triangle_shift_HB3));
}

void test_uz_PWM_SS_2L_set_triangle_shift(void) {
    struct uz_PWM_SS_2L_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
        .triangle_shift_HB1 = 0.5f,
        .triangle_shift_HB2 = 0.5f,
        .triangle_shift_HB3 = 0.5f
    };

    uz_PWM_SS_2L_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_PWM_SS_2L_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_PWM_SS_2L_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_PWM_SS_2L_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_PWM_SS_2L_hw_SetMinimumPulseWidth_Expect(config.base_address, config.min_pulse_width);
    uz_PWM_SS_2L_hw_SetDutyCycle_Expect(config.base_address, config.init_dutyCyc_HB1, config.init_dutyCyc_HB2, config.init_dutyCyc_HB3);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_PWM_SS_2L_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, config.triangle_shift_HB1, config.triangle_shift_HB2, config.triangle_shift_HB3);

    uz_PWM_SS_2L_t *self = uz_PWM_SS_2L_init(config);

    float triangle_shift_HB1 = 0.75f;
    float triangle_shift_HB2 = 0.15445f;
    float triangle_shift_HB3 = 0.95f;
    uz_PWM_SS_2L_hw_SetTriangleShift_Expect(config.base_address, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3);
    uz_PWM_SS_2L_set_triangle_shift(self, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3);

}

#endif // TEST
