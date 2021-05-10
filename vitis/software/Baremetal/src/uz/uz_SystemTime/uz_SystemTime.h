#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "uz_AxiTimer64Bit.h"
#include "../uz_HAL.h"

void uz_SystemTime_init();
void uz_SystemTime_ISR_Tic(); // start the stopwatch
void uz_SystemTime_ISR_Toc(); // stop the stopwatch

// Getter functions
float uz_SystemTime_GetIsrPeriodInUs();
float uz_SystemTime_GetIsrExectionTimeInUs();
uint64_t uz_SystemTime_GetInterruptCounter();
uint64_t uz_SystemTime_GetUptimeInUs();
unsigned int uz_SystemTime_GetUptimeInMs();
unsigned int uz_SystemTime_GetUptimeInSec();
unsigned int uz_SystemTime_GetUptimeInMin();
