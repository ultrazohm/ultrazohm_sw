#ifndef UZ_PWM_3L_HW_H
#define UZ_PWM_3L_HW_H

#include <stdint.h>
#include <stdbool.h>
#include "uz_PWM_3L_private.h"

typedef struct PWM_3L PWM_3L;
typedef struct PWM_3L* PWM_3L_handle;


void uz_PWM_3L_hw_set_carrier_f(uint32_t base_address, uint32_t f_carrier_hz);
void uz_PWM_3L_hw_enable_IP_core(uint32_t base_address);
void uz_PWM_3L_hw_set_u1(uint32_t base_address, float u1);
void uz_PWM_3L_get_switch_states(uint32_t base_address, uint8_t states[][4]);
uint32_t uz_PWM_3L_hw_enable_IP_core_readback(uint32_t base_address);
uint32_t uz_PWM_3L_hw_u1_readback(uint32_t base_address);
uint32_t uz_PWM_3L_hw_get_carrier(uint32_t base_address);
uint32_t uz_PWM_3L_hw_carrier_f_readback(uint32_t base_address);
#endif // UZ_PWM_3L_HW_H
