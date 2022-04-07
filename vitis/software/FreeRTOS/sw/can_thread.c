/******************************************************************************
* Copyright 2021 Robert Zipprich
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

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "APU_RPU_shared.h"

#include "../include/can.h"
#include "../include/can_thread.h"


// include for the Java-SlowData
#include "../../Baremetal/src/include/javascope.h"

struct APU_to_RPU_t ControlData_CAN;
float js_slowDataArray[JSSD_ENDMARKER];

//=============================================================================
// local variables
//=============================================================================

//=============================================================================
/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_Init_CAN1
 *---------------------------------------------------------------------------*
 * Description:
 *     Initialize the CAN-Interfaces for the CAN_Thread_CAN1
 *---------------------------------------------------------------------------*/

void CAN_Thread_Init_CAN0(){
	xil_printf(" Init CAN0 with 500kbaud/s \n\r");
	hal_can_init(XPAR_PSU_CAN_0_BASEADDR, XPAR_PSU_CAN_0_DEVICE_ID); //CAN 0 interface
}

void CAN_Thread_Init_CAN1(){
	xil_printf(" Init CAN1 with 500kbaud/s \n\r");
	hal_can_init(XPAR_PSU_CAN_1_BASEADDR, XPAR_PSU_CAN_1_DEVICE_ID); //CAN 1 interface
}

/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_SendSlowData(_int_int / _int_float / _int_uint / _float_int / _float_float / _float_uint / _uint_int / _uint_float / _uint_uint)
 *---------------------------------------------------------------------------*
 * Description:
 *     Function to send the SlowData via CAN-Bus.
 *     This function is designed to run in a for-loop
 *---------------------------------------------------------------------------*/
int CAN_Thread_SendSlowData(int Messagenumber, int32_t dezimalscaler_Value1, int32_t dezimalscaler_Value2, float Value1, float Value2){
	// Local Variables
	can_frame_t can_framebuffer_tx;
	int	CAN_SendBuffer = 0;

	// Check for reasonable dezimalscalers
	if(dezimalscaler_Value1 <= 0 || dezimalscaler_Value2 <= 0){
		// negativ or zero-scalers are not allowed!
		return 1;
	}

	// Build Can-Message
	can_framebuffer_tx.std_id = CAN_Msg_Start + Messagenumber;
	can_framebuffer_tx.dlc = 8;

	// Convert Data and store them
	CAN_SendBuffer = (int)((float)Value1 * dezimalscaler_Value1);
	can_framebuffer_tx.data[0] = CAN_SendBuffer >> 0  ;
	can_framebuffer_tx.data[1] = CAN_SendBuffer >> 8  ;
	can_framebuffer_tx.data[2] = CAN_SendBuffer >> 16 ;
	can_framebuffer_tx.data[3] = CAN_SendBuffer >> 24 ;

	// Convert Data and store them
	CAN_SendBuffer = (int)((float)Value2 * dezimalscaler_Value2);
	can_framebuffer_tx.data[4] = CAN_SendBuffer >> 0  ;
	can_framebuffer_tx.data[5] = CAN_SendBuffer >> 8  ;
	can_framebuffer_tx.data[6] = CAN_SendBuffer >> 16 ;
	can_framebuffer_tx.data[7] = CAN_SendBuffer >> 24 ;

	//Send
	hal_can_send_frame_blocking(&can_framebuffer_tx);
	return 0;
}


/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_CAN1
 *---------------------------------------------------------------------------*
 * Description:
 *      Started by the network-Thread, this Thread will handle the Communication
 *      via the CAN-Bus. Primary this Thread will read Target Values from the
 *      CAN-Bus and writes them down to the R5 through the IPI. Furthermore this 
 *      Thread will send actual Values regardign the Control and Measurement 
 *      over the CAN-Bus, with limited data-rate.
 * 
 * How the Thread works:
 *      1. check for new Messages
 *      2. if no message received -> Do nothing (should the task be suspended for x uSeconds and will be resumed from the ISR? good idea?)
 *      3. if new message received
 *          a.  read the content
 *          b.  set the ControlData_CAN
 *      4. Read-Cycle finished
 *      5. Count-up LifeCheck
 *      6. Send Countervalue of Lifecheck as first Dummy-Message
 *---------------------------------------------------------------------------*/
void CAN_Thread_CAN1(void *p){

	//Variables
	uint32_t i_LifeCheck_CAN_Thread1   = 0;
	can_frame_t can_framebuffer_rx;

	can_frame_t can_framebuffer_tx;

	// Init the CAN-Interface
	CAN_Thread_Init_CAN0();
	//CAN_Thread_Init_CAN1();

	while(1){

		//Check Fifos--------------------------------------------------------------------------------------------------------------------------------
		if(DEBUG_ThreadAlive_CAN_Thread1 == 1){
			// Check Fifos
			if(!hal_can_is_rx_empty()){
				xil_printf("RX-Fifo contains Messages!\n\r");
			}
			if(hal_can_is_tx_empty()){
				xil_printf("TX-Fifo is full!\n\r");
			}
		}

		// check if a message is available-----------------------------------------------------------------------------------------------------------
	    if( ! hal_can_is_rx_empty() ){
	        // get the new message
	        hal_can_receive_frame_blocking(&can_framebuffer_rx);

	        // extract the information from the message and store them in the ControlData_CAN struct

	        // Testmagic to Control the User-LED with msgID=1
	        if(DEBUG_ThreadAlive_CAN_Thread1 == 1){
				xil_printf("CAN-Message received: \n\r");
				xil_printf("ID:\t\t%d \n\r",can_framebuffer_rx.std_id);
				xil_printf("DLC:\t\t%d \n\r",can_framebuffer_rx.dlc);
				xil_printf("Data_0:\t%d \n\r",can_framebuffer_rx.data[0]);
				xil_printf("Data_1:\t%d \n\r",can_framebuffer_rx.data[1]);
				xil_printf("Data_2:\t%d \n\r",can_framebuffer_rx.data[2]);
				xil_printf("Data_3:\t%d \n\r",can_framebuffer_rx.data[3]);
				xil_printf("Data_4:\t%d \n\r",can_framebuffer_rx.data[4]);
				xil_printf("Data_5:\t%d \n\r",can_framebuffer_rx.data[5]);
				xil_printf("Data_6:\t%d \n\r",can_framebuffer_rx.data[6]);
				xil_printf("Data_7:\t%d \n\r",can_framebuffer_rx.data[7]);
	        }

	        // Change the ControlData_CAN if the ControlMessage arrived (ID 0d66 / 0x42)
	        if(can_framebuffer_rx.std_id == CAN_Msg_Control){
				ControlData_CAN.id			= (((uint16_t)can_framebuffer_rx.data[1]) << 8) | (uint16_t)can_framebuffer_rx.data[0];
				ControlData_CAN.value		= (((uint16_t)can_framebuffer_rx.data[3]) << 8) | (uint16_t)can_framebuffer_rx.data[2];
	        }

			if(DEBUG_ThreadAlive_CAN_Thread1 == 1){
				xil_printf("ControlData_CAN.id:\t%d \n\r",ControlData_CAN.id);
				xil_printf("ControlData_CAN.value:\t%d \n\r",ControlData_CAN.value);
			}
	    }

		// create Lifecheck--------------------------------------------------------------------------------------------------------------------------
		i_LifeCheck_CAN_Thread1++;
		if(i_LifeCheck_CAN_Thread1 > 255){
			i_LifeCheck_CAN_Thread1 =0;
		}
		// Build Can-Message for the Livecheck
		can_framebuffer_tx.std_id = CAN_Msg_Start;
		can_framebuffer_tx.dlc = 1;
		can_framebuffer_tx.data[0] = i_LifeCheck_CAN_Thread1;
		//Send Heartbeat of the CAN-Thread1
		hal_can_send_frame_blocking(&can_framebuffer_tx);

		// Send the whole SlowData-Array-------------------------------------------------------------------------------------------------------------
		// itterate through the Slow-Data-Array. This loop detects even/odd-numbers of Values in the Array and
		for(int i = 0 ; i < ceil((JSSD_ENDMARKER-2)/2);i++){
			CAN_Thread_SendSlowData(i+1, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[1+(i*2)], js_slowDataArray[2+(i*2)]);
			if ((JSSD_ENDMARKER%2) == 0) {
				// Case for odd Number of Slow-Data-Values
				if( i==(int)(ceil((JSSD_ENDMARKER-2)/2)-1) ){
					CAN_Thread_SendSlowData(i+2, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[3+(i*2)], 1.0f);
				}
			}else{
				// Case for even Number of Slow-Data-Values
				if( i==(int)(ceil((JSSD_ENDMARKER-2)/2)-1) ){
					CAN_Thread_SendSlowData(i+2, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[3+(i*2)], js_slowDataArray[4+(i*2)]);
				}
			}
		}

		// Use this style to send specific Values over CAN-------------------------------------------------------------------------------------------
		/*
		// Build Can-Message 1
		CAN_Thread_SendSlowData(1, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart], js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us]);
		// Build Can-Message 2
		CAN_Thread_SendSlowData(2, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_ISR_Period_us], js_slowDataArray[JSSD_FLOAT_FreqReadback]);
		// Build Can-Message 3
		CAN_Thread_SendSlowData(3, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_Milliseconds], js_slowDataArray[JSSD_FLOAT_ADCconvFactorReadback]);
		// Build Can-Message 4
		CAN_Thread_SendSlowData(4, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_Rs_Offline], js_slowDataArray[JSSD_FLOAT_Ld_Offline]);
		// Build Can-Message 5
		CAN_Thread_SendSlowData(5, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_Lq_Offline], js_slowDataArray[JSSD_FLOAT_PsiPM_Offline]);
		// Build Can-Message 6
		CAN_Thread_SendSlowData(6, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, js_slowDataArray[JSSD_FLOAT_J], js_slowDataArray[JSSD_FLOAT_polePairs]);
		// Build Can-Message 7
		CAN_Thread_SendSlowData(7, CAN_Msg_DecimalPlaces, CAN_Msg_DecimalPlaces, 0.0f, 0.0f);
		 */

		// Debug-Wait--------------------------------------------------------------------------------------------------------------------------------
		if(DEBUG_ThreadAlive_CAN_Thread1 == 1){
			// Delay in ms
			vTaskDelay((DEBUG_ThreadDelay_CAN_Thread1-ThreadDelay_CAN_Thread1) / portTICK_RATE_MS);
			// Message over UART to signalize a running Thread
			//xil_printf("Hello from the CAN-Thread\n\r");
			//xil_printf("%d \n\r",i_LifeCheck_CAN_Thread1);
		}

		// Delays the Thread to decrease busload-----------------------------------------------------------------------------------------------------
		vTaskDelay(ThreadDelay_CAN_Thread1 / portTICK_RATE_MS);
	}
}


