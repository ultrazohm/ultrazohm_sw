#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_fixedpoint.h"
#include "mock_uz_AXI.h"
#include "mock_uz_HAL.h"
#include <math.h>

#define TEST_ADDRESS 0x00FF

void setUp(void)
{
}

void tearDown(void)
{
}

const struct uz_fixedpoint_definition_t fixed_def = {
    .is_signed = true,
    .fractional_bits = 4,
    .integer_bits = 5};

void test_uz_fixedpoint_get_precision(void)
{
    // Precision of the fixed point variable is determined by the number of fractional bits
    // Precision is calculated by 2^(- number_of_fractional_bits)
    float expected_precision = ldexpf(1.0f, -(int)fixed_def.fractional_bits); // 2^(-4)=0.0625
    float precision = uz_fixedpoint_get_precision(fixed_def);
    TEST_ASSERT_EQUAL_FLOAT(expected_precision, precision);
}

void test_uz_fixedpoint_get_max_representable_value(void)
{
    float expected_max = ldexpf(1.0f, (int)fixed_def.integer_bits); // 2^5=32
    float returned_max = uz_fixedpoint_get_max_representable_value(fixed_def);
    TEST_ASSERT_EQUAL_FLOAT(expected_max, returned_max);
}

void test_uz_fixedpoint_get_min_representable_value_signed(void)
{
    float expected_min = ldexpf(-1.0f, (int)fixed_def.integer_bits); // -1*2^5=-32
    float returned_min = uz_fixedpoint_get_min_representable_value(fixed_def);
    TEST_ASSERT_EQUAL_FLOAT(expected_min, returned_min);
}

void test_uz_fixedpoint_get_min_representable_value_unsigned(void)
{
    struct uz_fixedpoint_definition_t fixed_def_unsigned = {
        .is_signed = false,
        .fractional_bits = 4,
        .integer_bits = 5};
    float expected_min = 0.0f; // unsigned -> min value is zero
    float returned_min = uz_fixedpoint_get_min_representable_value(fixed_def_unsigned);
    TEST_ASSERT_EQUAL_FLOAT(expected_min, returned_min);
}

void test_uz_fixedpoint_axi_write(void)
{

    float write_value = -1.0f;
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    uint32_t write_fixed = uz_fixedpoint_convert_signed_to_float(write_value,def); // first three bits are integer
    uz_axi_write_int32_Expect(TEST_ADDRESS, write_fixed);
    uz_fixedpoint_axi_write(TEST_ADDRESS, write_value, def);
}

void test_uz_fixedpoint_axi_read(void)
{
    float expected_return_value = 1.0f;
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    uint32_t return_value_fixed = 1 << def.fractional_bits; // first three bits are integer
    uz_axi_read_uint32_ExpectAndReturn(TEST_ADDRESS, return_value_fixed);
    float return_value = uz_fixedpoint_axi_read(TEST_ADDRESS, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value, return_value);
}

void test_uz_fixedpoint_check_limits_above_max(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    // all values that are above 2^3=9 or below -9 should trigger an assertion
    float above_max = 100.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_check_limits(above_max, def));
}

void test_uz_fixedpoint_check_limits_below_min(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    // all values that are above 2^3=9 or below -9 should trigger an assertion
    float below_min = -100.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_check_limits(below_min, def));
}

void test_uz_fixedpoint_check_limits_sign(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 3,
        .integer_bits = 3};
    // Fixed point definition is unsigned, thus this is below min and fails
    float below_min = -100.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_check_limits(below_min, def));
}

void test_uz_fixedpoint_write_fail_limits_too_big(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 3,
        .integer_bits = 3};
    float too_large_data = 1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_axi_write(TEST_ADDRESS, too_large_data, def));
}

void test_uz_fixedpoint_write_fail_limits_too_small(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    float too_small_data = -1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_axi_write(TEST_ADDRESS, too_small_data, def));
}

void test_uz_fixedpoint_read_fail_limits_too_small(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    uz_axi_read_uint32_ExpectAndReturn(TEST_ADDRESS, 0x11111111U); // Some random value that is large than sfix3_3 can represent
    TEST_ASSERT_FAIL_ASSERT(uz_fixedpoint_axi_read(TEST_ADDRESS, def));
}

void test_uz_fixedpoint_convert_to_float_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 3,
        .integer_bits = 3};
    uint32_t testinput = (1) << 3;
    float return_value=uz_fixedpoint_convert_to_float(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(1.0f,return_value);
}

void test_uz_fixedpoint_convert_to_float_negative(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 5,
        .integer_bits = 16};
    //uint32_t testinput = 0b111111111111111111111111111110000;
    int32_t testinput= ((int32_t)ldexpf(-4.0f, def.fractional_bits));
    float return_value=uz_fixedpoint_convert_signed_to_float(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f,return_value);
}

#endif // TEST
