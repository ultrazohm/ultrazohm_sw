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

#include "uz_incrementalEncoder_V26.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_INCREMENTALENCODER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <math.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_math_constants.h"
#include "uz_incrementalEncoder_V26.h"
#include "uz_incrementalEncoder_hw_V26.h"

#define QUADRATURE_FACTOR 4U // Quadrature factor used to calculate number of edges based on number of lines of the encoder. Incremental encoder have A+B lane by definition, thus this is always 4.

struct uz_incrementalEncoder_t_V26 {
    bool is_ready;
    struct uz_incrementalEncoder_config_V26 config;
    float pi2_inc_theta_electrical;
    float timer_fpga_ms;
    uint32_t increments_per_turn_elec;
    bool use_theta_el;
};

static uint32_t instance_counter = 0U;
static uz_incrementalEncoder_t_V26 instances[UZ_INCREMENTALENCODER_MAX_INSTANCES] = { 0 };

static uz_incrementalEncoder_t_V26* uz_incrementalEncoder_allocation(void);

static uz_incrementalEncoder_t_V26* uz_incrementalEncoder_allocation(void){
    uz_assert(instance_counter < UZ_INCREMENTALENCODER_MAX_INSTANCES);
    uz_incrementalEncoder_t_V26* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static void set_pi2_inc_V26(uz_incrementalEncoder_t_V26* self);
static void set_fpga_timer_V26(uz_incrementalEncoder_t_V26* self);
static void set_inc_per_turn_mechanical_V26(uz_incrementalEncoder_t_V26* self);
static void set_inc_per_turn_elec_V26(uz_incrementalEncoder_t_V26* self);
static bool check_if_theta_el_can_be_used_V26(uint32_t inc_per_turn,uint32_t pole_pair);
static void set_omega_per_over_sample_V26(uz_incrementalEncoder_t_V26* self);
static void set_timeout_V26(uz_incrementalEncoder_t_V26* self);
static void set_offset_V26(uz_incrementalEncoder_t_V26* self);
static void set_counting_direction_V26(uz_incrementalEncoder_t_V26* self);
static void set_configuration_V26(uz_incrementalEncoder_t_V26* self);

uz_incrementalEncoder_t_V26* uz_incrementalEncoder_init_V26(struct uz_incrementalEncoder_config_V26 config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert(config.ip_core_frequency_Hz == 100000000U); // IP-Core has to be used with 100 MHz! (V24 needs 50 MHz, V26 can use 100 MHz!)
    uz_assert_not_zero_uint32(config.line_number_per_turn_mech);
    uz_assert(config.line_number_per_turn_mech < UINT16_MAX); // Increments per turn is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_assert(config.Encoder_mech_Offset < UINT16_MAX); // Offset is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_assert(config.Encoder_elec_Offset < UINT16_MAX); // Offset is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_assert(config.Speed_Timeout_s > 0); // Check if timeout-Value > 0
    uz_incrementalEncoder_t_V26* self = uz_incrementalEncoder_allocation();
    self->config=config;
    self->use_theta_el=check_if_theta_el_can_be_used_V26(self->config.line_number_per_turn_mech,self->config.drive_pole_pair);
    uz_incrementalEncoder_hw_reset_ip_core_V26(config.base_address);
    set_configuration_V26(self);
    return (self);
}

float uz_incrementalEncoder_get_omega_mech_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_omega_MA_N4_V26(self->config.base_address);
    //return uz_incrementalEncoder_hw_get_omega(self->config.base_address);
}

float uz_incrementalEncoder_get_theta_el_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    //uz_assert(self->use_theta_el);
    return uz_incrementalEncoder_hw_get_theta_electric_V26(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_position_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_position_V26(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_position_wOffset_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_position_wOffset_V26(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_Index_Found_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_Index_found_V26(self->config.base_address);
}

void uz_incrementalEncoder_set_new_electrical_Offset_V26(uz_incrementalEncoder_t_V26* self, uint32_t encoder_Offset_elec){
	uz_assert(self->is_ready);
	uz_assert(self->config.Encoder_elec_Offset < UINT16_MAX);
	self->config.Encoder_elec_Offset = encoder_Offset_elec;
	uz_incrementalEncoder_hw_set_theta_el_Offset_V26(self->config.base_address, self->config.Encoder_elec_Offset);
}

void uz_incrementalEncoder_set_new_mechanical_Offset_V26(uz_incrementalEncoder_t_V26* self,  uint32_t encoder_Offset_mech){
	uz_assert(self->is_ready);
	uz_assert(self->config.Encoder_mech_Offset < UINT16_MAX);
	self->config.Encoder_mech_Offset = encoder_Offset_mech;
	uz_incrementalEncoder_hw_set_Position_Offset_V26(self->config.base_address, self->config.Encoder_mech_Offset);
}

// ----------------------------------------------------------- INTERNA BELOW ---------------------------------------------

static void set_configuration_V26(uz_incrementalEncoder_t_V26* self){
	set_offset_V26(self);
    set_timeout_V26(self);
	set_counting_direction_V26(self);
	set_pi2_inc_V26(self);
    set_fpga_timer_V26(self);
    set_inc_per_turn_mechanical_V26(self);
    set_inc_per_turn_elec_V26(self);
    set_omega_per_over_sample_V26(self);
}

bool check_if_theta_el_can_be_used_V26(uint32_t inc_per_turn, uint32_t pole_pair){
    bool use_theta_el=false;
    if (pole_pair != 0U){
        uint32_t division_reminder=inc_per_turn % pole_pair; // if inc_per_turn is an integer multiple of pole pairs, modulo returns zero
        if(division_reminder==0U){  // if modulo is not zero, one can not use theta el even thought the user intends to use it since pole_pair is not zero
            use_theta_el=true;
        } 
    }
    return use_theta_el;
}

static void set_timeout_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    uint32_t speed_timeout = self->config.Speed_Timeout_s * self->config.ip_core_frequency_Hz;
    uz_incrementalEncoder_hw_set_speed_timeout_value_V26(self->config.base_address,speed_timeout);
}

static void set_offset_V26(uz_incrementalEncoder_t_V26* self){
	 uz_assert(self->is_ready);
	 uz_incrementalEncoder_hw_set_Position_Offset_V26(self->config.base_address, self->config.Encoder_mech_Offset);
	 uz_incrementalEncoder_hw_set_theta_el_Offset_V26(self->config.base_address, self->config.Encoder_elec_Offset);
}

static void set_counting_direction_V26(uz_incrementalEncoder_t_V26* self){
	 uz_assert(self->is_ready);
	 uz_incrementalEncoder_hw_set_cw_ccw_direction_V26(self->config.base_address, self->config.Counting_Direction);
}

void set_pi2_inc_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    float pi2_inc=( (2.0f*UZ_PIf) /( (float)self->config.line_number_per_turn_mech * (float)QUADRATURE_FACTOR) ) * (float)self->config.drive_pole_pair;
    uz_incrementalEncoder_hw_set_pi2_inc_V26(self->config.base_address,pi2_inc);
}

void set_fpga_timer_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    float fpga_timer= (float)self->config.line_number_per_turn_mech/(2.0f*UZ_PIf* (float)self->config.ip_core_frequency_Hz);
    fpga_timer=fpga_timer; // No Correction factor
    uz_incrementalEncoder_hw_set_timer_fpga_ms_V26(self->config.base_address,fpga_timer);
}

void set_inc_per_turn_mechanical_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    uint32_t inc_per_turn=self->config.line_number_per_turn_mech*QUADRATURE_FACTOR;
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_V26(self->config.base_address,inc_per_turn);
}

void set_inc_per_turn_elec_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    if(self->use_theta_el){ // prevents division by zero if drive_pole_pair is 0 and thus theta_el is not used
        uint32_t inc_per_turn_el=(self->config.line_number_per_turn_mech*QUADRATURE_FACTOR)/self->config.drive_pole_pair;
        uz_incrementalEncoder_hw_set_increments_per_turn_electric_V26(self->config.base_address,inc_per_turn_el);
    }else{
        //uz_incrementalEncoder_hw_set_increments_per_turn_electric(self->config.base_address,self->config.line_number_per_turn_mech*QUADRATURE_FACTOR ); // if theta_el is not used, just set it to mechanical increments as a default
    	uint32_t inc_per_turn_el=round((self->config.line_number_per_turn_mech*QUADRATURE_FACTOR)/self->config.drive_pole_pair);
    	uz_incrementalEncoder_hw_set_increments_per_turn_electric_V26(self->config.base_address,inc_per_turn_el); // if theta_el is not used, just set it to mechanical increments as a default
    }
}

static void set_omega_per_over_sample_V26(uz_incrementalEncoder_t_V26* self){
    uz_assert(self->is_ready);
    float omega_per_over_sample=self->config.OmegaPerOverSample_in_rpm*((2.0f*UZ_PIf)/60.0f);
    uz_incrementalEncoder_hw_set_omegaPerOverSample_V26(self->config.base_address,omega_per_over_sample);
}


#endif
