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
#include "uz/uz_space_vector_modulation/uz_space_vector_modulation.h"

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
	float electricalRotorSpeed;
	float omega_mech;
	float omega_elec;
	float temp_VSI_1;
	float temp_VSI_2;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;

	bool select_CurrentControl;
	bool select_Real;
	bool select_CIL;
	float n_ref_rpm;
	float i_d_ref;
	float i_q_ref;
	float i_X_ref;
	float i_Y_ref;

	int PWM_select;
	//For testing purposes only
	float current_sector;
	float SV_angle;
	float alpha_trafo;
	float beta_trafo;
	float x_trafo;
	float y_trafo;
	float nullminus_trafo;
	float nullplus_trafo;


	uz_6ph_alphabeta_t u_ref_6ph_alphabeta;
	uz_6ph_abc_t u_ref_6ph_abc;
	uz_3ph_abc_t u_ref_abc;


	uz_6ph_dq_t v_dqxy_ref;

	uz_6ph_dq_t v_dqxy_limited_volts;
	uz_3ph_dq_t v_dq_limited_volts;
	uz_3ph_dq_t v_xy_limited_volts;
	uz_3ph_dq_t v_dq_non_limited_volts;
	uz_3ph_dq_t v_xy_non_limited_volts;
	uz_6ph_dq_t v_dqxy_limited_volts_k_old;
	uz_6ph_dq_t v_dqxy_non_limited_volts;
	uz_6ph_dq_t CIL_i_dqxy_meas;
	uz_6ph_abc_t REAL_i_abc_meas;
	uz_6ph_abc_t REAL_v_abc_meas;
	uz_6ph_abc_t REAL_v_abc_ref;
	uz_6ph_alphabeta_t REAL_v_vsd_ref;
	uz_6ph_dq_t REAL_i_dqxy_meas;
	uz_6ph_dq_t REAL_v_dqxy_meas;
	uz_3ph_dq_t CIL_v_dq_reference;
	uz_3ph_dq_t CIL_v_xy_reference;
	uz_3ph_dq_t CIL_v_z1z2_reference;
	uz_3ph_dq_t REAL_v_dq_reference;
	uz_3ph_dq_t REAL_v_xy_reference;
	uz_3ph_dq_t REAL_v_z1z2_reference;
	uz_3ph_dq_t i_dq_reference;
	uz_3ph_dq_t i_xy_reference;
	uz_3ph_dq_t i_z1z2_reference;
	uz_3ph_dq_t CIL_i_dq_meas;
	uz_3ph_dq_t CIL_i_xy_meas;
	uz_3ph_dq_t CIL_i_z1z2_meas;
	uz_3ph_dq_t REAL_i_dq_meas;
	uz_3ph_dq_t REAL_i_xy_meas;
	uz_3ph_dq_t REAL_i_z1z2_meas;
	struct uz_DutyCycle_2x3ph_t DutyCycle_output;
	struct uz_DutyCycle_2x3ph_t DutyCycle_6ph_test;

   	int phaseshiftoption;
	float shift_system_1;
	float shift_system_2;

	int test_var;
	float theta_from_ref;
	float Amp;

	float V_DC_Volts;

	float phi_rad;

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
	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;

	uz_IIR_Filter_t *IRR_filter_A1;
	uz_IIR_Filter_t *IRR_filter_B1;
	uz_IIR_Filter_t *IRR_filter_C1;
	uz_IIR_Filter_t *IRR_filter_A2;
	uz_IIR_Filter_t *IRR_filter_B2;
	uz_IIR_Filter_t *IRR_filter_C2;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

