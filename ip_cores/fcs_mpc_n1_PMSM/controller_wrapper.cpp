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
	// AXI LITE Interface
	#pragma HLS disaggregate variable=plant
	#pragma HLS INTERFACE mode=s_axilite 	port=plant 				bundle=data
	#pragma HLS INTERFACE mode=s_axilite 	port=U_OPT_out	 		bundle=data
	#pragma HLS INTERFACE mode=s_axilite 	port=lambda_in 			bundle=data
	#pragma HLS INTERFACE mode=s_axilite 	port=status_register 	bundle=data
	#pragma HLS INTERFACE mode=s_axilite	port=copy_mats_flag 	bundle=data
	#pragma HLS INTERFACE mode=s_axilite 	port=return 			bundle=data


	// AXI STREAM Interfaces
	DO_PRAGMA(HLS INTERFACE axis register depth= Nref	port = Y_REF_KK_src)
	DO_PRAGMA(HLS INTERFACE axis register depth= Nx		port = X_KK_src )

	// direct in/outputs
	#pragma HLS interface ap_none register port=counter_in
	#pragma HLS interface ap_none register port=counter_out
	#pragma HLS interface ap_none register port=Uopt_out
	#pragma HLS interface ap_none  port=copy_flag_out
	#pragma HLS interface ap_none  port=mpc_done
	#pragma HLS interface ap_none  port=matrices_updated_out


	float X_KK[Nx];
	#pragma HLS ARRAY_PARTITION variable=X_KK complete dim=1
	
	float Y_KK[Nref];
	#pragma HLS ARRAY_PARTITION variable=Y_KK complete dim=1

	sw_pos_t U_KK_a[3*Nh];
	#pragma HLS ARRAY_PARTITION variable=U_KK_a complete dim=1

	static float lambda_ip = 0.0f;

	sw_pos_t static U_opt[3 * Nh] = { 0,	1,	0}; // initalize previous switch position

	#pragma HLS ARRAY_PARTITION variable=U_opt		complete dim=1

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
#pragma HLS ARRAY_PARTITION variable=A_mat		complete dim=0
#pragma HLS ARRAY_PARTITION variable=B_mat		complete dim=0

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



