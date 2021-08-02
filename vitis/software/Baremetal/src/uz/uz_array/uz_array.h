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
    ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


typedef struct uz_array_float_t
{
    const size_t length; // length of the vector
    float * const data; // const pointer to data
}uz_array_float_t;

typedef struct uz_array_uint32_t
{
    const size_t length; // length of the vector
    uint32_t * const data; // const pointer to data
}uz_array_uint32_t;

typedef struct uz_array_int32_t
{
    const size_t length; // length of the vector
    int32_t * const data; // const pointer to data
}uz_array_int32_t;

typedef struct uz_array_int16_t
{
    const size_t length; // length of the vector
    int16_t * const data; // const pointer to data
}uz_array_int16_t;

typedef struct uz_array_uint16_t
{
    const size_t length; // length of the vector
    uint16_t * const data; // const pointer to data
}uz_array_uint16_t;

#endif // UZ_ARRAY_H
