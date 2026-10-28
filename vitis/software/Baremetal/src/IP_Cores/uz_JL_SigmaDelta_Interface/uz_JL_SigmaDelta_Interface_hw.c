#include "uz_JL_SigmaDelta_Interface_hw.h"

#include "uz_JL_SigmaDelta_Interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include <math.h>

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

void uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc(uint32_t base_address, bool switch_cont_disc)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + switch_cont_disc_Data_uz_JL_SigmaDelta_Interface, switch_cont_disc);
}

void uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle(uint32_t base_address, float dutycycle)
{
    uz_assert_not_zero(base_address);
    uint32_t raw_dutycycle = (uint32_t)(dutycycle *(1 << 15)); // clk_dutycycle port is sfix16_En15 in HDL (scaling 2^15)
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
    // HDL (addr_decoder): das Latch aller data_out_ps-Elemente erfolgt auf dem registrierten
    // Strobe-Bit; strobe_sw wird automatisch 0, sobald die Strobe-Adresse nicht mehr
    // beschrieben wird -> ein einzelner Write mit Bit0=1 genuegt, der zweite (false-)Write
    // ist redundant und spart eine AXI-Transaktion pro Aufruf (ISR-Pfad).
    uz_axi_write_bool(base_address + data_out_ps_Strobe_uz_JL_SigmaDelta_Interface, true);
    uz_axi_write_bool(base_address + data_out_ps_Strobe_uz_JL_SigmaDelta_Interface, false);
}

void uz_JL_SigmaDelta_Interface_hw_write_start_time_us(uint32_t base_address, float start_time_us)
{
    uz_assert_not_zero(base_address);
    uint16_t start_time_ticks = (uint16_t)roundf(start_time_us *100.0f);
    uz_axi_write_uint32(base_address + start_time_us_Data_uz_JL_SigmaDelta_Interface, start_time_ticks);
}

void uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid(uint32_t base_address, uint8_t delay_data_valid)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + delay_data_valid_Data_uz_JL_SigmaDelta_Interface, delay_data_valid);
}

bool uz_JL_SigmaDelta_Interface_hw_read_data_valid(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_bool(base_address + Data_valid_Data_uz_JL_SigmaDelta_Interface);
}

void uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods(uint32_t base_address, uint8_t sinc_sample_periods)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_uint32(base_address + sinc_sample_periods_Data_uz_JL_SigmaDelta_Interface, sinc_sample_periods);
}

void uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext(uint32_t base_address, bool use_clk_ext)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + use_clk_ext_Data_uz_JL_SigmaDelta_Interface, use_clk_ext);
}

void uz_JL_SigmaDelta_Interface_hw_reset_data_valid_cnt(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + rst_data_valid_cnt_Data_uz_JL_SigmaDelta_Interface, true);
    uz_axi_write_bool(base_address + rst_data_valid_cnt_Data_uz_JL_SigmaDelta_Interface, false);
}

uint8_t uz_JL_SigmaDelta_Interface_hw_read_data_valid_cnt(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return (uint8_t)uz_axi_read_uint32(base_address + data_valid_cnt_Data_uz_JL_SigmaDelta_Interface);
}

void uz_JL_SigmaDelta_Interface_hw_write_sel_pwm_trigger(uint32_t base_address, bool sel_pwm_trigger)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + sel_pwm_trigger_Data_uz_JL_SigmaDelta_Interface, sel_pwm_trigger);
}

void uz_JL_SigmaDelta_Interface_hw_write_i_ph_max(uint32_t base_address, int32_t i_ph_max)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + I_ph_max_Data_uz_JL_SigmaDelta_Interface, i_ph_max);
}

void uz_JL_SigmaDelta_Interface_hw_write_i_ph_min(uint32_t base_address, int32_t i_ph_min)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + I_ph_min_Data_uz_JL_SigmaDelta_Interface, i_ph_min);
}

void uz_JL_SigmaDelta_Interface_hw_write_u_dc_max(uint32_t base_address, int32_t u_dc_max)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + U_dc_max_Data_uz_JL_SigmaDelta_Interface, u_dc_max);
}

void uz_JL_SigmaDelta_Interface_hw_write_u_dc_min(uint32_t base_address, int32_t u_dc_min)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + U_dc_min_Data_uz_JL_SigmaDelta_Interface, u_dc_min);
}

void uz_JL_SigmaDelta_Interface_hw_write_en_udc(uint32_t base_address, bool en_udc)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + EN_Udc_Data_uz_JL_SigmaDelta_Interface, en_udc);
}

void uz_JL_SigmaDelta_Interface_hw_write_en_ph4(uint32_t base_address, bool en_ph4)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + EN_PH4_Data_uz_JL_SigmaDelta_Interface, en_ph4);
}

void uz_JL_SigmaDelta_Interface_hw_write_en_ocp(uint32_t base_address, bool en_ocp)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + EN_OCP_Data_uz_JL_SigmaDelta_Interface, en_ocp);
}

void uz_JL_SigmaDelta_Interface_hw_reset_flt(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_bool(base_address + FLT_Reset_Data_uz_JL_SigmaDelta_Interface, true);
    uz_axi_write_bool(base_address + FLT_Reset_Data_uz_JL_SigmaDelta_Interface, false);
}

uint32_t uz_JL_SigmaDelta_Interface_hw_read_flt_ps(uint32_t base_address)
{
    uz_assert_not_zero(base_address);
    return uz_axi_read_uint32(base_address + FLT_ps_Data_uz_JL_SigmaDelta_Interface);
}
