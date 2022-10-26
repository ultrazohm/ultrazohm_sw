#include "uz_min_cost_function_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_8_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

int32_t uz_min_cost_function_8_hw_get_Index_out_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // int32
    return uz_axi_read_int32(base_address + Index_AXI_Data_parallel_8_min_cost_function);
}

float uz_min_cost_function_8_hw_get_J_out_AXI(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix24_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 9,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + J_AXI_Data_parallel_8_min_cost_function, fixedpoint_definition);
}