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
#include "xcp/xcp_interface.h"





#include "../globalData.h"

#include "../include/uz_assertion_configuration.h"
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "../include/uz_adcLtc2311_ip_core_init.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

#include "../include/gpio_axi.h"
#include "../include/pwm_3L_driver.h"
#include "../include/encoder.h"
#include "../include/isr.h"


//====================================================================
// Type definitions
//====================================================================
typedef struct {
	uint8_t array_50_byte [50];
	uint8_t array_90_byte [90];
	uint8_t array_100_byte [100];

	uint8_t saw_u8;
	int8_t sin_u8;
	int8_t cos_u8;
	float sin_f;
} control_dummy_t;

//====================================================================
// Configuration
//====================================================================


//====================================================================
// Variables
//====================================================================
// Initialize the global variables
DS_Data Global_Data = {
    .rasv = {
        .halfBridge1DutyCycle = 0.0f,
        .halfBridge2DutyCycle = 0.0f,
        .halfBridge3DutyCycle = 0.0f,
        .halfBridge4DutyCycle = 0.0f,
        .halfBridge5DutyCycle = 0.0f,
        .halfBridge6DutyCycle = 0.0f,
		.halfBridge7DutyCycle = 0.0f,
		.halfBridge8DutyCycle = 0.0f,
		.halfBridge9DutyCycle = 0.0f,
		.halfBridge10DutyCycle = 0.0f,
		.halfBridge11DutyCycle = 0.0f,
		.halfBridge12DutyCycle = 0.0f
    },
    .av.pwm_frequency_hz = UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};


global_t global = {0};

extern control_dummy_t control_dummy;
control_dummy_t control_dummy = {0};

extern volatile uint32_t fpga_irq_cnt;
volatile uint32_t fpga_irq_cnt = 0;


#include "bsp_timer/bsp_timer.h"
extern float fpga_irq_time;
float fpga_irq_time = 0;
extern float fpga_irq_freq;
float fpga_irq_freq = 0;





//====================================================================
// Static functions
//====================================================================
// Todo remove
static void control_dummy_init(void)
{
	for (int i = 0; i < 50; i++) {
		control_dummy.array_50_byte[i] = i;
	}
	for (int i = 0; i < 90; i++) {
		control_dummy.array_90_byte[i] = i;
	}
	for (int i = 0; i < 100; i++) {
		control_dummy.array_100_byte[i] = i;
	}
}

// Todo remove
static void control_dummy_run(void)
{
	for (int i = 0; i < 50; i++) {
		control_dummy.array_50_byte[i]++;
	}
	for (int i = 0; i < 90; i++) {
		control_dummy.array_90_byte[i]++;
	}
	for (int i = 0; i < 100; i++) {
		control_dummy.array_100_byte[i]++;
	}

	// Get sine wave with about 1 Hz
	// Div_factor = call-rate / 255
	static int div_cnt = 0;
	div_cnt++;
	if (div_cnt >= 39) {
		div_cnt = 0;

		static uint8_t cnt_sin = 0;
		cnt_sin++;
		control_dummy.saw_u8 = cnt_sin;
		float angle = (M_PI * 2 * cnt_sin / UINT8_MAX);
		control_dummy.sin_f = sinf(angle);
		control_dummy.sin_u8 = sinf(angle) * INT8_MAX;
		control_dummy.cos_u8 = cosf(angle) * INT8_MAX;
	}
}

//====================================================================
// Global functions
//====================================================================
void irq_fpga(void *data)
{
	uint64_t ts_now = bsp_timer_timestamp_u64_get();

	static uint64_t ts_last = 0;
	fpga_irq_time = bsp_timer_tsU64_delta_us(ts_last, ts_now);
	fpga_irq_freq = (1 / fpga_irq_time * 1e6);
	ts_last = ts_now;

	fpga_irq_cnt++;


	//---------------------
	// Fast stuff
	if (global.ctrl.ctrl_enable) {
		control_dummy_run();
	}
	xcp_event_fast();

	//---------------------
	// Slow stuff
	static uint64_t ts_last_activation_1ms = 0;
	const uint64_t ticks_1ms = (BSP_TIMER_TICKS_PER_SECOND / 1000);
	if ((ts_now - ts_last_activation_1ms) >= ticks_1ms) {
		ts_last_activation_1ms = ts_now;
		xcp_events_1ms();
	}
}

void basis_setup(void *p)
{
	uz_assert_configuration();
	Initialize_AXI_GPIO();
	uz_adcLtc2311_ip_core_init();
    Global_Data.objects.deadtime_interlock_d1_pin_0_to_5 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5();
    Global_Data.objects.deadtime_interlock_d1_pin_6_to_11 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11();
    Global_Data.objects.deadtime_interlock_d1_pin_12_to_17 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17();
    Global_Data.objects.deadtime_interlock_d1_pin_18_to_23 = uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23();
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, true);
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, true);
    Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
    Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
    Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
    Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
    Global_Data.objects.mux_axi = initialize_uz_mux_axi();
    PWM_3L_Initialize(&Global_Data); // three-level modulator
    initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
    uz_axigpio_enable_datamover();


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




