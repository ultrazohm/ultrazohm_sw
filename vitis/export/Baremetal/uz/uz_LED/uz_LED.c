#include "uz_LED.h"

static void uz_led_turn_on(uz_statusLED *self);
static void uz_led_turn_off(uz_statusLED *self);

void uz_led_init(uz_statusLED *self, uz_gpio *hw){
	uz_assert_not_NULL(self);
	self->is_ready=true;
	self->hw=hw;
	self->turn_off=&uz_led_turn_off;
	self->turn_on=&uz_led_turn_on;
}

static void uz_led_turn_on(uz_statusLED *self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->hw->write_pin(self->hw,true);
}

static void uz_led_turn_off(uz_statusLED *self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->hw->write_pin(self->hw,false);
}
