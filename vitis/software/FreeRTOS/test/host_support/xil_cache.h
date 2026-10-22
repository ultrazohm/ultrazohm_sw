#ifndef HOST_XIL_CACHE_H
#define HOST_XIL_CACHE_H
#include <stdint.h>
static inline void Xil_DCacheInvalidateRange(uintptr_t address, uint32_t length) {
    (void)address; (void)length;
}
static inline void Xil_DCacheFlushRange(uintptr_t address, uint32_t length) {
    (void)address; (void)length;
}
#endif
