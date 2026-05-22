#pragma once

#include <stddef.h>
#include <stdio.h>

enum csv_field_type_t
{
    CSV_FIELD_FLOAT,
    CSV_FIELD_DOUBLE,
    CSV_FIELD_UINT32,
    CSV_FIELD_INT32,
    CSV_FIELD_UINT16,
    CSV_FIELD_INT16,
    CSV_FIELD_UINT8,
    CSV_FIELD_INT8
};

struct csv_field_descriptor_t
{
    const char *name;
    size_t offset;
    enum csv_field_type_t type;
};

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
                                      float add_time);

void write_csv_field(FILE *file, const void *field_ptr, enum csv_field_type_t type);