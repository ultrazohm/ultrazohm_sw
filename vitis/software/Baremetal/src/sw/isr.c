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
#include "../uz/uz_nn/uz_nn.h"
#include "../uz/uz_matrix/uz_matrix.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;


#define NUMBER_OF_INPUTS 13
#define NUMBER_OF_OUTPUTS 4
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 64

float x[NUMBER_OF_INPUTS] = {5,5,5,5,5,5,5,5,5,5,5,5,5};
float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer1_weights.csv"
};
float b_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer1_bias.csv"
};
float y_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer2_weights.csv"
};
float b_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer2_bias.csv"
};
float y_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float w_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer3_weights.csv"
};
float b_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {
#include "layer3_bias.csv"
};
float y_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};

float w_4[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {
#include "layer4_weights.csv"
};
float b_4[NUMBER_OF_OUTPUTS] = {
#include "layer4_bias.csv"
};
float y_4[NUMBER_OF_OUTPUTS] = {0};

struct uz_nn_layer_config config[4] = {
[0] = {
    .activation_function = ReLU,
    .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
    .number_of_inputs = NUMBER_OF_INPUTS,
    .length_of_weights = UZ_MATRIX_SIZE(w_1),
    .length_of_bias = UZ_MATRIX_SIZE(b_1),
    .length_of_output = UZ_MATRIX_SIZE(y_1),
    .weights = w_1,
    .bias = b_1,
    .output = y_1},
[1] = {.activation_function = ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .length_of_weights = UZ_MATRIX_SIZE(w_2),
        .length_of_bias = UZ_MATRIX_SIZE(b_2),
        .length_of_output = UZ_MATRIX_SIZE(y_2),
        .weights = w_2,
        .bias = b_2,
        .output = y_2},
		[2] = {.activation_function = ReLU,
		        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
		        .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
		        .length_of_weights = UZ_MATRIX_SIZE(w_3),
		        .length_of_bias = UZ_MATRIX_SIZE(b_3),
		        .length_of_output = UZ_MATRIX_SIZE(y_3),
		        .weights = w_3,
		        .bias = b_3,
		        .output = y_3},
[3] = {.activation_function = linear,
       .number_of_neurons = NUMBER_OF_OUTPUTS,
       .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
       .length_of_weights = UZ_MATRIX_SIZE(w_4),
       .length_of_bias = UZ_MATRIX_SIZE(b_4),
       .length_of_output = UZ_MATRIX_SIZE(y_4),
       .weights = w_4,
       .bias = b_4,
       .output = y_4}
};

uz_matrix_t* input;
uz_nn_t *software_nn;


// Global variable structure
extern DS_Data Global_Data;
#include "xparameters.h"
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer_hw.h"
#include "../IP_Cores/uz_mlp_three_layer/uz_mlp_three_layer.h"
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
extern uz_array_float_t output_data;
float input_raw_data[13]={1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f};
uz_array_float_t input_data={
		.data=&x[0],
		.length=UZ_ARRAY_SIZE(x)
};

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    }
   // uz_mlp_three_layer_hw_write_input(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR, input_data);
    uz_mlp_three_layer_hw_write_input_unsafe(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR, input_data);
    uz_mlp_three_layer_hw_write_enable_nn(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR,true);
    uz_mlp_three_layer_hw_write_enable_nn(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR,false);
    while(!(uz_mlp_three_layer_hw_read_valid_output(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR) )){
    	// do nothing while output is not valid
    }
    uz_mlp_three_layer_hw_read_output_unsafe(XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR,output_data);
   // uz_nn_ff(software_nn,input);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    // Set duty cycles for three-level modulator
  //  PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
  //                      Global_Data.rasv.halfBridge2DutyCycle,
   //                     Global_Data.rasv.halfBridge3DutyCycle);
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
	struct uz_mlp_three_layer_ip_config_t mlp_ip_config = {
	    .base_address =XPAR_UZ_MLP_THREE_LAYER_0_BASEADDR };
    int Status = 0;
    uz_mlp_three_layer_ip_t *mlp_ip = uz_mlp_three_layer_ip_init(mlp_ip_config );


    input=uz_matrix_init(x,UZ_MATRIX_SIZE(x),1,UZ_MATRIX_SIZE(x));
    software_nn = uz_nn_init(config, 4);

    uz_matrix_t* bias_1=uz_nn_get_bias_matrix(software_nn, 1);
    uz_matrix_t* weigth_1=uz_nn_get_weight_matrix(software_nn, 1);

    uz_matrix_t* bias_2=uz_nn_get_bias_matrix(software_nn, 2);
    uz_matrix_t* weigth_2=uz_nn_get_weight_matrix(software_nn, 2);

    uz_matrix_t* bias_3=uz_nn_get_bias_matrix(software_nn, 3);
    uz_matrix_t* weigth_3=uz_nn_get_weight_matrix(software_nn, 3);

    uz_matrix_t* bias_4=uz_nn_get_bias_matrix(software_nn, 4);
    uz_matrix_t* weigth_4=uz_nn_get_weight_matrix(software_nn, 4);

    uz_mlp_three_layer_write_bias(mlp_ip, 4U, bias_1, 1);
    uz_mlp_three_layer_write_bias(mlp_ip, 8U, bias_2, 2);
    uz_mlp_three_layer_write_bias(mlp_ip, 8U, bias_3, 3);
    uz_mlp_three_layer_write_bias(mlp_ip, 2U, bias_4, 4);

    uz_mlp_three_layer_write_weights(mlp_ip,4U,weigth_1,1U);
    uz_mlp_three_layer_write_weights(mlp_ip,8U,weigth_2,2U);
    uz_mlp_three_layer_write_weights(mlp_ip,8U,weigth_3,3U);
    uz_mlp_three_layer_write_weights(mlp_ip,2U,weigth_4,4U);

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
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
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
