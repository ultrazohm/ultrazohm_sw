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
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

#define MAX_PHASE_CURRENT_AMPERE	12.0f

// uz_transformation variables for uz_foc
uz_3ph_abc_t ph_currents_left_motor = {0.0f};
uz_3ph_abc_t ph_currents_right_motor = {0.0f};

uz_3ph_dq_t dq_currents_left_motor = {0.0f};
uz_3ph_dq_t dq_currents_right_motor = {0.0f};

uz_3ph_dq_t dq_ref_currents_left_motor = {0.0f};
uz_3ph_dq_t dq_ref_currents_right_motor = {0.0f};

uz_3ph_dq_t dq_ref_voltages_left_motor = {0.0f};
uz_3ph_dq_t dq_ref_voltages_right_motor = {0.0f};

uz_3ph_abc_t ph_ref_voltages_left_motor = {0.0f};
uz_3ph_abc_t ph_ref_voltages_right_motor = {0.0f};

// uz_foc variables
struct uz_DutyCycle_t dutycyc_left_motor = {0.0f};
struct uz_DutyCycle_t dutycyc_right_motor = {0.0f};

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
float n_ref=0.0f;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    n_ref=uz_wavegen_sine(1000.0f, 1.0f/5.0f);
    Global_Data.rasv.n_rpm_ref_left=n_ref;
    // convert adc readings of d1 to currents in ampere (former d4 card at my six-phase testbench) - pay attention to A1.cf in main.c !!!
    Global_Data.av.d_1_i_a1 = -1.0f * Global_Data.aa.A1.me.ADC_A4 - 0.0338f * Global_Data.aa.A1.me.ADC_A4 + 0.0259f;
    Global_Data.av.d_1_i_b1 = -1.0f * Global_Data.aa.A1.me.ADC_A3 - 0.0407f * Global_Data.aa.A1.me.ADC_A3 + 0.0280f;
    Global_Data.av.d_1_i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_A2 - 0.0401f * Global_Data.aa.A1.me.ADC_A2 + 0.0220f;
    // convert adc readings of d2 to currents in ampere (former d3 card at my six-phase testbench)
    Global_Data.av.d_2_i_a1 = -1.0f * Global_Data.aa.A1.me.ADC_B8 - 0.0541f * Global_Data.aa.A1.me.ADC_B8 + 0.0352f;
    Global_Data.av.d_2_i_b1 = -1.0f * Global_Data.aa.A1.me.ADC_B7 - 0.0516f * Global_Data.aa.A1.me.ADC_B7 + 0.0133f;
    Global_Data.av.d_2_i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_B6 - 0.0341f * Global_Data.aa.A1.me.ADC_B6 + 0.0383f;

    // assign measured currents to phase currents objects
    ph_currents_left_motor.a = Global_Data.av.d_1_i_a1;
    ph_currents_left_motor.b = Global_Data.av.d_1_i_b1;
    ph_currents_left_motor.c = Global_Data.av.d_1_i_c1;

    ph_currents_right_motor.a = Global_Data.av.d_2_i_a1;
    ph_currents_right_motor.b = Global_Data.av.d_2_i_b1;
    ph_currents_right_motor.c = Global_Data.av.d_2_i_c1;

    // check for software over-current limit
    if (fabsf(Global_Data.av.d_1_i_a1) > MAX_PHASE_CURRENT_AMPERE || fabsf(Global_Data.av.d_1_i_b1) > MAX_PHASE_CURRENT_AMPERE || fabsf(Global_Data.av.d_1_i_c1) > MAX_PHASE_CURRENT_AMPERE ||
    	fabsf(Global_Data.av.d_2_i_a1) > MAX_PHASE_CURRENT_AMPERE || fabsf(Global_Data.av.d_2_i_b1) > MAX_PHASE_CURRENT_AMPERE || fabsf(Global_Data.av.d_2_i_c1) > MAX_PHASE_CURRENT_AMPERE)
    {
    	uz_assert(0); // fail hard and loudly
    }

    // read all omega_mechs in rad/s from d5
    Global_Data.av.omega_mech_d5_1 = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.increEncoder_d5_1);
    Global_Data.av.omega_mech_d5_2 = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.increEncoder_d5_2);
    Global_Data.av.omega_mech_d5_3 = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.increEncoder_d5_3);

    // read all mechanical positions in increments from d5
    Global_Data.av.mech_position_d5_1 = uz_incrementalEncoder_get_position(Global_Data.objects.increEncoder_d5_1);
    Global_Data.av.mech_position_d5_2 = uz_incrementalEncoder_get_position(Global_Data.objects.increEncoder_d5_2);
    Global_Data.av.mech_position_d5_3 = uz_incrementalEncoder_get_position(Global_Data.objects.increEncoder_d5_3);

    // read all electric thetas in rad from d5
    Global_Data.av.theta_el_d5_1 = Global_Data.av.polepairs_left * uz_incrementalEncoder_get_theta_el(Global_Data.objects.increEncoder_d5_1);
    Global_Data.av.theta_el_d5_2 = Global_Data.av.polepairs_right * uz_incrementalEncoder_get_theta_el(Global_Data.objects.increEncoder_d5_2);
    Global_Data.av.theta_el_d5_3 = uz_incrementalEncoder_get_theta_el(Global_Data.objects.increEncoder_d5_3);

    // respect el. theta offset
    Global_Data.av.theta_el_left_motor = Global_Data.av.theta_el_d5_1 - Global_Data.av.theta_el_offset_left;
    Global_Data.av.theta_el_right_motor =Global_Data.av.polepairs_right*2.0f*UZ_PIf-(Global_Data.av.theta_el_d5_1 - Global_Data.av.theta_el_offset_right);

    // speeds in rpm
    Global_Data.av.left_speed_rpm = Global_Data.av.omega_mech_d5_1 * 30.0f * 0.3183; //0.3183 = 1/pi
    Global_Data.av.right_speed_rpm = Global_Data.av.omega_mech_d5_2 * 30.0f * 0.3183;

    // Read inverter adapter outputs
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);

    // transform measured currents to dq frame
    dq_currents_left_motor = uz_transformation_3ph_abc_to_dq(ph_currents_left_motor, Global_Data.av.theta_el_left_motor);
    dq_currents_right_motor = uz_transformation_3ph_abc_to_dq(ph_currents_right_motor, Global_Data.av.theta_el_right_motor);

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    if (current_state==running_state || current_state==control_state) {
    	// enable inverter adapter hardware
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    } else {
    	// disable inverter adapter hardware
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    }

    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state



    	// calculate uz_SpeedControl reference dq_currents
    	dq_ref_currents_left_motor = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_left_motor, Global_Data.av.omega_mech_d5_1, Global_Data.rasv.n_rpm_ref_left, Global_Data.av.U_ZK, dq_ref_currents_left_motor.d);
    	//dq_ref_currents_right_motor = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_right_motor, Global_Data.av.omega_mech_d5_2, Global_Data.rasv.n_rpm_ref_right, Global_Data.av.U_ZK, dq_ref_currents_right_motor.d);
    	// calculate uz_FOC reference dq-voltages
    	dq_ref_voltages_left_motor = uz_FOC_sample(Global_Data.objects.uz_FOC_left_motor, dq_ref_currents_left_motor, dq_currents_left_motor, Global_Data.av.U_ZK, Global_Data.av.theta_el_left_motor);
    	dq_ref_voltages_right_motor = uz_FOC_sample(Global_Data.objects.uz_FOC_right_motor, dq_ref_currents_right_motor, dq_currents_right_motor, Global_Data.av.U_ZK, Global_Data.av.theta_el_right_motor);
    	// transform reference voltages to abc frame
    	ph_ref_voltages_left_motor = uz_transformation_3ph_dq_to_abc(dq_ref_voltages_left_motor, Global_Data.av.theta_el_left_motor);
    	ph_ref_voltages_right_motor = uz_transformation_3ph_dq_to_abc(dq_ref_voltages_right_motor, Global_Data.av.theta_el_right_motor);
    	// calculate duty-cycle from reference voltages
    	dutycyc_left_motor = uz_FOC_generate_DutyCycles(ph_ref_voltages_left_motor, Global_Data.av.U_ZK);
    	dutycyc_right_motor = uz_FOC_generate_DutyCycles(ph_ref_voltages_right_motor, Global_Data.av.U_ZK);
    	// assign duty-cycles to global duty-cycle variables
    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_left_motor.DutyCycle_U;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_left_motor.DutyCycle_V;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_left_motor.DutyCycle_W;

    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_right_motor.DutyCycle_U;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_right_motor.DutyCycle_V;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_right_motor.DutyCycle_W;


    } else {
    	// reset FOC instances (clear integrators)
    	uz_FOC_reset(Global_Data.objects.uz_FOC_left_motor);
    	uz_FOC_reset(Global_Data.objects.uz_FOC_right_motor);
    	// reset speed controllers (clear integrators)
    	uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left_motor);
    	uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_right_motor);
    	// set global duty-cycles to 0.5
//    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
//    	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
//    	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
//
//    	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
//    	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
//    	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
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
