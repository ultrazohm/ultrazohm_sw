#ifndef UZ_NEWTON_RAPHSON
#define UZ_NEWTON_RAPHSON

#include "../uz_array/uz_array.h"
#include <stdbool.h>

#define MAX_POLYNOMIAL_ORDER 20U

struct uz_newton_raphson_config {
    uz_array_float_t coefficients; /**< Array which carries the coefficients of the polynomial (a,b,c,d,e etc.). \n These are only necessary, if the use_separate_coefficients member is true. */
    uz_array_float_t poly_coefficients; /**< Array which carries the coefficients for the polynomial. \n 
                                        They can be either nominated to 0/1 (use_separate_coefficients = true) or carry the combination of \n
                                        of the nominated value 0/1 and the corresponding coefficient a,b,c... */
    uz_array_float_t derivate_poly_coefficients; /**< Array which carries the coefficients for the derivate of the polynomial. \n 
                                        They can either only carry the derivative part(use_separate_coefficients = true) or carry the combination of \n 
                                        of the derivate part and the corresponding coefficient*/
    float initial_value; /**< Initial value with which the approximation starts. Should be a reasonable start value, otherwise the algorithm may not converge */
    uint32_t iterations;  /**< Number of iterations the algorithm will cycle through */

};

float uz_newton_raphson(struct uz_newton_raphson_config config);

void uz_newton_raphson_derivate(uz_array_float_t poly_coefficients, uz_array_float_t derivate_poly_coefficients);
#endif // UZ_NEWTON_RAPHSON
