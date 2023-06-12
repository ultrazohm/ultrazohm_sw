#include <stdint.h>
#include <stdio.h>
#include "uz_VSDinv.h"
#include "../uz_HLS_test.h"
#include "../uz_HLS_test.c"

#define TEST_RANGE 1e-3

int main(){
	float alpha=-5.0f, beta=-1.0f;
	float result[6] = {0,0,0,0,0,0};
	uz_VSDinv_6ph_asym(alpha, beta, &result[0], &result[1], &result[2], &result[3], &result[4], &result[5]);
	printf("Test result:\n");
	if(test_float_within(TEST_RANGE, -5.0f, result[0]) && test_float_within(TEST_RANGE, 1.634f, result[1]) && test_float_within(TEST_RANGE, 3.366f, result[2]) && test_float_within(TEST_RANGE, -4.8301f, result[3]) && test_float_within(TEST_RANGE, 3.8301f, result[4]) && test_float_within(TEST_RANGE, 1.0f, result[5])){
		printf("passed");
	}else{
		printf("failed");
	}
	return 0;
}
