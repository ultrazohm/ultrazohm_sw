#ifdef TEST

#include "unity.h"
#include <stddef.h>
#include <stdint.h>
#include "uz_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_array_float_initialization(void)
{
     // The data itself has to be initialized independed of the array data type.
     // Take care regarding the scope of this value, e.g., if it is inside a function the scope is automatic
     // automatic = variable is "gone" as soon as the function is finished, thus never return a pointer / the array data type to a automatic storage duration variable
    float data[5] = {1.12f, 2.87f, 3.3f, 4.6f, 51.5f};
    uz_array_float_t testarray = {
        .length = UZ_ARRAY_SIZE(data), // ALWAYS use the UZ_ARRAY_SIZE makro in the initialization of the length of the array
        .data = &data[0]}; // Pointer to the first element of the actual data of the array
    // This test is using an for-loop to highligth how the .length variable is inteded to be used
    for (size_t i = 0; i++; i < testarray.length)
    {
        TEST_ASSERT_EQUAL_FLOAT(data[i], testarray.data[i]);
    }
}

void test_uz_array_uint32_t_initialization(void)
{
    uint32_t data[5] = {1, 2, 3, 4, 5};
    uz_array_uint32_t testarray = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(data, testarray.data, testarray.length);
}

void test_uz_array_int32_t_initialization(void)
{
    int32_t data[5] = {-1, 2, -3, 4, -5};
    uz_array_int32_t testarray = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_EQUAL_INT32_ARRAY(data, testarray.data, testarray.length);
}


void test_uz_array_int16_t_initialization(void)
{
    int16_t data[5] = {-1, 2, -3, 4, -5};
    uz_array_int16_t testarray = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_EQUAL_INT16_ARRAY(data, testarray.data, testarray.length);
}

void test_uz_array_uint16_t_initialization(void)
{
    uint16_t data[5] = {1, 2, 3, 4, 5};
    uz_array_uint16_t testarray = {
        .length = UZ_ARRAY_SIZE(data),
        .data = &data[0]};
    TEST_ASSERT_EQUAL_UINT16_ARRAY(data, testarray.data, testarray.length);
}

#endif // TEST
