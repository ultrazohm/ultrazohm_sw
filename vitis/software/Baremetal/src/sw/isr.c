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

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

// External Declares FOC
extern uz_SpeedControl_t* SC_instance;
extern uz_SetPoint_t* SP_instance;
extern uz_CurrentControl_t* CC_instance;
extern struct uz_PMSM_t config_PMSM;

// Declare Variables FOC
struct uz_3ph_abc_t v_abc_Volts = {0};
struct uz_3ph_dq_t v_dq_Volts = {0};
struct uz_3ph_dq_t v_dq_ref_Volts = {0};
struct uz_3ph_abc_t i_abc_Amps = {0};
struct uz_3ph_dq_t i_dq_Amps = {0};
struct uz_3ph_dq_t i_dq_ref_Amps = {0};
float v_DC_Volts = 12.0f;
float i_DC_Amps = 0.0f;
float n_ref_rpm = 0.0f;
float M_ref_Nm = 0.0f;
float omega_m_rad_per_sec = 0.0f;
float omega_el_rad_per_sec = 0.0f;
float theta_el_rad = 0.0f;
float theta_el_offset = 1.4f;
struct uz_DutyCycle_t output = {0};
float Kp_speed = 0.01f;
float Ki_speed = 0.1f;
float Kp_id = 0.3f;
float Ki_id = 230.0f;
float Kp_iq = 0.5f;
float Ki_iq = 230.0f;

// External Declares Wavegen
extern uz_wavegen_chirp* chirp_instance;

// Declare Variables Wavegen
bool enable_noise=false;
float noise_amplitude=0.0f;
float

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

    // Read Measurement from ADCs and Encoder
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    // Read Measurement Data of Inverter Card
    v_abc_Volts.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    v_abc_Volts.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    v_abc_Volts.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    v_DC_Volts 	  = Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps.a  = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    i_abc_Amps.b  = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    i_abc_Amps.c  = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    i_DC_Amps    = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Get Current State
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
      // enable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    } else {
      // disable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    }

    // Calculation of Signals for FOC
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed_filtered*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec = omega_m_rad_per_sec*config_PMSM.polePairs;
    theta_el_rad = Global_Data.av.theta_elec-theta_el_offset;
    i_dq_Amps = uz_transformation_3ph_abc_to_dq(i_abc_Amps, theta_el_rad);

    // Enable Control
    if (current_state==control_state)
    {
    	// Noise and Chirp Generation
    	if(enable_noise){
    		i_dq_ref_Amps.q=0.0f;
    		//i_dq_ref_Amps.d=uz_wavegen_white_noise(noise_amplitude);
    		//i_dq_ref_Amps.d=uz_wavegen_sine(5.0f, noise_amplitude);
    		i_dq_ref_Amps.q=uz_wavegen_chirp_sample(chirp_instance, sampling_time);
    	}else{

    	}

    	// Field Oriented Control
    	//M_ref_Nm = uz_SpeedControl_sample(SC_instance, omega_m_rad_per_sec, n_ref_rpm);										// Calculate Reference Torque
    	//i_dq_ref_Amps = uz_SetPoint_sample(SP_instance, omega_m_rad_per_sec, M_ref_Nm, v_DC_Volts, i_dq_Amps);				// Calculate Reference Currents
    	v_dq_ref_Volts = uz_CurrentControl_sample(CC_instance, i_dq_ref_Amps, i_dq_Amps, v_DC_Volts, omega_el_rad_per_sec);		// Calculate Reference Voltages
    	output = uz_Space_Vector_Modulation(v_dq_ref_Volts, v_DC_Volts, theta_el_rad);											// Calculate Duty Cycles
    	Global_Data.rasv.halfBridge1DutyCycle = output.DutyCycle_A;																// Set Duty Cycle A
    	Global_Data.rasv.halfBridge2DutyCycle = output.DutyCycle_B;																// Set Duty Cycle B
    	Global_Data.rasv.halfBridge3DutyCycle = output.DutyCycle_C;																// Set Duty Cycle C
    }
    else
	{
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		uz_SpeedControl_reset(SC_instance);
		uz_CurrentControl_reset(CC_instance);
	}

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    //PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);

    // Change Variables during Runtime
    uz_SpeedControl_set_Kp(SC_instance, Kp_speed);
    uz_SpeedControl_set_Ki(SC_instance, Ki_speed);
    uz_CurrentControl_set_Kp_id(CC_instance, Kp_id);
    uz_CurrentControl_set_Kp_iq(CC_instance, Kp_iq);
    uz_CurrentControl_set_Ki_id(CC_instance, Ki_id);
    uz_CurrentControl_set_Ki_iq(CC_instance, Ki_iq);


    // Update JavaScope
    JavaScope_update(&Global_Data);

    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
       ultrazohm_state_machine_set_error(true);
    }

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
