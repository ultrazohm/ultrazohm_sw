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

#include "../include/gpio_axi.h"
#include "../defines.h"


// Initialize the  GPIO structure
XGpio Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE & SET DIRECTIONS OF GPIOs that are instanced on the FPGA
//----------------------------------------------------
int Initialize_AXI_GPIO(void){

	int Status;

	// Initialize the real GPIO (axi_gpio_2)
	Status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
				if(Status != XST_SUCCESS) return XST_FAILURE;
	// Set all four  GPIO to output
	//XGpio_SetDataDirection(&Gpio_OUT, GPIO_CHANNEL,0xF0); //SW: DIe ersten vier sind AUsgänge (=0) und die letzten 4 sind Eingänge (=F)
	// Set all  GPIO to output -> Geht das überhaupt?
	XGpio_SetDataDirection(&Gpio_OUT, GPIO_CHANNEL,0x00); //SW: DIe ersten acht sind AUsgänge (=0) Eingänge sind (01)

return Status;
}


