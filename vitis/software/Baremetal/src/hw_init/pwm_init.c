#include "../include/pwm_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_PWM_SS_2L_config_t pwm_config_d1_pin_0_to_5 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_d1_pin_6_to_11 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_d1_pin_12_to_17 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_2_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_d1_pin_18_to_23 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_3_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = true,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_0_to_5(void){
	return (uz_PWM_SS_2L_init(pwm_config_d1_pin_0_to_5));
}

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_6_to_11(void){
	return (uz_PWM_SS_2L_init(pwm_config_d1_pin_6_to_11));
}

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_12_to_17(void){
	return (uz_PWM_SS_2L_init(pwm_config_d1_pin_12_to_17));
}

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1_pin_18_to_23(void){
	return (uz_PWM_SS_2L_init(pwm_config_d1_pin_18_to_23));
}
