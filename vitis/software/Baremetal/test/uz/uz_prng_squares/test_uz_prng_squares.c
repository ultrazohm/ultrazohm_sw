#ifdef TEST

#include "unity.h"

#include "uz_prng_squares.h"
#include "export_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#define NUMBER_OF_CALLS 1000

void test_uz_prng_squares_uint32(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init();
    uint32_t random_number[NUMBER_OF_CALLS];
    for (uint32_t i = 0; i < NUMBER_OF_CALLS; i++)
    {
        random_number[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    //  char filepath[] = "../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_float.csv";
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_uint32.csv";
    export_array_uint32(random_number, NUMBER_OF_CALLS, filepath);
}

void test_uz_prng_squares_float(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init();
    float random_number[NUMBER_OF_CALLS];
    for (uint32_t i = 0; i < NUMBER_OF_CALLS; i++)
    {
        random_number[i] = uz_prng_squares_get_uniform_float_zero_to_one(squares);
    }
  //  char filepath[] = "../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_float.csv";
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_float.csv";
    export_array(random_number, NUMBER_OF_CALLS, filepath);
}

#endif // TEST
