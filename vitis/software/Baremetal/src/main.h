/******************************************************************************
* Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
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

#ifndef main_H_
#define main_H_

#include <math.h>										//Include for math operations
#include <stdbool.h>

// Xilinx library functions
#include "xscugic.h"									//Include for Interrupt handler (necessary for all GIC interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xtmrctr.h"									//Include of the Timer-Blocks

#include "include/uz_platform_state_machine.h"
#include "uz/uz_global_configuration.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "include/uz_adcLtc2311_ip_core_init.h"
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "include/uz_assertion_configuration.h"


// UltraZohm includes
#include "globalData.h"
#include "defines.h"
#include "include/isr.h"
#include "include/encoder.h"
#include "include/gpio_axi.h"
#include "include/javascope.h"
#include "include/mux_axi.h"
#include "include/pwm_3L_driver.h"

#include "uz/uz_HAL.h"

#include "uz/uz_LED/uz_LED_facade.h"
#include "uz/uz_PushButton/uz_PushButton_facade.h"

#include "uz/uz_MioGpio_mediator/uz_MioGpio_mediator.h"
#include "uz/uz_MioGpio_mediator/uz_MioGpioMapping.h"

#include "uz/uz_SystemTime/uz_SystemTime.h"

#include "include/pwm_init.h"
/*
// Includes IP-Cores driver for 6 Phase FSC-MPC
#include "IP_Cores/uz_vsd_and_park_transformation_6phase/uz_vsd_and_park_transformation_6phase.h"
#include "IP_Cores/uz_delay_compensation_fcs_mpc_6phase_pmsm/uz_delay_compensation_fcs_mpc_6phase_pmsm.h"
#include "IP_Cores/uz_phase_voltages_per_switching_state_fcs_mpc_6phase/uz_phase_voltages_per_switching_state_fcs_mpc_6phase.h"
#include "IP_Cores/uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm/uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm.h"
#include "IP_Cores/uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM/uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM.h"
*/

// Includes IP-Core drivers for 6 Phase FCS-MPC parallel 8
#include "IP_Cores/uz_vsd_8/uz_vsd_8.h"
#include "IP_Cores/uz_delay_compensation_8/uz_delay_compensation_8.h"
#include "IP_Cores/uz_phase_voltages_8/uz_phase_voltages_8.h"
#include "IP_Cores/uz_prediction_and_cost_function_8/uz_prediction_and_cost_function_8.h"
#include "IP_Cores/uz_min_cost_function_8/uz_min_cost_function_8.h"

#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"

//----------------------------------------------------
// FUNCTIONS
//----------------------------------------------------

void InitializeDataStructure(DS_Data* data);

#endif /* main_H_ */
