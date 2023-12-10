// #ifdef TEST

// #include "unity.h"
// #include "test_assert_with_exception.h"
// #include "uz_mtwister.h"
// #include "uz_math.h"
// #include "export_array.h"

// void setUp(void)
// {
// }

// void tearDown(void)
// {
// }

// void uz_twister_init(void)
// {
//   uz_mtwister_init(2U);
// }

// #define ARRAY_LENGTH_MEAN_TEST 5000U
// static void sample_normal_distribution_test_helper(float *mean_sampled, float *std_sampled, float mean, float std);

// void test_uz_random_normal_float_distribution_mean50(void)
// {
//   float mean = 50.0f;
//   float std = 0.5f;
//   float mean_sampled = 0.0f;
//   float std_sampled = 0.0f;
//   sample_normal_distribution_test_helper(&mean_sampled, &std_sampled, mean, std);
//   TEST_ASSERT_FLOAT_WITHIN(0.1f, mean, mean_sampled);
//   TEST_ASSERT_FLOAT_WITHIN(0.01f, std, std_sampled);
// }

// void test_uz_random_normal_float_distribution_mean0(void)
// {
//   float mean = 0.0f;
//   float std = 5.0f;
//   float mean_sampled = 0.0f;
//   float std_sampled = 0.0f;
//   sample_normal_distribution_test_helper(&mean_sampled, &std_sampled, mean, std);
//   TEST_ASSERT_FLOAT_WITHIN(0.1f, mean, mean_sampled);
//   TEST_ASSERT_FLOAT_WITHIN(0.01f, std, std_sampled);
// }

// void test_uz_random_normal_float_distribution_mean_negative(void)
// {
//   float mean = -10.0f;
//   float std = 5.0f;
//   float mean_sampled = 0.0f;
//   float std_sampled = 0.0f;
//   sample_normal_distribution_test_helper(&mean_sampled, &std_sampled, mean, std);
//   TEST_ASSERT_FLOAT_WITHIN(0.1f, mean, mean_sampled);
//   TEST_ASSERT_FLOAT_WITHIN(0.01f, std, std_sampled);
// }

// void test_uz_random_uniform_normal_float_distribution(void)
// {
//   uz_mtwister_t *test_instace = uz_mtwister_init(2U);
//   float array[ARRAY_LENGTH_MEAN_TEST] = {0.0f};
//   for (uint32_t i = 0; i < ARRAY_LENGTH_MEAN_TEST; i++)
//   {
//     // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
//     float rand = uz_mtwister_random_uniform_float(test_instace);
//     // printf("%f\n", (double)rand);
//     array[i] = rand;
//   }
//   float mean_sampled = uz_math_mean(array, ARRAY_LENGTH_MEAN_TEST);
//   float std_sampled = uz_math_standard_deviation(array, ARRAY_LENGTH_MEAN_TEST);
//   float mean=0.5f; // Uniform destiribution in the interval [0,1] has mean of 0.5
//   float std=(1.0f-0.0f)/sqrtf(12); // Variance of uniform distribution is (max-min)/sqrt(12) ~ 0.28
//  TEST_ASSERT_FLOAT_WITHIN(0.001f, mean, mean_sampled);
//  TEST_ASSERT_FLOAT_WITHIN(0.005f, std, std_sampled);
// }

// static void sample_normal_distribution_test_helper(float *mean_sampled, float *std_sampled, float mean, float std)
// {
//   uz_mtwister_t *test_instace = uz_mtwister_init(2U);
//   float array[ARRAY_LENGTH_MEAN_TEST] = {0.0f};
//   for (uint32_t i = 0; i < ARRAY_LENGTH_MEAN_TEST; i++)
//   {
//     // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
//     float rand = uz_mtwister_random_normal_float(test_instace, mean, std);
//     // printf("%f\n", (double)rand);
//     array[i] = rand;
//   }
//   uz_array_float_t my_array={
//     .data=array,
//     .length=UZ_ARRAY_SIZE(array)
//   };
//   *mean_sampled = uz_math_mean(my_array);
//   *std_sampled = uz_math_standard_deviation(my_array);
//   char filepath[] = "test/uz/uz_mtwister/randboxmueller.csv";
//   export_histogram(array,ARRAY_LENGTH_MEAN_TEST,filepath);
// }

// #endif // TEST