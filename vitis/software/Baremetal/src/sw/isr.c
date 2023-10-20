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
#include "../include/encoder_v25.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

#include "../uz/uz_dqn/uz_dqn.h"

#define PHASE_CURRENT_SCALING 12.5f
#define PHASE_VOLT_SCALING	12.0f
// Declaration for inverter Faults
float error_type = 0.0f;
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

struct uz_DutyCycle_t output = {0};
float theta_offset = -0.50f;
float theta_off_angle_pendulum = 0.5323f;
float omega_el_rad_per_sec = 0.0f;
float omega_m_rad_per_sec = 0.0f;
float Kp_id = 5.65f;
float Ki_id = 2715.0f;
float Kp_iq = 7.11f;
float Ki_iq = 2715.0f;
float speed_Kp = 0.0207f; // 0.0207f
float speed_Ki = 0.207f;
float action_current = 2.0f; // I_q fuer Agenten
float position_Kp = 0.5f;
// limits and time setting
float limit_error = 430.0f;
float disable_control = 380.0f;
int time_dqn = 15;
int time_wait_zero = 15;
// position control
float position_ref = 0.0f; // mm
int pos_strich = 0;         // Striche 0-2000
float pos_delta = 0;        // mm
float position_abs = 0.0f;  // mm
int globalposition = 0;
int i_counter = 0; // software counter for reference signal
int counter_for_reset = 0; // counter for occurence of software timeout
int counter_wait_pos = 0;
// nn testing
float old_theta_pendulum=0.0f;
float old_position=0.0f;
float angle_derv=0.0f;
float position_derv=0.0f;
extern uint32_t action_k;
extern uz_dqn_t *testdqn2;
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void Reset_obs_and_measurements();
uz_matrix_t *output_nn = NULL;
bool ext_clamping=false;
extern bool update_lock;
float epsilon_k;
enum dqn_chain chain = dqn_active;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    // Read Measurement from ADCs and Encoder
    ReadAllADC();
    // Read out all encoders
    update_speed_and_position_of_encoder_on_D5_1_ip_v25(&Global_Data);
    update_position_of_encoder_on_D5_2_ip_v25(&Global_Data);
    update_angle_of_encoder_on_D5_3_ip_v25(&Global_Data);
    // Pendulum and linear axis calculation
    Global_Data.av.theta_pendulum= Global_Data.av.theta_pendulum+theta_off_angle_pendulum;
    // calculate position
    globalposition = (int)Global_Data.av.position_pendulum;
    // count reference signals
    if ((pos_strich - globalposition) > 1500)
    {
    	i_counter++;
    }
    else if ((pos_strich - globalposition) < -1500)
    {
    	i_counter--;
    }
    position_abs = (float)(i_counter + (globalposition / (UZ_D5_POSINCREMENTAL_ENCODER_RESOLUTION * 4.0f))) * 5.0f;
    pos_strich = (int)Global_Data.av.position_pendulum;
    // calculate and transform observations for dqn
    Global_Data.obs.dqn_chart_position=position_abs/1.0e3f;
    // derivation angle and position with filtering and treshold
    angle_derv=(Global_Data.av.theta_pendulum-old_theta_pendulum)/Global_Data.av.isr_samplerate_s;// rad/s
    Global_Data.obs.dqn_angle_raw = Global_Data.av.theta_pendulum;
    if (fabsf(angle_derv) > 1.0e2f)
    {}
    else
    {
    	Global_Data.obs.dqn_angle_derv_raw = angle_derv;
        Global_Data.obs.dqn_angle_derv = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_angle, angle_derv);
    }
    old_theta_pendulum=Global_Data.av.theta_pendulum;
    position_derv=((Global_Data.obs.dqn_chart_position-old_position)/Global_Data.av.isr_samplerate_s);

    if (fabsf(position_derv) > 1.0e2f)
    {}
    else
    {
    	Global_Data.obs.dqn_chart_position_derv_raw= position_derv;
        Global_Data.obs.dqn_chart_position_derv = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_position, position_derv);
    }
    old_position=Global_Data.obs.dqn_chart_position;
    Global_Data.obs.dqn_angle = Global_Data.av.theta_pendulum- M_PI;// wegen funktionierender Referenzspur muss jetzt offset hinzugerechnet werden
    Global_Data.obs.dqn_sin_angle=sin(Global_Data.obs.dqn_angle);
    Global_Data.obs.dqn_cos_angle=cos(Global_Data.obs.dqn_angle);
    // Read Measurement Data of Inverter Card
    Global_Data.mv.v_abc_Volts.a = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_SCALING;
    Global_Data.mv.v_abc_Volts.b = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_SCALING;
    Global_Data.mv.v_abc_Volts.c = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_SCALING;
    Global_Data.mv.V_dc_volts 	  = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_SCALING;
    Global_Data.mv.i_abc_Amps.a  = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_SCALING;
    Global_Data.mv.i_abc_Amps.b  = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_SCALING;
    Global_Data.mv.i_abc_Amps.c  = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_SCALING;
    Global_Data.mv.i_DC_Amps    = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_SCALING;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    // Get Current State
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
        // enable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    }
    else {
     	// disable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    }
    // calculate data pmsm for foc
    Global_Data.av.theta_elec = Global_Data.av.theta_elec * 3.0f - theta_offset;
    Global_Data.av.theta_mech = Global_Data.av.theta_elec * (1.0f/3.0f);
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * (2.0f * UZ_PIf) / 60.0f;         // w_mech
    omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * 3.0f * (2.0f * M_PI) / 60.0f; // calculate w_el with pole pairs 3
    Global_Data.av.mechanicalRotorSpeed_IIR_Filter = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_2, Global_Data.av.mechanicalRotorSpeed);
    Global_Data.mv.i_dq_Amps = uz_transformation_3ph_abc_to_dq(Global_Data.mv.i_abc_Amps, Global_Data.av.theta_elec);

    epsilon_k=uz_dqn_get_epsilon(testdqn2);
    if (current_state==control_state)
    {
    	if (fabsf(position_abs) > limit_error){
    		uz_assert(0);
    	}
    	// switch case for switching between dqn, pos_control and other states
    	switch (chain) {
			case dqn_active:
				Global_Data.av.trigger_logging = 1.0f;
				counter_for_reset++;
				// get output from nn
		    	if (fabsf(position_abs) > disable_control){
		    		chain=limit_violation;
		    	}

		            switch (action_k){
		            case 0: Global_Data.rasv.dq_reference_current.q =action_current;
		            break;
		            case 1:	Global_Data.rasv.dq_reference_current.q=action_current/2.0f;
		            break;
		            case 2: Global_Data.rasv.dq_reference_current.q=0.0f;
		            break;
		            case 3:	Global_Data.rasv.dq_reference_current.q=-action_current/2.0f;
		            break;
		            case 4: Global_Data.rasv.dq_reference_current.q=-action_current;
		            break;
		            default: uz_assert(0);
		            }
		        if (counter_for_reset>(time_dqn*(int)UZ_PWM_FREQUENCY)){
		        	chain=limit_violation;
		        }
				break;
			case limit_violation:
				Global_Data.av.trigger_logging = 2.0f;
				Global_Data.rasv.dq_reference_current.q=0.0f;
                chain=return_to_zero_position;
				break;
			case return_to_zero_position:
				Global_Data.av.trigger_logging = 3.0f;
				Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, 0.0f, position_abs, ext_clamping);
				Global_Data.rasv.M_ref_Nm = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, - Global_Data.rasv.n_ref_rpm);
				Global_Data.rasv.dq_reference_current = uz_SetPoint_sample(Global_Data.objects.SP_instance, omega_m_rad_per_sec, Global_Data.rasv.M_ref_Nm, Global_Data.mv.V_dc_volts, Global_Data.mv.i_dq_Amps);
				if(fabsf(position_abs) < 1.0f){
					chain=wait_at_zero_position;
				}
				break;
			case wait_at_zero_position:
				Global_Data.av.trigger_logging = 4.0f;
				if(fabsf(position_abs) < 1.0f){
				if (counter_wait_pos<(time_wait_zero*(int)UZ_PWM_FREQUENCY)){
					counter_wait_pos++;
					}
				else{
					Reset_obs_and_measurements();
					chain=get_to_start_postion;
					}
				}
				else{
				Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, 0.0f, position_abs, ext_clamping);
				Global_Data.rasv.M_ref_Nm = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, - Global_Data.rasv.n_ref_rpm);
				Global_Data.rasv.dq_reference_current = uz_SetPoint_sample(Global_Data.objects.SP_instance, omega_m_rad_per_sec, Global_Data.rasv.M_ref_Nm, Global_Data.mv.V_dc_volts, Global_Data.mv.i_dq_Amps);
				}
				break;
			case get_to_start_postion:
				Global_Data.av.trigger_logging = 5.0f;
				position_ref = 150.0f;
				pos_delta = position_ref-position_abs;
				Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, position_ref, position_abs, ext_clamping);
				Global_Data.rasv.M_ref_Nm = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, - Global_Data.rasv.n_ref_rpm);
				Global_Data.rasv.dq_reference_current = uz_SetPoint_sample(Global_Data.objects.SP_instance, omega_m_rad_per_sec, Global_Data.rasv.M_ref_Nm, Global_Data.mv.V_dc_volts, Global_Data.mv.i_dq_Amps);
				if(fabsf(pos_delta) < 1.0f){
					if(!update_lock){
						chain=dqn_active;
					}
				}
				else{// counter im letzten case alle auf 0
					counter_for_reset = 0;
					counter_wait_pos = 0;
				}
				break;
			default:
				break;
    	}
    	if (fabsf(position_abs) < limit_error)
    	{
    	//Position Control, DQN has to be commented out
//    	Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, position_ref, position_abs, ext_clamping);
//    	Global_Data.rasv.M_ref_Nm = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, -Global_Data.rasv.n_ref_rpm );										// Calculate Reference Torque
//    	Global_Data.rasv.dq_reference_current = uz_SetPoint_sample(Global_Data.objects.SP_instance, omega_m_rad_per_sec, Global_Data.rasv.M_ref_Nm, Global_Data.mv.V_dc_volts, Global_Data.mv.i_dq_Amps);				// Calculate Reference Currents
    	Global_Data.rasv.dq_ref_Volts = uz_CurrentControl_sample(Global_Data.objects.CC_instance, Global_Data.rasv.dq_reference_current, Global_Data.mv.i_dq_Amps, Global_Data.mv.V_dc_volts, omega_el_rad_per_sec);		// Calculate Reference Voltages
    	output = uz_Space_Vector_Modulation(Global_Data.rasv.dq_ref_Volts, Global_Data.mv.V_dc_volts, Global_Data.av.theta_elec);											// Calculate Duty Cycles
    	Global_Data.rasv.halfBridge1DutyCycle = output.DutyCycle_A;	// Set Duty Cycle A
    	Global_Data.rasv.halfBridge2DutyCycle = output.DutyCycle_B;	// Set Duty Cycle B
    	Global_Data.rasv.halfBridge3DutyCycle = output.DutyCycle_C;	// Set Duty Cycle C
        // change control parameters during runtime
        uz_CurrentControl_set_Kp_id(Global_Data.objects.CC_instance, Kp_id);
        uz_CurrentControl_set_Kp_iq(Global_Data.objects.CC_instance, Kp_iq);
        uz_CurrentControl_set_Ki_id(Global_Data.objects.CC_instance, Ki_id);
        uz_CurrentControl_set_Ki_iq(Global_Data.objects.CC_instance, Ki_iq);
        uz_SpeedControl_set_Kp(Global_Data.objects.Speed_instance, speed_Kp);
        uz_SpeedControl_set_Ki(Global_Data.objects.Speed_instance, speed_Ki);
        uz_PI_Controller_set_Kp(Global_Data.objects.PI_instance, position_Kp);
    	}
    	}
    	else
    	{
    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
    	uz_SpeedControl_reset(Global_Data.objects.Speed_instance);
    	uz_CurrentControl_reset(Global_Data.objects.CC_instance);
    	}
    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
    // Update JavaScope
    JavaScope_update(&Global_Data);
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
        error_type = 1.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
//    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
//    	error_type = 2.0f;
//       ultrazohm_state_machine_set_error(true);
//    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    	error_type = 3.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    	error_type = 4.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    	error_type = 5.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    	error_type = 6.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    	error_type = 7.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    	error_type = 8.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    	error_type = 9.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    	error_type = 10.0f;
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
static void Reset_obs_and_measurements()
{
	Reset_global_Data(&Global_Data);
};
