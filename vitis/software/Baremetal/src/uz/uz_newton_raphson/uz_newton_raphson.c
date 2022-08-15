/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennis Hufnagel
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

#include "uz_newton_raphson.h"
#include <math.h>
#include "../uz_HAL.h"

#define MAX_POLYNOMIAL_ORDER 10U

static float uz_newton_raphson_calculate_f_x(struct uz_newton_raphson_config config, uz_array_float_t xpow, float result);

float uz_newton_raphson(struct uz_newton_raphson_config config) {
    uz_assert(config.coefficients.length <= (MAX_POLYNOMIAL_ORDER + 1U));
    uz_assert(config.derivate_poly_coefficients.length == (config.coefficients.length - 1U));
    float f_x = 0.0f;
    float f_derivate_x = 0.0f;  
    float result = config.initial_value;
    float xpow_temp[MAX_POLYNOMIAL_ORDER + 1U] = {0}; 
    uz_array_float_t xpow = {
        .length = UZ_ARRAY_SIZE(xpow_temp),
        .data = &xpow_temp[0]
    }; 
    for (uint32_t k=0U;k < config.iterations; k++) {
        f_x = uz_newton_raphson_calculate_f_x(config, xpow, result);
        for (uint32_t i=0;i < config.derivate_poly_coefficients.length;i++) {
            f_derivate_x += config.derivate_poly_coefficients.data[i] * config.coefficients.data[i+1U] * xpow.data[i];
        }
        result = result - (f_x / f_derivate_x);
        f_x = 0.0f;
        f_derivate_x = 0.0f;  
    }
    f_x=0.0f;
    f_x = uz_newton_raphson_calculate_f_x(config, xpow, result);
    if( (f_x > config.root_absolute_tolerance ) || ( f_x< -config.root_absolute_tolerance) ){
        uz_assert(0U); // Root could not be approximated with sufficient precision
    }

    return (result);
}

void uz_newton_raphson_derivate(struct uz_newton_raphson_config config) {
    uz_assert(config.derivate_poly_coefficients.length == (config.coefficients.length - 1U));
    float temp = 0.0f;
    for (uint32_t i=0;i < config.derivate_poly_coefficients.length;i++) {
        if(config.coefficients.data[i+1U] != 0.0f) {
            temp = 1.0f;    
        } else {
            temp = 0.0f;
        }
        config.derivate_poly_coefficients.data[i] = ((float)i + 1.0f) * temp;
    }
}

static float uz_newton_raphson_calculate_f_x(struct uz_newton_raphson_config config, uz_array_float_t xpow, float result) {
    float f_x = 0.0f;
    for (uint32_t i=0U;i < config.coefficients.length;i++) {
            if (i == 0U) {
                xpow.data[i] = 1.0f;
            } else {
                xpow.data[i] = xpow.data[i-1U] * result;
            } 
            f_x += config.coefficients.data[i] * xpow.data[i];
        }
    return(f_x);
}













