//APU_RPU_shared.h
#pragma once
// OCM Bank Adresses
// See UG1085 v2.4 table 18-1 OCM Mapping Summary (https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm)
#define MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU 	0xFFFD0000 // bank 1 is for r5->a53 user data
#define MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU 	0xFFFE0000 // bank 2 is for a53->r5 user data
#define MEM_SHARED_START_OCM_BANK_3_JAVASCOPE 	0xFFFF0000 // bank 3 is for r5->a53 javascope
#define JS_CHANNELS 		20
// update by hand when changing JS_CHANNELS
// Bank 3 of OCM has 64 KB, thus a maximum of 16K float values can be stored
#define JAVASCOPE_DATA_SIZE_2POW  	128

// Experimental feature - read docs before use
#define USE_A53_AS_ACCELERATOR_FOR_R5_ISR		TRUE

#include <stdbool.h>
struct javascope_data_t
{
	uint32_t    status;
	float	    slowDataContent;
	uint32_t    slowDataID;
	float       scope_ch[JS_CHANNELS];
};

struct APU_to_RPU_t
{
	uint32_t id;
	float value;
};

struct APU_to_RPU_user_data_t
{
	// create variables that you want to share from A53 to R5
	uint32_t slowDataCounter;
	float DutyCycle_A1;
	float DutyCycle_B1;
	float DutyCycle_C1;
	float DutyCycle_A2;
	float DutyCycle_B2;
	float DutyCycle_C2;
	float v_dqxy_limited_volts_d;
	float v_dqxy_limited_volts_q;
	float v_dqxy_limited_volts_x;
	float v_dqxy_limited_volts_y;
};

struct RPU_to_APU_user_data_t
{
	// create variables that you want to share from R5 to A53
	uint32_t slowDataCounter;
	bool control_state_active;
	bool select_CIL;
	bool select_CurrentControl;
	bool select_DDPG_1_64;
	bool select_Real;
	float omega_elec;
	float mechanicalRotorSpeed;
	float v_dc1;
	float theta_elec;
	float i_dq_reference_d;
	float i_dq_reference_q;
	float i_xy_reference_x;
	float i_xy_reference_y;
	float CIL_i_dq_meas_d;
	float CIL_i_dq_meas_q;
	float CIL_i_xy_meas_x;
	float CIL_i_xy_meas_y;
	float REAL_i_dq_meas_d;
	float REAL_i_dq_meas_q;
	float REAL_i_xy_meas_x;
	float REAL_i_xy_meas_y;
};
