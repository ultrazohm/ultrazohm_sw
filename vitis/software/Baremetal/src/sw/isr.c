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

//test
float I_d_test = 0.0f;
float I_q_test = 0.0f;

//FOC and speed control
struct uz_3ph_abc_t measurement_current = {0};
struct uz_3ph_abc_t measurement_voltage = {0};
struct uz_3ph_dq_t dq_measurement_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_ref_Volts = {0};
struct uz_DutyCycle_t output = {0};
struct uz_3ph_abc_t uvw_ref = {0};
float omega_el_rad_per_sec = 0.0f;
float omega_m_rad_per_sec = 0.0f;
bool ext_clamping = false;
int flg_ParameterID = 0U;

//Parameter ID
extern uz_ParameterID_Data_t ParaID_Data;
extern uz_ParameterID_t* ParameterID;
struct uz_3ph_dq_t ParaID_v_dq = {0};
struct uz_DutyCycle_t ParaID_DutyCycle = {0};

// Conversion factors for current and voltage
#define NUMBER_OF_TURNS_CURRENT_MEASURING 3.0f
#define ADC_CURRENT_SCALING	  80.0f/NUMBER_OF_TURNS_CURRENT_MEASURING
#define ADC_CURRENT_OFFSET    2.5f //Offset for LEM Sensors
#define DC_VOLT_CONV		  12.5f
#define ADC_PH_VOLT_OFFSET	  2.5f
#define USE_RESOLVER		  1U	// 0U: IncrementalEncoder on D5, 1U: Resolver on D4
#define MAX_CURRENT_ASSERTION	25.0f
#define MAX_SPEED_ASSERTION		1000.0f
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
    // Read Encoder
    if(USE_RESOLVER == 0U){
    	// Use Encoder with following assignments
    	// Global_Data.av.theta_el in rad --> Uses UZ_D5_MOTOR_POLE_PAIR_NUMBER of global_configuration
    	// Global_Daata.av.mechanicalRotorSpeed and mechanicalRotorSpeed_filtered in rpm
    	update_speed_and_position_of_encoder_on_D5(&Global_Data);
    } else{
    	// Use Resolver on D4 with following assignments
    	// Global_Data.av.mechanicalRotorSpeed in rpm
    	// Global_Data.av.theta_mech in rad
    	update_position_and_speed_of_resolverIP(&Global_Data);
    }
    //theta offset and theta elec
    if(USE_RESOLVER == 0){
    	// Only theta_elec available from IPCore
    	Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    } else {
    	// offset values for theta_mech 3.106790
    	// 0.1255947
    	// 6.221634
    	// 3.473124
    	// 3.102956
      	Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    }

    // convert ADC currents
    measurement_current.a = ADC_CURRENT_SCALING * (Global_Data.aa.A1.me.ADC_A1 - ADC_CURRENT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors
    measurement_current.b = ADC_CURRENT_SCALING * (Global_Data.aa.A1.me.ADC_A2 - ADC_CURRENT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors
    measurement_current.c = ADC_CURRENT_SCALING * (Global_Data.aa.A1.me.ADC_A3 - ADC_CURRENT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors
    dq_measurement_current = uz_transformation_3ph_abc_to_dq(measurement_current, Global_Data.av.theta_elec);

    if ((fabs(measurement_current.a) > MAX_CURRENT_ASSERTION) || (fabs(measurement_current.b) > MAX_CURRENT_ASSERTION) || (fabs(measurement_current.c) > MAX_CURRENT_ASSERTION) || (fabs(Global_Data.av.mechanicalRotorSpeed) > MAX_SPEED_ASSERTION)){
    	// Assertion
    	output.DutyCycle_U=0.0f;
    	output.DutyCycle_V=0.0f;
    	output.DutyCycle_W=0.0f;
    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
    	ultrazohm_state_machine_set_stop(true);
    }


    measurement_voltage.a = DC_VOLT_CONV * (Global_Data.aa.A1.me.ADC_B5 - ADC_PH_VOLT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors
    measurement_voltage.b = DC_VOLT_CONV * (Global_Data.aa.A1.me.ADC_B6- ADC_PH_VOLT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors
    measurement_voltage.c = DC_VOLT_CONV * (Global_Data.aa.A1.me.ADC_B7- ADC_PH_VOLT_OFFSET);// Values have to be adjusted to ADC Place and to Current sensors

    Global_Data.av.U_ZK = DC_VOLT_CONV * Global_Data.aa.A1.me.ADC_A4;

    // Calculating I_d and I_q from I_set and angle
    I_q_test = sinf(Global_Data.rasv.I_angle/180.0f*M_PI)*Global_Data.rasv.I_set;
	I_d_test = cosf(Global_Data.rasv.I_angle/180.0f*M_PI)*Global_Data.rasv.I_set;

    // calculating values needed for control
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * (2.0f * M_PI) / 60.0f;// w_mech
    omega_el_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * Global_Data.av.polepairs * (2.0f * M_PI) / 60.0f;

    if (flg_ParameterID == 1U){
    	// Actual Values
	    ParaID_Data.ActualValues.V_DC = Global_Data.av.U_ZK;
	    ParaID_Data.ActualValues.omega_m = omega_m_rad_per_sec;
	    ParaID_Data.ActualValues.omega_el = omega_el_rad_per_sec;
	    ParaID_Data.ActualValues.theta_el = Global_Data.av.theta_elec;
	    ParaID_Data.ActualValues.I_abc = measurement_current;
	    ParaID_Data.ActualValues.V_abc = measurement_voltage;

	    //Calculate missing ActualValues
	    ParaID_Data.ActualValues.i_dq = dq_measurement_current;
	    ParaID_Data.ActualValues.v_dq = uz_transformation_3ph_abc_to_dq(measurement_voltage, Global_Data.av.theta_elec);
	    ParaID_Data.ActualValues.theta_m = Global_Data.av.theta_mech;

	    //Reference values
	    ParaID_Data.GlobalConfig.n_ref = Global_Data.rasv.n_ref_rpm;
	    ParaID_Data.GlobalConfig.i_dq_ref.d = Global_Data.rasv.i_d_ref;
	    ParaID_Data.GlobalConfig.i_dq_ref.d = Global_Data.rasv.i_q_ref;
    }

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	if (flg_ParameterID == 0U){
			if (Global_Data.av.flg_speed_control){
				dq_reference_current = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_el_rad_per_sec, Global_Data.rasv.n_ref_rpm, Global_Data.av.U_ZK, dq_reference_current.d);
			} else {
				dq_reference_current.d = Global_Data.rasv.i_d_ref;
				dq_reference_current.q = Global_Data.rasv.i_q_ref;
				dq_reference_current.zero = 0.0f;
			}
			 dq_ref_Volts = uz_FOC_sample(Global_Data.objects.FOC_instance, dq_reference_current, dq_measurement_current, Global_Data.av.U_ZK, omega_el_rad_per_sec);
			 uvw_ref = uz_transformation_3ph_dq_to_abc(dq_ref_Volts, Global_Data.av.theta_elec);
			 output = uz_FOC_generate_DutyCycles(uvw_ref, 24.0f);
			 uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
    	} else{
    		uz_ParameterID_step(ParameterID, &ParaID_Data);
    		ParaID_v_dq = uz_ParameterID_Controller(&ParaID_Data, Global_Data.objects.FOC_instance, Global_Data.objects.Speed_instance);
            ParaID_DutyCycle = uz_ParameterID_generate_DutyCycle(&ParaID_Data, ParaID_v_dq, Global_Data.objects.pwm_d1_pin_0_to_5);

        	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, ParaID_DutyCycle.DutyCycle_U, ParaID_DutyCycle.DutyCycle_V, ParaID_DutyCycle.DutyCycle_W);
    	}
	}else{
    	output.DutyCycle_U=0.0f;
    	output.DutyCycle_V=0.0f;
    	output.DutyCycle_W=0.0f;
    	uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_U, output.DutyCycle_V, output.DutyCycle_W);
    	uz_FOC_reset(Global_Data.objects.FOC_instance);
    	uz_SpeedControl_reset(Global_Data.objects.Speed_instance);
    }
 //   uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
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
