#include <stdint.h>
#include "../uz_HAL.h"

#include <xtmrctr.h>
#include "xparameters.h"

#define UZ_AXI_TIMER_CLOCK_FREQ XPAR_TIMER_UPTIME_64BIT_CLOCK_FREQ_HZ

void uz_AxiTimer64Bit_init();
uint64_t uz_AxiTimer64Bit_ReadValue64Bit();
