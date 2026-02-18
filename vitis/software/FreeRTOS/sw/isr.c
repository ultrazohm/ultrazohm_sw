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

// define the size of the cache to flush
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)

struct APU_to_RPU_t ControlData;
extern volatile int js_connection_established;

// cf. main.c
extern uint32_t javascope_data_status;

// Javascope Queue parameters
QueueHandle_t js_queue;
int js_queue_full = 0;

int i_LifeCheck_Transfer_ipc = 0;

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

static void uz_a53_gic_reset_active_ipi_interrupts(XScuGic *Gic);

/**
 * Interrupt handler for IPI
 * synchronous interrupt with ISR on R5 -> frequency depends on R5 and indirectly on chosen PWM-based ISR-trigger
 */
void Transfer_ipc_Intr_Handler(void *data)
{
	// create pointer to javascope_data_t named javascope_data located at MEM_SHARED_START_OCM_BANK_3_JAVASCOPE
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
	// create pointers to user data variables located in OCM Bank 1 and 2
	struct RPU_to_APU_user_data_t volatile * const rpu_to_apu_user_data = (struct RPU_to_APU_user_data_t*)MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU;
	struct APU_to_RPU_user_data_t volatile * const apu_to_rpu_user_data = (struct APU_to_RPU_user_data_t*)MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU;
	int status;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


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
		// info: queue is purged when new connection is established in 'ethernet.c'
	}

	// Maintain APU-local copy of status word (cf. main.c)
	javascope_data_status = javascope_data->status;

	u32_t ControlData_length = sizeof(ControlData)/sizeof(float); // XIpiPsu_WriteMessage expects number of 32bit values as message length

#if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
	// invalidate cache of shared memory before read
	Xil_DCacheInvalidateRange( MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU, CACHE_FLUSH_SIZE_RPU_TO_APU);

	// get data from r5 from shared memory
	// some_variable  = rpu_to_apu_user_data->...

	/* do your computations that you want to accelerate here... */

	// write data to r5 in shared memory and flush cache
	apu_to_rpu_user_data->slowDataCounter  = rpu_to_apu_user_data->slowDataCounter; //just an example

	Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);

	/* ...until here */
#endif

	// Write message for acknowledge of the interrupt to RPU
	status = XIpiPsu_WriteMessage(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, (u32_t*)(&ControlData), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

	// Valid IPI. Clear the appropriate bit in the respective ISR
	XIpiPsu_ClearInterruptStatus(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

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

	XScuGic_Config *GIC_Config;

	// Interrupt controller configuration
	GIC_Config = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);

	if(GIC_Config == NULL) {
		uz_printf("APU: Error: GIC Config failed\r\n");
		return XST_FAILURE;
	}


	// Interrupt controller initialization
	Status = XScuGic_CfgInitialize(&GIC_instance, GIC_Config, GIC_Config->CpuBaseAddress);
		if(Status != XST_SUCCESS) {
			uz_printf("APU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	// Clear latched active interrupt register - for UZ warm start
	uz_a53_gic_reset_active_ipi_interrupts(&GIC_instance);

	return Status;
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Apu_IpiInit(&IPI_instance, INTERRUPT_ID_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: IPI initialization failed\r\n");
		return XST_FAILURE;
	}

	// create queue for buffering R5 interrupt -> ethernet thread
	js_queue = xQueueCreate( JS_QUEUE_SIZE_ELEMENTS, sizeof(struct javascope_data_t) );
	if (js_queue == NULL){
		uz_printf("APU: Error: Queue creation failed\r\n");
		return XST_FAILURE;
	}

	// Initialize RPU GIC and Connect IPI interrupt
	Status = Apu_GicInit(&GIC_instance, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)Transfer_ipc_Intr_Handler, &IPI_instance);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: GIC initialization failed\r\n");
		return XST_FAILURE;
	}

	// Enable interrupt on CPU level
	Xil_ExceptionEnable();

	return Status;
}

//==============================================================================================================================================================
/**
 * Apu_GicInit() - This function initializes APU GIC and connects
 * 					interrupts with the associated handlers
 * @GIC_instance_ptr		Pointer to the GIC instance
 * @IntId			Interrupt ID to be connected and enabled
 * @Handler			Associated handler for the Interrupt ID
 * @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
 */
u32 Apu_GicInit(XScuGic *GIC_instance_ptr, u32 IntId, Xil_ExceptionHandler Handler, void *PeriphInstPtr)
{
	u32 Status = XST_SUCCESS;

	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,GIC_instance_ptr);

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	Status = XScuGic_Connect(GIC_instance_ptr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(GIC_instance_ptr, IntId);

	uz_printf("APU: Apu_GicInit: Done\r\n");
	return Status;
}


//==============================================================================================================================================================
/**
 * Apu_IpiInit() - This function initializes APU IPI and enables IPI interrupts
 *
 * @IpiInstPtr		Pointer to the IPI instance
 */
u32 Apu_IpiInit(XIpiPsu *IPI_instance_Ptr,u16 DeviceId)
{
	XIpiPsu_Config *IPI_config;
	int status;

	// Interrupt controller configuration
	IPI_config = XIpiPsu_LookupConfig(DeviceId);
		if (IPI_config == NULL) {
			uz_printf("APU: Error: Ipi Init failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(IPI_instance_Ptr, IPI_config, IPI_config->BaseAddress);
		if (status != XST_SUCCESS) {
			uz_printf("APU: Error: IPI Config failed\r\n");
			return XST_FAILURE;
		}

	XIpiPsu_InterruptEnable(IPI_instance_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	uz_printf("APU: APU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}



/* Return true if the distributor marks IntId as ACTIVE */
static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    const u32 reg_off = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bitmask = (u32)1U << (IntId % 32U);
    const u32 act     = XScuGic_DistReadReg(Gic, reg_off);
    return ((act & bitmask) != 0U);
}

/**
 * @brief Clear latched (stuck ACTIVE) IPI interrupt(s) on the A53 by issuing EOIR (End Of Interrupt Register).
 *
 * Currently un-latches only XPAR_XIPIPSU_0_INT_ID, but is structured as a list so you can
 * extend it to more interrupt IDs later.
 */
static void uz_a53_gic_reset_active_ipi_interrupts(XScuGic *Gic)
{
    /* List is intentionally an array to make it easy to extend later */
    static const u32 uz_ipi_int_ids[] = {
        (u32)XPAR_XIPIPSU_0_INT_ID
        /* add more IDs here if needed */
    };

    uz_assert_not_NULL(Gic);
    uz_assert_not_NULL(Gic->Config);

	for (u32 i = 0U; i < (u32)(sizeof(uz_ipi_int_ids) / sizeof(uz_ipi_int_ids[0])); ++i)
	{
		const u32 id = uz_ipi_int_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("APU GIC: Cleared ACTIVE for IPI interrupt ID %u\r\n", (unsigned long)id);

		}
	}


}

