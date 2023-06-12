#include "uz_PI_controller.h"
float uz_PI_controller(
		// axi inputs
		float axi_referenceValue, float axi_sampletime, float axi_KI, float axi_KP, float axi_limit, bool axi_reset,
		// hw input
		float actualValue,
		// hw debug output
		float *d_I_sum, float *d_error, float *d_P_sum, float *d_preIntegrator, float *d_KI, float *d_KP, float *d_limit, float *d_preLimit
		){
#pragma HLS INTERFACE mode=s_axilite port=axi_referenceValue
#pragma HLS INTERFACE mode=s_axilite port=axi_sampletime
#pragma HLS INTERFACE mode=s_axilite port=axi_KI
#pragma HLS INTERFACE mode=s_axilite port=axi_KP
#pragma HLS INTERFACE mode=s_axilite port=axi_limit
#pragma HLS INTERFACE mode=s_axilite port=axi_reset
#pragma HLS INTERFACE mode=ap_none port=actualValue
#pragma HLS INTERFACE mode=ap_none port=return

#pragma HLS INTERFACE mode=ap_none port=d_I_sum
#pragma HLS INTERFACE mode=ap_none port=d_error
#pragma HLS INTERFACE mode=ap_none port=d_P_sum
#pragma HLS INTERFACE mode=ap_none port=d_preIntegrator
#pragma HLS INTERFACE mode=ap_none port=d_KI
#pragma HLS INTERFACE mode=ap_none port=d_KP
#pragma HLS INTERFACE mode=ap_none port=d_limit
#pragma HLS INTERFACE mode=ap_none port=d_preLimit


	static float I_sum;
	float error, P_sum, preIntegrator, preLimit;
	float out;
	if(axi_reset){
		I_sum = 0.0f;
		//out = 0.0f;
	}else{
		error = axi_referenceValue - actualValue;
		P_sum = error * axi_KP;
		preIntegrator = error * axi_KI;
		I_sum += preIntegrator * axi_sampletime;
		preLimit = I_sum+P_sum;
		out = limit_value(preLimit, axi_limit);
	}
	*d_I_sum = I_sum;
	*d_error = error;
	*d_P_sum = P_sum;
	*d_preIntegrator = preIntegrator;
	*d_KI = axi_KI;
	*d_KP = axi_KP;
	*d_limit = axi_limit;
	*d_preLimit = preLimit;


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

