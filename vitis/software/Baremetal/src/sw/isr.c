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

#define MAX_PHASE_CURRENT_AMP  10.0f
#define ADC_CURRENT_OFFSET    2.5f //Offset for LEM Sensors
#define NUMBER_OF_TURNS_CURRENT_MEASURING 3.0f
#define ADC_CURRENT_SCALING	  80.0f/NUMBER_OF_TURNS_CURRENT_MEASURING
#define ADC_VOLTAGE_OFFSET 0	// 8.6
#define ADC_VOLTAGE_SCALING 12.5f
#define DC_VOLTAGE_SCALING 12.5f
#define MAX_SPEED_ASSERTION 1500 //rpm

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
#include "../uz/uz_signals/uz_signals.h"


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// Parameter ID
extern uz_ParameterID_Data_t ParaID_Data;
extern uz_ParameterID_t* ParameterID;

//
bool Parameter_ID_enabled = true;
bool Speed_Control_enabled = false;

struct uz_ParameterID_controller ParameterIDController;

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


    // read Resolver
    Global_Data.av.resolver_outputs_d4 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4);

    Global_Data.av.theta_mech = Global_Data.av.resolver_outputs_d4.position_mech_2pi;
    Global_Data.av.theta_elec = Global_Data.av.resolver_outputs_d4.position_el_2pi; //rad
    Global_Data.av.omega_mech_rad_per_sec = Global_Data.av.resolver_outputs_d4.omega_mech_rad_s;	// rad/s
    Global_Data.av.omega_el_rad_per_sec = Global_Data.av.resolver_outputs_d4.omega_mech_rad_s * ParaID_Data.GlobalConfig.PMSM_config.polePairs;	// rad/s
    Global_Data.av.mechanicalRotorSpeed = Global_Data.av.resolver_outputs_d4.n_mech_rpm;

    // read currents, convert to dq
    Global_Data.av.i_abc_act.a = (Global_Data.aa.A1.me.ADC_A1 - ADC_CURRENT_OFFSET) * ADC_CURRENT_SCALING;	// oder A2?
    Global_Data.av.i_abc_act.b = (Global_Data.aa.A1.me.ADC_A2 - ADC_CURRENT_OFFSET) * ADC_CURRENT_SCALING;
    Global_Data.av.i_abc_act.c = (Global_Data.aa.A1.me.ADC_A3 - ADC_CURRENT_OFFSET) * ADC_CURRENT_SCALING;

    Global_Data.av.i_dq_act = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_act, Global_Data.av.theta_elec);

    Global_Data.av.i_abc_act_filtered.a = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a, Global_Data.av.i_abc_act.a);
    Global_Data.av.i_abc_act_filtered.b = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b, Global_Data.av.i_abc_act.b);
    Global_Data.av.i_abc_act_filtered.c = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c, Global_Data.av.i_abc_act.c);

    // voltages:
    Global_Data.av.u_abc_act.a = (Global_Data.aa.A1.me.ADC_B5 - ADC_VOLTAGE_OFFSET) * ADC_VOLTAGE_SCALING;	// oder A2?
    Global_Data.av.u_abc_act.b = (Global_Data.aa.A1.me.ADC_B6 - ADC_VOLTAGE_OFFSET) * ADC_VOLTAGE_SCALING;
    Global_Data.av.u_abc_act.c = (Global_Data.aa.A1.me.ADC_B7 - ADC_VOLTAGE_OFFSET) * ADC_VOLTAGE_SCALING;

    // read U_ZK
    Global_Data.av.U_ZK = DC_VOLTAGE_SCALING * Global_Data.aa.A1.me.ADC_A4;	// oder A2?

//---------------------------------------------------------------------------------------------------------------------------------


    // Parameter ID stuff:
    ParaID_Data.ActualValues.I_abc = Global_Data.av.i_abc_act;

    ParaID_Data.ActualValues.V_DC = Global_Data.av.U_ZK;
    ParaID_Data.ActualValues.V_abc = Global_Data.av.u_abc_act;


    ParaID_Data.ActualValues.omega_m = Global_Data.av.omega_mech_rad_per_sec;
    ParaID_Data.ActualValues.omega_el = Global_Data.av.omega_el_rad_per_sec;
    ParaID_Data.ActualValues.theta_el = Global_Data.av.theta_elec;


    //Calculate missing ActualValues
    ParaID_Data.ActualValues.i_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.I_abc, ParaID_Data.ActualValues.theta_el);
    ParaID_Data.ActualValues.v_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.V_abc, ParaID_Data.ActualValues.theta_el);
    ParaID_Data.ActualValues.theta_m = Global_Data.av.theta_mech;






    // check current and speed limits
	if(fabs(Global_Data.av.i_abc_act.a) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_act.b) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc_act.c) > MAX_PHASE_CURRENT_AMP || (fabs(Global_Data.av.mechanicalRotorSpeed) > MAX_SPEED_ASSERTION)) {
		//ultrazohm_state_machine_set_stop(true);
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge10DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge11DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge12DutyCycle = 0.0f;
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

		//uz_assert(0);
	}



    // check DC-Bus voltage




    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {

    	if(Parameter_ID_enabled){

			// Parameter ID:
			uz_ParameterID_step(ParameterID, &ParaID_Data);

			ParameterIDController.CC_instance_dq = Global_Data.objects.CC_instance;
			ParameterIDController.SC_instance = Global_Data.objects.Speed_instance;
			ParameterIDController.SP_instance = Global_Data.objects.SP_instance;

			Global_Data.rasv.ParaID_v_dq = uz_ParameterID_Controller(&ParaID_Data, ParameterIDController);
			Global_Data.rasv.dutyCycles = uz_ParameterID_generate_DutyCycle(&ParaID_Data, Global_Data.rasv.ParaID_v_dq, Global_Data.objects.pwm_d1_pin_0_to_5);

    	}else{

            // Start: Control algorithm - only if ultrazohm is in control state


    		if(Speed_Control_enabled){
            	// Speed Control:
            	Global_Data.rasv.torque_ref = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, Global_Data.av.omega_mech_rad_per_sec, Global_Data.rasv.speed_ref_rpm);
               	// us_SetPoint
                Global_Data.rasv.i_dq_ref_currentcontrol = uz_SetPoint_sample(Global_Data.objects.SP_instance, Global_Data.av.omega_mech_rad_per_sec, Global_Data.rasv.M_ref_Nm, Global_Data.av.U_ZK, Global_Data.av.i_dq_act);
    		}
    		else{
    			// i_dq ref from GUI
    			Global_Data.rasv.i_dq_ref_currentcontrol = Global_Data.rasv.i_dq_ref;
    		}


        	// uz_CurrentControl
        	Global_Data.rasv.u_abc_ref = uz_CurrentControl_sample_abc(Global_Data.objects.CC_instance, Global_Data.rasv.i_dq_ref_currentcontrol, Global_Data.av.i_dq_act, Global_Data.av.U_ZK, Global_Data.av.omega_el_rad_per_sec, Global_Data.av.theta_elec);
        	Global_Data.rasv.u_dq_ref = uz_transformation_3ph_abc_to_dq(Global_Data.rasv.u_abc_ref, Global_Data.av.theta_elec);

        	// Modulation
        	Global_Data.rasv.dutyCycles = uz_Space_Vector_Modulation(Global_Data.rasv.u_dq_ref, Global_Data.av.U_ZK, Global_Data.av.theta_elec);

    	}

    	// write DutyCycles
		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.dutyCycles.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.dutyCycles.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.dutyCycles.DutyCycle_C;


    }else{

    	// reset current control
    	uz_CurrentControl_reset(Global_Data.objects.CC_instance);
    	// reset speed control
    	uz_SpeedControl_reset(Global_Data.objects.Speed_instance);

    	// write DutyCycles
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;

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
