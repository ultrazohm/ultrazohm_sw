#include "uz_struct_helper.h"

// The define "UNITY_UINT" comes from unity (https://github.com/ThrowTheSwitch/Unity/blob/master/src/unity_internals.h)
// Use for the "line" argument of the AssertEqual function to prevent warnings and issues regarding the size of int (32, 64 bit...)

void AssertEqual_uz_fixedpoint_definition_t(struct uz_fixedpoint_definition_t expected, struct uz_fixedpoint_definition_t actual, UNITY_UINT line) {
  UNITY_TEST_ASSERT_EQUAL_INT32(expected.integer_bits, actual.integer_bits, line, "Fixed point definition .integer_bits comparison failed");
  UNITY_TEST_ASSERT_EQUAL_INT32(expected.fractional_bits, actual.fractional_bits, line, "Fixed point definition .fractional_bits comparison failed");
  UNITY_TEST_ASSERT_EQUAL_UINT32(expected.is_signed, actual.is_signed, line, "Fixed point definition .is_signed comparison failed");
}