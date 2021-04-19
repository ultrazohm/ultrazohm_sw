#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

typedef struct uz_axiTestIP uz_axiTestIP;
typedef struct uz_axiTestIP *uz_axiTestIP_handle;

uz_axiTestIP_handle uz_axiTestIP_init(uz_axiTestIP_handle self);
void uz_axiTestIP_set_A_int32(uz_axiTestIP_handle self, int32_t A);
void uz_axiTestIP_set_B_int32(uz_axiTestIP_handle self, int32_t B);
int32_t uz_axiTestIP_get_C_int32(uz_axiTestIP_handle self);
void uz_axiTestIP_set_A_float(uz_axiTestIP_handle self, float A);
void uz_axiTestIP_set_B_float(uz_axiTestIP_handle self, float B);
float uz_axiTestIP_get_C_float(uz_axiTestIP_handle self);
