#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "../../uz/uz_HAL.h"
#include "uz_simExpl_addr.h"

typedef struct {
	uint32_t baseAddr;
	float Vin;
	float IR;
	float Iout;
	float Vdiode;
}uz_simExpl;

typedef uz_simExpl* uz_simExpl_handle;

uz_simExpl_handle uz_simExpl_init(uint32_t baseAddr);
void uz_simExpl_setVin(uz_simExpl_handle self,float Vin);
float uz_simExpl_getIR(uz_simExpl_handle self);
float uz_simExpl_getVdiode(uz_simExpl_handle self);
float uz_simExpl_getIout(uz_simExpl_handle self);
