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

#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "xil_printf.h"

//Includes for Ethernet
#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

//Includes for CAN
#define CAN_ACTIVE 0 // (1 = CAN is active)  and (0 = CAN is inactive)
#include "include/can.h"

//Includes from own files
#include "main.h"
#include "defines.h"
#include "include/isr.h"
#include "uz/uz_PHY_reset/uz_phy_reset.h"

#include "xbram.h"
#include "xil_mmu.h"
#include "xil_cache.h"
#include "xtime_l.h"
#include "sleep.h"
#include "uz/uz_HAL.h"
#include "xgpio.h"
#include "xgpiops.h"
#include "xil_mem.h"

size_t lifecheck_mainThread = 0;
size_t lifeCheck_networkThread = 0;

#if LWIP_DHCP==1
extern volatile int dhcp_timoutcntr;
err_t dhcp_start(struct netif *netif);
#endif

static struct netif server_netif;

A53_Data Global_Data_A53;

/*
#define PL_TO_BRAM_WORDCOUNT 14;// number of data words stored in BRAM from PL
float log_array_local[350];		// local array in PS for BRAM data (memcpy-destination)

XGpio PLtoggle;
XTime xStart, xEnd;						// XTime = u64
float xDifference_us, xDifference_s; 	// define BRAM read-out latency benchmark variables

int PS_TO_BRAM_WORDCOUNT;
int BRAM_OFFSET;
float DiffArray[50];
int cnt_to_50 = 0;

extern XGpioPs myPlGpio;
*/


//==============================================================================================================================================================
void print_ip(char *msg, ip_addr_t *ip)
{
	xil_printf(msg);
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

//==============================================================================================================================================================
void print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw){

	print_ip("Board IP: ", ip);
	print_ip("Netmask : ", mask);
	print_ip("Gateway : ", gw);
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  main
 *---------------------------------------------------------------------------*
 * Description:
 *      Starts only the main thread "main_thread()" with priority
 *      "DEFAULT_THREAD_PRIO". Afterwards nothing will happen here.
 *---------------------------------------------------------------------------*/
int main()
{
	//SW: Initialize the Interrupts in the main, because by doing it in the network-threat, there were always problems that the thread was killed.
	Initialize_InterruptHandler();

	// Initialize GPIO for PL signal during measurement
	//XGpio_Initialize(&PLtoggle, XPAR_UZ_SYSTEM_UZ_ENABLE_AXI_GPIO_2_DEVICE_ID);
	//XGpio_SetDataDirection(&PLtoggle, 1, 0x00000000); // bits set to 0 are output

	//XGpioPs_Config *PL_IOreference_Config;
	//PL_IOreference_Config = XGpioPs_LookupConfig(XPAR_PSU_GPIO_0_DEVICE_ID);
	//XGpioPs_CfgInitialize(&myPlGpio, PL_IOreference_Config, PL_IOreference_Config->BaseAddr);
/*	XGpio_Config *PL_IOreference_Config;
	PL_IOreference_Config =  XGpio_LookupConfig(XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID);
	XGpio_CfgInitialize(&PLtoggle, PL_IOreference_Config, PL_IOreference_Config->BaseAddress);
	XGpio_SetDataDirection(&PLtoggle, 1, 0x00000000); // bits set to 0 are output
*/

	// Cache Functionality
	//Xil_DCacheEnable();
	//Xil_ConfigureL1Prefetch(4);
	//Xil_SetTlbAttributes(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, NORM_WB_CACHE);

	// Write specific values to BRAM baseadress with offset
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 60, 8);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 64, 9);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 56, 10);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 72, 11);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 76, 12);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 80, 13);
	//XBram_WriteReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 84, 14);

	// Store random values in BRAM directly after the last PL-written word
/*
	PS_TO_BRAM_WORDCOUNT = sizeof(log_array_local)/sizeof(log_array_local[0]) - PL_TO_BRAM_WORDCOUNT; // number of data words stored in BRAM from PS
	BRAM_OFFSET = sizeof(log_array_local[0]) * PL_TO_BRAM_WORDCOUNT;
	int WriteBuffer[PS_TO_BRAM_WORDCOUNT];
	for(int i=0; i<PS_TO_BRAM_WORDCOUNT; i++){
		WriteBuffer[i] = rand();
	}
	memcpy((void*)XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + BRAM_OFFSET, WriteBuffer, sizeof(WriteBuffer));
*/

/*	for(int i=0; i<128; i++){
		log_array_local[i] = rand();
	}
*/
	// Define a callback function used for the instantiated timer

	// Generate new software timer instance


	//Start the main-threat
	sys_thread_new("main_thrd", (void(*)(void*))main_thread, 0,
	                THREAD_STACKSIZE,
	                DEFAULT_THREAD_PRIO);
	vTaskStartScheduler();

	xil_printf("APU: Error in scheduler");

	return 0;
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  network_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Initializes the InterruptServiceRoutine (ISR) in order to enable a
 *      Data transfer between the both processors in a deterministic time
 *      period. Afterwards the network thread enables the basic send and receive
 *      functions for the Ethernet/TCP communication with the receive thread
 *      "xemacif_input_thread()". This thread runs always!
 *---------------------------------------------------------------------------*/
void network_thread(void *p)
{
	// Initialize the Interrupts
	Initialize_ISR();

    struct netif *netif;
    /* the mac address of the board. this should be unique per board */
    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
#if LWIP_IPV6==0
    ip_addr_t ipaddr, netmask, gw;
#if LWIP_DHCP==1
    int mscnt = 0;
#endif
#endif

    netif = &server_netif;

    xil_printf("\r\n\r\n");
    xil_printf("APU: Network thread started\r\n");

#if LWIP_IPV6==0
#if LWIP_DHCP==0
    /* initialize IP addresses to be used */
    IP4_ADDR(&ipaddr,  192, 168, 1, 233);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      192, 168, 1, 1);
#endif

    /* print out IP settings of the board */

#if LWIP_DHCP==0
    print_ip_settings(&ipaddr, &netmask, &gw);
    /* print all application headers */
#endif

#if LWIP_DHCP==1
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#endif
#endif

    /* Add network interface to the netif_list, and set it as default */
    if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
	xil_printf("APU: Error adding N/W interface\r\n");
	return;
    }

    netif_set_default(netif);

    /* specify that the network if is up */
    netif_set_up(netif);

    /* start packet receive thread - required for lwIP operation */
    sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, netif,
            THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);

#if CAN_ACTIVE==1
	xil_printf(" Init CAN \n\r"); //CAN interface
	//hal_can_init(XPAR_PSU_CAN_0_BASEADDR, XPAR_PSU_CAN_0_DEVICE_ID); //CAN 0 interface
	hal_can_init(XPAR_PSU_CAN_1_BASEADDR, XPAR_PSU_CAN_1_DEVICE_ID); //CAN 1 interface

	can_frame_t can_frame_rx; //CAN interface
#endif

#if LWIP_DHCP==1
    dhcp_start(netif);
    while (1) {
    	lifeCheck_networkThread++;

    	//log_array_local[0] = XBram_ReadReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 0);
    	//log_array_local[1] = XBram_ReadReg(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, 4);
    	//Xil_DCacheFlushRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));

    	// Measurement of BRAM readout process
    	//Xil_DCacheInvalidateRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));
    	//Xil_DCacheFlush();
    	//Xil_DCacheInvalidate();

 /*   	PS_TO_BRAM_WORDCOUNT = sizeof(log_array_local)/sizeof(log_array_local[0]);
    	for(int i=0; i<PS_TO_BRAM_WORDCOUNT; i++){
    		log_array_local[i] = rand();
    	}
//for writing */

    	//memcpy(log_array_local, (void*)XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));
    	//XGpio_DiscreteWrite(&PLtoggle, 1, 0xffffffff);
    	//XGpioPs_WritePin(&myPlGpio, 164, 1);
/*    	XGpioPs_WritePin(&myPlGpio, 163, 1);
    	XTime_GetTime(&xStart);
    	Xil_DCacheInvalidateRange(XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));
    	memcpy(log_array_local, (void*)XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR, sizeof(log_array_local));
    	XTime_GetTime(&xEnd);
    	asm("nop;");
    	XGpioPs_WritePin(&myPlGpio, 163, 0);
    	XGpioPs_WritePin(&myPlGpio, 164, 0);
    	//XGpio_DiscreteWrite(&PLtoggle, 1, 0x00000000);
    	xDifference_us = (float)(xEnd-xStart)/(COUNTS_PER_SECOND/1000000);
    	xDifference_s = (float)(xEnd-xStart)/COUNTS_PER_SECOND;
    	printf("Time diff: %.10f us\n", xDifference_us);
    	printf("Time diff: %.10f s\n", xDifference_s);

    	if(cnt_to_50<50){
    		DiffArray[cnt_to_50] = xDifference_us;
    	}
    	cnt_to_50++;
*/
    	//int TmpArray[PS_TO_BRAM_WORDCOUNT];
    	//for(int i=0; i<PS_TO_BRAM_WORDCOUNT; i++){
    	//	TmpArray[i] = rand();
    	//}
    	//memcpy((void*)XPAR_UZ_USER_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + BRAM_OFFSET, TmpArray, sizeof(TmpArray));


      	if(lifeCheck_networkThread > 2500){
      		lifeCheck_networkThread =0;
      	}

		#if CAN_ACTIVE==1
			if( ! hal_can_is_rx_empty() ){
				hal_can_receive_frame_blocking(&can_frame_rx);
				if(can_frame_rx.std_id == 0x22) {
				//	XcpCommand( (uint32_t *) can_frame_rx.data );
					can_send_2();
				} else {

					//hal_can_debug_print_frame(&can_frame_rx);
					//xil_printf("received a not XCP related CAN frame \n\r");
				}
				//usleep(1000 * 500);
			}else{
				can_send_1();
				//usleep(1000 * 500);
			}

			// no tx message pending
			if( hal_can_is_tx_done()) {
				//XcpSendCallBack();
			}
		#endif

		vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);
		dhcp_fine_tmr();
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >= DHCP_COARSE_TIMER_SECS*1000) {
			dhcp_coarse_tmr();
			mscnt = 0;
		}
	}
#else
    xil_printf("\r\n");
    xil_printf("%20s %6s %s\r\n", "Server", "Port", "Connect With..");
    xil_printf("%20s %6s %s\r\n", "--------------------", "------", "--------------------");

    print_echo_app_header();
    xil_printf("\r\n");
    sys_thread_new("echod", application_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);
    vTaskDelete(NULL);
#endif

    return;
}


//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  main_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Starts the network thread "network_thread()" with priority
 *      "DEFAULT_THREAD_PRIO". Afterwards the main thread starts and builds up
 *      the Ethernet communication. If it is not possible after a couple of
 *      seconds, a time-out will occur. If a communication is possible, the
 *      application thread "application_thread()" will be started.
 *      This thread runs only until the LifeCheck counter receives the value of 20
 *      with a step size of 0.25 second = 5 seconds (500us * 10000).
 *      This is also the time for the time-out (if no connection is available).
 *---------------------------------------------------------------------------*/
int main_thread()
{
#if LWIP_DHCP==1
	int mscnt = 0;
#endif

	// reset phy
	uz_phy_reset();

	/* initialize lwIP before calling sys_thread_new */
    lwip_init();

    /* any thread using lwIP should be created using sys_thread_new */
    //Open thread for Ethernet communication
    sys_thread_new("NW_THRD", network_thread, NULL,
		THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);


#if LWIP_DHCP==1
    while (1) {

	lifecheck_mainThread++;
	if(lifecheck_mainThread > 2500){
		lifecheck_mainThread =0;
	}

	vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);
		if (server_netif.ip_addr.addr) {
			xil_printf("APU: DHCP request success\r\n");
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
			print_echo_app_header();
			xil_printf("\r\n");
			sys_thread_new("echod", application_thread, 0,
					THREAD_STACKSIZE,
					DEFAULT_THREAD_PRIO);
			break;
		}
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >=1000) { // define timeout time here
			xil_printf("APU: DHCP request timed out\r\n");
			xil_printf("APU: Configuring default IP of 192.168.1.233\r\n");
			IP4_ADDR(&(server_netif.ip_addr),  192, 168, 1, 233);
			IP4_ADDR(&(server_netif.netmask), 255, 255, 255,  0);
			IP4_ADDR(&(server_netif.gw),  192, 168, 1, 1);
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
			/* print all application headers */
			xil_printf("\r\n");
			xil_printf("%20s %6s %s\r\n", "Server", "Port", "Connect With..");
			xil_printf("%20s %6s %s\r\n", "--------------------", "------", "--------------------");

			print_echo_app_header();
			xil_printf("\r\n");
			sys_thread_new("echod", application_thread, 0,
					THREAD_STACKSIZE,
					DEFAULT_THREAD_PRIO);
			break;
		}
	}
#endif

    vTaskDelete(NULL);
    return 0;
}



//==============================================================================================================================================================
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


//==============================================================================================================================================================
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


//==============================================================================================================================================================
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
