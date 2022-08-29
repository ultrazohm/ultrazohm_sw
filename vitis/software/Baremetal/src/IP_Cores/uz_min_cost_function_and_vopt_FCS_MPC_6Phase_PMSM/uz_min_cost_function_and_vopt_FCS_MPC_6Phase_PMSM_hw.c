#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(uint32_t base_address, _Bool use_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    // bool
     uz_axi_write_bool(base_address + use_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, use_AXI);
}

void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(uint32_t base_address, float J_in_AXI)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix20_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 9};
    uz_fixedpoint_axi_write(base_address + J_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase, J_in_AXI, fixedpoint_definition);
}