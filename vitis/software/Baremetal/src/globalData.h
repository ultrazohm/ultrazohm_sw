#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz/uz_BLDC_control/uz_BLDC_control.h"
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
	float I_L1; 		// Grid side current in A
	float I_L2; 		// Grid side current in A
	float I_L3; 		// Grid side current in A
	float U_L1; 		// Grid side voltage in V
	float U_L2; 		// Grid side voltage in V
	float U_L3; 		// Grid side voltage in V
	float I_U; 		// Machine side current in A
	float I_V; 		// Machine side current in A
	float I_W; 		// Machine side current in A
	float U_U; 		// Machine side voltage in V
	float U_V; 		// Machine side voltage in V
	float U_W; 		// Machine side voltage in V
	float U_ZK; 		// DC-Link voltage in V
	float U_ZK2; 	// DC-Link voltage 2 in V
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float mechanicalPosition; 		// in m
	float mechanicalTorque; 			// in Nm
	float mechanicalTorqueSensitive; // in Nm
	float mechanicalTorqueObserved; 	// in Nm for observing the load torque
	float I_d;
	float I_q;
	float U_d;
	float U_q;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad
	float omega_mech;
	float omega_elec; //rad/s
	float temperature;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	float u_a;
	float u_b;
	float u_c;
	float i_a;
	float i_b;
	float i_c;
	float I_ZK;
	float errorcode;

	float d_a_ref;
	float d_b_ref;
	float d_c_ref;
	bool directDuty;

	uz_3ph_abc_t i_abc_m;
	uz_3ph_abc_t u_abc_m;
	uz_3ph_dq_t i_dq_m;
	uz_3ph_dq_t u_dq_m;
	uz_3ph_dq_t i_dq_ref;
	uz_3ph_dq_t u_dq_ref;

	// @@@@@@@
	float d_BLDC;
	float u_BLDC_ref;
	int sector;
	float n_act_rpm;
	float n_ref_rpm;
	float I_ph_m;
	float i_ref_kaskade;
	float I_ph_ref;
	bool SpeedControl;
	bool CurrentControl;
	bool CascadeControl;
	bool DutyCycleControl;
	float U_ctrl_ref;
	float I_ph_error;
	float n_RPM_error;
	float i_high;
	float u_ab;
	float u_ca;
	float u_bc;
	float u_n;
	float u_ph1;
	float u_ph2;
	float u_ph3;
	float n_ref_filtered;
	// @@@@@@@

	struct uz_DutyCycle_t output_Dutycycle;

	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
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
	uz_incrementalEncoder_t* encoder_D5;
	uz_mux_axi_t* mux_axi;
	uz_inverter_adapter_t* inverter_D1;
	uz_CurrentControl_t* current_control;
	uz_PI_Controller* PI_current; //@@@
	uz_PI_Controller* PI_speed; //@@@@
	uz_PI_Controller* PI_speed_only; //@@@@
	uz_BLDC_control* BLDC_systems; //@@@@
	uz_IIR_Filter_t* RefSpeedFilter; //@@@@
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

