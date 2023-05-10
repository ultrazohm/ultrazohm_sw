/******************************************************************************
 *
 * controller_wrapper.h
 *
 * Copyright (C) 2020 Institute EAL, TU M�nchen, All rights reserved.
 *
 *  Created on: 12.05.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "ap_fixed.h"
#include <algorithm>
#include "pred_controller_hw.h"
#include <assert.h>

#ifdef VITIS
	#include "hls_math.h"
#else
	#include <math.h>
#endif

using namespace std;

// Sign of variable x
#define SIGN(x) (((x)>=0) ? (1) : (-1)) 
//Max of x or y
#define MAX(x, y) (((x) < (y)) ? (y) : (x)) 
// Min of x or y
#define MIN(x, y) (((x) > (y)) ? (y) : (x)) 
// limiting the variable x between high and low
#define LIMIT(x,low,high) ((x) >(high)?(high):((x) < (low) ? (low) : (x)))

#ifndef Pred_controller_H_
#define Pred_controller_H_

#define myFixed_LENGTH		32
#define myFixed_INT_BITS	3 // up to 8.xxxx
#define myFxLng_LENGTH		37
#define myFxLng_INT_BITS	8 // 256.xxxx 
//typedef ap_fixed<32, 1, AP_TRN, AP_WRAP> myFixed;
//typedef float myFixed;
//typedef ap_fixed<myFixed_LENGTH, myFixed_INT_BITS, AP_RND_CONV, AP_SAT> myFixed;
//typedef ap_fixed<myFixed_LENGTH, myFixed_INT_BITS, AP_TRN, AP_WRAP> myFixed;
typedef ap_fixed<myFixed_LENGTH, myFixed_INT_BITS> myFixed;
typedef ap_fixed<myFxLng_LENGTH, myFxLng_INT_BITS> myFxLng;


typedef ap_int<3> int3;	 
typedef ap_uint<1> uint1;
typedef ap_uint<2> uint2;
typedef ap_uint<3> uint3;
typedef ap_uint<4> uint4;
typedef ap_uint<5> uint5;
typedef ap_uint<6> uint6;

typedef unsigned char uint8;
typedef unsigned int uint32; 
typedef unsigned short uint16;



// define type for switch position here
// e.g. 1bit sufficient for 2 level inverter, but 3 level inverter needs 2bits to represent the three possible switch positions
typedef ap_uint<1> sw_pos_t; 
struct sw_seq_t {
	sw_pos_t a;
	sw_pos_t b;
	sw_pos_t c;
};

struct plant_mats_t{
	float A_mat[Nx][Nx];
	float B_mat[Nx][Nin];
};

void ctrl_wrapper(float X_KK_src[Nx], float Y_REF_KK_src[Nref],
	int U_OPT_out[Nopt], uint1 *copy_mats_flag,
	plant_mats_t *plant,
	float *lambda_in, int *status_register,
	// ap_none outputs below
	uint16 *counter_in, uint16 *counter_out,
	uint3 *Uopt_out, volatile bool *copy_flag_out,
	volatile bool *mpc_done, volatile bool *matrices_updated_out
);

void fcsmpc_n1(
		float A_mat[Nx][Nx],
		float B_mat[Nx][Nin],
		float xkk[Nx],
		sw_pos_t ukk[Nopt],
		float ykk[Nout],
		float lambda_u,
		sw_pos_t uopt[Nopt],
		bool matrices_updated
	);

#endif
