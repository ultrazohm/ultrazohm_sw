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

# define MAX_CURRENT 5.0f
# define CONTROL_FREQUENCY 10000



//============== Declares for PMSM ===========
// FOC instances and configs
extern uz_pmsmModel_t *pmsm;
extern uz_CurrentControl_t *CurrentControl_instance;

// FOC structs
struct uz_3ph_dq_t i_dq_ref_javascope = {0};
struct uz_3ph_dq_t i_dq_CIL_Ampere = {0};
struct uz_3ph_dq_t i_dq_reference_Ampere = {0};
struct uz_3ph_dq_t measured_currents_Amp = {0};
struct uz_3ph_dq_t CurrentControl_output_Volts = {0};

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

// Inverster Measurement
struct uz_3ph_abc_t i_abc_actual_Ampere = {0};
struct uz_3ph_abc_t v_abc_actual_Volts = {0};
struct uz_3ph_dq_t i_dq_actual_Ampere = {0};
struct uz_3ph_dq_t v_dq_actual_Volts = {0};
struct uz_DutyCycle_t DutyCycle_output = {0};

// variables for the simu mode
bool select_automatic_idiq = false;
bool use_CiL = false;
bool use_PI = false;
bool use_Motor = false;

// FOC variables
float n_rpm_ref_javascope = 0.0f;
float poles = 3.0f;
float theta_elec_offset = 5.4f;

float start_marker=0.0f;
int k = 0;
int idx = 0;



//Reference profile values for idq
float ref_iq[10] = {
	0, 1,  2, 3, 2.5, 1.5, 1, 3.5, 2, 1
};

float ref_id[10] ={
	0, -1, -2, -0.5, -1, -1, 0, -0.5, -2, -2
};

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

    update_speed_and_position_of_encoder_on_D5(&Global_Data);


    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // whether to use profile or javascope values for idq reference
    	if (select_automatic_idiq) {
    		start_marker = 1.0f;;
    		if ((k%200)==0) {
    			if (idx >= (sizeof(ref_id)/sizeof(ref_id[0]))) {
    				i_dq_reference_Ampere.d = 0;
    				i_dq_reference_Ampere.q = 0;
    			} else {
    				i_dq_reference_Ampere.d = ref_id[idx];
    				i_dq_reference_Ampere.q = ref_iq[idx];
    				idx+=1;
    			}
    		}
    		k+=1;
    	} else {
    		i_dq_reference_Ampere = i_dq_ref_javascope;
    		k=0;
    		idx=0;
    	}

    	if (use_CiL) { //Controler-in the -Loop

    	    	 	   uz_pmsmModel_trigger_input_strobe(pmsm);		//Signalisiert dem PMSM-Modell, dass neue Eingangsdaten anliegen
    	    	       uz_pmsmModel_trigger_output_strobe(pmsm);	//Signalisiert, dass Ausgangsdaten aktualisiert wurden und abgeholt werden können
    	    	       pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);	//ruft die neuesten Simulationsdaten des PMSM-Modells ab

    	    	       i_dq_CIL_Ampere.d = pmsm_outputs.i_d_A;		//d-strom aus der simulation gespeichert
    	    	       i_dq_CIL_Ampere.q = pmsm_outputs.i_q_A;		//q-strom aus der simulation gespeichert

    	    	       Global_Data.av.I_d = pmsm_outputs.i_d_A;		//d-strom aus der simulation in Global_Data gespeichert
    	    	       Global_Data.av.I_q = pmsm_outputs.i_q_A;		//q-strom aus der simulation in Global_Data gespeichert
    	    	       Global_Data.av.omega_m = pmsm_outputs.omega_mech_1_s;	//mechanische rotorderhzahl 1/s in Global_Data
    	    	       Global_Data.av.mechanicalRotorSpeed = (pmsm_outputs.omega_mech_1_s/(2.0f*M_PI)) * 60.0f;	//mechsnische rotordrehzahl in rpm (U/min)
    	    	       Global_Data.av.omega_elec = pmsm_outputs.omega_mech_1_s * poles;	//elektrische drehzahl
    	    	       measured_currents_Amp.d = pmsm_outputs.i_d_A;
    	    	       measured_currents_Amp.q = pmsm_outputs.i_q_A;



    if (current_state==control_state)
    {




    	       CurrentControl_output_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_dq_reference_Ampere, measured_currents_Amp, 48.0f, Global_Data.av.omega_elec);
    	       pmsm_inputs.v_q_V=CurrentControl_output_Volts.q;
    	       pmsm_inputs.v_d_V=CurrentControl_output_Volts.d;
    	       Global_Data.av.U_q = CurrentControl_output_Volts.q;
    	       Global_Data.av.U_d = CurrentControl_output_Volts.d;
    	       pmsm_inputs.omega_mech_1_s = ( n_rpm_ref_javascope / 60.0f ) * 2.0f * M_PI;
    	       uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);


    	}
   }


    	if (use_Motor) {

    	    	//Global_Data.av.theta_mech = Global_Data.av.theta_mech;	//mechanischer winkel
    	    	Global_Data.av.omega_elec = Global_Data.av.mechanicalRotorSpeed*2.0f*M_PI/60.0f * poles;	//elektrische drehzahl
    	    	Global_Data.av.theta_elec = fmodf(Global_Data.av.theta_elec * poles,2*M_PI) - theta_elec_offset;  // changed the encoder function to write the theta onto theta_mech - mechanischer winkel
    	    	Global_Data.av.theta_elec_adv = (1.5f*(1.0f / CONTROL_FREQUENCY) * Global_Data.av.omega_elec) + Global_Data.av.theta_elec;	// angle advance 3/2*T_a*omega - elektrischer winkelvorschub

    	    	//Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    	    	//Overtemperature for H1
    	    	if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
    	    	    ultrazohm_state_machine_set_error(true);
    	    	 }
    	    	//Overtemperature for H2
    	    	 if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    	    	    ultrazohm_state_machine_set_error(true);
    	    	 }
    	    	//Overtemperature for H3
    	    	if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    	    	    ultrazohm_state_machine_set_error(true);
    	    	}

    	    	// Read measurment data of the inverter
    	    	Global_Data.av.I_a = Global_Data.aa.A2.me.ADC_A4 * 12.5f;
    	    	Global_Data.av.I_b = Global_Data.aa.A2.me.ADC_A3 * 12.5f;
    	    	Global_Data.av.I_c = Global_Data.aa.A2.me.ADC_A2 * 12.5f;
    	    	Global_Data.av.I_DC = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    	    	Global_Data.av.U_a = Global_Data.aa.A2.me.ADC_B8 * 12.0f;
    	    	Global_Data.av.U_b = Global_Data.aa.A2.me.ADC_B7 * 12.0f;
    	    	Global_Data.av.U_c = Global_Data.aa.A2.me.ADC_B6 * 12.0f;
    	    	Global_Data.av.U_ZK = Global_Data.aa.A2.me.ADC_A1 * 12.0f;

    	    	// check for current limit
    	    	 if (fabs(Global_Data.av.I_a) > MAX_CURRENT || fabs(Global_Data.av.I_b) > MAX_CURRENT || fabs(Global_Data.av.I_c) > MAX_CURRENT) {
    	    	    	    	    		ultrazohm_state_machine_set_stop(true);
    	    	    	    	    	}

    	    	// assign measurements to motor control structs
    	    	i_abc_actual_Ampere.a = Global_Data.av.I_a;
    	    	i_abc_actual_Ampere.b = Global_Data.av.I_b;
    	    	i_abc_actual_Ampere.c = Global_Data.av.I_c;

    	    	v_abc_actual_Volts.a = Global_Data.av.U_a;
    	    	v_abc_actual_Volts.b = Global_Data.av.U_b;
    	    	v_abc_actual_Volts.c = Global_Data.av.U_c;

    	    	i_dq_actual_Ampere = uz_transformation_3ph_abc_to_dq(i_abc_actual_Ampere, Global_Data.av.theta_elec);
    	    	v_dq_actual_Volts = uz_transformation_3ph_abc_to_dq(v_abc_actual_Volts, Global_Data.av.theta_elec);

    	    	Global_Data.av.I_d = i_dq_actual_Ampere.d;
    	    	Global_Data.av.I_q = i_dq_actual_Ampere.q;

    	    	Global_Data.av.U_d = v_dq_actual_Volts.d;
    	    	Global_Data.av.U_q = v_dq_actual_Volts.q;







    	    	if (current_state == running_state || current_state == control_state) {
    	    				// enable inverter adapter hardware
    	    				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	    			} else {
    	    				// disable inverter adapter hardware
    	    				uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    	    			}

    	    	if (current_state==control_state) {

    	    	    			CurrentControl_output_Volts = uz_CurrentControl_sample(CurrentControl_instance, i_dq_reference_Ampere, i_dq_actual_Ampere, Global_Data.av.U_ZK, Global_Data.av.omega_elec);  // 1. Stromregler (PI im dq-System)
    	    	    			DutyCycle_output = uz_Space_Vector_Modulation(CurrentControl_output_Volts, Global_Data.av.U_ZK, Global_Data.av.theta_elec_adv);  // 2. Raumzeigermodulation (SVM)

    	    	    			Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.DutyCycle_A;
    	    					Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.DutyCycle_B;
    	    					Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.DutyCycle_C;



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
