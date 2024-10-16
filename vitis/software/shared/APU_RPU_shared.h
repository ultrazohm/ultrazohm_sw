//APU_RPU_shared.h
#pragma once
#include "stdbool.h"

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
	float dutycyc[6];
	float iterations;
	float dob_error_estimate[4];
};

struct RPU_to_APU_user_data_t
{
	// create variables that you want to share from R5 to A53
	float v_DC_pu;
	float theta_el_pos;
	float theta_el_neg;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ts_times_ZB_over_Lx;
	float Ts_times_ZB_over_Ly;
	float Rs_over_ZB;
	float Ld_over_LB;
	float Lq_over_LB;
	float Lx_over_LB;
	float Ly_over_LB;
	float psi_pm_over_psiB;
	float omega_el_pu;
	float i_d_pu;
	float i_q_pu;
	float i_x_pu;
	float i_y_pu;
	float i_d_ref_pu;
	float i_q_ref_pu;
	float i_x_ref_pu;
	float i_y_ref_pu;
	float lambda_dq;
	float lambda_xy;
	float solver_tolerance;
	float max_iter;
	bool HC_off_on;
	float psiPM_h_pu[2];
	float phiPM_h[2];
	bool kalman_off_on;
	float kalman_R;
	float kalman_Q1;
	float kalman_Q2;
	bool a53_ctrl_off_on;
};
