/*----------------------------------------------------------------------------
| platform_baremetal.c
|   Bare-metal Cortex-R5 platform backend for the XCPlite engine (Option Z).
|   Replaces platform_freertos.c / platform.c for the R5 control core: no OS,
|   no sockets, no threads. Single core => "mutex" is an IRQ critical section
|   (the only concurrency is ISR_Control's XcpEvent vs the main-loop pump).
|
|   Implements exactly the platform symbols the engine needs:
|     mutexInit/mutexDestroy/platformMutexLock/platformMutexUnlock
|     clockInit/clockGet/clockGetString
|
|   UltraZohm integration: Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "platform.h"
#include <stdio.h>   /* snprintf */
#include <stdint.h>

/* uz_SystemTime free-running 1 us uptime clock (UZ Baremetal lib). */
extern uint64_t uz_SystemTime_GetUptimeInUs(void);

/**************************************************************************/
/* Mutex == IRQ critical section (ARMv7-R), nesting-safe                   */
/**************************************************************************/

static volatile uint32_t s_crit_nesting = 0u;
static volatile uint32_t s_saved_irq_disabled = 0u; /* CPSR I-bit (0x80) at outermost lock */

void platformMutexLock(MUTEX *m) {
    (void)m;
    uint32_t cpsr;
    __asm volatile("mrs %0, cpsr" : "=r"(cpsr) :: "memory");
    __asm volatile("cpsid i" ::: "memory"); /* disable IRQ */
    if (s_crit_nesting++ == 0u) {
        s_saved_irq_disabled = cpsr & 0x80u; /* remember whether IRQ was already off */
    }
}

void platformMutexUnlock(MUTEX *m) {
    (void)m;
    if (s_crit_nesting > 0u && --s_crit_nesting == 0u && s_saved_irq_disabled == 0u) {
        __asm volatile("cpsie i" ::: "memory"); /* re-enable IRQ only if it was on before */
    }
}

void mutexInit(MUTEX *m, bool recursive, uint32_t spinCount) {
    (void)recursive; (void)spinCount;
    if (m != NULL) *m = 0u; /* storage unused; the critical section is global */
}

void mutexDestroy(MUTEX *m) {
    (void)m;
}

/**************************************************************************/
/* Clock — 1 us, arbitrary epoch, from uz_SystemTime                       */
/**************************************************************************/

bool clockInit(void) {
    return true; /* uz_SystemTime is initialised by the Baremetal app */
}

uint64_t clockGet(void) {
    return uz_SystemTime_GetUptimeInUs();
}

char *clockGetString(char *s, uint32_t l, uint64_t c) {
    snprintf(s, l, "%gs", (double)c / CLOCK_TICKS_PER_S);
    return s;
}
