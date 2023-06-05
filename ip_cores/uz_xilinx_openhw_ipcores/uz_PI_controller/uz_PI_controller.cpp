#include "uz_PI_controller.h"
float uz_PI_controller(float referenceValue, float actualValue, float sampletime, float KI, float KP, float limit, bool reset, float *axi_referenceValue, float *axi_actualValue, float *error, float *P_sum){
#pragma HLS INTERFACE mode=s_axilite port=referenceValue
#pragma HLS INTERFACE mode=ap_none port=actualValue
#pragma HLS INTERFACE mode=s_axilite port=sampletime
#pragma HLS INTERFACE mode=s_axilite port=KI
#pragma HLS INTERFACE mode=s_axilite port=KP
#pragma HLS INTERFACE mode=s_axilite port=limit
#pragma HLS INTERFACE mode=s_axilite port=reset
#pragma HLS INTERFACE mode=s_axilite port=axi_referenceValue
#pragma HLS INTERFACE mode=s_axilite port=axi_actualValue
#pragma HLS INTERFACE mode=s_axilite port=error
#pragma HLS INTERFACE mode=s_axilite port=P_sum
#pragma HLS INTERFACE mode=ap_none port=return

	static float I_sum;
	float out;
	if(reset){
		I_sum = 0.0f;
		out = 0.0f;
	}else{
		*error = referenceValue - actualValue;
		*P_sum = *error * KP;
		float preIntegrator = *error * KI;
		out = limit_value(I_sum+*P_sum, limit);
		I_sum += preIntegrator * sampletime;
	}
*axi_referenceValue = referenceValue;
*axi_actualValue = actualValue;
	return out;
}

float limit_value(float value, float limit){
	if(value > limit)
		value = limit;
	else if(value < -1*limit){
		value = -1*limit;
	}
	return value;
}

