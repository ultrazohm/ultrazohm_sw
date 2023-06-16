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

// Data for PMSM
#include "../IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
extern uz_pmsm_model6ph_dq_t *pmsm;
float omega_mech = 100.0f;
float load_torque = 0.0f;
struct uz_pmsm_model6ph_dq_outputs_general_t pmsm_output = {0};

// Data for Transformation
#include "../IP_Cores/uz_pmsm6ph_transformation/uz_pmsm6ph_transformation.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
extern uz_pmsm6ph_transformation_t *transformation;
uz_6ph_abc_t transformation_currents_abc = {0};
float theta_el = 0.0f;

// Data for PI
#include "../uz/uz_piController/uz_piController.h"
extern uz_PI_Controller *PI_d_current;
extern uz_PI_Controller *PI_q_current;
uz_6ph_dq_t transformed_currents = {0};
uz_3ph_dq_t setp_currents = {0};
uz_6ph_dq_t output_voltage_dq = {0};
uz_6ph_abc_t out_voltage_abc = {0};
uz_3ph_abc_t out_voltage_abc1 = {0};
uz_3ph_abc_t out_voltage_abc2 = {0};

// Data for PWM
float V_dc_volts = 100.0f;

// Data for FOC PS
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_space_vector_modulation/uz_space_vector_modulation.h"
uz_3ph_dq_t i_actual_3ph = {0};
uz_3ph_dq_t u_ref_3ph = {0};
uz_6ph_dq_t u_ref_6ph = {0};
uz_3ph_dq_t i_ref = {0};
extern uz_CurrentControl_t* cc_instance;
struct uz_DutyCycle_2x3ph_t duty_cycle = {0};

// Data for FOC PL
#include "../IP_Cores/uz_FOC/xuz_foc.h"
extern XUz_foc FOC_ip_instance;
bool reset = false;
uint32_t* int_idref = (uint32_t*)&i_ref.d;
uint32_t* int_iqref = (uint32_t*)&i_ref.q;


uz_PI_Controller *PI_d_current=NULL;
uz_PI_Controller *PI_q_current=NULL;
extern uint32_t* int_KI;
extern uint32_t* int_KP;
extern uint32_t* int_limit;
extern uint32_t* int_ts;

// settings
extern bool openhw_pspl;
extern float openhw_udc;


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

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
    //update_speed_and_position_of_encoder_on_D5(&Global_Data);

    ///////////////////////////////////////////
        ////////////////////CIL////////////////////
        ///////////////////////////////////////////
    	  uz_pmsm_model6ph_dq_set_inputs_general(pmsm,omega_mech,load_torque);                                          // set omega and load torque (only one active)
    	  pmsm_output = uz_pmsm_model6ph_dq_get_outputs_general(pmsm);                                                  // read outputs from PMSM
    	  transformation_currents_abc = uz_pmsm6ph_transformation_get_currents(transformation);                         // read current from transformation
    	  theta_el = uz_pmsm6ph_transformation_get_theta_el(transformation);											// read theta from transformation
    	  transformed_currents = uz_transformation_asym30deg_6ph_abc_to_dq(transformation_currents_abc, theta_el);      // transform currents


        platform_state_t current_state=ultrazohm_state_machine_get_state();
        if (current_state==control_state)
        {
        	///////////////////////////////////////////
    		////////////////////FOC////////////////////
    		///////////////////////////////////////////
            switch(openhw_pspl){
            case false:
            	XUz_foc_Set_axi_id_reference(&FOC_ip_instance, *int_idref);
            	XUz_foc_Set_axi_iq_reference(&FOC_ip_instance, *int_iqref);
            	XUz_foc_Set_axi_id_KI(&FOC_ip_instance, *int_KI);
				XUz_foc_Set_axi_id_KP(&FOC_ip_instance, *int_KP);
				XUz_foc_Set_axi_limit(&FOC_ip_instance, *int_limit);
				XUz_foc_Set_axi_sampletime(&FOC_ip_instance, *int_ts);
				XUz_foc_Set_axi_iq_KI(&FOC_ip_instance, *int_KI);
				XUz_foc_Set_axi_iq_KP(&FOC_ip_instance, *int_KP);
            	break;
            case true:
            	i_actual_3ph.d = transformed_currents.d;
            	i_actual_3ph.q = transformed_currents.q;
            	u_ref_3ph = uz_CurrentControl_sample(cc_instance, i_ref, i_actual_3ph, openhw_udc, pmsm_output.omega_mech);
            	u_ref_6ph.d = u_ref_3ph.d;
            	u_ref_6ph.q = u_ref_3ph.q;
            	duty_cycle = uz_FOC_generate_DutyCycles_6ph(uz_transformation_asym30deg_6ph_dq_to_abc(u_ref_6ph, theta_el), openhw_udc);
            	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, duty_cycle.system1.DutyCycle_A, duty_cycle.system1.DutyCycle_B, duty_cycle.system1.DutyCycle_C);
            	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, duty_cycle.system2.DutyCycle_A, duty_cycle.system2.DutyCycle_B, duty_cycle.system2.DutyCycle_C);
            	break;
            default: assert(0); break;
            }
        }

        // Reset both controller
    	if(reset){
    		XUz_foc_Set_axi_reset(&FOC_ip_instance, true);
    		uz_CurrentControl_reset(cc_instance);
    	}else{
    		XUz_foc_Set_axi_reset(&FOC_ip_instance, false);
    	}

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
