#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct uz_ipCore uz_ipCore;
typedef uz_ipCore *uz_ipCore_handle;

uz_ipCore_handle uz_ipCore_init(uz_ipCore_handle self);
void uz_ipCore_setVariable(uz_ipCore_handle self,int variable);
int uz_ipCore_getVariable(uz_ipCore_handle self);