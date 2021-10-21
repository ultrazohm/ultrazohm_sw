#include "uz_LED.h"
#include "../uz_HAL.h"


void uz_led_init(uz_statusLED *self, uz_gpio *hw){
	uz_assert_not_NULL(self);
	self->is_ready=true;
	self->hw=hw;
}

void uz_led_turn_on(uz_statusLED *self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_gpio_write_pin(self->hw,true);
}

void uz_led_turn_off(uz_statusLED *self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_gpio_write_pin(self->hw,false);
}
