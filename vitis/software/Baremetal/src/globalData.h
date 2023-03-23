#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "uz/uz_Transformation/uz_Transformation.h"
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
	float i_dc1;
	float i_a2;
	float i_b2;
	float i_c2;
	float i_dc2;
	float v_a1;
	float v_b1;
	float v_c1;
	float v_dc1;
	float v_a2;
	float v_b2;
	float v_c2;
	float v_dc2;
	float i_alpha;
	float i_beta;
	float i_x;
	float i_y;
	float i_z1;
	float i_z2;
	float i_d;
	float i_q;
	float mechanicalRotorSpeedRPM;
	float electricalRotorSpeedRPM;
	float mechanicalRotorSpeedRADpS;
	float electricalRotorSpeedRADpS;
	float v_d;
	float v_q;
	float theta_elec_rad;
	float theta_mech_rad;
	float theta_mech_offset_rad;
	float theta_mech_calculated;
	float theta_offset_rad;
	float temperature_inv_1;
	float temperature_inv_2;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs1;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs2;
	float polepairs;
	uint32_t  heartbeatframe_content;
	struct uz_resolverIP_position_velocity_t posVel_mech;
	struct uz_resolverIP_position_velocity_t posVel_el;
	bool logging;
	int js_cnt_slowData;
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
	float res_gain_scope;
	uint16_t selected_subsystem;
	uz_3ph_dq_t ab_i_dq_PI_ref;
	uz_3ph_dq_t xy_i_dq_PI_ref;
	float resonant_order;
	float kp_dq;
	float ki_dq;
	float kp_xy;
	float ki_xy;
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
	uz_resolverIP_t* resolver_d5_1;
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

