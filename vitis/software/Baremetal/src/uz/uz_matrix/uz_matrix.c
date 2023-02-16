/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2021 Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../uz_global_configuration.h"
#include "uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <string.h> // for memcpy

uz_matrix_t *uz_matrix_init(uz_matrix_t *self, float *data, uint32_t length_of_data, uint32_t rows, uint32_t columns)
{
    uz_assert_not_NULL(self);
    uz_assert_false(self->length_of_data);
    uz_assert_not_zero_unsigned_int(rows);
    uz_assert_not_zero_unsigned_int(columns);
    uz_assert(length_of_data == (rows * columns));
    self->length_of_data = length_of_data;
    self->rows = rows;
    self->columns = columns;
    self->data = data;
    return (self);
}

uint32_t uz_matrix_get_number_of_rows(uz_matrix_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->length_of_data);
    return (self->rows);
}

uint32_t uz_matrix_get_number_of_columns(uz_matrix_t const *const self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->length_of_data);
    return (self->columns);
}

void uz_matrix_elementwise_product(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->length_of_data);
    uz_assert(B->length_of_data);
    uz_assert(C_out->length_of_data);
    uz_assert(A->columns == B->columns);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == B->rows);
    uz_assert(A->rows == C_out->rows);

    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {
            C_out->data[(row * A->columns) + column] = A->data[(row * A->columns) + column] * B->data[(row * A->columns) + column];
        }
    }
}

float uz_matrix_get_element_zero_based(uz_matrix_t const *const A, uint32_t row, uint32_t column)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(row <= A->rows);
    uz_assert(column <= A->columns);
    return (A->data[(row * A->columns) + column]);
}

void uz_matrix_set_element_zero_based(uz_matrix_t *const A, float x, uint32_t row, uint32_t column)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(row <= A->rows);
    uz_assert(column <= A->columns);
    A->data[(row * A->columns) + column] = x;
}

void uz_matrix_sum(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->length_of_data);
    uz_assert(B->length_of_data);
    uz_assert(C_out->length_of_data);
    uz_assert(A->columns == B->columns);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == B->rows);
    uz_assert(A->rows == C_out->rows);

    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {
            C_out->data[(row * A->columns) + column] = A->data[(row * A->columns) + column] + B->data[(row * A->columns) + column];
        }
    }
}

float uz_matrix_dot_product(uz_matrix_t const *const A, uz_matrix_t const *const B)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert(A->length_of_data);
    uz_assert(B->length_of_data);
    uz_assert(A->columns == B->columns);
    uz_assert(A->rows == 1U);
    uz_assert(B->rows == 1U);
    float C = 0.0f;
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {
            C += A->data[(row * A->columns) + column] * B->data[(row * A->columns) + column];
        }
    }
    return (C);
}

void uz_matrix_multiply(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->length_of_data);
    uz_assert(B->length_of_data);
    uz_assert(C_out->length_of_data);
    // C= A * B
    // number of columns in A must b equal to rows of B
    uz_assert(A->columns == B->rows);
    // the product of an m x n matrix and n x k matrix is an m x k
    // i.e. A->row x B->column
    uz_assert(A->rows == C_out->rows);
    uz_assert(B->columns == C_out->columns);
    uz_matrix_set_zero(C_out);
    // The following implementation is "slow" as in it does not use special mechanism to speed it up. See the following resources for possible improvements.
    // https://github.com/deuxbot/fast-matrix-multiplication/blob/master/mxm.c
    // https://en.wikipedia.org/wiki/Matrix_multiplication
    uint32_t m = A->rows;
    uint32_t n = A->columns;
    uint32_t p = B->columns;
    for (uint32_t i = 0; i < m; i++)
    {
        for (uint32_t j = 0; j < p; j++)
        {
            for (uint32_t k = 0; k < n; k++)
            {
                C_out->data[(p * i) + j] += A->data[(n * i) + k] * B->data[(p * k) + j];
            }
        }
    }
}

void uz_matrix_set_zero(uz_matrix_t *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {
            A->data[(row * A->columns) + column] = 0.0f;
        }
    }
}

void uz_matrix_set_unity_matrix(uz_matrix_t *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(A->rows==A->columns);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {   if (row == column){
            A->data[(row * A->columns) + column] = 1.0f;
        }
            else{
            A->data[(row * A->columns) + column] = 0.0f;
            }
        }
    }
}

void uz_matrix_set_zero_except_diagonal(uz_matrix_t *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(A->rows==A->columns);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {   if (row == column){}
            
            else{
            A->data[(row * A->columns) + column] = 0.0f;
            }
        }
    }
}

void uz_matrix_set_rowvector_as_diagonal(uz_matrix_t *const A,uz_matrix_t *const rowvector)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(A->rows==A->columns);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {   if (row == column){
        A->data[(row * A->columns) + column] = rowvector->data[column];
        }
        else{
            }
        }
    }
}
void uz_matrix_set_columnvector_as_diagonal(uz_matrix_t *const A,uz_matrix_t *const columnvector)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert(A->rows==A->columns);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {   if (row == column){
        A->data[(row * A->columns) + column] = columnvector->data[row];
        }
        else{
            }
        }
    }
}
void uz_matrix_add(uz_matrix_t const *const A, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(C_out);
    uz_assert(A->length_of_data);
    uz_assert(C_out->length_of_data);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == C_out->rows);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        {
            C_out->data[(row * A->columns) + column] += A->data[(row * A->columns) + column];
        }
    }
}

void uz_matrix_add_scalar(uz_matrix_t *const A, float scalar)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    for (uint32_t i = 0; i < (A->rows * A->columns); i++)
    {
        A->data[i] += scalar;
    }
}

void uz_matrix_multiply_by_scalar(uz_matrix_t *const A, float scalar)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    for (uint32_t i = 0; i < (A->rows * A->columns); i++)
    {
        A->data[i] = A->data[i] * scalar;
    }
}

void uz_matrix_apply_function_to_each_element(uz_matrix_t *const A, float (*f)(float))
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(f);
    uz_assert(A->length_of_data);
    for (uint32_t i = 0; i < (A->rows * A->columns); i++)
    {
        A->data[i] = f(A->data[i]);
    }
}

void uz_matrix_apply_function_to_diagonal(uz_matrix_t *const A, float (*f)(float))
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(f);
    uz_assert(A->length_of_data);
    uz_assert(A->rows==A->columns);
    for (uint32_t row = 0; row < A->rows; row++)
    {
        for (uint32_t column = 0; column < A->columns; column++)
        { 
        if (row == column){
            A->data[(row * A->columns) + column] = f(A->data[(row * A->columns) + column]);
        }
        else{
            }
        }
    }
}

float uz_matrix_get_max_value(uz_matrix_t const *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uint32_t length_of_data = A->columns * A->rows;
    float maximum_value = A->data[0U]; // Set maximum arbitrarily to first element to initialize the variable
    for (uint32_t i = 1U; i < length_of_data; i++)
    { // Already got the value of the first element [0], thus start at 1
        if (A->data[i] > maximum_value)
        {
            maximum_value = A->data[i];
        }
    }
    return maximum_value;
}

uint32_t uz_matrix_get_max_index(uz_matrix_t const *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uint32_t length_of_data = A->columns * A->rows;
    float maximum_value = A->data[0U]; // Set maximum arbitrarily to first element to initialize the variable
    uint32_t max_index = 0U;
    for (uint32_t i = 1U; i < length_of_data; i++)
    { // Already got the value of the first element [0], thus start at 1
        if (A->data[i] > maximum_value)
        {
            maximum_value = A->data[i];
            max_index = i;
        }
    }
    return max_index;
}

void uz_matrix_transpose(uz_matrix_t *A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->length_of_data);
    uz_assert((A->rows * A->columns) > 0U); // Guard for VLA
    uint32_t old_rows = A->rows;
    uint32_t old_columns = A->columns;
    // cppcheck-suppress misra-c2012-18.8 // VLA are not allowed, but are here the better alternative to using malloc. In-place matrix transposition for non-square matrix is an better, not implemented alternative
    float helper_data[A->rows * A->columns]; // VLA to store
    void *ptr_res = memcpy(helper_data, A->data, (A->rows * A->columns) * sizeof(float));
    uz_assert_not_NULL(ptr_res); // checks return value of memcpy to make sure something happend
    A->rows = old_columns;
    A->columns = old_rows;
    for (uint32_t row = 0U; row < old_rows; row++)
    {
        for (uint32_t column = 0U; column < old_columns; column++)
        {
            float x = helper_data[(row * old_columns) + column];
            uz_matrix_set_element_zero_based(A, x, column, row);
        }
    }
}

void uz_matrix_copy(uz_matrix_t const *const source, uz_matrix_t *const destination)
{    
    uz_assert_not_NULL(source);
    uz_assert_not_NULL(destination);
    uz_assert(source->length_of_data == destination->length_of_data);
    destination->rows=source->rows;
    destination->columns=source->columns;

    for(uint32_t i=0U;i<destination->length_of_data;i++){
        destination->data[i]=source->data[i];
    }

}

void uz_matrix_columnvec_concatenate_horizontal(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->length_of_data);
    uz_assert(B->length_of_data);
    uz_assert(C_out->length_of_data);
    // eine Spalte nur, wegen 
    uz_assert(A->columns == B->columns == C_out->columns == 1);
    uz_assert((A->rows + B->rows) == C_out->rows);
    uz_matrix_set_zero(C_out);
    uint32_t m = A->rows;
    uint32_t n = B->rows;
    // loop first through A, then through C
    for (uint32_t i = 0; i < m; i++)
    {
    C_out->data[i] = A->data[i];
    }
    for (uint32_t k = 0; k < n; k++)
    {
    C_out->data[m + k] = B->data[k];
    }
}