/******************************************************************************
 * fcsmpc_n1.cpp
 *
 * Copyright (C) 2021 Institute EAL, TU München, All rights reserved.
 *
 *  Created on: 09.11.2021
 *      Author: Eyke Liegmann (EL)
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "controller_wrapper.h"

void fcsmpc_n1(
		float A_mat[Nx][Nx],
		float B_mat[Nx][Nin],
		float xkk[Nx],
		sw_pos_t ukk[Nopt], 
		float ykk[Nout],
		float lambda_u,
		sw_pos_t uopt[Nopt],
		bool matrices_updated
		)
{
	// Multiplying C*A*xkk
	float A_x[Nout];
	#pragma HLS ARRAY_PARTITION variable=A_x complete dim=1
	calc_Ax:for (uint3 i = 0; i < Nout; i++) // Nout due to C*A
	{
		#pragma HLS PIPELINE
		for (uint3 j = 0; j < Nx; j++)
		{
			if(j==0)
				A_x[i] =  A_mat[i][j] * xkk[j]; // reset value
			else
				A_x[i] += A_mat[i][j] * xkk[j];
		}
	}

	// pre-calculating Ax-i_ref, because
	// x_pred(k+1) = Ax(k) + Bu(k)
	// J = (x_pred - y_ref)^2 = (Ax + Bu - y_ref)^2 = ((Ax-yref) +Bu)^2
	float Ax_iref[Nout];
	#pragma HLS ARRAY_PARTITION variable=Ax_iref complete dim=1
	calc_Ax_iref:for (uint2 j = 0; j < Nout; j++){
		Ax_iref[j] = A_x[j] - ykk[j];
	}
	// all switch combinations, maybe naive :)
	sw_pos_t u_cand[Nsw_combs][Nin] = {
			{0,     0,     0},
			{0,     0,     1},
			{0,     1,     0},
			{0,     1,     1},
			{1,     0,     0},
			{1,     0,     1},
			{1,     1,     0},
			{1,     1,     1},
	};
	#pragma HLS ARRAY_PARTITION variable=u_cand complete dim=0


	// add loop over all switch positions!
	// performing B_mul_Pab*Uopt
	static float B_u[Nout][Nsw_combs] = {};
//	#pragma HLS ARRAY_PARTITION variable=B_u complete dim=0
	if(matrices_updated == true) {
		calc_Bu_Nsw:for (uint3 i = 0; i < Nout; i++){
			for (uint2 j = 0; j < Nin; j++){
				for (uint5 sw = 0; sw < Nsw_combs; sw++) {

						if(j==0) // reset value
						{
							if (u_cand[sw][j] ==	1){	// +1
								B_u[i][sw] =  B_mat[i][j];
							}
							else{
								B_u[i][sw] = 0;
							}
						}
						else
						{
							if (u_cand[sw][j] ==	1){	// +1
								B_u[i][sw] += B_mat[i][j];
							}
							//else{} adding 0 can be skipped
						}

				}
			}
	}
	}

	float cost_i[Nsw_combs];
	#pragma HLS ARRAY_PARTITION variable=cost_i complete dim=0
	float Ax_Bu_iref[Nout][Nsw_combs];
	#pragma HLS ARRAY_PARTITION variable=Ax_Bu_iref complete dim=0

	calc_cost_i:for (uint5 sw = 0; sw < Nsw_combs; sw++) {
#pragma HLS PIPELINE
		 Ax_Bu_iref[0][sw] = Ax_iref[0] + B_u[0][sw];
		 Ax_Bu_iref[1][sw] = Ax_iref[1] + B_u[1][sw];

		 cost_i[sw] = (Ax_Bu_iref[0][sw]*Ax_Bu_iref[0][sw]) + (Ax_Bu_iref[1][sw] * Ax_Bu_iref[1][sw]);

	}


	// pre-calculating multiples of lambda_u
    #define LAMBDA_VALUES_MAX 7 // Max_transitions * Nin + 1 = 2*3+1=7
	float static lambda_u_local[LAMBDA_VALUES_MAX] = {};
	#pragma HLS ARRAY_PARTITION variable=lambda_u_local complete dim=0
	if(lambda_u_local[1] != lambda_u){
		lambda_u_local[1] = lambda_u;
		calc_lambdau:for(uint4 i = 2; i< LAMBDA_VALUES_MAX; i++){
			lambda_u_local[i] = lambda_u*i;
		}
	}

	// calculating switching costs
	//uint5 u_delta[Nsw_combs];
	int u_delta[Nsw_combs];
	float cost_u[Nsw_combs];
	#pragma HLS ARRAY_PARTITION variable=u_delta complete dim=0
	#pragma HLS ARRAY_PARTITION variable=cost_u complete dim=0


	calc_cost_u:for(uint5 i = 0; i < Nsw_combs; i++){

		u_delta[i]  = abs(ukk[0] - u_cand[i][0]);
		u_delta[i] += abs(ukk[1] - u_cand[i][1]);
		u_delta[i] += abs(ukk[2] - u_cand[i][2]);
		cost_u[i]	= lambda_u_local[u_delta[i]] ;
	}

	float cost_total[Nsw_combs];
	float cost_min = 1e9; // arbitrary high number to compare against in the first step

	uint5 index_min = Nsw_combs;

	calc_cost_tot:for(uint5 sw = 0; sw < Nsw_combs; sw++) {
		cost_total[sw] = cost_u[sw] + cost_i[sw];
	}

	find_min:for (uint5 sw = 0; sw < Nsw_combs; sw++) {
		if (cost_total[sw] < cost_min) {
			cost_min = cost_total[sw];
			index_min = sw;
		}
	}

	assert(index_min < Nsw_combs);

	uopt[0] = u_cand[index_min][0];
	uopt[1] = u_cand[index_min][1];
	uopt[2] = u_cand[index_min][2];
}
