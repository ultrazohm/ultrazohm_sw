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
#include "uz_platform_state_machine.h"
#include "uz/uz_global_configuration.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "include/uz_adcLtc2311_ip_core_init.h"
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

#include "uz_assertion_configuration.h"
// Initialize the global variables
DS_Data Global_Data;

#define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION 5000.0f
#define UZ_D5_MOTOR_POLE_PAIR_NUMBER 4.0f
#define UZ_ISR_FREQUENCY 10e3f
float uz_isr_frequency_hz = UZ_ISR_FREQUENCY;
float uz_isr_rate_s = 1.0f / UZ_ISR_FREQUENCY;
float uz_isr_samplerate_s = (1.0f / UZ_ISR_FREQUENCY) * (Interrupt_ISR_freq_factor);

int main(void)
{
    uz_assert_configuration(); // This has to be the first line of code in main.c
    int status = UZ_SUCCESS;
    uz_printf("\r\n\r\n");
    uz_printf("Welcome to the UltraZohm\r\n");
    uz_printf("----------------------------------------\r\n");

    // Initialize the global "Global_Data" structure -> the values can be overwritten afterwards from the Java-GUI -> this must be the first INIT-function, because it is required subsequently!
    InitializeDataStructure(&Global_Data);
    uz_adcLtc2311_ip_core_init();

    uz_interlockDeadtime2L_handle deadtime_slotd1 = uz_interlockDeadtime2L_staticAllocator_slotD1();
    uz_interlockDeadtime2L_set_enable_output(deadtime_slotd1, true);
    initialize_pwm_2l_on_D1();
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
        ultrazohm_state_machine();
    }
    return (status);
}

//==============================================================================================================================================================
void InitializeDataStructure(DS_Data *data)
{
    // Control
    data->cw.ControlReference = CurrentControl; // default because of Parameter ID
    // Default control method

    data->rasv.halfBridge1DutyCycle = 0.0;
    data->rasv.halfBridge2DutyCycle = 0.0;
    data->rasv.halfBridge3DutyCycle = 0.0;

    // Initialize ADC conversion factors
    //  Conversion Factor of 10, because the full input range of the ADC is +-5V = 10V range
    data->aa.A1.cf.ADC_A1 = 10;
    data->aa.A1.cf.ADC_A2 = 10;
    data->aa.A1.cf.ADC_A3 = 10;
    data->aa.A1.cf.ADC_A4 = 10;
    data->aa.A1.cf.ADC_B5 = 10;
    data->aa.A1.cf.ADC_B6 = 10;
    data->aa.A1.cf.ADC_B7 = 10;
    data->aa.A1.cf.ADC_B8 = 10;

    data->aa.A2.cf.ADC_A1 = 10;
    data->aa.A2.cf.ADC_A2 = 10;
    data->aa.A2.cf.ADC_A3 = 10;
    data->aa.A2.cf.ADC_A4 = 10;
    data->aa.A2.cf.ADC_B5 = 10;
    data->aa.A2.cf.ADC_B6 = 10;
    data->aa.A2.cf.ADC_B7 = 10;
    data->aa.A2.cf.ADC_B8 = 10;

    data->aa.A3.cf.ADC_A1 = 10;
    data->aa.A3.cf.ADC_A2 = 10;
    data->aa.A3.cf.ADC_A3 = 10;
    data->aa.A3.cf.ADC_A4 = 10;
    data->aa.A3.cf.ADC_B5 = 10;
    data->aa.A3.cf.ADC_B6 = 10;
    data->aa.A3.cf.ADC_B7 = 10;
    data->aa.A3.cf.ADC_B8 = 10;
}
