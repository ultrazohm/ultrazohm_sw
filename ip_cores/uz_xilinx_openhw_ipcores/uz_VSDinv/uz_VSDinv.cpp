#include "uz_VSDinv.h"
#include "../uz_VSD_shared/uz_VSD_shared.cpp"

//for full VSD
//	void uz_VSDinv_6ph_asym(float in[6], float *out_a1, float *out_b1, float *out_c1, float *out_a2, float *out_b2, float *out_c2){
void uz_VSDinv_6ph_asym(float in_alpha, float in_beta, float *out_a1, float *out_b1, float *out_c1, float *out_a2, float *out_b2, float *out_c2){
#pragma HLS INTERFACE mode=ap_none port=in_alpha
#pragma HLS INTERFACE mode=ap_none port=in_beta
#pragma HLS INTERFACE mode=ap_none port=out_a1
#pragma HLS INTERFACE mode=ap_none port=out_b1
#pragma HLS INTERFACE mode=ap_none port=out_c1
#pragma HLS INTERFACE mode=ap_none port=out_a2
#pragma HLS INTERFACE mode=ap_none port=out_b2
#pragma HLS INTERFACE mode=ap_none port=out_c2
#pragma HLS dataflow
	//for full VSD
	//float cpy_in[6] = {in[0], in[1], in[2], in[3], in[4], in[5]};
	float cpy_in[6] = {in_alpha, in_beta, 0, 0, 0, 0};
	uz_6ph_arraymul(0, cpy_in, out_a1);
	uz_6ph_arraymul(1, cpy_in, out_b1);
	uz_6ph_arraymul(2, cpy_in, out_c1);
	uz_6ph_arraymul(3, cpy_in, out_a2);
	uz_6ph_arraymul(4, cpy_in, out_b2);
	uz_6ph_arraymul(5, cpy_in, out_c2);
}

void multiply_line(const int line, float const val[6], float products[6]){
#pragma HLS INLINE
#pragma HLS dataflow
	float const vsd_mat[6][6] = {
	        { 1.0000000f, 0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f },
	        { -0.5000001f, 0.8660254f, -0.4999999f, -0.8660254f, 1.0000000f, -0.0000000f },
	        { -0.4999999f, -0.8660254f, -0.5000001f, 0.8660254f, 1.0000000f, 0.0000000f },
	        { 0.8660254f, 0.5000000f, -0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
	        { -0.8660254f, 0.5000000f, 0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
	        { 0.0000000f, -1.0000000f, 0.0000000f, -1.0000000f, 0.0000000f, 1.0000000f }
	    };
	multiply(vsd_mat[line][0], val[0], &products[0]);
	multiply(vsd_mat[line][1], val[1], &products[1]);
/* for full VSD
	multiply(vsd_mat[line][2], val[2], &products[2]);
	multiply(vsd_mat[line][3], val[3], &products[3]);
	multiply(vsd_mat[line][4], val[4], &products[4]);
	multiply(vsd_mat[line][5], val[5], &products[5]);
*/
	products[2] = 0;
	products[3] = 0;
	products[4] = 0;
	products[5] = 0;
}
