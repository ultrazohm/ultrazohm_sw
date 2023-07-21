/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for LEDs
 */

#include "xparameters.h"
#include "xgpiops.h"

#include "uz_led_abstraction.h"
#include "bsp_led.h"
#include "../global_data.h"


typedef enum led_t_ {
	led_pin_ready,
	led_pin_running,
	led_pin_error,
	led_pin_user,
	led_pin_cnt // Must be last!
} led_pin_t;

//====================================================================
// Static variables
//====================================================================
static bool led_values [led_pin_cnt] = {0};

//====================================================================
// Static functions
//====================================================================
static void bsp_led_set__(led_pin_t led, bool on)
{
	switch (led) {
	case led_pin_ready:   uz_led_abstraction_set(0, on); break;
	case led_pin_running: uz_led_abstraction_set(1, on); break;
	case led_pin_error:   uz_led_abstraction_set(2, on); break;
	case led_pin_user:    uz_led_abstraction_set(3, on); break;
	default: xil_printf("ERROR: %s(): unknown LED %d\n", __func__, led);
	}
	led_values[led] = on;
}

//static bool bsp_led_get__(led_pin_t led)
//{
//	return led_values[led];
//}

//====================================================================
// Global functions
//====================================================================
void bsp_led_init(void)
{
	uz_led_abstraction_init();
	for (int i = 0; i < led_pin_cnt; i++) {
		bsp_led_set__(i, 0);
	}
}

//void bsp_led_set(led_pin_t led, bool on)
//{
//	bsp_led_set__(led, on);
//}
//
//bool bsp_led_get(led_pin_t led)
//{
//	return bsp_led_get__(led);
//}

void bsp_led_run(void)
{
	bsp_led_set__(led_pin_ready, global.led.ready);
	bsp_led_set__(led_pin_running, global.led.running);
	bsp_led_set__(led_pin_error, global.led.error);
	bsp_led_set__(led_pin_user, global.led.user);
}
