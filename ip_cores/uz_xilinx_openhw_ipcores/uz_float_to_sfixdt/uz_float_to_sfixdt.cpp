#include "uz_float_to_sfixdt.h"

void uz_float_to_sfixdt(float in_float, uint8_t fraction, int32_t *out_sfix){
#pragma HLS INTERFACE mode=ap_none port=in_float
#pragma HLS INTERFACE mode=ap_none port=fraction
#pragma HLS INTERFACE mode=ap_none port=out_sfix
	*out_sfix = (uint32_t)(roundf(ldexpf(in_float, fraction)));
}
