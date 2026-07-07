#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
#include "IP_Cores/uz_plantPT1/uz_plantPT1.h"
#include "uz/uz_ddpg/uz_ddpg_agent.h"
#include "uz/uz_dqn/uz_dqn_agent.h"
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
	float d3_input_loopback_uint32;
	float dqn_pt1_actual;
	float dqn_pt1_reference;
	float dqn_pt1_setpoint;
	float dqn_pt1_action;
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
	int32_t resolver_pl_interface_d4_1_revolution_counter;
	float resolver_pl_interface_d4_1_position_mech_2pi;
	float resolver_pl_interface_d4_1_position_el_2pi;
	float resolver_pl_interface_d4_1_omega_mech_rad_s;
	float resolver_pl_interface_d4_1_n_mech_rpm;
	float resolver_pl_interface_d4_1_omega_el_rad_s;
	int32_t resolver_pl_interface_d4_2_revolution_counter;
	float resolver_pl_interface_d4_2_position_mech_2pi;
	float resolver_pl_interface_d4_2_position_el_2pi;
	float resolver_pl_interface_d4_2_omega_mech_rad_s;
	float resolver_pl_interface_d4_2_n_mech_rpm;
	float resolver_pl_interface_d4_2_omega_el_rad_s;
	int32_t resolver_pl_interface_d4_3_revolution_counter;
	float resolver_pl_interface_d4_3_position_mech_2pi;
	float resolver_pl_interface_d4_3_position_el_2pi;
	float resolver_pl_interface_d4_3_omega_mech_rad_s;
	float resolver_pl_interface_d4_3_n_mech_rpm;
	float resolver_pl_interface_d4_3_omega_el_rad_s;
	float incremental_encoder_d5_1_theta_el;
	float incremental_encoder_d5_1_omega_mech;
	float incremental_encoder_d5_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_1_position;
	uint32_t incremental_encoder_d5_1_position_w_offset;
	uint32_t incremental_encoder_d5_1_index_found;
	float incremental_encoder_d5_2_theta_el;
	float incremental_encoder_d5_2_omega_mech;
	float incremental_encoder_d5_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_2_position;
	uint32_t incremental_encoder_d5_2_position_w_offset;
	uint32_t incremental_encoder_d5_2_index_found;
	float incremental_encoder_d5_3_theta_el;
	float incremental_encoder_d5_3_omega_mech;
	float incremental_encoder_d5_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_3_position;
	uint32_t incremental_encoder_d5_3_position_w_offset;
	uint32_t incremental_encoder_d5_3_index_found;
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
	float pwm_3L_0_halfBridgeDutyCycle_1;
	float pwm_3L_0_halfBridgeDutyCycle_2;
	float pwm_3L_0_halfBridgeDutyCycle_3;
/* Project Wizard END: referenceAndSetValues */
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	uz_plantPT1_t* plant_pt1;
	uz_dqn_agent_t* dqn_agent;
	uz_ddpg_agent_t* ddpg_agent;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_wavegen_three_phase* three_phase_sine;
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_adcLtc2311_t* adc_ltc2311_a2;
	uz_adcLtc2311_t* adc_ltc2311_a3;
	uz_inverter_adapter_t* inverter_adapter_d1;
	uz_inverter_adapter_t* inverter_adapter_d2;
	uz_resolverIP_t* resolver_ip_d4_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_1;
	uz_resolverIP_t* resolver_ip_d4_2;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_2;
	uz_resolverIP_t* resolver_ip_d4_3;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_3;
	uz_incrementalEncoder_t* incremental_encoder_d5_1;
	uz_incrementalEncoder_t* incremental_encoder_d5_2;
	uz_incrementalEncoder_t* incremental_encoder_d5_3;
/* Project Wizard END: objects */
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif
