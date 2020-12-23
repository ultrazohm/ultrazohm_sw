/******************************************************************************
*
* main.h
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
* Description: Zynq UltraScale+
*
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
#include "include/gpio_axi.h"
#include "include/pwm.h"
#include "include/javascope.h"
#include "include/control.h"
#include "include/pwm_3L_driver.h"
#include "IP_Cores/Trans_123_dq/dqTransform.h"

#include "uz/uz_HAL.h"

#include "uz/uz_LED/uz_LED_facade.h"
#include "uz/uz_PushButton/uz_PushButton_facade.h"

#include "uz/uz_MioGpio_mediator/uz_MioGpio_mediator.h"
#include "uz/uz_MioGpio_mediator/uz_MioGpioMapping.h"

//ADC define
#define TX_BUFFER_SIZE						1
#define RX_BUFFER_SIZE  					64
//Defines for averaging the current from the ADC
#define  CURRENT_BUF_SIZE 					6
#define  CURRENT_BUF_SIZE_INVERS 			1/CURRENT_BUF_SIZE

// ========== JavaScope-Ethernet =========================================================================
//Defines for JavaScope (4 or 2 channels)
#define chJavaScope			4
//#define chJavaScope		2

//----------------------------------------------------
// FUNCTIONS
//----------------------------------------------------

void plotData(DS_Data* data);
void turnPowerElectronicsOff(DS_Data* data);
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
