#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define TEST_RANGE 1e-3

void uz_VSD_6ph_asym(float in[6], float *out_1, float *out_2, float *out_3, float *out_4, float *out_5, float *out_6);
bool test_float_within(float range, float val1, float val2);

int main(){
	float test_in[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
	float out[6];
	uz_VSD_6ph_asym(test_in, &out[0], &out[0], &out[0], &out[0], &out[0], &out[0]);
	if(test_float_within(TEST_RANGE, -0.7877f, out[0]) &&
			test_float_within(TEST_RANGE, -0.7887f, out[1]) &&
			test_float_within(TEST_RANGE, -0.2113f, out[2]) &&
			test_float_within(TEST_RANGE, -0.2113f, out[3]) &&
			test_float_within(TEST_RANGE, 2.0f, out[4]) &&
			test_float_within(TEST_RANGE, 5.0f, out[5]))
		return 0;
	else
		return 0;
}

bool test_float_within(float range, float val1, float val2){
	bool feedback = false;
	if(fabs(val1-val2)<=range)
		feedback = true;
	else
		feedback = false;
	return feedback;
}
