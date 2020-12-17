/******************************************************************************
*
* gpio.c
*
* Copyright (C) 2018 Institute ELSYS, TH N�rnberg,   All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#include "../include/gpio_axi.h"
#include "xgpio.h"
#include "../defines.h"

// Initialize the  GPIO structure
XGpio Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE & SET DIRECTIONS OF GPIOs that are instanced on the FPGA
//----------------------------------------------------
int Initialize_AXI_GPIO(void){

	int Status;
	Status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
	if(Status != XST_SUCCESS) return XST_FAILURE;
	XGpio_SetDataDirection(&Gpio_OUT, GPIO_CHANNEL,0x00); //SW: DIe ersten acht sind AUsg�nge (=0) Eing�nge sind (1)

return Status;
}


