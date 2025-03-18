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

#include "IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "Codegen/uz_flussschaetzer.h"

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
	float i_a;
	float i_b;
	float i_c;
	float u_a;
	float u_b;
	float u_c;
	float U_ZK; 		// DC-Link voltage in V
	float I_ZK;			// DC-Link current in A
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
	float theta_elec2;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float omega_mech;
	float omega_elec;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float errorcode;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	float n_ref_rpm;
	bool select_speed_control;

	uz_3ph_abc_t i_abc_m;
	uz_3ph_abc_t u_abc_m;
	uz_3ph_dq_t i_dq_m;
	uz_3ph_dq_t u_dq_m;
	uz_3ph_dq_t i_dq_ref;
	uz_3ph_dq_t u_dq_ref;
	Flussschaetzer_output_data FS_output;
	uz_3ph_alphabeta_t i_alphabeta_m;
	uz_3ph_alphabeta_t u_alphabeta_ref;

	struct uz_DutyCycle_t output_Dutycycle;

	struct uz_pmsmModel_outputs_t pmsmModel_output;
	struct uz_pmsmModel_inputs_t pmsmModel_input;

	bool select_CIL;


	float d_a_ref;
	float d_b_ref;
	float d_c_ref;
	float u_ab;
	float u_bc;
	float u_ca;
	float u_n;
	float u_ph1;
	float u_ph2;
	float u_ph3;

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
	uz_inverter_adapter_t* inverter_d1;

	uz_CurrentControl_t* current_control;
	uz_SpeedControl_t* speed_control;

	uz_pmsmModel_t *pmsmModel;
	uz_Flussschaetzer_t *Flussschaetzer;

}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

