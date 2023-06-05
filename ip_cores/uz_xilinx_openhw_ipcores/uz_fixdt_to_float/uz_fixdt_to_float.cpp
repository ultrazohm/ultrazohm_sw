#include "uz_fixdt_to_float.h"

void uz_fixdt_to_float(int32_t in_fixed, uint8_t fraction, uint8_t word, bool sign, float *out_float){
#pragma HLS INTERFACE mode=ap_none port=in_fixed
#pragma HLS INTERFACE mode=ap_none port=fraction
#pragma HLS INTERFACE mode=ap_none port=word
#pragma HLS INTERFACE mode=ap_none port=sign
#pragma HLS INTERFACE mode=ap_none port=out_float
    int32_t in_local = in_fixed;				//use local variable
	if(sign && in_fixed & (1<<(word-1))){		//if signed and value negative
		in_local = in_local|(0xFFFFFFFF<<word); //fill up empty upper bits with 1
	}
	float input_float = (float)in_local;
	*out_float = ldexpf(input_float, -fraction);
}
