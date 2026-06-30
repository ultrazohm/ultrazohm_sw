#include "export_struct_to_csv.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "unity.h"
#include "test_assert_with_exception.h"

/*
 * Self-describing little-endian binary export consumed by
 * test/integration_tests/convert_binary_export_to_parquet.py. The exact
 * on-disk layout is documented in that script's module docstring; keep the two
 * in sync when bumping BINARY_EXPORT_VERSION.
 */
#define BINARY_EXPORT_MAGIC "UZBIN001"
#define BINARY_EXPORT_MAGIC_LENGTH 8U
#define BINARY_EXPORT_VERSION 1U
#define BINARY_EXPORT_FIELD_NAME_BUFFER_LENGTH 128U

static void write_binary_data(FILE *file, const void *data, size_t size)
{
    if (fwrite(data, 1U, size, file) != size)
    {
        TEST_FAIL_MESSAGE("Binary export write failed");
    }
}

static void write_binary_field_header(FILE *file, const char *field_name, enum csv_field_type_t type)
{
    TEST_ASSERT_NOT_NULL(field_name);
    const size_t field_name_length = strlen(field_name);
    TEST_ASSERT_TRUE(field_name_length <= UINT16_MAX);

    const uint8_t type_id = (uint8_t)type;
    const uint16_t name_length = (uint16_t)field_name_length;

    write_binary_data(file, &type_id, sizeof(type_id));
    write_binary_data(file, &name_length, sizeof(name_length));
    write_binary_data(file, field_name, field_name_length);
}

static void write_binary_export_header(FILE *file, size_t length, size_t field_count, bool has_time, float add_time)
{
    TEST_ASSERT_TRUE(length <= UINT64_MAX);
    TEST_ASSERT_TRUE(field_count <= UINT32_MAX);
    const uint16_t endian_check = 1U;
    TEST_ASSERT_EQUAL_UINT8(1U, *((const uint8_t *)&endian_check));

    const uint32_t version = BINARY_EXPORT_VERSION;
    const uint64_t row_count = (uint64_t)length;
    const uint32_t stored_field_count = (uint32_t)field_count;
    const uint8_t stored_has_time = has_time ? 1U : 0U;
    const double sample_time = (double)add_time;

    write_binary_data(file, BINARY_EXPORT_MAGIC, BINARY_EXPORT_MAGIC_LENGTH);
    write_binary_data(file, &version, sizeof(version));
    write_binary_data(file, &row_count, sizeof(row_count));
    write_binary_data(file, &stored_field_count, sizeof(stored_field_count));
    write_binary_data(file, &stored_has_time, sizeof(stored_has_time));
    write_binary_data(file, &sample_time, sizeof(sample_time));
}

static void write_binary_field(FILE *file, const void *field_ptr, enum csv_field_type_t type)
{
    switch (type)
    {
    case CSV_FIELD_FLOAT:
        write_binary_data(file, field_ptr, sizeof(float));
        break;
    case CSV_FIELD_DOUBLE:
        write_binary_data(file, field_ptr, sizeof(double));
        break;
    case CSV_FIELD_UINT32:
        write_binary_data(file, field_ptr, sizeof(uint32_t));
        break;
    case CSV_FIELD_INT32:
        write_binary_data(file, field_ptr, sizeof(int32_t));
        break;
    case CSV_FIELD_UINT16:
        write_binary_data(file, field_ptr, sizeof(uint16_t));
        break;
    case CSV_FIELD_INT16:
        write_binary_data(file, field_ptr, sizeof(int16_t));
        break;
    case CSV_FIELD_UINT8:
        write_binary_data(file, field_ptr, sizeof(uint8_t));
        break;
    case CSV_FIELD_INT8:
        write_binary_data(file, field_ptr, sizeof(int8_t));
        break;
    default:
        TEST_FAIL_MESSAGE("Unsupported binary field type");
        break;
    }
}

void write_csv_field(FILE *file, const void *field_ptr, enum csv_field_type_t type)
{
    switch (type)
    {
    case CSV_FIELD_FLOAT:
        fprintf(file, "%f", (double)(*(const float *)field_ptr));
        break;
    case CSV_FIELD_DOUBLE:
        fprintf(file, "%f", *(const double *)field_ptr);
        break;
    case CSV_FIELD_UINT32:
        fprintf(file, "%lu", (unsigned long)(*(const uint32_t *)field_ptr));
        break;
    case CSV_FIELD_INT32:
        fprintf(file, "%ld", (long)(*(const int32_t *)field_ptr));
        break;
    case CSV_FIELD_UINT16:
        fprintf(file, "%u", (unsigned int)(*(const uint16_t *)field_ptr));
        break;
    case CSV_FIELD_INT16:
        fprintf(file, "%d", (int)(*(const int16_t *)field_ptr));
        break;
    case CSV_FIELD_UINT8:
        fprintf(file, "%u", (unsigned int)(*(const uint8_t *)field_ptr));
        break;
    case CSV_FIELD_INT8:
        fprintf(file, "%d", (int)(*(const int8_t *)field_ptr));
        break;
    default:
        TEST_FAIL_MESSAGE("Unsupported CSV field type");
        break;
    }
}

void export_input_output_arrays_to_csv(const char *filename,
                                              const void *input_array,
                                              size_t input_element_size,
                                              const struct csv_field_descriptor_t *input_fields,
                                              size_t input_field_count,
                                              const void *output_array,
                                              size_t output_element_size,
                                              const struct csv_field_descriptor_t *output_fields,
                                              size_t output_field_count,
                                              size_t length,
                                              float add_time)
{
    FILE *file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_NOT_NULL(input_array);
    TEST_ASSERT_NOT_NULL(input_fields);
    TEST_ASSERT_NOT_NULL(output_array);
    TEST_ASSERT_NOT_NULL(output_fields);

    if (add_time != 0.0f)
    {
        fprintf(file, "time;");
    }

    for (size_t field_index = 0U; field_index < input_field_count; ++field_index)
    {
        fprintf(file, "input_%s", input_fields[field_index].name);
        fprintf(file, ";");
    }
    for (size_t field_index = 0U; field_index < output_field_count; ++field_index)
    {
        fprintf(file, "output_%s", output_fields[field_index].name);
        if (field_index < (output_field_count - 1U))
        {
            fprintf(file, ";");
        }
    }
    fprintf(file, "\n");

    for (size_t element_index = 0U; element_index < length; ++element_index)
    {
        const unsigned char *input_element = (const unsigned char *)input_array + (element_index * input_element_size);
        const unsigned char *output_element = (const unsigned char *)output_array + (element_index * output_element_size);

        if (add_time != 0.0f)
        {
            fprintf(file, "%.10f;", (double)element_index * (double)add_time);
        }

        for (size_t field_index = 0U; field_index < input_field_count; ++field_index)
        {
            const void *field_ptr = input_element + input_fields[field_index].offset;
            write_csv_field(file, field_ptr, input_fields[field_index].type);
            fprintf(file, ";");
        }

        for (size_t field_index = 0U; field_index < output_field_count; ++field_index)
        {
            const void *field_ptr = output_element + output_fields[field_index].offset;
            write_csv_field(file, field_ptr, output_fields[field_index].type);
            if (field_index < (output_field_count - 1U))
            {
                fprintf(file, ";");
            }
        }
        fprintf(file, "\n");
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}

void export_array_of_struct_to_csv(const char *filename,
                                   const void *array,
                                   size_t element_size,
                                   const struct csv_field_descriptor_t *fields,
                                   size_t field_count,
                                   size_t length,
                                   float add_time)
{
    FILE *file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_NOT_NULL(array);
    TEST_ASSERT_NOT_NULL(fields);

    if (add_time != 0.0f)
    {
        fprintf(file, "time;");
    }

    for (size_t field_index = 0U; field_index < field_count; ++field_index)
    {
        fprintf(file, "%s", fields[field_index].name);
        if (field_index < (field_count - 1U))
        {
            fprintf(file, ";");
        }
    }
    fprintf(file, "\n");

    for (size_t element_index = 0U; element_index < length; ++element_index)
    {
        const unsigned char *element = (const unsigned char *)array + (element_index * element_size);

        if (add_time != 0.0f)
        {
            fprintf(file, "%.10f;", (double)element_index * (double)add_time);
        }

        for (size_t field_index = 0U; field_index < field_count; ++field_index)
        {
            const void *field_ptr = element + fields[field_index].offset;
            write_csv_field(file, field_ptr, fields[field_index].type);
            if (field_index < (field_count - 1U))
            {
                fprintf(file, ";");
            }
        }
        fprintf(file, "\n");
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}

void export_input_output_arrays_to_binary(const char *filename,
                                          const void *input_array,
                                          size_t input_element_size,
                                          const struct csv_field_descriptor_t *input_fields,
                                          size_t input_field_count,
                                          const void *output_array,
                                          size_t output_element_size,
                                          const struct csv_field_descriptor_t *output_fields,
                                          size_t output_field_count,
                                          size_t length,
                                          float add_time)
{
    FILE *file = fopen(filename, "wb");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_NOT_NULL(input_array);
    TEST_ASSERT_NOT_NULL(input_fields);
    TEST_ASSERT_NOT_NULL(output_array);
    TEST_ASSERT_NOT_NULL(output_fields);

    write_binary_export_header(file, length, input_field_count + output_field_count, add_time != 0.0f, add_time);

    for (size_t field_index = 0U; field_index < input_field_count; ++field_index)
    {
        char field_name[BINARY_EXPORT_FIELD_NAME_BUFFER_LENGTH] = {0};
        const int chars_written = snprintf(field_name, sizeof(field_name), "input_%s", input_fields[field_index].name);
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, chars_written);
        TEST_ASSERT_TRUE((size_t)chars_written < sizeof(field_name));
        write_binary_field_header(file, field_name, input_fields[field_index].type);
    }
    for (size_t field_index = 0U; field_index < output_field_count; ++field_index)
    {
        char field_name[BINARY_EXPORT_FIELD_NAME_BUFFER_LENGTH] = {0};
        const int chars_written = snprintf(field_name, sizeof(field_name), "output_%s", output_fields[field_index].name);
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, chars_written);
        TEST_ASSERT_TRUE((size_t)chars_written < sizeof(field_name));
        write_binary_field_header(file, field_name, output_fields[field_index].type);
    }

    for (size_t element_index = 0U; element_index < length; ++element_index)
    {
        const unsigned char *input_element = (const unsigned char *)input_array + (element_index * input_element_size);
        const unsigned char *output_element = (const unsigned char *)output_array + (element_index * output_element_size);

        if (add_time != 0.0f)
        {
            const double time = (double)element_index * (double)add_time;
            write_binary_data(file, &time, sizeof(time));
        }

        for (size_t field_index = 0U; field_index < input_field_count; ++field_index)
        {
            const void *field_ptr = input_element + input_fields[field_index].offset;
            write_binary_field(file, field_ptr, input_fields[field_index].type);
        }

        for (size_t field_index = 0U; field_index < output_field_count; ++field_index)
        {
            const void *field_ptr = output_element + output_fields[field_index].offset;
            write_binary_field(file, field_ptr, output_fields[field_index].type);
        }
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}

void export_array_of_struct_to_binary(const char *filename,
                                      const void *array,
                                      size_t element_size,
                                      const struct csv_field_descriptor_t *fields,
                                      size_t field_count,
                                      size_t length,
                                      float add_time)
{
    FILE *file = fopen(filename, "wb");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_NOT_NULL(array);
    TEST_ASSERT_NOT_NULL(fields);

    write_binary_export_header(file, length, field_count, add_time != 0.0f, add_time);

    for (size_t field_index = 0U; field_index < field_count; ++field_index)
    {
        write_binary_field_header(file, fields[field_index].name, fields[field_index].type);
    }

    for (size_t element_index = 0U; element_index < length; ++element_index)
    {
        const unsigned char *element = (const unsigned char *)array + (element_index * element_size);

        if (add_time != 0.0f)
        {
            const double time = (double)element_index * (double)add_time;
            write_binary_data(file, &time, sizeof(time));
        }

        for (size_t field_index = 0U; field_index < field_count; ++field_index)
        {
            const void *field_ptr = element + fields[field_index].offset;
            write_binary_field(file, field_ptr, fields[field_index].type);
        }
    }

    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}
