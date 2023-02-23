/******************************************************************************
* Copyright 2023 Robert Zipprich
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

#include "../../uz/uz_global_configuration.h"
#if UZ_LINEARREGRESSIONCORE_MAX_INSTANCES > 0U
#include "uz_LinearRegressionCore.h"

struct uz_LinearRegressionCore_t {
    uint32_t 				    base_address;
	uint32_t 				    ip_clk_frequency_Hz;
	bool 						is_ready;
	uint32_t 					enabled_Channels;
};

static uint32_t instance_counter = 0U;
static uz_LinearRegressionCore_t instances[UZ_LINEARREGRESSIONCORE_MAX_INSTANCES] = { 0 };

static uz_LinearRegressionCore_t* uz_LinearRegressionCore_allocation(void);

static uz_LinearRegressionCore_t* uz_LinearRegressionCore_allocation(void){
    uz_assert(instance_counter < UZ_LINEARREGRESSIONCORE_MAX_INSTANCES);
    uz_LinearRegressionCore_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_LinearRegressionCore_t* uz_LinearRegressionCore_init(struct uz_LinearRegressionCore_config_t config) {
	uz_LinearRegressionCore_t* self  = uz_LinearRegressionCore_allocation();
    // Store settings
    self-> base_address         = config.base_address;
    self-> ip_clk_frequency_Hz  = config.ip_clk_frequency_Hz;
    self-> enabled_Channels 	= config.enabled_Channels;

    //Write settings
    write_Channel_hw(Channel_Select_Register,config.enabled_Channels);
    return (self);
}

void enable_Channel(uz_LinearRegressionCore_t* self, uint32_t Channel_nr){			// enables Linear Regression on specified Channel
	uz_assert_not_NULL(self);
	uz_assert_true(self->is_ready);
	self-> enabled_Channels = (self-> enabled_Channels | Channel_nr);
	enable_Channel_hw(self->base_address, Channel_nr);
}

void disable_Channel(uz_LinearRegressionCore_t* self, uint32_t Channel_nr){			// disables Linear Regression on specified Channel
	uz_assert_not_NULL(self);
	uz_assert_true(self->is_ready);
	self-> enabled_Channels = (self-> enabled_Channels & ~Channel_nr);
	disable_Channel_hw(self->base_address, Channel_nr);
}

uint32_t check_Channel(uz_LinearRegressionCore_t* self){							// check Channels
	uz_assert_not_NULL(self);
	uz_assert_true(self->is_ready);
	self->enabled_Channels = check_Channel_hw(self->base_address);
	return self->enabled_Channels;
}


#endif
