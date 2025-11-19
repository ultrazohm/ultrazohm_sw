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
#include "../uz/uz_math_constants.h"
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

uint32_t ssi_min_raw = 1000U;
uint32_t ssi_max_raw = 0U;

extern uz_codegen codegenInstance;
float generate_sawtooth(float amplitude, float frequency, float sample_time);
float sawtooth=0.0f;

//uint16_t gray_pos = 0U;
//uint32_t dir = 0U;

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

    Global_Data.av.ssi0_position_raw = uz_ssi_interface_get_position_raw_single_turn(Global_Data.objects.ssi_0_encoder);
    Global_Data.av.ssi0_position_mech_si = uz_ssi_interface_get_position_mech_si_single_turn(Global_Data.objects.ssi_0_encoder);
    Global_Data.av.ssi0_position_el_si = uz_ssi_interface_get_position_el_si_single_turn(Global_Data.objects.ssi_0_encoder);

    Global_Data.av.ssi1_position_raw = uz_ssi_interface_get_position_raw_single_turn(Global_Data.objects.ssi_1_encoder);
    Global_Data.av.ssi1_position_mech_si = uz_ssi_interface_get_position_mech_si_single_turn(Global_Data.objects.ssi_1_encoder);
    Global_Data.av.ssi1_position_el_si = uz_ssi_interface_get_position_el_si_single_turn(Global_Data.objects.ssi_1_encoder);
    Global_Data.av.ssi1_position_multiturn_raw = uz_ssi_interface_get_position_raw_multi_turn(Global_Data.objects.ssi_1_encoder);
    Global_Data.av.ssi1_position_multiturn = uz_ssi_interface_get_position_multi_turn(Global_Data.objects.ssi_1_encoder);

    Global_Data.av.ssi0_speed_mech_rad_s_ip = uz_ssi_interface_get_speed_mech_si(Global_Data.objects.ssi_0_encoder);
    Global_Data.av.ssi0_speed_el_rad_s_ip = uz_ssi_interface_get_speed_el_si(Global_Data.objects.ssi_0_encoder);
    Global_Data.av.ssi0_speed_mech_rpm_ip = uz_ssi_interface_get_speed_mech_rpm(Global_Data.objects.ssi_0_encoder);

//    Global_Data.av.ssi0_debug_pre_slice = (float)(uz_axi_read_uint32(XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR + 0x15C));
//	Global_Data.av.ssi0_debug_post_slice = (float)(uz_axi_read_uint32(XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR + 0x160));

//    sawtooth = uz_wavegen_sawtooth(2*UZ_PIf, 16.67f);
    sawtooth = generate_sawtooth(2.0f*UZ_PIf, Global_Data.av.snd_fld[6], 100e-6f); // set frequency via send_field_6 in JavaScope

    // write sawtooth to ip core input
//    uz_fixedpoint_axi_write(XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR + 0x120, sawtooth, fp_type_sawtooth);

    if (Global_Data.av.ssi0_position_raw > ssi_max_raw) {
    	ssi_max_raw = Global_Data.av.ssi0_position_raw;
    }

    if (Global_Data.av.ssi0_position_raw < ssi_min_raw) {
        	ssi_min_raw = Global_Data.av.ssi0_position_raw;
        }

///* TEST CODE FOR GETTING SAWTOOTH BEHAVIOR OF SINGLE-TURN POSITION */
//    // Convert Gray code to binary
//    uint16_t gray_to_binary(uint16_t gray) {
//        uint16_t bin = gray;
//        while (gray >>= 1) {
//            bin ^= gray;
//        }
//        return bin;
//    }
//
//    // Convert binary to Gray code (if needed)
//    uint16_t binary_to_gray(uint16_t bin) {
//        return bin ^ (bin >> 1);
//    }
//
//    // Map Gray code + direction -> corrected binary position
//    uint16_t decode_gray(uint16_t gray, int direction) {
//        const uint16_t N = 1 << 13;  // 8192 states for 13-bit
//        uint16_t pos = gray_to_binary(gray);
//
//        if (direction) {
//            // If reversed traversal: mirror position
//            pos = (N - 1) - pos;
//        }
//
//        return pos;  // corrected binary position (0…8191)
//    }
//
//    gray_pos = binary_to_gray(Global_Data.av.ssi1_position_raw);
//    if ((uint32_t)(Global_Data.av.ssi1_position_multiturn_raw) % 2U == 0U) {
//    	dir = 0U;
//    }else{
//    	dir = 1U;
//    }

//    Global_Data.av.ssi1_position_decoded = decode_gray(gray_pos, dir);
    /* END TEST CODE */

    codegenInstance.input.position_mech_SI = Global_Data.av.ssi0_position_mech_si;
//    codegenInstance.input.position_mech_SI = sawtooth;
    uz_codegen_step(&codegenInstance); // 3.5 microseconds
    Global_Data.av.ssi0_speed_mech_rad_s = codegenInstance.output.omega_mech;
    Global_Data.av.ssi0_speed_mech_rpm = Global_Data.av.ssi0_speed_mech_rad_s * 30.0f/UZ_PIf;

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
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

// Function to generate a sawtooth waveform from 0 to amplitude
// amplitude: peak value of the waveform (must be positive)
// frequency: frequency of the waveform in Hz
// sample_time: time between each sample in seconds (e.g., 0.001 for 1 kHz sampling)
// Returns the next sample of the sawtooth waveform
float generate_sawtooth(float amplitude, float frequency, float sample_time) {
    static float phase = 0.0f;

    float phase_increment = frequency * sample_time;

    // Wrap the phase
    if (phase >= 1.0f) {
        phase -= 1.0f;
    }

    // Output ranges from 0 to amplitude
    float output = amplitude * phase;

    phase += phase_increment;

    return output;
}
