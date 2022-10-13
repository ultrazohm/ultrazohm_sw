/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Josef Knoblach
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


#include "../uz_global_configuration.h"

#if UZ_RESONANT_CONTROLLER_MAX_INSTANCES > 0U

#include "uz_resonant_controller.h"
#include "../uz_HAL.h"

static unsigned int instances_counter_ResonantController = 0;

static uz_resonantController instances_ResonantController[UZ_RESONANT_CONTROLLER_MAX_INSTANCES] = { 0 };

static uz_resonantController* uz_ResonantController_allocation(void);


static uz_resonantController* uz_ResonantController_allocation(void) {
	uz_assert(instances_counter_ResonantController < UZ_RESONANT_CONTROLLER_MAX_INSTANCES);
	uz_resonantController* self = &instances_ResonantController[instances_counter_ResonantController];
	instances_counter_ResonantController++;
	return (self);
}


uz_resonantController* uz_resonantController_init(void) {
	uz_resonantController* self = uz_ResonantController_allocation();
	self->PtrToModelData=&self->modelData;
	self->PtrToModelData->dwork=&self->dwork;
	self->PtrToModelData->inputs=&self->input;
	self->PtrToModelData->outputs=&self->output;
	Resonant_Controller_initialize(self->PtrToModelData);
	return (self);
}





void uz_resonantController_step(uz_resonantController *self) {
	uz_assert_not_NULL(self);
	Resonant_Controller_step(self->PtrToModelData);
}


void uz_resonantController_reset(uz_resonantController *self){
	self->PtrToModelData->inputs->Reset = 1.0;
	self->PtrToModelData->inputs->in_m = 0.0;
	self->PtrToModelData->inputs->in_ref = 0.0;
	Resonant_Controller_step(self->PtrToModelData);
	self->PtrToModelData->inputs->Reset = 0.0;
}

#endif
