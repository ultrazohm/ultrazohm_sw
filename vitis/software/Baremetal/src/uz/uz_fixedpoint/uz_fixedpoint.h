#ifndef UZ_FIXEDPOINT_H
#define UZ_FIXEDPOINT_H

#include <stdint.h>
#include <stdbool.h>

struct uz_fixedpoint_definition_t{
    const bool is_signed;
    const uint32_t fractional_bits;
    const uint32_t integer_bits;
};

struct uz_fixedpoint_t{
    uint32_t raw_value;
    struct uz_fixedpoint_definition_t definition;
}

float uz_fixedpoint_convert_to_float(struct uz_fixedpoint_t input);
struct uz_fixedpoint_t uz_fixedpoint_convert_to_fixed(float data, struct uz_fixedpoint_t fixed_data);

float uz_fixedpoint_get_precision(struct uz_fixedpoint_t input);
float uz_fixedpoint_get_max_representable_value(struct uz_fixedpoint_t input);
float uz_fixedpoint_get_min_representable_value(struct uz_fixedpoint_t input);

float uz_fixedpoint_axi_read(uint32_t base_address, struct uz_fixedpoint_definition_t fixed_data);
void uz_fixedpoint_axi_write(uint32_t base_address, struct uz_fixedpoint_definition_t fixed_data);

#endif // UZ_FIXEDPOINT_H
