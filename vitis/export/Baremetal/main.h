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
#include "xgpiops.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "xscugic.h"									//Include for Interrupt handler (necessary for all GIC interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xil_types.h" 								//Include for Datatypes
#include "xtmrctr.h"									//Include of the Timer-Blocks

// UltraZohm includes
#include "globalData.h"
#include "defines.h"
#include "include/isr.h"
#include "include/adc.h"
#include "include/encoder.h"
#include "include/gpio.h"
#include "include/gpio_axi.h"
#include "include/pwm.h"
#include "include/javascope.h"
#include "include/control.h"
#include "include/pwm_3L_driver.h"
#include "IP_Cores/Trans_123_dq/dqTransform.h"

#include "uz/uz_HAL.h"

#include "uz/uz_LED/uz_LED_facade.h"
#include "uz/uz_MioGpio_mediator/uz_MioGpio_mediator.h"
#include "uz/uz_MioGpio_mediator/uz_MioGpioMapping.h"
/* Definitions */
#define LED_DELAY 10000000							/* Software delay length */

//ADC define
#define TX_BUFFER_SIZE						1
#define RX_BUFFER_SIZE  					64
//Defines for averaging the current from the ADC
#define  CURRENT_BUF_SIZE 					6
#define  CURRENT_BUF_SIZE_INVERS 			1/CURRENT_BUF_SIZE

//ADC define
#define XAdcPL_RAWToCurrent_6A			0.0036747685 //Faktor 12 Bit vergleiche Excel: "Auslegung Stromsensoren LEM"

//Frequencies in the system
#define FPGA_100MHz		100000000.0f		//Clock frequency
#define FPGA_50MHz		50000000.0f			//Clock frequency
#define FPGA_20MHz		20000000.0f			//Clock frequency
#define FPGA_10MHz		10000000.0f			//Clock frequency

// ========== JavaScope-Ethernet =========================================================================
//Defines for JavaScope (4 or 2 channels)
#define chJavaScope			4
//#define chJavaScope		2

//----------------------------------------------------
// FUNCTIONS
//----------------------------------------------------

int plotData(DS_Data* data);
int turnPowerElectronicsOff(DS_Data* data);
int turnPowerElectronicsOn(DS_Data* data);
int AXI2TCM_on(void);
int ControllerOff(DS_Data* data);
int ErrorHandling(DS_Data* data);
int ErrorReset(DS_Data* data);
int ControllerOn(DS_Data* data);
int ADC_Set_Offset(void);
int ADC_Clear_Offset(void);
int InitializeDataStructure(DS_Data* data);


#endif /* main_H_ */
