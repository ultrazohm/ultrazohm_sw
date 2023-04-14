#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"

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
	float i_a_d1;
	float i_b_d1;
	float i_c_d1;
	float i_a_d2;
	float i_b_d2;
	float i_c_d2;
	float v_a_d1;
	float v_b_d1;
	float v_c_d1;
	float v_a_d2;
	float v_b_d2;
	float v_c_d2;
	float v_dc_d1;
	float v_dc_d2;
	float i_dc_d1;
	float i_dc_d2;
	float i_d_d1;
	float i_q_d1;
	float i_d_d2;
	float i_q_d2;
	float v_d_d1;
	float v_q_d1;
	float v_d_d2;
	float v_q_d2;
	float speed_rpm_d5_1;
	float speed_rpm_d5_2;
	struct uz_resolverIP_position_velocity_t theta_el_omega_el_D5_1;
	struct uz_resolverIP_position_velocity_t theta_el_omega_el_D5_2;
	struct uz_resolverIP_position_velocity_t theta_mech_omega_mech_D5_1;
	struct uz_resolverIP_position_velocity_t theta_mech_omega_mech_D5_2;
	struct uz_inverter_adapter_outputs_t inverter_D1_status;
	struct uz_inverter_adapter_outputs_t inverter_D2_status;
	float mean_temp_inv_d1;
	float mean_temp_inv_d2;
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
	uz_3ph_dq_t i_dq_ref_d1;
	uz_3ph_dq_t i_dq_ref_d2;
	float M_ref_d1;
	float n_ref_d1;
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
	uz_mux_axi_t* mux_axi;
	uz_inverter_adapter_t* uz_d_inverter_D1;
	uz_inverter_adapter_t* uz_d_inverter_D2;
	uz_resolverIP_t* uz_d_resolver_D5_1;
	uz_resolverIP_t* uz_d_resolver_D5_2;
	uz_CurrentControl_t* current_ctrl_d1;
	uz_SetPoint_t* setpoint_ctrl_d1;
	uz_SpeedControl_t* speed_ctrl_d1;
	uz_CurrentControl_t* current_ctrl_d2;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

