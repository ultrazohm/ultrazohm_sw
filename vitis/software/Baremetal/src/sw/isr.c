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

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

#define PHASE_CURRENT_CONV_U 		1000/11.211;
#define PHASE_CURRENT_CONV_V 		1000/11.211;
#define PHASE_CURRENT_CONV_W 		1000/11.211;
#define PHASE_CURRENT_OFFSET_VOLT 	2.5

#define DC_LINK_VOLT_CONV 			1/0.0546		// DC-Voltage 0...5 V -> 0...91.5 V
#define PHASE_VOLT_CONV_U 			1/0.0546		// Voltage DC_GND to Phase U
#define PHASE_VOLT_CONV_V 			1/0.0546
#define PHASE_VOLT_CONV_W 			1/0.0546
#define MOSFET_TEMP_CONV_U 			1

#define MAX_CURRENT_ASSERTION 		300.0f
#define MAX_SPEED_ASSERTION			500.0f
#define MAX_TEMP_ASSERTION			80.0f

bool SKAI_nERROUT = 0U;			// Start in error-mode
bool flg_reset_SKAI = 0U;
platform_state_t last_state;
platform_state_t current_state;
int reset_counter=0;

// Variables for Current Control and Speed Control
/*
struct uz_3ph_abc_t measurement_current = {.a = 0.0f, .b = 0.0f, .c = 0.0f};
struct uz_3ph_abc_t measurement_voltage = {.a = 0.0f, .b = 0.0f, .c = 0.0f};

struct uz_3ph_dq_t dq_measurement_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_measurement_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

struct uz_3ph_dq_t dq_decoup_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};


struct uz_DutyCycle_t output = {
		.DutyCycle_A = 0.0f,
		.DutyCycle_B = 0.0f,
		.DutyCycle_C = 0.0f,
};
*/


//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    //update_speed_and_position_of_encoder_on_D5(&Global_Data);

    Global_Data.av.I_U = (Global_Data.aa.A1.me.ADC_A4 - 0.075f) * PHASE_CURRENT_CONV_U;
    Global_Data.av.I_V = (Global_Data.aa.A1.me.ADC_A3 - 0.155f) * PHASE_CURRENT_CONV_V;
    Global_Data.av.I_W = (Global_Data.aa.A1.me.ADC_A2 - 0.02f) * PHASE_CURRENT_CONV_W;

    Global_Data.av.U_ZK = Global_Data.aa.A1.me.ADC_A1 * DC_LINK_VOLT_CONV;
    Global_Data.av.U_U = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_U;
    Global_Data.av.U_V = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_V;
    Global_Data.av.U_W = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_W;

    Global_Data.av.temperature = Global_Data.aa.A1.me.ADC_B5 * MOSFET_TEMP_CONV_U;

    // Assertion check
    if (fabs(Global_Data.av.I_U) >= MAX_CURRENT_ASSERTION | fabs(Global_Data.av.I_V) >= MAX_CURRENT_ASSERTION | fabs(Global_Data.av.I_W) >= MAX_CURRENT_ASSERTION | fabs(Global_Data.av.mechanicalRotorSpeed) >= MAX_SPEED_ASSERTION | fabs(Global_Data.av.temperature) >= MAX_TEMP_ASSERTION){
    	// Assertion to Stop Machine if max. Current or max. Speed
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	ultrazohm_state_machine_set_stop(true);
    	// Set reset-gpio to zero
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 0U);
    }

    SKAI_nERROUT = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.input_gpio, 0);

    last_state = current_state;
    current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	//uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    	//uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
        // Start: Control algorithm - only if ultrazohm is in control state
    	if(current_state != last_state){
    		// First step in control-loop
    		flg_reset_SKAI = 1U;
    		reset_counter = 0;
    		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	}
    	if (flg_reset_SKAI){
    		// Check if control loop is enabled for one period
    		if(reset_counter > 0){
    			uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 1U);
    			if (SKAI_nERROUT == 1U){
    				flg_reset_SKAI = 0;
    				uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    			}
    		}
    		reset_counter++;
    	} else{
    		// Begin of control algorithm


    	    // Set Dutycycle
    	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    	}
    } else{
    	// Jumped out of control state --> Reset has to be low for 1 ms
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 0U);
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    }


    Global_Data.rasv.SKAI_nERROUT = SKAI_nERROUT;
    Global_Data.rasv.flg_reset_SKAI = flg_reset_SKAI;
    Global_Data.rasv.SKAI_reset_counter = reset_counter;

    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
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
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
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
