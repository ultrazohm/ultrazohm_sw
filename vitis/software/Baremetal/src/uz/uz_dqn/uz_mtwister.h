#ifndef UZ_MTWISTER_H
#define UZ_MTWISTERs_H

#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "mtwister.h"


float uz_random_box_mueller(MTRand* seed,float mean, float std);
void polar_box_muller(float *retval, uint32_t range);

#endif // UZ_DQN_H