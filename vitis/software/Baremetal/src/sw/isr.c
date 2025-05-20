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
#include <stdint.h>
#include <stdlib.h>
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
#include "xil_cache.h"
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

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();


// Define print function
// #define PRINTF print
#define PRINTF uz_printf

#ifndef XPAR_OPENCL_CLOC_VADD_KERNEL_0_BASEADDR
#define XPAR_OPENCL_CLOC_VADD_KERNEL_0_BASEADDR 0x90000000
#endif

#ifndef XPAR_XGPIO_0_BASEADDR
#define XPAR_XGPIO_0_BASEADDR 0x80100000
#endif

static void test_nn(void) {

	//PRINTF("test_nn() called\r\n");
    
	Xil_DCacheDisable();
	
	unsigned int length = 1024;

	char* accel_base_adr = (char*) XPAR_OPENCL_CLOC_VADD_KERNEL_0_BASEADDR;
	char* gpio_base_adr  = (char*) XPAR_XGPIO_0_BASEADDR;
	int32_t* input_a     = (int32_t*) malloc(length * 4);
	int32_t* input_b     = (int32_t*) malloc(length * 4);
	int32_t* output      = (int32_t*) malloc(length * 4);

	if(input_a == NULL || input_b == NULL || output == NULL) {
		// Ensure HEAP is of sufficient size
		//PRINTF("test_nn() malloc failed\r\n");
		return;        
	}


	// Initialization loop
	for (unsigned int i = 0 ; i < length ; i++){
		input_a[i] = i;
		input_b[i] = i;
		output[i]  = 0;
	}

	uint32_t pasid          = 0;
	uint16_t kp_wg_size_x   = length;
	uint16_t kp_wg_size_y   = 1;
	uint16_t kp_wg_size_z   = 1;
	uint32_t kp_grid_size_x = length;
	uint32_t kp_grid_size_y = 1;
	uint32_t kp_grid_size_z = 1;
	uint32_t kernel_meta    = 0x31;

	// write kernel configuration
	// pack kernel arguemts to use less AXI transfers
	uint64_t transfer1 = ((uint64_t)kp_wg_size_z   << 48) | ((uint64_t)kp_wg_size_y << 32) | ((uint64_t)kp_wg_size_x << 16) | kernel_meta;
	uint64_t transfer2 = ((uint64_t)kp_grid_size_y << 32) | kp_grid_size_x;
	uint64_t transfer3 = ((uint64_t)pasid          << 32) | kp_grid_size_z;

	uint64_t arg_transfer1 = (uint64_t) input_a;
	uint64_t arg_transfer2 = (uint64_t) input_b;
	uint64_t arg_transfer3 = (uint64_t) output;

	*((volatile uint64_t*)(accel_base_adr+0x0))  = transfer1;
	*((volatile uint64_t*)(accel_base_adr+0x8))  = transfer2;
	*((volatile uint64_t*)(accel_base_adr+0x10)) = transfer3;

	*((volatile uint64_t*)(accel_base_adr+0x20)) = 0; // Kernel Function
	*((volatile uint64_t*)(accel_base_adr+0x28)) = arg_transfer1;
	*((volatile uint64_t*)(accel_base_adr+0x30)) = arg_transfer2;
	*((volatile uint64_t*)(accel_base_adr+0x38)) = arg_transfer3;

	//Xil_DCacheFlush();
	
	//PRINTF("test_nn() Setting 'START' Flag\r\n");
	
	// Set START FLAG to HIGH
	*((volatile uint32_t*)(gpio_base_adr+0x8)) = 0x1;

	// Wait for kernel START FLAG acknowledgement
	while ( (*((volatile uint32_t*)(gpio_base_adr+0x0)) & 0x1) == 0) {
		// You may want to wait here with sleep
	}
	
	//PRINTF("test_nn() Clearing 'START' Flag\r\n");

	// ultrazohm_state_machine_set_userLED(true);
	// Clear START FLAG
	*((volatile uint32_t*)(gpio_base_adr+0x8)) = 0x0;

	// Wait until START FLAG is removed by kernel
	while (  (*((volatile uint32_t*)(gpio_base_adr+0x0)) & 0x1) != 0) {
		// You may want to wait here with sleep
	}
	
	// Now the kernel is running    
	//PRINTF("test_nn() wait for completion\r\n");


	// WAIT FOR COMPLETION

	// Wait for FINISHED SIGNAL 
	while ( (*((volatile uint64_t*)(gpio_base_adr+0x0)) & 0x2) == 0) {
		// You may want to wait here with sleep
	}

	// Send FINISHED ACK
	*((volatile uint64_t*)(gpio_base_adr+0x8)) = 0x2;
	
	//PRINTF("test_nn() wait for finished gone\r\n");

	// Wait until finished is gone
	while (  (*((volatile uint64_t*)(gpio_base_adr+0x0)) & 0x2) != 0) {
		// You may want to wait here with sleep
	}

	// Clear finished ACK
	*((volatile uint64_t*)(gpio_base_adr+0x8)) = 0x0;


	// Check for results
	//PRINTF("test_nn() check results\r\n");
	for(int32_t i = 0 ; i < length ; i++) {
		if(output[i] != i*2) {
			// ultrazohm_state_machine_set_error(true);
			//PRINTF("result is incorrect\r\n");
			break;
		}
	}

    // if (success == 1) {
	// 	ultrazohm_state_machine_set_userLED(true);
	// }

	free(input_a);
	free(input_b);
	free(output);

	Xil_DCacheEnable();
}

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	test_nn();
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
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
