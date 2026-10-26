#ifndef UZ_JAVASCOPE_STATUS_H
#define UZ_JAVASCOPE_STATUS_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h> /* uz_assert uses strstr for the source filename. */
#include "../uz/uz_HAL.h"
#include "uz_platform_state_machine.h"

#define JAVASCOPE_STATUS_LED_READY       UINT32_C(0x00000001)
#define JAVASCOPE_STATUS_LED_RUNNING     UINT32_C(0x00000002)
#define JAVASCOPE_STATUS_LED_ERROR       UINT32_C(0x00000004)
#define JAVASCOPE_STATUS_LED_USER        UINT32_C(0x00000008)

/* Optional feedback hooks; cleared by the default Baremetal implementation. */
#define JAVASCOPE_STATUS_BUTTON_1         UINT32_C(0x00000010)
#define JAVASCOPE_STATUS_BUTTON_2         UINT32_C(0x00000020)
#define JAVASCOPE_STATUS_BUTTON_3         UINT32_C(0x00000040)
#define JAVASCOPE_STATUS_BUTTON_4         UINT32_C(0x00000080)
#define JAVASCOPE_STATUS_BUTTON_5         UINT32_C(0x00000100)
#define JAVASCOPE_STATUS_BUTTON_6         UINT32_C(0x00000200)
#define JAVASCOPE_STATUS_BUTTON_7         UINT32_C(0x00000400)
#define JAVASCOPE_STATUS_BUTTON_8         UINT32_C(0x00000800)
#define JAVASCOPE_STATUS_LOGGING_TRIGGER  UINT32_C(0x00001000)

/* Bits 31:30 carry the platform state; bits 29:0 keep their existing meanings.
 * Explicit codes keep the wire format independent of enum ordering.
 * Regenerate the CLI channel mapping after changing these codes.
 */
#define JAVASCOPE_PLATFORM_STATE_MASK    UINT32_C(0xC0000000)
#define JAVASCOPE_PLATFORM_IDLE          UINT32_C(0x00000000)
#define JAVASCOPE_PLATFORM_RUNNING       UINT32_C(0x40000000)
#define JAVASCOPE_PLATFORM_CONTROL       UINT32_C(0x80000000)
#define JAVASCOPE_PLATFORM_ERROR         UINT32_C(0xC0000000)

/**
 * @brief Return a status word with one bit assigned the given Boolean value.
 * @param status Original status word; passed by value and not modified.
 * @param flag Exactly one bit in positions 0 through 29; invalid masks assert.
 * @param enabled True sets the flag, false clears it. Repeated calls do not toggle.
 * @return Updated status with every other bit preserved.
 */
static inline uint32_t uz_javascope_set_status_bit(uint32_t status, uint32_t flag, bool enabled);

/**
 * @brief Return a status word with the current platform state in bits 31:30.
 * @param status Original status word; passed by value and not modified.
 * @param state One of the four platform_state_t values; invalid values assert.
 * @return Updated status with bits 29:0 preserved.
 */
static inline uint32_t uz_javascope_set_platform_state(uint32_t status, platform_state_t state);

static inline uint32_t uz_javascope_set_status_bit(uint32_t status, uint32_t flag, bool enabled) {
	uz_assert(flag != UINT32_C(0));
	uz_assert((flag & (flag - UINT32_C(1))) == UINT32_C(0));
	uz_assert((flag & JAVASCOPE_PLATFORM_STATE_MASK) == UINT32_C(0));

	uint32_t updated_status = status;
	if (enabled) {
		updated_status |= flag;
	} else {
		updated_status &= ~flag;
	}
	return updated_status;
}

static inline uint32_t uz_javascope_set_platform_state(uint32_t status, platform_state_t state) {
	uint32_t encoded_state = JAVASCOPE_PLATFORM_ERROR;
	switch (state) {
	case idle_state:
		encoded_state = JAVASCOPE_PLATFORM_IDLE;
		break;
	case running_state:
		encoded_state = JAVASCOPE_PLATFORM_RUNNING;
		break;
	case control_state:
		encoded_state = JAVASCOPE_PLATFORM_CONTROL;
		break;
	case error_state:
		encoded_state = JAVASCOPE_PLATFORM_ERROR;
		break;
	default:
		uz_assert(false);
		break;
	}
	return (status & ~JAVASCOPE_PLATFORM_STATE_MASK) | encoded_state;
}

#endif
