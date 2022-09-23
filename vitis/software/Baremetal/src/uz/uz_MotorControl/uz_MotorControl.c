/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennis Hufnagel
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

#include "uz_MotorControl.h"
#include "../uz_global_configuration.h"
#if UZ_MOTORCONTROL_MAX_INSTANCES > 0
typedef struct uz_MotorControl_t {
	bool is_ready;
	struct uz_MotorControl_config config;
}uz_MotorControl_t;

static uint32_t instances_counter = 0;

static uz_MotorControl_t instances[UZ_MOTORCONTROL_MAX_INSTANCES] = {0};


/**
 * @brief Memory allocation of the uz_MotorControl_t struct
 *
 * @return Pointer to uz_MotorControl_t instance
 */
static uz_MotorControl_t* uz_MotorControl_allocation(void);

static uz_MotorControl_t* uz_MotorControl_allocation(void) {
	uz_assert(instances_counter < UZ_CURRENTCONTROL_MAX_INSTANCES);
	uz_CurrentControl_t* self = &instances[instances_counter];
	uz_assert(self->is_ready == false);
	instances_counter++;
	self->is_ready = true;
	return (self);
}

uz_MotorControl_t* uz_MotorControl_init(struct uz_MotorControl_config config) {
	uz_MotorControl_t* self = uz_MotorControl_allocation();
	self->config = config;
	return (self);
}

#endif
