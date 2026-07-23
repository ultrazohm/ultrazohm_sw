#include "uz_JL_SDDemod_hw.h"

#include "uz_JL_SDDemod_hwAddresses.h"
#include "../../uz/uz_AXI.h"


void uz_JL_SDDemod_hw_write_dezi_U(uint32_t base_address, uint16_t dezimation)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + Dezimation_U_Data_uz_JL_SDDemod, dezimation);
}

void uz_JL_SDDemod_hw_write_data_delay(uint32_t base_address, uint16_t filt_input_delay)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + filt_input_delay_Data_uz_JL_SDDemod, filt_input_delay);
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

void uz_JL_SDDemod_hw_write_calib_ads_en(uint32_t base_address, bool calib_en)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + calibration_en_Data_uz_JL_SDDemod, calib_en);
}

void uz_JL_SDDemod_hw_write_clk_dsw_en(uint32_t base_address, bool dsw_clk_en)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + DSW_clk_en_Data_uz_JL_SDDemod, dsw_clk_en);
}

void uz_JL_SDDemod_hw_write_clk_dutycycle(uint32_t base_address, float dutycycle)
{
    uz_assert_not_zero(base_address);
    uint32_t raw_dutycycle = (uint32_t)(dutycycle *(1 << 10));
    uz_axi_write_uint32(base_address + clk_dutycycle_Data_uz_JL_SDDemod, raw_dutycycle);
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
