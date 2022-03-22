#include "uz_piController.h"
#include "uz_signals.h"
#include <stdio.h>
int main()
{
	uz_PI_Controller_config config = {0};
	config.Kp = 10.0f;
	config.Ki = 10.0f;
	config.samplingTime_sec = 0.001f;
	config.upper_limit = 10.0f;
	config.lower_limit = -10.0f;
    float referenceValue[13] = {2.54f, 5.0f, -1.45f, -1.23f, 5.54f, 10.32f, -9.45f, -15.23f, 2.0f, 1.0f, 12.0f, 12.0f, 2.0f};
    float actualValue[13]    = {1.62f, 6.5f, -3.25f, 2.54f, 1.62f, 6.5f, -3.25f, 2.54f, 1.0f, 2.0f, 2.0f, 12.1f, 12.0f};
    float out[13];
    printf("\n HW output\r");
    for(int j=0;j<13;j++){
        uz_PI_Controller_sample(&config,false, referenceValue[j], actualValue[j], false, &out[j]);
        printf("result %f\r",out[j]);
    }

	uz_PI_Controller_config self;
	self.Kp = 10.0f;
	self.Ki = 10.0f;
	self.samplingTime_sec = 0.001f;
	self.upper_limit = 10.0f;
	self.lower_limit = -10.0f;
	bool ext_clamping = false;
	bool internal_clamping = false;
	float I_sum;
	float output[13];
	printf("\n SW output\r");
	for(int i=0;i<13;i++){
	float error = referenceValue[i] - actualValue[i];
	float old_I_sum = I_sum;
	float preIntegrator = error * self.Ki;
	float P_sum = error * self.Kp;
	float output_before_saturation = old_I_sum + P_sum;
	float value_after_deadzone;
		if ( (output_before_saturation >= self.lower_limit) && (output_before_saturation <= self.upper_limit) ) {
			value_after_deadzone = 0.0f;
		} else if (output_before_saturation > self.upper_limit) {
			value_after_deadzone = output_before_saturation - self.upper_limit;
		} else {
			value_after_deadzone = output_before_saturation - self.lower_limit;
		}

	float sign_after_deadzone;
		if (value_after_deadzone < 0.0f){
			sign_after_deadzone = -1.0f;
		}
		else if (value_after_deadzone > 0.0f) {
			sign_after_deadzone = 1.0f;
		} else {
			sign_after_deadzone = 0.0f;
		}

	float sign_preIntegrator;
		if (preIntegrator < 0.0f){
			sign_preIntegrator = -1.0f;
		}
		else if (preIntegrator > 0.0f) {
			sign_preIntegrator = 1.0f;
		} else {
			sign_preIntegrator = 0.0f;
		}
	if ( (0.0f != value_after_deadzone) && (sign_after_deadzone == sign_preIntegrator) ) {
		internal_clamping = true;
	} else {
		internal_clamping = false;
	}

	bool clamping_active  = (ext_clamping == true) || (internal_clamping == true); // clamping is active if internal clamping or external clamping is true
	if ( clamping_active ) {
		I_sum += 0.0f;
	} else {
		I_sum += preIntegrator * self.samplingTime_sec;
	}


	if (output_before_saturation > self.upper_limit) {
			output[i] = self.upper_limit;
		} else if (output_before_saturation < self.lower_limit) {
			output[i] = self.lower_limit;
		} else{
			output[i] =output_before_saturation;
		}
	if(I_rst){
		I_sum = 0.0f;
		internal_clamping = false;
	}
	printf("result %f\r",output[i]);
	}

	for(int k=0;k<13;k++){

		if(out[k] == output[k]){
			printf("Test passed\r");
		}
		else{
			printf("Test failed\r");
		}
	}

}



