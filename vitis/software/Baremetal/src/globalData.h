#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "uz/uz_space_vector_modulation/uz_space_vector_modulation.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_PMSM_config/uz_PMSM_config.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_piController/uz_piController.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_signals/uz_signals.h"
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
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float theta_elec;
	float theta_el_Last_deg;
	float theta_mech_Last_deg;
	float theta_el_Pruef_deg;
	float theta_mech_Pruef_deg;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	// float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float error;

	struct uz_resolver_pl_interface_outputs_t resolver_outputs_d4_Last;
	struct uz_resolver_pl_interface_outputs_t resolver_outputs_d4_Pruef;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d3;

	struct uz_3ph_abc_t u_abc_inverter1;
	struct uz_3ph_abc_t u_abc_inverter2;
	struct uz_3ph_abc_t u_abc_inverter3;
	struct uz_3ph_abc_t i_abc_inverter1;
	struct uz_3ph_abc_t i_abc_inverter2;
	struct uz_3ph_abc_t i_abc_inverter3;

	struct uz_3ph_abc_t u_abc_3ph_Last_meas;
	struct uz_3ph_abc_t i_abc_3ph_Last_meas;
	struct uz_6ph_abc_t u_abc_6ph_Pruef_meas;
	struct uz_6ph_abc_t i_abc_6ph_Pruef_meas;
	struct uz_3ph_dq_t  u_dq_3ph_Last_meas;
	struct uz_3ph_dq_t  i_dq_3ph_Last_meas;
	struct uz_6ph_dq_t  u_dq_6ph_Pruef_meas;
	struct uz_6ph_dq_t  i_dq_6ph_Pruef_meas;
	float i_dc1, i_dc2, i_dc3;
	float u_dc1, u_dc2, u_dc3;
	float temp_VSI_1, temp_VSI_2, temp_VSI_3;

	float shift_a1;
	float shift_b1;
	float shift_c1;
	float shift_a2;
	float shift_b2;
	float shift_c2;

	struct uz_DutyCycle_2x3ph_t DutyCycle_output;

	float testSineAmplitude;
	float testSineFreq;
	bool activeTestSine;
	bool activeConstDuty;
	float constDuty;

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

	struct uz_DutyCycle_t duty_cycles_3ph_Last;
	struct uz_DutyCycle_2x3ph_t duty_cycles_6ph_Pruef;

	struct uz_3ph_dq_t u_dq_3ph_Last_soll;
	struct uz_3ph_dq_t i_dq_3ph_Last_soll;
	struct uz_6ph_dq_t u_dq_6ph_Pruef_soll;
	struct uz_6ph_dq_t i_dq_6ph_Pruef_soll;
	float n_mech_Last_soll;
	float M_Last_soll;
	float n_mech_Pruef_soll;
	float M_Pruef_soll;

	bool speed_control_3ph_Last;
	bool speed_control_6ph_Pruef;
	bool current_control_3ph_Last;
	bool current_control_6ph_Pruef;

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
	uz_mux_axi_t* mux_axi;

	uz_resolver_pl_interface_t* resolver_pl_d4_Last;
	uz_resolver_pl_interface_t* resolver_pl_d4_Pruef;
	uz_resolverIP_t* resolverIP_Last;
	uz_resolverIP_t* resolverIP_Pruef;

	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;
	uz_inverter_adapter_t* inverter_d3;

	uz_SetPoint_t* torque_to_current_dq_3ph_Last_object;
	uz_SetPoint_t* torque_to_current_dq_6ph_Pruef_object;
	uz_SpeedControl_t* speed_control_3ph_Last_object;
	uz_SpeedControl_t* speed_control_6ph_Pruef_object;
	uz_CurrentControl_t* current_control_3ph_Last_object;
	uz_CurrentControl_t* current_control_dq_6ph_Pruef_object;
	uz_CurrentControl_t* current_control_xy_6ph_Pruef_object;

	uz_IIR_Filter_t* speed_prefilter_Last;
	uz_IIR_Filter_t* speed_prefilter_Pruef;
} object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

