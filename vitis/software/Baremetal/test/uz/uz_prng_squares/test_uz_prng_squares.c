#ifdef TEST

#include "unity.h"

#include "uz_prng_squares.h"
#include "export_array.h"
#include "uz_array.h"
#include "uz_math.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#define NUMBER_OF_CALLS 5000

void test_uz_prng_squares_uint32(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(0U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array={
        .data=random_number,
        .length=UZ_ARRAY_SIZE(random_number)
    };

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    char filepath[] = "test/uz/uz_prng_squares/uz_prng_squares_uint32.csv";
    export_array_uint32(random_array, filepath);
}



#endif // TEST
