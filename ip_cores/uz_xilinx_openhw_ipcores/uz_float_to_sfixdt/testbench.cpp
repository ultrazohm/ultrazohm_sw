#include "uz_float_to_sfixdt.h"
#include "../uz_HLS_test.h"
#include "../uz_HLS_test.c"


#define TEST_RANGE 1e-3
#define FRACTION 12U

int main(){
	float num = 0.75f;
	int32_t result;
	uz_float_to_sfixdt(num, FRACTION, &result);
	printf("Test result:\n");
	test_equal_int32_t(0xc00, result);
	num = -0.44f;
	uz_float_to_sfixdt(num, FRACTION, &result);
	test_equal_int32_t(0xFFFFF8F6, result);
	return 0;
}


