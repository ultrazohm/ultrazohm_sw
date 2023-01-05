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
#include "../IP_Cores/uz_dac_interface/uz_dac_interface.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../uz/uz_math_constants.h"
#include "../IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "../IP_Cores/uz_pmsm6ph_transformation/uz_pmsm6ph_transformation.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;

float amplitude1 = 4.0f;
float frequency1 = 250.0f;
float offset1 = 0.0f;
float phase1 = 0.0f;

float amplitude2 = 4.0f;
float frequency2 = 250.0f;
float offset2 = 0.0f;
float phase2 = UZ_PIf/6.0f;

uz_3ph_abc_t three_phase1, three_phase1, three_phase2, three_phase22;

float dac_input[8]={-1.0f, -1.5f, -2.0f, -2.5f, -3.0f, -3.5f, -4.0f, -4.5f};

                uz_array_float_t dac_input_array={
                .data=&dac_input[0],
                .length=UZ_ARRAY_SIZE(dac_input)
            };

// 2x3ph PMSM parameters
const uz_PMSM_6ph_t dengine={
		.R_ph_Ohm=0.2615f,
		.Ld_Henry=0.0018f,
		.Lq_Henry=0.0038f,
		.Lx_Henry=0.0024f,
		.Ly_Henry=0.0025f,
		.polePairs=5.0f,
		.Psi_PM_Vs=0.19f
};

// 2x3ph PMSM rated values
const rated_val_t rated_val={
		.VR=400.0f,
		.IR=7.071f,
//		.IR=14.142f,
		.nR=3000.0f
};

// p.u. base values
const base_val_t base_val={
		.VB=sqrt(2.0f/3.0f)*rated_val.VR,
		.IB=sqrt(2.0f)*rated_val.IR,
		.omegaB=rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs,
		.ZB=(sqrt(2.0f/3.0f)*rated_val.VR)/(sqrt(2.0f)*rated_val.IR),
		.LB=(sqrt(2.0f/3.0f)*rated_val.VR)/(sqrt(2.0f)*rated_val.IR)/(rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs),
		.psiB=(sqrt(2.0f/3.0f)*rated_val.VR)/(rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs)
};

const float Ts = 1.0f/UZ_PWM_FREQUENCY;

//pre-calculated factors for delay compensation and prediction model
const pre_calc_val_t pre_calc_val={
		.Rs_over_ZB = dengine.R_ph_Ohm/base_val.ZB,
		.Ts_times_ZB_over_Ld = Ts*base_val.ZB/dengine.Ld_Henry,
		.Ts_times_ZB_over_Lq = Ts*base_val.ZB/dengine.Lq_Henry,
		.Ts_times_ZB_over_Lx = Ts*base_val.ZB/dengine.Lx_Henry,
		.Ts_times_ZB_over_Ly = Ts*base_val.ZB/dengine.Ly_Henry,
		.Ld_over_LB = dengine.Ld_Henry/base_val.LB,
		.Lq_over_LB = dengine.Lq_Henry/base_val.LB,
		.psi_pm_over_psiB = dengine.Psi_PM_Vs/base_val.psiB
};

uint32_t test_index = 42;
float test_angle = 0.0;

float id_ref = 0.0f;
float iq_ref = 0.0f;
float ix_ref = 0.0f;
float iy_ref = 0.0f;

float lambda_d = 1.0f;
float lambda_q = 1.0f;
float lambda_x = 1.0f;
float lambda_y = 1.0f;
float lambda_u = 0.000f;

uz_6ph_abc_t pmsm_ph_currents = {0};


// pointers to initalized IP-cores and others from main
extern uz_pmsm_model6ph_dq_t *pmsm;
extern uz_PWM_SS_2L_t *pwm_instance_1;
extern uz_PWM_SS_2L_t *pwm_instance_2;
extern uz_pmsm6ph_transformation_t *transformation_6ph;

// data storage for PMSM
struct uz_pmsm_model6ph_dq_outputs_general_t pmsm_outputs = {
    .torque = 0.0f,
    .omega_mech = 0.0f,
    .theta_el = 0.0f};
float load_torque = 0.0f;
float setp_omega = 0.0f;// 16.6f*2.0f*M_PI;
float setp_rpm = 0.0f;






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

    setp_omega = setp_rpm / 60.0f * 2.0f * M_PI;
    // set use PL interfaces for PMSM
    uz_pmsm_model6ph_dq_set_use_axi_input(pmsm,false);

    // read and write general outputs and inputs from PMSM
    pmsm_outputs = uz_pmsm_model6ph_dq_get_outputs_general(pmsm);
    uz_pmsm_model6ph_dq_set_inputs_general(pmsm,setp_omega,load_torque);

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

    //Global_Data.objects.three_phase1 = uz_wavegen_three_phase_sample(amplitude1, frequency1, offset1, phase1);
    //Global_Data.objects.three_phase2 = uz_wavegen_three_phase_sample(amplitude2, frequency2, offset2, phase2);
    //Global_Data.av.theta_elec = uz_wavegen_sawtooth(2*UZ_PIf, frequency1);
    //Global_Data.av.theta_elec = test_angle*UZ_PIf/180.0;

    //uz_axi_write_int32(XPAR_UZ_USER_UZ_PARK_TRANSFORM_IP_0_BASEADDR+0x100, uz_convert_float_to_sfixed(Global_Data.av.theta_elec, 14));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_PARK_TRANSFORM_IP_0_BASEADDR+0x100, uz_convert_float_to_sfixed(1.0f, 14));

    //write offset angle to park transform ip core
    uz_axi_write_int32(XPAR_UZ_USER_UZ_PARK_TRANSFORM_IP_0_BASEADDR+0x104, uz_convert_float_to_sfixed(0.0f, 14)); //no offset

//    dac_input[0]=Global_Data.objects.three_phase1.a;
//    dac_input[1]=Global_Data.objects.three_phase1.b;
//    dac_input[2]=Global_Data.objects.three_phase1.c;
//    dac_input[3]=Global_Data.objects.three_phase2.a;
//    dac_input[4]=Global_Data.objects.three_phase2.b;
//    dac_input[5]=Global_Data.objects.three_phase2.c;

    uz_dac_interface_set_ouput_values(Global_Data.objects.dac_instance,&dac_input_array);

    // read p.u. phase currents from ip-core
    Global_Data.av.ia1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x180),15);
    Global_Data.av.ib1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x184),15);
    Global_Data.av.ic1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x188),15);
    Global_Data.av.ia2 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x18C),15);
    Global_Data.av.ib2 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x190),15);
    Global_Data.av.ic2 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PU_CON_IP_0_BASEADDR+0x194),15);

    // read SI phase currents from pmsm ip-core
    pmsm_ph_currents = uz_pmsm6ph_transformation_get_currents(transformation_6ph);
    Global_Data.av.ia1_cil = pmsm_ph_currents.a1;
    Global_Data.av.ib1_cil = pmsm_ph_currents.b1;
    Global_Data.av.ic1_cil = pmsm_ph_currents.c1;
    Global_Data.av.ia2_cil = pmsm_ph_currents.a2;
    Global_Data.av.ib2_cil = pmsm_ph_currents.b2;
    Global_Data.av.ic2_cil = pmsm_ph_currents.c2;
    Global_Data.av.theta_elec = uz_pmsm6ph_transformation_get_theta_el(transformation_6ph);

    // read VSD currents from ip-core
    Global_Data.av.alpha = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x100),11);
    Global_Data.av.beta = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x104),11);
    Global_Data.av.y1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x108),11);
    Global_Data.av.x1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x10C),11);
    Global_Data.av.z1 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x110),11);
    Global_Data.av.z2 = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_VSD_6PH_IP_0_BASEADDR+0x114),11);

    // read dq currents from ip-core
    Global_Data.av.I_d = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PARK_TRANSFORM_IP_0_BASEADDR+0x108), 16);
    Global_Data.av.I_q = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_PARK_TRANSFORM_IP_0_BASEADDR+0x10C), 16);

    // read p.u. voltages according to index
    //uz_axi_write_uint32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR+0x104, test_index); //write index via AXI
    Global_Data.av.ud_pu = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR+0x108), 24);
    Global_Data.av.uq_pu = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR+0x10C), 24);
    Global_Data.av.ux_pu = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR+0x110), 24);
    Global_Data.av.uy_pu = uz_convert_sfixed_to_float(uz_axi_read_int32(XPAR_UZ_USER_UZ_6_PH_VOLTAGES_IP_0_BASEADDR+0x114), 24);

    // read delay compensation currents from ip-core
    //uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR+0x100, uz_convert_float_to_sfixed(frequency1/dengine.polePairs*2.0f*UZ_PIf/base_val.omegaB, 15));
    Global_Data.av.id_delay = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR+0x104), 24);
    Global_Data.av.iq_delay = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR+0x108), 24);
    Global_Data.av.ix_delay = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR+0x10C), 24);
    Global_Data.av.iy_delay = uz_convert_sfixed_to_float(uz_axi_read_uint32(XPAR_UZ_USER_UZ_6PH_DELAY_IP_0_BASEADDR+0x110), 24);

    // cost
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x100, uz_convert_float_to_sfixed(id_ref/base_val.IB, 11));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x104, uz_convert_float_to_sfixed(iq_ref/base_val.IB, 11));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x108, uz_convert_float_to_sfixed(ix_ref/base_val.IB, 11));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x10C, uz_convert_float_to_sfixed(iy_ref/base_val.IB, 11));

    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x114, uz_convert_float_to_sfixed(lambda_d, 17));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(lambda_q, 17));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x11C, uz_convert_float_to_sfixed(lambda_x, 17));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x120, uz_convert_float_to_sfixed(lambda_y, 17));
    uz_axi_write_int32(XPAR_UZ_USER_UZ_6PH_COST_IP_0_BASEADDR + 0x124, uz_convert_float_to_sfixed(lambda_u, 17));

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
