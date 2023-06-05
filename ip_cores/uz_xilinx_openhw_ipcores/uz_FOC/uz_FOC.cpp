#include "uz_FOC.h"
void uz_FOC(float actual_id, float actual_iq, float sampletime, bool reset_PL, float *ref_ud, float *ref_uq, float set_i_d, float set_i_q, float KP_d, float KI_d, float KP_q, float KI_q, bool reset_PS, float limit, float *out_KP_d, float *out_idref, bool *out_status, float *test_out_pl){
#pragma HLS INTERFACE mode=ap_none port=actual_id
#pragma HLS INTERFACE mode=ap_none port=actual_id
#pragma HLS INTERFACE mode=s_axilite port=sampletime
#pragma HLS INTERFACE mode=ap_none port=reset_PL
#pragma HLS INTERFACE mode=ap_none port=ref_ud
#pragma HLS INTERFACE mode=ap_none port=ref_uq
#pragma HLS INTERFACE mode=s_axilite port=set_i_d
#pragma HLS INTERFACE mode=s_axilite port=set_i_q
#pragma HLS INTERFACE mode=s_axilite port=KP_d
#pragma HLS INTERFACE mode=s_axilite port=KI_d
#pragma HLS INTERFACE mode=s_axilite port=KP_q
#pragma HLS INTERFACE mode=s_axilite port=KI_q
#pragma HLS INTERFACE mode=s_axilite port=reset_PS
#pragma HLS INTERFACE mode=s_axilite port=limit
#pragma HLS INTERFACE mode=s_axilite port=out_KP_d
#pragma HLS INTERFACE mode=s_axilite port=out_idref
#pragma HLS INTERFACE mode=s_axilite port=out_status
#pragma HLS INTERFACE mode=ap_none port=test_out_pl

//#pragma HLS DATAFLOW
	static float I_sum_d = 0.0f;
	static float I_sum_q = 0.0f;
	bool reset = reset_PL||reset_PS;
	bool status_d = uz_PI_Controller_sample_parallel(set_i_d, actual_id, sampletime, KP_d, KI_d, limit, reset, &I_sum_d, ref_ud);
	bool status_q = uz_PI_Controller_sample_parallel(set_i_q, actual_iq, sampletime, KP_q, KI_q, limit, reset, &I_sum_q, ref_uq);
	*out_KP_d = KP_d;
	*out_idref = set_i_d;
	*out_status = status_d||status_q;
	*test_out_pl = 1.0f + I_sum_q;
}



bool uz_PI_Controller_sample_parallel(float referenceValue, float actualValue, float sampletime, const float KI, const float KP, float limit, bool reset, float *I_sum, float *out){
	if(reset){
		*I_sum = 0.0f;
		*out = 0.0f;
		return true;
	}else{
		float error = referenceValue - actualValue;
		float P_sum = error * KP;
		float preIntegrator = error * KI;
		*out = *I_sum + P_sum;
		if(*out > limit)
			*out = limit;
		else if(*out < -1*limit){
			*out = -1*limit;
		}
		*I_sum += preIntegrator * sampletime;
		return false;
	}
}
