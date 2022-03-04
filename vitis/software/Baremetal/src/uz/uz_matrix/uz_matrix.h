#ifndef UZ_MATRIX_H
#define UZ_MATRIX_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Struct for the matrix
 * 
 */
struct uz_matrix_t
{
    uint32_t length_of_data; /**< Number of data elements in the matrix, has to be calculated with UZ_MATRIX_SIZE */
    uint32_t rows; /**< Number of rows of the matrix */
    uint32_t columns; /**< Number of columns of the matrix*/
    float *data; /**< Pointer to the actual data array*/
};

/**
 * @brief Standard macro to get the size of supplied matrix data at compile time.
 *        See:
 *        - https://github.com/chromium/chromium/blob/HEAD/third_party/protobuf/php/ext/google/protobuf/php-upb.c
 *        - https://stackoverflow.com/questions/1598773/is-there-a-standard-function-in-c-that-would-return-the-length-of-an-array/1598827#1598827
 */
#define UZ_MATRIX_SIZE(x) \
    ((sizeof(x)/sizeof(0[x])) / ((uint32_t)(!(sizeof(x) % sizeof(0[x])))))

/**
 * @brief Typedef for uz_matrix_t struct
 * 
 */
typedef struct uz_matrix_t uz_matrix_t;

/**
 * @brief Initialize an uz_matrix
 * 
 * @param self Pointer to the instance
 * @param data Pointer to the data
 * @param length_of_data Number of data elements calculated by UZ_MATRIX_SIZE makro
 * @param rows Number of rows
 * @param columns Number of columns
 * @return uz_matrix_t* Returns an pointer to the instance that was passed
 */
uz_matrix_t *uz_matrix_init(uz_matrix_t *self,float *data, uint32_t length_of_data, uint32_t rows, uint32_t columns);


/**
 * @brief Returns the number of rows of the given uz_matrix
 * 
 * @param self Pointer to a uz_matrix_t instance 
 * @return uint32_t
 */
uint32_t uz_matrix_get_number_of_rows(uz_matrix_t const*const self);

/**
 * @brief Returns the number of columns of the given uz_matrix
 * 
 * @param self Pointer to a uz_matrix_t instance 
 * @return uint32_t 
 */
uint32_t uz_matrix_get_number_of_columns(uz_matrix_t const*const self);

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
float uz_matrix_get_element_zero_based(uz_matrix_t const*const A,uint32_t row, uint32_t column);

/**
 * @brief Set the element row x column of matrix A with zero based indexing.
 * 
 * @param A Matrix object
 * @param x Value that the element is set to
 * @param row Row of element to set
 * @param column Column of element to set
 */
void uz_matrix_set_element_zero_based(uz_matrix_t *const A,float x,uint32_t row, uint32_t column);


/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the multiplication is written to C_out
 */
void uz_matrix_multiply(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t* const C_out);

/**
 * @brief Calculates the elementwise product C_out= A .* B of all elements of the matrix A and B (also called Hadamard-Product)
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
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
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Sum of A and B is written to C_out
 */
void uz_matrix_sum(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t *const C_out);

/**
 * @brief Calculates C_out += A
 * 
 * @param A Pointer to a uz_matrix_t instance 
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
 * @param A Pointer to a uz_matrix_t instance 
 * @param scalar Scalar value with which each element of A is multiplied
 */
void uz_matrix_multiply_by_scalar(uz_matrix_t *const A, float scalar);

/**
 * @brief Applies a function f, that is passed as a function pointer, to each of the elements 
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param f Function pointer, function has to accept one float as argument and return one float
 */
void uz_matrix_apply_function_to_each_element(uz_matrix_t *const A, float(*f)(float) );


/**
 * @brief Retruns the value of the biggest element of the matrix
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @return float 
 */
float uz_matrix_get_max_value(uz_matrix_t const*const A);

/**
 * @brief Returns the index at which position the biggest value is located in the matrix A
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @return uint32_t 
 */
uint32_t uz_matrix_get_max_index(uz_matrix_t const*const A);

/**
 * @brief Transposes the matrix A
 * 
 * @param A Pointer to a uz_matrix_t instance 
 */
void uz_matrix_transpose(uz_matrix_t* A);


#endif // UZ_MATRIX_H
