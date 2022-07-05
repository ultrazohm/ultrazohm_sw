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

// For FOC
#include "../uz/uz_FOC/uz_FOC.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
extern int i;

uz_3ph_alphabeta_t m_alphabeta_currents = {0};

// For IP-Core trans_dq_alphabeta_123
#include "../IP_Cores/uz_trans_dq_alphabeta_123/uz_trans_dq_alphabeta_123.h"
extern uz_dq_alphabeta_123_IPcore_t* test_instance_dq_alphabeta_123;
struct uz_3ph_alphabeta_t alphabeta_currents_dq_alphabeta_123 = {0};
//struct uz_3ph_abc_t abc_currents_dq_alphabeta_123 = {0};
struct uz_3ph_dq_t updated_values={
		.d = 0,
		.q = 0
};

// For IP-Core trans_123_alphabeta_dq
#include "../IP_Cores/uz_123_alphabeta_dq_transformation/uz_123_alphabeta_dq_transformation.h"
extern uz_dqIPcore_t* test_instance_123_alphabeta_dq;
struct uz_3ph_alphabeta_t alphabeta_currents_123_alphabeta_dq = {0};
extern float i_alpha_123_alphabeta_dq;
extern float i_beta_123_alphabeta_dq;
struct uz_3ph_abc_t abc_currents_123_alphabeta_dq = {0};
extern float i_a_123_alphabeta_dq;
extern float i_b_123_alphabeta_dq;
extern float i_c_123_alphabeta_dq;


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

//FOC instance
extern uz_FOC* FOC_instance;
//Speed Controller Instance:
extern uz_SpeedControl_t* speed_control_instance;
//other  FOC variables
struct uz_3ph_dq_t  m_dq0_currents = {0};
struct uz_3ph_dq_t  ref_dq0_currents = {0};	//reference currents for control

struct uz_3ph_dq_t  ref_dq0_voltage = {0};		//reference voltage for pwm/ inverter dq
struct uz_3ph_abc_t ref_abc_voltage = {0};											//abc

struct uz_DutyCycle_t pwm_dutyCycle = {0};			//Duty-Cycle of the three phase pwm

float omega_el_rad_per_sec = 0.0f;
float theta_el_offset = 0.0f;		//additive offset of theta_el

// Measured currents for crude over current protection
struct uz_3ph_abc_t m_abc_currents = {0};
float adc_factor = (20.0f / 2.084f);
float adc_offset = -2.43f;

//Speed-Control:
float n_ref_rpm = 100.0f;
float speed_id_ref_Ampere = 0.0f;
bool ext_clamping = false;

extern struct uz_FOC_config config_FOC;
extern struct uz_PMSM_t config_PMSM;

extern struct uz_dqIPcore_t* dq_Transformator;
uz_3ph_dq_t m_T_dq_currents = {0};
uz_3ph_abc_t m_T_abc_currents = {0};
uz_3ph_alphabeta_t m_T_alphabeta_currents = {0};

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
	if (i==1){
	// Measured currents
	m_abc_currents.a = (Global_Data.aa.A2.me.ADC_B6 +adc_offset)*adc_factor;
	m_abc_currents.b = (Global_Data.aa.A2.me.ADC_B8 +adc_offset)*adc_factor;
	m_abc_currents.c = (Global_Data.aa.A2.me.ADC_B7 +adc_offset)*adc_factor;

	//crude over current protection
	if((fabs(m_abc_currents.a) > 12.0f || fabs(m_abc_currents.b) > 12.0f || fabs(m_abc_currents.c) > 12.0f)&&(updated_values.d !=0 || updated_values.q !=0)) {
		//i++;
		uz_assert(0);
	}
	//else{
	//	i=0;
	//}
	//if(i>=5){
		//uz_assert(0);
	//}

	// Read output ia ib ic from IP-Core trans_123_alphabeta_dq
	abc_currents_123_alphabeta_dq=uz_123_alphabeta_dqIPcore_get_i_abc(test_instance_123_alphabeta_dq);

		//crude over current protection
		//if((fabs(abc_currents_123_alphabeta_dq.a) > 12.0f || fabs(abc_currents_123_alphabeta_dq.b) > 12.0f || fabs(abc_currents_123_alphabeta_dq.c) > 12.0f)&&(updated_values.d !=0 || updated_values.q !=0)) {
		//	i++;}
		//else{
		//	i=0;
		//}
		//if(i>=5){
		//uz_assert(0);
		//}

		i_a_123_alphabeta_dq=abc_currents_123_alphabeta_dq.a;
		i_b_123_alphabeta_dq=abc_currents_123_alphabeta_dq.b;
		i_c_123_alphabeta_dq=abc_currents_123_alphabeta_dq.c;

	// Read output ialpha ibeta from IP_Core trans_123_alphabeta_dq
	alphabeta_currents_123_alphabeta_dq = uz_123_alphabeta_dqIPcore_get_i_alphabeta(test_instance_123_alphabeta_dq);
	i_alpha_123_alphabeta_dq=alphabeta_currents_123_alphabeta_dq.alpha;
	i_beta_123_alphabeta_dq=alphabeta_currents_123_alphabeta_dq.beta;

	// Read output ialpha ibeta from IP-Core trans_dq_alphabeta_123
	 alphabeta_currents_dq_alphabeta_123 = uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(test_instance_dq_alphabeta_123);
	 Global_Data.av.i_alpha_IP_CORE=alphabeta_currents_dq_alphabeta_123.alpha;
	 Global_Data.av.i_beta_IP_CORE=alphabeta_currents_dq_alphabeta_123.beta;

	// Read output ia ib ic from IP-Core trans_dq_alphabeta_123
	// abc_currents_dq_alphabeta_123 = uz_dq_alphabeta_123_IPcore_get_i_abc(test_instance_dq_alphabeta_123);
	// Global_Data.av.i_a_IP_CORE=abc_currents_dq_alphabeta_123.a;
	// Global_Data.av.i_b_IP_CORE=abc_currents_dq_alphabeta_123.b;
	// Global_Data.av.i_c_IP_CORE=abc_currents_dq_alphabeta_123.c;

	 // Update idref iqref from IP-Core trans_dq_alphabeta_123
	 uz_dq_alphabeta_123_IPcore_idref_iqref_update(test_instance_dq_alphabeta_123,updated_values);
	}


    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

	//select right offset and factors for ADC

m_abc_currents.a = (Global_Data.aa.A2.me.ADC_B6 +adc_offset)*adc_factor;
m_abc_currents.b = (Global_Data.aa.A2.me.ADC_B8 +adc_offset)*adc_factor;
m_abc_currents.c = (Global_Data.aa.A2.me.ADC_B7 +adc_offset)*adc_factor;

//write currents into Global_Data
Global_Data.av.I_U = m_abc_currents.a;
Global_Data.av.I_V = m_abc_currents.b;
Global_Data.av.I_W = m_abc_currents.c;

//transform meassured currents to dq-System
m_dq0_currents = uz_transformation_3ph_abc_to_dq(m_abc_currents, Global_Data.av.theta_elec + theta_el_offset);

Global_Data.av.I_d = m_dq0_currents.d;
Global_Data.av.I_q = m_dq0_currents.q;

omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed*config_FOC.config_PMSM.polePairs*2.0f*M_PI/60;


//alpha_beta Ströme als Vergleich
m_alphabeta_currents = uz_transformation_3ph_abc_to_alphabeta(m_abc_currents);
Global_Data.av.I_alpha = m_alphabeta_currents.alpha;
Global_Data.av.I_beta = m_alphabeta_currents.beta;

//Set new control parameter from javascope
uz_FOC_set_Kp_id(FOC_instance, Global_Data.cp.kp_d);
uz_FOC_set_Kp_iq(FOC_instance, Global_Data.cp.kp_q);
uz_FOC_set_Ki_id(FOC_instance, Global_Data.cp.ki_d);
uz_FOC_set_Ki_iq(FOC_instance, Global_Data.cp.ki_q);

uz_SpeedControl_set_Ki(speed_control_instance, Global_Data.cp.ki_speed);
uz_SpeedControl_set_Kp(speed_control_instance, Global_Data.cp.kp_speed);


    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

		//Call FOC-algorithm
	ref_dq0_voltage = uz_FOC_sample(FOC_instance, ref_dq0_currents, m_dq0_currents, Global_Data.av.U_ZK, omega_el_rad_per_sec);
		//Transform dq to abc-voltage
	ref_abc_voltage = uz_transformation_3ph_dq_to_abc(ref_dq0_voltage, Global_Data.av.theta_elec + theta_el_offset);
		//calculate pwm-dutyclcles for inverter
	pwm_dutyCycle = uz_FOC_generate_DutyCycles(ref_abc_voltage, Global_Data.av.U_ZK);

	Global_Data.rasv.halfBridge1DutyCycle = pwm_dutyCycle.DutyCycle_U;
	Global_Data.rasv.halfBridge2DutyCycle = pwm_dutyCycle.DutyCycle_V;
	Global_Data.rasv.halfBridge3DutyCycle = pwm_dutyCycle.DutyCycle_W;

    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

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
