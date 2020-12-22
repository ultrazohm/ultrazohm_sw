#ifndef UZ_GPIO_H
#define UZ_GPIO_H

#include <stdbool.h>
#include "xgpiops.h"
#include "../uz_HAL.h"

typedef struct uz_gpio_{
	XGpioPs *hw;
	_Bool isReady;
	int PinNumber;
	int Direction;
	void (*SetDirection)(struct uz_gpio_ *self, uint32_t Direction);
	uint32_t (*GetDirection)(struct uz_gpio_ *self);
	void (*SetEnableOutput)(struct uz_gpio_ *self, uint32_t EnableOutput);
	uint32_t (*GetEnableOutput)(struct uz_gpio_ *self);
	void (*WritePin) (struct uz_gpio_ *self, uint32_t value);
	uint32_t (*ReadPin) (struct uz_gpio_ *self);
}uz_gpio;

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, uint32_t PinNumber, uint32_t Direction);

#endif
