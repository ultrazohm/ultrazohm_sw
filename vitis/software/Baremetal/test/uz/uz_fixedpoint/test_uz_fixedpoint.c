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

void test_uz_fixedpoint_get_precision(void)
{
    // Precision of the fixed point variable is determined by the number of fractional bits
    // Precision is calculated by 2^(- number_of_fractional_bits)
    const struct uz_fixedpoint_definition_t fixed_def = {
        .is_signed = true,
        .fractional_bits = 4,
        .integer_bits = 5,
        .rounding_type=round_trunc};

    float expected_precision = 0.0625f; // 2^(-4)=0.0625
    float precision = uz_fixedpoint_get_precision(fixed_def);
    TEST_ASSERT_EQUAL_FLOAT(expected_precision, precision);
}

// Unsinged values min/max
void test_uz_fixedpoint_get_max_representable_value_signed(void)
{
    const struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 5,
        .integer_bits = 11};
    float expected_max = 1023.96875f; // 2^(11-1)-2^(-5)
    float returned_max = uz_fixedpoint_get_max_representable_value(def);
    TEST_ASSERT_EQUAL_FLOAT(expected_max, returned_max);
}

void test_uz_fixedpoint_get_min_representable_value_signed(void)
{
    const struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 5,
        .integer_bits = 11};
    float expected_min = -1024.0f; // -1*2^(11-1)=-1024
    float returned_min = uz_fixedpoint_get_min_representable_value(def);
    TEST_ASSERT_EQUAL_FLOAT(expected_min, returned_min);
}

// Unsigned values min/max

void test_uz_fixedpoint_get_max_representable_value_unsigned(void)
{
    const struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 5,
        .integer_bits = 11};
    float expected_max = 2047.96875; //2^{11}-0.0312=2047.96875
    float returned_max = uz_fixedpoint_get_max_representable_value(def);
    TEST_ASSERT_EQUAL_FLOAT(expected_max, returned_max);
}

void test_uz_fixedpoint_get_min_representable_value_unsigned(void)
{
    struct uz_fixedpoint_definition_t fixed_def_unsigned = {
        .is_signed = false,
        .fractional_bits = 5,
        .integer_bits = 11};
    float expected_min = 0.0f; // unsigned -> min value is zero
    float returned_min = uz_fixedpoint_get_min_representable_value(fixed_def_unsigned);
    TEST_ASSERT_EQUAL_FLOAT(expected_min, returned_min);
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

// Conversion functions
//
// Unsigned to float
void test_uz_fixedpoint_convert_unsiged_to_float_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_result = 2.75f;
    uint32_t testinput = 11;
    float return_value = uz_fixedpoint_convert_unsigned_to_float(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_result, return_value);
}

// Signed to float
void test_uz_fixedpoint_convert_to_float_negative(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_result = -2.75f;
    int32_t testinput = -11;
    float return_value = uz_fixedpoint_convert_signed_to_float(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_result, return_value);
}

void test_uz_fixedpoint_convert_to_float_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_result = 2.75f;
    int32_t testinput = 11;
    float return_value = uz_fixedpoint_convert_signed_to_float(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_result, return_value);
}

// float to unsigned fixed
void test_uz_fixedpoint_convert_to_unsigned_fixed(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 2,
        .integer_bits = 14};
    float testinput = 2.75f;
    uint32_t expected_retrun = 11;
    uint32_t return_value = uz_fixedpoint_convert_to_unsigned_fixed(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_retrun, return_value);
}

void test_uz_fixedpoint_convert_to_signed_fixed(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14,
        .rounding_type = round_trunc};
    float testinput = -2.9f;
    int32_t expected_retrun = -11;
    int32_t return_value = uz_fixedpoint_convert_to_signed_fixed(testinput, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_retrun, return_value);
}

// read/write functions
void test_uz_fixedpoint_axi_write_signed_negative(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float write_value = -2.75f;
    int32_t expected_write = -11; // first three bits are integer
    uz_axi_write_int32_Expect(TEST_ADDRESS, expected_write);
    uz_fixedpoint_axi_write(TEST_ADDRESS, write_value, def);
}

void test_uz_fixedpoint_axi_write_signed_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float write_value = 2.75f;
    int32_t expected_write = 11; // first three bits are integer
    uz_axi_write_int32_Expect(TEST_ADDRESS, expected_write);
    uz_fixedpoint_axi_write(TEST_ADDRESS, write_value, def);
}

void test_uz_fixedpoint_axi_write_unsigned_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 2,
        .integer_bits = 14};
    float write_value = 2.75f;
    uint32_t expected_write = 11U; // first three bits are integer
    uz_axi_write_uint32_Expect(TEST_ADDRESS, expected_write);
    uz_fixedpoint_axi_write(TEST_ADDRESS, write_value, def);
}

void test_uz_fixedpoint_axi_read_unsigned(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = false,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_return_value = 2.75f;
    uint32_t expected_read_value = 11U;
    uz_axi_read_uint32_ExpectAndReturn(TEST_ADDRESS, expected_read_value);
    float return_value = uz_fixedpoint_axi_read(TEST_ADDRESS, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value, return_value);
}

void test_uz_fixedpoint_axi_read_signed_positive(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_return_value = 2.75f;
    int32_t expected_read_value = 11;
    uz_axi_read_int32_ExpectAndReturn(TEST_ADDRESS, expected_read_value);
    float return_value = uz_fixedpoint_axi_read(TEST_ADDRESS, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value, return_value);
}

void test_uz_fixedpoint_axi_read_signed_negative(void)
{
    struct uz_fixedpoint_definition_t def = {
        .is_signed = true,
        .fractional_bits = 2,
        .integer_bits = 14};
    float expected_return_value = -2.75f;
    int32_t expected_read_value = -11;
    uz_axi_read_int32_ExpectAndReturn(TEST_ADDRESS, expected_read_value);
    float return_value = uz_fixedpoint_axi_read(TEST_ADDRESS, def);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value, return_value);
}

#endif // TEST
