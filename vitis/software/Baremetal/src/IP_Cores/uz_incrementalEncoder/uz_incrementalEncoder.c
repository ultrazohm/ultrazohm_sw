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

#include "uz_incrementalEncoder.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_INCREMENTALENCODER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <math.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_math_constants.h"
#include "uz_incrementalEncoder.h" 
#include "uz_incrementalEncoder_hw.h" 

#define QUADRATURE_FACTOR 4U // Quadrature factor used to calculate number of edges based on number of lines of the encoder. Incremental encoder have A+B lane by definition, thus this is always 4.

struct uz_incrementalEncoder_t {
    bool is_ready;
    struct uz_incrementalEncoder_config config;
    float pi2_inc_theta_electrical;
    float timer_fpga_ms;
    uint32_t increments_per_turn_elec;
    bool use_theta_el;
};

static uint32_t instance_counter = 0U;
static uz_incrementalEncoder_t instances[UZ_INCREMENTALENCODER_MAX_INSTANCES] = { 0 };

static uz_incrementalEncoder_t* uz_incrementalEncoder_allocation(void);

static uz_incrementalEncoder_t* uz_incrementalEncoder_allocation(void){
    uz_assert(instance_counter < UZ_INCREMENTALENCODER_MAX_INSTANCES);
    uz_incrementalEncoder_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static void set_pi2_inc(uz_incrementalEncoder_t* self);
static void set_fpga_timer(uz_incrementalEncoder_t* self);
static void set_inc_per_turn_mechanical(uz_incrementalEncoder_t* self);
static void set_inc_per_turn_elec(uz_incrementalEncoder_t* self);
static bool check_if_theta_el_can_be_used(uint32_t inc_per_turn,uint32_t pole_pair);
static void set_omega_per_over_sample(uz_incrementalEncoder_t* self);
static void set_offset(uz_incrementalEncoder_t* self);
static void set_counting_direction(uz_incrementalEncoder_t* self);
static void set_configuration(uz_incrementalEncoder_t* self);

uz_incrementalEncoder_t* uz_incrementalEncoder_init(struct uz_incrementalEncoder_config config) {
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert(config.ip_core_frequency_Hz == 100000000U); // IP-Core has to be used with 100 MHz! (V24 needs 50 MHz, V26 can use 100 MHz!)
    uz_assert_not_zero_uint32(config.line_number_per_turn_mech);
    uz_assert(config.line_number_per_turn_mech < UINT16_MAX); // Increments per turn is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_assert(config.Encoder_mech_Offset < UINT16_MAX); // Offset is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_assert(config.Encoder_elec_Offset < UINT16_MAX); // Offset is implemented as a 16 bit unsigned int in the IP-core hardware
    uz_incrementalEncoder_t* self = uz_incrementalEncoder_allocation();
    self->config=config;
    self->use_theta_el=check_if_theta_el_can_be_used(self->config.line_number_per_turn_mech,self->config.drive_pole_pair);
    set_configuration(self);
    return (self);
}

float uz_incrementalEncoder_get_omega_mech(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_omega(self->config.base_address);
}

float uz_incrementalEncoder_get_theta_el(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    uz_assert(self->use_theta_el);
    return uz_incrementalEncoder_hw_get_theta_electric(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_position(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_position(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_position_wOffset(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_position_wOffset(self->config.base_address);
}

uint32_t uz_incrementalEncoder_get_Index_Found(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    return uz_incrementalEncoder_hw_get_Index_found(self->config.base_address);
}

// ----------------------------------------------------------- INTERNA BELOW ---------------------------------------------


static void set_configuration(uz_incrementalEncoder_t* self){
	set_offset(self);
	set_counting_direction(self);
	set_pi2_inc(self);
    set_fpga_timer(self);
    set_inc_per_turn_mechanical(self);
    set_inc_per_turn_elec(self);
    set_omega_per_over_sample(self);
}

bool check_if_theta_el_can_be_used(uint32_t inc_per_turn, uint32_t pole_pair){
    bool use_theta_el=false;
    if (pole_pair != 0U){
        uint32_t division_reminder=inc_per_turn % pole_pair; // if inc_per_turn is an integer multiple of pole pairs, modulo returns zero
        if(division_reminder==0U){  // if modulo is not zero, one can not use theta el even thought the user intends to use it since pole_pair is not zero
            use_theta_el=true;
        } 
    }
    return use_theta_el;
}

static void set_offset(uz_incrementalEncoder_t* self){
	 uz_assert(self->is_ready);
	 uz_incrementalEncoder_hw_set_Position_Offset(self->config.base_address, self->config.Encoder_mech_Offset);
	 uz_incrementalEncoder_hw_set_theta_el_Offset(self->config.base_address, self->config.Encoder_elec_Offset);
}

static void set_counting_direction(uz_incrementalEncoder_t* self){
	 uz_assert(self->is_ready);
	 uz_incrementalEncoder_hw_set_cw_ccw_direction(self->config.base_address, self->config.Counting_Direction);
}

void set_pi2_inc(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    float pi2_inc=( (2.0f*UZ_PIf) /( (float)self->config.line_number_per_turn_mech * (float)QUADRATURE_FACTOR) ) * (float)self->config.drive_pole_pair;
    uz_incrementalEncoder_hw_set_pi2_inc(self->config.base_address,pi2_inc);
}

void set_fpga_timer(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    float fpga_timer= (float)self->config.line_number_per_turn_mech/(2.0f*UZ_PIf* (float)self->config.ip_core_frequency_Hz);
    fpga_timer=fpga_timer*2.0f; // Correction factor of 2 due to bug in IP-Core, see issue #145
    uz_incrementalEncoder_hw_set_timer_fpga_ms(self->config.base_address,fpga_timer);
}

void set_inc_per_turn_mechanical(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    uint32_t inc_per_turn=self->config.line_number_per_turn_mech*QUADRATURE_FACTOR;
    uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(self->config.base_address,inc_per_turn);
}

void set_inc_per_turn_elec(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    if(self->use_theta_el){ // prevents division by zero if drive_pole_pair is 0 and thus theta_el is not used
        uint32_t inc_per_turn_el=(self->config.line_number_per_turn_mech*QUADRATURE_FACTOR)/self->config.drive_pole_pair;
        uz_incrementalEncoder_hw_set_increments_per_turn_electric(self->config.base_address,inc_per_turn_el);
    }else{
        uz_incrementalEncoder_hw_set_increments_per_turn_electric(self->config.base_address,self->config.line_number_per_turn_mech*QUADRATURE_FACTOR ); // if theta_el is not used, just set it to mechanical increments as a default
    }
}

static void set_omega_per_over_sample(uz_incrementalEncoder_t* self){
    uz_assert(self->is_ready);
    float omega_per_over_sample=self->config.OmegaPerOverSample_in_rpm*((2.0f*UZ_PIf)/60.0f);
    uz_incrementalEncoder_hw_set_omegaPerOverSample(self->config.base_address,omega_per_over_sample);
}


#endif
