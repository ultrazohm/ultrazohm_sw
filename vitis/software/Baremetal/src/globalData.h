#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "xparameters.h"
#include "IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"
#include "IP_Cores/uz_NN_acc/uz_NN_acc.h"
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
	float i_dc1;
	float i_dc2;
	float v_a1; 		// Machine side voltage in V
	float v_b1; 		// Machine side voltage in V
	float v_c1; 		// Machine side voltage in V
	float v_a2; 		// Machine side voltage in V
	float v_b2; 		// Machine side voltage in V
	float v_c2; 		// Machine side voltage in V
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
	float I_X;
	float I_Y;
	float U_d;
	float U_q;
	float U_X;
	float U_Y;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float omega_mech;
	float omega_elec;
	float temp_VSI_1;
	float temp_VSI_2;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;
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
	uz_pmsm_model6ph_dq_t* CIL_pmsm;
	uz_CurrentControl_t* CC_dq_instance;
	uz_CurrentControl_t* CC_xy_instance;
	uz_matrix_t* matrix_input_15n;
	uz_nn_t* nn_layer_15n;
	uz_matrix_t* matrix_input_17n;
	uz_matrix_t* matrix_output_17n;
	uz_nn_t* nn_layer_17n;
	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;
	uz_NN_acc_t* NN_acc_Instance;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

