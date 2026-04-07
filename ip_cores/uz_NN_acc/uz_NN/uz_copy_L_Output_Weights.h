#ifndef UZ_COPY_L_OUTPUT_WEIGHTS_H
#define UZ_COPY_L_OUTPUT_WEIGHTS_H

#include <stdio.h>
#include <stdint.h>

void uz_copy_L_Output_Weights(float* padded_array, float* non_padded_array, const uint_fast32_t padded_array_columns, const uint_fast32_t padded_array_rows, const uint_fast32_t non_padded_array_columns);

#endif
