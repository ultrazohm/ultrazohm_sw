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
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/pwm_init.h"
#include "../include/project_wizard_visualization.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

/* Project Wizard BEGIN: adc_readout_definitions */
static uz_array_int16_t analog_adc_data;
/* Project Wizard END: adc_readout_definitions */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void update_adapter_a1(void);
static void update_adapter_a2(void);
static void update_adapter_a3(void);
static void update_adapter_d1(void);
static void update_adapter_d2(void);
static void update_adapter_d3(void);
static void update_adapter_d4(void);
static void update_adapter_d5(void);

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
/* Project Wizard BEGIN: adc_readout */
    analog_adc_data = uz_dataMover_update_buffer_and_get_data();
/* Project Wizard END: adc_readout */
    update_adapter_a1();
    update_adapter_a2();
    update_adapter_a3();
    update_adapter_d1();
    update_adapter_d2();
    update_adapter_d3();
    update_adapter_d4();
    update_adapter_d5();

    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == idle_state)
    {
        /* Project Wizard BEGIN: idle_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
/* Project Wizard END: idle_state isr_actions */
    }
    else if (current_state == running_state)
    {
        /* Project Wizard BEGIN: running_state isr_actions */
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, false, false, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d1, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, true);
/* Project Wizard END: running_state isr_actions */
    }
    else if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
        uz_3ph_abc_t three_phase_sine_wave = uz_wavegen_three_phase_sample(Global_Data.objects.three_phase_sine, 0.5f, 2.0f, 0.5f);
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = three_phase_sine_wave.a;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = three_phase_sine_wave.b;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = three_phase_sine_wave.c;
        Global_Data.rasv.pwm_3L_0_halfBridgeDutyCycle_1 = three_phase_sine_wave.a;
        Global_Data.rasv.pwm_3L_0_halfBridgeDutyCycle_2 = three_phase_sine_wave.b;
        Global_Data.rasv.pwm_3L_0_halfBridgeDutyCycle_3 = three_phase_sine_wave.c;

        /* Project Wizard BEGIN: control_state isr_actions */
/* Project Wizard END: control_state isr_actions */
    }
    else if (current_state == error_state)
    {
        /* Project Wizard BEGIN: error_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_d2, false);
/* Project Wizard END: error_state isr_actions */
    }
    
    /* Project Wizard BEGIN: pwm_runtime */
    project_wizard_update_pwm_outputs(&Global_Data);
/* Project Wizard END: pwm_runtime */

    project_wizard_visualization_update(&Global_Data);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

static void update_adapter_a1(void)
{
    /* Project Wizard BEGIN: A1 isr_control */
    Global_Data.av.adc_ltc2311_a1_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[0], 0U);
    Global_Data.av.adc_ltc2311_a1_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[1], 1U);
    Global_Data.av.adc_ltc2311_a1_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[2], 2U);
    Global_Data.av.adc_ltc2311_a1_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[3], 3U);
    Global_Data.av.adc_ltc2311_a1_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[4], 4U);
    Global_Data.av.adc_ltc2311_a1_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[5], 5U);
    Global_Data.av.adc_ltc2311_a1_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[6], 6U);
    Global_Data.av.adc_ltc2311_a1_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[7], 7U);
/* Project Wizard END: A1 isr_control */
}

static void update_adapter_a2(void)
{
    /* Project Wizard BEGIN: A2 isr_control */
    Global_Data.av.adc_ltc2311_a2_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[8], 0U);
    Global_Data.av.adc_ltc2311_a2_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[9], 1U);
    Global_Data.av.adc_ltc2311_a2_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[10], 2U);
    Global_Data.av.adc_ltc2311_a2_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[11], 3U);
    Global_Data.av.adc_ltc2311_a2_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[12], 4U);
    Global_Data.av.adc_ltc2311_a2_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[13], 5U);
    Global_Data.av.adc_ltc2311_a2_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[14], 6U);
    Global_Data.av.adc_ltc2311_a2_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[15], 7U);
/* Project Wizard END: A2 isr_control */
}

static void update_adapter_a3(void)
{
    /* Project Wizard BEGIN: A3 isr_control */
    Global_Data.av.adc_ltc2311_a3_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[16], 0U);
    Global_Data.av.adc_ltc2311_a3_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[17], 1U);
    Global_Data.av.adc_ltc2311_a3_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[18], 2U);
    Global_Data.av.adc_ltc2311_a3_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[19], 3U);
    Global_Data.av.adc_ltc2311_a3_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[20], 4U);
    Global_Data.av.adc_ltc2311_a3_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[21], 5U);
    Global_Data.av.adc_ltc2311_a3_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[22], 6U);
    Global_Data.av.adc_ltc2311_a3_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[23], 7U);
/* Project Wizard END: A3 isr_control */
}

static void update_adapter_d1(void)
{
    /* Project Wizard BEGIN: D1 isr_control */
    update_inverter_adapter_d1_outputs(&Global_Data);
/* Project Wizard END: D1 isr_control */
}

static void update_adapter_d2(void)
{
    /* Project Wizard BEGIN: D2 isr_control */
    update_inverter_adapter_d2_outputs(&Global_Data);
/* Project Wizard END: D2 isr_control */
}

static void update_adapter_d3(void)
{
    /* Project Wizard BEGIN: D3 isr_control */
/* Project Wizard END: D3 isr_control */
}

static void update_adapter_d4(void)
{
    /* Project Wizard BEGIN: D4 isr_control */
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_1_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_1);
    Global_Data.av.resolver_pl_interface_d4_1_revolution_counter = resolver_pl_interface_d4_1_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_1_position_mech_2pi = resolver_pl_interface_d4_1_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_position_el_2pi = resolver_pl_interface_d4_1_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_omega_mech_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_1_n_mech_rpm = resolver_pl_interface_d4_1_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_1_omega_el_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_1);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_2_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_2);
    Global_Data.av.resolver_pl_interface_d4_2_revolution_counter = resolver_pl_interface_d4_2_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_2_position_mech_2pi = resolver_pl_interface_d4_2_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_position_el_2pi = resolver_pl_interface_d4_2_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_omega_mech_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_2_n_mech_rpm = resolver_pl_interface_d4_2_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_2_omega_el_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_2);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_3_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_3);
    Global_Data.av.resolver_pl_interface_d4_3_revolution_counter = resolver_pl_interface_d4_3_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_3_position_mech_2pi = resolver_pl_interface_d4_3_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_position_el_2pi = resolver_pl_interface_d4_3_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_omega_mech_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_3_n_mech_rpm = resolver_pl_interface_d4_3_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_3_omega_el_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_3);
/* Project Wizard END: D4 isr_control */
}

static void update_adapter_d5(void)
{
    /* Project Wizard BEGIN: D5 isr_control */
    Global_Data.av.incremental_encoder_d5_1_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_2_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_3_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_3);
/* Project Wizard END: D5 isr_control */
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
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

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
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



