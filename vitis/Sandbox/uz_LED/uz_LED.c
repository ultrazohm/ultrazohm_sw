#include "uz_LED.h"

static void uz_led_turnOn(uz_StatusLed *self);
static void uz_led_turnOff(uz_StatusLed *self);

int uz_led_init(uz_StatusLed *self){
	uz_assertNotNull(self);
	self->isReady=true;
	self->turnOff=&uz_led_turnOff;
	self->turnOn=&uz_led_turnOn;
};

static void uz_led_turnOn(uz_StatusLed *self){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	//call GPIO API
};

static void uz_led_turnOff(uz_StatusLed *self){
	uz_assertNotNull(self);
	uz_assert(self->isReady);
	//call GPIO API
};
