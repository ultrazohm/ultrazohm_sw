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
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

struct uz_3ph_abc_t i_actual_A_abc = {0};
struct uz_DutyCycle_t dutycyle = {0};

struct uz_3ph_dq_t i_actual_Ampere = {
    .d = 0.0f,
    .q = 0.0f,
    .zero = 0.0f};

struct uz_3ph_dq_t i_reference_Ampere = {
    .d = 0.0f,
    .q = 0.0f,
    .zero = 0.0f};

float V_dc_volts = 24.0f;
float omega_el_rad_per_sec = 0.0f;
float theta_el_rad = 0.0f;

float theta_offset = -0.54f;          // 0.0f; // 6.07759f; // zum Bestimmen eine Phase bestromen, dadurch Ausrichtung d-Achse auf bestromte, theta_elec muss 0 oder 2pi sein mit offset
float adc_scaling = (20.0f / 2.084f); // 3.2f
float poles = 3.0f;
struct uz_3ph_dq_t v_dq_Volts = {0};
extern uz_CurrentControl_t *CC_instance;

enum encoderoffset_states
{
    encoderoffset_init = 0,
    encoderoffset_positive_accelerate,
    encoderoffset_positive_i0,
    encoderoffset_positive_measurement,
    encoderoffset_negative_accelerate,
    encoderoffset_negative_i0,
    encoderoffset_negative_measurement,
    encoderoffset_calculate_offset,
    encoderoffset_sgd,
    encoderoffset_finished,
};

uz_filter_cumulativeavg_t filter_i_q=NULL;
uz_filter_cumulativeavg_t filter_i_d=NULL;
uz_filter_cumulativeavg_t filter_u_d=NULL;
uz_filter_cumulativeavg_t filter_u_q=NULL;
uz_filter_cumulativeavg_t filter_omega_el=NULL;

enum encoderoffset_states encoderoffset_current_state;
bool theta_offset_estimation = false;


float value_filter_i_q=0.0f;
float value_filter_i_d=0.0f;
float value_filter_u_d=0.0f;
float value_filter_u_q=0.0f;
float value_filter_omega_el=0.0f;



void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    theta_el_rad = fmodf(Global_Data.av.theta_elec * poles - theta_offset, 2 * M_PI); // *poles da bei PMSM config nur 1 Pol angegeben
    i_actual_A_abc.a = (Global_Data.aa.A1.me.ADC_A2 - 2.425f) * adc_scaling;          // zeigt 2.5 bei 0 an
    i_actual_A_abc.b = (Global_Data.aa.A1.me.ADC_A4 - 2.425f) * adc_scaling;
    i_actual_A_abc.c = (Global_Data.aa.A1.me.ADC_A3 - 2.425f) * adc_scaling;
    i_actual_Ampere = uz_transformation_3ph_abc_to_dq(i_actual_A_abc, theta_el_rad);
    omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * poles * 2.0f * M_PI / 60.0f;

    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == control_state)
    {
        if (theta_offset_estimation)
        {

            float uz_encoderoffset_estimate_offset()
            {

                switch (encoderoffset_current_state)
                {
                case encoderoffset_init:
                    i_reference_Ampere.q = 0.0f;
                    i_reference_Ampere.d = 0.0f;
                    encoderoffset_current_state = encoderoffset_positive_accelerate;
                    break;
                case encoderoffset_positive_accelerate:
                    if (i_actual_Ampere.q < abs(1.0f))
                    {
                        i_reference_Ampere.q = 1.0f;
                    }
                    else
                    {
                        i_reference_Ampere.q = 0.0f;
                        encoderoffset_current_state = encoderoffset_positive_i0;
                    }
                    break;
                case encoderoffset_positive_i0:
                    if (i_actual_Ampere.q < abs(0.1f)) // wait until current is actually zero
                    {
                        if (omega_el_rad_per_sec > abs(5.0f)) // measure as long as omega_el is not zero
                        {
                            // measure
                        }
                        else
                        {
                            encoderoffset_current_state=encoderoffset_positive_measurement; // measurement is finished
                        }
                    }
                    break;
                case encoderoffset_positive_measurement:
                    // nothing
                default:
                    break;
                }
            };
        }

        // Start: Control algorithm - only if ultrazohm is in control state
        // Alternatively the sample function can output the UVW-values
        v_dq_Volts = uz_CurrentControl_sample(CC_instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
        struct uz_3ph_abc_t v_abc_Volts = uz_transformation_3ph_dq_to_abc(v_dq_Volts, theta_el_rad);
        dutycyle = uz_CurrentControl_generate_DutyCycles(v_abc_Volts, V_dc_volts);
        Global_Data.rasv.halfBridge1DutyCycle = dutycyle.DutyCycle_U;
        Global_Data.rasv.halfBridge2DutyCycle = dutycyle.DutyCycle_V;
        Global_Data.rasv.halfBridge3DutyCycle = dutycyle.DutyCycle_W;
    }
    else
    {
        Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
        Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
        Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
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


    filter_i_q=uz_filter_cumulativeavg_init();
    filter_i_d=uz_filter_cumulativeavg_init();
    filter_u_d=uz_filter_cumulativeavg_init();
    filter_u_q=uz_filter_cumulativeavg_init();
    filter_omega_el=uz_filter_cumulativeavg_init();


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
    // uz_mux_axi_enable(Global_Data.objects.mux_axi);

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
