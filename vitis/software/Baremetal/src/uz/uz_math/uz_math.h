#ifndef UZ_MATH_H

#define UZ_MATH_H

#include <stdint.h>

float uz_math_mean(float *vector, uint32_t size);

float uz_math_variance(float *vector, uint32_t size);

float uz_math_standard_deviation(float *vector, uint32_t size);

#endif // UZ_MATH_H