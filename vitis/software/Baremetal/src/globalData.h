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
#include "include/uz_platform_state_machine.h"
#include "uz/uz_Space_Vector_Modulation_6ph/uz_Space_Vector_Modulation_6ph.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"

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
	float i_a1; 		// Machine side current in A
	float i_b1; 		// Machine side current in A
	float i_c1; 		// Machine side current in A
	float i_a2; 		// Machine side current in A
	float i_b2; 		// Machine side current in A
	float i_c2; 		// Machine side current in A
	float i_a_Last; 		// Machine side current in A
	float i_b_Last; 		// Machine side current in A
	float i_c_Last; 		// Machine side current in A
	float i_dc1;
	float i_dc2;
	float i_dc_Last;
	float v_a1; 		// Machine side voltage in V
	float v_b1; 		// Machine side voltage in V
	float v_c1; 		// Machine side voltage in V
	float v_a2; 		// Machine side voltage in V
	float v_b2; 		// Machine side voltage in V
	float v_c2; 		// Machine side voltage in V
	float v_a_Last; 		// Machine side voltage in V
	float v_b_Last; 		// Machine side voltage in V
	float v_c_Last; 		// Machine side voltage in V
	float v_dc_Last;
	float v_dc1;
	float v_dc2;
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
	float I_x;
	float I_y;
	float U_d;
	float U_q;
	float U_x;
	float U_y;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
	struct uz_resolver_pl_interface_outputs_t resolver_outputs_d4_Last;
	struct uz_resolver_pl_interface_outputs_t resolver_outputs_d4_Pruef;
	float temp_VSI_1;
	float temp_VSI_2;
	float temp_VSI_3;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d3;
	bool select_Control;
	bool select_fixed_values;
	uz_6ph_dq_t v_dqxy_ref;
	uz_3ph_dq_t v_dq_ref;
	uz_6ph_abc_t i_abc_meas;
	uz_6ph_abc_t v_abc_meas;
	uz_6ph_dq_t i_dqxy_meas;
	uz_6ph_dq_t v_dqxy_meas;
	uz_3ph_dq_t i_dq_meas;
	uz_3ph_dq_t i_dq_ref;
	struct uz_DutyCycle_2x3ph_t DutyCycle_output;
	struct uz_svm_asym_6ph_CSVPWM24_out svm_out;
	float button;
	float error;

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
	uz_resolver_pl_interface_t* resolver_pl_d4_Last;
	uz_resolver_pl_interface_t* resolver_pl_d4_Pruef;
	uz_resolverIP_t* resolverIP_Last;
	uz_resolverIP_t* resolverIP_Pruef;
	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;
	uz_inverter_adapter_t* inverter_d3;
	uz_CurrentControl_t* CC_dq_instance;
	uz_CurrentControl_t* CC_xy_instance;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

