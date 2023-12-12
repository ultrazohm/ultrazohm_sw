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
 * @brief Extract a row vector from a uz_matrix_t instance, and write it to rowvector 
 * 
 * @param matrix Pointer to a uz_matrix_t instance, matrix
 * @param rowvector Pointer to a uz_matrix_t instance, rowvector 
 * @param row Row of element to extract, zero based
 */

void uz_matrix_get_row_vector_zero_based(uz_matrix_t const *const matrix,uz_matrix_t const *const rowvector, uint32_t row);

/**
 * @brief Extract a column vector from a uz_matrix_t instance, and write it to columnvector 
 * 
 * @param matrix Pointer to a uz_matrix_t instance, matrix
 * @param columnvector Pointer to a uz_matrix_t instance, columnvector 
 * @param column Column of element to extract, zero based
 */

void uz_matrix_get_column_vector_zero_based(uz_matrix_t const *const matrix,uz_matrix_t const *const columnvector, uint32_t column);
/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the multiplication is written to C_out
 */
void uz_matrix_multiply(uz_matrix_t const*const A, uz_matrix_t const*const B, uz_matrix_t* const C_out);
/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param source Matrix where the data is copied from
 * @param destination  Matrix where the data is copied to
 * @param smoothfact Smoothingfactor for Copy Data
 */
void uz_matrix_update_smooth(uz_matrix_t const *const source, uz_matrix_t *const destination, float smoothfact);
/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param source_rowvec Rowvector where the data is copied from
 * @param destination_matrix  Matrix where the data is copied to
 * @param rowind Rowindex where vector is copied
 */
void uz_matrix_copy_row_to_matrix(uz_matrix_t const *const source_rowvec, uz_matrix_t *const destination_matrix, uint32_t rowind);
/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B
 * 
 * @param source_matrix Matrix where the data is copied from
 * @param destination_rowvec  Rowvector where the data is copied to
 * @param rowind Rowindex, where rowvector is copied from the matrix
 */
void uz_matrix_copy_row_from_matrix(uz_matrix_t const *const source_matrix, uz_matrix_t *const destination_rowvec, uint32_t rowind);

/**
 * @brief Calculates the "real" matrix multiplication C_out=A * B, sets C not to zero and sums it up
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the multiplication is written to C_out
 */
void uz_matrix_multiply_acc(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out);

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
 * @brief Applies a function f, that is passed as a function pointer, to the diagonal of a uz_matrix
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param f Function pointer, function has to accept one float as argument and return one float
 */
void uz_matrix_apply_function_to_diagonal(uz_matrix_t *const A, float (*f)(float) );

/**
 * @brief Returns the value of the biggest element of the matrix
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

/**
 * @brief Copies the matrix source into the matrix destination. Requires that source and destination have the same length. Rows, columns, and data will be overwritten by this function!
 *
 * @param source Matrix to be copied
 * @param destination Matrix where the data is copied to
 */
void uz_matrix_copy(uz_matrix_t const*const source, uz_matrix_t *const destination);
/**
 * @brief Sets matrix A to a unity/identity matrix
 * 
 * @param A Pointer to a uz_matrix_t instance 
 */
void uz_matrix_set_unity_matrix(uz_matrix_t *const A);

/**
 * @brief Sets whole matrix zero except diagonal axis (see unity matrix)
 * 
 * @param A Pointer to a uz_matrix_t instance 
 */
void uz_matrix_set_zero_except_diagonal(uz_matrix_t *const A);

/**
 * @brief Calculates the elementwise product C_out= A .* B of all elements of the columncevtor A and the matrix B, differs from the uz_matrix_elemtwise_product, because it can handle different dimensions.
 * See https://de.mathworks.com/help/matlab/ref/times.html.
 * 
 * @param A Pointer to a uz_matrix_t instance, must be a Columnvector
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the elementwise product is written to C_out
 */
void uz_matrix_columnvec_matrix_product(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out);
/**
 * @brief Set a columnvector of length V to the elements of an matrix A with dimension V x V.
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param columnvector Pointer to a uz_matrix_t instance, which is a columnvector 
 */
void uz_matrix_set_columnvector_as_diagonal(uz_matrix_t *const A,uz_matrix_t *const columnvector);
/**
 * @brief Set a rowvector of length V to the diagonal elements of an matrix A with dimension V x V.
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param rowvector Pointer to a uz_matrix_t instance, which is a rowvector 
 */
void uz_matrix_set_rowvector_as_diagonal(uz_matrix_t *const A,uz_matrix_t *const rowvector);
/**
 * @brief Reshape(A,[],1),reshape(B,[],1) and then concatenate them vertically see cat(1,reshape(A,[],1),reshape(B,[],1)) in matlab
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the operation is written to C_out
 */
void uz_matrix_reshape_and_concatenate(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out);
/**
 * @brief Reshape(A,[],1),reshape(B,[],1) and then concatenate them vertically see cat(1,reshape(A,[],1),reshape(B,[],1)) in matlab,
 * !!! Attention. Does not reset the Result of the operation C_out, this have to be done manually before!
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param B Pointer to a uz_matrix_t instance 
 * @param C_out Result of the operation is written to C_out
 */

void uz_matrix_reshape_and_concatenate_acc(uz_matrix_t const *const A, uz_matrix_t const *const B, uz_matrix_t *const C_out);
/**
 * @brief Check all elements of an uz_matrix and clipp all between min and max
 * 
 * @param A Pointer to a uz_matrix_t instance 
 * @param min Minimum value for clipping 
 * @param max Maximum value for clipping
 */
void uz_matrix_clipp_values(uz_matrix_t const *const A, float min, float max);
#endif // UZ_MATRIX_H
