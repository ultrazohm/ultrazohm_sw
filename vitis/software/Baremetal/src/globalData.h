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
	uz_3ph_dq_t v_dq;
	float M_ref;
	float Is_ref;
	float Is;
	float current_angle;
	float current_angle_ref;
	float omega_mech;
	float omega_elec;
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float theta_elec;
	float theta_mech;
	float theta_elec_advanced;
	float theta_offset; //in rad/s
	struct uz_DutyCycle_t DutyCycle;
	struct uz_PMSM_t pmsm_config;
	struct uz_PMSM_flux_fitting_parameter_config_t fitting_parameter;
	struct uz_pmsmModel_outputs_t pmsm_outputs;
	struct uz_pmsmModel_inputs_t pmsm_inputs;
	float temperature;
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
	uz_LUT_1D_t* LUT_CIL_angle;
	uz_LUT_1D_t* LUT_CIL_Is;
	uz_LUT_1D_t* LUT_bench_angle;
	uz_LUT_1D_t* LUT_bench_Is;
	uz_pmsmModel_t* pmsmModel;
	uz_CurrentControl_t* CurrentControl;
	uz_approximate_flux_t* FluxApproximation;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

