#include "matrix_multiply.h"


void MatrixMultiplication(float *A_input, float *B_input, float *C_output, uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns){
#pragma HLS INTERFACE m_axi port=A_input bundle=arrays depth=32 offset=slave
#pragma HLS INTERFACE m_axi port=B_input bundle=arrays depth=32 offset=slave
#pragma HLS INTERFACE m_axi port=C_output bundle=arrays depth=32 offset=slave
#pragma HLS INTERFACE s_axilite port=A_rows
#pragma HLS INTERFACE s_axilite port=B_rows
#pragma HLS INTERFACE s_axilite port=B_columns
#pragma HLS INTERFACE mode=ap_ctrl_chain port=return
	const uint_fast32_t M = A_rows;
	const uint_fast32_t N = B_rows;
	const uint_fast32_t K = B_columns;

	float A[5] = {0};
	float B[25] = {0};
	float C[5] = {0};
	//Burst read input
	for(int i=0; i < 5; i++) {
		A[i] = A_input[i];
	}

	for(int i=0; i < 25; i++) {
		B[i] = B_input[i];
	}

	for (uint_fast32_t m = 0; m < M; m++) {
		float acc[25]={0};
		for (uint_fast32_t k = 0; k < K; k++) {
			for (uint_fast32_t n = 0; n < N; n++) {
				acc[n] = A[(N * m) + n] * B[(K * n) + k];
		    }
		    for (uint_fast32_t n = 0; n < N; n++) {
		    	C[(K * m) + k] += acc[n];
		    }
		}
	}

	//Burst write output
	for(int i=0; i < 5; i++) {
		C_output[i] = C[i];
	}
}

