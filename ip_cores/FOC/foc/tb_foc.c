#include "uz_FOC.h"
#include <stdio.h>

//For floating point comparison
typedef union {
 float fval;
 unsigned int rawbits;
} float_union_t;

bool approx_eqf(float x, float y, int ulp_err_lim, float abs_err_lim)
    {
     float_union_t lx, ly;
     lx.fval = x;
     ly.fval = y;
     if (((x == 0.0f) ^ (y == 0.0f)) || (__signbit(x) != __signbit(y)))
     {
		#ifndef NDEBUG
		 if (x != y) { // (-0.0 == +0.0) so warning not printed for that case
			 printf("\nWARNING: Comparing floating point value against zero ");
			 printf("or values w/ differing signs. ");
			 printf("Absolute error limit has been used.\n");
		 }
		#endif
		 return fabs(x - y) <= fabs(abs_err_lim);
     }
     // Do ULP base comparison for all other cases
     return abs((int)lx.rawbits - (int)ly.rawbits) <= ulp_err_lim;
    }

int main()
{
	uz_FOC config = {0};
	struct uz_dq_t i_actual_Ampere = {0};
	struct uz_dq_t i_reference_Ampere = {0};
	struct uz_PMSM_t config_PMSM = {0};
	uz_PI_Controller_config config_id = {0};
	uz_PI_Controller_config config_iq = {0};

	config_id.Kp = 6.75f;
	config_id.Ki = 2000.0f;
	config_id.samplingTime_sec = 0.00001f;
	config_id.upper_limit = 10.0f;
	config_id.lower_limit = -10.0f;
	config_iq.Kp = 6.75f;
	config_iq.Ki = 2000.0f;
	config_iq.samplingTime_sec = 0.00001f;
	config_iq.upper_limit = 10.0f;
	config_iq.lower_limit = -10.0f;
	config.config_PMSM.Ld_Henry = 0.00027f;
	config.config_PMSM.Lq_Henry = 0.00027f;
	config.config_PMSM.Psi_PM_Vs = 0.0082f;
	config.decoupling_select = linear_decoupling;
	config.ext_clamping = false;
	config.I_rst = false;
	i_actual_Ampere.d = 0.0f;
	i_actual_Ampere.q = 0.0f;
	i_actual_Ampere.zero = 0.0f;
	i_reference_Ampere.d = 1.0f;
	i_reference_Ampere.q = 1.0f;
	i_reference_Ampere.zero = 0.0f;
	float omega_el_rad_per_sec = 0.0f;
	float V_dc_volts = 24.0f;
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
	float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};

	//Reference results
	float ud_out[11]={6.750000,5.089250,3.842018,2.901536,2.201211,1.674242,1.280621,0.980216,0.753020,0.585711,0.458180};
	float uq_out[11]={6.750000,5.089250,3.842168,2.902282,2.203474,1.686348,1.298281,1.013603,0.813535,0.672503,0.578441};
	printf("\n HW output\r");
	printf(" D-Parameter Q-Parameter\r");
	float out_d[11];
	float out_q[11];
	for(int i=0;i<11;i++){
		i_actual_Ampere.q = values_iq[i];
		i_actual_Ampere.d = values_id[i];
		omega_el_rad_per_sec = values_omega[i];
		uz_FOC_sample(&config, &config_id, &config_iq, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, &out_d[i], &out_q[i]);
		printf(" %f\t %f\r",out_d[i],out_q[i]);
	}


//comparison of sw and hw outputs*/
    bool test;
    printf("\n Comparison for D parameter \r");
	for(int j=0;j<11;j++){
		test = approx_eqf(ud_out[j], out_d[j], 10000, 1000);
		if(test){
			printf("Test passed D\r");
		}
		else{
			printf("Test failed D %f\r", ud_out[j]-out_d[j]);
		}
	}

    bool testt;
    printf("\n Comparison for Q parameter \r");
	for(int k=0;k<11;k++){
		testt = approx_eqf(uq_out[k], out_q[k], 10000, 1000);
		if(testt){
			printf("Test passed Q\r");
		}
		else{
			printf("Test failed Q %f\r", uq_out[k]-out_q[k]);
		}
	}
}



