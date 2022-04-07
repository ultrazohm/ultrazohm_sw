#include "uz_piController.h"
#include "uz_signals.h"
#include <stdio.h>
int main()
{
//config parameters
	uz_PI_Controller_config config = {0};
	/*	//setup parameters
   //12,12.10 test if clamping was active during limitation
	//1,2- testwith negative error
	config.Kp = 10.0f;
	config.Ki = 10.0f;
	config.samplingTime_sec = 0.001f;
	config.upper_limit = 10.0f;
	config.lower_limit = -10.0f;
	//Tests if proportional part of the controller outputs the expected values
	//everything passed
	config.Ki = 0.0f;
	config.Kp = 11.54f;
	config.upper_limit = 100.0f;
	config.lower_limit = -100.0f;
	config.samplingTime_sec = 0.001f;
	//Tests if the output limitation of the controller functions as expected
	//everything passed           -- working properly
	config.upper_limit = 10.0f;
	config.lower_limit = -10.0f;
	config.Ki = 0.0f;
	config.Kp = 11.54f;
	config.samplingTime_sec = 0.001f;
	//Tests if the integrator of the controller outputs the expected values.
	//everything failed- Hw op is all zero   - working properliy
	config.Ki = 1.0f;
	config.Kp = 0.0f;
	config.upper_limit = 100.0f;
	config.lower_limit = -100.0f;
	config.samplingTime_sec = 1.0f;
	//Test the limitation&clamping for I-part
	//Hw output is zero for everythig
	config.upper_limit = 5.0f;
	config.lower_limit = -5.0f;
	config.Ki = 1.0f;
	config.Kp = 0.0f;
	config.samplingTime_sec = 1.0f;
	//normal operating parameters
	//2,6,7,9 failed
	config.Ki = 1.0f;
	config.Kp = 11.54f;
	config.upper_limit = 20.0f;
	config.lower_limit = -20.0f;
	config.samplingTime_sec = 1.0f;*/
	//Tests if the external clamping signal stops the integrator from rising
	config.samplingTime_sec = 1.0f;
	config.Ki = 1.0f;
	config.Kp = 1.154f;
	config.upper_limit = 20.0f;
	config.lower_limit = -20.0f;

    float referenceValue[13] = {2.54f, 5.0f, -1.45f, -1.23f, 5.54f, 10.32f, -9.45f, -15.23f, 2.0f, 1.0f, 12.0f, 12.0f, 2.0f};
    float actualValue[13]    = {1.62f, 6.5f, -3.25f, 2.54f, 1.62f, 6.5f, -3.25f, 2.54f, 1.0f, 2.0f, 2.0f, 12.1f, 12.0f};

//Hardware part
    float out[13];
    printf("\n HW output\r");
    for(int j=0;j<13;j++){
        uz_PI_Controller_sample(&config,false, referenceValue[j], actualValue[j], false, &out[j]);
        printf(" %f\r",out[j]);
    }

//Software part
	bool ext_clamping = false;
	bool internal_clamping = false;
	float I_sum;
	float output[13];
	printf("\n SW output\r");
	for(int i=0;i<13;i++){
	float error = referenceValue[i] - actualValue[i];
	float old_I_sum = I_sum;
	float preIntegrator = error * config.Ki;
	float P_sum = error * config.Kp;
	float output_before_saturation = old_I_sum + P_sum;
//uz_signals_dead_zone
	float value_after_deadzone;
	if ( (output_before_saturation >= config.lower_limit) && (output_before_saturation <= config.upper_limit) ) {
		value_after_deadzone = 0.0f;
	} else if (output_before_saturation > config.upper_limit) {
		value_after_deadzone = output_before_saturation - config.upper_limit;
	} else {
		value_after_deadzone = output_before_saturation - config.lower_limit;
	}
//uz_signals_get_sign_of_value
	float sign_after_deadzone;
	if (value_after_deadzone < 0.0f){
		sign_after_deadzone = -1.0f;
	}
	else if (value_after_deadzone > 0.0f) {
		sign_after_deadzone = 1.0f;
	} else {
		sign_after_deadzone = 0.0f;
	}
//uz_signals_get_sign_of_value
	float sign_preIntegrator;
	if (preIntegrator < 0.0f){
		sign_preIntegrator = -1.0f;
	}
	else if (preIntegrator > 0.0f) {
		sign_preIntegrator = 1.0f;
	} else {
		sign_preIntegrator = 0.0f;
	}
//uz_PI_Controller_Clamping_Circuit
	if ( (0.0f != value_after_deadzone) && (sign_after_deadzone == sign_preIntegrator) ) {
		internal_clamping = true;
	} else {
		internal_clamping = false;
	}
	bool clamping_active  = (ext_clamping == true) || (internal_clamping == true); // clamping is active if internal clamping or external clamping is true
	if ( clamping_active ) {
		I_sum += 0.0f;
	} else {
		I_sum += preIntegrator * config.samplingTime_sec;
	}
//uz_signals_saturation
	if (output_before_saturation > config.upper_limit) {
		output[i] = config.upper_limit;
	} else if (output_before_saturation < config.lower_limit) {
		output[i] = config.lower_limit;
	} else{
		output[i] =output_before_saturation;
	}
	if(I_rst){
		I_sum = 0.0f;
		internal_clamping = false;
	}
	printf("result %f\r",output[i]);
	}
//comparison of sw and hw outputs
	for(int k=0;k<13;k++){
		if(out[k] == output[k]){
			printf("Test passed\r");
		}
		else{
			printf("Test failed %f\r", out[k]-output[k]);
		}

	}

}



