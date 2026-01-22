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

#define GPIO_out_ID XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_2_DEVICE_ID /* GPIO device that GPIO is connected to output*/

#define AXI_GPIO_CHANNEL_OUT 		1U
#define AXI_GPIO_CHANNEL_TIMESTAMP  2U   //timestamp input channel

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
#define AXI_GPIO_ALL_INPUTS 	UINT32_MAX

// Initialize the  GPIO structure
static XGpio Gpio_OUT; /* GPIO Device driver instance for the real GPIOs */

//----------------------------------------------------
// INITIALIZE & SET DIRECTIONS OF GPIOs that are instanced on the FPGA
//----------------------------------------------------
void Initialize_AXI_GPIO(void)
{
    int status = XGpio_Initialize(&Gpio_OUT, GPIO_out_ID);
    uz_assert(XST_SUCCESS == status);
    XGpio_SetDataDirection(&Gpio_OUT, AXI_GPIO_CHANNEL_OUT, 	  0U); //all 32 signals are outputs - 0 = output
    XGpio_SetDataDirection(&Gpio_OUT, AXI_GPIO_CHANNEL_TIMESTAMP, UINT32_MAX); //all 32 signals are inputs  - 1 = input

}

void uz_axigpio_disable_pwm_and_power_electronics(void)
{
    XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL_OUT, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE));
}
void uz_axigpio_enable_pwm_and_power_electronics(void)
{
    XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL_OUT, (AXI_GPIO_PWM_MODULES | AXI_GPIO_DIGITAL_ENABLE));
}
void uz_axigpio_disable_datamover(void)
{
    XGpio_DiscreteClear(&Gpio_OUT, AXI_GPIO_CHANNEL_OUT, AXI_GPIO_AXI2TCM_ENABLE);
}
void uz_axigpio_enable_datamover(void)
{
    XGpio_DiscreteSet(&Gpio_OUT, AXI_GPIO_CHANNEL_OUT, AXI_GPIO_AXI2TCM_ENABLE);
}

uint32_t uz_get_bitstream_timestamp_raw(void)
{
	uint32_t timestamp = XGpio_DiscreteRead(&Gpio_OUT, AXI_GPIO_CHANNEL_TIMESTAMP);
    return timestamp;
}


void uz_print_bitstream_timestamp(void)
{

	uint32_t timestamp = uz_get_bitstream_timestamp_raw();

    // Format: ddddd_MMMM_yyyyyy_hhhhh_mmmmmm_ssssss
    // Bits:   31..27 26..23 22..17 16..12 11..6  5..0
	uint32_t day      = (timestamp >> 27) & 0x1F;  // 5 bits
	uint32_t month    = (timestamp >> 23) & 0x0F;  // 4 bits
	uint32_t year_off = (timestamp >> 17) & 0x3F;  // 6 bits, offset from 2000
	uint32_t hour     = (timestamp >> 12) & 0x1F;  // 5 bits
	uint32_t minute   = (timestamp >> 6)  & 0x3F;  // 6 bits
	uint32_t second   =  timestamp        & 0x3F;  // 6 bits

	uint32_t year = 2000u + year_off;

//    uz_printf("USR_ACCESS raw: 0x%08X\n", timestamp);
    uz_printf("Bitstream timestamp : %04u-%02u-%02u at %02u:%02u:%02u\n",
           year, month, day, hour, minute, second);
}
