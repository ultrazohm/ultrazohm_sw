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
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_Transformation/uz_Transformation.h"


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
extern float CurrentOn_Angle_deg;
extern float CurrentOff_Angle_deg;
extern float CurrentOn_Reference_A;
extern float i_ref;
extern float PIon_Angle_Active_deg;
extern float PIon_Angle_Inactive_deg;
extern float flg_theta_mech_prediction;
extern float flg_InductanceDeviation_Compensation;
extern float flg_Inductance_PreControl;

struct uz_3ph_abc_t ref_voltage = {0};
float theta_m_deg = 0.0f;
struct uz_DutyCycle_t output = {0};
int flg_PI_on_active = 0U;			// local variable for activation of rising/falling current control
float L_min = 1*0.470f/1000.0f;
float L_max = 1*2.0f/1000.0f;
//float R = 2.0f*0.044;		// Serial
float R = 0.022;
float i_ref_last = 0.0f;
float u_precontrol = 0.0f;
float Inductance_deviation = 0.001f*(2.0f-0.47f)/(80.0f*M_PI/180.0f);	// H/rad 	//Parallel
int u_precontrol_counter = 0;

#define PHASE_CURRENT_CONV	0.5f*37.373/2.0f	//Parallel: factor of 0.5 to get current of each coil
#define PHASE_VOLTAGE_CONV		250.0f
#define PHASE_VOLT_OFF		0.0f
#define INV_TEMP_CONV		1.0f
#define DC_VOLT_CONV		250.0f
#define DC_VOLT_OFF			250.0f

#define MAX_CURRENT_ASSERTION 45.0f
#define MAX_SPEED_ASSERTION	  3500.0f
#define T_dead_prediction	1.0f/SAMPLE_FREQUENCY



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
    update_position_and_speed_of_resolverIP(&Global_Data);

    // convert ADC readings to currents in Amps
    // Connect coil with phase a1 and b1
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_B6 * PHASE_CURRENT_CONV;
    // convert ADC readings to dc link voltages
    Global_Data.av.U_ZK = -1.0f * Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV - DC_VOLT_OFF;

    // Read phase voltages
    Global_Data.av.u_a1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLTAGE_CONV - PHASE_VOLT_OFF;
    Global_Data.av.u_b1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_VOLTAGE_CONV - PHASE_VOLT_OFF;
    Global_Data.av.u_c1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_VOLTAGE_CONV - PHASE_VOLT_OFF;

    // Read temperature of inverter
    Global_Data.av.inverter_temp = Global_Data.aa.A1.me.ADC_A4 * PHASE_VOLTAGE_CONV - PHASE_VOLT_OFF;

    // filter values
    Global_Data.av.i_a1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a1, Global_Data.av.i_a1);
    //Global_Data.av.i_b1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b1, Global_Data.av.i_b1);
    //Global_Data.av.i_c1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c1, Global_Data.av.i_c1);
    Global_Data.av.U_ZK_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_dc, Global_Data.av.U_ZK);

    Global_Data.av.U_ZK_filt = 500.0f;

	if(fabs(Global_Data.av.i_a1_filt) > MAX_CURRENT_ASSERTION || fabs(Global_Data.av.i_b1_filt) > MAX_CURRENT_ASSERTION || fabs(Global_Data.av.i_c1_filt) > MAX_CURRENT_ASSERTION || fabs(Global_Data.av.mechanicalRotorSpeed) > MAX_SPEED_ASSERTION) {
    	// Assertion
    	output.DutyCycle_U=0.0f;
    	output.DutyCycle_V=0.0f;
    	output.DutyCycle_W=0.0f;
    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
    	ultrazohm_state_machine_set_stop(true);
	}

    // theta offset and scaling to el. angle
	Global_Data.av.theta_mech_unwraped = Global_Data.av.theta_mech - Global_Data.av.theta_offset;
	// Wrap mechanical angle from 0...2pi
	if (Global_Data.av.theta_mech_unwraped < 0.0f){
		Global_Data.av.theta_m_offset_comp = Global_Data.av.theta_mech_unwraped + (2*M_PI);
	} else{
		Global_Data.av.theta_m_offset_comp = Global_Data.av.theta_mech_unwraped;
	}
    //Global_Data.av.theta_m_offset_comp = Global_Data.av.theta_mech - Global_Data.av.theta_offset;
    Global_Data.av.theta_elec = Global_Data.av.theta_m_offset_comp * Global_Data.av.polepairs;


    //Prediction of mechanical angle
    if (flg_theta_mech_prediction == 1.0f || flg_Inductance_PreControl == 1.0f){
    	theta_m_deg = Global_Data.av.theta_m_offset_comp * 180.0f/M_PI + Global_Data.av.mechanicalRotorSpeed/60.0f * 360.0f * T_dead_prediction;
    } else{
    	theta_m_deg = Global_Data.av.theta_m_offset_comp * 180.0f/M_PI;
    }

    //Set active Controller
    if((theta_m_deg >= PIon_Angle_Active_deg && theta_m_deg <= PIon_Angle_Inactive_deg) || (theta_m_deg >= (PIon_Angle_Active_deg + 180.0f) && theta_m_deg <= (PIon_Angle_Inactive_deg + 180.0f))){
    	// Controller for low inductance
    	flg_PI_on_active = 1U;
    	uz_PI_Controller_reset(Global_Data.objects.PI_cntr1_off);
    } else {
    	// Controller for high inductance
		flg_PI_on_active = 0U;
		uz_PI_Controller_reset(Global_Data.objects.PI_cntr1_on);
    }


	// Set precontroller to zero
    u_precontrol = 0.0f;
    // Set Current reference value
    if((theta_m_deg >= CurrentOn_Angle_deg && theta_m_deg <= CurrentOff_Angle_deg) || (theta_m_deg >= (CurrentOn_Angle_deg + 180.0f) && theta_m_deg <= (CurrentOff_Angle_deg + 180.0f))){
    	if (flg_Inductance_PreControl == 1.0f && u_precontrol_counter < 1 && i_ref_last == 0.0f){
    		// Set reference value for controller to zero
    		i_ref = 0.0;
    		// Calculate voltage of u = R * i + L * di/dt for next timestep
    		u_precontrol = L_min * CurrentOn_Reference_A/T_dead_prediction + R * CurrentOn_Reference_A;
    		u_precontrol_counter++;
    	} else{
        	i_ref = CurrentOn_Reference_A;
        	u_precontrol_counter = 0;
    	}
    } else{
    	if (flg_Inductance_PreControl == 1.0f && i_ref_last != 0.0f && u_precontrol_counter < 1){
    		// Leave reference value of controller at last setpoint
    		i_ref = CurrentOn_Reference_A;
    		// Calculate voltage of u = R * i + L * di/dt for next timestep
			u_precontrol = -1.0*(L_max * CurrentOn_Reference_A/T_dead_prediction);
			u_precontrol_counter++;
    	} else{
    		i_ref = 0.0f;
    		u_precontrol_counter=0;
    	}
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	// One controller used for both coils in series
    	if (flg_PI_on_active == 1U){
    		ref_voltage.a = uz_PI_Controller_sample(Global_Data.objects.PI_cntr1_on, i_ref, Global_Data.av.i_a1, false);
    		// Inductance deviation compensation: u_ind = dL/dt * i
    		if (flg_InductanceDeviation_Compensation == 1.0f){
    			ref_voltage.a = ref_voltage.a + Inductance_deviation * Global_Data.av.mechanicalRotorSpeed/60.0 * 2.0 * M_PI * Global_Data.av.i_a1_filt;
    		}
    	} else{
    		ref_voltage.a = uz_PI_Controller_sample(Global_Data.objects.PI_cntr1_off, i_ref, Global_Data.av.i_a1, false);
    	}
    	if (flg_Inductance_PreControl == 1.0f){
			ref_voltage.a = ref_voltage.a + u_precontrol;
    	}
    	ref_voltage.b = 0.0f;
    	ref_voltage.c = 0.0f;

    	i_ref_last = i_ref;


    	output = uz_FOC_generate_DutyCycles(ref_voltage, Global_Data.av.U_ZK_filt);

    	Global_Data.rasv.halfBridge1DutyCycle = output.DutyCycle_U;
    	Global_Data.rasv.halfBridge2DutyCycle = output.DutyCycle_V;
    	//Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	//Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;

    } else{
    	output.DutyCycle_U=0.0f;
    	output.DutyCycle_V=0.0f;
    	output.DutyCycle_W=0.0f;
    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
    	uz_PI_Controller_reset(Global_Data.objects.PI_cntr1_on);
    	uz_PI_Controller_reset(Global_Data.objects.PI_cntr1_off);
    	ref_voltage.a = 0.0f;
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
