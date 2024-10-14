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
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"

#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// =============== Declares for PMSM 1 =============== //
float n_ref_rpm_heidrive = 0.0f;
float n_ref_rpm_heidrive_javascope = 0.0f;

// Stuff
uint32_t setpoint_index = 0U;
uint32_t n_ref_setpoint_index = 0U;

uint32_t Fehlerfall = 0U;
extern uz_3ph_dq_t i_dq_ref_java_Amps_brose;

struct uz_pmsm_measurement_values heidrive_measurements = {0.0f};

float heidrive_reference_speed_in_rpm = 0.0f;
uz_3ph_dq_t heidrive_reference_currents_in_A = {0.0f};

static void ReadAllADC();
bool enable_controller = false;
bool manual_dutycycle=true;

// // First inverter
// v_abc_Volts_brose.a = 11.7657f * Global_Data.aa.A1.me.ADC_B8 + 0.0533f;
// v_abc_Volts_brose.b = 11.7657f * Global_Data.aa.A1.me.ADC_B7 + 0.0533f;
// v_abc_Volts_brose.c = 11.7657f * Global_Data.aa.A1.me.ADC_B6 + 0.0533f;
// v_DC_Volts_brose = 48.0f; // Global_Data.aa.A1.me.ADC_A1 * 12.0f;
// i_abc_Amps_hoener.a = 12.223f * Global_Data.aa.A1.me.ADC_A4 + 0.0164f;
// i_abc_Amps_hoener.b = 12.3123f * Global_Data.aa.A1.me.ADC_A3 + 0.0161f;
// i_abc_Amps_hoener.c = 12.4303f * Global_Data.aa.A1.me.ADC_A2 - 0.0184f;
// i_DC_Amps_brose = Global_Data.aa.A1.me.ADC_B5 * 12.5f;

// // Read Measurement of Second Inverter
// v_abc_Volts_heidrive.a = 11.6798f * Global_Data.aa.A2.me.ADC_B8 - 0.3648f;
// v_abc_Volts_heidrive.b = 11.7657f * Global_Data.aa.A2.me.ADC_B7 + 0.0533f;
// v_abc_Volts_heidrive.c = 11.7657f * Global_Data.aa.A2.me.ADC_B6 + 0.0533f;
// v_DC_Volts_heidrive = 48.0f; // Global_Data.aa.A2.me.ADC_A1 * 12.0f;
// i_abc_Amps_heidrive.a = 12.2889f * Global_Data.aa.A2.me.ADC_A4 + 0.0802f;
// i_abc_Amps_heidrive.b = 11.8330f * Global_Data.aa.A2.me.ADC_A3 + 0.1344f;
// i_abc_Amps_heidrive.c = 11.7894f * Global_Data.aa.A2.me.ADC_A2 + 0.1197f;
// i_DC_Amps_heidrive = Global_Data.aa.A2.me.ADC_B5 * 12.5f;

// struct uz_pmsm_actual_data heidrive_actual_data = {0.0f};

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_2(&Global_Data);

    // i_dq_ref_Amps_brose.d = i_dq_ref_java_Amps_brose.d;
    // i_dq_ref_Amps_brose.q = i_dq_ref_java_Amps_brose.q;
    // n_ref_rpm_heidrive = n_ref_rpm_heidrive_javascope;

    heidrive_measurements.i_dc_from_adc_ampere_per_volt = Global_Data.aa.A2.me.ADC_B5;
    heidrive_measurements.v_dc_from_adc_volt_per_volt = 48.0f / 12.0f;
    heidrive_measurements.phase_currents_from_adc_ampere_per_volt.a = Global_Data.aa.A2.me.ADC_B8;
    heidrive_measurements.phase_currents_from_adc_ampere_per_volt.b = Global_Data.aa.A2.me.ADC_B7;
    heidrive_measurements.phase_currents_from_adc_ampere_per_volt.c = Global_Data.aa.A2.me.ADC_B6;
    heidrive_measurements.omega_mech_rad_per_sec = Global_Data.av.omega_mech_rad_per_sed;
    heidrive_measurements.theta_mech = Global_Data.av.theta_elec_heidrive;

    Global_Data.av.inverter_outputs_d1_brose = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1_brose);
    Global_Data.av.inverter_outputs_d2_heidrive = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2_heidrive);

    // Get current state
    platform_state_t current_state = ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state)
    {
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_brose, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_heidrive, true);
    }
    else
    {
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_brose, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_heidrive, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_brose, true, true, true);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2_heidrive, true, true, true);
    }

    if (current_state == control_state)
    {
        uz_pmsm_controller_enable(Global_Data.objects.heidrive_controller, enable_controller);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_brose, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2_heidrive, false, false, false);
    }
    else
    {
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_brose, true, true, true);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d2_heidrive, true, true, true);
    }
    struct uz_DutyCycle_t duty = uz_pmsm_controller_sample(Global_Data.objects.heidrive_controller, heidrive_measurements, heidrive_reference_speed_in_rpm, heidrive_reference_currents_in_A);

    if(!manual_dutycycle){
    	Global_Data.rasv.halfBridge4DutyCycle = duty.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = duty.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = duty.DutyCycle_C;
    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_brose, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d2_heidrive, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    JavaScope_update(&Global_Data);

    // Inverter 1 safety
    // Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    // Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 1U;
    }
    // Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_L1)
    {
        // ultrazohm_state_machine_set_error(true);
        Fehlerfall = 2U;
    }
    // Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 3U;
    }
    // Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 4U;
    }
    // Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_H3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 5U;
    }
    // Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1_brose.FAULT_L3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 6U;
    }
    // Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    // Binding of the signals to the driver is slightly unintuitive
    // Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1_brose.OC_L1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 7U;
    }
    // Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1_brose.OC_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 8U;
    }
    // Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1_brose.OC_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 9U;
    }
    // Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1_brose.OC_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 10U;
    }

    // Inverter 2 safety
    // Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    // Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 11U;
    }
    // Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_L1)
    {
        // ultrazohm_state_machine_set_error(true);
        Fehlerfall = 12U;
    }
    // Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 13U;
    }
    // Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 14U;
    }
    // Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_H3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 15U;
    }
    // Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2_heidrive.FAULT_L3)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 16U;
    }
    // Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    // Binding of the signals to the driver is slightly unintuitive
    // Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2_heidrive.OC_L1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 17U;
    }
    // Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2_heidrive.OC_H1)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 18U;
    }
    // Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2_heidrive.OC_L2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 19U;
    }
    // Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d2_heidrive.OC_H2)
    {
        ultrazohm_state_machine_set_error(true);
        Fehlerfall = 20U;
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
    // uz_mux_axi_enable(Global_Data.objects.mux_axi);

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
