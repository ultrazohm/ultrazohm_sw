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
  float mean = 50.0f;
  float std = 0.5f;
  uint32_t length = 5000;
  float array[5000] = {0.0f};
  for(uint32_t i=0; i<length; i++) {
    // uint kann nicht in der Funktion gecastet werden, sonst kann man nichts mehr skalieren, es kommt nur 0 und 1 raus
    float rand = uz_random_box_mueller(&r, mean, std);
    printf("%f\n", (double)rand);
    array[i]= rand;
  }
export_histogram(&array,length);
// check with matlab plot histogram and x,y
}

#endif // TEST