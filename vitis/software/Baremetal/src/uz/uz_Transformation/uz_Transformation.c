/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "uz_Transformation.h"
#include "../uz_HAL.h"
#include <math.h>
uz_dq_t uz_dq_transformation(uz_UVW_t input, float theta_el_rad){
    uz_alphabeta_t ab = uz_clarke_transformation(input);
    float sin_coefficent = sinf(theta_el_rad);
    float cos_coefficent = cosf(theta_el_rad);
    uz_dq_t output = {
        .d = (cos_coefficent * ab.alpha) + (sin_coefficent * ab.beta),
        .q = (-sin_coefficent * ab.alpha) + (cos_coefficent * ab.beta),
        .zero = ab.gamma
    };
    return(output);
}

uz_UVW_t uz_dq_inverse_transformation(uz_dq_t input, float theta_el_rad){
   
   float sin_coefficent = sinf(theta_el_rad);
   float cos_coefficent = cosf(theta_el_rad);
    uz_alphabeta_t ab = {
        .alpha = (cos_coefficent * input.d) - (sin_coefficent * input.q),
        .beta = (sin_coefficent * input.d) + (cos_coefficent * input.q),
        .gamma = input.zero
    };
    uz_UVW_t output=uz_clarke_inverse_transformation(ab);
    return(output);
}

uz_alphabeta_t uz_clarke_transformation(uz_UVW_t input) {
	uz_alphabeta_t output = {
        .alpha = (2.0f / 3.0f) * (input.U - (input.V / 2.0f) - (input.W / 2.0f) ),
        .beta = (2.0f / 3.0f) * ( (input.V * (sqrtf(3.0f) / 2.0f) ) - (input.W * (sqrtf(3.0f) / 2.0f) ) ),
        .gamma = (1.0f / 3.0f) * (input.U + input.V + input.W)
    };
    return(output);
}

uz_UVW_t uz_clarke_inverse_transformation(uz_alphabeta_t input){
    uz_UVW_t output = {
        .U =  input.alpha + input.gamma,
        .V = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (sqrtf(3.0f) / 2.0f) ) + input.gamma,
        .W = (input.alpha * (-1.0f / 2.0f) ) + (input.beta * (-sqrtf(3.0f) / 2.0f) ) + input.gamma
    };
    return(output);
}


