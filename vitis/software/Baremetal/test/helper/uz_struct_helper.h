#pragma once

#include "unity.h"

// List of header files that define public structs / typedefs that are passed into functions
#include "uz_fixedpoint.h"

// List of function declarations for costum test functions to assert equality on a per-member basis
void AssertEqual_uz_fixedpoint_definition_t(struct uz_fixedpoint_definition_t expected, struct uz_fixedpoint_definition_t actual, UNITY_UINT line);

// List of defines that map the function declarations to a type / struct name
// Has to match exactly (case sensitive) the name of the struct (including struct_) or the typedef (without struct_ or typedef, just the name)
#define UNITY_TEST_ASSERT_EQUAL_struct_uz_fixedpoint_definition_t(expected, actual, line, message) AssertEqual_uz_fixedpoint_definition_t(expected, actual, line)

