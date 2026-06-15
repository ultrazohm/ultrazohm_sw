#ifdef TEST

#include "unity.h"

#include "uz_SVPWM6phIP.h"
#include "test_assert_with_exception.h"
#include "mock_uz_SVPWM6phIP_hw.h" // Mock the _hw functions to isolate testing
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

struct uz_SVPWM6phIP_t {
    bool is_ready;
    struct uz_SVPWM6phIP_config_t config;
};


void test_uz_SVPWM6phIP_set_pwm_mode(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .Tristate_HB4 = false,
        .Tristate_HB5 = false,
        .Tristate_HB6 = false,
        .min_Ton_time = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_T1 = 0.0f,
        .init_T2 = 0.0f,
        .init_T3 = 0.0f,
        .init_T4 = 0.0f,
        .init_T5 = 0.0f,
        .init_SV1 = 0,
        .init_SV2 = 0,
        .init_SV3 = 0,
        .init_SV4 = 0,
        .init_SV5 = 0,
        .trigger_source = trigger_at_MIN
    };

    uz_SVPWM6phIP_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_SVPWM6phIP_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_SVPWM6phIP_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_SVPWM6phIP_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_SVPWM6phIP_hw_SetMinimumTon_Expect(config.base_address, config.min_Ton_time);
    uz_SVPWM6phIP_hw_Set_T_and_SV_Expect(config.base_address, config.init_T1, config.init_T2, config.init_T3, config.init_T4, config.init_T5, config.init_SV1, config.init_SV2, config.init_SV3, config.init_SV4, config.init_SV5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 4, config.Tristate_HB4);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 5, config.Tristate_HB5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 6, config.Tristate_HB6);
    uz_SVPWM6phIP_hw_SetTriggerSource_Expect(config.base_address, config.trigger_source);

    uz_SVPWM6phIP_t *self = uz_SVPWM6phIP_init(config);

    enum uz_SVPWM6phIP_PWM_mode pwm_mode = direct_control_via_FPGA;

    uz_SVPWM6phIP_hw_SetMode_Expect(self->config.base_address, pwm_mode);
    uz_SVPWM6phIP_set_PWM_mode(self, pwm_mode);
}

void test_uz_SVPWM6phIP_set_tristate(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .Tristate_HB4 = false,
        .Tristate_HB5 = false,
        .Tristate_HB6 = false,
        .min_Ton_time = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_T1 = 0.0f,
        .init_T2 = 0.0f,
        .init_T3 = 0.0f,
        .init_T4 = 0.0f,
        .init_T5 = 0.0f,
        .init_SV1 = 0,
        .init_SV2 = 0,
        .init_SV3 = 0,
        .init_SV4 = 0,
        .init_SV5 = 0,
        .trigger_source = trigger_at_MIN
    };
    uz_SVPWM6phIP_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_SVPWM6phIP_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_SVPWM6phIP_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_SVPWM6phIP_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_SVPWM6phIP_hw_SetMinimumTon_Expect(config.base_address, config.min_Ton_time);
    uz_SVPWM6phIP_hw_Set_T_and_SV_Expect(config.base_address, config.init_T1, config.init_T2, config.init_T3, config.init_T4, config.init_T5, config.init_SV1, config.init_SV2, config.init_SV3, config.init_SV4, config.init_SV5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 4, config.Tristate_HB4);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 5, config.Tristate_HB5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 6, config.Tristate_HB6);
    uz_SVPWM6phIP_hw_SetTriggerSource_Expect(config.base_address, config.trigger_source);

    uz_SVPWM6phIP_t *self = uz_SVPWM6phIP_init(config);

    bool tristate_hb1 = false;
    bool tristate_hb2 = true;
    bool tristate_hb3 = true;
    bool tristate_hb4 = false;
    bool tristate_hb5 = true;
    bool tristate_hb6 = false;

    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 1,tristate_hb1);
    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 2,tristate_hb2);
    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 3,tristate_hb3);
    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 4,tristate_hb4);
    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 5,tristate_hb5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(self->config.base_address, 6,tristate_hb6);
    uz_SVPWM6phIP_set_tristate(self, tristate_hb1, tristate_hb2, tristate_hb3, tristate_hb4, tristate_hb5, tristate_hb6);
}

void test_uz_SVPWM6phIP_set_T_and_SV(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .Tristate_HB4 = false,
        .Tristate_HB5 = false,
        .Tristate_HB6 = false,
        .min_Ton_time = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_T1 = 0.0f,
        .init_T2 = 0.0f,
        .init_T3 = 0.0f,
        .init_T4 = 0.0f,
        .init_T5 = 0.0f,
        .init_SV1 = 0,
        .init_SV2 = 0,
        .init_SV3 = 0,
        .init_SV4 = 0,
        .init_SV5 = 0,
        .trigger_source = trigger_at_MIN
    };

    float T1 = 0.5f;
    float T2 = 0.2f;   
    float T3 = 0.1f;
    float T4 = 0.3f;
    float T5 = 0.6f;

    uint32_t SV1 = 43;
    uint32_t SV2 = 18;
    uint32_t SV3 = 16;
    uint32_t SV4 = 14;
    uint32_t SV5 = 20;
    uz_SVPWM6phIP_hw_Set_T_and_SV_Expect(config.base_address, T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5);
    uz_SVPWM6phIP_hw_Set_T_and_SV(config.base_address, T1,T2,T3,T4,T5,SV1,SV2,SV3,SV4,SV5);
}

void test_uz_SVPWM6phIP_init(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .Tristate_HB4 = false,
        .Tristate_HB5 = false,
        .Tristate_HB6 = false,
        .min_Ton_time = 0.01f,
        .PWM_freq_Hz = 100e6f,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_T1 = 0.0f,
        .init_T2 = 0.0f,
        .init_T3 = 0.0f,
        .init_T4 = 0.0f,
        .init_T5 = 0.0f,
        .init_SV1 = 0,
        .init_SV2 = 0,
        .init_SV3 = 0,
        .init_SV4 = 0,
        .init_SV5 = 0,
        .trigger_source = trigger_at_MIN
    };

    uz_SVPWM6phIP_hw_SetStatus_Expect(config.base_address, config.PWM_en); 
    uz_SVPWM6phIP_hw_SetMode_Expect(config.base_address, config.PWM_mode);
    uz_SVPWM6phIP_hw_SetExternalCounterSource_Expect(config.base_address, config.use_external_counter);
    uz_SVPWM6phIP_hw_SetCarrierFrequency_Expect(config.base_address, config.ip_clk_frequency_Hz, config.PWM_freq_Hz);
    uz_SVPWM6phIP_hw_SetMinimumTon_Expect(config.base_address, config.min_Ton_time);
    uz_SVPWM6phIP_hw_Set_T_and_SV_Expect(config.base_address, config.init_T1, config.init_T2, config.init_T3, config.init_T4, config.init_T5, config.init_SV1, config.init_SV2, config.init_SV3, config.init_SV4, config.init_SV5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 1, config.Tristate_HB1);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 2, config.Tristate_HB2);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 3, config.Tristate_HB3);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 4, config.Tristate_HB4);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 5, config.Tristate_HB5);
    uz_SVPWM6phIP_hw_SetTristate_Expect(config.base_address, 6, config.Tristate_HB6);
    uz_SVPWM6phIP_hw_SetTriggerSource_Expect(config.base_address, config.trigger_source);

    uz_SVPWM6phIP_init(config); //call without use of return value to avoid compiler warning of unused variable
}

void test_uz_SVPWM6phIP_init_with_zero_base_Address(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    config.base_address = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_init(config));
}

void test_uz_SVPWM6phIP_init_with_zero_ip_clk(void)
{
    struct uz_SVPWM6phIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    config.ip_clk_frequency_Hz = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_SVPWM6phIP_init(config));
}

#endif // TEST

