#include "uz_VSD.h"
#include "../lib/uz_VSD_shared/uz_VSD_shared.h"
#include "../lib/uz_VSD_shared/uz_VSD_shared.cpp"
void uz_VSD_6ph_asym(float in_a1, float in_b1, float in_c1, float in_a2, float in_b2, float in_c2, float *out_alpha, float *out_beta){
#pragma HLS INTERFACE mode=ap_none port=out_beta
#pragma HLS INTERFACE mode=ap_none port=out_alpha
#pragma HLS INTERFACE mode=ap_none port=in_a1
#pragma HLS INTERFACE mode=ap_none port=in_b1
#pragma HLS INTERFACE mode=ap_none port=in_c1
#pragma HLS INTERFACE mode=ap_none port=in_a2
#pragma HLS INTERFACE mode=ap_none port=in_b2
#pragma HLS INTERFACE mode=ap_none port=in_c2
#pragma HLS dataflow
	float cpy_in[6] = {in_a1, in_b1, in_c1, in_a2, in_b2, in_c2};

	uz_6ph_arraymul(0, cpy_in, out_alpha);
	uz_6ph_arraymul(1, cpy_in, out_beta);
	//used for full VSD
	//uz_6ph_arraymul(2, cpy_in, out_3);
	//uz_6ph_arraymul(3, cpy_in, out_4);
	//uz_6ph_arraymul(4, cpy_in, out_5);
	//uz_6ph_arraymul(5, cpy_in, out_6);
}

void multiply_line(const int line, float const val[6], float products[6]){
#pragma HLS INLINE
#pragma HLS dataflow
	float const vsd_mat[6][6] = {
	        { 0.3333333f, -0.1666667f, -0.1666667f, 0.2886751f, -0.2886751f, 0.0000000f },
	        { 0.0000000f, 0.2886751f, -0.2886751f, 0.1666667f, 0.1666667f, -0.3333333f },
	        { 0.3333333f, -0.1666667f, -0.1666667f, -0.2886751f, 0.2886751f, 0.0000000f },
	        { 0.0000000f, -0.2886751f, 0.2886751f, 0.1666667f, 0.1666667f, -0.3333333f },
	        { 0.3333333f, 0.3333333f, 0.3333333f, 0.0000000f, 0.0000000f, 0.0000000f },
	        { 0.0000000f, 0.0000000f, 0.0000000f, 0.3333333f, 0.3333333f, 0.3333333f }
	    };
	multiply(vsd_mat[line][0], val[0], &products[0]);
	multiply(vsd_mat[line][1], val[1], &products[1]);
	multiply(vsd_mat[line][2], val[2], &products[2]);
	multiply(vsd_mat[line][3], val[3], &products[3]);
	multiply(vsd_mat[line][4], val[4], &products[4]);
	multiply(vsd_mat[line][5], val[5], &products[5]);
}
