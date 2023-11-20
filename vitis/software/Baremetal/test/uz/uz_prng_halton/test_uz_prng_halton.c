#ifdef TEST

#include "unity.h"

#include "uz_prng_halton.h"
#include "uz_array.h"
#include "export_array.h"


void setUp(void)
{
}

void tearDown(void)
{
}
#define NUMBER_OF_CALLS 5000

void test_uz_prng_halton_float(void)
{
    uz_prng_halton_t *halton = uz_prng_halton_init(7U);
    float random_number[NUMBER_OF_CALLS];
    uz_array_float_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_halton_get_uniform_float(halton);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_halton/uz_prng_halton_float.csv";
    export_array_float(random_array, filepath);
}

#endif // TEST
