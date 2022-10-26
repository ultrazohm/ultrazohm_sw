#include "uz_vsd_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_vsd_8_hwAdresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_vsd_8_hw_set_thetaOffset(uint32_t base_address, float thetaOffset)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 20,
        .integer_bits = 4};
    uz_fixedpoint_axi_write(base_address + theta_el_offset__Data_parallel_8_VSD_and_Park, thetaOffset, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_a1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_a1_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_b1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_b1_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_c1(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_c1_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_a2(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_a2_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_b2(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_b2_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}

float uz_vsd_8_hw_get_i_c2(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_c2_axi_Data_parallel_8_VSD_and_Park, fixedpoint_definition);
}