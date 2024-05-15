#include "../include/pwm_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_PWM_SS_2L_config_t pwm_config_0 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
//        .Tristate_HB1 = true,
//        .Tristate_HB2 = true,
//        .Tristate_HB3 = true,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY_0,
		.PWM_mode = normalized_input_via_AXI,
//        .PWM_mode = direct_control_via_FPGA,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_1 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_1_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY_1,
//        .PWM_mode = normalized_input_via_AXI,
		.PWM_mode = direct_control_via_FPGA,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_2 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_2_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY_2,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

static struct uz_PWM_SS_2L_config_t pwm_config_3 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_3_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY_3,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_HB1 = 0.0f,
        .init_dutyCyc_HB2 = 0.0f,
        .init_dutyCyc_HB3 = 0.0f,
		.triangle_shift_HB1 = 0.0f,
		.triangle_shift_HB2 = 0.0f,
		.triangle_shift_HB3 = 0.0f,
		.trigger_source = trigger_at_MIN
};

uz_PWM_SS_2L_t* initialize_pwm_0_2l(void){
	return (uz_PWM_SS_2L_init(pwm_config_0));
}

uz_PWM_SS_2L_t* initialize_pwm_1_2l(void){
	return (uz_PWM_SS_2L_init(pwm_config_1));
}

uz_PWM_SS_2L_t* initialize_pwm_2_2l(void){
	return (uz_PWM_SS_2L_init(pwm_config_2));
}

uz_PWM_SS_2L_t* initialize_pwm_3_2l(void){
	return (uz_PWM_SS_2L_init(pwm_config_3));
}
