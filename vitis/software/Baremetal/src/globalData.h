#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
#include "uz/uz_pmsm_control/uz_pmsm_control.h"
#include "IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"

enum control_mode {
	CIL,
	REAL
};

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float d3_input_loopback_uint32;
	float i_a_Beckhoff;
	float i_b_Beckhoff;
	float i_c_Beckhoff;
	float v_a_Beckhoff;
	float v_b_Beckhoff;
	float v_c_Beckhoff;
	float v_dc_Beckhoff;
	float i_dc_Beckhoff;
	float i_d_Beckhoff;
	float i_q_Beckhoff;
	float v_d_Beckhoff;
	float v_q_Beckhoff;
	float speed_n_rpm_Beckhoff;
	float theta_el_Beckhoff;
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
	uint32_t io_card_d1_state;
	uint32_t io_card_d2_state;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_A;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_B;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_C;
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
	float speed_n_ref_rpm_Beckhoff;
	float i_d_ref_A_Beckhoff_cil;
	float i_q_ref_A_Beckhoff_cil;
	enum control_mode control_mode_select;
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_wavegen_three_phase* three_phase_sine;
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_adcLtc2311_t* adc_ltc2311_a2;
	uz_adcLtc2311_t* adc_ltc2311_a3;
	uz_axi_gpio_t* axi_gpio_d1;
	uz_axi_gpio_t* axi_gpio_d2;
	uz_temperaturecard_t* temperature_card_d3;
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
	uz_pmsm_control_t* pmsm_control_Beckhoff_AM8071;
	uz_axi_gpio_t* dhg_reset_gpio;
	uz_axi_gpio_t* dhg_input_gpio;
	uz_pmsmModel_t* pmsm_cil_Beckhoff;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif

