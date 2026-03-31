#ifndef UZ_LUT_1D_H
#define UZ_LUT_1D_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

typedef struct uz_LUT_1D_t uz_LUT_1D_t;

/**
 * @brief Initializes a 1D Look-Up Table (LUT) instance with the provided breakpoints, data, and length.
 *
 * @param breakpoints pointer to uz_array_float_t objects for breakpoints for the LUT. Breakpoints array must be in ascending order and have the same length as data
 * @param data pointer to uz_array_float_t object for data values corresponding to the breakpoints. Data array must have the same length as breakpoints
 * @return uz_LUT_1D_t*
 */
uz_LUT_1D_t *uz_LUT_1D_init(uz_array_float_t *breakpoints, uz_array_float_t *data);

/**
 * @brief Returns the value from the LUT corresponding to the given input using linear interpolation. If the input is outside the bounds of the breakpoints, it returns the value of the nearest breakpoint.
 *
 * @param self instance of the LUT_1D
 * @param input value corresponding to the breakpoints
 * @return float
 */
float uz_LUT_1D_get_value(uz_LUT_1D_t *self, float input);

#endif // UZ_LUT_1D_H
