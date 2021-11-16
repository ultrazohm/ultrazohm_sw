#include "uz_fixedpoint.h"

#include "../uz_AXI.h"
#include "../uz_HAL.h"
#include <math.h>

static float convert_data_and_round(float data, struct uz_fixedpoint_definition_t fixed_data);

float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input)
{
    return ldexpf(1.0f, -input.fractional_bits); // 1*2^(-fractional_bits)
}

float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input)
{
    float max_value = 0.0f;
    if (input.is_signed)
    {
        max_value = ldexpf(1.0f, input.integer_bits - 1) - uz_fixedpoint_get_precision(input);
    }
    else
    {
        max_value = ldexpf(1.0f, input.integer_bits) - uz_fixedpoint_get_precision(input);
    }
    return max_value;
}

float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input)
{
    float min_value = 0.0f;
    if (input.is_signed)
    {
        min_value = ldexpf(-1.0f, input.integer_bits - 1);
    }
    return (min_value);
}

void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32 >= (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    uz_assert(data <= uz_fixedpoint_get_max_representable_value(fixedpoint_definition));
    uz_assert(data >= uz_fixedpoint_get_min_representable_value(fixedpoint_definition));
}

float uz_fixedpoint_convert_unsigned_to_float(uint32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(!fixedpoint_definition.is_signed);
    float input_float = (float)input;
    float output = ldexpf(input_float, -fixedpoint_definition.fractional_bits);
    return output;
}

float uz_fixedpoint_convert_signed_to_float(int32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(fixedpoint_definition.is_signed);
    float input_float = (float)input;
    float output = ldexpf(input_float, -fixedpoint_definition.fractional_bits);
    return output;
}

uint32_t uz_fixedpoint_convert_to_unsigned_fixed(float data, struct uz_fixedpoint_definition_t fixed_data)
{
    uz_assert(!fixed_data.is_signed);
    uz_fixedpoint_check_limits(data, fixed_data);
    uint32_t unsigned_output = (uint32_t)convert_data_and_round(data,fixed_data);
    return unsigned_output;
}

int32_t uz_fixedpoint_convert_to_signed_fixed(float data, struct uz_fixedpoint_definition_t fixed_data)
{
    uz_assert(fixed_data.is_signed);
    uz_fixedpoint_check_limits(data, fixed_data);
    int32_t signed_output = (int32_t)convert_data_and_round(data,fixed_data);
    return signed_output;
}

static float convert_data_and_round(float data, struct uz_fixedpoint_definition_t fixed_data)
{
    float output = ldexpf(data, fixed_data.fractional_bits);
    output=roundf(output); // round to nearest integer since a cast only truncates (drops) the fractional
    return output;
}

float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    float read_value = 0.0f;
    if (fixedpoint_definition.is_signed)
    {
        int32_t register_value_signed = uz_axi_read_int32(memory_address);
        read_value = uz_fixedpoint_convert_signed_to_float(register_value_signed, fixedpoint_definition);
    }
    else
    {
        uint32_t register_value_unsigned = uz_axi_read_uint32(memory_address);
        read_value = uz_fixedpoint_convert_unsigned_to_float(register_value_unsigned, fixedpoint_definition);
    }
    uz_fixedpoint_check_limits(read_value, fixedpoint_definition);
    return read_value;
}

void uz_fixedpoint_axi_write(uint32_t memory_address, float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    uz_fixedpoint_check_limits(data, fixedpoint_definition);
    if (fixedpoint_definition.is_signed)
    {
        int32_t fixed_point_data_signed = uz_fixedpoint_convert_to_signed_fixed(data, fixedpoint_definition);
        uz_axi_write_int32(memory_address, fixed_point_data_signed);
    }
    else
    {
        uint32_t fixed_point_data_unsigned = uz_fixedpoint_convert_to_unsigned_fixed(data, fixedpoint_definition);
        uz_axi_write_uint32(memory_address, fixed_point_data_unsigned);
    }
}