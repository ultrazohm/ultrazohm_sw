/******************************************************************************
*
* gpio.c
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg,   All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#include "xgpiops.h"
#include "../include/gpio.h"
#include "../defines.h"


Xuint32	Pin30;
Xuint32	Pin31;
Xuint32	Pin44;
Xuint32	Pin45;
Xuint32	Pin40;

// Initialize the  GPIO structure
static XGpioPs Gpio_inst;											/* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE GPIOs that are instanced directly from the processor (MIO pins)
//----------------------------------------------------
int Initialize_PS_GPIO(uint32_t gpio_base_address, uint32_t gpio_device_id){

	int status;

	XGpioPs_Config gpio_config;
	gpio_config.BaseAddr = gpio_base_address; // e.g.: XPAR_PSU_GPIO_0_BASEADDR;
	gpio_config.DeviceId = gpio_device_id; // e.g.: XPAR_PSU_GPIO_0_DEVICE_ID;

	// Initialize the processor GPIO (MIO pins)
	status = XGpioPs_CfgInitialize(&Gpio_inst, &gpio_config, gpio_config.BaseAddr);
	if(status != XST_SUCCESS) return XST_FAILURE;

return status;
}


//----------------------------------------------------
// SET DIRECTIONS of the processor GPIOs
//----------------------------------------------------
int SetDirection_PS_GPIO(uint32_t gpio_MIO_number, uint32_t direction){

	int status = XST_SUCCESS;

	//Set the direction of the pins separately
	XGpioPs_SetDirectionPin(&Gpio_inst, gpio_MIO_number, direction); //0 for Input Direction, 1 for Output Direction

return status;
}


//----------------------------------------------------
// SET ENABLE of the processor GPIOs
//----------------------------------------------------
int Enable_PS_GPIO(uint32_t gpio_MIO_number, uint32_t PinSetting){

	int status = XST_SUCCESS;

	//Enable the specified pin separately
	XGpioPs_SetOutputEnablePin(&Gpio_inst, gpio_MIO_number, PinSetting); //0 for Off, 1 for On

	Pin30 = XGpioPs_GetOutputEnablePin(&Gpio_inst,30);
	Pin31 = XGpioPs_GetOutputEnablePin(&Gpio_inst,31);
	Pin44 = XGpioPs_GetOutputEnablePin(&Gpio_inst,44);
	Pin45 = XGpioPs_GetOutputEnablePin(&Gpio_inst,45);
	Pin40 = XGpioPs_GetOutputEnablePin(&Gpio_inst,40);

return status;
}



//----------------------------------------------------
// Write a Pin from the processor GPIOs
//----------------------------------------------------
int WritePin_PS_GPIO(uint32_t gpio_MIO_number, uint32_t data){

	int status = XST_SUCCESS;

	//Write the data of the pins separately
	XGpioPs_WritePin(&Gpio_inst, gpio_MIO_number, data); // for date: 0 or 1

return status;
}

