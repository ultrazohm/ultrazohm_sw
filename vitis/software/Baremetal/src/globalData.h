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
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "include/uz_platform_state_machine.h"
#include "uz/uz_Space_Vector_Modulation_6ph/uz_Space_Vector_Modulation_6ph.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
#include "IP_Cores/uz_pmsmModel_6ph_dqxy/uz_pmsmModel_6ph_dqxy.h"
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
	float i_dc1;
	float i_dc2;
	float i_dc_Last;
	float v_dc_Last;
	float v_dc1;
	float v_dc2;
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_Last; 		// in rpm
	float theta_elec_Last;
	float theta_mech_Last;
	float theta_elec;
	float theta_elec_advanced;
	float theta_elec_old;
	float theta_mech;
	float theta_offset; //in rad/s
	float omega_elec_Last;
	float omega_mech_Last;
	float omega_elec;
	float omega_mech;
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
	float error;
	//Pruef-machine
	uz_6ph_abc_t i_abc;
	uz_6ph_abc_t v_abc;
	uz_6ph_abc_t v_abc_ref;
	uz_6ph_dq_t i_dqxy;
	uz_6ph_dq_t i_dqxy_ref;
	uz_6ph_dq_t i_dqxy_integrated_error;
	uz_6ph_dq_t i_dqxy_error;
	uz_6ph_dq_t v_dqxy;
	uz_6ph_dq_t v_dqxy_ref;
	uz_6ph_dq_t v_dqxy_non_limited;
	uz_6ph_dq_t u_dqxy_ref;
	struct uz_DutyCycle_2x3ph_t DutyCycle;
	//Last-machine
	uz_3ph_abc_t i_abc_Last;
	uz_3ph_abc_t v_abc_Last;
	uz_3ph_dq_t i_dq_Last;
	uz_3ph_dq_t v_dq_Last;
	uz_3ph_dq_t i_dq_Last_ref;
	uz_3ph_dq_t v_dq_Last_ref;
	struct uz_DutyCycle_t DutyCycle_Last;
	float n_ref_Last;
	float M_ref_Last;
	struct uz_pmsmModel_6ph_dqxy_outputs_t pmsm_outputs;
	struct uz_pmsmModel_6ph_dqxy_inputs_t pmsm_inputs;
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
	uz_resolver_pl_interface_t* resolver_pl_d4_Last;
	uz_resolver_pl_interface_t* resolver_pl_d4_Pruef;
	uz_resolverIP_t* resolverIP_Last;
	uz_resolverIP_t* resolverIP_Pruef;
	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;
	uz_inverter_adapter_t* inverter_d3;
	uz_CurrentControl_t* CC_dq_instance_Pruef;
	uz_CurrentControl_t* CC_xy_instance_Pruef;
	uz_CurrentControl_t* CC_dq_instance_Last;
	uz_SpeedControl_t* speed_ctrl_Last;
	uz_SetPoint_t* setpoint_ctrl_Last;
	uz_IIR_Filter_t* speed_prefilter_Last;
	uz_pmsmModel_6ph_dqxy_t* pmsm_model;
	uz_matrix_t* matrix_input_acc;
	uz_matrix_t* matrix_output_acc;
	uz_nn_t* nn_layer_acc;
	uz_NN_acc_t* NN_acc_Instance;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

