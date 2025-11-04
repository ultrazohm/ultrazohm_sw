#ifndef UZ_DENSE_H
#define UZ_DENSE_H

#include <stdio.h>
#include <stdint.h>

void uz_dense(const float *input, const float *weights, const float *bias, float *output,
                const uint_fast32_t input_columns, const uint_fast32_t output_columns);

#endif
