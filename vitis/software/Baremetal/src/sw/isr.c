/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/pwm_init.h"
#include "../include/project_wizard_visualization.h"
#include "../include/error_checks.h"
#include "../include/wolfspeed_inverter_temperature.h"
#include "../uz/uz_math_constants.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

/* Project Wizard BEGIN: adc_readout_definitions */
static uz_array_int16_t analog_adc_data;
/* Project Wizard END: adc_readout_definitions */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void update_adapter_a1(void);
static void update_adapter_a2(void);
static void update_adapter_a3(void);
static void update_adapter_d1(void);
static void update_adapter_d2(void);
static void update_adapter_d3(void);
static void update_adapter_d4(void);
static void update_adapter_d5(void);
static void reset_im_current_offset_calibration(void);
static void update_setpoint_trajectories(void);
static float update_measurements(void);
static void update_temperature_user_led(float temperature_degC);
static void update_im_current_offset_calibration(platform_state_t current_state);
static platform_state_t update_protection(platform_state_t current_state);
static void update_im_control(float encoder_mechanical_angle_rad);

/* AXI-GPIO bit index matching the bitstream signal DIG_13. */
#define D1_DIG_13_PIN_ZERO_BASED 13U
#define D1_DIG_15_PIN_ZERO_BASED 15U

static const error_checks_config_t im_error_checks_config={.vdc_min_V=MOTOR_SOR_v_dc_lower_V,.vdc_max_V=MOTOR_SOR_v_dc_upper_V,.iphase_max_A=MOTOR_SOR_i_abc_upper_A,.max_mechanical_speed_rpm=MOTOR_SOR_speed_upper_rpm};
static float im_current_offset_a,im_current_offset_b,im_current_offset_c;
static double im_current_sum_a,im_current_sum_b,im_current_sum_c;
static double im_current_square_sum_a,im_current_square_sum_b,im_current_square_sum_c;
static uint32_t im_current_offset_samples;
static bool setpoint_trajectories_enabled_last = false;
static bool idle_reset_done;
static bool im_pwm_tristated_for_calibration;

static void reset_im_current_offset_calibration(void)
{
	im_current_offset_a = 0.0f;
	im_current_offset_b = 0.0f;
	im_current_offset_c = 0.0f;
	im_current_sum_a = 0.0;
	im_current_sum_b = 0.0;
	im_current_sum_c = 0.0;
	im_current_square_sum_a = 0.0;
	im_current_square_sum_b = 0.0;
	im_current_square_sum_c = 0.0;
	im_current_offset_samples = 0U;
}

static void update_setpoint_trajectories(void)
{
	float* const setpoints[SETPOINT_TRAJECTORY_COUNT] = {
		&Global_Data.rasv.im_i_d_reference_A,
		&Global_Data.rasv.im_i_q_reference_A,
		&Global_Data.rasv.im_frequency_reference_Hz,
		&Global_Data.rasv.im_speed_reference_rpm,
	};
	if (setpoint_trajectories_enabled_last && !Global_Data.rasv.setpoint_trajectories_enabled) {
		for (uint32_t trajectory = 0U; trajectory < SETPOINT_TRAJECTORY_COUNT; trajectory++) {
			uz_Trajectory_Stop(Global_Data.objects.setpoint_trajectories[trajectory].instance);
			uz_Trajectory_Reset(Global_Data.objects.setpoint_trajectories[trajectory].instance);
		}
	}
	setpoint_trajectories_enabled_last = Global_Data.rasv.setpoint_trajectories_enabled;
	for (uint32_t trajectory = 0U; trajectory < SETPOINT_TRAJECTORY_COUNT; trajectory++) {
		setpoint_trajectory_state_t * const state = &Global_Data.objects.setpoint_trajectories[trajectory];
		if (!Global_Data.rasv.setpoint_trajectories_enabled) {
			state->start = state->target;
			state->active_target = state->target;
			*setpoints[trajectory] = state->target;
			continue;
		}
		if (state->target != state->active_target) {
			state->start = *setpoints[trajectory];
			state->active_target = state->target;
			uz_Trajectory_Reset(state->instance);
			uz_Trajectory_Start(state->instance);
		}
		float const ramp_factor = uz_Trajectory_Step(state->instance);
		if (ramp_factor <= 0.0f) {
			uz_Trajectory_Stop(state->instance);
		}
		*setpoints[trajectory] = state->active_target + ramp_factor *
			(state->start - state->active_target);
	}
}

static float update_measurements(void)
{
	static bool v_dc_filter_initialized = false;
	float const encoder_mechanical_angle_rad =
		(2.0f * UZ_PIf * (float)(Global_Data.av.incremental_encoder_d5_2_position_w_offset %
		 MOTOR_ENCODER_INCREMENTS_PER_MECHANICAL_TURN)) /
		(float)MOTOR_ENCODER_INCREMENTS_PER_MECHANICAL_TURN;
	float const temperature_duty_ratio = uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(
		Global_Data.objects.inverter_temperature_pwm);
	Global_Data.av.inverter_temperature_pwm_duty_cycle_percent = temperature_duty_ratio * 100.0f;
	Global_Data.av.inverter_temperature_pwm_frequency_Hz = uz_PWM_duty_freq_detection_get_frequency_in_Hz(
		Global_Data.objects.inverter_temperature_pwm);
	Global_Data.av.inverter_temperature_degC = wolfspeed_inverter_temperature_from_duty_ratio(temperature_duty_ratio);
	update_temperature_user_led(Global_Data.av.inverter_temperature_degC);
	Global_Data.av.im_v_dc_V = Global_Data.av.adc_ltc2311_a1_ch3 - 2.5f;
	if (!v_dc_filter_initialized) {
		/* Prefill the complete window to avoid a zero-valued startup transient. */
		for (uint32_t sample = 0U; sample < MOTOR_V_DC_MOVING_AVERAGE_LENGTH; sample++) {
			Global_Data.av.im_v_dc_filtered_V = uz_movingAverageFilter_sample(
				Global_Data.objects.im_v_dc_moving_average, Global_Data.av.im_v_dc_V);
		}
		v_dc_filter_initialized = true;
	} else {
		Global_Data.av.im_v_dc_filtered_V = uz_movingAverageFilter_sample(
			Global_Data.objects.im_v_dc_moving_average, Global_Data.av.im_v_dc_V);
	}
	if (Global_Data.rasv.im_enable_foc) {
		Global_Data.av.im_speed_rpm = -Global_Data.av.incremental_encoder_d5_2_omega_mech
			* (60.0f / (2.0f * UZ_PIf));
	} else {
		/* Commissioning estimate for U/f operation with an assumed 2 % slip. */
		Global_Data.av.im_speed_rpm = Global_Data.av.im_control_actual.u_f_command_frequency_Hz
			* (60.0f / MOTOR_PolePairs) * 0.98f;
	}
	return encoder_mechanical_angle_rad;
}

static void update_temperature_user_led(float temperature_degC)
{
	bool led_on = false;
	if (isfinite(temperature_degC)) {
		if (temperature_degC >= INVERTER_TEMPERATURE_USER_LED_BLINK_DEG_C) {
			uint32_t const blink_phase = uz_SystemTime_GetUptimeInMs() /
				INVERTER_TEMPERATURE_USER_LED_BLINK_HALF_PERIOD_MS;
			led_on = (blink_phase % 2U) != 0U;
		} else if (temperature_degC >= INVERTER_TEMPERATURE_USER_LED_ON_DEG_C) {
			led_on = true;
		}
	}
	ultrazohm_state_machine_set_userLED(led_on);
}

static void update_im_current_offset_calibration(platform_state_t current_state)
{
	if (current_state != idle_state) im_pwm_tristated_for_calibration = false;
	if (im_current_offset_samples < MOTOR_CURRENT_OFFSET_SAMPLE_COUNT) {
		if ((current_state == idle_state) && im_pwm_tristated_for_calibration
			&& isfinite(Global_Data.av.im_v_dc_V) && (Global_Data.av.im_v_dc_V >= MOTOR_SOR_v_dc_lower_V)) {
			float const raw_a = Global_Data.av.adc_ltc2311_a1_ch0;
			float const raw_b = Global_Data.av.adc_ltc2311_a1_ch1;
			float const raw_c = Global_Data.av.adc_ltc2311_a1_ch2;
			im_current_sum_a += raw_a; im_current_sum_b += raw_b; im_current_sum_c += raw_c;
			im_current_square_sum_a += (double)raw_a * raw_a;
			im_current_square_sum_b += (double)raw_b * raw_b;
			im_current_square_sum_c += (double)raw_c * raw_c;
			im_current_offset_samples++;
			if (im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT) {
				double const count = (double)MOTOR_CURRENT_OFFSET_SAMPLE_COUNT;
				double const mean_a = im_current_sum_a / count;
				double const mean_b = im_current_sum_b / count;
				double const mean_c = im_current_sum_c / count;
				im_current_offset_a = (float)mean_a; im_current_offset_b = (float)mean_b; im_current_offset_c = (float)mean_c;
				float const variance_a = fmaxf(0.0f, (float)(im_current_square_sum_a / count - mean_a * mean_a));
				float const variance_b = fmaxf(0.0f, (float)(im_current_square_sum_b / count - mean_b * mean_b));
				float const variance_c = fmaxf(0.0f, (float)(im_current_square_sum_c / count - mean_c * mean_c));
				Global_Data.av.im_current_offset_max_stddev_A = sqrtf(fmaxf(variance_a, fmaxf(variance_b, variance_c)));
				if (Global_Data.av.im_current_offset_max_stddev_A > MOTOR_CURRENT_OFFSET_MAX_STDDEV_A) reset_im_current_offset_calibration();
			}
		} else {
			reset_im_current_offset_calibration();
		}
	}
	bool const valid = im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT;
	Global_Data.av.im_i_a_A = valid ? Global_Data.av.adc_ltc2311_a1_ch0 - im_current_offset_a : 0.0f;
	Global_Data.av.im_i_b_A = valid ? Global_Data.av.adc_ltc2311_a1_ch1 - im_current_offset_b : 0.0f;
	Global_Data.av.im_i_c_A = valid ? Global_Data.av.adc_ltc2311_a1_ch2 - im_current_offset_c : 0.0f;
	Global_Data.av.im_current_offset_a_A = im_current_offset_a;
	Global_Data.av.im_current_offset_b_A = im_current_offset_b;
	Global_Data.av.im_current_offset_c_A = im_current_offset_c;
	Global_Data.av.im_current_offset_progress_percent = 100.0f * (float)im_current_offset_samples / (float)MOTOR_CURRENT_OFFSET_SAMPLE_COUNT;
	Global_Data.av.im_current_offset_valid = valid ? 1.0f : 0.0f;
	Global_Data.av.im_current_sum_error_A = Global_Data.av.im_i_a_A + Global_Data.av.im_i_b_A + Global_Data.av.im_i_c_A;
}

static float get_im_control_v_dc_V(void)
{
	#if MOTOR_U_F_USE_FIXED_V_DC == 1
	return Global_Data.rasv.im_enable_foc
		? Global_Data.av.im_v_dc_V : MOTOR_U_F_FIXED_V_DC_V;
	#else
	return (!Global_Data.rasv.im_enable_foc && Global_Data.rasv.im_use_filtered_v_dc)
		? Global_Data.av.im_v_dc_filtered_V : Global_Data.av.im_v_dc_V;
	#endif
}

static platform_state_t update_protection(platform_state_t current_state)
{
	bool const monitor_dc_undervoltage = (current_state == running_state) || (current_state == control_state);
	(void)error_checks_step_im(get_im_control_v_dc_V(), Global_Data.av.im_i_a_A, Global_Data.av.im_i_b_A,
		Global_Data.av.im_i_c_A, Global_Data.av.im_speed_rpm, &im_error_checks_config, monitor_dc_undervoltage);
	return ultrazohm_state_machine_get_state();
}

static void update_im_control(float encoder_mechanical_angle_rad)
{
	float const control_v_dc_V = get_im_control_v_dc_V();
	struct uz_im_measurement_values const measurements = {
		.i_abc_A = {.a = Global_Data.av.im_i_a_A, .b = Global_Data.av.im_i_b_A, .c = Global_Data.av.im_i_c_A},
		.v_abc_V = {0}, .v_dc_V = control_v_dc_V, .i_dc_A = 0.0f,
		.rotor_speed_rpm = Global_Data.av.im_speed_rpm,
		.rotor_mechanical_angle_rad = encoder_mechanical_angle_rad,
	};
	uz_im_control_enable(Global_Data.objects.im_control,
		im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT);
	struct uz_DutyCycle_t const duty = uz_im_control_sample_duty(Global_Data.objects.im_control,
		measurements, Global_Data.rasv.im_speed_reference_rpm,
		(uz_3ph_dq_t){.d = Global_Data.rasv.im_i_d_reference_A, .q = Global_Data.rasv.im_i_q_reference_A},
		Global_Data.rasv.im_frequency_reference_Hz);
	Global_Data.av.im_control_actual = *uz_im_control_get_actual_data(Global_Data.objects.im_control);
	Global_Data.av.im_control_reference = *uz_im_control_get_reference_values(Global_Data.objects.im_control);
	Global_Data.av.im_control_measurements = *uz_im_control_get_im_measurement_values(Global_Data.objects.im_control);
	Global_Data.av.im_control_violation = uz_im_control_get_safe_operating_area_violation(Global_Data.objects.im_control);
	Global_Data.av.im_control_violation_code = (float)Global_Data.av.im_control_actual.safe_operating_region_status;
	if (Global_Data.av.im_control_violation != uz_im_control_no_violation) ultrazohm_state_machine_set_error(true);
	Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = duty.DutyCycle_A;
	Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = duty.DutyCycle_B;
	Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = duty.DutyCycle_C;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
	update_setpoint_trajectories();
/* Project Wizard BEGIN: adc_readout */
    analog_adc_data = uz_dataMover_update_buffer_and_get_data();
/* Project Wizard END: adc_readout */
    update_adapter_a1();
    update_adapter_a2();
    update_adapter_a3();
    update_adapter_d1();
    update_adapter_d2();
    update_adapter_d3();
    update_adapter_d4();
    update_adapter_d5();
	float const encoder_mechanical_angle_rad = update_measurements();
	platform_state_t current_state = ultrazohm_state_machine_get_state();
	update_im_current_offset_calibration(current_state);
	current_state = update_protection(current_state);
    if (current_state == idle_state)
    {
		if (!idle_reset_done) {
			IM_testbench_reset_idle(&Global_Data);
			idle_reset_done = true;
		}
		uz_im_control_enable(Global_Data.objects.im_control, false);
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, false);
        /* Project Wizard BEGIN: idle_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
/* Project Wizard END: idle_state isr_actions */
		im_pwm_tristated_for_calibration = true;
    }
    else if (current_state == running_state)
    {
		idle_reset_done = false;
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, true);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, true);
        /* Project Wizard BEGIN: running_state isr_actions */
		bool const im_offset_valid = im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT;
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0,
			!im_offset_valid, !im_offset_valid, !im_offset_valid);
/* Project Wizard END: running_state isr_actions */
    }
    else if (current_state == control_state)
    {
		idle_reset_done = false;
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, true);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, true);
        // Start: Control algorithm - only if ultrazohm is in control state
		update_im_control(encoder_mechanical_angle_rad);

        /* Project Wizard BEGIN: control_state isr_actions */
/* Project Wizard END: control_state isr_actions */
    }
    else if (current_state == error_state)
    {
		idle_reset_done = false;
		uz_im_control_enable(Global_Data.objects.im_control, false);
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, false);
        /* Project Wizard BEGIN: error_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
/* Project Wizard END: error_state isr_actions */
    }
    
    /* Project Wizard BEGIN: pwm_runtime */
    project_wizard_update_pwm_outputs(&Global_Data);
/* Project Wizard END: pwm_runtime */

    project_wizard_visualization_update(&Global_Data);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

static void update_adapter_a1(void)
{
    /* Project Wizard BEGIN: A1 isr_control */
    Global_Data.av.adc_ltc2311_a1_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[0], 0U);
    Global_Data.av.adc_ltc2311_a1_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[1], 1U);
    Global_Data.av.adc_ltc2311_a1_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[2], 2U);
    Global_Data.av.adc_ltc2311_a1_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[3], 3U);
    Global_Data.av.adc_ltc2311_a1_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[4], 4U);
    Global_Data.av.adc_ltc2311_a1_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[5], 5U);
    Global_Data.av.adc_ltc2311_a1_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[6], 6U);
    Global_Data.av.adc_ltc2311_a1_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[7], 7U);
/* Project Wizard END: A1 isr_control */
}

static void update_adapter_a2(void)
{
    /* Project Wizard BEGIN: A2 isr_control */
    Global_Data.av.adc_ltc2311_a2_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[8], 0U);
    Global_Data.av.adc_ltc2311_a2_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[9], 1U);
    Global_Data.av.adc_ltc2311_a2_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[10], 2U);
    Global_Data.av.adc_ltc2311_a2_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[11], 3U);
    Global_Data.av.adc_ltc2311_a2_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[12], 4U);
    Global_Data.av.adc_ltc2311_a2_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[13], 5U);
    Global_Data.av.adc_ltc2311_a2_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[14], 6U);
    Global_Data.av.adc_ltc2311_a2_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[15], 7U);
/* Project Wizard END: A2 isr_control */
}

static void update_adapter_a3(void)
{
    /* Project Wizard BEGIN: A3 isr_control */
/* Project Wizard END: A3 isr_control */
}

static void update_adapter_d1(void)
{
    /* Project Wizard BEGIN: D1 isr_control */
    Global_Data.av.io_card_d1_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d1);
    Global_Data.av.inverter_hardware_overcurrent =
        uz_axi_gpio_read_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_15_PIN_ZERO_BASED) ? 1.0f : 0.0f;
/* Project Wizard END: D1 isr_control */
}

static void update_adapter_d2(void)
{
    /* Project Wizard BEGIN: D2 isr_control */
    update_inverter_adapter_d2_outputs(&Global_Data);
/* Project Wizard END: D2 isr_control */
}

static void update_adapter_d3(void)
{
    /* Project Wizard BEGIN: D3 isr_control */
/* Project Wizard END: D3 isr_control */
}

static void update_adapter_d4(void)
{
    /* Project Wizard BEGIN: D4 isr_control */
/* Project Wizard END: D4 isr_control */
}

static void update_adapter_d5(void)
{
/* Project Wizard BEGIN: D5 isr_control */
    Global_Data.av.incremental_encoder_d5_1_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position_w_offset_javascope =
        (float)Global_Data.av.incremental_encoder_d5_1_position_w_offset;

    Global_Data.av.incremental_encoder_d5_2_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset_javascope =
        (float)Global_Data.av.incremental_encoder_d5_2_position_w_offset;
    Global_Data.av.incremental_encoder_d5_2_index_found_javascope =
        Global_Data.av.incremental_encoder_d5_2_index_found ? 1.0f : 0.0f;

    Global_Data.av.incremental_encoder_d5_3_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position_w_offset_javascope =
        (float)Global_Data.av.incremental_encoder_d5_3_position_w_offset;
/* Project Wizard END: D5 isr_control */
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}


//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}
