#include <stdint.h>
#include <stdio.h>
#include "uz_fixdt_to_float.h"
#define FIXDT_SIGNED 1U
#define FIXDT_WORD 27U
#define FIXDT_FRACTION 18U


int main(){
	int32_t testval = 0x0507df3;
	float out = 0.0f;
	printf("Result:\n");
	uz_fixdt_to_float(testval, FIXDT_FRACTION, FIXDT_WORD, FIXDT_SIGNED, &out);
	printf("Expected: +20.123f, out: %f\n", out);
	testval = 0x7c03a5e;
	uz_fixdt_to_float(testval, FIXDT_FRACTION, FIXDT_WORD, FIXDT_SIGNED, &out);
	printf("Expected: -15.943f, out: %f\n", out);
	return 0;
}
