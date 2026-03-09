#ifndef UZ_LUT_1D_H
#define UZ_LUT_1D_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

typedef struct uz_LUT_1D_t uz_LUT_1D_t;

/**
 * @brief Initializes a 1D Look-Up Table (LUT) instance with the provided breakpoints, data, and length.
 * 
 * @param breakpoints pointer to uz_array_float_t objects for breakpoints for the LUT. Data Array must be in ascending order and have the same length as data
 * @param data pointer to uz_array_float_t object for data values corresponding to the breakpoints. Data Array must be in ascending order and must have the same length as breakpoints
 * @param length length of arrays breakpoints and data, must be greater than 1
 * @return uz_LUT_1D_t* 
 */
uz_LUT_1D_t* uz_LUT_1D_init(uz_array_float_t * breakpoints, uz_array_float_t * data, uint32_t length);


float uz_LUT_1D_get_value(uz_LUT_1D_t* self, float input);

#endif // UZ_LUT_1D_H
