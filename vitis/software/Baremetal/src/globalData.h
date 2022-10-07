#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_FOC/uz_FOC.h"
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
	float i_a1;
	float i_b1;
	float i_c1;
	float i_a2;
	float i_b2;
	float i_c2;
	float i_a1_filt;
	float i_b1_filt;
	float i_c1_filt;
	float i_a2_filt;
	float i_b2_filt;
	float i_c2_filt;
	float U_ZK; 		// DC-Link voltage in V
	float U_ZK_filt;
	float U_ZK2; 		// DC-Link voltage 2 in V
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalPosition; 		// in m
	float i_d;
	float i_q;
	float i_d_ref;
	float i_q_ref;
	float rpm_ref;
	float rpm_ref_filt;
	float i_alpha;
	float i_beta;
	float u_d;
	float u_q;
	float u_d_ref;
	float u_q_ref;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
	float theta_m_offset_comp;
	float polepairs;
	float u_a1;
	float u_b1;
	float u_c1;
	float inverter_temp;	// in °C
	float theta_mech_unwraped;
	float u_precontrol;
	float flg_rising_edge;
	float flg_falling_edge;
	float precontrol_counter_on;
	float precontrol_counter_off;
	float add_on_voltage;
	uint32_t  heartbeatframe_content;
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
	uz_resolverIP_t* resolver_IP;
	uz_IIR_Filter_t* iir_u_dc;
	uz_IIR_Filter_t* iir_i_a1;
	uz_IIR_Filter_t* iir_i_b1;
	uz_IIR_Filter_t* iir_i_c1;
	uz_IIR_Filter_t* iir_i_a2;
	uz_IIR_Filter_t* iir_i_b2;
	uz_IIR_Filter_t* iir_i_c2;
	uz_IIR_Filter_t* iir_rpm_ref;
	uz_FOC* foc_current;
	uz_SpeedControl_t* foc_speed;
	uz_PI_Controller* PI_cntr1_on;
	uz_PI_Controller* PI_cntr1_off;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

