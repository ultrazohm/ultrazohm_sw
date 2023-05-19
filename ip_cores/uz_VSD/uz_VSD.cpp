#include <stdint.h>

void uz_6ph_arraymul(const int line, float const val[6], float *out_);
void multiply(float arg1, float arg2, float *product);
void multiply_line(const int line, float const val[6], float products[6]);

void uz_VSD_6ph_asym(float in[6], float *out_1, float *out_2, float *out_3, float *out_4, float *out_5, float *out_6){
#pragma HLS latency min=4 max=8
#pragma HLS dataflow
	float cpy_in[6] = {in[0], in[1], in[2], in[3], in[4], in[5]};

	uz_6ph_arraymul(0, cpy_in, &out_1);
	uz_6ph_arraymul(1, cpy_in, &out_2);
	uz_6ph_arraymul(2, cpy_in, &out_3);
	uz_6ph_arraymul(3, cpy_in, &out_4);
	uz_6ph_arraymul(4, cpy_in, &out_5);
	uz_6ph_arraymul(5, cpy_in, &out_6);


}

void uz_6ph_arraymul(const int line, float const val[6], float *out_){
#pragma HLS INLINE
	float products[6];
	multiply_line(line, val, products);
    *out_ = products[0] + products[1] + products[2] + products[3] + products[4] + products[5];
}

void multiply(float arg1, float arg2, float *product){
#pragma HLS INLINE
*product = arg1*arg2;
}

void multiply_line(const int line, float const val[6], float products[6]){
#pragma HLS INLINE
#pragma HLS dataflow
	const float vsd_mat[6][6] = {
	        { 1.0000000f, 0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f },
	        { -0.5000001f, 0.8660254f, -0.4999999f, -0.8660254f, 1.0000000f, -0.0000000f },
	        { -0.4999999f, -0.8660254f, -0.5000001f, 0.8660254f, 1.0000000f, 0.0000000f },
	        { 0.8660254f, 0.5000000f, -0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
	        { -0.8660254f, 0.5000000f, 0.8660254f, 0.5000000f, 0.0000000f, 1.0000000f },
	        { 0.0000000f, -1.0000000f, 0.0000000f, -1.0000000f, 0.0000000f, 1.0000000f }
	    };
	multiply(vsd_mat[line][0], val[0], &products[0]);
	multiply(vsd_mat[line][1], val[1], &products[1]);
	multiply(vsd_mat[line][2], val[2], &products[2]);
	multiply(vsd_mat[line][3], val[3], &products[3]);
	multiply(vsd_mat[line][4], val[4], &products[4]);
	multiply(vsd_mat[line][5], val[5], &products[5]);

}


