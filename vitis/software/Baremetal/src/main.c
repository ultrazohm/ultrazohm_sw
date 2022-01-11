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
#include "uz/uz_global_configuration.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "include/uz_adcLtc2311_ip_core_init.h"
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
// Initialize the global variables
int i_LifeCheck;

_Bool bNewControlMethodAvailable = false;
_Bool bInit = false;
DS_Data Global_Data;

static void uz_assertCallback(const char8 *file, s32 line)
{
    uz_printf("\r\nAssertion in file %s on line %d\r\n", file, line);
    uz_led_set_errorLED_on();
    uz_led_set_readyLED_off();
    uz_led_set_runningLED_off();
    ErrorHandling(&Global_Data);
}

#define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION 5000.0f
#define UZ_D5_MOTOR_POLE_PAIR_NUMBER 4.0f
#define UZ_ISR_FREQUENCY 10e3f
float uz_isr_frequency_hz=UZ_ISR_FREQUENCY;
float uz_isr_rate_s=1.0f/UZ_ISR_FREQUENCY;
float uz_isr_samplerate_s=(1.0f/UZ_ISR_FREQUENCY)* (Interrupt_ISR_freq_factor);



int main(void)
{
    int status = UZ_SUCCESS;
    Xil_AssertSetCallback((Xil_AssertCallback)uz_assertCallback);
    uz_printf("\r\n\r\n");
    uz_printf("Welcome to the UltraZohm\r\n");
    uz_printf("----------------------------------------\r\n");

    // Initialize the global "Global_Data" structure -> the values can be overwritten afterwards from the Java-GUI -> this must be the first INIT-function, because it is required subsequently!
    InitializeDataStructure(&Global_Data);
    uz_adcLtc2311_ip_core_init();
    Initialize_AXI_GPIO();
    uz_frontplane_button_and_led_init();

    uz_interlockDeadtime2L_handle deadtime_slotd1 = uz_interlockDeadtime2L_staticAllocator_slotD1();
    uz_interlockDeadtime2L_set_enable_output(deadtime_slotd1, true);
    initialize_pwm_2l_on_D1();
    PWM_3L_Initialize(&Global_Data); // three-level modulator
    initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);

    // Initialize Timer in order to Trigger the ISRs
    Initialize_Timer();
    uz_SystemTime_init();

    // Initialize the Soft-Oscilloscope ("JavaScope")
    JavaScope_initalize(&Global_Data);

    // Initialize the Interrupts
    Initialize_ISR();

    // Turn on AXI2TCM communication
    AXI2TCM_on();

    // Infinite loop
    while (1)
    {

        // poll the buttons
        Global_Data.dv.sw1 = uz_GetPushButtonEnableSystem();
        Global_Data.dv.sw2 = uz_GetPushButtonEnableControl();
        Global_Data.dv.sw3 = uz_GetPushButtonStop();
        // Set the system enable flag to false if SW1 is pressed
        if (Global_Data.dv.sw1 == true)
        {
            Global_Data.cw.enableSystem = true;
        }
        // Set the control enable flag to false if SW2 is pressed
        if (Global_Data.dv.sw2 == true)
        {
            Global_Data.cw.enableControl = true;
        }
#if (UZ_HARDWARE_VERSION > 2U) // in CarrierBoard_v2 there are no buttons, therefore SW_stop is always zero/false
        // Set the control enable and system enable flag to false if SW3 is pressed
        if (Global_Data.dv.sw3 == false)
        {
            Global_Data.cw.enableControl = false;
            Global_Data.cw.enableSystem = false;
        }
#endif
        if (Global_Data.cw.enableSystem == false)
        {
            turnPowerElectronicsOff(&Global_Data); // Switch power converter off
        }
        else if ((Global_Data.cw.enableSystem == true) && bInit == false)
        {                                                 // Call this function only once. If there was an error, "enableSystem " must be reseted!
            bInit = turnPowerElectronicsOn(&Global_Data); // Switch power converter on
        }

        if (Global_Data.cw.enableControl == true)
        {
            ControllerOn(&Global_Data); // Switch controller on
        }
        else
        {
            ControllerOff(&Global_Data); // Switch controller off
        }

        i_LifeCheck++; // LiveCheck for the main while-1 loop
        if (i_LifeCheck > 2500)
        {
            i_LifeCheck = 0;
        }
    }
    return (status);
}

//==============================================================================================================================================================
int turnPowerElectronicsOff(DS_Data *data)
{
    bInit = false;
    data->cw.enableControl = false;             // Switch controller off
    uz_axigpio_disable_pwm_and_power_electronics();
    return (0);
}

//==============================================================================================================================================================
int turnPowerElectronicsOn(DS_Data *data)
{
    uz_axigpio_enable_pwm_and_power_electronics();
    bInit = true;
    return (0);
}

//==============================================================================================================================================================
void ControllerOff(DS_Data *data)
{
    uz_led_set_runningLED_off();
}

//==============================================================================================================================================================
void ControllerOn(DS_Data *data)
{
    uz_led_set_runningLED_on();
}

//==============================================================================================================================================================
void ErrorHandling(DS_Data *data)
{

    ControllerOff(data);                // Switch controller off
    data->cw.enableControl = false;     // Switch controller off

    turnPowerElectronicsOff(data); // Switch power electronics off
    data->cw.enableSystem = false; // Switch power electronics off
}

//==============================================================================================================================================================
void ErrorReset(DS_Data *data)
{
    uz_led_set_errorLED_off();
}

//==============================================================================================================================================================
void AXI2TCM_on()
{
    uz_axigpio_enable_datamover();
}

//==============================================================================================================================================================
void InitializeDataStructure(DS_Data *data)
{
    // Control
    data->cw.ControlReference = CurrentControl;    // default because of Parameter ID
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
