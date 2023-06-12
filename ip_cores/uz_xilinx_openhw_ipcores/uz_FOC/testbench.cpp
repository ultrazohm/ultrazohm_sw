#include "uz_FOC.h"
#include "../lib/uz_HLS_test/uz_HLS_test.h"
#include "../lib/uz_HLS_test/uz_HLS_test.c"


#define TEST_RANGE 1e-3

int main(){

bool status;
float test1, test2;




float sampletime = 1.0f;
    float Ki = 1.0f, Kp = 11.54f, limit = 20.0f, ref_d = 12.0f, act_d = 2.0f, ref_q = 2.0f, act_q = 12.0f;
    float output_ref_d[5] = {20.0f, 20.0f, 20.0f, 20.0f, 20.0f};
    float output_ref_q[5] = {-20.0f, -20.0f, -20.0f, -20.0f, -20.0f};
    float ref_ud, ref_uq;
    for(int i=0;i<5;i++){
    	uz_FOC(output_ref_d[i], output_ref_q[i], sampletime, Ki, Kp, Ki, Kp, limit, false, act_d, act_q, false, &ref_ud, &ref_uq);
    	test_float_within(TEST_RANGE, output_ref_d[i], ref_ud);
    	test_float_within(TEST_RANGE, output_ref_q[i], ref_uq);
    }
}
