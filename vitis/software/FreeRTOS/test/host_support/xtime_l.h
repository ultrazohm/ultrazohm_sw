#ifndef HOST_XTIME_L_H
#define HOST_XTIME_L_H
#include <stdint.h>
typedef uint64_t XTime;
#define COUNTS_PER_SECOND 33333332U
static inline void XTime_GetTime(XTime *value) {
    static uint64_t ticks;
    ticks += 100U;
    *value = ticks;
}
#endif
