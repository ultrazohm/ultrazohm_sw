#ifdef TEST

#include "unity.h"

#include "uz_prng_mtwister.h"
#include "mt19937.h"
#include "uz_array.h"
#include "export_array.h"

#define NUMBER_OF_CALLS 5000

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_prng_mtwister_init(void)
{
    uz_prng_mtwister_t *twister = uz_prng_mtwister_init(0U);
}

void test_uz_prng_squares_uint32(void)
{
    uz_prng_mtwister_t *mtwister = uz_prng_mtwister_init(0U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_mtwister_get_uniform_uint32(mtwister);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_mtwister/uz_prng_mtwister_uint32.csv";
    export_array_uint32(random_array, filepath);
}

#endif // TEST
