#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct uz_ipCore uz_ipCore;

uz_ipCore* uz_ipCore_init(uz_ipCore* self);
void uz_ipCore_set_variable(uz_ipCore* self,int variable);
int uz_ipCore_get_variable(uz_ipCore* self);