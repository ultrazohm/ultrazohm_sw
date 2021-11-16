#include "unity.h"
#include "uz_fixedpoint_helper.h"

void AssertEqual_uz_fixedpoint_definition_t(uz_fixedpoint_definition_t expected, uz_fixedpoint_definition_t actual, unsigned short line) {
  TEST_ASSERT_EQUAL(0, 1); // This doesn't fails because this function never called
//  UNITY_TEST_ASSERT_EQUAL_UINT8(expected.acceptance, actual.acceptance, line, "OtaAcceptance .acceptance comparison failed");
//  UNITY_TEST_ASSERT_EQUAL_UINT8(expected.fwRegion, actual.fwRegion, line, "OtaAcceptance .fwRegion comparison failed");
//  UNITY_TEST_ASSERT_EQUAL_UINT32(expected.version, actual.version, line, "OtaAcceptance .version comparison failed");
}