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
#include "../include/uz_resolverIP_init.h"
#include "../uz/uz_math_constants.h"

#include "float.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

float theta_mech_resolver_ip = 0.0f;
float theta_elec_resolver_ip = 0.0f;
float speed_rpm_resolver_ip = 0.0f;

float theta_mech_res_calc_ip = 0.0f;
float theta_elec_res_calc_ip = 0.0f;
float omega_mech_res_calc_ip = 0.0f;
float rpm_mech_res_calc_ip = 0.0f;
float cnt_ip =0.0f;
bool reset_ip_cnt = false;

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_mech_calc_from_resolver = 0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;
bool first_ISR = true;

float theta_m_offset = 0.0;
float theta_m_mod = 0.0f;
float theta_el_mod = 0.0f;
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
//    update_speed_and_position_of_encoder_on_D5(&Global_Data);
    update_position_and_speed_of_resolverIP(&Global_Data);
//    update_position_of_resolverIP(&Global_Data);
//    update_speed_of_resolverIP(&Global_Data);

    Global_Data.av.pl_interface = uz_resolver_pl_interface_get_outputs(Global_Data.objects.pl_interface);
//    uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_PL_INTER_0_BASEADDR + 0x104, false); // cnt_reset false=normal operation
//
//    uz_axi_write_float(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_PL_INTER_0_BASEADDR + 0x114, theta_m_offset); // theta_el offset
//
//    theta_mech_res_calc_ip = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x118),20); //position_mech_2pi
//	theta_elec_res_calc_ip = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x11C),20); //position_el_2pi
//	omega_mech_res_calc_ip = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x120),11); //omega_mech
//	rpm_mech_res_calc_ip = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x128),11); //rpm_mech
//	cnt_ip = uz_axi_read_int32(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x124); //cnt

	theta_mech_res_calc_ip = Global_Data.av.pl_interface.position_mech_2pi;
	theta_elec_res_calc_ip = Global_Data.av.pl_interface.position_el_2pi;
	omega_mech_res_calc_ip = Global_Data.av.pl_interface.omega_mech_rad_s;
	rpm_mech_res_calc_ip = Global_Data.av.pl_interface.n_mech_rpm;

    theta_mech_resolver_ip = theta_mech_calc_from_resolver + theta_m_offset;
    theta_elec_resolver_ip = theta_mech_calc_from_resolver*5.0f + theta_m_offset*5.0f;

    Global_Data.av.theta_m_mod = uz_modf(theta_mech_resolver_ip, 6.2830f);
    Global_Data.av.theta_el_mod = uz_modf(theta_elec_resolver_ip, 6.2830f);


    speed_rpm_resolver_ip = Global_Data.av.mechanicalRotorSpeed;

    if (reset_ip_cnt == true) {
//    uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x104, true);
    } else {
//   	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x104, false);
    }

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

        // reset SW and FPGA resolver calculation counter for having defined init state
        if (first_ISR == true) {
        	cnt=0;
        	cnt_float=0.0f;
        	first_ISR=false;
//        	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_UZ_RESOLVER_MECH_REV_0_BASEADDR + 0x104, false);
        }

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


float uz_modf(float u0, float u1)
{
  float q;
  float y;
  _Bool yEq;
  y = u0;
  if (u1 == 0.0f) {
    if (u0 == 0.0f) {
      y = u1;
    }
  } else if (u0 == 0.0f) {
    y = 0.0f / u1;
  } else {
    y = fmodf(u0, u1);
    yEq = (y == 0.0f);
    if ((!yEq) && (u1 > floorf(u1))) {
      q = fabsf(u0 / u1);
      yEq = (fabsf(q - floorf(q + 0.5f)) <= FLT_EPSILON * q);
    }

    if (yEq) {
      y = 0.0f;
    } else if ((u0 < 0.0f) != (u1 < 0.0f)) {
      y += u1;
    }
  }

  return y;
}
