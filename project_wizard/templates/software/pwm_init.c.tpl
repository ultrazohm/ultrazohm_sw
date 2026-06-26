/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#include "../include/pwm_init.h"
#include "../defines.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_private.h"
#include "../IP_Cores/PWM_SS_3L_ip_addr.h"
#include "xil_io.h"
#include "xparameters.h"
#include <math.h>

{% for instance in pwm_2l_instances %}
static struct uz_PWM_SS_2L_config_t project_wizard_pwm_2l_{{ instance.index }}_config = {
    .base_address = {{ instance.pwm_base_address_macro }},
    .ip_clk_frequency_Hz = {{ instance.pwm_config.ip_clk_frequency_Hz }},
    .Tristate_HB1 = {{ instance.pwm_config.Tristate_HB1 }},
    .Tristate_HB2 = {{ instance.pwm_config.Tristate_HB2 }},
    .Tristate_HB3 = {{ instance.pwm_config.Tristate_HB3 }},
    .min_pulse_width_in_microseconds = {{ instance.pwm_config.min_pulse_width_in_microseconds }},
    .PWM_freq_Hz = {{ instance.pwm_config.PWM_freq_Hz }},
    .PWM_mode = {{ instance.pwm_config.PWM_mode }},
    .PWM_en = {{ instance.pwm_config.PWM_en }},
    .use_external_counter = {{ instance.pwm_config.use_external_counter }},
    .init_dutyCyc_HB1 = {{ instance.pwm_config.init_dutyCyc_HB1 }},
    .init_dutyCyc_HB2 = {{ instance.pwm_config.init_dutyCyc_HB2 }},
    .init_dutyCyc_HB3 = {{ instance.pwm_config.init_dutyCyc_HB3 }},
    .triangle_shift_HB1 = {{ instance.pwm_config.triangle_shift_HB1 }},
    .triangle_shift_HB2 = {{ instance.pwm_config.triangle_shift_HB2 }},
    .triangle_shift_HB3 = {{ instance.pwm_config.triangle_shift_HB3 }},
    .trigger_source = {{ instance.pwm_config.trigger_source }}
};

static uz_interlockDeadtime2L project_wizard_deadtime_2l_{{ instance.index }} = {
    .base_address = {{ instance.deadtime_base_address_macro }},
    .clock_frequency_MHz = {{ instance.deadtime_config.clock_frequency_MHz }},
    .deadtime_us = {{ instance.deadtime_config.deadtime_us }},
    .inverse_bottom_switch = {{ instance.deadtime_config.inverse_bottom_switch }}
};

uz_PWM_SS_2L_t* initialize_project_wizard_pwm_2l_{{ instance.index }}(void)
{
    return uz_PWM_SS_2L_init(project_wizard_pwm_2l_{{ instance.index }}_config);
}

uz_interlockDeadtime2L_handle initialize_project_wizard_deadtime_2l_{{ instance.index }}(void)
{
    return uz_interlockDeadtime2L_init(&project_wizard_deadtime_2l_{{ instance.index }});
}

{% endfor %}
{% if pwm_3l_enabled %}
#define PROJECT_WIZARD_PWM_3L_BASE_ADDRESS {{ pwm_3l_base_address_macro }}
#define PROJECT_WIZARD_PWM_3L_REG_RESET (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + IPCore_Reset_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_ENABLE (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_en_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_MODE (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + Mode_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_COUNTER_MAX (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_counter_max_value_int_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_MIN_PULSE_WIDTH (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + PWM_min_pulse_width_0to1_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_A (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u1_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_B (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u2_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_DUTY_C (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + m_u3_norm_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_A (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB1_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_B (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB2_AXI_Data_PWM_SS_3L_ip)
#define PROJECT_WIZARD_PWM_3L_REG_TRISTATE_C (PROJECT_WIZARD_PWM_3L_BASE_ADDRESS + TriState_HB3_AXI_Data_PWM_SS_3L_ip)

static void project_wizard_pwm_3l_set_status(int32_t enable)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_ENABLE, (int32_t)enable);
}

static void project_wizard_pwm_3l_set_mode(int32_t mode)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_MODE, (int32_t)mode);
}

static void project_wizard_pwm_3l_set_carrier_frequency(float pwm_freq_hz)
{
    float switching_period_s = 1.0f / pwm_freq_hz;
    float counter_max_value = switching_period_s * FPGA_100MHz / 2.0f;
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_COUNTER_MAX, (int32_t)counter_max_value);
}

static void project_wizard_pwm_3l_set_minimum_pulse_width(float minimum_pulse_width)
{
    LIMIT(minimum_pulse_width, 0.0f, 1.0f);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_MIN_PULSE_WIDTH, (int32_t)ldexpf(minimum_pulse_width, Q12));
}

static void project_wizard_pwm_3l_set_tristate(int32_t tristate_a, int32_t tristate_b, int32_t tristate_c)
{
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_A, (int32_t)tristate_a);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_B, (int32_t)tristate_b);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_TRISTATE_C, (int32_t)tristate_c);
}

static void project_wizard_pwm_3l_set_duty_cycle(float duty_a, float duty_b, float duty_c)
{
    LIMIT(duty_a, -1.0f, 1.0f);
    LIMIT(duty_b, -1.0f, 1.0f);
    LIMIT(duty_c, -1.0f, 1.0f);
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_A, (int32_t)ldexpf(duty_a, Q12));
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_B, (int32_t)ldexpf(duty_b, Q12));
    Xil_Out32(PROJECT_WIZARD_PWM_3L_REG_DUTY_C, (int32_t)ldexpf(duty_c, Q12));
}

void initialize_project_wizard_pwm_3l(DS_Data* data)
{
    project_wizard_pwm_3l_set_status({{ pwm_3l_config.enable }});
    project_wizard_pwm_3l_set_mode({{ pwm_3l_config.mode }});
    project_wizard_pwm_3l_set_carrier_frequency({{ pwm_3l_config.carrier_frequency_Hz }});
    project_wizard_pwm_3l_set_minimum_pulse_width({{ pwm_3l_config.minimum_pulse_width }});
    project_wizard_pwm_3l_set_duty_cycle(
        {{ pwm_3l_config.initial_duty_a }},
        {{ pwm_3l_config.initial_duty_b }},
        {{ pwm_3l_config.initial_duty_c }}
    );
    project_wizard_pwm_3l_set_tristate(
        {{ pwm_3l_config.tristate_a }},
        {{ pwm_3l_config.tristate_b }},
        {{ pwm_3l_config.tristate_c }}
    );
}

{% endif %}
void project_wizard_update_pwm_outputs(DS_Data* data)
{
{% for instance in pwm_2l_instances %}
    uz_PWM_SS_2L_set_duty_cycle(
        data->objects.project_wizard_pwm_2l_{{ instance.index }},
        data->rasv.halfBridge{{ instance.half_bridge_a }}DutyCycle,
        data->rasv.halfBridge{{ instance.half_bridge_b }}DutyCycle,
        data->rasv.halfBridge{{ instance.half_bridge_c }}DutyCycle
    );
{% endfor %}
{% if pwm_3l_enabled %}
    project_wizard_pwm_3l_set_duty_cycle(
        data->rasv.halfBridge1DutyCycle,
        data->rasv.halfBridge2DutyCycle,
        data->rasv.halfBridge3DutyCycle
    );
{% endif %}
}
