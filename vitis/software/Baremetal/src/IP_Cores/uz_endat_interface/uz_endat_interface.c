/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2025 Michael Hoerner
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

#include "uz_endat_interface.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_ENDAT_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_endat_interface.h" 
#include "uz_endat_interface_hw.h" 
#include "../../uz/uz_signals/uz_signals.h"

#define RAD_PER_SECOND_TO_RPM (30.0f/UZ_PIf)
struct uz_endat_interface_t {
    bool is_ready;
    struct uz_endat_interface_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_endat_interface_t instances[UZ_ENDAT_INTERFACE_MAX_INSTANCES] = { 0 };

static uz_endat_interface_t* uz_endat_interface_allocation(void);
static uint32_t ceil_div(uint32_t a, uint32_t b);

static uz_endat_interface_t* uz_endat_interface_allocation(void){
    uz_assert(instance_counter < UZ_ENDAT_INTERFACE_MAX_INSTANCES);
    uz_endat_interface_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_endat_interface_t* uz_endat_interface_init(struct uz_endat_interface_config_t config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    uz_assert_not_zero_uint32(config.endat_clk_frequency_Hz);
    uz_assert_not_zero_uint32(config.endat_encoder_bit_width_single_turn);
    uz_assert_not_zero_uint32(config.machine_polepairs);
    uz_endat_interface_t* self = uz_endat_interface_allocation();
    self->config=config;
    uz_endat_interface_set_config(self);
    return (self);
}

void uz_endat_interface_set_config(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert((self->config.endat_encoder_bit_width_multi_turn + self->config.endat_encoder_bit_width_single_turn + self->config.endat_encoder_number_of_CRC_bits) <= 64U);
    // calculate endat clock divider from ip core clock frequency and endat clock frequency
    uint32_t endat_clk_divider = ceil_div(self->config.ip_clk_frequency_Hz, (2U*self->config.endat_clk_frequency_Hz));
    // write configuration
    uz_endat_interface_hw_write_endat_clock_divider(self->config.base_address, endat_clk_divider);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(self->config.base_address, self->config.endat_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(self->config.base_address, self->config.endat_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits(self->config.base_address, self->config.endat_encoder_number_of_CRC_bits);
    uz_endat_interface_hw_write_pll_parameters(self->config.base_address, self->config.sampling_interval_seconds, self->config.kp_pll, self->config.ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs(self->config.base_address, self->config.machine_polepairs);
    uz_endat_interface_set_mechanical_offset_endat_single_turn(self, self->config.position_mech_offset_si_single_turn);
}

uint32_t uz_endat_interface_get_position_raw_single_turn(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_position_raw_single_turn(self->config.base_address));
}

uint32_t uz_endat_interface_get_position_raw_multi_turn(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_position_raw_multi_turn(self->config.base_address));
}

uint32_t uz_endat_interface_get_position_multi_turn(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_position_multi_turn(self->config.base_address));
}

float uz_endat_interface_get_position_mech_si_single_turn(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_position_mech_si_single_turn(self->config.base_address));
}

float uz_endat_interface_get_position_el_si_single_turn(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_position_el_si_single_turn(self->config.base_address));
}

float uz_endat_interface_get_speed_mech_si(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_speed_mech_si(self->config.base_address));
}

float uz_endat_interface_get_speed_el_si(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_speed_el_si(self->config.base_address));
}

float uz_endat_interface_get_speed_mech_rpm(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_endat_interface_hw_read_speed_mech_rpm(self->config.base_address));
}

void uz_endat_interface_enable_ip(uz_endat_interface_t *self, bool ip_core_off_on) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_endat_interface_hw_write_ip_core_enable(self->config.base_address, ip_core_off_on);
}

void uz_endat_interface_set_mechanical_offset_endat_single_turn(uz_endat_interface_t *self, float position_mech_offset_si_single_turn) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);   

    uint32_t bit_count_single_turn = (1U << self->config.endat_encoder_bit_width_single_turn) - 1U;
    int32_t position_mech_offset_ticks_single_turn = (float)(bit_count_single_turn) / (2.0f * UZ_PIf) * position_mech_offset_si_single_turn;
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn(self->config.base_address, position_mech_offset_ticks_single_turn);
}

void uz_endat_interface_set_mode_command(uz_endat_interface_t *self, uint32_t mode_command) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_endat_interface_hw_write_endat_mode_command(self->config.base_address, mode_command);
}

/**
 * @brief Calculates the ceiled value of an unsigned integer division.
 * @brief Attention: Does not catch overflow of (a+b)>UINT32_MAX.
 *
 * @param a Dividend
 * @param b Divisor
 *
 * @return Ceiled unsigned integer division
 */
static uint32_t ceil_div(uint32_t a, uint32_t b) {
    uz_assert(b !=0U);
    return (a + b - 1U) / b;
}

#endif
