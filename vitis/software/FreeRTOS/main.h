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
#include "defines.h"

#include "xparameters.h"								//SW: Include for the implemented IP-Blocks from the PL
#include "xstatus.h"
#include "xscugic.h"									//Include for Interrupt handler (necessary for all interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xbasic_types.h" 								//Include for Datatypes
#include "xtmrctr.h"									//Include of the Timer-Blocks
#include "math.h"										//Include for math operations
#include "include/uz_apu_assert_configuration.h"
#include "uz/uz_HAL.h"

// ========== Threads =========================================================================
#define THREAD_STACKSIZE 1024
#define THREAD_PRIO_I2CIO                   1U
#define THREAD_PRIO_CAN                     1U
#define THREAD_PRIO_DEFAULT                 2U
#define THREAD_PRIO_MAIN                    THREAD_PRIO_DEFAULT
#define THREAD_PRIO_NETWORK_BRINGUP         THREAD_PRIO_DEFAULT
#define THREAD_PRIO_JAVASCOPE_SOCKET_MANAGER THREAD_PRIO_DEFAULT
#define THREAD_PRIO_JAVASCOPE_STREAM         3U
#define THREAD_PRIO_XEMACIF_INPUT           3U

// Period (in ms) of the endless loop in i2cio_thread()
#define I2CIO_THREAD_TIMER_MS	(50U)

// ========== JavaScope-Ethernet =========================================================================
// Period (in ms) of the endless loop in network_bringup_thread()
#define NETWORK_LOOPPERIOD_MS	(500U)

#define TCPPACKETSIZE 1460 // Maximum TCP packet size. Default: 1460. Jumbo frames would allow up to 8960.
#define TCPPORT 1000	   // JavaScope TCP service port
#define NETWORK_SEND_FIELD_SIZE JS_SAMPLES_PER_PACKET
// IP address, netmask, and gateway are configured in main.c.

// ========== JavaScope-Queue =========================================================================
#define JS_QUEUE_SIZE_ELEMENTS  	1000000
#define JS_QUEUE_RECEIVE_TICKS2WAIT 0U  // Non-blocking: the JavaScope stream task polls queue depth before dequeuing, so a timeout is not needed
#define JS_CONTROL_QUEUE_SIZE_ELEMENTS 256U


// ========== Definitions =========================================================================
#define OUTPUT_PIN							1 								//This Pin is an Output
#define INPUT_PIN							0 								//This Pin is an Input

#define ENABLE_PIN							1 								//This Pin is enabled
#define DISABLE_PIN							0 								//This Pin is disabled

#define PUSHBUTTONS_CHANNEL 				1								/* GPIO port for PushButtons */
#define LED_CHANNEL 						1								/* GPIO port for LEDs */
#define GPIO_CHANNEL 						1								/* GPIO port for GPIOs */

// ========== Structures =========================================================================

typedef struct		// One JavaScope TCP frame: status plus batched slow-data and 20 sampled channels.
{
	uint32_t status;
	float slowDataContent[NETWORK_SEND_FIELD_SIZE];
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


// ========== Functions and Threads ======================================================================
int main_thread();
void print_javascope_app_header(ip_addr_t *ip);
void javascope_socket_manager_thread(void *p);
void lwip_init();


#ifdef __cplusplus
}
#endif

