#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include <stdlib.h>
#include "uz_mtwister.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_box_mueller_rand(void)
{
  // use mtwister, calculate double between 0 and 1 and scale it to Randmax
  //double randmax = 500; seedRand(0) 
  MTRand r = seedRand(1);
  float mean = 2.0f;
  float std = 10.5f;
  for(uint32_t i=0; i<200; i++) {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    float rand = uz_random_box_mueller(&r, mean, std);
    printf("%f\n", (double)rand);
  }
}

#endif // TEST