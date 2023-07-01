/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for LEDs
 */

#include <stdbool.h>

//====================================================================
// Type definitions
//====================================================================

//====================================================================
// Global functions
//====================================================================
void bsp_led_init(void);
//void bsp_led_set(led_pin_t led, bool on);
//bool bsp_led_get(led_pin_t led);
void bsp_led_run(void);
