#include "export_struct_to_csv.h"

#include <stdint.h>

#include "unity.h"
#include "test_assert_with_exception.h"

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
            fprintf(file, "%f;", (double)element_index * (double)add_time);
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