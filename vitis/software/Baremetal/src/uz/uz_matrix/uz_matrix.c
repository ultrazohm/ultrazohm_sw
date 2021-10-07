#include "../uz_global_configuration.h"
#if UZ_MATRIX_MAX_INSTANCES > 0
#include "uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>

struct uz_matrix_t
{
    bool is_ready;
    size_t rows;
    size_t columns;
    float *data;
};

static size_t instance_counter = 0U;
static uz_matrix_t instances[UZ_MATRIX_MAX_INSTANCES] = { 0 };

static uz_matrix_t* uz_matrix_allocation(void);

static uz_matrix_t* uz_matrix_allocation(void){
    uz_assert(instance_counter < UZ_MATRIX_MAX_INSTANCES);
    uz_matrix_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_matrix_t *uz_matrix_init(float* data,size_t length_of_data, size_t rows, size_t columns)
{
    uz_assert_not_NULL(data);
    uz_assert_not_zero_unsigned_int(rows);
    uz_assert_not_zero_unsigned_int(columns);
    uz_assert(length_of_data == (rows*columns));
    uz_matrix_t *self = uz_matrix_allocation();
    self->is_ready = true;
    self->rows = rows;
    self->columns = columns;
    self->data = data;
    return (self);
}

size_t uz_matrix_get_number_of_rows(uz_matrix_t const*const self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->rows);
}

size_t uz_matrix_get_number_of_columns(uz_matrix_t const*const self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (self->columns);
}


void uz_matrix_elementwise_product(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->is_ready);
    uz_assert(B->is_ready);
    uz_assert(C_out->is_ready);
    uz_assert(A->columns == B->columns);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == B->rows);
    uz_assert(A->rows == C_out->rows);

    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t column = 0; column < A->columns; column++)
        {
            C_out->data[ (row * A->columns) + column] = A->data[(row * A->columns )+ column] * B->data[(row * A->columns) + column];
        }
    }
}

float uz_matrix_get_element_zero_based(uz_matrix_t const*const A, size_t row, size_t column)
{
    uz_assert_not_NULL(A);
    uz_assert(A->is_ready);
    uz_assert(row <= A->rows);
    uz_assert(column <= A->columns);
    return (A->data[(row * A->columns)+ column]);
}

void uz_matrix_set_element_zero_based(uz_matrix_t *const A,float x,size_t row, size_t column)
{
    uz_assert_not_NULL(A);
    uz_assert(A->is_ready);
    uz_assert(row <= A->rows);
    uz_assert(column <= A->columns);
    A->data[(row * A->columns) + column]=x;
}

void uz_matrix_sum(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->is_ready);
    uz_assert(B->is_ready);
    uz_assert(C_out->is_ready);
    uz_assert(A->columns == B->columns);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == B->rows);
    uz_assert(A->rows == C_out->rows);

    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t column = 0; column < A->columns; column++)
        {
            C_out->data[(row * A->columns )+ column] = A->data[(row * A->columns) + column] + B->data[(row * A->columns) + column];
        }
    }
}

float uz_matrix_dot_product(uz_matrix_t const*const A, uz_matrix_t const*const B)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert(A->is_ready);
    uz_assert(B->is_ready);
    uz_assert(A->columns == B->columns);
    uz_assert(A->rows == 1U);
    uz_assert(B->rows == 1U);
    float C = 0.0f;
    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t column = 0; column < A->columns; column++)
        {
            C += A->data[ (row * A->columns) + column] * B->data[ (row * A->columns) + column];
        }
    }
    return (C);
}



void uz_matrix_multiply(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out)
{
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(B);
    uz_assert_not_NULL(C_out);
    uz_assert(A->is_ready);
    uz_assert(B->is_ready);
    uz_assert(C_out->is_ready);
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
    size_t m = A->rows;
    size_t n = A->columns;
    size_t p = B->columns;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < p; j++)
        {
            for (size_t k = 0; k < n; k++)
            {
                C_out->data[(p * i) + j] += A->data[(n * i) + k] * B->data[(p * k) + j];
            }
        }
    }
}

void uz_matrix_set_zero(uz_matrix_t *const A)
{
    uz_assert_not_NULL(A);
    uz_assert(A->is_ready);
    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t column = 0; column < A->columns; column++)
        {
            A->data[(row * A->columns) + column] = 0.0f;
        }
    }
}

void uz_matrix_add(uz_matrix_t const *const A, uz_matrix_t *const C_out){
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(C_out);
    uz_assert(A->is_ready);
    uz_assert(C_out->is_ready);
    uz_assert(A->columns == C_out->columns);
    uz_assert(A->rows == C_out->rows);
    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t column = 0; column < A->columns; column++)
        {
            C_out->data[(row * A->columns) + column] += A->data[(row * A->columns) + column];
        }
    }
}


void uz_matrix_add_scalar(uz_matrix_t *const A, float scalar){
    uz_assert_not_NULL(A);
    uz_assert(A->is_ready);
    for (size_t i=0;i < (A->rows*A->columns);i++){
        A->data[i] += scalar;
    }
}

void uz_matrix_multiply_by_scalar(uz_matrix_t *const A, float scalar){
    uz_assert_not_NULL(A);
    uz_assert(A->is_ready);
    for (size_t i=0;i < (A->rows*A->columns);i++){
        A->data[i] = A->data[i] * scalar;
    }
}

void uz_matrix_apply_function_to_each_element(uz_matrix_t *const A, float(*f)(float) ){
    uz_assert_not_NULL(A);
    uz_assert_not_NULL(f);
    uz_assert(A->is_ready);
    for (size_t i=0;i < (A->rows*A->columns);i++){
        A->data[i]=f(A->data[i]);
    }
}

#endif
