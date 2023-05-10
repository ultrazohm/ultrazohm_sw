/******************************************************************************
 *
 * controller_wrapper.cpp
 *
 * Copyright (C) 2020 Institute EAL, TU M�nchen, All rights reserved.
 *
 *  Created on: 12.05.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "controller_wrapper.h"

void ctrl_wrapper(	float X_KK_src[Nx],		float Y_REF_KK_src[Nref],
				int U_OPT_out[Nopt],		uint1 *copy_mats_flag,
				plant_mats_t *plant,
				float *lambda_in,		int *status_register,
	// ap_none outputs below
				uint16 *counter_in, uint16 *counter_out,
				uint3 *Uopt_out, volatile bool *copy_flag_out,
				volatile bool *mpc_done, volatile bool *matrices_updated_out
)
{
	//AXI LITE Interface
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=plant
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=U_OPT_out
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=lambda_in
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=status_register
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=copy_mats_flag
	#pragma HLS INTERFACE mode=s_axilite bundle=data port=return

	// AXI STREAM Interfaces
	#pragma HLS INTERFACE mode=axis depth=Nref port=Y_REF_KK_src register
	#pragma HLS INTERFACE mode=axis depth=Nx port=X_KK_src register

	// direct in/outputs
	#pragma HLS INTERFACE mode=ap_none port=counter_in register
	#pragma HLS INTERFACE mode=ap_none port=counter_out register
	#pragma HLS INTERFACE mode=ap_none port=Uopt_out register
	#pragma HLS INTERFACE mode=ap_none port=copy_flag_out
	#pragma HLS INTERFACE mode=ap_none port=mpc_done
	#pragma HLS INTERFACE mode=ap_none port=matrices_updated_out


	float X_KK[Nx];
	#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=X_KK
	
	float Y_KK[Nref];
	#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Y_KK

	sw_pos_t U_KK_a[3*Nh];
	#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=U_KK_a

	static float lambda_ip = 0.0f;

	sw_pos_t static U_opt[3 * Nh] = { 0,	1,	0}; // initalize previous switch position

	#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=U_opt

	x_kk_cpy:for(uint2 row=0;row<Nx;row++){
	#pragma HLS PIPELINE
		X_KK[row] = X_KK_src[row];
	}
	
	y_ref_kk_cpy:for(uint2 row=0;row<Nref;row++){
	#pragma HLS PIPELINE
		Y_KK[row] = Y_REF_KK_src[row];
	 }
	
	u_kk_cpy:for(uint2 row=0;row<3*Nh;row++){
		#pragma HLS PIPELINE
		U_KK_a[row] = U_opt[row]; // via static variable U_opt
	}

	static float A_mat[Nx][Nx];
	static float B_mat[Nx][Nin];
	#pragma HLS ARRAY_PARTITION dim=0 type=complete variable=A_mat
	#pragma HLS ARRAY_PARTITION dim=0 type=complete variable=B_mat

	bool matrices_updated = false;
	*matrices_updated_out = false;

	lambda_ip = *lambda_in;

	if (*copy_mats_flag == 1)
	{
		*copy_flag_out = true;

		copy_Amat:for (uint3 i = 0; i < Nx; i++)
		{
			for (uint3 j = 0; j < Nx; j++)
			{
				A_mat[i][j] = plant->A_mat[i][j];
			}
		}

		copy_Bmat:for (uint3 i = 0; i < Nx; i++)
		{
			for (uint2 j = 0; j < Nin; j++)
			{
				B_mat[i][j] = plant->B_mat[i][j];
			}
		}

		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	}
	else
	{
		*copy_flag_out = false;
	}
	
	//*copy_mats_flag = 0; // unfortunately reading and writing through s_axilite on the same variable is not possible


	// call FCS-MPC algorithm here
	fcsmpc_n1(A_mat, B_mat, X_KK, U_KK_a, Y_KK, lambda_ip, U_opt, matrices_updated);

	// switch position - index value expected on the output of this module
	//		 0				0b0
	//		+1				0b1
	*Uopt_out = uint3(U_opt[0]) | ((uint3(U_opt[1])) << 1) | ((uint3(U_opt[2])) << 2);

	*mpc_done = true;

	// copy optimal solution to AXI
	Copy_U_opt_axi:for (uint2 jj = 0; jj < Nopt; jj++)
	{
		#pragma HLS PIPELINE
		U_OPT_out[jj] = ((int)U_opt[jj]);
	}

	*counter_out = *counter_in;
	*mpc_done = false; // reset done flag
		
}



