#pragma once

#include "uz_fixedpoint.h"

void AssertEqual_uz_fixedpoint_definition_t(uz_fixedpoint_definition_t expected, uz_fixedpoint_definition_t actual, unsigned short line);

#define UNITY_TEST_ASSERT_EQUAL_uz_fixedpoint_definition_t(expected, actual, line, message) AssertEqual_uz_fixedpoint_definition_t(expected, actual, line)

