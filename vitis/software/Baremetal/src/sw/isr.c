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

#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_spwm/uz_spwm.h"
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "../uz/uz_Trajectory/uz_Trajectory.h"

#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f

#define PHASE_CURRENT_CONV_a	12.5f * 0.988f
#define PHASE_CURRENT_CONV_b	12.5f * 0.996f
#define PHASE_CURRENT_CONV_c	12.5f * 1.001f

#define PHASE_CURRENT_OFFSET_a	0.0f + 0.006f
#define PHASE_CURRENT_OFFSET_b	0.0f - 0.005f
#define PHASE_CURRENT_OFFSET_c 0.0f + 0.009f

#define PHASE_VOLT_CONV_a	12.0f
#define PHASE_VOLT_CONV_b	12.0f
#define PHASE_VOLT_CONV_c	12.0f

#define PHASE_VOLT_OFFSET_a	0.0f
#define PHASE_VOLT_OFFSET_b	0.0f
#define PHASE_VOLT_OFFSET_c	0.0f

#define MAX_MOTOR_SPEED_RPM 2000.0f
#define MAX_PHASE_CURRENT_AMP 4.2f
#define MAX2_PHASE_CURRENT_AMP 6.0f
#define MAX_DC_VOLT 50.0f
#define MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1 1.0f
#define MAX_COUNT_MAX_PHASE_CURRENT_AMP_1 UZ_PWM_FREQUENCY / INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE * MAX_SECONDS_MAX_PHASE_CURRENT_AMP_1


unsigned int currentlimit_counter = 0;

float CIL_omega_mech = 0.0f;
float CIL_n_ref_rpm = 1000.0f;
float CIL_omega_elec = 0.0f;
float CIL_U_ZK = 0.0f;

bool theta_offset_bestimmung = false;

//float theta_offest = -3.3f;

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

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    Global_Data.av.omega_mech = 1*((Global_Data.av.mechanicalRotorSpeed_filtered / 60.0f) * (2.0f * (float)M_PI));
    Global_Data.av.omega_elec = Global_Data.av.omega_mech * 3;
    Global_Data.av.theta_elec = fmodf(((Global_Data.av.theta_mech*3) + Global_Data.av.theta_offset),(2* M_PI));
    //Global_Data.av.theta_elec = fmodf(Global_Data.av.theta_elec,  (2* M_PI));


   // Global_Data.av.omega_mech = -1*((Global_Data.av.mechanicalRotorSpeed_filtered / 60.0f) * (2.0f * (float)M_PI));
    //Global_Data.av.omega_elec = Global_Data.av.omega_mech * UZ_D5_MOTOR_POLE_PAIR_NUMBER;
    //Global_Data.av.theta_elec = -(Global_Data.av.theta_elec + theta_offest) + 2*M_PI;
    //Global_Data.av.theta_elec = fmodf(Global_Data.av.theta_elec,  (2* M_PI));

    //Global_Data.av.theta_elec=uz_incrementalEncoder_get_theta_el(Global_Data.objects.encoder_D5);

    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Enable Gates:
    if (current_state == running_state || current_state == control_state) {
      // enable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    } else {
      // disable inverter adapter hardware
      uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    }


    if(Global_Data.av.select_CIL) {
    	uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsmModel);
    	uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsmModel);
    }


    // Read out measured currents and voltages:

    Global_Data.av.u_a = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_a +PHASE_VOLT_OFFSET_a;
    Global_Data.av.u_b = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_b +PHASE_VOLT_OFFSET_b;
    Global_Data.av.u_c = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_c +PHASE_VOLT_OFFSET_c;
    Global_Data.av.U_ZK = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
    Global_Data.av.i_a = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_a +PHASE_CURRENT_OFFSET_a;
    Global_Data.av.i_b = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_b +PHASE_CURRENT_OFFSET_b;
    Global_Data.av.i_c = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_c +PHASE_CURRENT_OFFSET_c;
    Global_Data.av.I_ZK = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

    Global_Data.av.u_ab =    Global_Data.av.u_a -   Global_Data.av.u_b;
    Global_Data.av.u_bc =    Global_Data.av.u_b -   Global_Data.av.u_c;
    Global_Data.av.u_ca =    Global_Data.av.u_c -   Global_Data.av.u_a;
    Global_Data.av.u_n =    (Global_Data.av.u_a + Global_Data.av.u_b + Global_Data.av.u_c)/3;
    Global_Data.av.u_ph1 =   Global_Data.av.u_a - Global_Data.av.u_n;
    Global_Data.av.u_ph2 =   Global_Data.av.u_b - Global_Data.av.u_n;
    Global_Data.av.u_ph3 =   Global_Data.av.u_c - Global_Data.av.u_n;

    // over current and over temperature protection:

    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 5.0f;
    }
    //Overtemperature for L1
   // if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
    //   ultrazohm_state_machine_set_error(true);
    //   Global_Data.av.errorcode = 6.0f;
   // }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 7.0f;
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 8.0f;
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 9.0f;
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 10.0f;
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 11.0f;
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 12.0f;
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 13.0f;
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
       ultrazohm_state_machine_set_error(true);
       Global_Data.av.errorcode = 14.0f;
    }


    if(fabs(Global_Data.av.mechanicalRotorSpeed_filtered) > MAX_MOTOR_SPEED_RPM ){
        	ultrazohm_state_machine_set_stop(true);
        				   Global_Data.av.errorcode = 4.0f;
        }


    if(fabs(Global_Data.av.i_a) > MAX2_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b) > MAX2_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c) > MAX2_PHASE_CURRENT_AMP ){
    	ultrazohm_state_machine_set_stop(true);
    				   Global_Data.av.errorcode = 3.0f;
    }



    // Software current limit
    if(fabs(Global_Data.av.i_a) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c) > MAX_PHASE_CURRENT_AMP ){


    	currentlimit_counter = currentlimit_counter + 1;

    	if( (float)currentlimit_counter > MAX_COUNT_MAX_PHASE_CURRENT_AMP_1){
    		// Disable Inverter
			   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
			   ultrazohm_state_machine_set_stop(true);
			   Global_Data.av.errorcode = 1.0f;
    	}
    }else{
    	currentlimit_counter = 0;
    }

    if(!Global_Data.av.select_CIL){
		// check DC Bus
		if(fabs(Global_Data.av.U_ZK) > MAX_DC_VOLT) {

		   // Disable Inverter
		   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
		   ultrazohm_state_machine_set_stop(true);
		   Global_Data.av.errorcode = 2.0f;

		}
    }

    // current and voltage in structs
	Global_Data.av.i_abc_m.a = Global_Data.av.i_a;
	Global_Data.av.i_abc_m.b = Global_Data.av.i_b;
	Global_Data.av.i_abc_m.c = Global_Data.av.i_c;

	Global_Data.av.u_abc_m.a = Global_Data.av.u_a;
	Global_Data.av.u_abc_m.b = Global_Data.av.u_b;
	Global_Data.av.u_abc_m.c = Global_Data.av.u_c;


	// FS_Data auslesen
    Global_Data.av.FS_output = uz_Flussschaetzer_step(Global_Data.objects.Flussschaetzer,Global_Data.av.u_alphabeta_ref,Global_Data.av.i_alphabeta_m,0);
    Global_Data.av.n_FS = Global_Data.av.FS_output.omega_m_est*(30/M_PI);

if (Global_Data.av.fluxOntheta == 1)
	{Global_Data.av.theta_elec_used =  Global_Data.av.FS_output.theta_el_kor;

	}
else {
	Global_Data.av.theta_elec_used =  Global_Data.av.theta_elec;
}

	// abc-dq Transformation
    Global_Data.av.i_dq_m = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_m, Global_Data.av.theta_elec_used);
    Global_Data.av.u_dq_m = uz_transformation_3ph_abc_to_dq(Global_Data.av.u_abc_m, Global_Data.av.theta_elec_used);

    // abc-alphabeta Transformation
    Global_Data.av.i_alphabeta_m =  uz_transformation_3ph_abc_to_alphabeta(Global_Data.av.i_abc_m);
    Global_Data.av.u_alphabeta_ref = uz_transformation_3ph_dq_to_alphabeta(Global_Data.av.u_dq_ref, Global_Data.av.theta_elec_used);

    // dq-alphabeta Transformation


    if (Global_Data.av.fluxOnomega == 1)
    	{Global_Data.av.omega_elec_used =  Global_Data.av.FS_output.omega_m_est* UZ_D5_MOTOR_POLE_PAIR_NUMBER;
    	Global_Data.av.omega_mech_used = Global_Data.av.FS_output.omega_m_est;
    	}
    else {Global_Data.av.omega_elec_used =  Global_Data.av.omega_elec;
    Global_Data.av.omega_mech_used = Global_Data.av.omega_mech;}




    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state


    	if(Global_Data.av.select_CIL){
    		CIL_omega_mech = (CIL_n_ref_rpm / 60.0f) * 2.0f * (float)M_PI;
    		CIL_omega_elec = CIL_omega_mech * UZ_D5_MOTOR_POLE_PAIR_NUMBER;
    		CIL_U_ZK = 48.0f;


    		Global_Data.av.pmsmModel_output = uz_pmsmModel_get_outputs(Global_Data.objects.pmsmModel);

    		Global_Data.av.i_dq_m.d = Global_Data.av.pmsmModel_output.i_d_A;
    		Global_Data.av.i_dq_m.q = Global_Data.av.pmsmModel_output.i_q_A;

    		Global_Data.av.u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.current_control, Global_Data.av.i_dq_ref, Global_Data.av.i_dq_m, CIL_U_ZK, CIL_omega_elec);

    		Global_Data.av.pmsmModel_input.omega_mech_1_s = CIL_n_ref_rpm;
			Global_Data.av.pmsmModel_input.v_d_V = Global_Data.av.u_dq_ref.d;
			Global_Data.av.pmsmModel_input.v_q_V = Global_Data.av.u_dq_ref.q;

    		uz_pmsmModel_set_inputs(Global_Data.objects.pmsmModel, Global_Data.av.pmsmModel_input);


    		Global_Data.av.output_Dutycycle.DutyCycle_A = 0.0f;
    		Global_Data.av.output_Dutycycle.DutyCycle_B = 0.0f;
    		Global_Data.av.output_Dutycycle.DutyCycle_C = 0.0f;
    	}else{
    		Global_Data.av.Traj_1 = uz_Trajectory_Step(Global_Data.objects.TraceGen_1);
    		if (Global_Data.av.select_speed_control == true){

    			// Generate Trajectory
    			 if (Global_Data.av.trajectoryON == 1){
    			  Global_Data.av.n_ref_rpm =Global_Data.av.Traj_1;}

    		Global_Data.av.i_dq_ref.q = uz_SpeedControl_sample(Global_Data.objects.speed_control, Global_Data.av.omega_mech_used, Global_Data.av.n_ref_rpm);
				Global_Data.av.i_dq_ref.d = 0.0f;
    		}
    			Global_Data.av.u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.current_control, Global_Data.av.i_dq_ref, Global_Data.av.i_dq_m, Global_Data.av.U_ZK, Global_Data.av.omega_elec_used);
    		   //output_Dutycycle = uz_Space_Vector_Modulation(Global_Data.av.u_dq_ref, Global_Data.av.U_ZK, Global_Data.av.theta_elec);

    		   Global_Data.av.output_Dutycycle = uz_spwm_dq(Global_Data.av.u_dq_ref, Global_Data.av.U_ZK, Global_Data.av.theta_elec_used);

    	}

		   Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_A;
		   Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_B;
		   Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.output_Dutycycle.DutyCycle_C;



    }else{

    	uz_CurrentControl_reset(Global_Data.objects.current_control);
    	uz_SpeedControl_reset(Global_Data.objects.speed_control);
    	uz_Flussschaetzer_reset(Global_Data.objects.Flussschaetzer);

    	if(theta_offset_bestimmung){
        	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.d_a_ref;
        	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.d_b_ref;
        	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.d_c_ref;
    	}else{
			Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
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
