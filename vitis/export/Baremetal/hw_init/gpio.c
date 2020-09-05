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


// Initialize the  GPIO structure
static XGpioPs Gpio_inst;											/* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE GPIOs that are instanced directly from the processor (MIO pins)
//----------------------------------------------------
int Initialize_GPIO( ){

	int status;
	xil_printf(" Init GPIO \n\r"); //GPIO interface
	Initialize_PS_GPIO(XPAR_PSU_GPIO_0_BASEADDR, XPAR_PSU_GPIO_0_DEVICE_ID); //GPIO 0 interface

	//Subsequently i specify each Pin separately, in order to avoid to activate an not used Pin
	//The Pin number is the MIO number (see Vivado)
	//sets direction of LED to output
	SetDirection_PS_GPIO(LED_ready,OUTPUT_PIN); //Configure GPIO
	SetDirection_PS_GPIO(LED_running,OUTPUT_PIN); //Configure GPIO
	SetDirection_PS_GPIO(LED_error,OUTPUT_PIN); //Configure GPIO
	SetDirection_PS_GPIO(LED_user,OUTPUT_PIN); //Configure GPIO
	// sets direction of switches to input
	SetDirection_PS_GPIO(SW_system,INPUT_PIN); //Configure GPIO
	SetDirection_PS_GPIO(SW_control,INPUT_PIN); //Configure GPIO
	SetDirection_PS_GPIO(SW_stop,INPUT_PIN); //Configure GPIO

	//Enbale the specified Pins on the Bank separately
	//The Pin number is the MIO number (see Vivado)
	Enable_PS_GPIO(LED_ready,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(LED_running,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(LED_error,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(LED_user,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(SW_system,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(SW_control,ENABLE_PIN); //Enable the GPIO
	Enable_PS_GPIO(SW_stop,ENABLE_PIN); //Enable the GPIO

return status;
}

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

//----------------------------------------------------
// Read a Pin from the processor GPIOs
//----------------------------------------------------
int ReadPin_PS_GPIO(uint32_t gpio_MIO_number){

	//int status = XST_SUCCESS;
	Xint32 value=0;
	//Write the data of the pins separately
	value=XGpioPs_ReadPin(&Gpio_inst, gpio_MIO_number); // for date: 0 or 1

return value;
}
