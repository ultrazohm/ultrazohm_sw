#pragma once

#include <xtmrctr.h>
#include "xparameters.h"

void uz_SystemTime_init();
void uz_SystemTime_update();
void uz_SystemTime_ReadTimer();

// Getter functions
float uz_SystemTime_GetIsrPeriodInUs();
float uz_SystemTime_GetIsrExectionTimeInUs();
uint64_t uz_SystemTime_GetInterruptCounter();
uint64_t uz_SystemTime_GetUptimeInUs();
unsigned int uz_SystemTime_GetUptimeInMs();
unsigned int uz_SystemTime_GetUptimeInSec();
unsigned int uz_SystemTime_GetUptimeInMin();
