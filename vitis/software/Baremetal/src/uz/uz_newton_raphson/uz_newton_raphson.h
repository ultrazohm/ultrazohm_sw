#ifndef UZ_NEWTON_RAPHSON
#define UZ_NEWTON_RAPHSON

#include "../uz_array/uz_array.h"
#include <stdbool.h>


struct uz_newton_raphson_config {
    uz_array_float_t coefficients; /**< Array which carries the coefficients of the polynomial (i.e. 14*x³) */
    uz_array_float_t derivate_poly_coefficients; /**< Array which carries the coefficients for the derivate of the polynomial. \n 
                                        They only carry the derivative part, i.e. the scaled value of the original function times the factor from the derivate (x^4 -> 4x^3). 
                                        The coefficients (a,b,c,d, etc.) are NOT included in this array.*/
    float initial_value; /**< Initial value with which the approximation starts. Should be a reasonable start value, otherwise the algorithm may not converge */
    uint32_t iterations;  /**< Number of iterations the algorithm will cycle through */
    float root_absolute_tolerance; /**< Absolute tolerance of the approximated root. An assertion is triggered if the polynomial evaluates to a value outside of the tolerance (-tolerance<f(x_root)<tolerance) for the approximated root x_root. This happens if there are not enough iterations, the given polynomial does not have a real-valued root, or the initial value was not choosen in a way that leads to convergence. */
};

/**
 * @brief Approximates the root of the polynomial
 * 
 * @param config uz_newton_raphson_config struct
 * @return float root of the polynomial
 */
float uz_newton_raphson(struct uz_newton_raphson_config config);

/**
 * @brief Calculates the derivate of the function. Writes the values directly into the derivate array. The derivate is scaled to (0/1 * derivate_factor).
 * 
 * @param config uz_newton_raphson_config struct
 */
void uz_newton_raphson_derivate(struct uz_newton_raphson_config config);

#endif // UZ_NEWTON_RAPHSON
