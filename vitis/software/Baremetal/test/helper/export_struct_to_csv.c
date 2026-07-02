#include "export_struct_to_csv.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"
#include "test_assert_with_exception.h"

/* The output directories (e.g. docs/ceedling_test_output/...) are gitignored and are
   created by `make ceedling_tests` in docs/ (target ceedling_test_output); the failure
   message names the CSV path so a missing directory is obvious. */
static FILE *open_csv_file_for_write(const char *filename)
{
    FILE *file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL_MESSAGE(file, filename);
    return file;
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
    FILE *file = open_csv_file_for_write(filename);
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
    FILE *file = open_csv_file_for_write(filename);
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

/*
 * Faster drop-in for export_array_of_struct_to_csv. The slow version calls fprintf
 * per field/separator/row (tens of millions of calls + glibc's heavy %f path for a
 * multi-million-row log). This version formats into a large user buffer flushed with
 * a few big fwrites, and converts numbers with a fixed-precision integer-scaling
 * formatter instead of %f. Output is numerically identical to the slow version's
 * "%f" (6 decimals) / "%.10f" (time) form.
 *
 * Rounding note: the integer-scaling path rounds half away from zero, whereas %f
 * rounds half to even, so a value landing exactly on a 0.5e-6 (or 0.5e-10) boundary
 * may differ in the last digit. That is cosmetic for a profile dump; values are
 * equivalent. Out-of-range magnitudes and non-finite values fall back to snprintf.
 */
/*
 * Staging buffer flushed to the FILE* with one fwrite (≈one write() syscall) per fill.
 * It does NOT need to hold the whole output -- the OS page cache absorbs that. Measured
 * on a 600 MB / 6M-row export: <1 MiB hurts (more syscalls), but past ~1 MiB the curve is
 * nearly flat (1 MiB->64 MiB is only ~6%) and >64 MiB regresses as it falls out of CPU
 * cache. 8 MiB sits in the sweet spot; the real cost is the formatting CPU + the 600 MB write.
 */
#define CSV_FAST_BUFFER_BYTES (8U << 20) /* 8 MiB */

struct csv_out_buffer_t
{
    char *data;
    size_t capacity;
    size_t length;
    FILE *file;
};

static void csv_buffer_flush(struct csv_out_buffer_t *buffer)
{
    if (buffer->length != 0U)
    {
        if (fwrite(buffer->data, 1U, buffer->length, buffer->file) != buffer->length)
        {
            TEST_FAIL_MESSAGE("CSV fast export write failed");
        }
        buffer->length = 0U;
    }
}

/* Guarantee at least `needed` free bytes; flushes when the pending data would overflow. */
static void csv_buffer_reserve(struct csv_out_buffer_t *buffer, size_t needed)
{
    TEST_ASSERT_TRUE(needed <= buffer->capacity);
    if (buffer->length + needed > buffer->capacity)
    {
        csv_buffer_flush(buffer);
    }
}

static void csv_buffer_putc(struct csv_out_buffer_t *buffer, char c)
{
    csv_buffer_reserve(buffer, 1U);
    buffer->data[buffer->length++] = c;
}

static void csv_buffer_write(struct csv_out_buffer_t *buffer, const char *bytes, size_t count)
{
    csv_buffer_reserve(buffer, count);
    memcpy(buffer->data + buffer->length, bytes, count);
    buffer->length += count;
}

static void csv_buffer_puts(struct csv_out_buffer_t *buffer, const char *text)
{
    csv_buffer_write(buffer, text, strlen(text));
}

static void csv_buffer_put_u64(struct csv_out_buffer_t *buffer, uint64_t value)
{
    char digits[20];
    size_t count = 0U;
    do
    {
        digits[count++] = (char)('0' + (value % 10U));
        value /= 10U;
    } while (value != 0U);
    csv_buffer_reserve(buffer, count);
    while (count != 0U)
    {
        buffer->data[buffer->length++] = digits[--count];
    }
}

static void csv_buffer_put_i64(struct csv_out_buffer_t *buffer, int64_t value)
{
    uint64_t magnitude;
    if (value < 0)
    {
        csv_buffer_putc(buffer, '-');
        magnitude = (uint64_t)(-(value + 1)) + 1U; /* avoids INT64_MIN overflow */
    }
    else
    {
        magnitude = (uint64_t)value;
    }
    csv_buffer_put_u64(buffer, magnitude);
}

/* Append `value` with a fixed number of decimals, matching printf "%.<decimals>f". */
static void csv_buffer_put_fixed(struct csv_out_buffer_t *buffer, double value, unsigned decimals, uint64_t scale, const char *fallback_format)
{
    if (!isfinite(value))
    {
        csv_buffer_puts(buffer, isnan(value) ? "nan" : (value < 0.0 ? "-inf" : "inf"));
        return;
    }

    const double magnitude = fabs(value);
    /* Keep the scaled value within the range where double->int64 split stays exact. */
    if (magnitude >= 9.0e18 / (double)scale)
    {
        char fallback[512];
        const int written = snprintf(fallback, sizeof(fallback), fallback_format, value);
        if (written > 0)
        {
            csv_buffer_write(buffer, fallback, (size_t)written);
        }
        return;
    }

    const uint64_t scaled = (uint64_t)(magnitude * (double)scale + 0.5); /* round half up */
    uint64_t fraction = scaled % scale;

    if (signbit(value)) /* matches %f: keeps the sign even when the value rounds to zero */
    {
        csv_buffer_putc(buffer, '-');
    }
    csv_buffer_put_u64(buffer, scaled / scale);
    csv_buffer_putc(buffer, '.');

    char fraction_digits[20];
    for (int i = (int)decimals - 1; i >= 0; --i)
    {
        fraction_digits[i] = (char)('0' + (fraction % 10U));
        fraction /= 10U;
    }
    csv_buffer_write(buffer, fraction_digits, decimals);
}

static void csv_buffer_put_field(struct csv_out_buffer_t *buffer, const void *field_ptr, enum csv_field_type_t type)
{
    switch (type)
    {
    case CSV_FIELD_FLOAT:
        csv_buffer_put_fixed(buffer, (double)(*(const float *)field_ptr), 6U, 1000000ULL, "%f");
        break;
    case CSV_FIELD_DOUBLE:
        csv_buffer_put_fixed(buffer, *(const double *)field_ptr, 6U, 1000000ULL, "%f");
        break;
    case CSV_FIELD_UINT32:
        csv_buffer_put_u64(buffer, *(const uint32_t *)field_ptr);
        break;
    case CSV_FIELD_INT32:
        csv_buffer_put_i64(buffer, *(const int32_t *)field_ptr);
        break;
    case CSV_FIELD_UINT16:
        csv_buffer_put_u64(buffer, *(const uint16_t *)field_ptr);
        break;
    case CSV_FIELD_INT16:
        csv_buffer_put_i64(buffer, *(const int16_t *)field_ptr);
        break;
    case CSV_FIELD_UINT8:
        csv_buffer_put_u64(buffer, *(const uint8_t *)field_ptr);
        break;
    case CSV_FIELD_INT8:
        csv_buffer_put_i64(buffer, *(const int8_t *)field_ptr);
        break;
    default:
        TEST_FAIL_MESSAGE("Unsupported CSV field type");
        break;
    }
}

void export_array_of_struct_to_csv_fast(const char *filename,
                                        const void *array,
                                        size_t element_size,
                                        const struct csv_field_descriptor_t *fields,
                                        size_t field_count,
                                        size_t length,
                                        float add_time)
{
    FILE *file = open_csv_file_for_write(filename);
    TEST_ASSERT_NOT_NULL(array);
    TEST_ASSERT_NOT_NULL(fields);

    char *storage = (char *)malloc(CSV_FAST_BUFFER_BYTES);
    TEST_ASSERT_NOT_NULL(storage);
    struct csv_out_buffer_t buffer = {storage, CSV_FAST_BUFFER_BYTES, 0U, file};

    if (add_time != 0.0f)
    {
        csv_buffer_puts(&buffer, "time;");
    }

    for (size_t field_index = 0U; field_index < field_count; ++field_index)
    {
        csv_buffer_puts(&buffer, fields[field_index].name);
        if (field_index < (field_count - 1U))
        {
            csv_buffer_putc(&buffer, ';');
        }
    }
    csv_buffer_putc(&buffer, '\n');

    for (size_t element_index = 0U; element_index < length; ++element_index)
    {
        const unsigned char *element = (const unsigned char *)array + (element_index * element_size);

        if (add_time != 0.0f)
        {
            csv_buffer_put_fixed(&buffer, (double)element_index * (double)add_time, 10U, 10000000000ULL, "%.10f");
            csv_buffer_putc(&buffer, ';');
        }

        for (size_t field_index = 0U; field_index < field_count; ++field_index)
        {
            const void *field_ptr = element + fields[field_index].offset;
            csv_buffer_put_field(&buffer, field_ptr, fields[field_index].type);
            if (field_index < (field_count - 1U))
            {
                csv_buffer_putc(&buffer, ';');
            }
        }
        csv_buffer_putc(&buffer, '\n');
    }

    csv_buffer_flush(&buffer);
    free(storage);
    TEST_ASSERT_EQUAL_INT(0, fclose(file));
}