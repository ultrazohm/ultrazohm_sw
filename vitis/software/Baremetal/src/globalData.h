#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
#include "IP_Cores/uz_plantPT1/uz_plantPT1.h"
#include "IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "uz/uz_ddpg/uz_ddpg_agent.h"
#include "uz/uz_dqn/uz_dqn_agent.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float d3_input_loopback_uint32;
	float dqn_pt1_actual;
	float dqn_pt1_reference;
	float dqn_pt1_javascope_setpoint;
	float dqn_pt1_action;
	float deskbench_dut_i_a_A;
	float deskbench_dut_i_b_A;
	float deskbench_dut_i_c_A;
	float deskbench_dut_i_dc_A;
	float deskbench_dut_v_a_V;
	float deskbench_dut_v_b_V;
	float deskbench_dut_v_c_V;
	float deskbench_dut_v_dc_V;
	float deskbench_dut_i_d_A;
	float deskbench_dut_i_q_A;
	float deskbench_dut_v_d_V;
	float deskbench_dut_v_q_V;
	float deskbench_dut_omega_mech_rad_s;
	float deskbench_dut_speed_rpm;
	float deskbench_dut_theta_el_rad;
	float deskbench_dut_mean_temp_degC;
	float deskbench_dut_pmsm_model_i_d_A;
	float deskbench_dut_pmsm_model_i_q_A;
	float deskbench_dut_pmsm_model_torque_Nm;
	float deskbench_dut_pmsm_model_omega_mech_rad_s;
	float deskbench_prime_mover_i_a_A;
	float deskbench_prime_mover_i_b_A;
	float deskbench_prime_mover_i_c_A;
	float deskbench_prime_mover_i_dc_A;
	float deskbench_prime_mover_v_a_V;
	float deskbench_prime_mover_v_b_V;
	float deskbench_prime_mover_v_c_V;
	float deskbench_prime_mover_v_dc_V;
	float deskbench_prime_mover_i_d_A;
	float deskbench_prime_mover_i_q_A;
	float deskbench_prime_mover_v_d_V;
	float deskbench_prime_mover_v_q_V;
	float deskbench_prime_mover_omega_mech_rad_s;
	float deskbench_prime_mover_speed_rpm;
	float deskbench_prime_mover_theta_el_rad;
	float deskbench_prime_mover_mean_temp_degC;
	float deskbench_machine_polepairs;
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
	float deskbench_prime_mover_n_ref_rpm;
	float deskbench_prime_mover_n_ref_rpm_filtered;
	float deskbench_prime_mover_M_ref_Nm;
	uz_3ph_dq_t deskbench_prime_mover_i_dq_ref_A;
	uz_3ph_dq_t deskbench_dut_i_dq_ref_A;
/* Project Wizard BEGIN: referenceAndSetValues */
	struct uz_DutyCycle_t prime_mover_duty_cycle;
	struct uz_DutyCycle_t dut_duty_cycle;
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
	uz_pmsmModel_t* deskbench_dut_pmsm_model;
	uz_CurrentControl_t* deskbench_current_ctrl_prime_mover;
	uz_CurrentControl_t* deskbench_current_ctrl_dut;
	uz_SetPoint_t* deskbench_setpoint_ctrl_prime_mover;
	uz_SpeedControl_t* deskbench_speed_ctrl_prime_mover;
	uz_IIR_Filter_t* deskbench_speed_filter_prime_mover;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0_d1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0_d1;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1_d2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1_d2;
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
