#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_movingAverageFilter/uz_movingAverageFilter.h"
#include "uz/uz_ParameterID_rc/uz_ParameterID_rc.h"
#include "uz/uz_ParameterID_rs/uz_ParameterID_rs.h"
#include "IP_Cores/uz_IncrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"

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

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float torque;
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
	float v_d_right_meas;
	float v_q_right_meas;
	float v_d_left_meas;
	float v_q_left_meas;
	float omega_mech_right;
	float omega_mech_left;
	float speed_rpm_left;
	float speed_rpm_right;
	float temp;
	float vcc_lp;
	float vcc_fp;
	float fcc_aux;
	float theta_el_right_advanced;
	float theta_el_right;
	float theta_el_offset_right;
	float theta_el_left_advanced;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_left;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_right;
	struct uz_inverter_adapter_outputs_t inverter_left_status;
	struct uz_inverter_adapter_outputs_t inverter_right_status;
	float mean_temp_inv_left;
	float mean_temp_inv_right;
	float polepairs_left;
	float polepairs_right;
	uz_temperaturecard_OneGroup channel_A_data;
	float average_temp_right;
	float average_temp_left;
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
	float n_ref_left;
	float js_set_n_ref_left;
	float n_ref_left_filt;
	float operatingpoints_rc_meas;
	uz_3ph_dq_t i_dq_ref_right;
	uz_3ph_dq_t js_set_i_dq_ref_right;
	uz_3ph_dq_t i_dq_ref_rc_meas_right;
	uz_3ph_dq_t i_dq_ref_left;
	struct uz_parameterID_rc_ref_val_t rc_meas_output;
	struct uz_parameterid_output rs_meas_output;
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
	uz_resolverIP_t* resolver_left;
	uz_resolverIP_t* resolver_right;
	uz_incrementalEncoder_t* encoder_right;
	uz_resolver_pl_interface_t* resolver_pl_interface_left;
	uz_resolver_pl_interface_t* resolver_pl_interface_right;
	uz_CurrentControl_t* current_ctrl_left;
	uz_CurrentControl_t* current_ctrl_right;
	uz_SpeedControl_t* speed_ctrl_left;
	uz_SetPoint_t* setpoint_ctrl_left;
	uz_inverter_adapter_t* uz_d_inverter_left;
	uz_inverter_adapter_t* uz_d_inverter_right;
	uz_mux_axi_t* mux_axi;
	uz_IIR_Filter_t* iir_filter_ref_speed_left;
	uz_parameterID_rc_t* rc_meas_instance;
	uz_parameterid_rs_t* rs_meas_instance;
	uz_temperaturecard_t* temperature_card_d3;
	uz_IIR_Filter_t *tracking_error_filter_prime_mover;
	uz_IIR_Filter_t *phase_a_lowpass;
	uz_IIR_Filter_t *phase_b_lowpass;
	uz_IIR_Filter_t *phase_c_lowpass;
	uz_IIR_Filter_t *d2_phase_a_lowpass;
	uz_IIR_Filter_t *d2_phase_b_lowpass;
	uz_IIR_Filter_t *d2_phase_c_lowpass;
	}object_pointers_t;


typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

