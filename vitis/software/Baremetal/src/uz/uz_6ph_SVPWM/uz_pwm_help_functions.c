#include "uz_pwm_help_functions.h"
#include "../uz_math_constants.h"


struct uz_DutyCycle_t uz_add_zerosequence_and_saturate_3ph(uz_3ph_abc_t u_abc_ref, float u_n, float V_dc_volts){
	struct uz_DutyCycle_t output = {0};
	// adding zero sequence
	output.DutyCycle_A = (u_abc_ref.a + u_n) / V_dc_volts + 0.5f;
	output.DutyCycle_B = (u_abc_ref.b + u_n) / V_dc_volts + 0.5f;
	output.DutyCycle_C = (u_abc_ref.c + u_n) / V_dc_volts + 0.5f;

	// saturation
	output.DutyCycle_A = uz_signals_saturation(output.DutyCycle_A, 1.0f, 0.0f);
	output.DutyCycle_B = uz_signals_saturation(output.DutyCycle_B, 1.0f, 0.0f);
	output.DutyCycle_C = uz_signals_saturation(output.DutyCycle_C, 1.0f, 0.0f);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_add_zerosequence_and_saturate_6ph(uz_6ph_abc_t u_abc1abc2_ref, float u_n1, float u_n2, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};
	// adding zero sequence

	uz_3ph_abc_t u_abc_ref1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	uz_3ph_abc_t u_abc_ref2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_add_zerosequence_and_saturate_3ph(u_abc_ref1, u_n1, V_dc_volts);
	output.system2 = uz_add_zerosequence_and_saturate_3ph(u_abc_ref2, u_n2, V_dc_volts);

	return output;
}



int getSector24(float theta){

	theta = uz_bring_angle_between_0_2_pi(theta);

	int sector_24 = floor( theta/(M_PI/12.0f) - fmod(theta, M_PI/12.0f) ) + 1;
	if(sector_24 > 24){
		sector_24 = 1;
	}
	return sector_24;
}



int getSector12(float theta){

	theta = uz_bring_angle_between_0_2_pi(theta);

	int sector_12 = floor( theta/(M_PI/6.0f) - fmod(theta, M_PI/6.0f) ) + 1;
	if(sector_12 > 12){
		sector_12 = 1;
	}
	return sector_12;
}


float uz_bring_angle_between_0_2_pi(float theta_rad){
	while(theta_rad < 0.0f){
		theta_rad = theta_rad + 2.0f*M_PI;
	}
	theta_rad = fmod(theta_rad, 2.0f*M_PI);

	return theta_rad;
}

float uz_get_angle_3ph_alphabeta_reference(uz_3ph_alphabeta_t u_alphabeta_ref){
	return fmod(  atan2f(u_alphabeta_ref.beta, u_alphabeta_ref.alpha)+2.0f*M_PI, 2.0f*M_PI);
}

