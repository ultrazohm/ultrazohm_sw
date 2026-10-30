#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "uz/uz_pmsm_control/uz_pmsm_control.h"
#include "../src/uz/uz_signals/uz_signals.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	struct uz_pmsmModel_inputs_t pmsm_cil_inputs;
	struct uz_pmsmModel_outputs_t pmsm_cil_outputs;
	struct uz_pmsm_measurement_values dut_measurements;
	enum uz_pmsm_control_safe_operating_region_violation dut_violation;
	float dut_violation_code; /* JavaScope transports floats, not enum storage. */
	/* Project Wizard BEGIN: actualValues */
	float adc_ltc2311_a1_ch0;
	float adc_ltc2311_a1_ch1;
	float adc_ltc2311_a1_ch2;
	float adc_ltc2311_a1_ch3;
	float adc_ltc2311_a1_ch4;
	float adc_ltc2311_a1_ch5;
	float adc_ltc2311_a1_ch6;
	float adc_ltc2311_a1_ch7;
	float adc_ltc2311_a2_ch0;
	float adc_ltc2311_a2_ch1;
	float adc_ltc2311_a2_ch2;
	float adc_ltc2311_a2_ch3;
	float adc_ltc2311_a2_ch4;
	float adc_ltc2311_a2_ch5;
	float adc_ltc2311_a2_ch6;
	float adc_ltc2311_a2_ch7;
	float adc_ltc2311_a3_ch0;
	float adc_ltc2311_a3_ch1;
	float adc_ltc2311_a3_ch2;
	float adc_ltc2311_a3_ch3;
	float adc_ltc2311_a3_ch4;
	float adc_ltc2311_a3_ch5;
	float adc_ltc2311_a3_ch6;
	float adc_ltc2311_a3_ch7;
	struct uz_inverter_adapter_outputs_t inverter_adapter_d1;
	struct uz_inverter_adapter_outputs_t inverter_adapter_d2;
	uint32_t ssi_encoder_d4_1_position_raw_single_turn;
	uint32_t ssi_encoder_d4_1_position_raw_multi_turn;
	uint32_t ssi_encoder_d4_1_position_multi_turn;
	float ssi_encoder_d4_1_position_mech_si_single_turn;
	float ssi_encoder_d4_1_position_el_si_single_turn;
	float ssi_encoder_d4_1_speed_mech_si;
	float ssi_encoder_d4_1_speed_el_si;
	float ssi_encoder_d4_1_speed_mech_rpm;
	int32_t resolver_pl_interface_d5_1_revolution_counter;
	float resolver_pl_interface_d5_1_position_mech_2pi;
	float resolver_pl_interface_d5_1_position_el_2pi;
	float resolver_pl_interface_d5_1_omega_mech_rad_s;
	float resolver_pl_interface_d5_1_n_mech_rpm;
	float resolver_pl_interface_d5_1_omega_el_rad_s;
	int32_t resolver_pl_interface_d5_2_revolution_counter;
	float resolver_pl_interface_d5_2_position_mech_2pi;
	float resolver_pl_interface_d5_2_position_el_2pi;
	float resolver_pl_interface_d5_2_omega_mech_rad_s;
	float resolver_pl_interface_d5_2_n_mech_rpm;
	float resolver_pl_interface_d5_2_omega_el_rad_s;
/* Project Wizard END: actualValues */
} actualValues;

typedef struct _referenceAndSetValues_ {
/* Project Wizard BEGIN: referenceAndSetValues */
	float pwm_2L_0_halfBridgeDutyCycle_1;
	float pwm_2L_0_halfBridgeDutyCycle_2;
	float pwm_2L_0_halfBridgeDutyCycle_3;
	float pwm_2L_1_halfBridgeDutyCycle_1;
	float pwm_2L_1_halfBridgeDutyCycle_2;
	float pwm_2L_1_halfBridgeDutyCycle_3;
	float pwm_2L_2_halfBridgeDutyCycle_1;
	float pwm_2L_2_halfBridgeDutyCycle_2;
	float pwm_2L_2_halfBridgeDutyCycle_3;
	float pwm_2L_3_halfBridgeDutyCycle_1;
	float pwm_2L_3_halfBridgeDutyCycle_2;
	float pwm_2L_3_halfBridgeDutyCycle_3;
	float pwm_3L_0_halfBridgeDutyCycle_1;
	float pwm_3L_0_halfBridgeDutyCycle_2;
	float pwm_3L_0_halfBridgeDutyCycle_3;
/* Project Wizard END: referenceAndSetValues */
	float speed_ref_rpm_prime_mover;
	uz_3ph_dq_t dut_current_reference_A;
	float pmsm_cil_dc_link_voltage_V;
	bool dut_acknowledge_error; /* One-shot request; accepted only outside control_state. */
	float ramped_speed_ref_rpm_prime_mover;
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	uz_pmsmModel_t *pmsm_cil;
	uz_pmsm_control_t *dut;
	uz_ramp_t *speed_ref_ramp_prime_mover;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_2;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_3;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_3;
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_adcLtc2311_t* adc_ltc2311_a2;
	uz_adcLtc2311_t* adc_ltc2311_a3;
	uz_inverter_adapter_t* inverter_adapter_d1;
	uz_inverter_adapter_t* inverter_adapter_d2;
	uz_ssi_interface_t* ssi_encoder_d4_1;
	uz_resolverIP_t* resolver_ip_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_1;
	uz_resolverIP_t* resolver_ip_d5_2;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_2;
/* Project Wizard END: objects */
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif

