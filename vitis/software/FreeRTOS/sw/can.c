/******************************************************************************
* Copyright 2021 Sebastian Wendel
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

#include "xcanps.h"
#include "xparameters.h"
#include "../include/can.h"


//=============================================================================
// defines for configuration of the CAN
//=============================================================================

// Vivado Setting (if unchanged): CAN IP Clock = 100 MHz
// Prescaler = f_IP_CAN / (500 kBaud/s * 8 Quantums/Baud) = 100 MHz / 4 MHz = 25
#define CAN_BAUD_RATE_PRESCALER 25

#define CAN_SYNCJUMPWIDTH		1
#define CAN_SECOND_TIMESEGMENT	2
#define CAN_FIRST_TIMESEGMENT	5

//=============================================================================
// local variables
//=============================================================================
static XCanPs can_inst;



//=============================================================================
// functions
//=============================================================================

int hal_can_init(uint32_t can_base_address, uint32_t can_device_id)
{
	int status = XST_SUCCESS;

	XCanPs_Config can_config;
	can_config.BaseAddr = can_base_address; // e.g.: XPAR_PS7_CAN_0_BASEADDR;
	can_config.DeviceId = can_device_id; // e.g.: XPAR_PS7_CAN_0_DEVICE_ID;


	status = XCanPs_CfgInitialize(&can_inst, &can_config, can_config.BaseAddr);
	if (status != XST_SUCCESS) {
		return status;
	}


	// Run self-test on the device, which verifies basic sanity of the
	// device and the driver.
	status = XCanPs_SelfTest(&can_inst);
	if (status != XST_SUCCESS) {
		return status;
	}


	XCanPs_EnterMode(&can_inst, XCANPS_MODE_CONFIG);
	while(XCanPs_GetMode(&can_inst) != XCANPS_MODE_CONFIG);

	// register value of prescaler is (prescaler - 1) !!
	XCanPs_SetBaudRatePrescaler(&can_inst, CAN_BAUD_RATE_PRESCALER - 1);


	XCanPs_SetBitTiming(&can_inst,
			CAN_SYNCJUMPWIDTH - 1,
			CAN_SECOND_TIMESEGMENT - 1,
			CAN_FIRST_TIMESEGMENT - 1);


	// go into final mode
	XCanPs_EnterMode(&can_inst, XCANPS_MODE_NORMAL);
	while(XCanPs_GetMode(&can_inst) != XCANPS_MODE_NORMAL);


	return status;
}

int hal_can_is_rx_empty(void)
{
	return XCanPs_IsRxEmpty(&can_inst);
}

int hal_can_is_tx_empty(void)
{
	return XCanPs_IsTxFifoFull(&can_inst);
}

int hal_can_is_tx_done(void)
{
	return XCanPs_IsTxDone(&can_inst);
}


int hal_can_send_frame_blocking(can_frame_t* can_frame_tx_p)
{
	uint32_t tx_frame[4];
	int status = XST_FAILURE;

	// set identifier
	tx_frame[0] = XCanPs_CreateIdValue(can_frame_tx_p->std_id, 0, 0, 0, 0);

	// set data length
	tx_frame[1] = XCanPs_CreateDlcValue(can_frame_tx_p->dlc);

	// copy data
	uint8_t *data_frame_copy_pointer;
	data_frame_copy_pointer = (uint8_t *)(&tx_frame[2]);
	int lc;
	for (lc = 0; lc < can_frame_tx_p->dlc; lc++) {
		*(data_frame_copy_pointer++) = (uint8_t) can_frame_tx_p->data[lc];
	}


	// Wait until TX FIFO has room
	while (XCanPs_IsTxFifoFull(&can_inst) == TRUE);

	/*
	 * Now send the frame.
	 *
	 * Another way to send a frame is keep calling XCan_Send() until it
	 * returns XST_SUCCESS. No check on if TX FIFO is full is needed anymore
	 * in that case.
	 */
	status = XCanPs_Send(&can_inst, tx_frame);


	return status;
}


int hal_can_send_frame_blocking_wrapper(uint16_t std_id, uint8_t dlc, uint8_t* data)
{
	int status = XST_FAILURE;
	can_frame_t can_frame_tx;

	can_frame_tx.std_id = std_id;
	can_frame_tx.dlc = dlc;

	int lc;
	for(lc = 0; lc < dlc; lc++) {
		can_frame_tx.data[lc] = data[lc];
	}

	status = hal_can_send_frame_blocking(&can_frame_tx);

	return status;
}


int hal_can_receive_frame_blocking(can_frame_t *can_frame_rx_p)
{
	int status = XST_FAILURE;

	// poll until a frame is received
	while (XCanPs_IsRxEmpty(&can_inst) == TRUE);

	uint32_t rx_data_block[4];
	status = XCanPs_Recv(&can_inst, rx_data_block);

	can_frame_rx_p->std_id = (rx_data_block[0] & XCANPS_IDR_ID1_MASK ) >> XCANPS_IDR_ID1_SHIFT;
	can_frame_rx_p->dlc = (rx_data_block[1] & XCANPS_DLCR_DLC_MASK ) >> XCANPS_DLCR_DLC_SHIFT;
	* ((uint32_t *) &can_frame_rx_p->data[0]) = rx_data_block[2];
	* ((uint32_t *) &can_frame_rx_p->data[4]) = rx_data_block[3];

	return status;
}


//=============================================================================
/*---------------------------------------------------------------------------*
 * Routine:  hal_can_debug_print_frame
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void hal_can_debug_print_frame(can_frame_t *can_frame_p)
{
	xil_printf("std_id: 0x%03X, dlc: %d, data[0]: 0x%02X \n\r",
			can_frame_p->std_id, can_frame_p->dlc, can_frame_p->data[0]);
}


//=============================================================================
/*---------------------------------------------------------------------------*
 * Routine:  can_send_1
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void can_send_1(void)
{
	static uint8_t tick;
	tick++;
	if(tick > 250){
		tick =0;
	}

	//xil_printf("tick: 0x%02X \n\r", tick);
	//Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR, tick);

	can_frame_t can_frame_tx;
	can_frame_tx.std_id = 0x123;
	can_frame_tx.dlc = 2;
	can_frame_tx.data[0] = 0x13;
	can_frame_tx.data[1] = tick;

	hal_can_send_frame_blocking(&can_frame_tx);
}


//==============================================================================
/*---------------------------------------------------------------------------*
 * Routine:  can_send_2
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void can_send_2(void)
{
	static uint8_t tick;
	tick=tick+10;
	if(tick > 250){
		tick =0;
	}

	//xil_printf("tick: 0x%02X \n\r", tick);
	//Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR, tick);

	can_frame_t can_frame_tx;
	can_frame_tx.std_id = 0x52;
	can_frame_tx.dlc = 2;
	can_frame_tx.data[0] = 0x12;
	can_frame_tx.data[1] = tick;

	hal_can_send_frame_blocking(&can_frame_tx);
}
