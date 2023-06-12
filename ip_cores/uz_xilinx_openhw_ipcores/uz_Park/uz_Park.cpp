#include "uz_Park.h"

void uz_Park(float in_trafo_alpha, float in_trafo_beta, float in_inv_d, float in_inv_q, float theta_el, float *out_trafo_d, float *out_trafo_q, float *out_inv_alpha, float *out_inv_beta){
#pragma HLS INTERFACE mode=ap_none port=in_trafo_alpha
#pragma HLS INTERFACE mode=ap_none port=in_trafo_beta
#pragma HLS INTERFACE mode=ap_none port=in_inv_d
#pragma HLS INTERFACE mode=ap_none port=in_inv_q
#pragma HLS INTERFACE mode=ap_none port=theta_el
#pragma HLS INTERFACE mode=ap_none port=out_trafo_d
#pragma HLS INTERFACE mode=ap_none port=out_trafo_q
#pragma HLS INTERFACE mode=ap_none port=out_inv_alpha
#pragma HLS INTERFACE mode=ap_none port=out_inv_beta
	float sin_theta = sinf(theta_el);
	float cos_theta = cosf(theta_el);
	float in_alphabeta[2] = {in_trafo_alpha, in_trafo_beta};
	float in_dq[2] = {in_inv_d, in_inv_q};
	uz_matrix_multiply(in_alphabeta[0], in_alphabeta[1], cos_theta, sin_theta, out_trafo_d);
	uz_matrix_multiply(in_alphabeta[0], in_alphabeta[1], -1*sin_theta, cos_theta, out_trafo_q);
	uz_matrix_multiply(in_dq[0], in_dq[1], cos_theta, -1*sin_theta, out_inv_alpha);
	uz_matrix_multiply(in_dq[0], in_dq[1], sin_theta, cos_theta, out_inv_beta);
}

void uz_matrix_multiply(float x1, float x2, float y1, float y2, float *out){
#pragma HLS INLINE
	float products[2];
	double_multiply(x1, x2, y1, y2, products);
    *out = products[0] + products[1];
}

void double_multiply(float x1, float x2, float y1, float y2, float products[2]){
#pragma HLS INLINE
	multiply(x1, y1, &products[0]);
	multiply(x2, y2, &products[1]);
}

void multiply(float arg1, float arg2, float *product){
#pragma HLS INLINE
	*product = arg1*arg2;
}
