#include "../uz_global_configuration.h"
#if UZ_LUT_2D_MAX_INSTANCES > 0U

#include "uz_LUT_2D.h"
#include <stdbool.h>
#include "../uz_HAL.h"

static bool uz_LUT2D_check_breakpoints_increasing(uz_array_float_t *breakpoints);
static uint32_t uz_LUT2D_find_interval(const uz_array_float_t *breakpoints, float input);
static float uz_LUT2D_clamp(float value, float min_value, float max_value);

typedef struct uz_LUT_2D_t
{
    bool is_ready;
    uz_array_float_t *breakpoints_x;
    uz_array_float_t *breakpoints_y;
    uz_array_float_t *data;
    uint32_t x_length;
    uint32_t y_length;
} uz_LUT_2D_t;

static uint32_t instances_counter_LUT_2D = 0U;

static uz_LUT_2D_t instances_LUT_2D[UZ_LUT_2D_MAX_INSTANCES] = {0};

/**
 * @brief Memory allocation of the uz_LUT_2D_t struct
 *
 * @return Pointer to uz_LUT_2D_t instance
 */
static uz_LUT_2D_t *uz_LUT_2D_allocation(void);

static uz_LUT_2D_t *uz_LUT_2D_allocation(void)
{
    uz_assert(instances_counter_LUT_2D < UZ_LUT_2D_MAX_INSTANCES);
    uz_LUT_2D_t *self = &instances_LUT_2D[instances_counter_LUT_2D];
    uz_assert(self->is_ready == false);
    instances_counter_LUT_2D++;
    self->is_ready = true;
    return self;
}

uz_LUT_2D_t *uz_LUT_2D_init(uz_array_float_t *breakpoints_x, uz_array_float_t *breakpoints_y, uz_array_float_t *data)
{
    uz_assert_not_NULL(breakpoints_x);
    uz_assert_not_NULL(breakpoints_y);
    uz_assert_not_NULL(data);
    uz_assert_not_NULL(breakpoints_x->data);
    uz_assert_not_NULL(breakpoints_y->data);
    uz_assert_not_NULL(data->data);
    uz_assert(breakpoints_x->length >= 2U);
    uz_assert(breakpoints_y->length >= 2U);
    uz_assert(data->length == (breakpoints_x->length * breakpoints_y->length));
    uz_assert(uz_LUT2D_check_breakpoints_increasing(breakpoints_x));
    uz_assert(uz_LUT2D_check_breakpoints_increasing(breakpoints_y));

    uz_LUT_2D_t *self = uz_LUT_2D_allocation();
    self->breakpoints_x = breakpoints_x;
    self->breakpoints_y = breakpoints_y;
    self->data = data;
    self->x_length = breakpoints_x->length;
    self->y_length = breakpoints_y->length;
    return self;
}

static bool uz_LUT2D_check_breakpoints_increasing(uz_array_float_t *breakpoints)
{
    uz_assert_not_NULL(breakpoints);
    uz_assert(breakpoints->length >= 2U);
    for (uint32_t i = 0U; i < breakpoints->length - 1U; i++)
    {
        float data = breakpoints->data[i];
        float next_data = breakpoints->data[i + 1U];
        if (data >= next_data)
        {
            return false;
        }
    }
    return true;
}

static float uz_LUT2D_clamp(float value, float min_value, float max_value)
{
    if (value <= min_value)
    {
        return min_value;
    }
    if (value >= max_value)
    {
        return max_value;
    }
    return value;
}

static uint32_t uz_LUT2D_find_interval(const uz_array_float_t *breakpoints, float input)
{
    if (input <= breakpoints->data[0U])
    {
        return 0U;
    }
    if (input >= breakpoints->data[breakpoints->length - 1U])
    {
        return breakpoints->length - 2U;
    }

    uint32_t idx = 0U;
    uint32_t left = 0U;
    uint32_t right = breakpoints->length - 2U; // search space is [0, length-2]

    while (left <= right)
    {
        uint32_t midpoint = left + ((right - left) >> 1);
        float bp_mid = breakpoints->data[midpoint];
        float bp_mid1 = breakpoints->data[midpoint + 1U];

        if ((input >= bp_mid) && (input < bp_mid1))
        {
            idx = midpoint;
            break;
        }
        if (input < bp_mid)
        {
            if (midpoint == 0U)
            {
                idx = 0U;
                break;
            }
            right = midpoint - 1U;
        }
        else
        {
            left = midpoint + 1U;
        }
    }
    return idx;
}

float uz_LUT_2D_get_value(uz_LUT_2D_t *self, float input_x, float input_y)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->x_length >= 2U);
    uz_assert(self->y_length >= 2U);

    float clamped_x = uz_LUT2D_clamp(input_x, self->breakpoints_x->data[0], self->breakpoints_x->data[self->x_length - 1U]);
    float clamped_y = uz_LUT2D_clamp(input_y, self->breakpoints_y->data[0], self->breakpoints_y->data[self->y_length - 1U]);

    uint32_t idx_x = uz_LUT2D_find_interval(self->breakpoints_x, clamped_x);
    uint32_t idx_y = uz_LUT2D_find_interval(self->breakpoints_y, clamped_y);

    float x0 = self->breakpoints_x->data[idx_x];
    float x1 = self->breakpoints_x->data[idx_x + 1U];
    float y0 = self->breakpoints_y->data[idx_y];
    float y1 = self->breakpoints_y->data[idx_y + 1U];

    float tx = (clamped_x - x0) / (x1 - x0);
    float ty = (clamped_y - y0) / (y1 - y0);

    uint32_t idx00 = (idx_y * self->x_length) + idx_x;
    uint32_t idx10 = (idx_y * self->x_length) + (idx_x + 1U);
    uint32_t idx01 = ((idx_y + 1U) * self->x_length) + idx_x;
    uint32_t idx11 = ((idx_y + 1U) * self->x_length) + (idx_x + 1U);

    float f00 = self->data->data[idx00];
    float f10 = self->data->data[idx10];
    float f01 = self->data->data[idx01];
    float f11 = self->data->data[idx11];

    float f0 = f00 + tx * (f10 - f00);
    float f1 = f01 + tx * (f11 - f01);

    return f0 + ty * (f1 - f0);
}

#endif
