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

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

// ========== Include Files =========================================================================
#include "lwip/sockets.h"

#include "xparameters.h"								//SW: Include for the implemented IP-Blocks from the PL
#include "xstatus.h"
#include "xil_printf.h"
#include "xscugic.h"									//Include for Interrupt handler (necessary for all interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xbasic_types.h" 								//Include for Datatypes
#include "xtmrctr.h"									//Include of the Timer-Blocks
#include "math.h"										//Include for math operations
#include <stdio.h>

// ========== Threads =========================================================================
#define THREAD_STACKSIZE 1024

// ========== JavaScope-Ethernet =========================================================================
#define TCPPACKETSIZE 1460 //Maximum TCPPaketSize -> Default: 1460 -> Jumbo-Frames would enable a TCPPACKETSIZE of 8960
#define TCPPORT 1000	   //Random chosen, but equivalent to the Concerto-OHMrichter
#define NUMTCPWORKERS 3
#define NETWORK_SEND_FIELD_SIZE 15 //EL //before: 30
//The IP-address, SubNet address-and StandartGateway-address are set in the main-thread in the main.c

// ========== Definitions =========================================================================
#define PI 3.141592653589

#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define PUSHBUTTONS_CHANNEL 				1								/* GPIO port for PushButtons */
#define LED_CHANNEL 						1								/* GPIO port for LEDs */
#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */

// ========== Structures =========================================================================

typedef struct		// status + time + 20 elemente (32bit) + 16 bit
{
	u32_t status;
	u32_t slowDataContent[NETWORK_SEND_FIELD_SIZE];
	Xfloat32 val_01[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_02[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_03[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_04[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_05[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_06[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_07[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_08[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_09[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_10[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_11[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_12[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_13[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_14[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_15[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_16[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_17[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_18[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_19[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 val_20[NETWORK_SEND_FIELD_SIZE];
    Xfloat32 slowDataID[NETWORK_SEND_FIELD_SIZE];
} NetworkSendStruct;


typedef struct
{
	u32_t status_BareToRTOS;
	_Bool SampledDataWriteDone;
	_Bool SampledDataReadDone;
	_Bool SampledDataError;
	u32_t slowDataContent;
	u16_t slowDataID;
	Xfloat32 val[20]; // EL: changed from uint16 to float
} ARM_to_Oszi_Data_shared_struct;

typedef struct
{
	u16_t id;
	u16_t value;
	u16_t digInputs;
} Oszi_to_ARM_Data_shared_struct;


typedef struct _errorWord_ { // 16 bits
	u16_t  errorCodeXilinx:8;
	_Bool wrongInterruptByIPI:1; //Wrong interrupt arrived
	_Bool missingInterruptByIPI:1; //No Interrupt arrived
	_Bool InitFailedInterruptByIPI:1; //Error during initialization
	_Bool communicationTimeoutOccured:1;
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
	_Bool rsvd4:1;
} errorWord;

typedef struct _errorReset_ { // 5 bits
	_Bool communicationTimeoutOccured:1;
	_Bool rsvd1:1;
	_Bool rsvd2:1;
	_Bool rsvd3:1;
	_Bool rsvd4:1;
	//boolean rsvd5:1;
} errorReset;

typedef struct _A53_Data_ {
	errorWord ew;
	errorReset er;
} A53_Data;

// ========== Functions and Threads ======================================================================
void Transfer_ipc(void);
int main_thread();
void print_echo_app_header();
void application_thread();
void lwip_init();

#if CAN_ACTIVE==1
	void can_send_1(void); 		//CAN interface: Test function for CAN
	void can_send_2(void); 		//CAN interface: Test function for CAN
	void hal_can_debug_print_frame(can_frame_t *can_frame_p); //CAN interface: Test function for CAN
#endif

#ifdef __cplusplus
}
#endif

