#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"
#include "uz/uz_pmsm_control/uz_pmsm_control.h"
#include "uz/uz_IM_Control/uz_im_control.h"
#include "uz/uz_Trajectory/uz_Trajectory.h"

#define SETPOINT_TRAJECTORY_COUNT 6U

/** Runtime state of one JavaScope-controlled setpoint trajectory. */
typedef struct {
	uz_Trajectory_t *instance;
	float start;
	float target;
	float active_target;
} setpoint_trajectory_state_t;

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float d3_input_loopback_uint32;
	struct uz_pmsm_actual_data va_control_actual;
	struct uz_pmsm_reference_values va_control_reference;
	enum uz_pmsm_control_safe_operating_region_violation va_control_violation;
	float va_control_violation_code;
	float im_i_a_A, im_i_b_A, im_i_c_A;
	float im_v_dc_V, im_speed_rpm;
	struct uz_im_actual_data im_control_actual;
	struct uz_im_reference_values im_control_reference;
	struct uz_im_measurement_values im_control_measurements;
	enum uz_im_control_safe_operating_region_violation im_control_violation;
	float im_control_violation_code;
	float im_current_offset_a_A, im_current_offset_b_A, im_current_offset_c_A;
	float im_current_offset_progress_percent;
	float im_current_offset_max_stddev_A;
	float im_current_sum_error_A;
	float im_current_offset_valid;
	float inverter_temperature_pwm_duty_cycle_percent;
	float inverter_temperature_pwm_frequency_Hz;
	float inverter_temperature_degC;
	float inverter_hardware_overcurrent;
	/* Project Wizard BEGIN: actualValues */
	float adc_ltc2311_a1_ch0;
	float adc_ltc2311_a1_ch1;
	float adc_ltc2311_a1_ch2;
	float adc_ltc2311_a1_ch3;
	float adc_ltc2311_a1_ch4;
	float adc_ltc2311_a1_ch5;
	float adc_ltc2311_a1_ch6;
	float adc_ltc2311_a1_ch7;
	float adc_ltc2311_a2_ch0;
	float adc_ltc2311_a2_ch1;
	float adc_ltc2311_a2_ch2;
	float adc_ltc2311_a2_ch3;
	float adc_ltc2311_a2_ch4;
	float adc_ltc2311_a2_ch5;
	float adc_ltc2311_a2_ch6;
	float adc_ltc2311_a2_ch7;
	uint32_t io_card_d1_state;
	struct uz_inverter_adapter_outputs_t inverter_adapter_d2;
	float incremental_encoder_d5_2_theta_el;
	float incremental_encoder_d5_2_omega_mech;
	float incremental_encoder_d5_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_2_position;
	uint32_t incremental_encoder_d5_2_position_w_offset;
	uint32_t incremental_encoder_d5_2_index_found;
/* Project Wizard END: actualValues */
} actualValues;

typedef struct _referenceAndSetValues_ {
	float va_speed_reference_rpm;
	uz_3ph_dq_t va_current_reference_A;
	float va_disturbance_torque_Nm;
	bool va_enable_speed_control;
	bool va_acknowledge_error;
	bool setpoint_trajectories_enabled;
	float im_frequency_reference_Hz;
	float im_i_d_reference_A;
	float im_i_q_reference_A;
	bool im_enable_foc;
	bool im_enable_kalman_filter;
	bool im_enable_resonant_control;
/* Project Wizard BEGIN: referenceAndSetValues */
	float pwm_2L_0_halfBridgeDutyCycle_1;
	float pwm_2L_0_halfBridgeDutyCycle_2;
	float pwm_2L_0_halfBridgeDutyCycle_3;
	float pwm_2L_1_halfBridgeDutyCycle_1;
	float pwm_2L_1_halfBridgeDutyCycle_2;
	float pwm_2L_1_halfBridgeDutyCycle_3;
	float pwm_3L_0_halfBridgeDutyCycle_1;
	float pwm_3L_0_halfBridgeDutyCycle_2;
	float pwm_3L_0_halfBridgeDutyCycle_3;
/* Project Wizard END: referenceAndSetValues */
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	uz_pmsm_control_t* va_control;
	uz_im_control_t* im_control;
	uz_PWM_duty_freq_detection_t* inverter_temperature_pwm;
	setpoint_trajectory_state_t setpoint_trajectories[SETPOINT_TRAJECTORY_COUNT];
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_adcLtc2311_t* adc_ltc2311_a2;
	uz_axi_gpio_t* axi_gpio_d1;
	uz_inverter_adapter_t* inverter_adapter_d2;
	uz_incrementalEncoder_t* incremental_encoder_d5_2;
/* Project Wizard END: objects */
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif
