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

enum init_chain
{
    init_assertions = 0,
    init_gpios,
    init_software,
    init_ip_cores,
    print_msg,
    init_interrupts,
    infinite_loop
};
enum init_chain initialization_chain = init_assertions;



#include "xsysmon.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xil_printf.h"

#define SYSMON_DEVICE_ID 	XPAR_SYSMON_0_DEVICE_ID

int SysMonPolledExample(u16 SysMonDeviceId, int *Temp);
static XSysMon SysMonInst;      /* System Monitor driver instance */
int Status;
int Temp;
int main(void)
{



	/*
	 * Run the SysMonitor polled example, specify the Device ID that is
	 * generated in xparameters.h .
	 */



    int status = UZ_SUCCESS;
    while (1)
    {
        switch (initialization_chain)
        {
        case init_assertions:
            uz_assert_configuration(); // This has to be the first line of code in main.c
            initialization_chain = init_gpios;
            break;
        case init_gpios:
            Initialize_AXI_GPIO();               // This has to be the second line of code in main.c since the assertion callback uses the AXI_GPIO to disable the system
            uz_frontplane_button_and_led_init(); // This has to be the third line of code since the assertion callback uses the LEDs to indicate an error
            initialization_chain = init_software;
            break;
        case init_software:
            Initialize_Timer();
            uz_SystemTime_init();
            JavaScope_initalize(&Global_Data);
            initialization_chain = init_ip_cores;
            break;
        case init_ip_cores:
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
            initialization_chain = print_msg;
            break;
        case print_msg:
            uz_printf("\r\n\r\n");
            uz_printf("Welcome to the UltraZohm\r\n");
            uz_printf("----------------------------------------\r\n");
            while(1){
            	Status = SysMonPolledExample(SYSMON_DEVICE_ID, &Temp);
            }
            initialization_chain = init_interrupts;
            break;
        case init_interrupts:
            uz_axigpio_enable_datamover();
            Initialize_ISR(); // Initialize the Interrupts and enable them - last line of code before infinite loop
            initialization_chain = infinite_loop;
            break;
        case infinite_loop:
            ultrazohm_state_machine_step();
            break;
        default:
            break;
        }
    }
    return (status);
}


int SysMonPolledExample(u16 SysMonDeviceId, int *Temp)
{
	int Status;
	volatile u32 Value;
	XSysMon_Config *ConfigPtr;
	u16 TempData;
	u16 VccauxData;
	XSysMon *SysMonInstPtr = &SysMonInst;


	/*
	 * Initialize the SysMon driver.
	 */
	ConfigPtr = XSysMon_LookupConfig(SysMonDeviceId);
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}
	XSysMon_CfgInitialize(SysMonInstPtr, ConfigPtr,
				ConfigPtr->BaseAddress);

	/*
	 * Self Test the System Monitor/ADC device
	 */
	Status = XSysMon_SelfTest(SysMonInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Disable the Channel Sequencer before configuring the Sequence
	 * registers.
	 */
	XSysMon_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_SAFE);


	/*
	 * Setup the Averaging to be done for the channels in the
	 * Configuration 0 register as 16 samples:
	 */
	XSysMon_SetAvg(SysMonInstPtr, XSM_AVG_16_SAMPLES);

	/*
	 * Setup the Sequence register for 1st Auxiliary channel
	 * Setting is:
	 *	- Add acquisition time by 6 ADCCLK cycles.
	 *	- Bipolar Mode
	 *
	 * Setup the Sequence register for 16th Auxiliary channel
	 * Setting is:
	 *	- Add acquisition time by 6 ADCCLK cycles.
	 *	- Unipolar Mode
	 */
	Status = XSysMon_SetSeqInputMode(SysMonInstPtr, XSM_SEQ_CH_AUX00);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XSysMon_SetSeqAcqTime(SysMonInstPtr, XSM_SEQ_CH_AUX15 |
						XSM_SEQ_CH_AUX00);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Enable the averaging on the following channels in the Sequencer
	 * registers:
	 * 	- On-chip Temperature
	 * 	- On-chip VCCAUX supply sensor
	 * 	- 1st Auxiliary Channel
	 * 	- 16th Auxiliary Channel
	 */
	Status =  XSysMon_SetSeqAvgEnables(SysMonInstPtr, XSM_SEQ_CH_TEMP |
						XSM_SEQ_CH_VCCAUX |
						XSM_SEQ_CH_AUX00 |
						XSM_SEQ_CH_AUX15);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the following channels in the Sequencer registers:
	 * 	- On-chip Temperature
	 * 	- On-chip VCCAUX supply sensor
	 * 	- 1st Auxiliary Channel
	 * 	- 16th Auxiliary Channel
	 */
	Status =  XSysMon_SetSeqChEnables(SysMonInstPtr, XSM_SEQ_CH_TEMP |
						XSM_SEQ_CH_VCCAUX |
						XSM_SEQ_CH_AUX00 |
						XSM_SEQ_CH_AUX15);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Set the ADCCLK frequency equal to 1/32 of System clock for the System
	 * Monitor/ADC in the Configuration Register 2.
	 */
	XSysMon_SetAdcClkDivisor(SysMonInstPtr, 32);

	/*
	 * Enable the Channel Sequencer in continuous sequencer cycling mode.
	 */
	XSysMon_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_CONTINPASS);

	/*
	 * Wait till the End of Sequence occurs
	 */
	XSysMon_GetStatus(SysMonInstPtr); /* Clear the old status */
	while ((XSysMon_GetStatus(SysMonInstPtr) & XSM_SR_EOS_MASK) !=
			XSM_SR_EOS_MASK);

	/*
	 * Disable all the alarms in the Configuration Register 1
	 */
	XSysMon_SetAlarmEnables(SysMonInstPtr, 0x0);


	/*
	 * Read the ADC converted Data from the data registers for on-chip
	 * temperature and on-chip VCCAUX
	 */
	TempData = XSysMon_GetAdcData(SysMonInstPtr, XSM_CH_TEMP);
	VccauxData = XSysMon_GetAdcData(SysMonInstPtr, XSM_CH_VCCAUX);

	/*
	 * Convert the ADC data into temperature
	 */
	*Temp = XSysMon_RawToTemperature(TempData);

	/*
	 * Set up Alarm threshold registers for
	 * On-chip Temperature High limit
	 * On-chip Temperature Low limit
	 * VCCAUX High limit
	 * VCCAUX Low limit
	 */
	XSysMon_SetAlarmThreshold(SysMonInstPtr, XSM_ATR_TEMP_UPPER,
						TempData - 0x007F);
	XSysMon_SetAlarmThreshold(SysMonInstPtr, XSM_ATR_TEMP_LOWER,
						TempData - 0x007F);
	XSysMon_SetAlarmThreshold(SysMonInstPtr, XSM_ATR_VCCAUX_UPPER,
						VccauxData - 0x007F);
	XSysMon_SetAlarmThreshold(SysMonInstPtr, XSM_ATR_VCCAUX_LOWER,
						VccauxData + 0x007F);

	/*
	 * Enable Alarm 0 for on-chip temperature and Alarm 2 for on-chip
	 * VCCAUX in the Configuration Register 1.
	 */
	XSysMon_SetAlarmEnables(SysMonInstPtr, (XSM_CFR1_ALM_VCCAUX_MASK |
						XSM_CFR1_ALM_TEMP_MASK));

	/*
	 * Enable the Channel Sequencer in continuous cycling mode.
	 */
	XSysMon_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_CONTINPASS);

	/*
	 * Read the current value of on-chip Temperature.
	 */
	Value = XSysMon_GetAdcData(SysMonInstPtr, XSM_CH_TEMP);

	/*
	 * Read the Maximum value of on-chip Temperature.
	 */
	Value = XSysMon_GetMinMaxMeasurement(SysMonInstPtr, XSM_MAX_TEMP);

	/*
	 * Read the Minimum value of on-chip Temperature.
	 */
	Value = XSysMon_GetMinMaxMeasurement(SysMonInstPtr, XSM_MIN_TEMP);

	/*
	 * Check if alarm for on-chip temperature is set.
	 */
	Value = XSysMon_GetAlarmOutputStatus(SysMonInstPtr) & XSM_AOR_TEMP_MASK;
	if (Value) {
		/*
		 * Alarm for on-chip temperature is set.
		 * The required processing should be put here.
		 */
	}

	/*
	 * Read the current value of on-chip VCCAUX.
	 */
	Value = XSysMon_GetAdcData(SysMonInstPtr, XSM_CH_VCCAUX);

	/*
	 * Read the Maximum value of on-chip VCCAUX.
	 */
	Value = XSysMon_GetMinMaxMeasurement(SysMonInstPtr, XSM_MAX_VCCAUX);

	/*
	 * Read the Minimum value of on-chip VCCAUX.
	 */
	Value = XSysMon_GetMinMaxMeasurement(SysMonInstPtr, XSM_MIN_VCCAUX);

	/*
	 * Check if alarm for on-chip VCCAUX is set.
	 */
	Value = XSysMon_GetAlarmOutputStatus(SysMonInstPtr) &
			XSM_AOR_VCCAUX_MASK;
	if (Value) {
		/*
		 * Alarm for on-chip VCCAUX is set.
		 * The required processing should be put here.
		 */
	}

	return XST_SUCCESS;
}
