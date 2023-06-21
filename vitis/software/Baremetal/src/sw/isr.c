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


//Changes
struct uz_pmsm_model6ph_dq_outputs_general_t CIL_out_general = {0};
uz_6ph_dq_t v_dqxy_limited_volts = {0};
uz_6ph_dq_t v_dqxy_limited_volts_k_old = {0};
uz_6ph_dq_t v_dqxy_non_limited_volts = {0};
uz_6ph_dq_t CIL_i_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t CIL_v_dq_reference = {0};
uz_3ph_dq_t CIL_v_xy_reference = {0};
uz_3ph_dq_t CIL_v_z1z2_reference = {0};
uz_3ph_dq_t CIL_i_dq_reference = {0};
uz_3ph_dq_t CIL_i_xy_reference = {0};
uz_3ph_dq_t CIL_i_z1z2_reference = {0};
uz_3ph_dq_t CIL_i_dq_meas= {0};
uz_3ph_dq_t CIL_i_xy_meas = {0};
uz_3ph_dq_t CIL_i_z1z2_meas = {0};
float CIL_omega_mech = 100.0f; //fixed speed for the CIL model
float rated_current = 10.0f;
float rated_Speed_rpm = 3000.0f;
float speed_weight = 1.0f / 3000.0f;
float V_DC_Volts = 565.0f;
float U_max = 565.0f / 1.732050808f; // sqrt(3) Because of SpaceVetorLimitation
float Voltage_Scaling = 1.0f / (565.0f / 1.732050808f);
float ts = 1.0f / UZ_PWM_FREQUENCY;
float omega_el_rad_per_sec = 0.0f;
float polepairs = 5.0f;
extern bool select_CurrentControl;
extern bool select_DDPG_1_64;
extern bool select_DDPG_3_64;
extern bool select_Real;
extern bool select_CIL;
extern bool select_automatic_idiq;
extern float n_ref_rpm;
extern float i_d_ref;
extern float i_q_ref;
extern float i_X_ref;
extern float i_Y_ref;
int reset = 0U;
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

    //Take measurements independent of control_state
    if(select_Real) {
            	Global_Data.av.resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d2);
            	Global_Data.av.theta_elec = Global_Data.av.resolver_outputs.position_el_2pi;
            	Global_Data.av.theta_mech = Global_Data.av.resolver_outputs.position_mech_2pi;
            	Global_Data.av.omega_mech = Global_Data.av.resolver_outputs.omega_mech_rad_s;
            	Global_Data.av.omega_elec = Global_Data.av.omega_mech * polepairs;

            	Global_Data.av.temp_VSI_1 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.pwm_duty_freq_detection_VSI_1).TempDegreesCelsius;
            	Global_Data.av.temp_VSI_2 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.pwm_duty_freq_detection_VSI_2).TempDegreesCelsius;

    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        if(select_CIL) {
        	CIL_i_dq_reference.d = i_d_ref;
        	CIL_i_dq_reference.q = i_q_ref;
        	CIL_i_xy_reference.d = i_X_ref;
        	CIL_i_xy_reference.q = i_Y_ref;
        	CIL_omega_mech = (n_ref_rpm / 60.0f) * 2.0f * UZ_PIf;
        	if(reset) {
        		uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
        	}
        	uz_pmsm_model6ph_dq_set_inputs_general(Global_Data.objects.CIL_pmsm,CIL_omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
        	uz_pmsm_model6ph_dq_set_voltage(Global_Data.objects.CIL_pmsm,v_dqxy_limited_volts);              // set input voltage
        	CIL_out_general = uz_pmsm_model6ph_dq_get_outputs_general(Global_Data.objects.CIL_pmsm);    // read out resulting general outputs
        	CIL_i_meas = uz_pmsm_model6ph_dq_get_output_currents(Global_Data.objects.CIL_pmsm);   // read out actual currents
        	Global_Data.av.mechanicalRotorSpeed = (CIL_out_general.omega_mech * 60.0f) / (2.0f * UZ_PIf);
        	omega_el_rad_per_sec = CIL_out_general.omega_mech * polepairs;
        	CIL_i_dq_meas.d = CIL_i_meas.d;
        	Global_Data.av.I_d = CIL_i_meas.d;
        	CIL_i_dq_meas.q = CIL_i_meas.q;
        	Global_Data.av.I_q = CIL_i_meas.q;
        	CIL_i_xy_meas.d = CIL_i_meas.x;
        	Global_Data.av.I_X = CIL_i_meas.x;
        	CIL_i_xy_meas.q = CIL_i_meas.y;
        	Global_Data.av.I_Y = CIL_i_meas.y;
        	CIL_i_z1z2_meas.d = CIL_i_meas.z1;
        	CIL_i_z1z2_meas.q = CIL_i_meas.z2;
        	if(select_CurrentControl) {
        		CIL_v_dq_reference = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, CIL_i_dq_reference, CIL_i_dq_meas, V_DC_Volts, omega_el_rad_per_sec);
        		CIL_v_xy_reference = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, CIL_i_xy_reference, CIL_i_xy_meas, V_DC_Volts, omega_el_rad_per_sec);
        	} else if(select_DDPG_1_64) {

        	} else if(select_DDPG_3_64) {

        	}
        	v_dqxy_limited_volts.d = CIL_v_dq_reference.d;
        	Global_Data.av.U_d = CIL_v_dq_reference.d;
        	v_dqxy_limited_volts.q = CIL_v_dq_reference.q;
        	Global_Data.av.U_q = CIL_v_dq_reference.q;
        	v_dqxy_limited_volts.x = CIL_v_xy_reference.d;
        	Global_Data.av.U_X = CIL_v_xy_reference.d;
        	v_dqxy_limited_volts.y = CIL_v_xy_reference.q;
        	Global_Data.av.U_Y = CIL_v_xy_reference.q;
        	v_dqxy_limited_volts.z1 = 0.0f;
        	v_dqxy_limited_volts.z2 = 0.0f;

        } else {
        	uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
        }

        if(select_Real) {
        	if(select_CurrentControl) {

        	} else if(select_DDPG_1_64) {

        	} else if(select_DDPG_3_64) {

        	}
        } else {

        }
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
