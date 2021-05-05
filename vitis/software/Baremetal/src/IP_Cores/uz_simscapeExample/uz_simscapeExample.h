#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_SystemTime/uz_SystemTime.h"

typedef struct uz_simscapeExample uz_simscapeExample;
typedef struct uz_simscapeExample *uz_simscapeExample_handle;

uz_simscapeExample_handle uz_simscapeExample_init(uz_simscapeExample_handle self);
void uz_simscapeExample_step_model_once(uz_simscapeExample_handle self);

