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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_spwm/uz_spwm.h"
#include "../uz/uz_math_constants.h"
#include "../include/FOC.h"
#include "../uz/uz_signals/uz_signals.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;
extern base_val_t inverse_base_val;


uz_6ph_abc_t six_ph_currents = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta = {0.0f};
uz_3ph_alphabeta_t three_ph_alphabeta = {0.0f};
uz_3ph_dq_t rotating_dq = {0};
uz_3ph_dq_t rotating_xy = {0};
uz_6ph_dq_t six_ph_dq = {0};

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

// conversion defines for ADC readings
//#define PHASE_CURRENT_CONV	16.75f
#define PHASE_CURRENT_CONV	11.65f
//#define DC_VOLT_CONV_1	140.27f
#define DC_VOLT_CONV_1		99.35f
//#define DC_VOLT_OFF_1		450.25f
#define DC_VOLT_OFF_1		450.25f
//#define DC_VOLT_CONV_2	141.28f
#define DC_VOLT_CONV_2		99.35f
#define DC_VOLT_OFF_2		450.25f
#define TORQUE_CONV			20.0f // 20Nm/V
// software current limit
#define MAX_PHASE_CURRENT_AMP  12.0f
#define MAX_DC_VOLT 590.0f

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

    //get resolver data
    Global_Data.av.resolver_pl_interface = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface);
    Global_Data.av.theta_elec_rad_ip = Global_Data.av.resolver_pl_interface.position_el_2pi;
    Global_Data.av.theta_mech_rad_ip = Global_Data.av.resolver_pl_interface.position_mech_2pi;
    Global_Data.av.mechanicalRotorSpeedRPM_ip = Global_Data.av.resolver_pl_interface.n_mech_rpm;
    Global_Data.av.mechanicalRotorSpeedRADpS_ip = Global_Data.av.resolver_pl_interface.omega_mech_rad_s;
//    Global_Data.av.electricalRotorSpeedRPM = Global_Data.av.mechanicalRotorSpeedRPM_ip*Global_Data.av.polepairs;
    Global_Data.av.electricalRotorSpeedRADpS = Global_Data.av.mechanicalRotorSpeedRADpS_ip*Global_Data.av.polepairs;

    //get ADC data
    // convert ADC readings to currents in Amps
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    // convert ADC readings to voltages
    Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A4 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_dc2 =Global_Data.aa.A2.me.ADC_A4 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    // convert ADC reading to torque
//    Global_Data.av.torque = Global_Data.aa.A3.me.ADC_A1 * TORQUE_CONV;


    // check current limit
	if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
		ultrazohm_state_machine_set_stop(true);
	}

	// check fast fpga current limit violation
	if (uz_axi_read_bool(XPAR_UZ_USER_UZ_CUR_LIM_0_BASEADDR + 0x108) == true) {
		ultrazohm_state_machine_set_stop(true);
		Global_Data.av.overcurrent_FPGA = true;
		Global_Data.av.overcurrent_FPGA_fl = 1.0f;
	} else {
		Global_Data.av.overcurrent_FPGA = false;
		Global_Data.av.overcurrent_FPGA_fl = 0.0f;
	}

	// check DC Bus voltage limit
	if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
			ultrazohm_state_machine_set_stop(true);
	}

	// check inverter fault
//	if(uz_axi_gpio_read_pin_zero_based(Global_Data.objects.inv_fault_in, 0U) == true || uz_axi_gpio_read_pin_zero_based(Global_Data.objects.inv_fault_in, 1U) == true) {
//		ultrazohm_state_machine_set_stop(true);
//	}

    // VSD transform phase currents
    six_ph_currents.a1 = Global_Data.av.i_a1;
    six_ph_currents.b1 = Global_Data.av.i_b1;
    six_ph_currents.c1 = Global_Data.av.i_c1;
    six_ph_currents.a2 = Global_Data.av.i_a2;
    six_ph_currents.b2 = Global_Data.av.i_b2;
    six_ph_currents.c2 = Global_Data.av.i_c2;
    six_ph_alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_currents);

    Global_Data.av.i_alpha = six_ph_alphabeta.alpha;
    Global_Data.av.i_beta = six_ph_alphabeta.beta;
    Global_Data.av.i_X = six_ph_alphabeta.x;
    Global_Data.av.i_Y = six_ph_alphabeta.y;

    // Park transform alpha/beta currents
//    three_ph_alphabeta.alpha = six_ph_alphabeta.alpha;
//    three_ph_alphabeta.beta = six_ph_alphabeta.beta;
//    rotating_dq = uz_transformation_3ph_alphabeta_to_dq(three_ph_alphabeta, Global_Data.av.theta_elec_rad_ip);
//    Global_Data.av.i_d = rotating_dq.d;
//    Global_Data.av.i_q = rotating_dq.q;

    // Park transform alpha/beta currents with positive turning, and XY currents with negative turning angle
    six_ph_dq = uz_transformation_asym30deg_6ph_alphabeta_XY_to_dq_xy(six_ph_alphabeta, Global_Data.av.theta_elec_rad_ip, 2*UZ_PIf-Global_Data.av.theta_elec_rad_ip);
    Global_Data.av.i_d = six_ph_dq.d;
    Global_Data.av.i_q = six_ph_dq.q;
    Global_Data.av.i_x = six_ph_dq.x;
    Global_Data.av.i_y = six_ph_dq.y;

    // p.u. convert currents for control
    Global_Data.av.i_d_pu = Global_Data.av.i_d*inverse_base_val.IB;
    Global_Data.av.i_q_pu = Global_Data.av.i_q*inverse_base_val.IB;
    Global_Data.av.i_x_pu = Global_Data.av.i_x*inverse_base_val.IB;
    Global_Data.av.i_y_pu = Global_Data.av.i_y*inverse_base_val.IB;
    Global_Data.av.omega_mech_pu = Global_Data.av.mechanicalRotorSpeedRADpS_ip*inverse_base_val.omegaB;
    Global_Data.av.omega_el_pu = Global_Data.av.electricalRotorSpeedRADpS*inverse_base_val.omegaB;
    Global_Data.av.i_d_ref_pu = Global_Data.av.i_d_ref*inverse_base_val.IB;
    Global_Data.av.i_q_ref_pu = Global_Data.av.i_q_ref*inverse_base_val.IB;
    Global_Data.av.i_x_ref_pu = Global_Data.av.i_x_ref*inverse_base_val.IB;
    Global_Data.av.i_y_ref_pu = Global_Data.av.i_y_ref*inverse_base_val.IB;
    Global_Data.av.v_dc1_pu = Global_Data.av.v_dc1*inverse_base_val.VB;

    // assign to structs
    i_dq_actual.d = Global_Data.av.i_d;
    i_dq_actual.q = Global_Data.av.i_q;

	i_dq_ref.d = Global_Data.av.i_d_ref;
	i_dq_ref.q = Global_Data.av.i_q_ref;




    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==idle_state)
    {
    	uz_CurrentControl_reset(Global_Data.objects.foc_current);
//    	uz_axi_write_bool(XPAR_UZ_CUR_LIM_0_BASEADDR + 0x104, true); //reset overcurrent IP

    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
    }

    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.foc_current, i_dq_ref, i_dq_actual, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
    	alphabeta_ref_volts = uz_transformation_3ph_dq_to_alphabeta(u_dq_ref, Global_Data.av.theta_elec_rad_ip);
    	vsd_ref_volts.alpha = alphabeta_ref_volts.alpha;
    	vsd_ref_volts.beta = alphabeta_ref_volts.beta;
    	phase_ref_volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(vsd_ref_volts);

    	input1.a = phase_ref_volts.a1;
    	input1.b = phase_ref_volts.b1;
    	input1.c = phase_ref_volts.c1;
    	input2.a = phase_ref_volts.a2;
    	input2.b = phase_ref_volts.b2;
    	input2.c = phase_ref_volts.c2;

    	output1 = uz_spwm_abc(input1, Global_Data.av.v_dc1);
    	output2 = uz_spwm_abc(input2, Global_Data.av.v_dc2);

    	if(Global_Data.rasv.current_ctrl_select == IMPL_MOD) {
    		// ATTENTION those are actually 1 minus dutycyc, see javascope.c
    	    Global_Data.rasv.halfBridge1DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[0], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge2DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[1], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge3DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[2], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge4DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[3], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge5DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[4], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge6DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[5], 1.0f, 0.0f);
    		// ATTENTION

    	} else {
    		Global_Data.rasv.halfBridge1DutyCycle = output1.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = output1.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = output1.DutyCycle_C;
    		Global_Data.rasv.halfBridge4DutyCycle = output2.DutyCycle_A;
    		Global_Data.rasv.halfBridge5DutyCycle = output2.DutyCycle_B;
    		Global_Data.rasv.halfBridge6DutyCycle = output2.DutyCycle_C;
    	}

    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

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
