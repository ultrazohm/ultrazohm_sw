#ifndef UZ_SS_DEBUG_HW_H
#define UZ_SS_DEBUG_HW_H

#include <stdint.h>
#include <stdbool.h>
#include "uz_SS_Debug_private.h"

typedef struct SSDebug SSDebug;
typedef struct SSDebug* SSDebug_handle;

/**
 * @brief sets the SS output.
 *
 * @param base_address base address of IP core instance
 * @param switchStates: true (enable), false (disable)
 */
void uz_SS_Debug_set(uint32_t base_address, bool switchStates []);

/**
 * @brief gets the SS output.
 *
 * @param base_address base address of IP core instance
 * @param switchStates: true (enabled), false (disabled)
 */
void uz_SS_Debug_get(uint32_t base_address, bool switchStates []);

#endif //UZ_SS_DEBUG_HW_H
