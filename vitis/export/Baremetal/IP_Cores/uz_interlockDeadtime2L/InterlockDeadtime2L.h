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

typedef struct InterlockDeadtime2L_{
    // 'inherits' from InterlockDeadtime_hw
    InterlockDeadtime_hw hw;
    int ClockFrequencyMHz;
    bool IsReady;
    float MaxDeadtimeInMicroSeconds;
    float DeadtimeInMicroSeconds;
    void (*SetEnableOutput) (struct InterlockDeadtime2L_ *self, bool EnableOutput);
    bool (*GetEnableOutput) (const struct InterlockDeadtime2L_ *self);
    int (*SetDeadtimeInMicroseconds) (struct InterlockDeadtime2L_ *self, float DeadtimeInMicroSeconds);
    float (*GetDeadtimeInMicroseconds) (const struct InterlockDeadtime2L_ *self);
} InterlockDeadtime2L;

// Init function
int InterlockDeadtime2L_init(InterlockDeadtime2L *self, uint32_t DeviceId, uint32_t BaseAddr, int ClockFrequencyMHz, bool InverseBotSwitch, float DeadtimeInMicroSeconds);

#endif
