/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Global data type
 */

#include "bsp_led/bsp_led.h"

//====================================================================
// Type definitions
//====================================================================
typedef struct {
	bool ready;
	bool running;
	bool error;
	bool user;
} led_t;

typedef struct {
	uint8_t ctrl_enable;
} ctrl_t;

typedef struct {
	led_t led;
	ctrl_t ctrl;
} global_t;

//====================================================================
// Global variables
//====================================================================
// Everyone can use this
extern global_t global;
