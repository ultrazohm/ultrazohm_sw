#include "uz_fixedpoint.h"

#include "../uz_AXI.h"
#include "../uz_HAL.h"
#include <math.h>


float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input)
{
    uz_assert(32U > (input.fractional_bits + input.integer_bits));
    return ldexpf(1, -(int)input.fractional_bits); // 1*2^(-fractional_bits)
}

float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input)
{
    uz_assert(32U > (input.fractional_bits + input.integer_bits));
    return ldexpf(1, (int)input.integer_bits);
}

float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input)
{
    uz_assert(32U > (input.fractional_bits + input.integer_bits));
    float min_value = 0.0f;
    if (input.is_signed)
    {
        min_value = (-1.0f) * uz_fixedpoint_get_max_representable_value(input);
    }
    return (min_value);
}

void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32U > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    uz_assert(data <= uz_fixedpoint_get_max_representable_value(fixedpoint_definition));
    uz_assert(data >= uz_fixedpoint_get_min_representable_value(fixedpoint_definition));
}

float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    uz_assert(32U > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    uint32_t register_value = uz_axi_read_uint32(memory_address);
    float read_value=uz_fixedpoint_convert_to_float(register_value, fixedpoint_definition);
    uz_fixedpoint_check_limits(read_value,fixedpoint_definition);
    return read_value;
}

void uz_fixedpoint_axi_write(uint32_t memory_address, float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    uz_fixedpoint_check_limits(data,fixedpoint_definition);
    uint32_t fixed_data = uz_fixedpoint_convert_to_fixed(data, fixedpoint_definition);
    uz_axi_write_uint32(memory_address, fixed_data);
}

float uz_fixedpoint_convert_to_float(uint32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32U > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    return ldexpf((float)input, -fixedpoint_definition.fractional_bits); // 2^(-fractional bits)
}

uint32_t uz_fixedpoint_convert_to_fixed(float data, struct uz_fixedpoint_definition_t fixed_data)
{
    uz_fixedpoint_check_limits(data,fixed_data);
    return ((uint32_t)ldexpf(data, fixed_data.fractional_bits));
}
