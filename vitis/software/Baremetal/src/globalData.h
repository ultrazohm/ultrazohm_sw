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
#include "uz/uz_approximate_flux/uz_approximate_flux.h"
#include "uz/uz_CurrentControl_Kp_id_adjustment/uz_CurrentControl_Kp_id_adjustment.h"
#include "uz/uz_CurrentControl_Kp_iq_adjustment/uz_CurrentControl_Kp_iq_adjustment.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_pmsm_control/uz_pmsm_control.h"
#include "uz/uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"

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
	float mechanicalRotorSpeed_brose; 		// in rpm
	float omega_mech_rad_per_sec_brose;		// in rpm
	float mechanicalRotorSpeed_heidrive; 		// in rpm
	float mechanicalRotorSpeed_3; 		// in rpm
	float mechanicalRotorSpeed_filtered_brose; // in rpm
	float mechanicalRotorSpeed_filtered_heidrive; // in rpm
	float mechanicalRotorSpeed_filtered_3; // in rpm
	float mechanicalPosition; 		// in m
	float mechanicalTorque; 			// in Nm
	float mechanicalTorqueSensitive; // in Nm
	float mechanicalTorqueObserved; 	// in Nm for observing the load torque
	float I_d_1;
	float I_q_1;
	float I_d_2;
	float I_q_2;
	float U_d_1;
	float U_q_1;
	float theta_elec_brose;
	float theta_elec_heidrive;
	float omega_mech_rad_per_sed_unfiltered;
	float omega_mech_rad_per_sed ;
	float theta_elec_3;
	float theta_mech_brose;
	float theta_offset_1; //in rad/s
	float theta_offset_2; //in rad/s
	float omega_el_brose;
	float omega_el_heidrive;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1_brose;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2_heidrive;
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed_1;
	float electricalRotorSpeed_2;
	float snd_fld[21];
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
	uz_PWM_SS_2L_t* pwm_d1_brose;
	uz_PWM_SS_2L_t* pwm_d2_heidrive;
	uz_PWM_SS_2L_t* pwm_d1_pin_12_to_17;
	uz_PWM_SS_2L_t* pwm_d1_pin_18_to_23;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_6_to_11;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_12_to_17;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_18_to_23;
	uz_incrementalEncoder_t* encoder_D5_1;
	uz_incrementalEncoder_t* encoder_D5_2;
	uz_incrementalEncoder_t* encoder_D5_3;
	uz_encoder_offset_estimation_t * offset_estimation;
	uz_mux_axi_t *mux_axi;
	uz_inverter_adapter_t* inverter_d1_brose;
	uz_inverter_adapter_t* inverter_d2_heidrive;
	uz_resolver_pl_interface_t* resolver_pl_d4;
	uz_resolverIP_t* resolver_d4;
	uz_matrix_t* matrix_input;
	uz_nn_t* nn_layer;
	uz_IIR_Filter_t* speed_setpoint_filter_heidrive;
	uz_IIR_Filter_t* tracking_error_filter_heidrive;
	uz_pmsm_control_t *heidrive_controller;
	uz_pmsm_control_t *brose_controller;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	struct uz_pmsm_actual_data * heidrive_actual_data;
	struct uz_pmsm_measurement_values *heidrive_measurement_values;
	struct uz_pmsm_reference_values *heidrive_reference_values;
	struct uz_pmsm_actual_data *brose_actual_data;
	struct uz_pmsm_measurement_values *brose_measurement_values;
	struct uz_pmsm_reference_values *brose_reference_values;
	float* heidrive_theta_offset;
	float* brose_theta_offset;
	object_pointers_t objects;
} DS_Data;

#endif
