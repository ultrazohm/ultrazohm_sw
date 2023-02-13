#ifndef UZ_COMPLEX_H
#define UZ_COMPLEX_H

#include "../uz_math_constants.h"
#include <stdint.h>
#include <math.h>

typedef struct uz_complex_cartesian_t{
    float real;
    float imaginary;
}uz_complex_cartesian_t;

typedef struct uz_complex_exponential_t{
    float absolute;
    float phase;
}uz_complex_exponential_t;

uz_complex_cartesian_t uz_complex_multiplication(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2);

uz_complex_cartesian_t uz_complex_addition(uz_complex_cartesian_t arg1, uz_complex_cartesian_t arg2);

uz_complex_cartesian_t uz_complex_division(uz_complex_cartesian_t dividend, uz_complex_cartesian_t divisor);

uz_complex_exponential_t uz_complex_cartesian_to_exponential(uz_complex_cartesian_t in);

uz_complex_cartesian_t uz_complex_exponential_to_cartesian(uz_complex_exponential_t in);

#endif // UZ_COMPLEX_H
