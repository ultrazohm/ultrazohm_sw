#include "uz_HLS_test.h"
bool test_float_within(float range, float val1, float val2){
	bool feedback = false;
	if(fabs(val1-val2)<=range){
		feedback = true;
		printf("passed:");
	}else{
		feedback = false;
		printf("failed:");
	}
	printf(" Expected: %.3f, was: %.3f\n", val1, val2);
	return feedback;
}


bool test_equal_int32_t(int32_t val1, int32_t val2){
	bool feedback = false;
	if(val1 == val2){
		feedback = true;
		printf("passed:");
	}else{
		feedback = false;
		printf("failed:");
	}
	printf(" Expected: %d, was: %d\n", val1, val2);
	return feedback;
}
