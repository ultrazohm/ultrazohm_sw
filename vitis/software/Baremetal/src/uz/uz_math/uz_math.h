#ifndef UZ_MATH_H
#define UZ_MATH_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

float uz_math_mean(uz_array_float_t array);
float uz_math_variance_uncorrected(uz_array_float_t array);
float uz_math_standard_deviation(uz_array_float_t array);
float uz_math_mean_uint32_t(uz_array_uint32_t array);

#endif // UZ_MATH_H