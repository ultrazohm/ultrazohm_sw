#include "unity.h"
#include "uz_fixedpoint_helper.h"

void AssertEqual_uz_fixedpoint_definition_t(uz_fixedpoint_definition_t expected, uz_fixedpoint_definition_t actual, unsigned short line) {
  UNITY_TEST_ASSERT_EQUAL_INT32(expected.integer_bits, actual.integer_bits, line, "Fixed point definition .integer_bits comparison failed");
  UNITY_TEST_ASSERT_EQUAL_INT32(expected.fractional_bits, actual.fractional_bits, line, "Fixed point definition .fractional_bits comparison failed");
  UNITY_TEST_ASSERT_EQUAL_UINT32(expected.is_signed, actual.is_signed, line, "Fixed point definition .is_signed comparison failed");
}