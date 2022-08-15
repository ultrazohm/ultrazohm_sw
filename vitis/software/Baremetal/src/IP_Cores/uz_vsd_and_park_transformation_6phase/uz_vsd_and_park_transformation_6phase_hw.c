#include "uz_vsd_and_park_transformation_6phase_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_vsd_and_park_transformation_6phase_hwAddresses.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

void uz_vsd_and_park_transformation_6phase_hw_set_thetaOffset(uint32_t base_address, float thetaOffset)
{
    uz_assert_not_zero_uint32(base_address);
    //sfix24_En20
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .is_signed = true,
        .fractional_bits = 20,
        .integer_bits = 4};
    uz_fixedpoint_axi_write(base_address + theta_el_offset__Data_VSD_and_Park_transformation, thetaOffset, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_alpha(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_alpha_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_beta(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_beta_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_d(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_d_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_q(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_q_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_x(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_x_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_y(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_y_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_0_plus(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_0_plus_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}

float uz_vsd_and_park_transformation_6phase_hw_get_i_0_minus(uint32_t base_address)
{
    uz_assert_not_zero_uint32(base_address);
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 7,
        .is_signed = true};
    return uz_fixedpoint_axi_read(base_address + i_0_minus_axi_Data_VSD_and_Park_transformation, fixedpoint_definition);
}