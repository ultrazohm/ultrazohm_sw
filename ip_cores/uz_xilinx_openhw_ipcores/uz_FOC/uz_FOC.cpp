#include "uz_FOC.h"
void uz_FOC(
		// axi inputs
		float axi_id_reference, float axi_iq_reference, float axi_sampletime, float axi_id_KI, float axi_id_KP, float axi_iq_KI, float axi_iq_KP, float axi_limit, bool axi_reset,
		// hw input
		float id_actual, float iq_actual, bool reset_PL,
		// hw output
		float *ud_ref, float *uq_ref){
#pragma HLS INTERFACE mode=s_axilite port=axi_id_reference
#pragma HLS INTERFACE mode=s_axilite port=axi_iq_reference
#pragma HLS INTERFACE mode=s_axilite port=axi_sampletime
#pragma HLS INTERFACE mode=s_axilite port=axi_id_KI
#pragma HLS INTERFACE mode=s_axilite port=axi_id_KP
#pragma HLS INTERFACE mode=s_axilite port=axi_iq_KI
#pragma HLS INTERFACE mode=s_axilite port=axi_iq_KP
#pragma HLS INTERFACE mode=s_axilite port=axi_limit
#pragma HLS INTERFACE mode=s_axilite port=axi_reset
#pragma HLS INTERFACE mode=ap_none port=id_actual
#pragma HLS INTERFACE mode=ap_none port=iq_actual
#pragma HLS INTERFACE mode=ap_none port=reset_PL
#pragma HLS INTERFACE mode=ap_none port=ud_ref
#pragma HLS INTERFACE mode=ap_none port=uq_ref



	static float I_sum_d = 0.0f;
	static float I_sum_q = 0.0f;
	bool reset = reset_PL||axi_reset;
	*ud_ref = uz_PI_Controller_sample_parallel(axi_id_reference, id_actual, axi_sampletime, axi_id_KI, axi_id_KP, axi_limit, reset, &I_sum_d);
	*uq_ref = uz_PI_Controller_sample_parallel(axi_iq_reference, iq_actual, axi_sampletime, axi_iq_KI, axi_iq_KP, axi_limit, reset, &I_sum_q);
}


float uz_PI_Controller_sample_parallel(float referenceValue, float actualValue, float sampletime, const float KI, const float KP, float limit, bool reset, float *I_sum){
#pragma HLS PIPELINE II=1
	float error, P_sum, preIntegrator, preLimit, out;
	if(reset){
		*I_sum = 0.0f;
		out = 0.0f;
	}else{
		error = referenceValue - actualValue;
		P_sum = error * KP;
		preIntegrator = error * KI;
		*I_sum += preIntegrator * sampletime;
		preLimit = *I_sum + P_sum;
		out = limit_value(preLimit, limit);
	}
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
