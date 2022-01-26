#include "uz_LED_facade.h"

static uz_statusLED readyLED;
static uz_statusLED runningLED;
static uz_statusLED errorLED;
static uz_statusLED userLED;

void uz_led_facade_init(uz_LedfacadeCfg cfg) {
	uz_led_init(&readyLED, cfg.LedReady);
	uz_led_init(&runningLED, cfg.LedRunning);
	uz_led_init(&errorLED, cfg.LedError);
	uz_led_init(&userLED, cfg.LedUser);
}

void uz_led_set_readyLED_on() {
	uz_led_turn_on(&readyLED);
}

void uz_led_set_readyLED_off() {
	uz_led_turn_off(&readyLED);
}

void uz_led_set_runningLED_on() {
	uz_led_turn_on(&runningLED);
}

void uz_led_set_runningLED_off() {
	uz_led_turn_off(&runningLED);
}

void uz_led_set_errorLED_on() {
	uz_led_turn_on(&errorLED);
}

void uz_led_set_errorLED_off() {
	uz_led_turn_off(&errorLED);
}

void uz_led_set_userLED_on() {
	uz_led_turn_on(&userLED);
}

void uz_led_set_userLED_off() {
	uz_led_turn_off(&userLED);
}
