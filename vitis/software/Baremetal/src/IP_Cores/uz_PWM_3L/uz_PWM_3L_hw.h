#ifndef UZ_PWM_3L_HW_H
#define UZ_PWM_3L_HW_H

#include <stdint.h>
#include <stdbool.h>
#include "uz_PWM_3L_private.h"

typedef struct PWM_3L PWM_3L;
typedef struct PWM_3L* PWM_3L_handle;


void uz_PWM_3L_hw_set_carrier_f(uint32_t base_address, uint32_t f_carrier_hz);
void uz_PWM_3L_hw_enable_IP_core(uint32_t base_address, bool enable);
void uz_PWM_3L_hw_set_u1(uint32_t base_address, float u1);

/**
 * @brief sets input source for duty cycle.
 *
 * @param base_address  //base address of the instance
 * @param mode: 1 (PWM over AXI), 2 (PWM over PL)
 */
void uz_PWM_3L_hw_set_mode(uint32_t base_address, uint8_t mode);

/**
 * @brief sets sampling mode for duty cycle.
 *
 * @param base_address  //base address of the instance
 * @param samplingMode:
 * 			1: Duty cycle is sampled at carrier max (synchronous)
 * 			2: Duty cycle is sampled at carrier min	(synchronous)
 * 			3: Duty cycle is sampled at carrier min and max (asynchronous)
 * 			4: Duty cycle is sampled at f_clk of IP block
 */
void uz_PWM_3L_hw_set_sampligPoint(uint32_t base_address, uint8_t samplingMode);
void uz_PWM_3L_get_switch_states(uint32_t base_address, uint8_t states[][4]);
void uz_PWM_3L_hw_set_min_PW(uint32_t base_address, uint32_t min_pw_ns);
uint32_t uz_PWM_3L_hw_enable_IP_core_readback(uint32_t base_address);
uint32_t uz_PWM_3L_hw_u1_readback(uint32_t base_address);
uint32_t uz_PWM_3L_hw_get_carrier(uint32_t base_address);
uint32_t uz_PWM_3L_hw_carrier_f_readback(uint32_t base_address);
#endif // UZ_PWM_3L_HW_H
