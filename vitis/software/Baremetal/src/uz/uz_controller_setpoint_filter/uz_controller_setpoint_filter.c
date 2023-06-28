/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Valentin Hoppe
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
#include "uz_controller_setpoint_filter.h"
#include "../uz_global_configuration.h"
#if UZ_DQ_SETPOINT_FILTER_MAX_INSTANCES > 0U
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdint.h>

struct uz_dq_setpoint_filter{
    bool is_ready;
    struct uz_IIR_Filter_config config_filter_d;
    struct uz_IIR_Filter_config config_filter_q;
    uz_IIR_Filter_t* iir_instance_d;
    uz_IIR_Filter_t* iir_instance_q;
};

static uint32_t instances_counter_dq_setpoint_filter = 0;
static uz_dq_setpoint_filter instances_dq_setpoint_filter[UZ_DQ_SETPOINT_FILTER_MAX_INSTANCES] = { 0 };
static uz_dq_setpoint_filter* uz_dq_setpoint_filter_allocation(void);

static uz_dq_setpoint_filter* uz_dq_setpoint_filter_allocation(void) {
	uz_assert(instances_counter_dq_setpoint_filter < UZ_DQ_SETPOINT_FILTER_MAX_INSTANCES);
	uz_dq_setpoint_filter* self = &instances_dq_setpoint_filter[instances_counter_dq_setpoint_filter];
	uz_assert(self->is_ready == false);
	instances_counter_dq_setpoint_filter++;
	self->is_ready = true;
	return (self);
}

uz_dq_setpoint_filter* uz_uz_dq_setpoint_filter_init(struct uz_dq_setpoint_filter_config config){
	uz_dq_setpoint_filter* self = uz_dq_setpoint_filter_allocation();
    uz_assert(UZ_IIR_FILTER_MAX_INSTANCES>=(2U*instances_counter_dq_setpoint_filter));
	self->config_filter_d = config.config_filter_d;
    self->config_filter_q = config.config_filter_q;
    self->iir_instance_d = uz_signals_IIR_Filter_init(self->config_filter_d);
    self->iir_instance_q = uz_signals_IIR_Filter_init(self->config_filter_q);
	return (self);
}

uz_3ph_dq_t uz_signals_IIR_Filter_dq_setpoint(uz_dq_setpoint_filter* self, uz_3ph_dq_t setpoint){
    uz_assert_not_NULL(self);
    uz_3ph_dq_t out = {
        .d = uz_signals_IIR_Filter_sample(self->iir_instance_d, setpoint.d),
        .q = uz_signals_IIR_Filter_sample(self->iir_instance_q, setpoint.q),
        .zero = 0.0f};
    return out;
}
#endif