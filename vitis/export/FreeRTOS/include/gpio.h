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

#ifndef GPIO_H_
#define GPIO_H_

#include "../main.h"

int Initialize_PS_GPIO(uint32_t gpio_base_address, uint32_t gpio_device_id);
int SetDirection_PS_GPIO(uint32_t gpio_MIO_number, uint32_t direction); // Init GPIOs
int Enable_PS_GPIO(uint32_t gpio_MIO_number, uint32_t PinSetting);
int WritePin_PS_GPIO(uint32_t gpio_MIO_number, uint32_t data);

#endif /* GPIO_H_ */
