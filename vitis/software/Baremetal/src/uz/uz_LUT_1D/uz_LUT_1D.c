#include "../uz_global_configuration.h"
#if UZ_LUT_1D_MAX_INSTANCES > 0U

#include "uz_LUT_1D.h"
#include <stdbool.h>
#include "../uz_HAL.h"

static bool uz_LUT1D_check_breakpoints_increasing(uz_array_float_t *breakpoints);

typedef struct uz_LUT_1D_t
{
    bool is_ready;
    uz_array_float_t *breakpoints;
    uz_array_float_t *data;
    uint32_t length;
} uz_LUT_1D_t;

static uint32_t instances_counter_LUT_1D = 0;

static uz_LUT_1D_t instances_LUT_1D[UZ_LUT_1D_MAX_INSTANCES] = {0};

/**
 * @brief Memory allocation of the uz_LUT_1D_t struct
 *
 * @return Pointer to uz_LUT_1D_t instance
 */
static uz_LUT_1D_t *uz_LUT_1D_allocation(void);

static uz_LUT_1D_t *uz_LUT_1D_allocation(void)
{
    uz_assert(instances_counter_LUT_1D < UZ_LUT_1D_MAX_INSTANCES);
    uz_LUT_1D_t *self = &instances_LUT_1D[instances_counter_LUT_1D];
    uz_assert(self->is_ready == false);
    instances_counter_LUT_1D++;
    self->is_ready = true;
    return (self);
}

uz_LUT_1D_t *uz_LUT_1D_init(uz_array_float_t *breakpoints, uz_array_float_t *data)
{
    uz_assert_not_NULL(breakpoints);
    uz_assert_not_NULL(data);
    uz_assert(breakpoints->length == data->length);
    uz_assert(uz_LUT1D_check_breakpoints_increasing(breakpoints));
    uz_LUT_1D_t *self = uz_LUT_1D_allocation();
    self->breakpoints = breakpoints;
    self->data = data;
    self->length = breakpoints->length;
    return self;
}

static bool uz_LUT1D_check_breakpoints_increasing(uz_array_float_t *breakpoints)
{
    for (uint32_t i = 0U; i < breakpoints->length - 1; i++)
    {
        float data = breakpoints->data[i];
        float next_data = breakpoints->data[i + 1U];
        if (data >= next_data  )
        {
            return false;
        }
    }
    return true;
}

float uz_LUT_1D_get_value(uz_LUT_1D_t *self, float input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float output = 0.0f;
    // Check if input is out of bounds
    if (input <= self->breakpoints->data[0])
    {
        return self->data->data[0];
    }
    if (input >= self->breakpoints->data[self->length - 1U])
    {
        return self->data->data[self->length - 1U];
    }
    // Find the interval for interpolation using binary search
    uint32_t idx = 0U;
    if (self->length > 1U)
    {
        uint32_t left = 0U;
        uint32_t right = self->length - 2U; // search space is [0, length-2]
        while (left <= right)
        {
            uint32_t midpoint = left + ((right - left) >> 1);
            float bp_mid = self->breakpoints->data[midpoint];
            float bp_mid1 = self->breakpoints->data[midpoint + 1U];
            if (input >= bp_mid && input < bp_mid1)
            {
                idx = midpoint;
                break;
            }
            else if (input < bp_mid)
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
        float x0 = self->breakpoints->data[idx];
        float x1 = self->breakpoints->data[idx + 1U];
        float y0 = self->data->data[idx];
        float y1 = self->data->data[idx + 1U];
        if (x1 == x0)
        {
            uz_assert(false); // Avoid division by zero, return y0 if breakpoints are the same
        }
        float slope = (y1 - y0) / (x1 - x0);
        output = y0 + slope * (input - x0);
    }
    else
    {
        output = self->data->data[0];
    }
    return output;
}
#endif