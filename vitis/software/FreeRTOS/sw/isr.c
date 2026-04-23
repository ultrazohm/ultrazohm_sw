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

// Cache ranges for optional A53/R5 accelerator user-data exchange.
#define CACHE_FLUSH_SIZE_RPU_TO_APU sizeof(*rpu_to_apu_user_data)
#define CACHE_FLUSH_SIZE_APU_TO_RPU sizeof(*apu_to_rpu_user_data)
#define UZ_GIC_INTERRUPT_PRIORITY_FREERTOS_SAFE (0xA0U)
#define UZ_GIC_TRIGGER_LEVEL_SENSITIVE (0x1U)

struct APU_to_RPU_t ControlData = {0};
extern volatile int js_connection_established;

// cf. main.c
extern uint32_t javascope_data_status;

// JavaScope queue handles and overflow state.
QueueHandle_t js_queue;
QueueHandle_t js_control_queue;
volatile int js_queue_overflow_dropped_samples = 0;
volatile int js_queue_purge_requested = 0;

int i_lifecheck_apu_ipi_isr = 0;

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

static void uz_a53_gic_reset_active_ipi_interrupts(XScuGic *Gic);

/**
 * Interrupt handler for the R5 -> A53 IPI.
 * Runs once per R5 JavaScope update and therefore at the R5 ISR-derived sample rate.
 */
void APU_IPI_ISR(void *data)
{
	// create pointer to javascope_data_t named javascope_data located at MEM_SHARED_START_OCM_BANK_3_JAVASCOPE
	struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
	// create pointers to user data variables located in OCM Bank 1 and 2
	struct RPU_to_APU_user_data_t volatile * const rpu_to_apu_user_data = (struct RPU_to_APU_user_data_t*)MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU;
	struct APU_to_RPU_user_data_t volatile * const apu_to_rpu_user_data = (struct APU_to_RPU_user_data_t*)MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU;
	int status;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	// R5 writes this shared region; invalidate A53 cache lines before reading it.
	Xil_DCacheInvalidateRange( MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE);

	// Queue samples only while a JavaScope TCP client is active.
	if(js_connection_established!=0)
	{
		size_t queue_status = xQueueSendToBackFromISR(js_queue, javascope_data, &xHigherPriorityTaskWoken);

		if (queue_status == errQUEUE_FULL)
		{
			js_queue_overflow_dropped_samples++;
			js_queue_purge_requested = 1;
			// The TCP worker observes this flag and purges the queued backlog.
		}
		else
		{
			// Yield to ethernet task only when the queue just crossed the send
			// threshold. Avoids a context switch on every ISR invocation while
			// still waking the sender without busy-poll delay.
			if (uxQueueMessagesWaitingFromISR(js_queue) == JS_SAMPLES_PER_PACKET) {
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}
	}

	// Maintain APU-local copy of status word (cf. main.c)
	javascope_data_status = javascope_data->status;

	// Consume at most one pending control command per ISR to preserve ordering.
	// If no command is pending, send an explicit no-op (id=0) to avoid re-sending old commands.
	BaseType_t control_command_available = xQueueReceiveFromISR(js_control_queue, &ControlData, &xHigherPriorityTaskWoken);
	if (control_command_available != pdTRUE) {
		ControlData.id = 0U;
		ControlData.value = 0.0f;
	}

	u32_t ControlData_length = sizeof(ControlData)/sizeof(uint32_t); // XIpiPsu_WriteMessage expects number of 32-bit words as message length

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

	// Return the next control command, or an explicit no-op, to the R5.
	status = XIpiPsu_WriteMessage(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK, (u32_t*)(&ControlData), ControlData_length, XIPIPSU_BUF_TYPE_RESP);

	// Valid IPI. Clear the appropriate bit in the respective ISR
	XIpiPsu_ClearInterruptStatus(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	i_lifecheck_apu_ipi_isr++;

	if(i_lifecheck_apu_ipi_isr > 25000){
		i_lifecheck_apu_ipi_isr =0;
	}

	// Not required in the current design: the Ethernet task polls queue depth and
	// uses non-blocking queue receive, so it is usually not blocked waiting to be
	// woken by this ISR.
	// portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE THE INTERRUPT HANDLER (from main)
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
// INITIALIZE & SET THE INTERRUPTS and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize the APU-side IPI instance used for R5 communication.
	Status = Apu_IpiInit(&IPI_instance, INTERRUPT_ID_IPI);
	if(Status != XST_SUCCESS) {
		uz_printf("APU: Error: IPI initialization failed\r\n");
		return XST_FAILURE;
	}

	// Queue R5 JavaScope samples for the Ethernet worker.
	js_queue = xQueueCreate( JS_QUEUE_SIZE_ELEMENTS, sizeof(struct javascope_data_t) );
	if (js_queue == NULL){
		uz_printf("APU: Error: Queue creation failed\r\n");
		return XST_FAILURE;
	}

	// Queue JavaScope control commands for the ISR/R5 response path.
	js_control_queue = xQueueCreate(JS_CONTROL_QUEUE_SIZE_ELEMENTS, sizeof(struct APU_to_RPU_t));
	if (js_control_queue == NULL){
		uz_printf("APU: Error: Control queue creation failed\r\n");
		return XST_FAILURE;
	}

	// Connect and enable the APU GIC interrupt for incoming R5 IPIs.
	Status = Apu_GicInit(&GIC_instance, XPAR_XIPIPSU_0_INT_ID,(Xil_ExceptionHandler)APU_IPI_ISR, &IPI_instance);
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
	XScuGic_SetPriorityTriggerType(GIC_instance_ptr, IntId, UZ_GIC_INTERRUPT_PRIORITY_FREERTOS_SAFE, UZ_GIC_TRIGGER_LEVEL_SENSITIVE);
	Status = XScuGic_Connect(GIC_instance_ptr, IntId, Handler, PeriphInstPtr);

	XScuGic_Enable(GIC_instance_ptr, IntId);

	uz_printf("APU: GIC initialized\r\n");
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
			uz_printf("APU: IPI initialization failed: no configuration found\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(IPI_instance_Ptr, IPI_config, IPI_config->BaseAddress);
		if (status != XST_SUCCESS) {
			uz_printf("APU: IPI configuration failed\r\n");
			return XST_FAILURE;
		}

	XIpiPsu_InterruptEnable(IPI_instance_Ptr, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

	uz_printf("APU: IPI initialized\r\n");
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

		// Check whether this interrupt ID is stuck in ACTIVE state.
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("APU GIC: Cleared ACTIVE for IPI interrupt ID %u\r\n", (unsigned long)id);

		}
	}


}

