#ifndef UZ_GPIO_H
#define UZ_GPIO_H

#include <stdbool.h>
#include "xgpiops.h"
#include "../uz_HAL.h"

typedef struct uz_gpio_ {
	XGpioPs *hw;
	_Bool is_ready;
	int pin_number;
	int direction;
	void (*set_direction)(struct uz_gpio_ *self, uint32_t direction);
	uint32_t (*get_direction)(struct uz_gpio_ *self);
	void (*set_enable_output)(struct uz_gpio_ *self, uint32_t EnableOutput);
	uint32_t (*get_enable_output)(struct uz_gpio_ *self);
	void (*write_pin)(struct uz_gpio_ *self, uint32_t value);
	uint32_t (*read_pin)(struct uz_gpio_ *self);
} uz_gpio;

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, uint32_t pin_number, uint32_t direction);

#endif
