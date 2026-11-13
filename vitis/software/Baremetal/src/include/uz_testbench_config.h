#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "../IP_Cores/uz_axi_gpio/uz_axi_gpio.h"
#include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"

typedef enum {
    UZ_MOTOR_BECKHOFF,
    UZ_MOTOR_HM,
    UZ_MOTOR_COUNT
} uz_motor_id_t;

typedef enum {
    UZ_INVERTER_DHG,
    UZ_INVERTER_WS,
    UZ_INVERTER_COUNT
} uz_inverter_id_t;

typedef enum {
    UZ_PWM_OUTPUT_2L_0,
    UZ_PWM_OUTPUT_2L_1,
    UZ_PWM_OUTPUT_COUNT
} uz_pwm_output_id_t;

typedef enum {
    UZ_DEADTIME_OUTPUT_2L_0,
    UZ_DEADTIME_OUTPUT_2L_1,
    UZ_DEADTIME_OUTPUT_COUNT
} uz_deadtime_output_id_t;

typedef enum {
    UZ_ADC_SOURCE_UNCONFIGURED,
    UZ_ADC_SOURCE_A1,
    UZ_ADC_SOURCE_A2,
    UZ_ADC_SOURCE_A3,
    UZ_ADC_SOURCE_COUNT
} uz_adc_source_id_t;

typedef struct {
    uint8_t phase_a;
    uint8_t phase_b;
    uint8_t phase_c;
    uint8_t dc_link;
} uz_testbench_adc_channels_t;

typedef struct {
    float phase_a_gain;
    float phase_b_gain;
    float phase_c_gain;
    float dc_link_gain;
    float phase_a_offset;
    float phase_b_offset;
    float phase_c_offset;
    float dc_link_offset;
} uz_testbench_adc_scaling_t;

typedef struct {
    uz_adc_source_id_t source;
    uz_testbench_adc_channels_t current_channels;
    uz_testbench_adc_channels_t voltage_channels;
    uz_testbench_adc_scaling_t current_scaling;
    uz_testbench_adc_scaling_t voltage_scaling;
} uz_testbench_adc_config_t;

typedef struct {
    uz_inverter_id_t inverter;
    uint8_t resolver_channel;
    int8_t resolver_direction;
} uz_testbench_motor_config_t;

typedef struct {
    uz_pwm_output_id_t pwm_output;
    uz_deadtime_output_id_t deadtime_output;
    float deadtime_us;
    uz_testbench_adc_config_t adc;
} uz_testbench_inverter_config_t;

typedef struct {
    uz_testbench_motor_config_t motor[UZ_MOTOR_COUNT];
    uz_testbench_inverter_config_t inverter[UZ_INVERTER_COUNT];
} uz_testbench_config_t;

const uz_testbench_config_t *uz_testbench_get_config(void);
const uz_testbench_motor_config_t *uz_testbench_get_motor_config(uz_motor_id_t motor);
const uz_testbench_inverter_config_t *uz_testbench_get_inverter_config(uz_inverter_id_t inverter);
uz_PWM_SS_2L_t *uz_testbench_get_pwm_for_motor(uz_motor_id_t motor);
uz_interlockDeadtime2L_handle uz_testbench_get_deadtime_for_motor(uz_motor_id_t motor);
uz_adcLtc2311_t *uz_testbench_get_adc_for_motor(uz_motor_id_t motor);
uz_axi_gpio_t *uz_testbench_get_gpio_for_inverter(uz_inverter_id_t inverter);
uz_resolver_pl_interface_t *uz_testbench_get_resolver_for_motor(uz_motor_id_t motor);
bool uz_testbench_validate_config(void);
bool uz_testbench_hardware_init(void);
