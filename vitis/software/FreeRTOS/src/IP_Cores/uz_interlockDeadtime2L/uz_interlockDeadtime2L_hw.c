/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Tobias Schindler
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "uz_interlockDeadtime2L_hw.h"
#include "uz_interlockDeadtime2L_hwAddresses.h"

void uz_interlockDeadtime2L_hw_set_reset(uint32_t base_address, bool reset) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + IPCore_Reset_uz_interlockDeadtime2L, reset);
}

void uz_interlockDeadtime2L_hw_set_enable(uint32_t base_address, bool enable) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + IPCore_Enable_uz_interlockDeadtime2L, enable);
}

void uz_interlockDeadtime2L_hw_set_inverseBotSwitch(uint32_t base_address, bool inverse_bottom_switch) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + axi_InverseBotSwitch_Data_uz_interlockDeadtime2L, inverse_bottom_switch);
}

void uz_interlockDeadtime2L_hw_set_delayCycles(uint32_t base_address, int delay_cycles) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert(delay_cycles >= 0);
	uz_assert(delay_cycles < UZ_INTERLOCKDEADTIME2L_HW_MAX_DELAY_CYCLES);
	uz_axi_write_uint32(base_address + axi_DelayCycles_Data_uz_interlockDeadtime2L, delay_cycles);
}

void uz_interlockDeadtime2L_hw_set_enableOutput(uint32_t base_address, bool enable_output) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + axi_EnableOutput_Data_uz_interlockDeadtime2L, enable_output);
}

bool uz_interlockDeadtime2L_hw_get_inverseBotSwitch(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_bool(base_address + axi_fb_InverseBotSwitch_Data_uz_interlockDeadtime2L));
}

int uz_interlockDeadtime2L_hw_get_delayCycles(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_uint32(base_address + axi_fb_DelayCycles_Data_uz_interlockDeadtime2L));
}

bool uz_interlockDeadtime2L_hw_get_enableOutput(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_bool(base_address + axi_fb_enable_Data_uz_interlockDeadtime2L));
}
