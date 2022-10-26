#include "uz_delay_compensation_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_delay_compensation_8_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_delay_compensation_8_set_psiPM(uint32_t base_address, float psiPM)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + psiPM_AXI_Data_parallel_8_delay_compensation, psiPM);
}

void uz_delay_compensation_8_set_Lq(uint32_t base_address, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Lq_AXI_Data_parallel_8_delay_compensation, Lq);
}

void uz_delay_compensation_8_set_Ld(uint32_t base_address, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Ld_AXI_Data_parallel_8_delay_compensation, Ld);
}

void uz_delay_compensation_8_set_Rs(uint32_t base_address, float Rs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + Rs_AXI_Data_parallel_8_delay_compensation, Rs);
}

void uz_delay_compensation_8_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ld = SampleTime/Ld;
    uz_axi_write_float(base_address + SampleTime_div_Ld_AXI_Data_parallel_8_delay_compensation, SampleTime_div_Ld);
}

void uz_delay_compensation_8_set_pole_pairs(uint32_t base_address, float pole_pairs)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    uz_axi_write_float(base_address + pole_pairs_AXI_Data_parallel_8_delay_compensation, pole_pairs);
}

void uz_delay_compensation_8_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lq = SampleTime/Lq;
    uz_axi_write_float(base_address + SampleTime_div_Lq_AXI_Data_parallel_8_delay_compensation, SampleTime_div_Lq);
}

void uz_delay_compensation_8_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Lx = SampleTime/Lx;
    uz_axi_write_float(base_address + SampleTime_div_Lx_AXI_Data_parallel_8_delay_compensation, SampleTime_div_Lx);
}

void uz_delay_compensation_8_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly)
{
    uz_assert_not_zero_uint32(base_address);
    //single
    float SampleTime_div_Ly = SampleTime/Ly;
    uz_axi_write_float(base_address + SampleTime_div_Ly_AXI_Data_parallel_8_delay_compensation, SampleTime_div_Ly);
}

float uz_delay_compensation_8_get_id_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + id_k_1_AXI_Data_parallel_8_delay_compensation, fixedpoint_definition);
}

float uz_delay_compensation_8_get_iq_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + iq_k_1_AXI_Data_parallel_8_delay_compensation, fixedpoint_definition);
}

float uz_delay_compensation_8_get_ix_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + ix_k_1_AXI_Data_parallel_8_delay_compensation, fixedpoint_definition);
}

float uz_delay_compensation_8_get_iy_k_1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + iy_k_1_AXI_Data_parallel_8_delay_compensation, fixedpoint_definition);
}