#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
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
	/* Project Wizard BEGIN: actualValues */
	float incremental_encoder_d1_1_theta_el;
	float incremental_encoder_d1_1_omega_mech;
	float incremental_encoder_d1_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d1_1_position;
	uint32_t incremental_encoder_d1_1_position_w_offset;
	uint32_t incremental_encoder_d1_1_index_found;
	float incremental_encoder_d1_2_theta_el;
	float incremental_encoder_d1_2_omega_mech;
	float incremental_encoder_d1_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d1_2_position;
	uint32_t incremental_encoder_d1_2_position_w_offset;
	uint32_t incremental_encoder_d1_2_index_found;
	float incremental_encoder_d1_3_theta_el;
	float incremental_encoder_d1_3_omega_mech;
	float incremental_encoder_d1_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d1_3_position;
	uint32_t incremental_encoder_d1_3_position_w_offset;
	uint32_t incremental_encoder_d1_3_index_found;
	float incremental_encoder_d2_1_theta_el;
	float incremental_encoder_d2_1_omega_mech;
	float incremental_encoder_d2_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d2_1_position;
	uint32_t incremental_encoder_d2_1_position_w_offset;
	uint32_t incremental_encoder_d2_1_index_found;
	float incremental_encoder_d2_2_theta_el;
	float incremental_encoder_d2_2_omega_mech;
	float incremental_encoder_d2_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d2_2_position;
	uint32_t incremental_encoder_d2_2_position_w_offset;
	uint32_t incremental_encoder_d2_2_index_found;
	float incremental_encoder_d2_3_theta_el;
	float incremental_encoder_d2_3_omega_mech;
	float incremental_encoder_d2_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d2_3_position;
	uint32_t incremental_encoder_d2_3_position_w_offset;
	uint32_t incremental_encoder_d2_3_index_found;
	float incremental_encoder_d3_1_theta_el;
	float incremental_encoder_d3_1_omega_mech;
	float incremental_encoder_d3_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d3_1_position;
	uint32_t incremental_encoder_d3_1_position_w_offset;
	uint32_t incremental_encoder_d3_1_index_found;
	float incremental_encoder_d3_2_theta_el;
	float incremental_encoder_d3_2_omega_mech;
	float incremental_encoder_d3_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d3_2_position;
	uint32_t incremental_encoder_d3_2_position_w_offset;
	uint32_t incremental_encoder_d3_2_index_found;
	float incremental_encoder_d3_3_theta_el;
	float incremental_encoder_d3_3_omega_mech;
	float incremental_encoder_d3_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d3_3_position;
	uint32_t incremental_encoder_d3_3_position_w_offset;
	uint32_t incremental_encoder_d3_3_index_found;
	float incremental_encoder_d4_1_theta_el;
	float incremental_encoder_d4_1_omega_mech;
	float incremental_encoder_d4_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d4_1_position;
	uint32_t incremental_encoder_d4_1_position_w_offset;
	uint32_t incremental_encoder_d4_1_index_found;
	float incremental_encoder_d4_2_theta_el;
	float incremental_encoder_d4_2_omega_mech;
	float incremental_encoder_d4_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d4_2_position;
	uint32_t incremental_encoder_d4_2_position_w_offset;
	uint32_t incremental_encoder_d4_2_index_found;
	float incremental_encoder_d4_3_theta_el;
	float incremental_encoder_d4_3_omega_mech;
	float incremental_encoder_d4_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d4_3_position;
	uint32_t incremental_encoder_d4_3_position_w_offset;
	uint32_t incremental_encoder_d4_3_index_found;
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
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_2;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_3;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_3;
	uz_wavegen_three_phase* three_phase_sine;
	uz_incrementalEncoder_t* incremental_encoder_d1_1;
	uz_incrementalEncoder_t* incremental_encoder_d1_2;
	uz_incrementalEncoder_t* incremental_encoder_d1_3;
	uz_incrementalEncoder_t* incremental_encoder_d2_1;
	uz_incrementalEncoder_t* incremental_encoder_d2_2;
	uz_incrementalEncoder_t* incremental_encoder_d2_3;
	uz_incrementalEncoder_t* incremental_encoder_d3_1;
	uz_incrementalEncoder_t* incremental_encoder_d3_2;
	uz_incrementalEncoder_t* incremental_encoder_d3_3;
	uz_incrementalEncoder_t* incremental_encoder_d4_1;
	uz_incrementalEncoder_t* incremental_encoder_d4_2;
	uz_incrementalEncoder_t* incremental_encoder_d4_3;
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

