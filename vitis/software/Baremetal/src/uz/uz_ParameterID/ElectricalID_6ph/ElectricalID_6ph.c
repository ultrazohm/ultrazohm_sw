/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Valentin Hoppe
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

#include "ElectricalID_6ph.h"
#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz_HAL.h"

struct uz_ParaID_ElectricalID_6ph_t {
    bool is_ready;
};

static uint32_t instance_counter = 0U;
static uz_ParaID_ElectricalID_6ph_t instances[UZ_PARAMETERID_6PH_MAX_INSTANCES] = { 0 };

static uz_ParaID_ElectricalID_6ph_t* uz_ParaID_ElectricalID_6ph_allocation(void);

static uz_ParaID_ElectricalID_6ph_t* uz_ParaID_ElectricalID_6ph_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_6PH_MAX_INSTANCES);
    uz_ParaID_ElectricalID_6ph_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_ParaID_ElectricalID_6ph_t* uz_ParaID_ElectricalID_6ph_init(void) {
    uz_ParaID_ElectricalID_6ph_t* self = uz_ParaID_ElectricalID_6ph_allocation();
    return (self);
}

#endif
