#ifndef UZ_ARRAY_H
#define UZ_ARRAY_H
#include <stdint.h>
#include <stddef.h>

/**
 * @brief Standard macro to get the size of a array at compile time.
 *        See:
 *        - https://github.com/chromium/chromium/blob/HEAD/third_party/protobuf/php/ext/google/protobuf/php-upb.c
 *        - https://stackoverflow.com/questions/1598773/is-there-a-standard-function-in-c-that-would-return-the-length-of-an-array/1598827#1598827
 */
#define UZ_ARRAY_SIZE(x) \
    ((sizeof(x)/sizeof(0[x])) / ((uint32_t)(!(sizeof(x) % sizeof(0[x])))))

/**
 * @brief Array of floats with length to pass and receive from functions.
 * 
 */
typedef struct uz_array_float_t
{
    uint32_t length; /**< length of the vector - use UZ_ARRAY_SIZE makro to determine */
    float *data; /**< pointer to data */
}uz_array_float_t;

/**
 * @brief Array of uint32_t with length to pass and receive from functions.
 * 
 */
typedef struct uz_array_uint32_t
{
    uint32_t length; /**< length of the vector - use UZ_ARRAY_SIZE makro to determine */
    uint32_t *data;  /**< pointer to data */
}uz_array_uint32_t;

/**
 * @brief Array of int32_t with length to pass and receive from functions.
 * 
 */
typedef struct uz_array_int32_t
{
    uint32_t length; /**< length of the vector - use UZ_ARRAY_SIZE makro to determine */
    int32_t *data;  /**< pointer to data */
}uz_array_int32_t;

/**
 * @brief Array of int16_t with length to pass and receive from functions.
 * 
 */
typedef struct uz_array_int16_t
{
    uint32_t length; /**< length of the vector - use UZ_ARRAY_SIZE makro to determine */
    int16_t *data;  /**< pointer to data */
}uz_array_int16_t;

/**
 * @brief Array of uint16_t with length to pass and receive from functions.
 * 
 */
typedef struct uz_array_uint16_t
{
    uint32_t length; /**< length of the vector - use UZ_ARRAY_SIZE makro to determine */
    uint16_t *data;  /**< pointer to data */
}uz_array_uint16_t;

#endif // UZ_ARRAY_H
