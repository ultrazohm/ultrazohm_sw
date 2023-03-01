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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_FOC/uz_FOC.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

struct uz_DutyCycle_t output = {0};
float theta_offset = -0.50f;
float omega_el_rad_per_sec = 0.0f;
float omega_m_rad_per_sec = 0.0f;
float Kp_id = 5.65f;
float Ki_id = 2715.0f;
float Kp_iq = 7.11f;
float Ki_iq = 2715.0f;
float speed_Kp = 0.0207f; // 0.0207f
float speed_Ki = 0.207f;
float adc_scaling = 9.5f/2.0f; // Refactoring actual ADC Values 19.05: durch 2, Ohmrichter umgelötet
float action_current = 3.7f; // I_q für Agenten
// speed control
bool ext_clamping = false;

// position control
float position_ref = 0.0f; // mm
int pos_strich = 0;         // Striche 0-2000
float pos_delta = 0;        // mm
float position_abs = 0.0f;  // mm
int globalposition = 0;
int i_counter = 0; // software counter for reference signal
int counter_ip_core_res = 0; // counter for software timeout
int counter_for_reset = 0; // counter for occurence of software timeout
int counter_wait_pos = 0;
// nn testing
float old_theta_pendulum=0.0f;
float old_position=0.0f;
float angle_derv=0.0f;
float position_derv=0.0f;
uint32_t action=0;



// ip core reset
extern float offset_theta_pendulum;
//=============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void Reset_obs_and_measurements();
extern bool dqn_mutex;
uz_matrix_t *output_nn = NULL;

enum dqn_chain
{
    dqn_active = 0,
    limit_violation,
	return_to_zero_position,
	reset_angle,
	wait_at_zero_position
};
enum dqn_chain chain = dqn_active;
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    // Read out all encoders
    update_speed_and_position_of_encoder_on_D5_1_ip_v25(&Global_Data);
    update_position_of_encoder_on_D5_2_ip_v25(&Global_Data);
    update_angle_of_encoder_on_D5_3_ip_v25(&Global_Data);
//    Global_Data.av.theta_pendulum= Global_Data.av.theta_pendulum-offset_theta_pendulum;
    // calculate position
    globalposition = (int)Global_Data.av.position_pendulum;
	// count reference signals
	if (pos_strich - globalposition > 1500)
	{
		i_counter++;
	}
	else if (pos_strich - globalposition < -1500)
	{
		i_counter--;
	}
	position_abs = (i_counter + globalposition / (UZ_D5_POSINCREMENTAL_ENCODER_RESOLUTION * 4.0f)) * 5.0f;
    pos_strich = (int)Global_Data.av.position_pendulum;
    // calculate and transform observations for dqn
    Global_Data.obs.dqn_chart_position=position_abs/1.0e3f;
    // derivation angle and position with filtering and treshold
    angle_derv=(Global_Data.av.theta_pendulum-old_theta_pendulum)/Global_Data.av.isr_samplerate_s;// rad/s
    Global_Data.obs.dqn_angle_raw = Global_Data.av.theta_pendulum;

    if (abs(angle_derv) > 1.0e2f)
    {}
    else
    {
        Global_Data.obs.dqn_angle_derv_raw = angle_derv;
    	Global_Data.obs.dqn_angle_derv = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_angle, angle_derv);
    }

    old_theta_pendulum=Global_Data.av.theta_pendulum;
    position_derv=((Global_Data.obs.dqn_chart_position-old_position)/Global_Data.av.isr_samplerate_s);

    if (abs(position_derv) > 1.0e2f)
    {}
    else
    {
        Global_Data.obs.dqn_chart_position_derv_raw= position_derv;
    	Global_Data.obs.dqn_chart_position_derv = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_position, position_derv);
    }
    old_position=Global_Data.obs.dqn_chart_position;
    Global_Data.obs.dqn_angle = Global_Data.av.theta_pendulum- M_PI+0.5323f;// wegen funktionierender Refrenzspur muss jetzt offset hinzugerechnet werden
    Global_Data.obs.dqn_sin_angle=sin(Global_Data.obs.dqn_angle);
    Global_Data.obs.dqn_cos_angle=cos(Global_Data.obs.dqn_angle);
    // calculate data pmsm for foc
    Global_Data.av.theta_elec = Global_Data.av.theta_elec * 3.0f - theta_offset;
    Global_Data.av.theta_mech = Global_Data.av.theta_elec * (1.0f/3.0f);
    Global_Data.mv.measurement_current.a = adc_scaling * (Global_Data.aa.A2.me.ADC_A2 - 2.5f); // -2.5  Hall Sensor
    Global_Data.mv.measurement_current.b = adc_scaling * (Global_Data.aa.A2.me.ADC_A4 - 2.5f);
    Global_Data.mv.measurement_current.c = adc_scaling * (Global_Data.aa.A2.me.ADC_A3 - 2.5f);
    Global_Data.mv.dq_measurement_current = uz_transformation_3ph_abc_to_dq(Global_Data.mv.measurement_current, Global_Data.av.theta_elec);
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * (2.0f * M_PI) / 60.0f;         // w_mech
    omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * 3.0f * (2.0f * M_PI) / 60.0f; // calculate w_el with pole pairs 3
    Global_Data.av.mechanicalRotorSpeed_IIR_Filter = uz_signals_IIR_Filter_sample(Global_Data.objects.LPF1_instance_2, Global_Data.av.mechanicalRotorSpeed);
    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == control_state)
    {
    	if (abs(position_abs) > 430){
    		uz_assert(0);
    	}
    	// switch case for switching between dqn, pos_control and other states
    	switch (chain) {
			case dqn_active:
				Global_Data.av.trigger_logging = 1.0f;
				counter_for_reset++;
				// get output from nn
		    	if (abs(position_abs)> 390){
		    		chain=limit_violation;
		    	}
		        if (dqn_mutex)
		        {
		            output_nn = uz_nn_get_output_data(Global_Data.objects.uz_nn_instance);
		            dqn_mutex = false;
		            action = uz_matrix_get_max_index(output_nn);
		            switch (action){
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
		        }
		        if (counter_for_reset>600000){
		        	chain=limit_violation;
		        }
				break;
			case limit_violation:
				Global_Data.av.trigger_logging = 0.0f;
				Global_Data.rasv.dq_reference_current.q=0.0f;
				chain=return_to_zero_position;
				break;
			case return_to_zero_position:
				Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, position_ref, position_abs, ext_clamping);
				Global_Data.rasv.dq_reference_current = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, - Global_Data.rasv.n_ref_rpm, Global_Data.rasv.V_dc_volts, 0.0f);
				if( abs(position_abs) < 1){
					chain=reset_angle;
				}
				break;
			case reset_angle:
					if (counter_ip_core_res < 300000)
					{
						counter_ip_core_res++;
					}
					else{
						reset_ip_core_of_encoder_on_D5_3_ip_v25(&Global_Data);
						counter_ip_core_res = 0;
						counter_for_reset = 0;
						counter_wait_pos = 0;
						chain=wait_at_zero_position;
						}
					break;
			case wait_at_zero_position:
				if(abs(position_abs) < 1){
				if (counter_wait_pos<5000){
					counter_wait_pos++;
					}
				else{
					Reset_obs_and_measurements();
					chain=dqn_active;
					}
				}
				else{
				Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, position_ref, position_abs, ext_clamping);
				Global_Data.rasv.dq_reference_current = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, - Global_Data.rasv.n_ref_rpm, Global_Data.rasv.V_dc_volts, 0.0f);
				}
				break;
			default:
				break;
    	}
    	if (abs(position_abs) < 430)
    	{
    	//Global_Data.rasv.n_ref_rpm = uz_PI_Controller_sample(Global_Data.objects.PI_instance, position_ref, position_abs, ext_clamping);
    	//Global_Data.rasv.dq_reference_current = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec,- Global_Data.rasv.n_ref_rpm, Global_Data.rasv.V_dc_volts, 0.0f);
    	Global_Data.rasv.dq_ref_Volts = uz_FOC_sample(Global_Data.objects.FOC_instance, Global_Data.rasv.dq_reference_current, Global_Data.mv.dq_measurement_current, Global_Data.rasv.V_dc_volts, omega_el_rad_per_sec);
        Global_Data.rasv.uvw_ref = uz_transformation_3ph_dq_to_abc(Global_Data.rasv.dq_ref_Volts, Global_Data.av.theta_elec);
        output = uz_FOC_generate_DutyCycles(Global_Data.rasv.uvw_ref, Global_Data.rasv.V_dc_volts);
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
        // change control parameters during runtime
        uz_FOC_set_Kp_id(Global_Data.objects.FOC_instance, Kp_id);
        uz_FOC_set_Kp_iq(Global_Data.objects.FOC_instance, Kp_iq);
        uz_FOC_set_Ki_id(Global_Data.objects.FOC_instance, Ki_id);
        uz_FOC_set_Ki_iq(Global_Data.objects.FOC_instance, Ki_iq);
        uz_SpeedControl_set_Kp(Global_Data.objects.Speed_instance, speed_Kp);
        uz_SpeedControl_set_Ki(Global_Data.objects.Speed_instance, speed_Ki);
    	}
    }
    else
    {
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
    }
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
static void Reset_obs_and_measurements()
{
	Reset_global_Data(&Global_Data);
}
