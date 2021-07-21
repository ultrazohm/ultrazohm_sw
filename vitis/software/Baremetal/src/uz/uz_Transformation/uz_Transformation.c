#include "uz_Transformation.h"
#include "../uz_HAL.h"
#include <math.h>


struct uz_dq uz_dq_Transformation(struct uz_UVW input, float theta_el_rad){
    struct uz_dq output ={
        .d = 0.0f,
        .q = 0.0f,
        .zero = 0.0f
    };
    output.d = (2.0f / 3.0f) * ( (cosf(theta_el_rad) * input.U) + (cosf(theta_el_rad -  ( (2.0f / 3.0f) * M_PI) ) * input.V) + (cosf(theta_el_rad - ( (4.0f / 3.0f) * M_PI) ) * input.W) );
    output.q = (2.0f / 3.0f) * ( -1.0f * (sinf(theta_el_rad) * input.U) - (sinf(theta_el_rad -  ( (2.0f / 3.0f) * M_PI) ) * input.V) - (sinf(theta_el_rad - ( (4.0f / 3.0f) * M_PI) ) * input.W) );
    output.zero = (1.0f / 3.0f) * (input.U + input.V + input.W);
    return(output);
}

struct uz_UVW uz_inverse_dq_Transformation(struct uz_dq input, float theta_el_rad){
    struct uz_UVW output = {
        .U = 0.0f,
        .V = 0.0f,
        .W = 0.0f
    };
    output.U = (cosf(theta_el_rad) * input.d) - (sinf(theta_el_rad) * input.q) + input.zero;
    output.V = (cosf(theta_el_rad -  ( (2.0f / 3.0f) * M_PI) ) * input.d) - (sinf(theta_el_rad - ( (2.0f / 3.0f) * M_PI) ) * input.q) + input.zero;
    output.W = (cosf(theta_el_rad -  ( (4.0f / 3.0f ) * M_PI) ) * input.d) - (sinf(theta_el_rad - ( (4.0f / 3.0f) * M_PI) ) * input.q) + input.zero;
    return(output);
}

struct uz_alphabeta uz_clarke_Transformation(struct uz_UVW input) {
	struct uz_alphabeta output = {
        .alpha = 0.0f,
        .beta = 0.0f,
        .gamma = 0.0f
    };
    output.alpha = (2.0f / 3.0f) * (input.U - (input.V / 2.0f) - (input.W / 2.0f) );
    output.beta = (2.0f / 3.0f) * (input.V * (sqrtf(3.0f) / 2.0f) ) - (input.W * (sqrtf(3.0f) / 2.0f) );
	output.gamma = (1.0f / 3.0f) * (input.U + input.V + input.W);
    return(output);
}

struct uz_UVW uz_inverse_clarke_Transformation(struct uz_alphabeta input){
    struct uz_UVW output = {
        .U = 0.0f,
        .V = 0.0f,
        .W = 0.0f
    };
    output.U = input.alpha + input.gamma;
    output.V = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (sqrtf(3.0f) / 2.0f) ) + input.gamma;
    output.W = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (-sqrtf(3.0f) / 2.0f) ) + input.gamma;
    return(output);
}


