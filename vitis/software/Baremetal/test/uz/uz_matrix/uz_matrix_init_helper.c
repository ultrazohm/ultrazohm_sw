#include "uz_matrix_init_helper.h"

#include <stdlib.h>

uz_matrix_t *init_array_test_helper(float* data, size_t rows,size_t columns)
{
    uz_matrix_t *pointer_to_matrix = malloc(sizeof(uz_matrix_t));
    pointer_to_matrix->columns=columns;
    pointer_to_matrix->rows=rows;
    pointer_to_matrix->data=data;
    pointer_to_matrix->length_of_data=rows*columns;
    return pointer_to_matrix;
}
