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
static void update_va_control(bool enable_output, bool monitor_dc_undervoltage);

/* AXI-GPIO bit index matching the bitstream signal DIG_13. */
#define D1_DIG_13_PIN_ZERO_BASED 13U
#define D1_DIG_15_PIN_ZERO_BASED 15U

static const error_checks_config_t va_error_checks_config = {
	.vdc_min_V = VA_PROTECTION_MIN_DC_VOLTAGE_V,
	.vdc_max_V = VA_PROTECTION_MAX_DC_VOLTAGE_V,
	.iphase_max_A = VA_PROTECTION_MAX_PHASE_CURRENT_A,
	.max_mechanical_speed_rpm = VA_PROTECTION_MAX_SPEED_RPM,
};
static const error_checks_config_t im_error_checks_config={.vdc_min_V=MOTOR_SOR_v_dc_lower_V,.vdc_max_V=MOTOR_SOR_v_dc_upper_V,.iphase_max_A=MOTOR_SOR_i_abc_upper_A,.max_mechanical_speed_rpm=MOTOR_SOR_speed_upper_rpm};
static float im_current_offset_a,im_current_offset_b,im_current_offset_c;
static double im_current_sum_a,im_current_sum_b,im_current_sum_c;
static uint32_t im_current_offset_samples;
static bool setpoint_trajectories_enabled_last = true;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
	float* const setpoints[6] = {
		&Global_Data.rasv.va_speed_reference_rpm,
		&Global_Data.rasv.va_current_reference_A.d,
		&Global_Data.rasv.va_current_reference_A.q,
		&Global_Data.rasv.im_i_d_reference_A,
		&Global_Data.rasv.im_i_q_reference_A,
		&Global_Data.rasv.im_frequency_reference_Hz,
	};
	if (setpoint_trajectories_enabled_last && !Global_Data.rasv.setpoint_trajectories_enabled) {
		for (uint32_t trajectory = 0U; trajectory < 6U; trajectory++) {
			uz_Trajectory_Stop(Global_Data.objects.setpoint_trajectories[trajectory]);
			uz_Trajectory_Reset(Global_Data.objects.setpoint_trajectories[trajectory]);
		}
	}
	setpoint_trajectories_enabled_last = Global_Data.rasv.setpoint_trajectories_enabled;
	for (uint32_t trajectory = 0U; trajectory < 6U; trajectory++) {
		if (!Global_Data.rasv.setpoint_trajectories_enabled) {
			Global_Data.rasv.setpoint_ramp_start[trajectory] =
				Global_Data.rasv.setpoint_ramp_target[trajectory];
			Global_Data.rasv.setpoint_ramp_active_target[trajectory] =
				Global_Data.rasv.setpoint_ramp_target[trajectory];
			*setpoints[trajectory] = Global_Data.rasv.setpoint_ramp_target[trajectory];
			continue;
		}
		if (Global_Data.rasv.setpoint_ramp_target[trajectory] !=
			Global_Data.rasv.setpoint_ramp_active_target[trajectory]) {
			/* Only the ISR modifies the active ramp. A new command therefore
			 * always starts exactly at the last value emitted by the ISR. */
			Global_Data.rasv.setpoint_ramp_start[trajectory] = *setpoints[trajectory];
			Global_Data.rasv.setpoint_ramp_active_target[trajectory] =
				Global_Data.rasv.setpoint_ramp_target[trajectory];
			uz_Trajectory_Reset(Global_Data.objects.setpoint_trajectories[trajectory]);
			uz_Trajectory_Start(Global_Data.objects.setpoint_trajectories[trajectory]);
		}
		float const ramp_factor = uz_Trajectory_Step(Global_Data.objects.setpoint_trajectories[trajectory]);
		if (ramp_factor <= 0.0f) {
			/* A short uz_Trajectory repeats back to its first sample after the
			 * final point. Stop at the target before that return can begin. */
			uz_Trajectory_Stop(Global_Data.objects.setpoint_trajectories[trajectory]);
		}
		*setpoints[trajectory] = Global_Data.rasv.setpoint_ramp_active_target[trajectory] + ramp_factor *
			(Global_Data.rasv.setpoint_ramp_start[trajectory] -
			 Global_Data.rasv.setpoint_ramp_active_target[trajectory]);
	}
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
	float const encoder_mechanical_angle_rad =
		(2.0f * UZ_PIf * (float)(Global_Data.av.incremental_encoder_d5_2_position_w_offset %
		 MOTOR_ENCODER_INCREMENTS_PER_MECHANICAL_TURN)) /
		(float)MOTOR_ENCODER_INCREMENTS_PER_MECHANICAL_TURN;
	float const temperature_duty_ratio = uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(Global_Data.objects.inverter_temperature_pwm);
	Global_Data.av.inverter_temperature_pwm_duty_cycle_percent = temperature_duty_ratio * 100.0f;
	Global_Data.av.inverter_temperature_pwm_frequency_Hz = uz_PWM_duty_freq_detection_get_frequency_in_Hz(Global_Data.objects.inverter_temperature_pwm);
	Global_Data.av.inverter_temperature_degC = wolfspeed_inverter_temperature_from_duty_ratio(temperature_duty_ratio);
	Global_Data.av.im_v_dc_V = Global_Data.av.adc_ltc2311_a1_ch3 - 2.5f;

	/* The current-sensor operating point is only valid with an energized DC link.
	 * Use 1000 consecutive valid samples; restart if the DC link drops out. */
	if (im_current_offset_samples < MOTOR_CURRENT_OFFSET_SAMPLE_COUNT) {
		if (isfinite(Global_Data.av.im_v_dc_V) &&
			(Global_Data.av.im_v_dc_V >= MOTOR_SOR_v_dc_lower_V)) {
			im_current_sum_a += Global_Data.av.adc_ltc2311_a1_ch0;
			im_current_sum_b += Global_Data.av.adc_ltc2311_a1_ch1;
			im_current_sum_c += Global_Data.av.adc_ltc2311_a1_ch2;
			im_current_offset_samples++;

			if (im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT) {
				im_current_offset_a = (float)(im_current_sum_a / (double)MOTOR_CURRENT_OFFSET_SAMPLE_COUNT);
				im_current_offset_b = (float)(im_current_sum_b / (double)MOTOR_CURRENT_OFFSET_SAMPLE_COUNT);
				im_current_offset_c = (float)(im_current_sum_c / (double)MOTOR_CURRENT_OFFSET_SAMPLE_COUNT);
			}
		} else {
			im_current_sum_a = 0.0;
			im_current_sum_b = 0.0;
			im_current_sum_c = 0.0;
			im_current_offset_samples = 0U;
		}
	}

	if (im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT) {
		Global_Data.av.im_i_a_A = Global_Data.av.adc_ltc2311_a1_ch0 - im_current_offset_a;
		Global_Data.av.im_i_b_A = Global_Data.av.adc_ltc2311_a1_ch1 - im_current_offset_b;
		Global_Data.av.im_i_c_A = Global_Data.av.adc_ltc2311_a1_ch2 - im_current_offset_c;
	} else {
		/* Avoid interpreting the uncorrected sensor operating point as current. */
		Global_Data.av.im_i_a_A = 0.0f;
		Global_Data.av.im_i_b_A = 0.0f;
		Global_Data.av.im_i_c_A = 0.0f;
	}
	Global_Data.av.im_speed_rpm=-Global_Data.av.va_control_actual.speed_in_rpm;

    platform_state_t current_state = ultrazohm_state_machine_get_state();
	bool const monitor_dc_undervoltage =
		(current_state == running_state) || (current_state == control_state);
	(void)error_checks_step(&Global_Data.av, &va_error_checks_config, monitor_dc_undervoltage);
	(void)error_checks_step_im(Global_Data.av.im_v_dc_V,Global_Data.av.im_i_a_A,Global_Data.av.im_i_b_A,Global_Data.av.im_i_c_A,Global_Data.av.im_speed_rpm,&im_error_checks_config,monitor_dc_undervoltage);
	current_state = ultrazohm_state_machine_get_state();
    if (current_state == idle_state)
    {
		uz_im_control_enable(Global_Data.objects.im_control, false);
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, false);
		update_va_control(false, false);
        /* Project Wizard BEGIN: idle_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
/* Project Wizard END: idle_state isr_actions */
    }
    else if (current_state == running_state)
    {
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, true);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, true);
		update_va_control(false, true);
        /* Project Wizard BEGIN: running_state isr_actions */
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, false, false, false);
/* Project Wizard END: running_state isr_actions */
    }
    else if (current_state == control_state)
    {
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, true);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, true);
        // Start: Control algorithm - only if ultrazohm is in control state
		update_va_control(true, true);
		struct uz_im_measurement_values const im_measurements = {
			.i_abc_A = {.a = Global_Data.av.im_i_a_A, .b = Global_Data.av.im_i_b_A, .c = Global_Data.av.im_i_c_A},
			.v_abc_V = {0}, .v_dc_V = Global_Data.av.im_v_dc_V, .i_dc_A = 0.0f,
			.rotor_speed_rpm = Global_Data.av.im_speed_rpm,
			.rotor_mechanical_angle_rad = encoder_mechanical_angle_rad,
		};
		uz_im_control_enable(Global_Data.objects.im_control,
			im_current_offset_samples == MOTOR_CURRENT_OFFSET_SAMPLE_COUNT);
		struct uz_DutyCycle_t const im_duty = uz_im_control_sample_duty(Global_Data.objects.im_control,
			im_measurements, 0.0f,
			(uz_3ph_dq_t){.d = Global_Data.rasv.im_i_d_reference_A, .q = Global_Data.rasv.im_i_q_reference_A},
			Global_Data.rasv.im_frequency_reference_Hz);
		Global_Data.av.im_control_actual = *uz_im_control_get_actual_data(Global_Data.objects.im_control);
		Global_Data.av.im_control_reference = *uz_im_control_get_reference_values(Global_Data.objects.im_control);
		Global_Data.av.im_control_measurements = *uz_im_control_get_im_measurement_values(Global_Data.objects.im_control);
		Global_Data.av.im_control_violation = uz_im_control_get_safe_operating_area_violation(Global_Data.objects.im_control);
		Global_Data.av.im_control_violation_code = (float)Global_Data.av.im_control_actual.safe_operating_region_status;
		if (Global_Data.av.im_control_violation != uz_im_control_no_violation) {
			ultrazohm_state_machine_set_error(true);
		}
		Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1=im_duty.DutyCycle_A;
		Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2=im_duty.DutyCycle_B;
		Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3=im_duty.DutyCycle_C;

        /* Project Wizard BEGIN: control_state isr_actions */
/* Project Wizard END: control_state isr_actions */
    }
    else if (current_state == error_state)
    {
		uz_im_control_enable(Global_Data.objects.im_control, false);
		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
		uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1, D1_DIG_13_PIN_ZERO_BASED, false);
		update_va_control(false, false);
        /* Project Wizard BEGIN: error_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.5f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.5f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.5f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
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
    Global_Data.av.incremental_encoder_d5_2_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_2);
/* Project Wizard END: D5 isr_control */
}

static void update_va_control(bool enable_output, bool monitor_dc_undervoltage)
{
    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = {.a = Global_Data.av.adc_ltc2311_a2_ch3, .b = Global_Data.av.adc_ltc2311_a2_ch2, .c = Global_Data.av.adc_ltc2311_a2_ch1},
        .v_abc_in_V = {.a = Global_Data.av.adc_ltc2311_a2_ch7, .b = Global_Data.av.adc_ltc2311_a2_ch6, .c = Global_Data.av.adc_ltc2311_a2_ch5},
        .v_dc_in_V = Global_Data.av.adc_ltc2311_a2_ch0,
        .i_dc_in_A = Global_Data.av.adc_ltc2311_a2_ch4,
        .omega_mech_rad_per_sec = Global_Data.av.incremental_encoder_d5_2_omega_mech,
        .theta_mech = Global_Data.av.incremental_encoder_d5_2_theta_el / 4.0f};

	/* An unpowered DC link is valid in idle/error. Overvoltage and overcurrent
	 * remain active in every state; undervoltage is armed in running/control. */
	if ((!monitor_dc_undervoltage) && (measurements.v_dc_in_V < VA_PROTECTION_MIN_DC_VOLTAGE_V)) {
		measurements.v_dc_in_V = VA_PROTECTION_MIN_DC_VOLTAGE_V;
	}

	bool const acknowledge_error = Global_Data.rasv.va_acknowledge_error;
	if (acknowledge_error) {
		/* The test-bench reset clears its error latch unconditionally. Do the
		 * equivalent for uz_pmsm_control with a neutral, valid measurement set.
		 * The real measurements are sampled and checked again directly below. */
		struct uz_pmsm_measurement_values reset_measurements = measurements;
		reset_measurements.i_abc_in_A = (uz_3ph_abc_t){.a = 0.0f, .b = 0.0f, .c = 0.0f};
		reset_measurements.v_dc_in_V = 0.5f * (VA_PROTECTION_MIN_DC_VOLTAGE_V + VA_PROTECTION_MAX_DC_VOLTAGE_V);
		reset_measurements.i_dc_in_A = 0.0f;
		reset_measurements.omega_mech_rad_per_sec = 0.0f;
		uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.va_control, reset_measurements);
		uz_pmsm_control_reset(Global_Data.objects.va_control);
		Global_Data.rasv.va_acknowledge_error = false;
	}

    uz_pmsm_control_enable_speed_control(Global_Data.objects.va_control, Global_Data.rasv.va_enable_speed_control);
    uz_pmsm_control_enable(Global_Data.objects.va_control, enable_output);
    struct uz_DutyCycle_t duty = uz_pmsm_control_sample_duty(Global_Data.objects.va_control, measurements,
        Global_Data.rasv.va_speed_reference_rpm, Global_Data.rasv.va_current_reference_A,
        Global_Data.rasv.va_disturbance_torque_Nm);

    Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = duty.DutyCycle_A;
    Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = duty.DutyCycle_B;
    Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = duty.DutyCycle_C;
    Global_Data.av.va_control_actual = *uz_pmsm_control_get_actual_data(Global_Data.objects.va_control);
    Global_Data.av.va_control_reference = *uz_pmsm_control_get_reference_values(Global_Data.objects.va_control);
    Global_Data.av.va_control_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.va_control);
	Global_Data.av.va_control_violation_code = (float)Global_Data.av.va_control_violation;
	if (Global_Data.av.va_control_violation != uz_pmsm_control_no_violation) {
		ultrazohm_state_machine_set_error(true);
	}
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
