#include "test.h"
#include <stdio.h>
#include "hls_math.h"

uz_3ph_abc_t UVW_system = {0};
uz_3ph_dq_t dq_system = {0};
uz_3ph_alphabeta_t alphabeta_system = {0};


int main(){
    UVW_system.a = 1.0f;
    UVW_system.b = -(1.0f / 2.0f);
    UVW_system.c = -(1.0f / 2.0f);
    float theta_el_rad = M_PI / 2.0f;
    uz_3ph_dq_t output = uz_transformation_3ph_abc_to_dq(UVW_system, theta_el_rad);

}
