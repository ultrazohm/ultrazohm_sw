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
#include "../uz/uz_HAL.h"
#include "../include/gpio_axi.h"
#include "xgpio.h"

#define GPIO_out_ID XPAR_AXI_GPIO_2_DEVICE_ID /* GPIO device that GPIO is connected to output*/

#define AXI_GPIO_CHANNEL 1

#define AXI_BIT_0 (1U << 0) // 0b00000001 - output[0] in PL
#define AXI_BIT_1 (1U << 1) // 0b00000010 - output[1] in PL
#define AXI_BIT_2 (1U << 2) // 0b00000100 - output[2] in PL
#define AXI_BIT_3 (1U << 3) // 0b00001000 - output[3] in PL
#define AXI_BIT_4 (1U << 4) // 0b00010000 - output[4] in PL
#define AXI_BIT_5 (1U << 5) // 0b00100000 - output[5] in PL
#define AXI_BIT_6 (1U << 6) // 0b01000000 - output[6] in PL
#define AXI_BIT_7 (1U << 7) // 0b10000000 - output[7] in PL

#define AXI_GPIO_PWM_MODULES    AXI_BIT_0
#define AXI_GPIO_DIGITAL_ENABLE AXI_BIT_1
#define AXI_GPIO_AXI2TCM_ENABLE AXI_BIT_4

// Initialize the  GPIO structure
static XGpio Gpio_OUT; /* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE & SET DIRECTIONS OF GPIOs that are instanced on the FPGA
//----------------------------------------------------
void Initialize_AXI_GPIO(void)
{
    int status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
    uz_assert(XST_SUCCESS == status);
    XGpio_SetDataDirection(&Gpio_OUT, AXI_GPIO_CHANNEL, 0x00U); //SW: First eight signals are outputs by setting the bitmask to zero for these
}

void uz_axigpio_disable_pwm_and_power_electronics(void)
{
    XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE));
}
void uz_axigpio_enable_pwm_and_power_electronics(void)
{
    XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE));
}
void uz_axigpio_disable_datamover(void)
{
    XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL, AXI_GPIO_AXI2TCM_ENABLE);
}
void uz_axigpio_enable_datamover(void)
{
    XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL, AXI_GPIO_AXI2TCM_ENABLE);
}
