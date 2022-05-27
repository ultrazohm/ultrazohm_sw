#include "uz_trans_dq_alphabeta_123_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_trans_dq_alphabeta_123_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_trans_dq_alphabeta_123_hw_set_thetaOffset(uint32_t base_address, float thetaOffset)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 20,
        .integer_bits = 4};
    uz_fixedpoint_axi_write(base_address + theta_offset_AXI_Data_Trans_dq_alphabeta_123_ip, thetaOffset, fixedpoint_definition);
}

void uz_trans_dq_alphabeta_123_hw_set_idref(uint32_t base_address, float idref)
{
     uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + Id_ref_AXI_Data_Trans_dq_alphabeta_123_ip, idref, fixedpoint_definition);  
}

void uz_trans_dq_alphabeta_123_hw_set_iqref(uint32_t base_address, float iqref)
{
     uz_assert_not_zero_uint32(base_address);
    //sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 11,
        .integer_bits = 7};
    uz_fixedpoint_axi_write(base_address + Iq_ref_AXI_Data_Trans_dq_alphabeta_123_ip, iqref, fixedpoint_definition);  
}

float uz_trans_dq_alphabeta_123_hw_get_i1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};

    float i1 = uz_fixedpoint_axi_read(base_address + i1_AXI_Data_Trans_dq_alphabeta_123_ip, fixedpoint_definition);
    return i1;
}

float uz_trans_dq_alphabeta_123_hw_get_i2(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float i2 = uz_fixedpoint_axi_read(base_address + i2_AXI_Data_Trans_dq_alphabeta_123_ip, fixedpoint_definition);
    return i2;
}

float uz_trans_dq_alphabeta_123_hw_get_i3(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float i3 = uz_fixedpoint_axi_read(base_address + i3_AXI_Data_Trans_dq_alphabeta_123_ip, fixedpoint_definition);
    return i3;
}

float uz_trans_dq_alphabeta_123_hw_get_ialpha(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float ialpha = uz_fixedpoint_axi_read(base_address + ialpha_AXI_Data_Trans_dq_alphabeta_123_ip, fixedpoint_definition);
    return ialpha;
}

float uz_trans_dq_alphabeta_123_hw_get_ibeta(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    float ibeta = uz_fixedpoint_axi_read(base_address + ibeta_AXI_Data_Trans_dq_alphabeta_123_ip, fixedpoint_definition);
    return ibeta;
}