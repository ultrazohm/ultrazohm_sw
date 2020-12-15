#ifndef INTERLOCKDEADTIME_H
#define INTERLOCKDEADTIME_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
// Xilinx library
#include "xil_assert.h"
#include "xstatus.h"

#include "InterlockDeadtime_hw.h"
//#include "xil_assert.h"

typedef struct InterlockDeadtime_{
    // 'inherits' from InterlockDeadtime_hw
    InterlockDeadtime_hw hw;
    int ClockFrequencyMHz;
    bool IsReady;
    float DeadtimeInMicroSeconds;
    int (*SetEnableOutput) (struct InterlockDeadtime_ *self, bool EnableOutput);
    bool (*GetEnableOutput) (const struct InterlockDeadtime_ *self);
    int (*SetDeadtimeInMicroseconds) (struct InterlockDeadtime_ *self, float DeadtimeInMicroSeconds);
    float (*GetDeadtimeInMicroseconds) (const struct InterlockDeadtime_ *self);
} InterlockDeadtime;

// Init function
int InterlockDeadtime_init(InterlockDeadtime *self, uint32_t DeviceId, uint32_t BaseAddr, int ClockFrequencyMHz, bool InverseBotSwitch, float DeadtimeInMicroSeconds);

#endif
