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
//#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

#define		RAD_PER_S_2_RPM		30.0f/UZ_PIf
#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT			15.0f

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

struct uz_3ph_abc_t i_abc_d1 = {0.0f};
struct uz_3ph_abc_t i_abc_d2 = {0.0f};
struct uz_3ph_dq_t i_dq_d1 = {0.0f};
struct uz_3ph_dq_t i_dq_d2 = {0.0f};
struct uz_3ph_dq_t i_dq_ref_d1 = {0.0f};
struct uz_3ph_dq_t i_dq_ref_d2 = {0.0f};
struct uz_3ph_dq_t v_dq_ref_d1 = {0.0f};
struct uz_3ph_dq_t v_dq_ref_d2 = {0.0f};
struct uz_DutyCycle_t dutycyc_d1 = {0.0f};
struct uz_DutyCycle_t dutycyc_d2 = {0.0f};
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
    // read electrical angle and speed from both resolvers
    Global_Data.av.theta_el_omega_el_D5_1 = uz_resolverIP_readElectricalPositionAndVelocity(Global_Data.objects.uz_d_resolver_D5_1);
    Global_Data.av.theta_el_omega_el_D5_2 = uz_resolverIP_readElectricalPositionAndVelocity(Global_Data.objects.uz_d_resolver_D5_2);
    // read mechanical angle and speed from both resolvers
    Global_Data.av.theta_mech_omega_mech_D5_1 = uz_resolverIP_readMechanicalPositionAndVelocity(Global_Data.objects.uz_d_resolver_D5_1);
    Global_Data.av.theta_mech_omega_mech_D5_2 = uz_resolverIP_readMechanicalPositionAndVelocity(Global_Data.objects.uz_d_resolver_D5_2);
    Global_Data.av.speed_rpm_d5_1 = Global_Data.av.theta_mech_omega_mech_D5_1.velocity * RAD_PER_S_2_RPM;
    Global_Data.av.speed_rpm_d5_2 = Global_Data.av.theta_mech_omega_mech_D5_2.velocity * RAD_PER_S_2_RPM;
    // update status of both inverters
    uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_D1);
    uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_D2);
    // assign status to Global_Data
    Global_Data.av.inverter_D1_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_D1);
    Global_Data.av.inverter_D2_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_D2);

    // assign measurements to Global_Data
    Global_Data.av.i_a_d1 	= Global_Data.aa.A1.me.ADC_A4 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_b_d1 	= Global_Data.aa.A1.me.ADC_A3 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_c_d1 	= Global_Data.aa.A1.me.ADC_A2 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_dc_d1 	= Global_Data.aa.A1.me.ADC_B5 * CURRENT_2_SI_AMPERE;
    Global_Data.av.v_a_d1 	= Global_Data.aa.A1.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_b_d1 	= Global_Data.aa.A1.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_c_d1 	= Global_Data.aa.A1.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_dc_d1 	= Global_Data.aa.A1.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

    Global_Data.av.i_a_d2 	= Global_Data.aa.A2.me.ADC_A4 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_b_d2 	= Global_Data.aa.A2.me.ADC_A3 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_c_d2 	= Global_Data.aa.A2.me.ADC_A2 * CURRENT_2_SI_AMPERE;
    Global_Data.av.i_dc_d2 	= Global_Data.aa.A2.me.ADC_B5 * CURRENT_2_SI_AMPERE;
    Global_Data.av.v_a_d2 	= Global_Data.aa.A2.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_b_d2 	= Global_Data.aa.A2.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_c_d2 	= Global_Data.aa.A2.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
    Global_Data.av.v_dc_d2 	= Global_Data.aa.A2.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

    i_abc_d1.a = Global_Data.av.i_a_d1;
    i_abc_d1.b = Global_Data.av.i_b_d1;
    i_abc_d1.c = Global_Data.av.i_c_d1;
    i_abc_d2.a = Global_Data.av.i_a_d2;
    i_abc_d2.b = Global_Data.av.i_b_d2;
    i_abc_d2.c = Global_Data.av.i_c_d2;

    // check for current limit
    if (fabs(Global_Data.av.i_a_d1) > MAX_CURRENT || fabs(Global_Data.av.i_b_d1) > MAX_CURRENT || fabs(Global_Data.av.i_c_d1) > MAX_CURRENT ||
   		fabs(Global_Data.av.i_a_d2) > MAX_CURRENT || fabs(Global_Data.av.i_b_d2) > MAX_CURRENT || fabs(Global_Data.av.i_c_d2) > MAX_CURRENT) {
    	uz_assert(NULL);
    }

    // claculate mean temp values over all measured temps of each inverter
    Global_Data.av.mean_temp_inv_d1 = (Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_D1_status.ChipTempDegreesCelsius_L3) * 0.1667;
    Global_Data.av.mean_temp_inv_d2 = (Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_D2_status.ChipTempDegreesCelsius_L3) * 0.1667;


    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // if "Stop"
    if (current_state==idle_state)
    {
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_D1, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_D2, false);
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_d1);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_d2);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_d1);
		// write zero dutycycle
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;

    }

    // if "Enable System"
    if (current_state==running_state)
    {
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_D1, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_D2, true);
    }


    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	// park transformation of measured currents
    	i_dq_d1 = uz_transformation_3ph_abc_to_dq(i_abc_d1, Global_Data.av.theta_el_omega_el_D5_1.position);
    	i_dq_d2 = uz_transformation_3ph_abc_to_dq(i_abc_d2, Global_Data.av.theta_el_omega_el_D5_2.position);
    	Global_Data.av.i_d_d1 = i_dq_d1.d;
    	Global_Data.av.i_q_d1 = i_dq_d1.q;
    	Global_Data.av.i_d_d2 = i_dq_d2.d;
    	Global_Data.av.i_q_d2 = i_dq_d2.q;
    	// calculate reference torque from speed ctrl of d1
    	Global_Data.rasv.M_ref_d1 = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_d1, Global_Data.av.theta_mech_omega_mech_D5_1.velocity, Global_Data.rasv.n_ref_d1);
    	// calculate current setpoint for speed control of d1
    	i_dq_ref_d1 = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_d1, Global_Data.av.theta_mech_omega_mech_D5_1.velocity, Global_Data.rasv.M_ref_d1, Global_Data.av.v_dc_d1, i_dq_d1);
    	// get reference currents from Global_Data
//    	i_dq_ref_d1 = Global_Data.rasv.i_dq_ref_d1;
    	i_dq_ref_d2 = Global_Data.rasv.i_dq_ref_d2;
    	// calculate reference voltages for current control
    	v_dq_ref_d1 = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_d1, i_dq_ref_d1, i_dq_d1, Global_Data.av.v_dc_d1, Global_Data.av.theta_el_omega_el_D5_1.velocity);
    	v_dq_ref_d2 = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_d2, i_dq_ref_d2, i_dq_d2, Global_Data.av.v_dc_d2, Global_Data.av.theta_el_omega_el_D5_2.velocity);
    	Global_Data.av.v_d_d1 = v_dq_ref_d1.d;
    	Global_Data.av.v_q_d1 = v_dq_ref_d1.q;
    	// calculate duty cycles from reference dq voltages
    	dutycyc_d1 = uz_Space_Vector_Modulation(v_dq_ref_d1, Global_Data.av.v_dc_d1, Global_Data.av.theta_el_omega_el_D5_1.position);
    	dutycyc_d2 = uz_Space_Vector_Modulation(v_dq_ref_d2, Global_Data.av.v_dc_d2, Global_Data.av.theta_el_omega_el_D5_2.position);

    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_d1.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_d1.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_d1.DutyCycle_C;
    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_d2.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_d2.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_d2.DutyCycle_C;


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
