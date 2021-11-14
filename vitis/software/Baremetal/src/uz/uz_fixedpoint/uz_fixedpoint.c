#include "uz_fixedpoint.h"

#include "../uz_AXI.h"
#include "../uz_HAL.h"
#include <math.h>

float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input)
{
    return ldexpf(1.0f, -input.fractional_bits); // 1*2^(-fractional_bits)
}

float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input)
{
    float max_value=0.0f;
    if(input.is_signed){
        max_value=ldexpf(1.0f,input.integer_bits-1)-uz_fixedpoint_get_precision(input);
    }else{
        max_value=ldexpf(1.0f,input.integer_bits)-uz_fixedpoint_get_precision(input);
    }
    return max_value;
}

float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input)
{
    float min_value = 0.0f;
    if (input.is_signed)
    {
        min_value = ldexpf(-1.0f,input.integer_bits-1);
    }
    return (min_value);
}

void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32 > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    uz_assert(data <= uz_fixedpoint_get_max_representable_value(fixedpoint_definition));
    uz_assert(data >= uz_fixedpoint_get_min_representable_value(fixedpoint_definition));
}

float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    uz_assert(32 > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    uint32_t register_value = uz_axi_read_uint32(memory_address);
    float read_value = uz_fixedpoint_convert_to_float(register_value, fixedpoint_definition);
    uz_fixedpoint_check_limits(read_value, fixedpoint_definition);
    return read_value;
}

void uz_fixedpoint_axi_write(uint32_t memory_address, float data, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert_not_zero_uint32(memory_address);
    uz_fixedpoint_check_limits(data, fixedpoint_definition);
    if (fixedpoint_definition.is_signed)
    {
        int32_t fixed_data_signed = uz_fixedpoint_convert_signed_to_float(data, fixedpoint_definition);
        uz_axi_write_int32(memory_address, fixed_data_signed);
    }
    else
    {

        uint32_t fixed_data_unsigned = uz_fixedpoint_convert_to_fixed(data, fixedpoint_definition);
        uz_axi_write_uint32(memory_address, fixed_data_unsigned);
    }
}

float uz_fixedpoint_convert_to_float(uint32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32 > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    float input_float = (float)input;
    float output = ldexpf(input_float, -fixedpoint_definition.fractional_bits);
    return output; // 2^(-fractional bits)
}

float uz_fixedpoint_convert_signed_to_float(int32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition)
{
    uz_assert(32 > (fixedpoint_definition.fractional_bits + fixedpoint_definition.integer_bits));
    float input_float = (float)input;
    float output = ldexpf(input_float, -fixedpoint_definition.fractional_bits);
    return output; // 2^(-fractional bits)
}

uint32_t uz_fixedpoint_convert_to_fixed(float data, struct uz_fixedpoint_definition_t fixed_data)
{
    uz_fixedpoint_check_limits(data, fixed_data);
    return ((uint32_t)ldexpf(data, fixed_data.fractional_bits));
}
