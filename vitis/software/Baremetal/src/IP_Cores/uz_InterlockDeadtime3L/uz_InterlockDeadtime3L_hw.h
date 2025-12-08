#ifndef UZ_INTERLOCKDEADTIME3L_HW_H
#define UZ_INTERLOCKDEADTIME3L_HW_H

#include <stdint.h>
#include <stdbool.h>
#include "uz_InterlockDeadtime3L_private.h"

typedef struct IntDead3L IntDead3L;
typedef struct IntDead3L* IntDead3L_handle;

/**
 * @brief enables/disables output of IP core.
 *
 * @param base_address base address of IP core instance
 * @param en: true (enable), false (disable)
 */
void uz_InterlockDeadtime3L_hw_enable_output(uint32_t base_address, bool en);

/**
 * @brief defines type of hardware.
 *
 * @param base_address base address of IP core instance
 * @param mode:
 * 			1: TNPC
 * 			2: NPC with DC/2 rating for mosfets
 * 			3: NPC with DC rating for mosfets
 */
void uz_InterlockDeadtime3L_hw_set_mode(uint32_t base_address, uint8_t mode);

/**
 * @brief sets delay of rising edge in ns.
 *
 * @param base_address base address of IP core instance
 * @param delay_ns
 */
void uz_InterlockDeadtime3L_hw_set_delay_ns(uint32_t base_address, uint32_t delay_ns);


#endif //UZ_INTERLOCKDEADTIME3L_HW_H
