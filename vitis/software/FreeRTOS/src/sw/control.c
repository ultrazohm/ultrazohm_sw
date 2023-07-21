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


global_t global;

extern volatile uint32_t fpga_irq_cnt;
volatile uint32_t fpga_irq_cnt = 0;

//====================================================================
// Functions
//====================================================================
void irq_fpga(void *data)
{
	fpga_irq_cnt++;


	// control_fast() goes here

	// XCP_event_fast() goes here

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




