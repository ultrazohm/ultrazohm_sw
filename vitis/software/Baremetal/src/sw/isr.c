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
#include "../uz/uz_Transformation/uz_Transformation.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;


// software limits
#define MAX_PHASE_CURRENT_AMP  20.0f
#define MAX_DC_VOLT 590.0f
#define MAX_TEMP_DEG 90.0f

// start uz tempcard
#include "../IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
void uz_TempCard_Measurement(DS_Data* Data);
// end uz tempcard

// start PWM freq temp measurement
#include "../IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
void uz_PWM_duty_freq_detection(DS_Data* Data);
// end PWM freq temp measurement

// start ADC readings
#define PHASE_CURRENT_CONV	16.75f
#define DC_VOLT_CONV		140.27f
void uz_ADC_currents(DS_Data* Data);
void uz_ADC_voltages(DS_Data* Data);
// end ADC readings

// for inverter test
#include "../uz/uz_wavegen/uz_wavegen.h"
uz_3ph_abc_t out_wavegen = {0};
float amplitude = 0.2f;

// control
void uz_transformations(uz_9ph_abc_t abc_in, uz_9ph_dq_t* full_dq, uz_3ph_dq_t* dq, uz_3ph_alphabeta_t* XY1, uz_3ph_alphabeta_t* XY2, uz_3ph_alphabeta_t* XY3, float theta);


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
    // read speed and angle
    Global_Data.av.rotational_position = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d2);

    // actual values reading functions
    uz_PWM_duty_freq_detection(&Global_Data);
    uz_TempCard_Measurement(&Global_Data);
    uz_ADC_currents(&Global_Data);
    uz_ADC_voltages(&Global_Data);

    // transformations
    uz_transformations(Global_Data.av.currents_abc, &Global_Data.av.full_currents_dq, &Global_Data.av.currents_dq, &Global_Data.av.currents_XY1, &Global_Data.av.currents_XY2, &Global_Data.av.currents_XY3, Global_Data.av.rotational_position.position_el_2pi);

	// check current limit
	if(fabs(Global_Data.av.currents_abc.a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.currents_abc.a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c2) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.currents_abc.a3) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.b3) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.currents_abc.c3) > MAX_PHASE_CURRENT_AMP) {
		uz_assert(0);
	}
	// check DC Bus
	if(fabs(Global_Data.av.U_ZK1) > MAX_DC_VOLT || fabs(Global_Data.av.U_ZK2) > MAX_DC_VOLT || fabs(Global_Data.av.U_ZK3) > MAX_DC_VOLT) {
			uz_assert(0);
	}
	// check inverter temp
	if(fabs(Global_Data.av.temperature_inv_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temperature_inv_2) > MAX_TEMP_DEG || fabs(Global_Data.av.temperature_inv_3) > MAX_TEMP_DEG) {
		//uz_assert(0);
	}

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	out_wavegen = uz_wavegen_three_phase_sample(amplitude, 50.0f, 0.5f);
    	Global_Data.rasv.halfBridge1DutyCycle = out_wavegen.a;
    	Global_Data.rasv.halfBridge2DutyCycle = out_wavegen.b;
    	Global_Data.rasv.halfBridge3DutyCycle = out_wavegen.c;
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

// user functions
void uz_transformations(uz_9ph_abc_t abc_in, uz_9ph_dq_t* full_dq, uz_3ph_dq_t* dq, uz_3ph_alphabeta_t* XY1, uz_3ph_alphabeta_t* XY2, uz_3ph_alphabeta_t* XY3, float theta){
	*full_dq = uz_transformation_9ph_abc_to_dq(abc_in, theta);
	dq->d = full_dq->d;
	dq->q = full_dq->q;
	XY1->alpha = full_dq->x1;
	XY1->beta = full_dq->y1;
	XY2->alpha = full_dq->x2;
	XY2->beta = full_dq->y2;
	XY3->alpha = full_dq->x3;
	XY3->beta = full_dq->y3;
}

void uz_ADC_currents(DS_Data* Data){
	// convert ADC readings to currents in Amps
	Data->av.currents_abc.a1 = Data->aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.b1 = Data->aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.c1 = Data->aa.A1.me.ADC_A1 * PHASE_CURRENT_CONV;
	Data->av.i_ZK1 = Data->aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a2 = Data->aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.b2 = Data->aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.c2 = Data->aa.A2.me.ADC_A1 * PHASE_CURRENT_CONV;
	Data->av.i_ZK2 = Data->aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.a3 = Data->aa.A3.me.ADC_A3 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.b3 = Data->aa.A3.me.ADC_A2 * PHASE_CURRENT_CONV;
	Data->av.currents_abc.c3 = Data->aa.A3.me.ADC_A1 * PHASE_CURRENT_CONV;
	Data->av.i_ZK3 = Data->aa.A3.me.ADC_B5 * PHASE_CURRENT_CONV;
}

void uz_ADC_voltages(DS_Data* Data){
	// convert ADC readings to voltages
	Data->av.U_ZK1 = Data->aa.A1.me.ADC_A4 * DC_VOLT_CONV + 591.3f;
	Data->av.voltages_abc.a1 = Data->aa.A1.me.ADC_B8 * DC_VOLT_CONV + 616.0f;
	Data->av.voltages_abc.b1 = Data->aa.A1.me.ADC_B7 * DC_VOLT_CONV + 614.8f;
	Data->av.voltages_abc.c1 = Data->aa.A1.me.ADC_B6 * DC_VOLT_CONV + 611.5f;
	Data->av.U_ZK2 = Data->aa.A2.me.ADC_A4 * DC_VOLT_CONV;
	Data->av.voltages_abc.a2 = Data->aa.A2.me.ADC_B8 * DC_VOLT_CONV;
	Data->av.voltages_abc.b2 = Data->aa.A2.me.ADC_B7 * DC_VOLT_CONV;
	Data->av.voltages_abc.c2 = Data->aa.A2.me.ADC_B6 * DC_VOLT_CONV;
	Data->av.U_ZK3 = Data->aa.A3.me.ADC_A4 * DC_VOLT_CONV;
	Data->av.voltages_abc.a3 = Data->aa.A3.me.ADC_B8 * DC_VOLT_CONV;
	Data->av.voltages_abc.b3 = Data->aa.A3.me.ADC_B7 * DC_VOLT_CONV;
	Data->av.voltages_abc.c3 = Data->aa.A3.me.ADC_B6 * DC_VOLT_CONV;
}

void uz_PWM_duty_freq_detection(DS_Data* Data){
	struct uz_PWM_duty_freq_detection_outputs_t temp_output;
	// start PWM freq temp measurement
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement1);
	Data->av.temperature_inv_1 = temp_output.TempDegreesCelsius;
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement2);
	Data->av.temperature_inv_2 = temp_output.TempDegreesCelsius;
	temp_output = uz_PWM_duty_freq_detection_get_outputs(Data->objects.tempMeasurement3);
	Data->av.temperature_inv_3 = temp_output.TempDegreesCelsius;
	// end PWM freq temp measurement
}

void uz_TempCard_Measurement(DS_Data* Data){
	// start uz tempcard
	uz_TempCard_IF_MeasureTemps_cyclic(Data->objects.uz_Tempcard);
	uz_temperaturecard_OneGroup channel_A_data = uz_TempCard_IF_get_channel(Data->objects.uz_Tempcard, 'a');
	Global_Data.av.winding_temperature.a1 = channel_A_data.temperature[3]*(channel_A_data.Channels_Valid[3]==1);
	Data->av.winding_temperature.b1 = channel_A_data.temperature[5]*(channel_A_data.Channels_Valid[5]==1);
	Data->av.winding_temperature.c1 = channel_A_data.temperature[7]*(channel_A_data.Channels_Valid[7]==1);
	Data->av.winding_temperature.a2 = channel_A_data.temperature[9]*(channel_A_data.Channels_Valid[9]==1);
	Data->av.winding_temperature.b2 = channel_A_data.temperature[11]*(channel_A_data.Channels_Valid[11]==1);
	Data->av.winding_temperature.c2 = channel_A_data.temperature[13]*(channel_A_data.Channels_Valid[13]==1);
	Data->av.winding_temperature.a3 = channel_A_data.temperature[15]*(channel_A_data.Channels_Valid[15]==1);
	Data->av.winding_temperature.b3 = channel_A_data.temperature[17]*(channel_A_data.Channels_Valid[17]==1);
	Data->av.winding_temperature.c3 = channel_A_data.temperature[19]*(channel_A_data.Channels_Valid[19]==1);
	Data->av.avg_winding_temperature =
			(Data->av.winding_temperature.a1 + Data->av.winding_temperature.b1 + Data->av.winding_temperature.c1 +
			Data->av.winding_temperature.a2 + Data->av.winding_temperature.b2 + Data->av.winding_temperature.c2 +
			Data->av.winding_temperature.a3 + Data->av.winding_temperature.b3 + Data->av.winding_temperature.c3)/
			((channel_A_data.Channels_Valid[3]==1) + (channel_A_data.Channels_Valid[5]==1) + (channel_A_data.Channels_Valid[7]==1) +
			(channel_A_data.Channels_Valid[9]==1) + (channel_A_data.Channels_Valid[11]==1) + (channel_A_data.Channels_Valid[13]==1) +
			(channel_A_data.Channels_Valid[15]==1) + (channel_A_data.Channels_Valid[17]==1) + (channel_A_data.Channels_Valid[19]==1));
	// end uz tempcard
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
