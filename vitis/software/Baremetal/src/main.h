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

// stdlib
#include <math.h>										//Include for math operations
#include <stdbool.h>

// Xilinx library functions
#include "xscugic.h"									//Include for Interrupt handler (necessary for all GIC interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xtmrctr.h"									//Include of the Timer-Blocks

// UltraZohm includes
#include "globalData.h"
#include "defines.h"
#include "include/isr.h"
#include "include/encoder.h"
#include "include/gpio_axi.h"
#include "include/javascope.h"
#include "include/pwm_3L_driver.h"

#include "uz/uz_HAL.h"

#include "uz/uz_LED/uz_LED_facade.h"
#include "uz/uz_PushButton/uz_PushButton_facade.h"

#include "uz/uz_MioGpio_mediator/uz_MioGpio_mediator.h"
#include "uz/uz_MioGpio_mediator/uz_MioGpioMapping.h"

#include "uz/uz_SystemTime/uz_SystemTime.h"

#include "include/pwm_init.h"


//----------------------------------------------------
// FUNCTIONS
//----------------------------------------------------

void plotData(DS_Data* data);
int turnPowerElectronicsOff(DS_Data* data);
int turnPowerElectronicsOn(DS_Data* data);
void AXI2TCM_on(void);
void ControllerOff(DS_Data* data);
void ErrorHandling(DS_Data* data);
void ErrorReset(DS_Data* data);
void ControllerOn(DS_Data* data);
void ADC_Set_Offset(void);
void ADC_Clear_Offset(void);
void InitializeDataStructure(DS_Data* data);

#endif /* main_H_ */
