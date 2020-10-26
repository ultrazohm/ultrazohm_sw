/******************************************************************************
*
* main.h
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

// ========== Include Files =========================================================================
#include "lwip/sockets.h"

#include "xparameters.h"								//SW: Include for the implemented IP-Blocks from the PL
#include "xgpiops.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "xscugic.h"									//Include for Interrupt handler (necessary for all interrupts)
#include "xipipsu.h"									//Include for Interrupt handler (necessary for all IPI interrupts)
#include "xbasic_types.h" 								//Include for Datatypes
//#include "xadcps.h"									//Include of ADC-Block
//#include "xsysmon.h"									//Include of ADC-Block
#include "xtmrctr.h"									//Include of the Timer-Blocks
#include "math.h"										//Include for math operations
#include <stdio.h>
#include "xiicps.h"

// ========== Threads =========================================================================
#define THREAD_STACKSIZE 1024

// ========== JavaScope-Ethernet =========================================================================
#define TCPPACKETSIZE 1460 //Maximum TCPPaketSize -> Default: 1460 -> Jumbo-Frames would enable a TCPPACKETSIZE of 8960
#define TCPPORT 1000	   //Random chosen, but equivalent to the Concerto-OHMrichter
#define NUMTCPWORKERS 3
#define NETWORK_SEND_FIELD_SIZE 30 //Default: 15
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

typedef struct		/* status + time + 21 elemente (16bit) */
{
	u32_t status;
	u32_t slowDataContent[NETWORK_SEND_FIELD_SIZE];
	u16_t val_01_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_02_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_03_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_04_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_05_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_06_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_07_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_08_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_09_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_10_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_11_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_12_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_13_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_14_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_15_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_16_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_17_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_18_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_19_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t val_20_uint16[NETWORK_SEND_FIELD_SIZE];
    u16_t slowDataID[NETWORK_SEND_FIELD_SIZE];
} NetworkSendStruct;

typedef struct
{
	u32_t status_BareToRTOS;
	_Bool SampledDataWriteDone;
	_Bool SampledDataReadDone;
	_Bool SampledDataError;
	u16_t schiebereg_ausgaenge;
	u32_t slowDataContent;
	u16_t slowDataID;
	u16_t val[20];
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


// I2C
	/************************** Constant Definitions ******************************/

	/*
	 * The following constants map to the XPAR parameters created in the
	 * xparameters.h file. They are defined here such that a user can easily
	 * change all the needed parameters in one place.
	 */
	#define IIC_DEVICE_ID		XPAR_XIICPS_1_DEVICE_ID

	/*
	 * The slave address to send to and receive from.
	 */
	#define IIC_SLAVE_ADDR		0x55
	#define IIC_SCLK_RATE		100000

	/*
	 * The following constant controls the length of the buffers to be sent
	 * and received with the IIC.
	 */
	#define TEST_BUFFER_SIZE	132

XIicPs Iic;		/**< Instance of the IIC Device */
u8 SendBuffer[TEST_BUFFER_SIZE];    /**< Buffer for Transmitting Data */
u8 RecvBuffer[TEST_BUFFER_SIZE];    /**< Buffer for Receiving Data */

int IicPsMasterPolledExample(u16 DeviceId);


#ifdef __cplusplus
}
#endif

