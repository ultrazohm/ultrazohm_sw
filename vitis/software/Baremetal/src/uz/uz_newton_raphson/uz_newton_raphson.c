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

/**
 * @brief Approximates the root of the polynomial
 * 
 * @param config uz_newton_raphson_config 
 * @return float root of the polynomial
 */
float uz_newton_raphson(struct uz_newton_raphson_config config) {
    uz_assert(config.poly_coefficients.length <= (MAX_POLYNOMIAL_ORDER + 1U));
    uz_assert(config.derivate_poly_coefficients.length == (config.poly_coefficients.length - 1U));
    float f_x = 0.0f;
    float f_derivate_x = 0.0f;  
    float result = config.initial_value;
    float xpow_temp[MAX_POLYNOMIAL_ORDER + 1U] = {0}; 
    uz_array_float_t xpow = {
        .length = UZ_ARRAY_SIZE(xpow_temp),
        .data = &xpow_temp[0]
    }; 
    uz_assert(config.coefficients.length == config.poly_coefficients.length); 
    for (uint32_t k=0U;k < config.iterations; k++) {
        for (uint32_t i=0U;i < config.poly_coefficients.length;i++) {
            if (i == 0U) {
                xpow.data[i] = 1.0f;
            } else {
                xpow.data[i] = xpow.data[i-1] * result;
            } 
            f_x += config.poly_coefficients.data[i] * config.coefficients.data[i] * xpow.data[i];
        }
        for (uint32_t i=0;i < config.derivate_poly_coefficients.length;i++) {
            f_derivate_x += config.derivate_poly_coefficients.data[i] * config.coefficients.data[i+1] * xpow.data[i];
        }
        result = result - (f_x / f_derivate_x);
        f_x = 0.0f;
        f_derivate_x = 0.0f;  
        }    
    return (result);
}


/**
 * @brief Calculates the derivate of the function
 * 
 * @param poly_coefficients coefficients of f(x)
 * @param derivate_poly_coefficients coefficients of f'(x). Array size must be the array size of f(x)-1
 */
void uz_newton_raphson_derivate(uz_array_float_t poly_coefficients, uz_array_float_t derivate_poly_coefficients) {
    uz_assert(derivate_poly_coefficients.length == (poly_coefficients.length - 1U));
    for (uint32_t i=0;i < derivate_poly_coefficients.length;i++) {
        derivate_poly_coefficients.data[i] = ((float)i + 1.0f) * poly_coefficients.data[i+1];
    }
}














