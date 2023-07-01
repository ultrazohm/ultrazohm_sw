/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for control function
 */


#include <stdint.h>

#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"

#include "global_data.h"



global_t global;

//====================================================================
// Configuration
//====================================================================

extern volatile uint32_t fpga_irq_cnt;
volatile uint32_t fpga_irq_cnt = 0;

void irq_fpga(void *data)
{
	fpga_irq_cnt++;


	// control_fast() goes here

	// XCP_event_fast() goes here

}

void basis_setup(void *p)
{
	bsp_led_init();
	xil_printf("APU: basis init done\n", __func__);

	global.led.error = 0;
	global.led.ready = 1;
	global.led.running = 0;
	global.led.user = 0;

	while (1) {
		static uint8_t cnt = 0;
		cnt++;
		global.led.running = (cnt & 1);



		bsp_led_run();



		vTaskDelay(100 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}




