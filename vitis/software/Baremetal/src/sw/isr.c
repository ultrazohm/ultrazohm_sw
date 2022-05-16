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

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
extern float voltage;
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
#include "../include/test_spi.h"
extern XSpi  SpiInstance;	 /* The instance of the SPI device */
float test_frequency=50.0f;
float voltage_times_two=0.0f;
float amp=2.3f;

#include "xparameters.h"

#define  IPCore_Reset_uz_dac         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_dac        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_dac     0x8  //contains unique IP timestamp (yymmddHHMM): 2205161445
#define  dac_data_1_Data_uz_dac      0x100  //data register for Inport dac_data_1
#define  trigger_write_Data_uz_dac   0x104  //data register for Inport trigger_write
#define  dac_data_2_Data_uz_dac      0x108  //data register for Inport dac_data_2
#define  dac_data_3_Data_uz_dac      0x10C  //data register for Inport dac_data_3
#define  dac_data_4_Data_uz_dac      0x110  //data register for Inport dac_data_4
#define  dac_data_5_Data_uz_dac      0x114  //data register for Inport dac_data_5
#define  dac_data_6_Data_uz_dac      0x118  //data register for Inport dac_data_6
#define  dac_data_7_Data_uz_dac      0x11C  //data register for Inport dac_data_7
#define  dac_data_8_Data_uz_dac      0x120  //data register for Inport dac_data_8

float dac_input[8]={-4, -3, -2, -1, 1, 2, 3, 4};

static int32_t test(float input);



void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
   // update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    }
	//while(1){
    //voltage=uz_wavegen_sawtooth(5.0f,test_frequency)-2.5f;
    //voltage=uz_wavegen_sine(2.2f, test_frequency);
    dac_input[0]=uz_wavegen_triangle_with_offset(amp, test_frequency , (-1.0f*amp)/2.0f);
    dac_input[1]=uz_wavegen_sine(amp,30.0f);
    dac_input[2]=uz_wavegen_sawtooth(amp, 55.0f);
    dac_input[3]=uz_wavegen_pulse(amp,35.0f,0.3f);

    dac_input[4]=uz_wavegen_sine(0.3f,60.0f); //uz_wavegen_triangle_with_offset(0.5f*amp, 20.f*test_frequency , (-1.0f*amp)/2.0f);
    dac_input[5]=uz_wavegen_sine(0.1f,60.0f);
    dac_input[6]=uz_wavegen_sawtooth(0.5f*amp, 20.0f);
    dac_input[7]=uz_wavegen_pulse(0.5f*amp,55.0f,0.6f);


    voltage_times_two=voltage*2.0f;

		start_trans(&SpiInstance);

    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_1_Data_uz_dac, test( dac_input[0]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_2_Data_uz_dac, test( dac_input[1]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_3_Data_uz_dac, test( dac_input[2]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_4_Data_uz_dac, test( dac_input[3]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_5_Data_uz_dac, test( dac_input[4]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_6_Data_uz_dac, test( dac_input[5]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_7_Data_uz_dac, test( dac_input[6]) );
    	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_8_Data_uz_dac, test( dac_input[7]) );
    //	uz_axi_write_int32(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+dac_data_2_Data_uz_dac, calcualte_dac_voltage( dac_input[1]) );
    	uz_axi_write_bool(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+trigger_write_Data_uz_dac, true);
    	uz_axi_write_bool(XPAR_UZ_USER_UZ_DAC_0_BASEADDR+trigger_write_Data_uz_dac, false);

	//}
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    // Set duty cycles for three-level modulator
    //PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
     //                   Global_Data.rasv.halfBridge2DutyCycle,
      //                  Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}


static int32_t test(float input){
	int32_t voltage_set_point=((input/2.5f)*32768)+32768;
	return voltage_set_point;
}


//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
//    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
//    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
//    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //uz_mux_axi_enable(Global_Data.objects.mux_axi);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TIMER_LOAD_VALUE" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "Timer_Interrupt" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer()
{

    int Status;

    // SETUP THE TIMER 1 for Interrupts
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_UZ_SYSTEM_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;
    // XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
    XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
    XTmrCtr_Reset(&Timer_Interrupt, 0);
    XTmrCtr_Start(&Timer_Interrupt, 0);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Timer_Interrupt_InstancePtr)
{
    XScuGic_Config *IntcConfig;
    int status;

    // Interrupt controller initialization
    IntcConfig = XScuGic_LookupConfig(DeviceId);
    status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IntcConfig_IPI;
    int status;

    // Interrupt controller configuration
    IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};
