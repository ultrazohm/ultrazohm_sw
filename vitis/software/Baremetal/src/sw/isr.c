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
uz_6ph_dq_t CIL_i_dqxy_meas = {0};
uz_6ph_abc_t REAL_i_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t CIL_v_dq_reference = {0};
uz_3ph_dq_t CIL_v_xy_reference = {0};
uz_3ph_dq_t CIL_v_z1z2_reference = {0};
uz_3ph_dq_t i_dq_reference = {0};
uz_3ph_dq_t i_xy_reference = {0};
uz_3ph_dq_t i_z1z2_reference = {0};
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
#define PHASE_CURRENT_CONV	16.75f
#define DC_VOLT_CONV_1		140.27f
#define DC_VOLT_OFF_1		450.25f
#define DC_VOLT_CONV_2		141.28f
#define DC_VOLT_OFF_2		452.17f
// software limits
#define MAX_PHASE_CURRENT_AMP  20.0f
#define MAX_DC_VOLT 590.0f
#define MAX_TEMP_DEG 90.0f

//neutral config
#define NEUTRAL_CONFIG 1U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_a1c1 = 0.0f;
float u_a2c2 = 0.0f;


uz_6ph_abc_t zero_offset = {0};
bool zero_finished = false;
uz_6ph_abc_t zero_offset_function(bool* flag);
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
    	//Read out speed&position
        Global_Data.av.resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d2);
        Global_Data.av.theta_elec = Global_Data.av.resolver_outputs.position_el_2pi;
        Global_Data.av.theta_mech = Global_Data.av.resolver_outputs.position_mech_2pi;
        Global_Data.av.omega_mech = Global_Data.av.resolver_outputs.omega_mech_rad_s;
        Global_Data.av.omega_elec = Global_Data.av.omega_mech * polepairs;
        Global_Data.av.mechanicalRotorSpeed = (Global_Data.av.omega_mech * 60.0f) / (2.0f * UZ_PIf);

        // Read out and convert ADC readings to currents in Amps
        Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
        Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
        Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_CURRENT_CONV;
        Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
        Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
        Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
        Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_CURRENT_CONV;
        Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

        // Read out and convert ADC readings to voltages
        Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A4 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
        Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.a1;
        Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.b1;
        Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.c1;
        Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A4 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
        Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.a2;
        Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.b2;
        Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.c2;
        // zero voltage reading at startup
            if(!zero_finished){
            	zero_offset = zero_offset_function(&zero_finished);
            }

        //Read out inverter temp
        Global_Data.av.temp_VSI_1 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.pwm_duty_freq_detection_VSI_1).TempDegreesCelsius;
        Global_Data.av.temp_VSI_2 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.pwm_duty_freq_detection_VSI_2).TempDegreesCelsius;
        // check current limit
        if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
        		fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
        		uz_assert(0);
        }
        // check DC Bus
        if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
        		uz_assert(0);
        }
        // check inverter temp
        if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG) {
        	//uz_assert(0);
        }

        //write to structs
        REAL_i_abc_meas.a1 = Global_Data.av.i_a1;
        REAL_i_abc_meas.b1 = Global_Data.av.i_b1;
        REAL_i_abc_meas.c1 = Global_Data.av.i_c1;
        REAL_i_abc_meas.a2 = Global_Data.av.i_a2;
        REAL_i_abc_meas.b2 = Global_Data.av.i_b2;
        REAL_i_abc_meas.c2 = Global_Data.av.i_c2;

        // calc u neutral voltage
        switch(NEUTRAL_CONFIG){
        case 1U:{
        	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1 + Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2) / 6.0f;
        	u_n2 = u_n1;
        	break;
        }
        case 2U:{
        	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1)/3.0f;
        	u_n2 = (Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2)/3.0f;
        	break;
        }
        default: break;
        }

        // calc phase voltages with neutral voltage
        REAL_v_abc_meas.a1 = Global_Data.av.v_a1 - u_n1;
        REAL_v_abc_meas.b1 = Global_Data.av.v_b1 - u_n1;
        REAL_v_abc_meas.c1 = Global_Data.av.v_c1 - u_n1;
        REAL_v_abc_meas.a2 = Global_Data.av.v_a2 - u_n2;
        REAL_v_abc_meas.b2 = Global_Data.av.v_b2 - u_n2;
        REAL_v_abc_meas.c2 = Global_Data.av.v_c2 - u_n2;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        if(select_CIL) {
        	i_dq_reference.d = i_d_ref;
        	i_dq_reference.q = i_q_ref;
        	i_xy_reference.d = i_X_ref;
        	i_xy_reference.q = i_Y_ref;
        	CIL_omega_mech = (n_ref_rpm / 60.0f) * 2.0f * UZ_PIf;
        	if(reset) {
        		uz_pmsm_model6ph_dq_reset(Global_Data.objects.CIL_pmsm);  // use reset variable to reset integrators from Expressions
        	}
        	uz_pmsm_model6ph_dq_set_inputs_general(Global_Data.objects.CIL_pmsm,CIL_omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
        	uz_pmsm_model6ph_dq_set_voltage(Global_Data.objects.CIL_pmsm,v_dqxy_limited_volts);              // set input voltage
        	CIL_out_general = uz_pmsm_model6ph_dq_get_outputs_general(Global_Data.objects.CIL_pmsm);    // read out resulting general outputs
        	CIL_i_dqxy_meas = uz_pmsm_model6ph_dq_get_output_currents(Global_Data.objects.CIL_pmsm);   // read out actual currents
        	Global_Data.av.mechanicalRotorSpeed = (CIL_out_general.omega_mech * 60.0f) / (2.0f * UZ_PIf);
        	omega_el_rad_per_sec = CIL_out_general.omega_mech * polepairs;
        	CIL_i_dq_meas.d = CIL_i_dqxy_meas.d;
        	Global_Data.av.I_d = CIL_i_dqxy_meas.d;
        	CIL_i_dq_meas.q = CIL_i_dqxy_meas.q;
        	Global_Data.av.I_q = CIL_i_dqxy_meas.q;
        	CIL_i_xy_meas.d = CIL_i_dqxy_meas.x;
        	Global_Data.av.I_X = CIL_i_dqxy_meas.x;
        	CIL_i_xy_meas.q = CIL_i_dqxy_meas.y;
        	Global_Data.av.I_Y = CIL_i_dqxy_meas.y;
        	CIL_i_z1z2_meas.d = CIL_i_dqxy_meas.z1;
        	CIL_i_z1z2_meas.q = CIL_i_dqxy_meas.z2;
        	if(select_CurrentControl) {
        		CIL_v_dq_reference = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, i_dq_reference, CIL_i_dq_meas, V_DC_Volts, omega_el_rad_per_sec);
        		CIL_v_xy_reference = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, i_xy_reference, CIL_i_xy_meas, V_DC_Volts, omega_el_rad_per_sec);
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

uz_6ph_abc_t zero_offset_function(bool* flag){
	static uz_6ph_abc_t data[1000];
	static uz_6ph_abc_t sum = {0};
	static int i = 0;
	uz_6ph_abc_t out = {0};
	data[i].a1 = Global_Data.av.v_a1;
	sum.a1 = sum.a1 + data[i].a1;
	data[i].b1 = Global_Data.av.v_b1;
	sum.b1 = sum.b1 + data[i].b1;
	data[i].c1 = Global_Data.av.v_c1;
	sum.c1 = sum.c1 + data[i].c1;
	data[i].a2 = Global_Data.av.v_a2;
	sum.a2 = sum.a2 + data[i].a2;
	data[i].b2 = Global_Data.av.v_b2;
	sum.b2 = sum.b2 + data[i].b2;
	data[i].c2 = Global_Data.av.v_c2;
	sum.c2 = sum.c2 + data[i].c2;
	i++;
	if(i==999){
		out.a1 = sum.a1/i;
		out.b1 = sum.b1/i;
		out.c1 = sum.c1/i;
		out.a2 = sum.a2/i;
		out.b2 = sum.b2/i;
		out.c2 = sum.c2/i;
		*flag = true;
	}
	return out;
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
