#include <stdio.h>
#include <math.h>
#include "controller_wrapper.h"

int main()
{
	plant_mats_t plant;

	float A_mat[Nx][Nx] = {
		{ 0.999411495568444  , 0.000001008309604  , 0.000224902693822  , 0.029430909213924 },
		{-0.000001008309604 ,  0.999411495568444 ,-0.029430909213924 ,  0.000224902693822} ,
		{ 0.000068504287262  ,-0.000000269019142  , 0.999939993871078  ,-0.007852663283863 },
		{ 0.000000269019142  , 0.000068504287262  , 0.007852663283863  , 0.999939993871078 }
	};
	float B_mat[Nx][Nin] = {
		 {  0.019823704746307 , -0.009911846600685 , -0.009911858145621 },
		 { -0.000000006665472 ,  0.017167835240160 , -0.017167828574688 },
		 {  0.000000679277695 , -0.000000341178911 , -0.000000338098783 },
		 {  0.000000001778313 ,  0.000000587382583 , -0.000000589160896 }
	};

	memcpy(plant.A_mat, A_mat, sizeof(A_mat));
	memcpy(plant.B_mat, B_mat, sizeof(B_mat));

	uint3 ukk_in = 0b101; 
	uint16 counter_in = 1;
	uint16 counter_out;
	uint1 copy_mats_flag = 1;

	float x_kk_in[Nx] = {
		   0.085766447463464,
		   0.993174932432677,
		   0.873615075308303,
		   0.269932537956247
	};

	float Y_REF_KK_src[Nout] = {
			   0.090063875432491,   
			   1.001364858063869
	};

	int U_opt_golden[3] = {0, 1, 0};
	int U_opt_golden2[3] = { 0, 1, 0 };

	int U_OPT_out[3] = { 3,3,3 };

	float lambda_in = 1e-3;
	int status_register = 0;

	uint3 Uopt_out = 0;
	bool copy_flag_out = 0;
	bool matrices_updated = 0;
	volatile bool mpc_done = 0;

	ctrl_wrapper(x_kk_in, Y_REF_KK_src,
		U_OPT_out,
		&copy_mats_flag,
		&plant,
		&lambda_in, &status_register,
		// ap_none outputs below
		&counter_in, &counter_out,
		&Uopt_out, &copy_flag_out,
		&mpc_done, &matrices_updated
	);

	float const epsilon = 1e-5;
	int mismatches = 0;
	// check optimal solution
	for (int row = 0; row < 3; row++)
	{
		if (U_OPT_out[row] != U_opt_golden[row])
		{
			bool result_correct = false;
			mismatches++;
			printf("U_opt incorrect at %i \n", row + 1);
		}
	}

	printf("ukk= %i %i %i\n", U_OPT_out[0], U_OPT_out[1], U_OPT_out[2]);
	if(mismatches==0)
		printf("HW/SW match\n");
	else
		printf("HW/SW %i mismatches\n", mismatches);

	copy_mats_flag = 0;

	// call second time for timing analysis
	ctrl_wrapper(x_kk_in, Y_REF_KK_src,
		U_OPT_out,
		&copy_mats_flag,
		&plant,
		&lambda_in, &status_register,
		// ap_none outputs below
		&counter_in, &counter_out,
		&Uopt_out, &copy_flag_out,
		&mpc_done, &matrices_updated
	);

	// check optimal solution
	for (int row = 0; row < 3; row++)
	{
		if (U_OPT_out[row] != U_opt_golden2[row])
		{
			bool result_correct = false;
			mismatches++;
			printf("U_opt incorrect at %i \n", row + 1);
		}
	}

	printf("ukk= %i %i %i\n", U_OPT_out[0], U_OPT_out[1], U_OPT_out[2]);
	if(mismatches==0)
		printf("HW/SW match\n");
	else
		printf("HW/SW %i mismatches\n", mismatches);

	return (mismatches);
}
