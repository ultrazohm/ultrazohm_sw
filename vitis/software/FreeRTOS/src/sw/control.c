/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface for control function
 */

#include <stdint.h>
#include <stdbool.h>

#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "../main.h"

#include "xcp/xcp_interface.h"
#include "global_data.h"
#include "bsp_timer/bsp_timer.h"

#include "../globalData.h"
#include "../include/uz_assertion_configuration.h"
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_hw.h"
#include "../IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "../include/uz_adcLtc2311_ip_core_init.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

#include "../include/gpio_axi.h"
#include "../include/pwm_3L_driver.h"
#include "../include/encoder.h"
#include "../include/pwm_init.h"
#include "../include/mux_axi.h"
#include "../include/adc.h"
#include "../include/isr.h"

//====================================================================
// Type definitions
//====================================================================
// TODO remove
typedef struct {
	uint8_t array_50_byte [50];
	uint8_t array_90_byte [90];
	uint8_t array_100_byte [100];

	uint8_t saw_u8;
	int8_t sin_u8;
	int8_t cos_u8;
	float sin_f;
} control_dummy_t;

typedef struct {
	float duty_cycle_1;
	float duty_cycle_2;
	float duty_cycle_3;
	float duty_cycle_4;
	float duty_cycle_5;
	float duty_cycle_6;
} duty_cycles_t;

typedef struct timing_value_t_ {
	float irq_rate;
	float irq_time;
	float task_fast;
	float task_slow;
	float task_1ms;
	float task_10ms;
	float config_update;
} timing_value_t;

typedef struct timing_t_ {
	timing_value_t now;
	timing_value_t max;
	float irq_freq_kHz;
} timing_t;

typedef struct sanity_t_ {
	uint32_t cnt_activation_irq_1ms;
	uint32_t cnt_activation_task_fast;
	uint32_t cnt_activation_task_1ms;
	uint32_t cnt_activation_task_10ms;
} sanity_t;

//====================================================================
// Configuration
//====================================================================
#define BACKGROUND_TASK_STACK_SIZE		1024
// Must be task with highest priority!
#define BACKGROUND_TASK_PRIO_1MS		7
#define BACKGROUND_TASK_PRIO_10MS		(BACKGROUND_TASK_PRIO_1MS - 1)

#define ACTIVATION_QUEUE_LEN			1
#define ACTIVATION_QUEUE_ITEM_SIZE		1

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
	.av.deadtime_us = UZ_DEADTIME_US,
    .av.isr_samplerate_s = (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa = {.A1 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
    	   .A2 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f},
		   .A3 = {.cf.ADC_A1 = 10.0f, .cf.ADC_A2 = 10.0f, .cf.ADC_A3 = 10.0f, .cf.ADC_A4 = 10.0f, .cf.ADC_B5 = 10.0f, .cf.ADC_B6 = 10.0f, .cf.ADC_B7 = 10.0f, .cf.ADC_B8 = 10.0f}
    }
};

volatile global_t global = {0};

volatile static duty_cycles_t duty_cycles;

volatile static timing_t timing_us;
volatile static sanity_t sanity;

static QueueHandle_t queue_task_1ms;
static QueueHandle_t queue_task_10ms;

// TODO remove
extern control_dummy_t control_dummy;
control_dummy_t control_dummy = {0};

//====================================================================
// Static functions
//====================================================================
#define TS__(name_, ts_start_, ts_end_) \
	timing_us.now.name_ = bsp_timer_tsU64_delta_us(ts_start_, ts_end_); \
	if (timing_us.now.name_ > timing_us.max.name_) \
	timing_us.max.name_ = timing_us.now.name_;

static void timing_max_reset(void)
{
	static uint64_t ts_last_activation = 0;
	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	if (bsp_timer_tsU64_delta_us(ts_last_activation, ts_now) >= (float)3e6) {
		ts_last_activation = ts_now;
		memset((void*)&timing_us.max, 0, sizeof(timing_us.max));
	}
}

// Todo remove
static void control_dummy_run(void)
{
	static bool init_once = 1;
	if (init_once) {
		init_once = 0;

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


static void task_fast(void)
{
	uint64_t ts_start = bsp_timer_timestamp_u64_get();

    ADC_readCardALL(&Global_Data);
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

	static bool pwm_enable_last = 1;
	if (pwm_enable_last != global.ctrl.pwm_enable) {
		if (global.ctrl.pwm_enable) {
			uz_axigpio_enable_pwm_and_power_electronics();
		} else {
			uz_axigpio_disable_pwm_and_power_electronics();
		}
	}
	pwm_enable_last = global.ctrl.pwm_enable;

	if (global.ctrl.ctrl_enable) {
		//control_dummy_run();



		Global_Data.rasv.halfBridge1DutyCycle = duty_cycles.duty_cycle_1;
		Global_Data.rasv.halfBridge2DutyCycle = duty_cycles.duty_cycle_2;
		Global_Data.rasv.halfBridge3DutyCycle = duty_cycles.duty_cycle_3;
		Global_Data.rasv.halfBridge4DutyCycle = duty_cycles.duty_cycle_4;
		Global_Data.rasv.halfBridge5DutyCycle = duty_cycles.duty_cycle_5;
		Global_Data.rasv.halfBridge6DutyCycle = duty_cycles.duty_cycle_6;
	} else {
		Global_Data.rasv.halfBridge1DutyCycle = 0;
		Global_Data.rasv.halfBridge2DutyCycle = 0;
		Global_Data.rasv.halfBridge3DutyCycle = 0;
		Global_Data.rasv.halfBridge4DutyCycle = 0;
		Global_Data.rasv.halfBridge5DutyCycle = 0;
		Global_Data.rasv.halfBridge6DutyCycle = 0;
		Global_Data.rasv.halfBridge7DutyCycle = 0;
		Global_Data.rasv.halfBridge8DutyCycle = 0;
		Global_Data.rasv.halfBridge9DutyCycle = 0;
		Global_Data.rasv.halfBridge10DutyCycle = 0;
		Global_Data.rasv.halfBridge11DutyCycle = 0;
		Global_Data.rasv.halfBridge12DutyCycle = 0;
	}

	// The function uz_PWM_SS_2L_set_duty_cycle() checks values and throws error! Catch this..
	#define RANGE_CHECK(duty_cycle_, min_, max_) \
	if ((duty_cycle_ < (float)min_) || (duty_cycle_ > (float)max_)) { \
		duty_cycle_ = 0; \
	}
	RANGE_CHECK(Global_Data.rasv.halfBridge1DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge2DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge3DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge4DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge5DutyCycle, 0, 1);
	RANGE_CHECK(Global_Data.rasv.halfBridge6DutyCycle, 0, 1);

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    // Currently not used
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Currently not used
    // Set duty cycles for three-level modulator
//    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
//                        Global_Data.rasv.halfBridge2DutyCycle,
//                        Global_Data.rasv.halfBridge3DutyCycle);

	xcp_event_fast();

	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	TS__(task_fast, ts_start, ts_now);
}

static void task_slow(void)
{
	uint64_t ts_start = bsp_timer_timestamp_u64_get();

	// 1 Second Task
	// Todo Vielleicht wo anders platzieren..
	static uint32_t div_cnt = 0;
	div_cnt++;
	if (div_cnt >= (uint32_t)1e3) {
		div_cnt = 0;
		timing_max_reset();
	}

	xcp_events_1ms();

	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	TS__(task_slow, ts_start, ts_now);
}

static void task_1ms(void)
{

}

static void task_10ms(void)
{

}

/*
 * This task runs with high priority in the background. It will be interrupted
 * only by fast_ctrl.
 * It runs with highest FreeRTOS priority. Fast-ctrl runs in irq.
 */
static void task_background_1ms(void *p)
{
	while (1) {
		/*
		 * Implement simple activation of this task with a queue.
		 * Read blocking from queue. An interrupt will write to the queue
		 * each tick and thus activate this task.
		 */
		uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
		xQueueReceive(queue_task_1ms, buf, portMAX_DELAY);

		uint64_t ts_start = bsp_timer_timestamp_u64_get();
		sanity.cnt_activation_task_1ms++;
		task_1ms();
		uint64_t ts_now = bsp_timer_timestamp_u64_get();
		TS__(task_1ms, ts_start, ts_now);
	}
}

/*
 * This task runs with high priority in the background. It will be interrupted
 * only by fast_ctrl and task_1ms.
 * It runs with second highest FreeRTOS priority. Fast-ctrl runs in irq.
 */
static void task_background_10ms(void *p)
{
	while (1) {
		/*
		 * Implement simple activation of this task with a queue.
		 * Read blocking from queue. An interrupt will write to the queue
		 * each tick and thus activate this task.
		 */
		uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
		xQueueReceive(queue_task_10ms, buf, portMAX_DELAY);

		uint64_t ts_start = bsp_timer_timestamp_u64_get();
		sanity.cnt_activation_task_10ms++;
		task_10ms();
		uint64_t ts_now = bsp_timer_timestamp_u64_get();
		TS__(task_10ms, ts_start, ts_now);
	}
}

static void configuration_update(void)
{
	uint64_t ts_start = bsp_timer_timestamp_u64_get();

	if ((global.ctrl.ctrl_enable == 0)
		&& (global.config.PWM_freq_Hz >= 1e3 && global.config.PWM_freq_Hz <= 100e3)) {
		Global_Data.av.pwm_frequency_hz = global.config.PWM_freq_Hz;
		Global_Data.av.isr_samplerate_s = (1.0f / Global_Data.av.pwm_frequency_hz);
		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_0_to_5,
								  Global_Data.av.pwm_frequency_hz);
		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_6_to_11,
								  Global_Data.av.pwm_frequency_hz);
	    // Currently not used
//		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_12_to_17,
//								  Global_Data.av.pwm_frequency_hz);
//		uz_PWM_SS_2L_set_PWM_freq(Global_Data.objects.pwm_d1_pin_18_to_23,
//								  Global_Data.av.pwm_frequency_hz);
	}

	if ((global.ctrl.ctrl_enable == 0)
		&& (global.config.deadtime_us >= 0 && global.config.deadtime_us <= 100)) {
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, 0);
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, 0);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, 0);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, 0);

		Global_Data.av.deadtime_us = global.config.deadtime_us;
		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, Global_Data.av.deadtime_us);
		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, Global_Data.av.deadtime_us);
//		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, Global_Data.av.deadtime_us);
//		uz_interlockDeadtime2L_set_deadtime_us(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, Global_Data.av.deadtime_us);

		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_0_to_5, 1);
		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_6_to_11, 1);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_12_to_17, 1);
//		uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1_pin_18_to_23, 1);
	}

	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	TS__(config_update, ts_start, ts_now);
}

//====================================================================
// Global functions
//====================================================================
void timer_irq_callback__(void)
{
	// Timer irq runs with 1 kHz
	sanity.cnt_activation_irq_1ms++;

	uint8_t buf[ACTIVATION_QUEUE_ITEM_SIZE];
	xQueueSendFromISR(queue_task_1ms, buf, NULL);
	static int div_cnt = 0;
	div_cnt++;
	if (div_cnt >= 10) {
		div_cnt = 0;
		xQueueSendFromISR(queue_task_10ms, buf, NULL);
	}

	// Call scheduler for a task switch
	portYIELD_FROM_ISR(pdTRUE);
}

void irq_fpga(void *data)
{
	uint64_t ts_start = bsp_timer_timestamp_u64_get();
	static uint64_t ts_last = 0;
	TS__(irq_rate, ts_last, ts_start);
	timing_us.irq_freq_kHz = (1 / timing_us.now.irq_rate * (float)1e3);
	ts_last = ts_start;

	//---------------------
	// Fast stuff
	sanity.cnt_activation_task_fast++;
	task_fast();

	//---------------------
	// Slow stuff
	static uint64_t ts_last_activation_1ms = 0;
	const uint64_t TICKS_1MS = (BSP_TIMER_TICKS_PER_SECOND / 1000);
	if ((ts_start - ts_last_activation_1ms) >= TICKS_1MS) {
		ts_last_activation_1ms = ts_start;
		task_slow();
	}

	//---------------------
	// Configuration changes
	if (global.config.config_update) {
		global.config.config_update = 0;
		configuration_update();
	}

	uint64_t ts_end = bsp_timer_timestamp_u64_get();
	TS__(irq_time, ts_start, ts_end);
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
	uz_axigpio_disable_pwm_and_power_electronics();

    Global_Data.objects.pwm_d1_pin_0_to_5 = initialize_pwm_2l_on_D1_pin_0_to_5();
    Global_Data.objects.pwm_d1_pin_6_to_11 = initialize_pwm_2l_on_D1_pin_6_to_11();
    Global_Data.objects.pwm_d1_pin_12_to_17 = initialize_pwm_2l_on_D1_pin_12_to_17();
    Global_Data.objects.pwm_d1_pin_18_to_23 = initialize_pwm_2l_on_D1_pin_18_to_23();
    Global_Data.objects.mux_axi = initialize_uz_mux_axi();
    // Currently not used
//    PWM_3L_Initialize(&Global_Data); // three-level modulator
    initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
    uz_axigpio_enable_datamover();

    // Set XCP stimuli variables to the currently active values.. so they are correctly viewed in CANape
    global.config.PWM_freq_Hz = Global_Data.av.pwm_frequency_hz;
    global.config.deadtime_us = Global_Data.av.deadtime_us;

	bsp_led_init();


	queue_task_1ms = xQueueGenericCreate(ACTIVATION_QUEUE_LEN, ACTIVATION_QUEUE_ITEM_SIZE, 0);
	xTaskCreate(task_background_1ms, "backgr1ms", BACKGROUND_TASK_STACK_SIZE,
			NULL, BACKGROUND_TASK_PRIO_1MS, NULL);
	queue_task_10ms = xQueueGenericCreate(ACTIVATION_QUEUE_LEN, ACTIVATION_QUEUE_ITEM_SIZE, 0);
	xTaskCreate(task_background_10ms, "backgr10ms", BACKGROUND_TASK_STACK_SIZE,
			NULL, BACKGROUND_TASK_PRIO_10MS, NULL);

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




