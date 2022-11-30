#include "test.h"
#include "hls_math.h"
#include "ap_fixed.h"

typedef ap_fixed<18,8,AP_RND,AP_SAT> fxd;

uz_3ph_dq_t uz_transformation_3ph_abc_to_dq(uz_3ph_abc_t input, float theta_el_rad)
{
	fxd a=input.a;
	fxd b=input.b;
	fxd c=input.c;
	fxd x= (fxd)0.66 * a;
	fxd y=(b) - (c);
	fxd z=( (fxd)0.66 * (fxd)0.5)*(y);
	fxd alpha =x - z;
	fxd beta = (fxd)0.57156 * (b-c);
	fxd gamma = (fxd)0.33* (a + b + c);

    fxd sin_coefficient = hls::sinf((fxd)theta_el_rad);
    fxd cos_coefficient = hls::cosf((fxd)theta_el_rad);
   // hls::sincosf( (fxd)theta_el_rad,&sin_coefficient, &cos_coefficient);
    uz_3ph_dq_t output = {
        .d = (float) ((cos_coefficient * alpha) + (sin_coefficient * beta)),
        .q = (float) ((-sin_coefficient *alpha) + (cos_coefficient * beta)),
        .zero = (float)gamma};

    return (output);
}








