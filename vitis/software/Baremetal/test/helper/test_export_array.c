#ifdef TEST
#include "unity.h"
#include "export_array.h"
#include <stdio.h>
#include <string.h>

#define OUTPUT "build/test_export_array.csv"

void setUp(void) {}
void tearDown(void) { remove(OUTPUT); }

static void assert_contents(FILE *file, const char *expected)
{
    char buffer[128] = {0};
    TEST_ASSERT_NOT_NULL(file);
    const size_t count = fread(buffer, 1U, sizeof(buffer) - 1U, file);
    const int error = ferror(file);
    const int closed = fclose(file);
    TEST_ASSERT_TRUE(count < sizeof(buffer) - 1U);
    TEST_ASSERT_EQUAL_INT(0, error);
    TEST_ASSERT_EQUAL_INT(0, closed);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_float_export_is_complete_on_return(void)
{
    float values[] = {1.25f, -0.5f};
    uz_array_float_t array = {.data = values, .length = 2U};
    export_array_float(array, OUTPUT);
    assert_contents(fopen(OUTPUT, "r"), "0,1.2500\n1,-0.5000\n");
}

void test_uint32_export_replaces_file_without_changing_open_reader(void)
{
    uint32_t values[] = {0U, UINT32_MAX};
    uz_array_uint32_t array = {.data = values, .length = 2U};
    export_array_uint32(array, OUTPUT);
    FILE *reader = fopen(OUTPUT, "r");
    TEST_ASSERT_NOT_NULL(reader);
    values[0] = 42U;
    array.length = 1U;
    export_array_uint32(array, OUTPUT);
    assert_contents(reader, "0,0\n1,4294967295\n");
    assert_contents(fopen(OUTPUT, "r"), "0,42\n");
}

void test_empty_export_replaces_previous_contents(void)
{
    float value = 1.0f;
    uz_array_float_t array = {.data = &value, .length = 1U};
    export_array_float(array, OUTPUT);
    array.length = 0U;
    export_array_float(array, OUTPUT);
    assert_contents(fopen(OUTPUT, "r"), "");
}
#endif
