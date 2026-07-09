
#include "uz_JL_SDDemod_hw.h"

#include "uz_JL_SDDemod_hwAddresses.h"
#include "../../uz/uz_AXI.h"


void uz_JL_SDDemod_hw_write_dezi_U(uint32_t base_address, uint16_t dezimation)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + Dezimation_U_Data_uz_JL_SDDemod, dezimation);
}

void uz_JL_SDDemod_hw_write_dezi_I(uint32_t base_address, uint16_t dezimation)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + Dezimation_I_Data_uz_JL_SDDemod, dezimation);
}

void uz_JL_SDDemod_hw_write_switch_edge(uint32_t base_address, bool switch_edge)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + switch_edge_Data_uz_JL_SDDemod, switch_edge);
}

void uz_JL_SDDemod_hw_write_clk_ratio(uint32_t base_address, uint16_t clk_ratio)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + clk_ratio_Data_uz_JL_SDDemod, clk_ratio);
}

int32_t uz_JL_SDDemod_hw_read_data_out_ps_U(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_U_Data_uz_JL_SDDemod);
}

int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH1(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_PH1_Data_uz_JL_SDDemod);
}

int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH2(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_PH2_Data_uz_JL_SDDemod);
}

int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH3(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_PH3_Data_uz_JL_SDDemod);
}

int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH4(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+data_out_ps_PH4_Data_uz_JL_SDDemod);
}