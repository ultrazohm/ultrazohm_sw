#ifdef TEST

#include "unity.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "export_struct_to_csv.h"

/*
 * Guards export_array_of_struct_to_csv_fast: it must produce byte-identical output
 * to the original export_array_of_struct_to_csv (for non-halfway values), and the
 * exact CSV text is pinned with explicit literals. Ceedling auto-links
 * export_struct_to_csv.c via the included header.
 */

#define SLOW_PATH "build/test_export_csv_slow.csv"
#define FAST_PATH "build/test_export_csv_fast.csv"

struct guard_row_t
{
    float f;
    double d;
    uint32_t u32;
    int32_t i32;
    int16_t i16;
    uint8_t u8;
    int8_t i8;
};

static const struct csv_field_descriptor_t guard_fields[] = {
    {"f", offsetof(struct guard_row_t, f), CSV_FIELD_FLOAT},
    {"d", offsetof(struct guard_row_t, d), CSV_FIELD_DOUBLE},
    {"u32", offsetof(struct guard_row_t, u32), CSV_FIELD_UINT32},
    {"i32", offsetof(struct guard_row_t, i32), CSV_FIELD_INT32},
    {"i16", offsetof(struct guard_row_t, i16), CSV_FIELD_INT16},
    {"u8", offsetof(struct guard_row_t, u8), CSV_FIELD_UINT8},
    {"i8", offsetof(struct guard_row_t, i8), CSV_FIELD_INT8}};

#define GUARD_FIELD_COUNT (sizeof(guard_fields) / sizeof(guard_fields[0]))

static char read_buffer[4096];

void setUp(void) {}
void tearDown(void) {}

static void read_file(const char *path, char *out, size_t out_size)
{
    FILE *file = fopen(path, "rb");
    TEST_ASSERT_NOT_NULL(file);
    const size_t read = fread(out, 1U, out_size - 1U, file);
    TEST_ASSERT_TRUE(read < out_size - 1U); /* whole file fit */
    out[read] = '\0';
    TEST_ASSERT_EQUAL_INT(0, fclose(file));
    (void)remove(path);
}

/* Values are chosen off the 0.5e-6 / 0.5e-10 rounding boundary so %f and the fast
 * integer-scaling formatter agree exactly. */
static const struct guard_row_t guard_rows[] = {
    {1.5f, 2.25, 7U, -3, 1000, 200U, -5},
    {-2.75f, 0.0, 0U, 2147483647, -32768, 0U, 127},
    {0.1f, -4.5, 4294967295U, -2147483647 - 1, 32767, 255U, -128}};

#define GUARD_ROW_COUNT (sizeof(guard_rows) / sizeof(guard_rows[0]))

void test_fast_matches_slow_without_time(void)
{
    export_array_of_struct_to_csv(SLOW_PATH, guard_rows, sizeof(guard_rows[0]), guard_fields, GUARD_FIELD_COUNT, GUARD_ROW_COUNT, 0.0f);
    export_array_of_struct_to_csv_fast(FAST_PATH, guard_rows, sizeof(guard_rows[0]), guard_fields, GUARD_FIELD_COUNT, GUARD_ROW_COUNT, 0.0f);

    char slow[4096];
    read_file(SLOW_PATH, slow, sizeof(slow));
    read_file(FAST_PATH, read_buffer, sizeof(read_buffer));
    TEST_ASSERT_EQUAL_STRING(slow, read_buffer);
}

void test_fast_matches_slow_with_time(void)
{
    export_array_of_struct_to_csv(SLOW_PATH, guard_rows, sizeof(guard_rows[0]), guard_fields, GUARD_FIELD_COUNT, GUARD_ROW_COUNT, 0.1f);
    export_array_of_struct_to_csv_fast(FAST_PATH, guard_rows, sizeof(guard_rows[0]), guard_fields, GUARD_FIELD_COUNT, GUARD_ROW_COUNT, 0.1f);

    char slow[4096];
    read_file(SLOW_PATH, slow, sizeof(slow));
    read_file(FAST_PATH, read_buffer, sizeof(read_buffer));
    TEST_ASSERT_EQUAL_STRING(slow, read_buffer);
}

void test_fast_exact_format_without_time(void)
{
    const struct guard_row_t row = {1.5f, 2.25, 42U, -3, 1000, 200U, -5};
    export_array_of_struct_to_csv_fast(FAST_PATH, &row, sizeof(row), guard_fields, GUARD_FIELD_COUNT, 1U, 0.0f);
    read_file(FAST_PATH, read_buffer, sizeof(read_buffer));
    TEST_ASSERT_EQUAL_STRING("f;d;u32;i32;i16;u8;i8\n1.500000;2.250000;42;-3;1000;200;-5\n", read_buffer);
}

void test_fast_exact_format_with_time(void)
{
    const struct guard_row_t row = {1.5f, 2.25, 42U, -3, 1000, 200U, -5};
    export_array_of_struct_to_csv_fast(FAST_PATH, &row, sizeof(row), guard_fields, GUARD_FIELD_COUNT, 1U, 0.5f);
    read_file(FAST_PATH, read_buffer, sizeof(read_buffer));
    TEST_ASSERT_EQUAL_STRING("time;f;d;u32;i32;i16;u8;i8\n0.0000000000;1.500000;2.250000;42;-3;1000;200;-5\n", read_buffer);
}

#endif // TEST
