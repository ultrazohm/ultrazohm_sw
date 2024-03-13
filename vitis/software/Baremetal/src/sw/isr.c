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
#include "../uz/uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

//Define input and output of the IP-Core///////////////////////////////
extern uz_pmsmModel_t *pmsm;
extern struct uz_PMSM_t config_PMSM;
extern uz_encoder_offset_estimation_t* encoder_offset_obj;
extern uz_CurrentControl_t* CurrentControl_instance;
uz_3ph_dq_t reference_currents_Amp = {0};
uz_3ph_dq_t measured_currents_Amp = {0};
uz_3ph_dq_t CurrentControl_output_Volts = {0};
uz_3ph_dq_t setpoint_current = {0};
float omega_el_rad_per_sec = 0.0f; // electrical rotational speed in red/sec
struct uz_pmsmModel_inputs_t pmsm_inputs={
   .omega_mech_1_s=0.0f,
   .v_d_V=0.0f,
   .v_q_V=0.0f,
   .load_torque=0.0f
 };
struct uz_pmsmModel_outputs_t pmsm_outputs={
   .i_d_A=0.0f,
   .i_q_A=0.0f,
   .torque_Nm=0.0f,
   .omega_mech_1_s=0.0f
 };

struct uz_3ph_dq_t i_actual_Ampere = {0};
struct uz_3ph_dq_t i_reference_Ampere = {0};
struct uz_DutyCycle_t output = {0};
 ///////////////////////////////////////////////////////////////////////
 struct uz_3ph_abc_t v_abc_Volts = {0};
 struct uz_3ph_dq_t v_dq_measured_Volts = {0};
 struct uz_3ph_dq_t v_dq_ref_Volts = {0};
 struct uz_3ph_abc_t i_abc_Amps = {0};
 struct uz_3ph_dq_t i_dq_measured_Amps = {0};
 struct uz_3ph_dq_t i_dq_ref_Amps = {0};
 struct uz_encoder_offset_estimation_status status;
 struct uz_3ph_abc_t ref_voltage_3ph_abc = {0};
 float v_DC_Volts = 0.0f;
 float i_DC_Amps = 0.0f;
 float theta_el_rad = 0.0f; //electrical rotor angle in rad
 float theta_el_offset = 0.0f;
 float omega_m_rad_per_sec = 0.0f;
 float n_ref_rpm = 0.0f;
 float M_ref_Nm = 0.0f;
 float theta;




 ///////////////////////////////////////////////////////////////////////

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
    // Read Measurment from ADCs and Encoder
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    // Read Measurement Data of Inverter Card/////////////////////////////////////////////////////////////////////
    v_abc_Volts.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    v_abc_Volts.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    v_abc_Volts.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    v_DC_Volts 	  = Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps.a  = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    i_abc_Amps.b  = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    i_abc_Amps.c  = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    i_DC_Amps    = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d3 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d3);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Get current state
        platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware///////////////////////////////////////////////////////////////////////////
    if (current_state == running_state || current_state == control_state) {
        	// enable inverter adapter hardware
            uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);
    } else {
        	// disable inverter adapter hardware
            uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed_filtered*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec = omega_m_rad_per_sec*config_PMSM.polePairs;
    theta_el_rad = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    i_dq_measured_Amps = uz_transformation_3ph_abc_to_dq(i_abc_Amps, theta_el_rad); //actual Amp
    v_dq_measured_Volts = uz_transformation_3ph_abc_to_dq(v_abc_Volts, theta_el_rad); // actual voltage

    // get encode offset status and progress
    status = uz_encoder_offset_estimation_get_status(encoder_offset_obj);

    // Offset Estimation
    v_dq_ref_Volts.q = Global_Data.av.U_q; //controller output ref voltage to gobal data

    // Enable Control
    if (current_state==control_state)
    {
    	if(!uz_encoder_offset_estimation_get_finished(encoder_offset_obj)){         // if not finished
    		reference_currents_Amp = uz_encoder_offset_estimation_step(encoder_offset_obj);//receive current controller setpoint current from stepping function
    	}else{
    			reference_currents_Amp.d = 0.0f;                                              // else: it is finished, setpoints are 0
    			reference_currents_Amp.q = 0.0f;
    	}
        // Start: Control algorithm - only if ultrazohm is in control state

    	 CurrentControl_output_Volts = uz_CurrentControl_sample(CurrentControl_instance, reference_currents_Amp, i_dq_measured_Amps, v_DC_Volts, omega_el_rad_per_sec);
    	 output = uz_Space_Vector_Modulation(CurrentControl_output_Volts, v_DC_Volts, theta_el_rad);
    	 ref_voltage_3ph_abc = uz_transformation_3ph_dq_to_abc(CurrentControl_output_Volts, theta_el_rad);
    	 Global_Data.rasv.halfBridge1DutyCycle = output.DutyCycle_A;		// Set Duty Cycle A
    	 Global_Data.rasv.halfBridge2DutyCycle = output.DutyCycle_B;	   // Set Duty Cycle B
    	 Global_Data.rasv.halfBridge3DutyCycle = output.DutyCycle_C;	  // Set Duty Cycle C

    }
    // Set duty cycles for teo-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);

    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d3.FAULT_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d3.FAULT_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d3.FAULT_H2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d3.FAULT_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d3.FAULT_H3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d3.FAULT_L3) {
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d3.OC_L1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d3.OC_H1) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d3.OC_L2) {
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d3.OC_H2) {
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
