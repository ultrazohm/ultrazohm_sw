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

#define GPIO_out_ID						XPAR_AXI_GPIO_2_DEVICE_ID 		/* GPIO device that GPIO is connected to output*/

#define AXI_GPIO_CHANNEL 1

#define AXI_BIT_0 (1U << 0)
#define AXI_BIT_1 (1U << 1)
#define AXI_BIT_2 (1U << 2)
#define AXI_BIT_3 (1U << 3)
#define AXI_BIT_4 (1U << 4)
#define AXI_BIT_5 (1U << 5)
#define AXI_BIT_6 (1U << 6)
#define AXI_BIT_7 (1U << 7)

#define AXI_GPIO_PWM_MODULES AXI_BIT_0
#define AXI_GPIO_DIGITAL_ENABLE AXI_BIT_1
#define AXI_GPIO_AXI2TCM_ENABLE AXI_BIT_4

// Initialize the  GPIO structure
static XGpio Gpio_OUT; /* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE & SET DIRECTIONS OF GPIOs that are instanced on the FPGA
//----------------------------------------------------
int Initialize_AXI_GPIO(void)
{

	int Status;
	Status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;
	XGpio_SetDataDirection(&Gpio_OUT, AXI_GPIO_CHANNEL, 0x00); //SW: DIe ersten acht sind AUsg�nge (=0) Eing�nge sind (1)

	return Status;
}

void uz_axigpio_disable_pwm_and_power_electronics(void)
{
	XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE)); //Switch power electronics off = 0b0001 = "Disable_Inverter" //Switch Gate connection off = 0b0010 = "Disable_Gate"
}
void uz_axigpio_enable_pwm_and_power_electronics(void)
{
	XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE)); //Switch power electronics on = 0b0001 = "Enable_Inverter" On  //Switch Gate connection on = 0b0010 = "Enable_Gate" On
}
void uz_axigpio_disable_datamover(void)
{
	XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL, AXI_GPIO_AXI2TCM_ENABLE); // 4 = 0b0100 Release the offset, otherwise converted output remains 0
}
void uz_axigpio_enable_datamover(void)
{
	XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL, AXI_GPIO_AXI2TCM_ENABLE); // bit 5 : 16 = 0b10000 Enables the AXI2TCM module to write measurements directly to the TCM
}
