#include <stdint.h>
#include <stdio.h>
#include "uz_Park.h"
#include "../uz_HLS_test.h"
#include "../uz_HLS_test.c"

#define TEST_RANGE 1e-3

int main(){
	float in_trafo_alpha = 4.0f, in_trafo_beta = -5.5f, in_inv_d = 4.0f, in_inv_q = -5.5f, theta_el = 50.1f;
	float out_trafo_d, out_trafo_q, out_inv_alpha, out_inv_beta;

	uz_Park(in_trafo_alpha, in_trafo_beta, in_inv_d, in_inv_q, theta_el, &out_trafo_d, &out_trafo_q, &out_inv_alpha, &out_inv_beta);

	printf("Test result:\n");
	test_float_within(TEST_RANGE, 4.851f, out_trafo_d);
	test_float_within(TEST_RANGE, -4.766f, out_trafo_q);
	test_float_within(TEST_RANGE, -6.084f, out_inv_beta);
	test_float_within(TEST_RANGE, 3.039f, out_inv_alpha);
	return 0;
}


