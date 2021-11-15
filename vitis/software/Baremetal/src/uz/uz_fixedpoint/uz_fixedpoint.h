#ifndef UZ_FIXEDPOINT_H
#define UZ_FIXEDPOINT_H

#include <stdint.h>
#include <stdbool.h>

struct uz_fixedpoint_definition_t{
    const bool is_signed; /**< Determines if the fixed point value is signed or unsigned */
    const int32_t fractional_bits; /**< Number of bits for the the fraction */
    const int32_t integer_bits; /**< Number of bits for the integer part */
};

float uz_fixedpoint_axi_read(uint32_t memory_address, struct uz_fixedpoint_definition_t fixedpoint_definition);
void uz_fixedpoint_axi_write(uint32_t memory_address,float data, struct uz_fixedpoint_definition_t fixedpoint_definition);

void uz_fixedpoint_check_limits(float data, struct uz_fixedpoint_definition_t fixedpoint_definition);
float uz_fixedpoint_get_precision(struct uz_fixedpoint_definition_t input);
float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_definition_t input);
float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_definition_t input);

float uz_fixedpoint_convert_unsigned_to_float(uint32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition);
float uz_fixedpoint_convert_signed_to_float(int32_t input, struct uz_fixedpoint_definition_t fixedpoint_definition);

uint32_t uz_fixedpoint_convert_to_unsigned_fixed(float data, struct uz_fixedpoint_definition_t fixed_data);
int32_t uz_fixedpoint_convert_to_signed_fixed(float data, struct uz_fixedpoint_definition_t fixed_data);

#endif // UZ_FIXEDPOINT_H
