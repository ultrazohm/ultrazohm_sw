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
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_Transformation/uz_Transformation.h"

#include "../uz/uz_FOC/uz_FOC.h"
#include "../uz/uz_filter/uz_filter.h"


#include "../uz/uz_VSD_6ph_FD_control/uz_VSD_6ph_FD.h"
#include "../uz/uz_VSD_6ph_FD_control/uz_VSD_6ph_ML_MT_Control.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;



// general variables/ Setting:

int N1N2 = 1;	// Configuration of neutral points (1 = 1N, 1 neutral point; 2 = 2N, 2 neutral points)
int ML = 1;		// Optimization during Open-Phase-Fault (1=ML, Minimum Loss; 0=MT, Maximum Torque)

// omega and theta
float theta_ = 0;
float omega_el_rad_per_sec = 0.0f;


//ParaID
#include "../uz/uz_ParameterID/uz_ParameterID_6ph.h"
extern uz_ParameterID_Data_t ParaID_Data;
extern uz_ParameterID_6ph_t* ParameterID;
uz_6ph_dq_t paraid_temp_dq_currents = {0};
//RaraID end


// variables for measured currents: m_xxxx
// variables for reference currents for control: ref_xxxx

uz_6ph_abc_t m_6ph_abc_currents = {0};
uz_6ph_alphabeta_t m_6ph_alphabeta_currents = {0};

uz_3ph_alphabeta_t m_alphabeta_currents = {0};
uz_3ph_dq_t m_dq_currents = {0};

uz_3ph_abc_t ref_volage_phase_set1 = {0};
uz_3ph_abc_t ref_volage_phase_set2 = {0};


// Inverter, PWM etc.:

struct uz_DutyCycle_t dutyCycles_set1 = {0};
struct uz_DutyCycle_t dutyCycles_set2 = {0};

extern struct uz_d_gan_inverter_t* gan_inverter_D3;
extern struct uz_d_gan_inverter_t* gan_inverter_D4;

// voltage measurement
uz_6ph_abc_t u_phase_UDC = {0};
uz_6ph_abc_t u_line_line = {0};
float ADC_conv_faktor_sys1 = -1.0f*36.0f/2.77f; //UDC!!


// Temp
uz_3ph_abc_t input1 = {0};
uz_3ph_abc_t input2 = {0};
uz_6ph_alphabeta_t temp_sept = {0};
uz_6ph_abc_t phase_ref_volts = {0};

float polepairs = 5.0f;

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

	omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed*polepairs*2.0f*M_PI/60;


	//ParaID
	paraid_temp_dq_currents = uz_transformation_asym30deg_6ph_abc_to_dq(m_6ph_abc_currents, Global_Data.av.theta_elec);
	paraid_temp_dq_currents.d = m_6ph_alphabeta_currents.alpha;
	paraid_temp_dq_currents.q = m_6ph_alphabeta_currents.beta;

	ParaID_Data.ActualValues.i_abc_6ph = m_6ph_abc_currents;
	ParaID_Data.ActualValues.i_dq_6ph = paraid_temp_dq_currents;
	ParaID_Data.ActualValues.v_abc_6ph = uz_line_line_to_abc(u_line_line);
	ParaID_Data.ActualValues.v_dq_6ph = uz_transformation_asym30deg_6ph_abc_to_dq(ParaID_Data.ActualValues.v_abc_6ph, 0.0f);
	ParaID_Data.ActualValues.V_DC = Global_Data.av.U_ZK;
	ParaID_Data.ActualValues.omega_m = Global_Data.av.mechanicalRotorSpeed*2.0f*M_PI/60;
	ParaID_Data.ActualValues.omega_el = omega_el_rad_per_sec;
	ParaID_Data.ActualValues.theta_el = Global_Data.av.theta_elec;
	ParaID_Data.ActualValues.theta_m = Global_Data.av.theta_mech;
	//ParaID ende


////////////////////////////////////////////////////////////////////////////////////////////////////
////			Phase current measurement and various transformations (dq, VSD)					////
////////////////////////////////////////////////////////////////////////////////////////////////////

	// ADC values from voltage Measurement
	u_phase_UDC.a1 = Global_Data.aa.A3.me.ADC_A4 * ADC_conv_faktor_sys1;
	u_phase_UDC.b1 = Global_Data.aa.A3.me.ADC_A3 * ADC_conv_faktor_sys1;
	u_phase_UDC.c1 = Global_Data.aa.A3.me.ADC_A2 * ADC_conv_faktor_sys1;
	u_phase_UDC.a2 = Global_Data.aa.A3.me.ADC_B8 * ADC_conv_faktor_sys1;
	u_phase_UDC.b2 = Global_Data.aa.A3.me.ADC_B7 * ADC_conv_faktor_sys1;
	u_phase_UDC.c2 = Global_Data.aa.A3.me.ADC_B6 * ADC_conv_faktor_sys1;

	// calculate line-to-line voltage
	u_line_line.a1 = u_phase_UDC.a1-u_phase_UDC.b1;
	u_line_line.b1 = u_phase_UDC.b1-u_phase_UDC.c1;
	u_line_line.c1 = u_phase_UDC.c1-u_phase_UDC.a1;
	u_line_line.a2 = u_phase_UDC.a2-u_phase_UDC.b2;
	u_line_line.b2 = u_phase_UDC.b2-u_phase_UDC.c2;
	u_line_line.c2 = u_phase_UDC.c2-u_phase_UDC.a2;

	//assign ADC values to motor current variables
    m_6ph_abc_currents.a1 = (-1.0*Global_Data.aa.A2.me.ADC_A4);
	m_6ph_abc_currents.b1 = (-1.0*Global_Data.aa.A2.me.ADC_A3);
	m_6ph_abc_currents.c1 = (-1.0*Global_Data.aa.A2.me.ADC_A2);
	m_6ph_abc_currents.a2 = (-1.0*Global_Data.aa.A2.me.ADC_B8);
	m_6ph_abc_currents.b2 = (-1.0*Global_Data.aa.A2.me.ADC_B7);
	//m_6ph_abc_currents.c2 = (-1.0*Global_Data.aa.A2.me.ADC_B6);

	m_6ph_abc_currents.c2 = - m_6ph_abc_currents.a1 - m_6ph_abc_currents.b1 - m_6ph_abc_currents.c1 -m_6ph_abc_currents.a2 - m_6ph_abc_currents.b2;


	//over current protection in Software:
	if(fabs(m_6ph_abc_currents.a1) > 30.0f || fabs(m_6ph_abc_currents.b1) > 30.0f || fabs(m_6ph_abc_currents.c1) > 30.0f || fabs(m_6ph_abc_currents.a2) > 30.0f || fabs(m_6ph_abc_currents.b2) > 30.0f || fabs(m_6ph_abc_currents.c2) > 30.0f){

		// set all dutycycles to 0
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

		//write duty-cycles to 0 to disable inverter
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);	//D3 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);	//D4 gan inv
	    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

		uz_assert(0);
	}


	//write phase currents into global_data-struct
	Global_Data.av.I_U = m_6ph_abc_currents.a1;
	Global_Data.av.I_V = m_6ph_abc_currents.b1;
	Global_Data.av.I_W = m_6ph_abc_currents.c1;
	Global_Data.av.I_X = m_6ph_abc_currents.a2;
	Global_Data.av.I_Y = m_6ph_abc_currents.b2;
	Global_Data.av.I_Z = m_6ph_abc_currents.c2;


	// VSD-Transform of currents:
	//Transform phase-currents to alpha-beta-x-y-z1-z2 and write to global_data-struct
	m_6ph_alphabeta_currents = uz_transformation_asym30deg_6ph_abc_to_alphabeta(m_6ph_abc_currents);

	Global_Data.av.I_alpha = m_6ph_alphabeta_currents.alpha;
	Global_Data.av.I_beta = m_6ph_alphabeta_currents.beta;
	Global_Data.av.I_x = m_6ph_alphabeta_currents.x;
	Global_Data.av.I_y = m_6ph_alphabeta_currents.y;
	Global_Data.av.I_z1 = m_6ph_alphabeta_currents.z1;
	Global_Data.av.I_z2 = m_6ph_alphabeta_currents.z2;

	//calculate meassured dq-currents
	m_alphabeta_currents.alpha = m_6ph_alphabeta_currents.alpha;
	m_alphabeta_currents.beta = m_6ph_alphabeta_currents.beta;
	m_dq_currents = uz_transformation_3ph_alphabeta_to_dq(m_alphabeta_currents, Global_Data.av.theta_elec + Global_Data.av.theta_offset);

	Global_Data.av.I_d = m_dq_currents.d;
	Global_Data.av.I_q = m_dq_currents.q;



////////////////////////////////////////////////////////////////////////////////////////////////////
////			Stuff for the inverter															////
////////////////////////////////////////////////////////////////////////////////////////////////////


	// read data from gan inverters:
	uz_d_gan_inverter_update_states(gan_inverter_D3);
	uz_d_gan_inverter_update_states(gan_inverter_D4);

	Global_Data.objects.gan_inverter_outputs_D3 = uz_d_gan_inverter_get_outputs(gan_inverter_D3);
	Global_Data.objects.gan_inverter_outputs_D4 = uz_d_gan_inverter_get_outputs(gan_inverter_D4);


	platform_state_t current_state=ultrazohm_state_machine_get_state();

	//enable gan inverters if system enable
	if (current_state == idle_state || current_state == error_state) {
		//Set Data To UZ_D_GaN_Inverter
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_1_UZ_D_GAN_INVERTER_0_BASEADDR, false);
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR, false);
	} else if (current_state == running_state || current_state == control_state) { //Call this function only once. If there was an error, "enableSystem " must be reseted!
		//Set Data To UZ_D_GaN_Inverter
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_1_UZ_D_GAN_INVERTER_0_BASEADDR, true);
		uz_d_gan_inverter_hw_set_PWM_EN(XPAR_UZ_DIGITAL_ADAPTER_UZ_D_GAN_INVERTER_UZ_D_GAN_INVERTER_0_BASEADDR, true);
	}


	//default dutyclcles:
	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.ref_halfBridge1DutyCycle;
	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.ref_halfBridge2DutyCycle;
	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.ref_halfBridge3DutyCycle;
	Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.ref_halfBridge4DutyCycle;
	Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.ref_halfBridge5DutyCycle;
	Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.ref_halfBridge6DutyCycle;
	Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.ref_halfBridge7DutyCycle;
	Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.ref_halfBridge8DutyCycle;
	Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.ref_halfBridge9DutyCycle;
	Global_Data.rasv.halfBridge10DutyCycle = Global_Data.rasv.ref_halfBridge10DutyCycle;
	Global_Data.rasv.halfBridge11DutyCycle = Global_Data.rasv.ref_halfBridge11DutyCycle;
	Global_Data.rasv.halfBridge12DutyCycle = Global_Data.rasv.ref_halfBridge12DutyCycle;

	theta_ = Global_Data.av.theta_elec + Global_Data.av.theta_offset;



////////////////////////////////////////////////////////////////////////////////////////////////////
////			Current control																	////
////////////////////////////////////////////////////////////////////////////////////////////////////
    if (current_state==control_state)
    {
    	//ParaID
		uz_ParameterID_6ph_step(ParameterID, &ParaID_Data);
		dutyCycles_set1.DutyCycle_U = ParaID_Data.ElectricalID_Output.PWM_Switch_0;
		dutyCycles_set1.DutyCycle_V = ParaID_Data.ElectricalID_Output.PWM_Switch_2;
		dutyCycles_set1.DutyCycle_W = ParaID_Data.ElectricalID_Output.PWM_Switch_4;
		dutyCycles_set2.DutyCycle_U = ParaID_Data.ElectricalID_Output.PWM_Switch_a2;
		dutyCycles_set2.DutyCycle_V = ParaID_Data.ElectricalID_Output.PWM_Switch_b2;
		dutyCycles_set2.DutyCycle_W = ParaID_Data.ElectricalID_Output.PWM_Switch_c2;
		//ParaID end
		//write duty-cycles
    	Global_Data.rasv.halfBridge4DutyCycle = dutyCycles_set2.DutyCycle_U;
    	Global_Data.rasv.halfBridge5DutyCycle = dutyCycles_set2.DutyCycle_V;
    	Global_Data.rasv.halfBridge6DutyCycle = dutyCycles_set2.DutyCycle_W;
    	Global_Data.rasv.halfBridge7DutyCycle = dutyCycles_set1.DutyCycle_U;
    	Global_Data.rasv.halfBridge8DutyCycle = dutyCycles_set1.DutyCycle_V;
    	Global_Data.rasv.halfBridge9DutyCycle = dutyCycles_set1.DutyCycle_W;
    }




    // duty cycles:
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);	//D3 gan inv
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);	//D4 gan inv
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
