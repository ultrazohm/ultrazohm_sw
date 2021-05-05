#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

#define UZ_INTERLOCKDEADTIME2L_HW_MAX_DELAY_CYCLES 1023 // Maximum number of delay cycles is based on the bit-width of the hardware counter which is 10

void uz_interlockDeadtime2L_hw_set_reset(uint32_t base_address, bool reset);
void uz_interlockDeadtime2L_hw_set_enable(uint32_t base_address, bool enable);
void uz_interlockDeadtime2L_hw_set_inverseBotSwitch(uint32_t base_address, bool inverse_bottom_switch);
void uz_interlockDeadtime2L_hw_set_delayCycles(uint32_t base_address, int delay_cycles);
void uz_interlockDeadtime2L_hw_set_enableOutput(uint32_t base_address, bool enable_output);
bool uz_interlockDeadtime2L_hw_get_inverseBotSwitch(uint32_t base_address);
int uz_interlockDeadtime2L_hw_get_delayCycles(uint32_t base_address);
bool uz_interlockDeadtime2L_hw_get_enableOutput(uint32_t base_address);


