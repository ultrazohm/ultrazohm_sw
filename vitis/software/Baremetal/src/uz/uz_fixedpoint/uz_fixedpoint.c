#include "uz_fixedpoint.h"

#include "../uz_AXI.h"
#include "../uz_HAL.h"

float uz_fixedpoint_axi_read(uint32_t base_address, struct uz_fixedpoint_definition_t fixed_data)
{
    uz_assert_not_zero_uint32(base_address);

    uint32_t register_value = uz_axi_read_uint32(base_address);
    float output = ldexpf((float)register_value, -fixed_data.fractional_bits);

    return output;
}

void uz_fixedpoint_axi_write(uint32_t base_address,float data, struct uz_fixedpoint_definition_t fixed_def)
{
    uz_assert_not_zero_uint32(base_address);

    uint32_t fixed_data=((uint32_t)ldexpf(data, fixed_def.fractional_bits))

    uz_axi_write_uint32(base_address,data);

}