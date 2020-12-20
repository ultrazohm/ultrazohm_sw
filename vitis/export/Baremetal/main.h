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

/* Definitions */
#define LED_DELAY 10000000							/* Software delay length */

#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */


// Defines that map the number of the MIO PIN of the PS to the signal name of the signal on the carrier board (X13)
#define PS_DIG_GPIO_01	30
#define PS_DIG_GPIO_02	31
#define PS_ANL_GPIO_01	44
#define PS_ANL_GPIO_02	45
#define EXT_GPIO_1 		13
#define EXT_GPIO_2 		33
#define EXT_GPIO_3 		34
#define EXT_GPIO_4 		39
#define EXT_GPIO_5 		40
#define EXT_GPIO_6 		52
#define EXT_GPIO_7 		53
#define EXT_GPIO_8 		55

// LED on carrier board and frontpanel
#define LED_1								EXT_GPIO_1
#define LED_2								EXT_GPIO_2
#define LED_3								EXT_GPIO_3
#define LED_4								EXT_GPIO_4

// Names of LED on frontpanel
#define LED_ready 	LED_1
#define LED_running LED_2
#define LED_error 	LED_3
#define LED_user 	LED_4

// Switches on frontpanel
#define SW_1 EXT_GPIO_6
#define SW_2 EXT_GPIO_7
#define SW_3 EXT_GPIO_5

#define SW_system  SW_1
#define SW_control SW_2
#define SW_stop    SW_3


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
