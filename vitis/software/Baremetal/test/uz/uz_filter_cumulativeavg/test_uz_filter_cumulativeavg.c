#ifdef TEST

#include "unity.h"

#include "uz_filter_cumulativeavg.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_filter_cumulativeavg_init(void)
{
    uz_filter_cumulativeavg_t *testinstance = uz_filter_cumulativeavg_init();
}

void test_uz_filter_cumulativeavg_some_values(void)
{
    uz_filter_cumulativeavg_t *testinstance = uz_filter_cumulativeavg_init();

    float values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float expected_mean = 5.5f;
    float mean = 0.0f;
    for (int i = 0; i < 10; i++)
    {
        mean = uz_filter_cumulativeavg_step(testinstance, values[i]);
    }
    TEST_ASSERT_EQUAL_FLOAT(expected_mean, mean);

    uz_filter_cumulativeavg_reset(testinstance);
    for (int i = 0; i < 10; i++)
    {
        mean = uz_filter_cumulativeavg_step(testinstance, values[i]);
    }
    TEST_ASSERT_EQUAL_FLOAT(expected_mean, mean);
}

#endif // TEST
