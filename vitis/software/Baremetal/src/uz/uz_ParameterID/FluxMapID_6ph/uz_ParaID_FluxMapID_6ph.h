/******************************************************************************
 * Copyright 2023 Valentin Hoppe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef UZ_PARAID_FLUXMAPID_6PH_H
#define UZ_PARAID_FLUXMAPID_6PH_H

#include "../uz_ParameterID_data.h"
#include "../../uz_CurrentControl/uz_CurrentControl.h"
#include "../../uz_ResonantController/uz_resonant_controller.h"
#include "../../uz_math_constants.h"

typedef struct uz_ParaID_FluxMapID_6ph_t uz_ParaID_FluxMapID_6ph_t;

uz_ParaID_FluxMapID_6ph_t* uz_FluxMapID_6ph_init(void);

void uz_FluxMapID_6ph_step(uz_ParaID_FluxMapID_6ph_t* self, uz_ParaID_FluxMapIDConfig_t ID_config, uz_ParaID_ActualValues_t actual, uz_ParaID_GlobalConfig_t global_config, uz_ParaID_ControlFlags_t flags);
bool uz_get_FluxMapID_6ph_entered(uz_ParaID_FluxMapID_6ph_t* self);
bool uz_get_FluxMapID_6ph_finished(uz_ParaID_FluxMapID_6ph_t* self);
uz_ParaID_Controller_Parameters_output_t* uz_get_FluxMapID_6ph_FOCoutput(uz_ParaID_FluxMapID_6ph_t* self);
uz_ParaID_FluxMapID_output_t* uz_get_FluxMapID_6ph_output(uz_ParaID_FluxMapID_6ph_t* self);
uz_ParaID_FluxMapID_extended_controller_output_t* uz_get_FluxMapID_6ph_extended_controller_output(uz_ParaID_FluxMapID_6ph_t* self);

uz_6ph_dq_t uz_FluxMapID_6ph_step_controllers(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance_1, uz_CurrentControl_t* CC_instance_2, uz_resonantController_t* resonant_1, uz_resonantController_t* resonant_2);

#endif // UZ_PARAID_FLUXMAPID_6PH_H
