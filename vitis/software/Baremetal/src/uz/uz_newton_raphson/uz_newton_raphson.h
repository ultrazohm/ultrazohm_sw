#ifndef UZ_NEWTON_RAPHSON
#define UZ_NEWTON_RAPHSON

#include "../uz_array/uz_array.h"
#include <stdbool.h>


struct uz_newton_raphson_config {
    uz_array_float_t coefficients; /**< Array which carries the coefficients of the polynomial (a,b,c,d,e etc.) */
    uz_array_float_t poly_coefficients; /**< Array which carries the coefficients for the polynomial. \n 
                                        They are scaled to 0/1 */
    uz_array_float_t derivate_poly_coefficients; /**< Array which carries the coefficients for the derivate of the polynomial. \n 
                                        They carry the derivative part, i.e. the scaled value of the original function times the factor from the derivate (x^4 -> 4x^3). */
    float initial_value; /**< Initial value with which the approximation starts. Should be a reasonable start value, otherwise the algorithm may not converge */
    uint32_t iterations;  /**< Number of iterations the algorithm will cycle through */

};

/**
 * @brief Approximates the root of the polynomial
 * 
 * @param config uz_newton_raphson_config 
 * @return float root of the polynomial
 */
float uz_newton_raphson(struct uz_newton_raphson_config config);

/**
 * @brief Calculates the derivate of the function
 * 
 * @param poly_coefficients coefficients of f(x)
 * @param derivate_poly_coefficients coefficients of f'(x). Array size must be the array size of f(x)-1
 */
void uz_newton_raphson_derivate(uz_array_float_t poly_coefficients, uz_array_float_t derivate_poly_coefficients);

#endif // UZ_NEWTON_RAPHSON
