#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"

enum current_control_select {
		PI_FOC,
		FCS_MPC,
		DDPG_CC
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
	float i_a_left;
	float i_b_left;
	float i_c_left;
	float i_a_right;
	float i_b_right;
	float i_c_right;
	float v_a_left;
	float v_b_left;
	float v_c_left;
	float v_a_right;
	float v_b_right;
	float v_c_right;
	float v_dc_left;
	float v_dc_right;
	float i_dc_left;
	float i_dc_right;
	float i_d_left;
	float i_q_left;
	float i_d_right;
	float i_q_right;
	float v_d_left;
	float v_q_left;
	float v_d_right;
	float v_q_right;
	float speed_rpm_left;
	float speed_rpm_right;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_left;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_right;
	struct uz_inverter_adapter_outputs_t inverter_left_status;
	struct uz_inverter_adapter_outputs_t inverter_right_status;
	float mean_temp_inv_left;
	float mean_temp_inv_right;
	float polepairs_left;
	float polepairs_right;
	float lambda_d;
	float lambda_q;
	float lambda_u;
	float lambda_u_e5;
	float i_max_mpc;
	float f_sw_avg_Hz;
	float i_d_ip;
	float i_q_ip;
	float i_a_pu;
	float i_b_pu;
	float i_c_pu;
	float vd_pu;
	float vq_pu;
	float id_delay_pu;
	float iq_delay_pu;
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
	float M_ref_left;
	float n_ref_left;
	uz_3ph_dq_t i_dq_ref_right;
	uz_3ph_dq_t i_dq_ref_left;
	enum current_control_select current_ctrl_select;
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
	uz_resolverIP_t* resolver_left;
	uz_resolverIP_t* resolver_right;
	uz_resolver_pl_interface_t* resolver_pl_interface_left;
	uz_resolver_pl_interface_t* resolver_pl_interface_right;
	uz_CurrentControl_t* current_ctrl_left;
	uz_CurrentControl_t* current_ctrl_right;
	uz_SpeedControl_t* speed_ctrl_left;
	uz_SetPoint_t* setpoint_ctrl_left;
	uz_inverter_adapter_t* uz_d_inverter_left;
	uz_inverter_adapter_t* uz_d_inverter_right;
	uz_mux_axi_t* mux_axi;
	uz_mux_axi_t* mux_axi_a2;
	uz_nn_t* nn_layer;
	uz_matrix_t* matrix_input;
}object_pointers_t;


typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

