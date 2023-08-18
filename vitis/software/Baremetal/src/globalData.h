#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_Transformation/uz_Transformation.h"
#include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"
#include "uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_FD.h"


struct pointers_PI_PI{
	uz_CurrentControl_t* dq;
	uz_CurrentControl_t* xy1;
	uz_CurrentControl_t* xy2;
	uz_CurrentControl_t* xy3;
};

struct pointers_PI_R{
	uz_CurrentControl_t* dq;
	uz_subspace_resonant_control* XY1;
	uz_subspace_resonant_control* XY2;
	uz_subspace_resonant_control* XY3;
};

struct pointers_PIR_PIR{
	uz_CurrentControl_t* PI_dq;
	uz_CurrentControl_t* PI_xy1;
	uz_CurrentControl_t* PI_xy2;
	uz_subspace_resonant_control* RES_dq;
	uz_subspace_resonant_control* RES_xy1;
	uz_subspace_resonant_control* RES_xy2;
	uz_subspace_resonant_control* RES_xy3;
	uz_subspace_resonant_control* RES_XY3;
};

struct pointers_fault_control{
	uz_CurrentControl_t* xy1;
	uz_CurrentControl_t* xy2;
	uz_CurrentControl_t* xy3;
};

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
	float U_ZK1; 		// DC-Link voltage in V
	float U_ZK2; 	// DC-Link voltage 2 in V
	float U_ZK3; 	// DC-Link voltage 3 in V
	float U_ZK; 	// Medium DC-Link voltage n V
	float i_ZK1; 		// DC-Link voltage in V
	float i_ZK2; 	// DC-Link voltage 2 in V
	float i_ZK3; 	// DC-Link voltage 2 in V
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float theta_el_offset; //in rad
	float temperature;
	uint32_t  heartbeatframe_content;
	float temperature_nut[9];
	float temperature_wickelkopf[9];
	float avg_temperature_nut;
	float avg_temperature_wickelkopf;
	float temperature_inv_1;
	float temperature_inv_2;
	float temperature_inv_3;
	struct uz_resolver_pl_interface_outputs_t rotational_position;
	uz_9ph_abc_t currents_abc;
	uz_9ph_abc_t voltages_abc;
	uz_9ph_alphabeta_t currents_alphabeta;
	uz_9ph_dq_t full_currents_dq;
	uz_9ph_dq_t full_voltages_dq;
	uz_3ph_dq_t currents_dq;
	uz_3ph_alphabeta_t currents_XY1;
	uz_3ph_alphabeta_t currents_XY2;
	uz_3ph_alphabeta_t currents_XY3;
	uz_3ph_dq_t currents_xy1;
	uz_3ph_dq_t currents_xy2;
	uz_3ph_dq_t currents_xy3;
	float omega_el;
	float torque_Nm;
	uz_3ph_dq_t debug_pi_xy1;
	uz_3ph_dq_t debug_pi_xy2;
	uz_3ph_dq_t debug_pi_xy3;
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
	uz_3ph_dq_t dq_setpoints;
	bool ctrl_xy1;
	bool ctrl_xy2;
	bool ctrl_xy3;
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
	uz_temperaturecard_t* uz_Tempcard;
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
	uz_PWM_duty_freq_detection_t* tempMeasurement3;
	uz_resolverIP_t* resolver_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_d2;
	uz_VSD_9ph_FD_t* fault_detection;
	uz_CurrentControl_t* cc_instance_dq;
	struct pointers_PI_PI objects_PI_PI;
	struct pointers_PI_R objects_PI_R;
	struct pointers_PIR_PIR objects_PIR_PIR;
	struct pointers_fault_control objects_fault_control;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

