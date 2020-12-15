/******************************************************************************
 *
 * gpio.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 21.08.2016
 *      Author: Sebastian Wendel (SW)
 *
******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../main.h"

void Initialize_GPIO(void);
int Initialize_PS_GPIO(uint32_t gpio_base_address, uint32_t gpio_device_id);
int SetDirection_PS_GPIO(uint32_t gpio_MIO_number, uint32_t direction); // Init GPIOs
int Enable_PS_GPIO(uint32_t gpio_MIO_number, uint32_t PinSetting);
int WritePin_PS_GPIO(uint32_t gpio_MIO_number, uint32_t data);
int ReadPin_PS_GPIO(uint32_t gpio_MIO_number);
#endif /* GPIO_H_ */
