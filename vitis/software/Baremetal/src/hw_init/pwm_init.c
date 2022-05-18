#include "../include/pwm_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_PWM_SS_2L_config_t pwm_config_d1 = {
        .base_address= XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR,
        .ip_clk_frequency_Hz=100000000,
        .Tristate_HB1 = false,
        .Tristate_HB2 = false,
        .Tristate_HB3 = false,
        .min_pulse_width = 0.01f,
        .PWM_freq_Hz = UZ_PWM_FREQUENCY,
        .PWM_mode = normalized_input_via_AXI,
        .PWM_en = true,
        .use_external_counter = false,
        .init_dutyCyc_A = 0.0f,
        .init_dutyCyc_B = 0.0f,
        .init_dutyCyc_C = 0.0f
};

uz_PWM_SS_2L_t* initialize_pwm_2l_on_D1(void){
	return (uz_PWM_SS_2L_init(pwm_config_d1));
}
