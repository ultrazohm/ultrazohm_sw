#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"
#include "IP_Cores/uz_NN_acc/uz_NN_acc.h"
#include "IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz/uz_PMSM_config/uz_PMSM_config.h"
#include "uz/uz_LUT_1D/uz_LUT_1D.h"
#include "uz/uz_approximate_flux/uz_approximate_flux.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
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

	//DUT values
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1_DUT;
	struct uz_pmsmModel_outputs_t PMSM_outputs;
	struct uz_pmsmModel_inputs_t PMSM_inputs;
	struct uz_resolver_pl_interface_outputs_t resolver_outputs_Load;
	float i_dc_DUT;
	float v_dc_DUT;
	float mechanicalRotorSpeed_DUT; 		// in rpm
	float theta_mech_DUT;
	float theta_elec_DUT;
	float theta_elec_advanced_DUT;
	float theta_elec_old_DUT;
	float theta_offset_DUT; //in rad/s
	float omega_elec_DUT;
	float omega_mech_DUT;
	float temp_VSI_DUT;
	uz_3ph_dq_t i_dq_DUT;
	uz_3ph_dq_t i_ref_dq_DUT;
	uz_3ph_abc_t i_abc_DUT;
	uz_3ph_dq_t v_dq_DUT;
	uz_3ph_dq_t v_ref_dq_DUT;
	uz_3ph_dq_t v_ref_dq_pre_limit_DUT;
	uz_3ph_abc_t v_abc_DUT;
	struct uz_DutyCycle_t DutyCycle_DUT;
	struct uz_DutyCycle_t DutyCycle_manual_DUT;
	float is_DUT;
	float is_ref_DUT;
	float current_angle_degree_DUT;
	float current_angle_ref_degree_DUT;
	float Torque_DUT;
	float Torque_ref_DUT;
	uz_3ph_dq_t flux_approx_real_DUT;
	uz_3ph_dq_t flux_approx_reference_DUT;
	uz_3ph_dq_t v_dq_ref_CIL_manual;
	uz_3ph_dq_t v_dq_ref_pre_limit_DUT;

	//Load values
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2_Load;
	float i_dc_Load;
	float v_dc_Load;
	float mechanicalRotorSpeed_Load; 		// in rpm
	float theta_elec_Load;
	float theta_mech_Load;
	float theta_elec_advanced_Load;
	float theta_elec_old_Load;
	float omega_elec_Load;
	float omega_mech_Load;
	float temp_VSI_Load;
	uz_3ph_dq_t i_dq_Load;
	uz_3ph_dq_t i_ref_dq_Load;
	uz_3ph_abc_t i_abc_Load;
	uz_3ph_dq_t v_dq_Load;
	uz_3ph_dq_t v_ref_dq_Load;
	uz_3ph_abc_t v_abc_Load;
	float is_Load;
	float Torque_Load;
	float Torque_ref_Load;
	float speed_ref_Load;
	float speed_ref_filtered_Load;
	struct uz_DutyCycle_t DutyCycle_Load;

	//other stuff
	float start_marker;

	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
} actualValues;

typedef struct _referenceAndSetValues_ {
	struct uz_PMSM_t PMSM_DUT_config;
	struct uz_PMSM_t PMSM_Load_config;
	struct uz_PMSM_flux_fitting_parameter_config_t Fitting_parameter_DUT;
	float StartMarker;
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
	uz_resolver_pl_interface_t* resolver_pl_IP;
	uz_resolverIP_t* resolver_IP;
	uz_inverter_adapter_t* inverter_d1_DUT;
	uz_inverter_adapter_t* inverter_d2_Load;
	uz_LUT_1D_t* LUT_current_angle;
	uz_LUT_1D_t* LUT_Is;
	uz_pmsmModel_t* PMSM_Model;
	uz_SpeedControl_t* SpeedControl_Load;
	uz_CurrentControl_t* CurrentControl_Load;
	uz_SetPoint_t* SetPoint_Load;
	uz_CurrentControl_t* CurrentControl_DUT;
	uz_approximate_flux_t* FluxApproximation_DUT;
	uz_matrix_t* matrix_input_acc;
	uz_matrix_t* matrix_output_acc;
	uz_nn_t* nn_layer_acc;
	uz_NN_acc_t* NN_acc_Instance;
	uz_IIR_Filter_t* Speed_Filter_Load;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

