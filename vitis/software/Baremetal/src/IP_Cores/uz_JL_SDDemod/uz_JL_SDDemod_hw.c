
#include "uz_JL_SDDemod_hw.h"

#include "uz_JL_SDDemod_hwAddresses.h"
#include "../../uz/uz_AXI.h"


void uz_JL_SDDemod_hw_write_R_axi(uint32_t base_address, uint16_t R_axi)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + Dezimation_Data_uz_JL_SDDemod, R_axi);
}

void uz_JL_SDDemod_hw_write_switch_clk(uint32_t base_address, bool switch_clk)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + switch_clk_Data_uz_JL_SDDemod, switch_clk);
}

void uz_JL_SDDemod_hw_write_clk_ratio(uint32_t base_address, uint16_t clk_ratio)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + clk_ratio_Data_uz_JL_SDDemod, clk_ratio);
}

int32_t uz_JL_SDDemod_hw_read_data(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_Data_uz_JL_SDDemod);
}