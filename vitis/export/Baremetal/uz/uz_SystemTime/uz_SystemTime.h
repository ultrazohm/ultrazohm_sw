#pragma once

#include <xtmrctr.h>
#include "xparameters.h"

void uz_SystemTime_init();
void uz_SystemTime_update();

void uz_SystemTime_timestamp();
void uz_SystemTime_ReadTimer();
float uz_SystemTime_StopStopwatchReturnTimeInUs();

unsigned int uz_SystemTime_GetUptimeInMs();
unsigned int uz_SystemTime_GetUptimeInSec();
unsigned int uz_SystemTime_GetUptimeInMin();
uint64_t uz_SystemTime_GetUptimeInUs();
uint64_t uz_SystemTime_GetInterruptCounter();
float uz_SystemTime_GetIsrExectionTimeInUs();
float uz_SystemTime_GetIsrPeriodInUs();
