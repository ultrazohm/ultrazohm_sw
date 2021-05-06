#include "uz_LED_facade.h"

static uz_statusLED readyLED, runningLED, errorLED, userLED;

void uz_led_facade_init(uz_LedfacadeCfg cfg) {
	uz_led_init(&readyLED, cfg.LedReady);
	uz_led_init(&runningLED, cfg.LedRunning);
	uz_led_init(&errorLED, cfg.LedError);
	uz_led_init(&userLED, cfg.LedUser);
}

void uz_led_set_readyLED_on() {
	readyLED.turn_on(&readyLED);
}

void uz_led_set_readyLED_off() {
	readyLED.turn_off(&readyLED);
}

void uz_led_set_runningLED_on() {
	runningLED.turn_on(&runningLED);
}

void uz_led_set_runningLED_off() {
	runningLED.turn_off(&runningLED);
}

void uz_led_set_errorLED_on() {
	errorLED.turn_on(&errorLED);
}

void uz_led_set_errorLED_off() {
	errorLED.turn_off(&errorLED);
}

void uz_led_set_userLED_on() {
	userLED.turn_on(&userLED);
}

void uz_led_set_userLED_off() {
	userLED.turn_off(&userLED);
}
