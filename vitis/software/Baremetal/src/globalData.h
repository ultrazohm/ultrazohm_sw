#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"
#include "IP_Cores/uz_NN_acc/uz_NN_acc.h"
#include "IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz/uz_PMSM_config/uz_PMSM_config.h"
#include "uz/uz_LUT_1D/uz_LUT_1D.h"
#include "uz/uz_approximate_flux/uz_approximate_flux.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

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
	uz_3ph_abc_t i_abc;
	uz_3ph_abc_t v_abc;
	uz_3ph_dq_t i_dq;
	uz_3ph_dq_t i_dq_ref;
	uz_3ph_dq_t v_dq_ref;
	uz_3ph_dq_t v_dq_ref_k2;
	uz_3ph_dq_t v_dq;
	float Torque_ref;
	float Torque;
	float v_dc;
	float n_ref_CIL;
	float Is_ref;
	float Is;
	float current_angle_deg;
	float current_angle_rad;
	float current_angle_ref;
	float omega_mech;
	float omega_elec;
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float theta_elec;
	float theta_mech;
	float theta_elec_advanced;
	float theta_offset; //in rad/s
	uz_3ph_dq_t flux_approx_real;
	uz_3ph_dq_t flux_approx_reference;
	struct uz_DutyCycle_t DutyCycle;
	struct uz_PMSM_t SynRM_config;
	struct uz_PMSM_flux_fitting_parameter_config_t fitting_parameter;
	struct uz_pmsmModel_outputs_t SynRM_outputs;
	struct uz_pmsmModel_inputs_t SynRM_inputs;
	bool HB_ok;
	bool OC_ok;
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
} actualValues;

typedef struct _referenceAndSetValues_ {
	uint32_t HB_ok_Pin_Number; // PIN 0 for status HB_ok
	uint32_t OC_ok_Pin_Number; // PIN 1 for status OC_ok
	uint32_t Inv_Reset_Pin_Number; 	// PIN 0 for reset DHG inverter
	uint32_t LMG_continues_Pin_Number; // Pin 1 for start/stop continues measurement on LMG
	uint32_t LMG_transient_Pin_Number; // Pin 2 for start/stop transient measurement on LMG
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
	uz_LUT_1D_t* LUT_CIL_current_angle;
	uz_LUT_1D_t* LUT_CIL_Is;
	uz_LUT_1D_t* LUT_bench_current_angle;
	uz_LUT_1D_t* LUT_bench_Is;
	uz_pmsmModel_t* SynRM_Model;
	uz_CurrentControl_t* CurrentControl;
	uz_approximate_flux_t* FluxApproximation;
	uz_matrix_t* matrix_input_acc;
	uz_matrix_t* matrix_output_acc;
	uz_nn_t* nn_layer_acc;
	uz_NN_acc_t* NN_acc_Instance;
	uz_axi_gpio_t* GPIO_output;
	uz_axi_gpio_t* GPIO_input;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

