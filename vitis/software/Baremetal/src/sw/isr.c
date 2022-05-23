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

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_mech_calc_from_resolver = 0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;

uz_6ph_abc_t six_ph_currents = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta = {0.0f};
uz_3ph_alphabeta_t three_ph_alphabeta = {0.0f};
uz_3ph_dq_t rotating_dq = {0};

uz_3ph_dq_t i_dq_ref = {0.0f};
uz_3ph_dq_t i_dq_actual = {0.0f};
uz_3ph_dq_t u_dq_ref = {0.0f};
uz_3ph_alphabeta_t alphabeta_ref_volts = {0.0f};
uz_6ph_alphabeta_t vsd_ref_volts = {0.0f};
uz_6ph_abc_t phase_ref_volts = {0.0f};

uz_3ph_abc_t input1 = {0.0f};
uz_3ph_abc_t input2 = {0.0f};
struct uz_DutyCycle_t output1 = {0};
struct uz_DutyCycle_t output2 = {0};

#define PHASE_CURRENT_CONV	37.735
#define DC_VOLT_CONV		250
#define DC_VOLT_OFF			250


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
    //update_position_of_resolverIP(&Global_Data);
    //update_speed_of_resolverIP(&Global_Data);
    //readRegister_of_resolverIP(&Global_Data);

    // convert ADC readings to currents in Amps
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_B6 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c2 = -1.0f * Global_Data.aa.A2.me.ADC_B6 * PHASE_CURRENT_CONV;
    // convert ADC readings to dc link voltages
    Global_Data.av.U_ZK = -1.0f * Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV - DC_VOLT_OFF;
    Global_Data.av.U_ZK2 = -1.0f * Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV - DC_VOLT_OFF;

    // filter values
    Global_Data.av.i_a1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a1, Global_Data.av.i_a1);
    Global_Data.av.i_b1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b1, Global_Data.av.i_b1);
    Global_Data.av.i_c1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c1, Global_Data.av.i_c1);
    Global_Data.av.i_a2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a2, Global_Data.av.i_a2);
    Global_Data.av.i_b2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b2, Global_Data.av.i_b2);
    Global_Data.av.i_c2_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c2, Global_Data.av.i_c2);
    Global_Data.av.U_ZK_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_dc, Global_Data.av.U_ZK);

    // theta offset and scaling to el. angle
    Global_Data.av.theta_m_offset_comp = theta_mech_calc_from_resolver - Global_Data.av.theta_offset;
    Global_Data.av.theta_elec = Global_Data.av.theta_m_offset_comp * Global_Data.av.polepairs;

    // transform phase currents
    six_ph_currents.a1 = Global_Data.av.i_a1_filt;
    six_ph_currents.b1 = Global_Data.av.i_b1_filt;
    six_ph_currents.c1 = Global_Data.av.i_c1_filt;
    six_ph_currents.a2 = Global_Data.av.i_a2_filt;
    six_ph_currents.b2 = Global_Data.av.i_b2_filt;
    six_ph_currents.c2 = Global_Data.av.i_c2_filt;
    six_ph_alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_currents);


    three_ph_alphabeta.alpha = six_ph_alphabeta.alpha;
    three_ph_alphabeta.beta = six_ph_alphabeta.beta;
    Global_Data.av.i_alpha = three_ph_alphabeta.alpha;
    Global_Data.av.i_beta = three_ph_alphabeta.beta;
    rotating_dq = uz_transformation_3ph_alphabeta_to_dq(three_ph_alphabeta, Global_Data.av.theta_elec);
    Global_Data.av.i_d = rotating_dq.d;
    Global_Data.av.i_q = rotating_dq.q;

    i_dq_actual.d = Global_Data.av.i_d;
    i_dq_actual.q = Global_Data.av.i_q;

	i_dq_ref.d = Global_Data.av.i_d_ref;
	i_dq_ref.q = Global_Data.av.i_q_ref;

	if(fabs(six_ph_currents.a1) > 10.0f || fabs(six_ph_currents.b1) > 10.0f || fabs(six_ph_currents.c1) > 10.0f ||
	   fabs(six_ph_currents.a2) > 10.0f || fabs(six_ph_currents.b2) > 10.0f || fabs(six_ph_currents.c2) > 10.0f) {
		uz_assert(0);
	}

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	u_dq_ref = uz_FOC_sample(Global_Data.objects.foc_current, i_dq_ref, i_dq_actual, Global_Data.av.U_ZK_filt, Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs);
    	alphabeta_ref_volts = uz_transformation_3ph_dq_to_alphabeta(u_dq_ref, Global_Data.av.theta_elec);
    	vsd_ref_volts.alpha = alphabeta_ref_volts.alpha;
    	vsd_ref_volts.beta = alphabeta_ref_volts.beta;
    	phase_ref_volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(vsd_ref_volts);

    	input1.a = phase_ref_volts.a1;
    	input1.b = phase_ref_volts.b1;
    	input1.c = phase_ref_volts.c1;
    	input2.a = phase_ref_volts.a2;
    	input2.b = phase_ref_volts.b2;
    	input2.c = phase_ref_volts.c2;

    	output1 = uz_FOC_generate_DutyCycles(input1, Global_Data.av.U_ZK_filt);
    	output2 = uz_FOC_generate_DutyCycles(input2, Global_Data.av.U_ZK_filt);

    	Global_Data.rasv.halfBridge1DutyCycle = output1.DutyCycle_U;
    	Global_Data.rasv.halfBridge2DutyCycle = output1.DutyCycle_V;
    	Global_Data.rasv.halfBridge3DutyCycle = output1.DutyCycle_W;
    	Global_Data.rasv.halfBridge4DutyCycle = output2.DutyCycle_U;
    	Global_Data.rasv.halfBridge5DutyCycle = output2.DutyCycle_V;
    	Global_Data.rasv.halfBridge6DutyCycle = output2.DutyCycle_W;

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

    // Determine mechanical angle of resolver
    if(theta_mech_old-Global_Data.av.theta_mech > 4.0f) {
    	cnt++;
    	cnt_float=(float)cnt;
    } else if (theta_mech_old-Global_Data.av.theta_mech < -4.0f) {
    	cnt--;
    	cnt_float=(float)cnt;
    }

    if(cnt > 1 || cnt < -1) {
    	cnt = 0;
    	cnt_float = 0.0f;
    }

    if(cnt_reset == 1) {
    	cnt = 0;
    	cnt_float = 0;
    	cnt_reset = 0;
    	cnt_reset_float=0;
    }


    if(cnt >= 0){
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech/uz_resolverIP_getResolverPolePairs(Global_Data.objects.resolver_IP) + cnt*2*3.14159265358979323846/2.0f;
    } else {
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech/2.0f + (2+cnt)*2*3.14159265358979323846/2.0f;
    }

    theta_mech_old = Global_Data.av.theta_mech;

    if (Global_Data.av.theta_mech <= theta_m_min) {
    	theta_m_min = Global_Data.av.theta_mech;
    }

    if (Global_Data.av.theta_mech >= theta_m_max) {
    	theta_m_max = Global_Data.av.theta_mech;
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
