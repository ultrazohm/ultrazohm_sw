#ifndef UZ_LUT_2D_H
#define UZ_LUT_2D_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

typedef struct uz_LUT_2D_t uz_LUT_2D_t;

/**
 * @brief Initializes a 2D Look-Up Table (LUT) instance with the provided breakpoints and grid data.
 *
 * Data layout:
 * - data is a flattened 2D array in row-major order
 * - x-axis changes fastest
 * - index = (y_index * breakpoints_x->length) + x_index
 *
 * Preconditions:
 * - breakpoints_x, breakpoints_y and data are not NULL
 * - their data pointers are not NULL
 * - both breakpoint arrays have length of at least 2
 * - both breakpoint arrays are strictly increasing (no duplicates)
 * - data length is breakpoints_x->length * breakpoints_y->length
 *
 * @param breakpoints_x pointer to x-axis breakpoints
 * @param breakpoints_y pointer to y-axis breakpoints
 * @param data pointer to flattened 2D grid values
 * @return uz_LUT_2D_t*
 */
uz_LUT_2D_t *uz_LUT_2D_init(uz_array_float_t *breakpoints_x, uz_array_float_t *breakpoints_y, uz_array_float_t *data);

/**
 * @brief Returns a bilinearly interpolated LUT value at (input_x, input_y).
 *
 * Inputs are clamped to the breakpoint ranges before interpolation.
 * NaN inputs propagate through the interpolation and result in NaN.
 *
 * @param self instance of the LUT_2D
 * @param input_x x-axis input value
 * @param input_y y-axis input value
 * @return float
 */
float uz_LUT_2D_get_value(uz_LUT_2D_t *self, float input_x, float input_y);

#endif // UZ_LUT_2D_H
