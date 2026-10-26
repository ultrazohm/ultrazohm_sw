#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "uz_platform_state_machine.h"

/* Named masks for individual status flags. */
#define JAVASCOPE_STATUS_LED_READY       UINT32_C(0x00000001)
#define JAVASCOPE_STATUS_LED_RUNNING     UINT32_C(0x00000002)
#define JAVASCOPE_STATUS_LED_ERROR       UINT32_C(0x00000004)
#define JAVASCOPE_STATUS_LED_USER        UINT32_C(0x00000008)

/* Prepared feedback hooks; currently not populated by Baremetal. */
#define JAVASCOPE_STATUS_BUTTON_1        UINT32_C(0x00000010)
#define JAVASCOPE_STATUS_BUTTON_2        UINT32_C(0x00000020)
#define JAVASCOPE_STATUS_BUTTON_3        UINT32_C(0x00000040)
#define JAVASCOPE_STATUS_BUTTON_4        UINT32_C(0x00000080)
#define JAVASCOPE_STATUS_BUTTON_5        UINT32_C(0x00000100)
#define JAVASCOPE_STATUS_BUTTON_6        UINT32_C(0x00000200)
#define JAVASCOPE_STATUS_BUTTON_7        UINT32_C(0x00000400)
#define JAVASCOPE_STATUS_BUTTON_8        UINT32_C(0x00000800)
#define JAVASCOPE_STATUS_LOGGING_TRIGGER UINT32_C(0x00001000)

/* Set or clear a named flag, preserving every other bit in the word. */
static inline void javascope_status_set_flag(uint32_t *status, uint32_t flag, bool enabled)
{
    if (enabled) {
        *status |= flag;
    } else {
        *status &= ~flag;
    }
}

/* JavaScope status bits 31:30 carry the platform state. Bits 29:0 retain
 * their existing LED, button and ParameterID meanings. No validity flag.
 * Keep these wire codes in sync with uz_cli/src/protocol.rs.
 */
#define JAVASCOPE_PLATFORM_STATE_MASK    UINT32_C(0xC0000000)
#define JAVASCOPE_PLATFORM_IDLE          UINT32_C(0x00000000)
#define JAVASCOPE_PLATFORM_RUNNING       UINT32_C(0x40000000)
#define JAVASCOPE_PLATFORM_CONTROL       UINT32_C(0x80000000)
#define JAVASCOPE_PLATFORM_ERROR         UINT32_C(0xC0000000)

/* Explicit mapping keeps the wire format independent of enum ordering. */
static inline uint32_t javascope_status_with_platform_state(
    uint32_t status, platform_state_t state)
{
    uint32_t encoded_state;
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
    default:
        encoded_state = JAVASCOPE_PLATFORM_ERROR;
        break;
    }
    return (status & ~JAVASCOPE_PLATFORM_STATE_MASK) | encoded_state;
}
