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
#include "../../uz/uz_math_constants.h"
#include "uz_endat_interface_hw.h" 

#define ENDAT_NUMBER_OF_CRC_BITS 5U
#define ENDAT_ENCODER_BIT_WIDTH_MAX 31U
#define ENDAT_ENCODER_POSITION_BITS_MAX 48U
#define ENDAT_FRAME_BITS_MAX 64U
#define ENDAT_CLOCK_DIVIDER_MIN 3U
#define ENDAT_CLOCK_DIVIDER_MAX 500U
#define MACHINE_POLEPAIRS_MAX 255U
#define SAMPLING_INTERVAL_MAX_SECONDS 0.0156f
#define KP_PLL_MAX 8191.0f
#define KI_PLL_MAX 262142.0f
// Largest float below INT32_MAX that can be safely cast to int32_t.
#define INT32_MAX_SAFE_FLOAT 2147483520.0f
#define POSITION_MECH_OFFSET_LIMIT_RAD (2.0f * UZ_PIf)
#define SAMPLING_DELAY_CLK_TICKS_MAX 194U
struct uz_endat_interface_t {
    bool is_ready;
    struct uz_endat_interface_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_endat_interface_t instances[UZ_ENDAT_INTERFACE_MAX_INSTANCES] = { 0 };

static uz_endat_interface_t* uz_endat_interface_allocation(void);
static void assert_self(uz_endat_interface_t *self);
static void uz_endat_interface_set_config(uz_endat_interface_t *self);
static void assert_config(struct uz_endat_interface_config_t config);
static uint32_t calculate_endat_clock_divider(uint32_t ip_clk_frequency_Hz, uint32_t endat_clk_frequency_Hz);
static int32_t calculate_position_mech_offset_ticks_single_turn(uint32_t endat_encoder_bit_width_single_turn, float position_mech_offset_si_single_turn);
static uint32_t ceil_div(uint32_t a, uint32_t b);

static uz_endat_interface_t* uz_endat_interface_allocation(void){
    uz_assert(instance_counter < UZ_ENDAT_INTERFACE_MAX_INSTANCES);
    uz_endat_interface_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static void assert_self(uz_endat_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
}

uz_endat_interface_t* uz_endat_interface_init(struct uz_endat_interface_config_t config) {
    assert_config(config);
    uz_endat_interface_t* self = uz_endat_interface_allocation();
    self->config=config;
    uz_endat_interface_set_config(self);
    return (self);
}

static void uz_endat_interface_set_config(uz_endat_interface_t *self) {
    assert_self(self);
    uint32_t endat_clk_divider = calculate_endat_clock_divider(self->config.ip_clk_frequency_Hz, self->config.endat_clk_frequency_Hz);
    uz_endat_interface_hw_write_endat_clock_divider(self->config.base_address, endat_clk_divider);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(self->config.base_address, self->config.endat_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(self->config.base_address, self->config.endat_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits(self->config.base_address, ENDAT_NUMBER_OF_CRC_BITS);
    uz_endat_interface_hw_write_pll_parameters(self->config.base_address, self->config.sampling_interval_seconds, self->config.kp_pll, self->config.ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs(self->config.base_address, self->config.machine_polepairs);
    uz_endat_interface_set_mechanical_offset_endat_single_turn(self, self->config.position_mech_offset_si_single_turn);
    uz_endat_interface_set_sampling_delay_clk_ticks(self, self->config.delay_sampling_in_clk_ticks);
}

uint32_t uz_endat_interface_get_position_raw_single_turn(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_position_raw_single_turn(self->config.base_address));
}

uint32_t uz_endat_interface_get_position_raw_multi_turn(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_position_raw_multi_turn(self->config.base_address));
}

uint32_t uz_endat_interface_get_position_multi_turn(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_position_multi_turn(self->config.base_address));
}

float uz_endat_interface_get_position_mech_si_single_turn(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_position_mech_si_single_turn(self->config.base_address));
}

float uz_endat_interface_get_position_el_si_single_turn(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_position_el_si_single_turn(self->config.base_address));
}

float uz_endat_interface_get_speed_mech_si(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_speed_mech_si(self->config.base_address));
}

float uz_endat_interface_get_speed_el_si(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_speed_el_si(self->config.base_address));
}

float uz_endat_interface_get_speed_mech_rpm(uz_endat_interface_t *self) {
    assert_self(self);
    return (uz_endat_interface_hw_read_speed_mech_rpm(self->config.base_address));
}

void uz_endat_interface_enable_ip(uz_endat_interface_t *self, bool ip_core_off_on) {
    assert_self(self);
    uz_endat_interface_hw_write_ip_core_enable(self->config.base_address, ip_core_off_on);
}

void uz_endat_interface_set_mechanical_offset_endat_single_turn(uz_endat_interface_t *self, float position_mech_offset_si_single_turn) {
    assert_self(self);

    int32_t position_mech_offset_ticks_single_turn = calculate_position_mech_offset_ticks_single_turn(self->config.endat_encoder_bit_width_single_turn, position_mech_offset_si_single_turn);
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn(self->config.base_address, position_mech_offset_ticks_single_turn);
}

void uz_endat_interface_set_mode_command(uz_endat_interface_t *self, enum uz_endat_interface_mode_command_t mode_command) {
    assert_self(self);
    uz_endat_interface_hw_write_endat_mode_command(self->config.base_address, (uint32_t)mode_command);
}

void uz_endat_interface_set_sampling_delay_clk_ticks(uz_endat_interface_t *self, uint32_t delay_clk_ticks) {
    assert_self(self);
    uz_endat_interface_hw_write_sampling_delay_clk_ticks(self->config.base_address, delay_clk_ticks);
}

static void assert_config(struct uz_endat_interface_config_t config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    uz_assert_not_zero_uint32(config.endat_clk_frequency_Hz);
    uz_assert_not_zero_uint32(config.endat_encoder_bit_width_single_turn);
    uz_assert_not_zero_uint32(config.machine_polepairs);

    uint32_t endat_clk_divider = calculate_endat_clock_divider(config.ip_clk_frequency_Hz, config.endat_clk_frequency_Hz);
    uz_assert(endat_clk_divider >= ENDAT_CLOCK_DIVIDER_MIN);
    uz_assert(endat_clk_divider <= ENDAT_CLOCK_DIVIDER_MAX);

    uz_assert(config.endat_encoder_bit_width_single_turn <= ENDAT_ENCODER_BIT_WIDTH_MAX);
    uz_assert(config.endat_encoder_bit_width_multi_turn <= ENDAT_ENCODER_BIT_WIDTH_MAX);
    uz_assert((config.endat_encoder_bit_width_multi_turn + config.endat_encoder_bit_width_single_turn) <= ENDAT_ENCODER_POSITION_BITS_MAX);
    uz_assert((config.endat_encoder_bit_width_multi_turn + config.endat_encoder_bit_width_single_turn + ENDAT_NUMBER_OF_CRC_BITS) <= ENDAT_FRAME_BITS_MAX);
    uz_assert(config.machine_polepairs <= MACHINE_POLEPAIRS_MAX);

    uz_assert(config.sampling_interval_seconds > 0.0f);
    uz_assert(config.sampling_interval_seconds < SAMPLING_INTERVAL_MAX_SECONDS);
    uz_assert(config.kp_pll >= 0.0f);
    uz_assert(config.kp_pll < KP_PLL_MAX);
    uz_assert(config.ki_pll >= 0.0f);
    uz_assert(config.ki_pll < KI_PLL_MAX);
    uz_assert(config.position_mech_offset_si_single_turn <= POSITION_MECH_OFFSET_LIMIT_RAD);
    uz_assert(config.position_mech_offset_si_single_turn >= -POSITION_MECH_OFFSET_LIMIT_RAD);
    uz_assert(config.delay_sampling_in_clk_ticks <= SAMPLING_DELAY_CLK_TICKS_MAX);
    calculate_position_mech_offset_ticks_single_turn(config.endat_encoder_bit_width_single_turn, config.position_mech_offset_si_single_turn);
}

static uint32_t calculate_endat_clock_divider(uint32_t ip_clk_frequency_Hz, uint32_t endat_clk_frequency_Hz) {
    uz_assert_not_zero_uint32(ip_clk_frequency_Hz);
    uz_assert_not_zero_uint32(endat_clk_frequency_Hz);
    uz_assert(endat_clk_frequency_Hz <= (UINT32_MAX / 2U));
    return ceil_div(ip_clk_frequency_Hz, (2U * endat_clk_frequency_Hz));
}

static int32_t calculate_position_mech_offset_ticks_single_turn(uint32_t endat_encoder_bit_width_single_turn, float position_mech_offset_si_single_turn) {
    uz_assert(endat_encoder_bit_width_single_turn > 0U);
    uz_assert(endat_encoder_bit_width_single_turn <= ENDAT_ENCODER_BIT_WIDTH_MAX);
    uz_assert(position_mech_offset_si_single_turn <= POSITION_MECH_OFFSET_LIMIT_RAD);
    uz_assert(position_mech_offset_si_single_turn >= -POSITION_MECH_OFFSET_LIMIT_RAD);

    uint32_t bit_count_single_turn = (1U << endat_encoder_bit_width_single_turn) - 1U;
    float position_mech_offset_ticks_single_turn = ((float)bit_count_single_turn / (2.0f * UZ_PIf)) * position_mech_offset_si_single_turn;
    uz_assert(position_mech_offset_ticks_single_turn <= INT32_MAX_SAFE_FLOAT);
    uz_assert(position_mech_offset_ticks_single_turn >= -INT32_MAX_SAFE_FLOAT);
    return (int32_t)position_mech_offset_ticks_single_turn;
}

/**
 * @brief Calculates the ceiled value of an unsigned integer division.
 *
 * @param a Dividend
 * @param b Divisor
 *
 * @return Ceiled unsigned integer division
 */
static uint32_t ceil_div(uint32_t a, uint32_t b) {
    uz_assert(b !=0U);
    return (a / b) + ((a % b) != 0U);
}

#endif
