#include "matrix_multiply.h"


void MatrixMultiplication(float const A[5], float const B[25], float C_out[5], uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns){
#pragma HLS INTERFACE s_axilite port=A
#pragma HLS INTERFACE s_axilite port=B
#pragma HLS INTERFACE s_axilite port=C_out
#pragma HLS INTERFACE s_axilite port=A_rows
#pragma HLS INTERFACE s_axilite port=B_rows
#pragma HLS INTERFACE s_axilite port=B_columns
#pragma HLS INTERFACE mode=ap_ctrl_chain port=return
	const uint_fast32_t M = A_rows;
	const uint_fast32_t N = B_rows;
	const uint_fast32_t K = B_columns;

		for (uint_fast32_t n = 0; n < N; n++) {
				C_out[n] = 0.0f;
		}
		for (uint_fast32_t m = 0; m < M; m++) {
			float acc[25]={0};
			for (uint_fast32_t k = 0; k < K; k++) {
				for (uint_fast32_t n = 0; n < N; n++) {
					acc[n] = A[(N * m) + n] * B[(K * n) + k];
			    }
			    for (uint_fast32_t n = 0; n < N; n++) {
			    	C_out[(K * m) + k] += acc[n];
			    }
			}

		}
}

//void MatrixMultiplication(float const A[5], float const B[25], float C_out[5], uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns, bool trigger, bool* is_done){
//#pragma HLS INTERFACE s_axilite port=A
//#pragma HLS INTERFACE s_axilite port=B
//#pragma HLS INTERFACE s_axilite port=C_out
//#pragma HLS INTERFACE s_axilite port=A_rows
//#pragma HLS INTERFACE s_axilite port=B_rows
//#pragma HLS INTERFACE s_axilite port=B_columns
//#pragma HLS INTERFACE s_axilite port=trigger
//#pragma HLS INTERFACE s_axilite port=is_done
//#pragma HLS INTERFACE mode=ap_ctrl_chain port=return
//	const uint_fast32_t M = A_rows;
//	const uint_fast32_t N = B_rows;
//	const uint_fast32_t K = B_columns;
//
//	if(trigger && *is_done == false) {
//		*is_done = false;
//		for (uint_fast32_t n = 0; n < N; n++) {
//				C_out[n] = 0.0f;
//		}
//		for (uint_fast32_t m = 0; m < M; m++) {
//			float acc[25]={0};
//			for (uint_fast32_t k = 0; k < K; k++) {
//				for (uint_fast32_t n = 0; n < N; n++) {
//					acc[n] = A[(N * m) + n] * B[(K * n) + k];
//			    }
//			    for (uint_fast32_t n = 0; n < N; n++) {
//			    	C_out[(K * m) + k] += acc[n];
//			    }
//			}
//
//		}
//		*is_done = true;
//	}
//
//}

//void MatrixMultiplication_Pointer(float const *A_pointer, float const *B_pointer, float *C_out_pointer, uint_fast32_t A_rows, uint_fast32_t B_rows, uint_fast32_t B_columns, bool trigger, bool* is_done){
//#pragma HLS INTERFACE ap_ctrl_none port=return
//   #pragma HLS INTERFACE m_axi port=A_pointer bundle=arrays depth=32 offset=slave
//   #pragma HLS INTERFACE m_axi port=B_pointer bundle=arrays depth=32 offset=slave
//   #pragma HLS INTERFACE m_axi port=C_out_pointer bundle=arrays depth=32 offset=slave
//#pragma HLS INTERFACE s_axilite port=A_rows bundle=control
//#pragma HLS INTERFACE s_axilite port=B_rows bundle=control
//#pragma HLS INTERFACE s_axilite port=B_columns bundle=control
//#pragma HLS INTERFACE s_axilite port=trigger bundle=control
//#pragma HLS INTERFACE s_axilite port=is_done bundle=control
//	const uint_fast32_t M = A_rows;
//	const uint_fast32_t N = B_rows;
//	const uint_fast32_t K = B_columns;
//	float A[5] = 0.0f;
//	float B[25] = 0.0f;
//	float C_out[5] = 0.0f;
//
//	for(int i=0; i < 5; i++) {
//		A[i] = A_pointer[i];
//	}
//
//	for(int i=0; i < 25; i++) {
//			B[i] = B_pointer[i];
//	}
//
//
//	if(trigger && *is_done == false) {
//		*is_done = false;
//		for (uint_fast32_t n = 0; n < N; n++) {
//				C_out[n] = 0.0f;
//		}
//		for (uint_fast32_t m = 0; m < M; m++) {
//			float acc[25]={0};
//			for (uint_fast32_t k = 0; k < K; k++) {
//				for (uint_fast32_t n = 0; n < N; n++) {
//					acc[n] = A[(N * m) + n] * B[(K * n) + k];
//			    }
//			    for (uint_fast32_t n = 0; n < N; n++) {
//			    	C_out[(K * m) + k] += acc[n];
//			    }
//			}
//
//		}
//		*is_done = true;
//	}
//
//	for(int i=0; i < 5; i++) {
//			C_out_pointer[i] = C_out[i];
//		}
//
//}

