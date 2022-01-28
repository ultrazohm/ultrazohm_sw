/******************************************************************************
 * Copyright 2021 Dennis Hufnagel
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
#ifndef UZ_PARAMETERID_H
#define UZ_PARAMETERID_H

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "../../globalData.h"
#include <math.h>
#include "../uz_HAL.h"
#include <stdbool.h>
#include "../uz_FOC/uz_FOC.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "ControlState/uz_PID_ControlState.h"
#include "ElectricalID/uz_PID_ElectricalID.h"
#include "FluxMapID/uz_PID_FluxMapID.h"
#include "FrictionID/uz_PID_FrictionID.h"
#include "OnlineID/uz_PID_OnlineID.h"
#include "TwoMassID/uz_PID_TwoMassID.h"

typedef struct uz_ParameterID_t uz_ParameterID_t;

enum uz_PID_Control_selection {
	No_Control = 0, Current_Control, Speed_Control
};
typedef struct uz_ParameterID_Data_t {
	uz_PID_ActualValues_t ActualValues;
	uz_PID_ControlFlags_t* ControlFlags;
	uz_PID_GlobalConfig_t GlobalConfig;
	uz_PID_ElectricalIDConfig_t ElectricalID_Config;
	uz_PID_TwoMassIDConfig_t TwoMassID_Config;
	uz_PID_FrictionIDConfig_t FrictionID_Config;
	uz_PID_FluxMapIDConfig_t FluxMapID_Config;
	uz_PID_OnlineIDConfig_t OnlineID_Config;
	uz_PID_AutoRefCurrentsConfig_t AutoRefCurrents_Config;
	uz_PID_ElectricalID_output_t *ElectricalID_Output;
	uz_PID_TwoMassID_output_t *TwoMassID_Output;
	uz_PID_FrictionID_output_t *FrictionID_Output;
	uz_PID_FluxMapID_output_t *FluxMapID_Output;
	uz_PID_OnlineID_output_t* OnlineID_Output;
	uz_PID_Controller_Parameters_output_t Controller_Parameters;
	uz_dq_t AutoRefCurrents_Output;
	uz_PID_FluxMapsData_t* FluxMap_Data;
	bool calculate_flux_maps;
	int FluxMap_counter;
	float Psi_D_pointer;
	float Psi_Q_pointer;
	float FluxMap_MeasuringPoints;
	enum uz_PID_Control_selection PID_Control_Selection;
} uz_ParameterID_Data_t;

uz_ParameterID_t* uz_ParameterID_init(void);

void uz_ParameterID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);
struct uz_DutyCycle_t uz_ParameterID_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance, uz_dq_t v_dq_Volts, uz_PWM_SS_2L_t* PWM_Module);

struct uz_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance);

void uz_ParameterID_initialize_data_structs(uz_ParameterID_Data_t *Data, uz_ParameterID_t *ParameterID);

void uz_ParameterID_CleanPsiArray(uz_ParameterID_t *self, uz_ParameterID_Data_t* Data);
void uz_ParameterID_CalcFluxMaps(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data);


#endif // UZ_PARAMETERID_H

#endif
