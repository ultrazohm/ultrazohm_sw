#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "uz_VSD.h"

#include "../uz_HLS_test.h"
#include "../uz_HLS_test.c"

#define TEST_RANGE 1e-3

int main(){
	float alpha, beta;
	uz_VSD_6ph_asym(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, &alpha, &beta);
	printf("Test result:\n");
	if(test_float_within(TEST_RANGE, -0.7877f, alpha) && test_float_within(TEST_RANGE, -0.7887f, beta)){
		printf("passed");
	}else{
		printf("failed");
	}
	return 0;
}


