/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann, Tobias Schindler
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

		/* Initialize the LED (axi_gpio_2) */
	//	Status = XGpio_Initialize(&GpioLED, LED_DEVICE_ID);
	//	if (Status != XST_SUCCESS) {
	//		return XST_FAILURE;
	//	}
		/*Set the direction for the LEDs to output. */
	//	XGpio_SetDataDirection(&GpioLED, LED_CHANNEL, 0x00);

		// Initialize Push Buttons (axi_gpio_1)
	//	Status = XGpio_Initialize(&GpioPushButton, PUSHBUTTONS_ID);
	//					if(Status != XST_SUCCESS) return XST_FAILURE;
		// Set all five pushbuttons direction to inputs
	//	XGpio_SetDataDirection(&GpioPushButton,PUSHBUTTONS_CHANNEL,0x1f);


		// Initialize the real GPIO PMOD_B1 (axi_gpio_0)
	//	Status = XGpio_Initialize(&Gpio_IN, GPIO_in_ID);
	//				if(Status != XST_SUCCESS) return XST_FAILURE;
		// Set all four  GPIO to input
	//	XGpio_SetDataDirection(&Gpio_IN, GPIO_CHANNEL,0xF0);

		// Initialize the real GPIO PMOD_B1 (axi_gpio_2)
		Status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
					if(Status != XST_SUCCESS) return XST_FAILURE;
		// Set all four  GPIO to output
		//XGpio_SetDataDirection(&Gpio_OUT, GPIO_CHANNEL,0xF0); //SW: DIe ersten vier sind AUsg�nge (=0) und die letzten 4 sind Eing�nge (=F)
		// Set all  GPIO to output -> Geht das �berhaupt?
		XGpio_SetDataDirection(&Gpio_OUT, GPIO_CHANNEL,0x00); //SW: DIe ersten acht sind AUsg�nge (=0) Eing�nge sind (1)

return Status;
}


