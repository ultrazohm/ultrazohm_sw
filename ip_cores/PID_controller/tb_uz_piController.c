#include "uz_piController.h"
#include "uz_signals.h"
#include <stdio.h>

//For floating point comparison
typedef union {
 float fval;
 unsigned int rawbits;
} float_union_t;

bool approx_eqf(float x, float y, int ulp_err_lim, float abs_err_lim)
    {
     float_union_t lx, ly;
     lx.fval = x;
     ly.fval = y;
     if (((x == 0.0f) ^ (y == 0.0f)) || (__signbit(x) != __signbit(y)))
     {
		#ifndef NDEBUG
		 if (x != y) { // (-0.0 == +0.0) so warning not printed for that case
			 printf("\nWARNING: Comparing floating point value against zero ");
			 printf("or values w/ differing signs. ");
			 printf("Absolute error limit has been used.\n");
		 }
		#endif
		 return fabs(x - y) <= fabs(abs_err_lim);
     }
     // Do ULP base comparison for all other cases
     return abs((int)lx.rawbits - (int)ly.rawbits) <= ulp_err_lim;
    }

int main()
{
//config parameters
	uz_PI_Controller_config config = {0};
	config.samplingTime_sec = 1.0f;
	config.Ki = 1.0f;
	config.Kp = 1.154f;
	config.upper_limit = 20.0f;
	config.lower_limit = -20.0f;
    float referenceValue[13] = {2.54f, 5.0f, -1.45f, -1.23f, 5.54f, 10.32f, -9.45f, -15.23f, 2.0f, 1.0f, 12.0f, 12.0f, 2.0f};
    float actualValue[13]    = {1.62f, 6.5f, -3.25f, 2.54f, 1.62f, 6.5f, -3.25f, 2.54f, 1.0f, 2.0f, 2.0f, 12.1f, 12.0f};
//SW values
    float output[13] = { 1.061680f,-0.811000f,1.497200f,-3.130580f,1.973680f,5.778280f,-1.964800f,-20.000000f,0.144000f,-1.164000f,10.530001f,8.874599f,-2.650002f};

//Hardware part
    float out[13];
    printf("\n HW output\r");
    for(int j=0;j<13;j++){
        uz_PI_Controller_sample(&config,false, referenceValue[j], actualValue[j], false, &out[j]);
        printf(" %f\r",out[j]);
    }

//comparison of sw and hw outputs*/
    bool test;
	for(int k=0;k<13;k++){
		test = approx_eqf(out[k], output[k], 12, 1);
		if(test){
			printf("Test passed\r");
		}
		else{
			printf("Test failed %f\r", out[k]-output[k]);
		}
	}
}



