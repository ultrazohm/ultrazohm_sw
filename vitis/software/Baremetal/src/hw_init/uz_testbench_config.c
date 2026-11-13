#include "../main.h"
#include "../include/uz_testbench_config.h"
extern DS_Data Global_Data;

static const uz_testbench_config_t testbench_config = {
    .motor = {
        [UZ_MOTOR_BECKHOFF] = {
            .inverter = UZ_INVERTER_DHG,
            .resolver_channel = 1U,
            .resolver_direction = 1
        },
        [UZ_MOTOR_HM] = {
            .inverter = UZ_INVERTER_WS,
            .resolver_channel = 3U,
            .resolver_direction = -1
        }
    },
    .inverter = {
        [UZ_INVERTER_DHG] = {
            .pwm_output = UZ_PWM_OUTPUT_2L_1,
            .deadtime_output = UZ_DEADTIME_OUTPUT_2L_1,
            .deadtime_us = UZ_PWM_DEADTIME_IN_US,
            .adc = {
                .source = UZ_ADC_SOURCE_A2,
                .current_channels = {.phase_a = 0U, .phase_b = 1U, .phase_c = 2U, .dc_link = 7U},
                .voltage_channels = {.phase_a = 4U, .phase_b = 5U, .phase_c = 6U, .dc_link = 3U},
                .current_scaling = {
                    .phase_a_gain = 40.0f, .phase_b_gain = 40.0f,
                    .phase_c_gain = 40.0f, .dc_link_gain = 40.0f,
                    .phase_a_offset = -0.15f, .phase_b_offset = 0.1f,
                    .phase_c_offset = -0.05f, .dc_link_offset = -0.3f
                },
                .voltage_scaling = {
                    .phase_a_gain = 363.6f, .phase_b_gain = 363.6f,
                    .phase_c_gain = 37.037f, .dc_link_gain = 142.3f,
                    .phase_a_offset = -0.0033f * 363.6f,
                    .phase_b_offset = -0.001f * 363.6f,
                    .phase_c_offset = -0.0017f * 37.037f,
                    .dc_link_offset = 0.0005f * 142.3f
                }
            }
        },
        [UZ_INVERTER_WS] = {
            .pwm_output = UZ_PWM_OUTPUT_2L_0,
            .deadtime_output = UZ_DEADTIME_OUTPUT_2L_0,
            .deadtime_us = UZ_PWM_DEADTIME_IN_US,
            /* The WS ADC adapter and calibration are not identified in the current source. */
            .adc = {
                .source = UZ_ADC_SOURCE_A1,
                .current_channels = {.phase_a = 0U, .phase_b = 1U, .phase_c = 2U, .dc_link = 7U},
                .voltage_channels = {.phase_a = 4U, .phase_b = 5U, .phase_c = 6U, .dc_link = 3U},
                .current_scaling = {
                    .phase_a_gain = 1.0f, .phase_b_gain = 1.0f,
                    .phase_c_gain = 1.0f, .dc_link_gain = 1.0f,
                    .phase_a_offset = -1.75f, .phase_b_offset = -1.75f,
                    .phase_c_offset = -1.75f, .dc_link_offset = 3.7f
                },
                .voltage_scaling = {
                    .phase_a_gain = 1.0f, .phase_b_gain = 1.0f,
                    .phase_c_gain = 1.0f, .dc_link_gain = 1.0f,
                    .phase_a_offset = 0.0f,
                    .phase_b_offset = 0.0f,
                    .phase_c_offset = 0.0f,
                    .dc_link_offset = 0.0f
                }
            }
        }
    }
};

const uz_testbench_config_t *uz_testbench_get_config(void)
{
    return &testbench_config;
}

const uz_testbench_motor_config_t *uz_testbench_get_motor_config(uz_motor_id_t motor)
{
    if ((int)motor < 0 || motor >= UZ_MOTOR_COUNT) {
        return NULL;
    }
    return &testbench_config.motor[motor];
}

const uz_testbench_inverter_config_t *uz_testbench_get_inverter_config(uz_inverter_id_t inverter)
{
    if ((int)inverter < 0 || inverter >= UZ_INVERTER_COUNT) {
        return NULL;
    }
    return &testbench_config.inverter[inverter];
}

static uz_PWM_SS_2L_t *get_pwm_output(uz_pwm_output_id_t output)
{
    switch (output) {
    case UZ_PWM_OUTPUT_2L_0:
        return Global_Data.objects.project_wizard_pwm_2l_0;
    case UZ_PWM_OUTPUT_2L_1:
        return Global_Data.objects.project_wizard_pwm_2l_1;
    default:
        uz_assert(0);
        return NULL;
    }
}

static uz_axi_gpio_t *get_gpio_for_pwm_output(uz_pwm_output_id_t output)
{
    switch (output) {
    case UZ_PWM_OUTPUT_2L_0:
        return Global_Data.objects.axi_gpio_d1;
    case UZ_PWM_OUTPUT_2L_1:
        return Global_Data.objects.axi_gpio_d2;
    default:
        uz_assert(0);
        return NULL;
    }
}

static uz_interlockDeadtime2L_handle get_deadtime_output(uz_deadtime_output_id_t output)
{
    switch (output) {
    case UZ_DEADTIME_OUTPUT_2L_0:
        return Global_Data.objects.project_wizard_deadtime_2l_0;
    case UZ_DEADTIME_OUTPUT_2L_1:
        return Global_Data.objects.project_wizard_deadtime_2l_1;
    default:
        return NULL;
    }
}

static uz_adcLtc2311_t *get_adc_source(uz_adc_source_id_t source)
{
    switch (source) {
    case UZ_ADC_SOURCE_A1:
        return Global_Data.objects.adc_ltc2311_a1;
    case UZ_ADC_SOURCE_A2:
        return Global_Data.objects.adc_ltc2311_a2;
    case UZ_ADC_SOURCE_A3:
        return Global_Data.objects.adc_ltc2311_a3;
    case UZ_ADC_SOURCE_UNCONFIGURED:
    default:
        return NULL;
    }
}

static uz_resolver_pl_interface_t *get_resolver(uint8_t channel)
{
    switch (channel) {
    case 1U:
        return Global_Data.objects.resolver_pl_interface_d4_1;
    case 2U:
        return Global_Data.objects.resolver_pl_interface_d4_2;
    case 3U:
        return Global_Data.objects.resolver_pl_interface_d4_3;
    default:
        return NULL;
    }
}

uz_PWM_SS_2L_t *uz_testbench_get_pwm_for_motor(uz_motor_id_t motor)
{
    const uz_testbench_motor_config_t *motor_config = uz_testbench_get_motor_config(motor);
    const uz_testbench_inverter_config_t *inverter_config;

    if (motor_config == NULL) {
        return NULL;
    }
    inverter_config = uz_testbench_get_inverter_config(motor_config->inverter);
    return (inverter_config != NULL) ? get_pwm_output(inverter_config->pwm_output) : NULL;
}

uz_interlockDeadtime2L_handle uz_testbench_get_deadtime_for_motor(uz_motor_id_t motor)
{
    const uz_testbench_motor_config_t *motor_config = uz_testbench_get_motor_config(motor);
    const uz_testbench_inverter_config_t *inverter_config;

    if (motor_config == NULL) {
        return NULL;
    }
    inverter_config = uz_testbench_get_inverter_config(motor_config->inverter);
    return (inverter_config != NULL) ? get_deadtime_output(inverter_config->deadtime_output) : NULL;
}

uz_adcLtc2311_t *uz_testbench_get_adc_for_motor(uz_motor_id_t motor)
{
    const uz_testbench_motor_config_t *motor_config = uz_testbench_get_motor_config(motor);
    const uz_testbench_inverter_config_t *inverter_config;

    if (motor_config == NULL) {
        return NULL;
    }
    inverter_config = uz_testbench_get_inverter_config(motor_config->inverter);
    return (inverter_config != NULL) ? get_adc_source(inverter_config->adc.source) : NULL;
}

uz_axi_gpio_t *uz_testbench_get_gpio_for_inverter(uz_inverter_id_t inverter)
{
    const uz_testbench_inverter_config_t *inverter_config = uz_testbench_get_inverter_config(inverter);
    return (inverter_config != NULL) ? get_gpio_for_pwm_output(inverter_config->pwm_output) : NULL;
}

uz_resolver_pl_interface_t *uz_testbench_get_resolver_for_motor(uz_motor_id_t motor)
{
    const uz_testbench_motor_config_t *motor_config = uz_testbench_get_motor_config(motor);
    return (motor_config != NULL) ? get_resolver(motor_config->resolver_channel) : NULL;
}

static bool adc_channels_are_valid(uz_testbench_adc_channels_t channels)
{
    return channels.phase_a < 8U && channels.phase_b < 8U &&
           channels.phase_c < 8U && channels.dc_link < 8U;
}

static bool adc_scaling_is_valid(uz_testbench_adc_scaling_t scaling)
{
    return scaling.phase_a_gain > 0.0f && scaling.phase_b_gain > 0.0f &&
           scaling.phase_c_gain > 0.0f && scaling.dc_link_gain > 0.0f;
}

bool uz_testbench_validate_config(void)
{
    for (int motor = 0; motor < UZ_MOTOR_COUNT; motor++) {
        const uz_testbench_motor_config_t *motor_config = &testbench_config.motor[motor];
        if (motor_config->inverter >= UZ_INVERTER_COUNT ||
            motor_config->resolver_channel < 1U || motor_config->resolver_channel > 3U ||
            (motor_config->resolver_direction != -1 && motor_config->resolver_direction != 1)) {
            return false;
        }
        for (int other = motor + 1; other < UZ_MOTOR_COUNT; other++) {
            if (motor_config->inverter == testbench_config.motor[other].inverter ||
                motor_config->resolver_channel == testbench_config.motor[other].resolver_channel) {
                return false;
            }
        }
    }

    for (int inverter = 0; inverter < UZ_INVERTER_COUNT; inverter++) {
        const uz_testbench_inverter_config_t *inverter_config = &testbench_config.inverter[inverter];
        if (inverter_config->pwm_output >= UZ_PWM_OUTPUT_COUNT ||
            inverter_config->deadtime_output >= UZ_DEADTIME_OUTPUT_COUNT ||
            inverter_config->deadtime_us < 0.0f ||
            inverter_config->adc.source <= UZ_ADC_SOURCE_UNCONFIGURED ||
            inverter_config->adc.source >= UZ_ADC_SOURCE_COUNT) {
            return false;
        }
        if (!adc_channels_are_valid(inverter_config->adc.current_channels) ||
            !adc_channels_are_valid(inverter_config->adc.voltage_channels) ||
            !adc_scaling_is_valid(inverter_config->adc.current_scaling) ||
            !adc_scaling_is_valid(inverter_config->adc.voltage_scaling)) {
            return false;
        }
        for (int other = inverter + 1; other < UZ_INVERTER_COUNT; other++) {
            const uz_testbench_inverter_config_t *other_config = &testbench_config.inverter[other];
            if (inverter_config->pwm_output == other_config->pwm_output ||
                inverter_config->deadtime_output == other_config->deadtime_output ||
                inverter_config->adc.source == other_config->adc.source) {
                return false;
            }
        }
    }
    return true;
}

bool uz_testbench_hardware_init(void)
{
    for (int output = 0; output < UZ_PWM_OUTPUT_COUNT; output++) {
        uz_PWM_SS_2L_t *pwm = get_pwm_output((uz_pwm_output_id_t)output);
        if (pwm == NULL) {
            uz_assert(0);
            return false;
        }
        uz_PWM_SS_2L_set_tristate(pwm, true, true, true);
    }

    if (!uz_testbench_validate_config()) {
        uz_assert(0);
        return false;
    }

    for (int motor = 0; motor < UZ_MOTOR_COUNT; motor++) {
        if (get_resolver(testbench_config.motor[motor].resolver_channel) == NULL) {
            uz_assert(0);
            return false;
        }
    }

    for (int inverter = 0; inverter < UZ_INVERTER_COUNT; inverter++) {
        const uz_testbench_inverter_config_t *inverter_config = &testbench_config.inverter[inverter];
        if (get_adc_source(inverter_config->adc.source) == NULL ||
            get_gpio_for_pwm_output(inverter_config->pwm_output) == NULL) {
            uz_assert(0);
            return false;
        }
    }

    for (int inverter = 0; inverter < UZ_INVERTER_COUNT; inverter++) {
        const uz_testbench_inverter_config_t *inverter_config = &testbench_config.inverter[inverter];
        uz_interlockDeadtime2L_handle deadtime = get_deadtime_output(inverter_config->deadtime_output);

        if (deadtime == NULL) {
            uz_assert(0);
            return false;
        }
        uz_interlockDeadtime2L_set_enable_output(deadtime, false);
        uz_interlockDeadtime2L_set_deadtime_us(deadtime, inverter_config->deadtime_us);
        uz_interlockDeadtime2L_set_enable_output(deadtime, true);
    }
    return true;
}
