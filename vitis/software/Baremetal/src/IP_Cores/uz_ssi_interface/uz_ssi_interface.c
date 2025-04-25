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

#include "uz_ssi_interface.h"

#include "../../uz_global_configuration.h"
#if UZ_SSI_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_ssi_interface.h" 

struct uz_ssi_interface_t {
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_ssi_interface_t instances[UZ_SSI_INTERFACE_MAX_INSTANCES] = { 0 };

static uz_ssi_interface_t* uz_ssi_interface_allocation(void);

static uz_ssi_interface_t* uz_ssi_interface_allocation(void){
    uz_assert(instance_counter < UZ_SSI_INTERFACE_MAX_INSTANCES);
    uz_ssi_interface_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_ssi_interface_t* uz_ssi_interface_init(struct uz_ssi_interface_config_t config) {
    uz_ssi_interface_t* self = uz_ssi_interface_allocation();

    //implement init with config

    return (self);
}

// update outputs function

#endif