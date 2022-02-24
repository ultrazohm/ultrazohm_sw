#ifndef UZ_MATRIX_H
#define UZ_MATRIX_H
#include <stddef.h>
#include <stdbool.h>


struct uz_matrix_t
{
    size_t length_of_data;
    size_t rows;
    size_t columns;
    float *data;
};

/**
 * @brief Standard macro to get the size of supplied matrix data at compile time.
 *        See:
 *        - https://github.com/chromium/chromium/blob/HEAD/third_party/protobuf/php/ext/google/protobuf/php-upb.c
 *        - https://stackoverflow.com/questions/1598773/is-there-a-standard-function-in-c-that-would-return-the-length-of-an-array/1598827#1598827
 */
#define UZ_MATRIX_SIZE(x) \
    ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

/**
 * @brief Object data type definition of the uz_matrix
 * 
 */
typedef struct uz_matrix_t uz_matrix_t;


uz_matrix_t *uz_matrix_init_without_allocation(uz_matrix_t *self,float *data, size_t length_of_data, size_t rows, size_t columns);

/**
 * @brief Initializes one matrix and allocates memory for it from the static allocator.
 * 
 * @param data Pointer to array with length rows*colums.
 * @param length_of_data Length of data calculated with UZ_MATRIX_SIZE macro
 * @param rows Number of rows of the matrix
 * @param columns Number of columns of the matrix
 * @return Pointer to the allocated matrix instance 
 */
uz_matrix_t* uz_matrix_init(float* data,size_t length_of_data, size_t rows, size_t columns);

/**
 * @brief Returns the number of rows of the given uz_matrix
 * 
 * @param self 
 * @return size_t 
 */
size_t uz_matrix_get_number_of_rows(uz_matrix_t const*const self);

/**
 * @brief Returns the number of columns of the given uz_matrix
 * 
 * @param self 
 * @return size_t 
 */
size_t uz_matrix_get_number_of_columns(uz_matrix_t const*const self);

/**
 * @brief Set all elements of the matrix A to zero
 * 
 * @param A Matrix object, has to be ready.
 */
void uz_matrix_set_zero(uz_matrix_t * const A);

/**
 * @brief Get the element row x column of matrix A with zero based indexing.
 * 
 * @param A Matrix object, hast to be ready.
 * @param row Row of element
 * @param column Column of element
 * @return float 
 */
float uz_matrix_get_element_zero_based(uz_matrix_t const*const A,size_t row, size_t column);

/**
 * @brief Set the element row x column of matrix A with zero based indexing.
 * 
 * @param A Matrix object
 * @param x Value that the element is set to
 * @param row Row of element to set
 * @param column Column of element to set
 */
void uz_matrix_set_element_zero_based(uz_matrix_t *const A,float x,size_t row, size_t column);


/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param A 
 * @param B 
 * @param C_out Result of the multiplication is written to C_out
 */
void uz_matrix_multiply(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t* const C_out);

/**
 * @brief Calculates the elementwise product C_out= A .* B of all elements of the matrix A and B (also called Hadamard-Product)
 * 
 * @param A 
 * @param B 
 * @param C_out Result of the elementwise product is written to C_out
 */
void uz_matrix_elementwise_product(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t* const C_out);

/**
 * @brief Calculates the dot product (scalar product) of the column vectors A and B.
 *        Rows of A and B have to be 1 and the column dimension mus be equal.
 * 
 * @param A Column or row vector
 * @param B Column or row vector
 * @return float 
 */
float uz_matrix_dot_product(uz_matrix_t const*const A, uz_matrix_t const*const B);

/**
 * @brief Calculates C_out = A + B
 * 
 * @param A 
 * @param B 
 * @param C_out Sum of A and B is written to C_out
 */
void uz_matrix_sum(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t *const C_out);

/**
 * @brief Calculates C_out += A
 * 
 * @param A 
 * @param C_out Adds the values of A to C_out
 */
void uz_matrix_add(uz_matrix_t const*const A, uz_matrix_t *const C_out);

/**
 * @brief Adds a scalar to all elements of the matrix A
 * 
 * @param A 
 * @param scalar 
 */
void uz_matrix_add_scalar(uz_matrix_t *const A, float scalar);

/**
 * @brief Multiplies all elements of the matrix A by a scalar
 * 
 * @param A 
 * @param scalar 
 */
void uz_matrix_multiply_by_scalar(uz_matrix_t *const A, float scalar);

/**
 * @brief Applies a function f, that is passed as a function pointer, to each of the elements 
 * 
 * @param A 
 * @param f Function pointer, function has to accept one float as argument and return one float
 */
void uz_matrix_apply_function_to_each_element(uz_matrix_t *const A, float(*f)(float) );


/**
 * @brief Retruns the value of the biggest element of the matrix
 * 
 * @param A 
 * @return float 
 */
float uz_matrix_get_max_value(uz_matrix_t const*const A);

/**
 * @brief Returns the index at which position the biggest value is located in the matrix A
 * 
 * @param A 
 * @return size_t 
 */
size_t uz_matrix_get_max_index(uz_matrix_t const*const A);

/**
 * @brief Transposes the matrix A
 * 
 * @param A 
 */
void uz_matrix_transpose(uz_matrix_t* A);


#endif // UZ_MATRIX_H
