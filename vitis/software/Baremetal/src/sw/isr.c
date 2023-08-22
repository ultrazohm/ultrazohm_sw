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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../include/testbench.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_signals/uz_signals.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// software limits
#define MAX_PHASE_CURRENT_AMP  10.0f
#define MAX_DC_VOLT 400.0f
#define MAX_SPEED_RPM 1000.0f
#define MAX_TEMP_DEG 90.0f
#define NEUTRAL_CFG 3U //1U: 1N, 3U: 3N

// modulation
#include "../uz/uz_spwm/uz_spwm.h"
struct uz_DutyCycle_3x3ph_t duty_cycle = {0};

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

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Actual value/////////////////////////////
////////////////////////////////////////////////////////////////////////////
    // read speed and angle
    uz_resolver_read_and_adapt_direction(&Global_Data);
    // actual values reading functions
    uz_PWM_duty_freq_detection(&Global_Data);
    uz_TempCard_Measurement(&Global_Data);
    Global_Data.av.currents_abc = uz_ADC_phase_currents(&Global_Data.aa);
    Global_Data.av.voltages_abc = uz_ADC_phase_voltages(&Global_Data.aa);
    uz_ADC_dc_values(&Global_Data);
    uz_ADC_torque(&Global_Data);
    uz_calc_phase_voltage(&Global_Data, NEUTRAL_CFG);
    // transformations
    uz_transformations(Global_Data.av.currents_abc, &Global_Data.av.full_currents_dq, &Global_Data.av.currents_dq, &Global_Data.av.currents_XY1, &Global_Data.av.currents_XY2, &Global_Data.av.currents_XY3, Global_Data.av.rotational_position.position_el_2pi);
    Global_Data.av.full_voltages_dq = uz_transformation_9ph_abc_to_dq(Global_Data.av.voltages_abc, Global_Data.av.rotational_position.position_el_2pi);
	Global_Data.av.currents_alphabeta = uz_transformation_9ph_abc_to_alphabeta(Global_Data.av.voltages_abc);

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Limits///////////////////////////////////
////////////////////////////////////////////////////////////////////////////
	// check current limit
	if(fabs(Global_Data.av.currents_abc.a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.currents_abc.a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c2) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.currents_abc.a3) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b3) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c3) > MAX_PHASE_CURRENT_AMP) {
		uz_limit_exceed(&Global_Data);
	}
	// check DC Bus
	if(fabs(Global_Data.av.U_ZK1) > MAX_DC_VOLT || fabs(Global_Data.av.U_ZK2) > MAX_DC_VOLT || fabs(Global_Data.av.U_ZK3) > MAX_DC_VOLT) {
		uz_limit_exceed(&Global_Data);
	}
	// check Speed
	if(fabs(Global_Data.av.rotational_position.n_mech_rpm) > MAX_SPEED_RPM) {
		uz_limit_exceed(&Global_Data);
	}
	// check inverter temp
	if(fabs(Global_Data.av.temperature_inv_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temperature_inv_2) > MAX_TEMP_DEG || fabs(Global_Data.av.temperature_inv_3) > MAX_TEMP_DEG) {
		uz_limit_exceed(&Global_Data);
	}


////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Control State////////////////////////////
////////////////////////////////////////////////////////////////////////////
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	// controller here

    }else{
		// set Duty Cycles zero when UZ is not running or not active
		if(current_state!=running_state){
			uz_set_DC_zero(&Global_Data);
		}
	}
////////////////////////////////////////////////////////////////////////////
///////////////////////////////////PWM set//////////////////////////////////
////////////////////////////////////////////////////////////////////////////
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
