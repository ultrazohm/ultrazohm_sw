#ifndef VA_CONTROL_H
#define VA_CONTROL_H

#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

/*
 * Central VA machine protection limits.
 * The PMSM controller latches a safe-operating-region violation when one of
 * these limits is exceeded. The ISR then switches the platform to error_state.
 */
#define VA_PROTECTION_MAX_SPEED_RPM       1000.0f
#define VA_PROTECTION_MAX_DC_VOLTAGE_V      30.0f
#define VA_PROTECTION_MIN_DC_VOLTAGE_V      20.0f
#define VA_PROTECTION_MAX_PHASE_CURRENT_A   15.0f
#define VA_PROTECTION_MAX_DQ_CURRENT_A      15.0f

uz_pmsm_control_t *va_control_init(void);

#endif
