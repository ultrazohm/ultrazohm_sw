#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_endat_interface/uz_endat_interface.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
#include "uz/uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"
#include "uz/uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"
// union allows to access the values as array and individual variables
// see also this link for more information: https://hackaday.com/2018/03/02/unionize-your-variables-an-introduction-to-advanced-data-types-in-c/
typedef union _ConversionFactors_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
		};
	float ADC_array[8];
} ConversionFactors;

typedef union _Measurements_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
		};
	float ADC_array[8];
} Measurements;

typedef struct _ADCcard_ {
	ConversionFactors 	cf;
	Measurements		me;
} ADCcard;

typedef struct _AnalogAdapters_ {
	ADCcard A1;
	ADCcard A2;
	ADCcard A3;
} AnalogAdapters;

typedef struct _machineEncoderValues_ {
	float theta_mech;
	float theta_elec;
	float mechanicalRotorSpeed; // in rpm
	float electricalRotorSpeed; // in rad/s
} machineEncoderValues;

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float mechanicalRotorSpeed;
	float theta_elec;
	float theta_mech;
	float mechanicalRotorSpeed_filtered;
	float snd_fld[21];
	uint32_t slowDataCounter;
	machineEncoderValues endat_machine;
	machineEncoderValues endat_software_pll_machine;
	float torque;
	float torque_filt;
	float i_a_left;
	float i_b_left;
	float i_c_left;
	float i_dc_left;
	float i_dc_right;
	float i_a_right;
	float i_b_right;
	float i_c_right;
	float v_a_left;
	float v_b_left;
	float v_c_left;
	float v_a_right;
	float v_b_right;
	float v_c_right;
	float v_dc_left;
	float v_dc_right;
	float i_d_left;
	float i_q_left;
	float i_d_right;
	float i_q_right;
	float v_d_left;
	float v_q_left;
	float v_d_right;
	float v_q_right;
	float omega_mech_right;
	float omega_el_right;
	float omega_mech_left;
	float omega_el_left;
	float polepairs_left;
	float polepairs_right;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d3_1;
	float omega_mech_d3_1;
	float position_el_2pi_d3_1;
	float position_mech_2pi_d3_1;
	float n_mech_rpm_d3_1;
	float position_mech_2pi_d4_1;
	float position_el_2pi_d4_1;
	float n_mech_rpm_d4_1;
	float overcurrent_ac;
	float overvoltage_dc;
	float undervoltage_dc;
	float overspeed;
	float overtorque;
	float encoder_offset_resolver_progress;
	float encoder_offset_resolver_diagnose;
	uz_3ph_dq_t encoder_offset_resolver_i_dq_ref;
	float encoder_offset_endat_progress;
	float encoder_offset_endat_diagnose;
	uz_3ph_dq_t encoder_offset_endat_i_dq_ref;
	bool currentcontrol_clamping_left;
	bool currentcontrol_clamping_right;
} actualValues;

typedef struct _referenceAndSetValues_ {
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
	float halfBridge4DutyCycle;
	float halfBridge5DutyCycle;
	float halfBridge6DutyCycle;
	float halfBridge7DutyCycle;
	float halfBridge8DutyCycle;
	float halfBridge9DutyCycle;
	float halfBridge10DutyCycle;
	float halfBridge11DutyCycle;
	float halfBridge12DutyCycle;
	float M_ref_left;
	float M_ref_right;
	float n_ref_left;
	float n_ref_right;
	float n_ref_left_filt;
	float n_ref_right_filt;
	float resolver_offset;
	float d4_to_d3_offset_mech;
	float d4_to_d3_offset_el;
	uz_3ph_dq_t i_dq_ref_right;
	uz_3ph_dq_t i_dq_ref_left;
	float torque_offset;
	float v_d_left_ref;
	float v_q_left_ref;
	float endat_offset;
} referenceAndSetValues;

typedef struct{
	uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5;
	uz_PWM_SS_2L_t* pwm_d1_pin_6_to_11;
	uz_PWM_SS_2L_t* pwm_d1_pin_12_to_17;
	uz_PWM_SS_2L_t* pwm_d1_pin_18_to_23;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_6_to_11;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_12_to_17;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_18_to_23;
	uz_incrementalEncoder_t* encoder_D5;
	uz_resolverIP_t* resolver_d3_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d3_1;
	uz_endat_interface_t* endat_encoder_d4_1;
	uz_pos_to_speed_pll_t* endat_speed_pll_d4_1;
	uz_encoder_offset_estimation_t* encoder_offset_estimation_resolver_d3;
	uz_encoder_offset_estimation_t* encoder_offset_estimation_endat_d4;
	uz_CurrentControl_t* current_ctrl_left;
	uz_CurrentControl_t* current_ctrl_right;
	uz_SpeedControl_t* speed_ctrl_left;
	uz_SpeedControl_t* speed_ctrl_right;
	uz_SetPoint_t* setpoint_ctrl_left;
	uz_SetPoint_t* setpoint_ctrl_right;
	uz_mux_axi_t* mux_axi;
	uz_IIR_Filter_t* iir_filter_ref_speed_left;
	uz_IIR_Filter_t* iir_filter_ref_speed_right;
	uz_IIR_Filter_t* iir_filter_torque;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif
