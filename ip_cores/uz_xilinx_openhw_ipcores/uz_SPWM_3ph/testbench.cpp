#include "uz_SPWM_3ph.h"
#include "../uz_HLS_test.h"
#include "../uz_HLS_test.c"

#define TEST_RANGE 1e-3

int main(){
	float ua = 100.0f, ub = -100.0f, uc = 4.0f, udc = 10.0f;
	float DCa, DCb, DCc;
	uz_SPWM_3ph(ua, ub, uc, udc, &DCa, &DCb, &DCc);
	printf("Test result:\n");

	test_float_within(TEST_RANGE, 1.0f, DCa);
	test_float_within(TEST_RANGE, 0.0f, DCb);
	test_float_within(TEST_RANGE, 0.9f, DCc);
	return 0;
}


