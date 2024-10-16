/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann
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

#include "xparameters.h"
#include "netif/xadapter.h"

#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

#include "../include/isr.h"
#include "../defines.h"
#include "APU_RPU_shared.h"
#include "xil_cache.h"

#include "../Codegen/uz_codegen.h"
extern uz_codegen codegenInstance;

// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)

struct APU_to_RPU_t ControlData;
extern int js_connection_established;

// cf. main.c
extern uint32_t javascope_data_status;

// Javascope Queue parameters
QueueHandle_t js_queue;
int js_queue_full = 0;

int i_LifeCheck_Transfer_ipc;

//Initialize the Interrupt structure
XScuGic INTCipc;	//Interrupt for IPC
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!
XScuGic_Config *IntcConfig;

/**
 * Apu_IpiHandler() - Interrupt handler for IPI
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
// Standard isr interrupt from BareMetal -> frequency depends on the Software-interrupt from BareMetal
void Transfer_ipc_Intr_Handler(void *data)
{
	// create pointer to javascope_data_t named javascope_data located at MEM_SHARED_START_OCM_BANK_3_JAVASCOPE
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
	// create pointers to user data variables located in OCM Bank 1 and 2
	struct RPU_to_APU_user_data_t volatile * const rpu_to_apu_user_data = (struct RPU_to_APU_user_data_t*)MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU;
	struct APU_to_RPU_user_data_t volatile * const apu_to_rpu_user_data = (struct APU_to_RPU_user_data_t*)MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU;
	int status;
	BaseType_t xHigherPriorityTaskWoken;


	// flush cache of shared memory for javascope data
	Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE_2POW);

	// if javascope connection is established
	if(js_connection_established!=0)
	{
		// append sample to queue
		size_t queue_status = xQueueSendToBackFromISR(js_queue, javascope_data, &xHigherPriorityTaskWoken);

		if (queue_status == errQUEUE_FULL)
		{
			js_queue_full++;
			// uz_printf("OsziData_queue is full\r\n");
		}
	}
	// queue is purged when new connection is established

	// Maintain APU-local copy of status word (cf. main.c)
	javascope_data_status = javascope_data->status;

	u32_t ControlData_length = sizeof(ControlData)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	// invalidate cache of shared memory before read
	Xil_DCacheInvalidateRange( MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU, CACHE_FLUSH_SIZE_RPU_TO_APU);

	// get data from r5 from shared memory
		codegenInstance.input.v_DC_pu = rpu_to_apu_user_data->v_DC_pu;
		codegenInstance.input.theta_el_pos = rpu_to_apu_user_data->theta_el_pos;
		codegenInstance.input.theta_el_neg = rpu_to_apu_user_data->theta_el_neg;
		codegenInstance.input.Ts_times_ZB_over_Ld = rpu_to_apu_user_data->Ts_times_ZB_over_Ld;
		codegenInstance.input.Ts_times_ZB_over_Lq = rpu_to_apu_user_data->Ts_times_ZB_over_Lq;
		codegenInstance.input.Ts_times_ZB_over_Lx = rpu_to_apu_user_data->Ts_times_ZB_over_Lx;
		codegenInstance.input.Ts_times_ZB_over_Ly = rpu_to_apu_user_data->Ts_times_ZB_over_Ly;
		codegenInstance.input.Rs_over_ZB = rpu_to_apu_user_data->Rs_over_ZB;
		codegenInstance.input.Ld_over_LB = rpu_to_apu_user_data->Ld_over_LB;
		codegenInstance.input.Lq_over_LB = rpu_to_apu_user_data->Lq_over_LB;
		codegenInstance.input.Lx_over_LB = rpu_to_apu_user_data->Lx_over_LB;
		codegenInstance.input.Ly_over_LB = rpu_to_apu_user_data->Ly_over_LB;
		codegenInstance.input.psi_pm_over_psiB = rpu_to_apu_user_data->psi_pm_over_psiB;
		codegenInstance.input.omega_el_pu = rpu_to_apu_user_data->omega_el_pu;
		codegenInstance.input.i_dq_pu[0] = rpu_to_apu_user_data->i_d_pu;
		codegenInstance.input.i_dq_pu[1] = rpu_to_apu_user_data->i_q_pu;
		codegenInstance.input.i_xy_pu[0] = rpu_to_apu_user_data->i_x_pu;
		codegenInstance.input.i_xy_pu[1] = rpu_to_apu_user_data->i_y_pu;
		codegenInstance.input.i_d_ref_pu = rpu_to_apu_user_data->i_d_ref_pu;
		codegenInstance.input.i_q_ref_pu = rpu_to_apu_user_data->i_q_ref_pu;
		codegenInstance.input.i_x_ref_pu = rpu_to_apu_user_data->i_x_ref_pu;
		codegenInstance.input.i_y_ref_pu = rpu_to_apu_user_data->i_y_ref_pu;
		codegenInstance.input.lambda_dq = rpu_to_apu_user_data->lambda_dq;
		codegenInstance.input.lambda_xy = rpu_to_apu_user_data->lambda_xy;
		codegenInstance.input.tolerance = rpu_to_apu_user_data->solver_tolerance;
		codegenInstance.input.max_iter = rpu_to_apu_user_data->max_iter;
		codegenInstance.input.HC_off_on = rpu_to_apu_user_data->HC_off_on;
		codegenInstance.input.psiPM_h_pu[0] = rpu_to_apu_user_data->psiPM_h_pu[0];
		codegenInstance.input.psiPM_h_pu[1] = rpu_to_apu_user_data->psiPM_h_pu[1];
		codegenInstance.input.phiPM_h[0] = rpu_to_apu_user_data->phiPM_h[0];
		codegenInstance.input.phiPM_h[1] = rpu_to_apu_user_data->phiPM_h[1];
		codegenInstance.input.kalman_off_on = rpu_to_apu_user_data->kalman_off_on;
		codegenInstance.input.kalman_R = rpu_to_apu_user_data->kalman_R;
		codegenInstance.input.kalman_Q1 = rpu_to_apu_user_data->kalman_Q1;
		codegenInstance.input.kalman_Q2 = rpu_to_apu_user_data->kalman_Q2;

		/* do your computations that you want to accelerate here... */
		if (rpu_to_apu_user_data->a53_ctrl_off_on == true) {
		uz_codegen_step(&codegenInstance);
		}

		// write data to r5 in shared memory and flush cache
		apu_to_rpu_user_data->dutycyc[0] = codegenInstance.output.d_opt[0];
		apu_to_rpu_user_data->dutycyc[1] = codegenInstance.output.d_opt[1];
		apu_to_rpu_user_data->dutycyc[2] = codegenInstance.output.d_opt[2];
		apu_to_rpu_user_data->dutycyc[3] = codegenInstance.output.d_opt[3];
		apu_to_rpu_user_data->dutycyc[4] = codegenInstance.output.d_opt[4];
		apu_to_rpu_user_data->dutycyc[5] = codegenInstance.output.d_opt[5];
		apu_to_rpu_user_data->iterations = codegenInstance.output.iterations_qp;
		apu_to_rpu_user_data->dob_error_estimate[0] = codegenInstance.output.dob_error_estimate[0];
		apu_to_rpu_user_data->dob_error_estimate[1] = codegenInstance.output.dob_error_estimate[1];
		apu_to_rpu_user_data->dob_error_estimate[2] = codegenInstance.output.dob_error_estimate[2];
		apu_to_rpu_user_data->dob_error_estimate[3] = codegenInstance.output.dob_error_estimate[3];

	Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);

	/* ...until here */
#endif

	// Write message for acknowledge of the interrupt to RPU
	status = XIpiPsu_WriteMessage(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, (u32_t*)(&ControlData), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

	// Valid IPI. Clear the appropriate bit in the respective ISR
	XIpiPsu_ClearInterruptStatus(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	i_LifeCheck_Transfer_ipc++;

	if(i_LifeCheck_Transfer_ipc > 25000){
		i_LifeCheck_Transfer_ipc =0;
	}

	// force context switch after ISR finishes -> switching to ethernet task
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE THE INTERRUPT HAndler (from main)
//----------------------------------------------------
int Initialize_InterruptHandler(){

	int Status = XST_SUCCESS;

	// Interrupt controller configuration
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
		if(IntcConfig == NULL) {
			uz_printf("APU: Error: GIC Config failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	Status = XScuGic_CfgInitialize(&INTCipc, IntcConfig, IntcConfig->CpuBaseAddress);
		if(Status != XST_SUCCESS) {
			uz_printf("APU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	return Status;
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize RPU GIC and Connect IPI interrupt
	Status = Apu_GicInit(&INTCipc, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)Transfer_ipc_Intr_Handler, &INTCInst_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: GIC initialization failed\r\n");
		return XST_FAILURE;
	}

	// create queue for buffering R5 interrupt -> ethernet thread
	js_queue = xQueueCreate( JS_QUEUE_SIZE_ELEMENTS, sizeof(struct javascope_data_t) );
	if (js_queue == NULL){
		uz_printf("APU: Error: Queue creation failed\r\n");
		return XST_FAILURE;
	}

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Apu_IpiInit(&INTCInst_IPI, INTERRUPT_ID_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: IPI initialization failed\r\n");
		return XST_FAILURE;
	}


	return Status;
}

//==============================================================================================================================================================
/**
 * Apu_GicInit() - This function initializes APU GIC and connects
 * 					interrupts with the associated handlers
 * @IntcInstPtr		Pointer to the GIC instance
 * @IntId			Interrupt ID to be connected and enabled
 * @Handler			Associated handler for the Interrupt ID
 * @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
 */
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler, void *PeriphInstPtr)
{
	u32 Status = XST_SUCCESS;

	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,IntcInstPtr);
	Xil_ExceptionEnable();										//Enable interrupts in the ARM

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	Status = XScuGic_Connect(IntcInstPtr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(IntcInstPtr, IntId);

	//uz_printf("APU: Apu_GicInit: Done\r\n");
	return Status;
}


//==============================================================================================================================================================
/**
 * Apu_IpiInit() - This function initializes APU IPI and enables IPI interrupts
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId)
{
	XIpiPsu_Config *IntcConfig_IPI;
	int status;

	// Interrupt controller configuration
	IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
		if (IntcConfig_IPI == NULL) {
			uz_printf("APU: Error: Ipi Init failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(IntcInst_IPI_Ptr, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
		if (status != XST_SUCCESS) {
			uz_printf("APU: Error: IPI Config failed\r\n");
			return XST_FAILURE;
		}

	XIpiPsu_InterruptEnable(IntcInst_IPI_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	uz_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}
