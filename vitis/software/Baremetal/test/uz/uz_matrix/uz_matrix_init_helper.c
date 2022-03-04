#include "uz_matrix_init_helper.h"

#include <stdlib.h>

uz_matrix_t *init_array_test_helper(float* data, uint32_t length_of_data,uint32_t rows,uint32_t columns)
{
    uz_matrix_t *pointer_to_matrix = malloc(sizeof(uz_matrix_t));
    uz_matrix_init(pointer_to_matrix,data,length_of_data,rows,columns);
    return pointer_to_matrix;
}
