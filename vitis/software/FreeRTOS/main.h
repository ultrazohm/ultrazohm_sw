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
#define NETWORK_SEND_FIELD_SIZE 15
//The IP-address, SubNet address-and StandartGateway-address are set in the main-thread in the main.c

// ========== JavaScope-Queue =========================================================================
#define JS_QUEUE_SIZE_ELEMENTS  	1000000
#define JS_QUEUE_RECEIVE_TICKS2WAIT 100  // 1 tick = 100ms, wait (almost) indefinitely


// ========== Definitions =========================================================================
#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define PUSHBUTTONS_CHANNEL 				1								/* GPIO port for PushButtons */
#define LED_CHANNEL 						1								/* GPIO port for LEDs */
#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */

// ========== Structures =========================================================================

typedef struct		// status + time + 20 elements (32bit) + 32 bit
{
	uint32_t status;
	uint32_t slowDataContent[NETWORK_SEND_FIELD_SIZE];
	float val_01[NETWORK_SEND_FIELD_SIZE];
    float val_02[NETWORK_SEND_FIELD_SIZE];
    float val_03[NETWORK_SEND_FIELD_SIZE];
    float val_04[NETWORK_SEND_FIELD_SIZE];
    float val_05[NETWORK_SEND_FIELD_SIZE];
    float val_06[NETWORK_SEND_FIELD_SIZE];
    float val_07[NETWORK_SEND_FIELD_SIZE];
    float val_08[NETWORK_SEND_FIELD_SIZE];
    float val_09[NETWORK_SEND_FIELD_SIZE];
    float val_10[NETWORK_SEND_FIELD_SIZE];
    float val_11[NETWORK_SEND_FIELD_SIZE];
    float val_12[NETWORK_SEND_FIELD_SIZE];
    float val_13[NETWORK_SEND_FIELD_SIZE];
    float val_14[NETWORK_SEND_FIELD_SIZE];
    float val_15[NETWORK_SEND_FIELD_SIZE];
    float val_16[NETWORK_SEND_FIELD_SIZE];
    float val_17[NETWORK_SEND_FIELD_SIZE];
    float val_18[NETWORK_SEND_FIELD_SIZE];
    float val_19[NETWORK_SEND_FIELD_SIZE];
    float val_20[NETWORK_SEND_FIELD_SIZE];
    float slowDataID[NETWORK_SEND_FIELD_SIZE];
} NetworkSendStruct;


typedef struct
{
	uint16_t id;
	uint16_t value;
	uint16_t digInputs;
} Oszi_to_ARM_Data_shared_struct;


typedef struct _errorWord_ { // 16 bits
	uint16_t  errorCodeXilinx:8;
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

