#ifndef UZ_GPIO_H
#define UZ_GPIO_H

#include <stdbool.h>
#include "xgpiops.h"

typedef struct uz_gpio_ {
	XGpioPs *hw;
	_Bool is_ready;
	int pin_number;
	int direction;
} uz_gpio;

void uz_gpio_init(uz_gpio *self, XGpioPs *Xgpio_instance, uint32_t pin_number, uint32_t direction);

void uz_gpio_set_direction(struct uz_gpio_ *self, uint32_t Direction);
uint32_t uz_gpio_get_direction(struct uz_gpio_ *self);
void uz_gpio_set_enable_output(struct uz_gpio_ *self, uint32_t EnableOutput);
uint32_t uz_gpio_get_enable_output(struct uz_gpio_ *self);
void uz_gpio_write_pin(struct uz_gpio_ *self, uint32_t value);
uint32_t uz_gpio_read_pin(struct uz_gpio_ *self);


#endif
