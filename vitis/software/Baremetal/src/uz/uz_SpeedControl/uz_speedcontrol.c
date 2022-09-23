/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
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


#include "uz_speedcontrol.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include <stdbool.h>

#if UZ_SPEEDCONTROL_MAX_INSTANCES > 0
typedef struct uz_SpeedControl_t {
	bool is_ready;
    bool ext_clamping;
	struct uz_SpeedControl_config config;
	struct uz_PI_Controller* Controller;
}uz_SpeedControl_t;

static uint32_t instance_speedcontrol_counter = 0U;
static uz_SpeedControl_t instances_speedcontrol[UZ_SPEEDCONTROL_MAX_INSTANCES] = { 0 };

static uz_SpeedControl_t* uz_SpeedControl_allocation(void);

static uz_SpeedControl_t* uz_SpeedControl_allocation(void){
 uz_assert(instance_speedcontrol_counter < UZ_SPEEDCONTROL_MAX_INSTANCES);
 uz_SpeedControl_t* self = &instances_speedcontrol[instance_speedcontrol_counter];
 uz_assert_false(self->is_ready);
 instance_speedcontrol_counter++;
 self->is_ready = true;
 return (self);
}

uz_SpeedControl_t* uz_SpeedControl_init(struct uz_SpeedControl_config config){
    uz_SpeedControl_t* self = uz_SpeedControl_allocation();
    self->Controller = uz_PI_Controller_init(config.config_controller);
    self->config = config;
    return(self);
}

float uz_SpeedControl_sample(uz_SpeedControl_t* self, float omega_m_rad_per_sec, float n_ref_rpm){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	float omega_m_ref_rad_per_sec = (n_ref_rpm * 2.0f * UZ_PIf) / 60.0f;
    float torque_Nm = uz_PI_Controller_sample(self->Controller, omega_m_ref_rad_per_sec, omega_m_rad_per_sec, self->ext_clamping);
    return(torque_Nm);
}

void uz_SpeedControl_reset(uz_SpeedControl_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	uz_PI_Controller_reset(self->Controller);
}

void uz_SpeedControl_set_Ki(uz_SpeedControl_t* self, float new_Ki){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    self->config.config_controller.Ki = new_Ki;
    uz_PI_Controller_set_Ki(self->Controller, new_Ki);
}

void uz_SpeedControl_set_Kp(uz_SpeedControl_t* self, float new_Kp){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    self->config.config_controller.Kp = new_Kp;
    uz_PI_Controller_set_Kp(self->Controller, new_Kp);
}

void uz_SpeedControl_update_limits(uz_SpeedControl_t* self, float upper_limit, float lower_limit){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    self->config.config_controller.upper_limit = upper_limit;
    self->config.config_controller.lower_limit = lower_limit;
	uz_PI_Controller_update_limits(self->Controller, upper_limit, lower_limit);
}

void uz_SpeedControl_set_ext_clamping(uz_SpeedControl_t* self, bool ext_clamping) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	self->ext_clamping = ext_clamping;
}

#endif
