#ifndef UZ_VSD_SHARED_C
#define UZ_VSD_SHARED_C

#include "uz_VSD_shared.h"
void multiply(float arg1, float arg2, float *product){
#pragma HLS INLINE off //if off: 5cycle delay 6000LUT, if on: 32cycle delay 1000LUT
*product = arg1*arg2;
}

void uz_6ph_arraymul(const int line, float const val[6], float *out_){
	#pragma HLS INLINE
	float products[6];
	multiply_line(line, val, products);
    *out_ = products[0] + products[1] + products[2] + products[3] + products[4] + products[5];
}

#endif
