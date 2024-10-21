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

// union allows to access the values as array and individual variables
// see also this link for more information: https://hackaday.com/2018/03/02/unionize-your-variables-an-introduction-to-advanced-data-types-in-c/
typedef union _ConversionFactors_
{
	struct
	{
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

typedef union _Measurements_
{
	struct
	{
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

typedef struct _ADCcard_
{
	ConversionFactors cf;
	Measurements me;
} ADCcard;

typedef struct _AnalogAdapters_
{
	ADCcard A1;
	ADCcard A2;
	ADCcard A3;
} AnalogAdapters;

typedef struct _actualValues_
{
	float pwm_frequency_hz;
	float isr_samplerate_s;
	float d5_1_omega_mech_rad_per_sec; // in rpm
	float d5_1_n_rpm;
	float d5_1_n_rpm_filtered; // in rpm
	float d5_2_theta_el;
	float d5_2_omega_mech_rad_per_sec;
	float d5_2_n_rpm;
	float d5_2_n_rpm_filtered;
	float d5_3_theta_el;
	float d5_3_omega_mech_rad_per_sec;
	float d5_3_n_rpm;
	float d5_3_n_rpm_filtered;
	float mechanicalRotorSpeed_filtered_prime_mover; // in rpm
	float d5_1_theta_el;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;
	struct uz_resolver_pl_interface_outputs_t Resolver_outputs;
	float temperature;
	uint32_t heartbeatframe_content;
	float electricalRotorSpeed_1;
	float electricalRotorSpeed_2;
	float snd_fld[21];
} actualValues;

typedef struct _referenceAndSetValues_
{
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

typedef struct
{
	uz_PWM_SS_2L_t *pwm_d1;
	uz_PWM_SS_2L_t *pwm_d2;
	uz_PWM_SS_2L_t *pwm_d1_pin_12_to_17;
	uz_PWM_SS_2L_t *pwm_d1_pin_18_to_23;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_6_to_11;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_12_to_17;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_18_to_23;
	uz_incrementalEncoder_t *encoder_D5_1;
	uz_incrementalEncoder_t *encoder_D5_2;
	uz_incrementalEncoder_t *encoder_D5_3;
	uz_mux_axi_t *mux_axi;
	uz_inverter_adapter_t *inverter_d1;
	uz_inverter_adapter_t *inverter_d2;
	uz_resolver_pl_interface_t *resolver_pl_d4;
	uz_resolverIP_t *resolver_d4;
	uz_approximate_flux_t *approximate_flux_instance;
	uz_CurrentControl_Kp_id_adjustment_t *Kp_id_adjustment_instance;
	uz_CurrentControl_Kp_iq_adjustment_t *Kp_iq_adjustment_instance;
	uz_matrix_t *matrix_input;
	uz_nn_t *nn_layer;
	uz_pmsm_control_t *d1_controller;
	uz_pmsm_control_t *d2_controller;
	uz_IIR_Filter_t *tracking_error_filter_prime_mover;
} object_pointers_t;

typedef struct controller_data
{
	struct uz_pmsm_actual_data *actual_data;
	struct uz_pmsm_measurement_values *measurement_values;
	struct uz_pmsm_reference_values *reference_values;
} controller_data;

typedef struct javascope_global
{
	float prime_mover_reference_speed_in_rpm;
	uz_3ph_dq_t dut_reference_currents_in_A;
	bool select_automatic_idiq;
	float start_marker;
} javascope_global;

typedef struct auto_profile
{
	float prime_mover_reference_speed_in_rpm;
	uz_3ph_dq_t dut_reference_currents_in_A;
	float speed_tracking_error;
	bool wait_for_n_ref;		   // needs to be true initially
	bool speed_setpoint_reached;   // needs to be false initially
	bool start_angle_found;		   // needs to be fals initially
	bool change_speed;			   // false initally
	uint32_t setpoint_index;	   // init als zero
	uint32_t n_ref_setpoint_index; // init als zero
	float theta_mech_dut_old;
} auto_profile;

typedef struct _DS_Data_
{
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
	controller_data dut;
	controller_data prime_mover;
	float prime_mover_reference_speed_in_rpm;
	float M_meas_Nm;
	bool d1_operating_region_violation;
	bool d2_operating_region_violation;
	uz_3ph_dq_t dut_reference_currents_in_A;
	javascope_global javascope;
	auto_profile profile;
} DS_Data;

#endif
