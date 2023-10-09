#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdlib.h>
#include "uz_mtwister.h"
#include "uz_math.h"

void export_histogram(float *array, uint32_t size);

void setUp(void)
{
}

void tearDown(void)
{
}


void uz_twister_init(void)
{
  uz_mtwister_init(2U);
}

#define ARRAY_LENGTH_MEAN_TEST 5000U

void test_uz_random_normal_float_distribution_mean50(void)
{
  // use mtwister, calculate double between 0 and 1 and scale it to Randmax
  // double randmax = 500; seedRand(0)

  uz_mtwister_t *test_instace = uz_mtwister_init(2U);
  float mean = 50.0f;
  float std = 0.5f;
  float array[ARRAY_LENGTH_MEAN_TEST] = {0.0f};
  for (uint32_t i = 0; i < ARRAY_LENGTH_MEAN_TEST; i++)
  {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    float rand = uz_mtwister_random_normal_float(test_instace, mean, std);
    // printf("%f\n", (double)rand);
    array[i] = rand;
  }
  export_histogram(array, ARRAY_LENGTH_MEAN_TEST);
  float mean_sampled = uz_math_mean(array, ARRAY_LENGTH_MEAN_TEST);
  float std_sampled = uz_math_standard_deviation(array, ARRAY_LENGTH_MEAN_TEST);
  TEST_ASSERT_FLOAT_WITHIN(0.1f,mean, mean_sampled);
  TEST_ASSERT_FLOAT_WITHIN(0.01f, std, std_sampled);
  // check with matlab plot histogram and x,y
}

void test_uz_random_normal_float_distribution_mean0(void)
{
  // use mtwister, calculate double between 0 and 1 and scale it to Randmax
  // double randmax = 500; seedRand(0)

  uz_mtwister_t *test_instace = uz_mtwister_init(2U);
  float mean = 0.0f;
  float std = 5.0f;
  float array[ARRAY_LENGTH_MEAN_TEST] = {0.0f};
  for (uint32_t i = 0; i < ARRAY_LENGTH_MEAN_TEST; i++)
  {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    float rand = uz_mtwister_random_normal_float(test_instace, mean, std);
    // printf("%f\n", (double)rand);
    array[i] = rand;
  }
  export_histogram(array, ARRAY_LENGTH_MEAN_TEST);
  float mean_sampled = uz_math_mean(array, ARRAY_LENGTH_MEAN_TEST);
  float std_sampled = uz_math_standard_deviation(array, ARRAY_LENGTH_MEAN_TEST);
  TEST_ASSERT_FLOAT_WITHIN(0.1f, mean, mean_sampled);
  TEST_ASSERT_FLOAT_WITHIN(0.01f, std, std_sampled);
  // check with matlab plot histogram and x,y
}

// void test_uz_twister_floats(void)
// {
//   // use mtwister, calculate double between 0 and 1 and scale it to Randmax
//   // double randmax = 500; seedRand(0)
//   MTRand r = seedRand(1);
//   uint32_t length = 5;
//   double array[5] = {0.0f};
//   for (uint32_t i = 0; i < length; i++)
//   {
//     double rand = generate_random_uniform_double(&r);
//     printf("%f\n", rand);
//     array[i] = rand;
//   }
// }

// void test_uint_32_t_array(void)
// {
//   MTRand r = seedRand(1);
//   float min_val = 1.0f;
//   float max_val = 3.0f;
//   uint32_t size = 5;
//   uint32_t array[5] = {0};
//   genRand_uint32_t_array(array, &r, size, min_val, max_val);
//   uint32_t expectedarray[5] = {2, 2, 2, 2, 2};
//   TEST_ASSERT_UINT32_ARRAY_WITHIN(1, expectedarray, array, UZ_MATRIX_SIZE(array));
// }

// void test_uint_32_t_array_high_numbers(void)
// {
//   MTRand r = seedRand(1);
//   float min_val = 0.0f;
//   float max_val = 200000000.0f;
//   uint32_t size = 50;
//   uint32_t array[50] = {0};
//   genRand_uint32_t_array(array, &r, size, min_val, max_val);
//   FILE *file1 = fopen("test/uz/uz_dqn/randnumbers.csv", "w");
//   if (file1 != NULL)
//   {
//     for (u_int32_t i = 0; i < size; i++)
//     {
//       fprintf(file1, "%d,%.4f\n", i, (double)array[i]);
//     }
//   }
// }

// void test_uint_32_t(void)
// {
//   MTRand r = seedRand(1);
//   float max_val = 5;
//   uint32_t output[200] = {0};
//   for (uint32_t i = 0; i < 200; i++)
//   {
//     output[i] = genRand_uint32_t(&r, max_val);
//   }
//   float x = 2.0f;
// }

// void test_uint_32_t_action(void)
// {
//   MTRand r = seedRand(1);
//   float max_val = 3;
//   uint32_t output[200] = {0};
//   for (uint32_t i = 0; i < 200; i++)
//   {
//     output[i] = genRand_uint32_t(&r, max_val);
//   }
//   float x = 2.0f;
// }

void export_histogram(float *array, uint32_t size)
{
  FILE *file1 = fopen("test/uz/uz_mtwister/randboxmueller.csv", "w");
  if (file1 != NULL)
  {
    for (u_int32_t i = 0; i < size; i++)
    {
      fprintf(file1, "%d,%.4f\n", i, (double)array[i]);
    }
  }
}



#endif // TEST