/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

// Includes from own files
#include "main.h"

// Initialize the global variables
DS_Data Global_Data={
    .rasv={
        .halfBridge1DutyCycle=0.0f,
        .halfBridge2DutyCycle=0.0f,
        .halfBridge3DutyCycle=0.0f
    },
    .av.pwm_frequency_hz=UZ_PWM_FREQUENCY,
    .av.isr_samplerate_s= (1.0f / UZ_PWM_FREQUENCY) * (Interrupt_ISR_freq_factor),
    .aa={
        .A1={
            .cf.ADC_A1=10.0f,
            .cf.ADC_A2=10.0f,
            .cf.ADC_A3=10.0f,
            .cf.ADC_A4=10.0f,
            .cf.ADC_B5=10.0f,
            .cf.ADC_B6=10.0f,
            .cf.ADC_B7=10.0f,
            .cf.ADC_B8=10.0f
        },
        .A2={
            .cf.ADC_A1=10.0f,
            .cf.ADC_A2=10.0f,
            .cf.ADC_A3=10.0f,
            .cf.ADC_A4=10.0f,
            .cf.ADC_B5=10.0f,
            .cf.ADC_B6=10.0f,
            .cf.ADC_B7=10.0f,
            .cf.ADC_B8=10.0f
        },
        .A3={
            .cf.ADC_A1=10.0f,
            .cf.ADC_A2=10.0f,
            .cf.ADC_A3=10.0f,
            .cf.ADC_A4=10.0f,
            .cf.ADC_B5=10.0f,
            .cf.ADC_B6=10.0f,
            .cf.ADC_B7=10.0f,
            .cf.ADC_B8=10.0f
        }
    }
};

int main(void)
{
    uz_assert_configuration(); // This has to be the first line of code in main.c
    int status = UZ_SUCCESS;
    uz_printf("\r\n\r\n");
    uz_printf("Welcome to the UltraZohm\r\n");
    uz_printf("----------------------------------------\r\n");

    uz_adcLtc2311_ip_core_init();
    Global_Data.objects.deadtime_interlock_d1= uz_interlockDeadtime2L_staticAllocator_slotD1();
    uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1, true);
    Global_Data.objects.pwm_d1= initialize_pwm_2l_on_D1();
    PWM_3L_Initialize(&Global_Data); // three-level modulator
    initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);

    // Initialize Timer in order to Trigger the ISRs
    Initialize_Timer();
    uz_SystemTime_init();
    Initialize_AXI_GPIO();
    uz_frontplane_button_and_led_init();
    JavaScope_initalize(&Global_Data);
    uz_axigpio_enable_datamover();
    Initialize_ISR(); // Initialize the Interrupts and enable them - last line of code before infinite loop

    // Infinite loop
    while (1)
    {
        ultrazohm_state_machine_step();
    }
    return (status);
}
