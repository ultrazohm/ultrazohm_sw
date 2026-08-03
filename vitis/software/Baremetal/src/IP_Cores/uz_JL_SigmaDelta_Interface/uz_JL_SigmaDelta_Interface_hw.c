#include "uz_JL_SigmaDelta_Interface_hw.h"

#include "uz_JL_SigmaDelta_Interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_JL_SigmaDelta_Interface_hw_write_clk_ratio(uint32_t base_address, uint16_t clk_ratio)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + clk_ratio_Data_uz_JL_SigmaDelta_Interface, clk_ratio);
}

void uz_JL_SigmaDelta_Interface_hw_write_switch_edge(uint32_t base_address, uint8_t switch_edge)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + switch_edge_Data_uz_JL_SigmaDelta_Interface, switch_edge);
}


void uz_JL_SigmaDelta_Interface_hw_write_data_delay(uint32_t base_address, uint16_t filt_input_delay)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + filt_input_delay_Data_uz_JL_SigmaDelta_Interface, filt_input_delay);
}

void uz_JL_SigmaDelta_Interface_hw_write_dezimation(uint32_t base_address, uint16_t dezimation)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + Dezimation_Data_uz_JL_SigmaDelta_Interface, dezimation);
}

void uz_JL_SigmaDelta_Interface_hw_write_clk_dsw_en(uint32_t base_address, bool dsw_clk_en)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + DSW_clk_en_Data_uz_JL_SigmaDelta_Interface, dsw_clk_en);
}

void uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(uint32_t base_address, float dutycycle)
{
    uz_assert_not_zero(base_address);
    uint32_t raw_dutycycle = (uint32_t)(dutycycle *(1 << 10));
    uz_axi_write_uint32(base_address + clk_dutycycle_Data_uz_JL_SigmaDelta_Interface, raw_dutycycle);
}

int32_t uz_JL_SigmaDelta_Interface_hw_read_data_out_U(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+SigmaDelta_Interface_data_out_U);
}

int32_t uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+SigmaDelta_Interface_data_out_PH1);
}

int32_t uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+SigmaDelta_Interface_data_out_PH2);
}

int32_t uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+SigmaDelta_Interface_data_out_PH3);
}

int32_t uz_JL_SigmaDelta_Interface_hw_read_data_out_PH4(uint32_t base_address){

    uz_assert_not_zero(base_address);
    return uz_axi_read_int32(base_address+SigmaDelta_Interface_data_out_PH4);
}

void uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+data_out_ps_Strobe_uz_JL_SigmaDelta_Interface,true);
    uz_axi_write_bool(base_address+data_out_ps_Strobe_uz_JL_SigmaDelta_Interface,false);
}
