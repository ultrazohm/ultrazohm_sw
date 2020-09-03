/******************************************************************************
*
* ethernet.c
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../main.h"

#define LONG_TIME 0xffff

extern ARM_to_Oszi_Data_shared_struct OsziData; //Data from A9_0 to A9_1 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
extern Oszi_to_ARM_Data_shared_struct ControlData; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
//extern SemaphoreHandle_t xSemaphore_IPC;
extern XGpio Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

NetworkSendStruct nwsend;

Xint16 i_LifeCheck_process_Ethernet =0, TransferSendAllowed=0;
char recv_buf[2048];
extern Xint16  NextPacketArrived;

//==============================================================================================================================================================
void print_echo_app_header()
{
    xil_printf("%20s %6d %s\r\n", "echo server",
    					TCPPORT,
                        "$ telnet <board_ip> 1000");

}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  process_request_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      thread spawned for each connection  = tcpWorker
 *      This thread sends and receives the data, regarding the information
 *      in the shared RAM. This thread runs always!
 *---------------------------------------------------------------------------*/
void process_request_thread(void *p)
{
	int clientfd = (int)p;
//	int RECV_BUF_SIZE = 2048;
//	char recv_buf[RECV_BUF_SIZE];
	int nread, nwrote;
    char *buffer;

    int foo;

    nwsend.status = 0x00;

    for(foo=0; foo<NETWORK_SEND_FIELD_SIZE; foo++){
     	nwsend.slowDataContent[foo] = 0;
     	nwsend.val_01_uint16[foo] = 0;
 		nwsend.val_02_uint16[foo] = 0;
 		nwsend.val_03_uint16[foo] = 0;
 		nwsend.val_04_uint16[foo]  = 0;
 		nwsend.val_05_uint16[foo]  = 0;
 		nwsend.val_06_uint16[foo]  = 0;
 		nwsend.val_07_uint16[foo] = 0;
 		nwsend.val_08_uint16[foo] = 0;
 		nwsend.val_09_uint16[foo] = 0;
 		nwsend.val_10_uint16[foo] = 0;
 		nwsend.val_11_uint16[foo]  = 0;
 		nwsend.val_12_uint16[foo]  = 0;
 		nwsend.val_13_uint16[foo]  = 0;
 		nwsend.val_14_uint16[foo] = 0;
 		nwsend.val_15_uint16[foo] = 0;
 		nwsend.val_16_uint16[foo] = 0;
 		nwsend.val_17_uint16[foo] = 0;
 		nwsend.val_18_uint16[foo] = 0;
 		nwsend.val_19_uint16[foo] = 0;
 		nwsend.val_20_uint16[foo] = 0;
 		nwsend.slowDataID[foo] = 0;
     }

     xil_printf("tcpWorker: start clientfd = 0x%x\n", clientfd);

	while (1) {

		u32_t command=0;
		u8_t i=0;

	  	for (i=0; i<NETWORK_SEND_FIELD_SIZE; i++){
	    		// Is there any new data available?
	    		//Semaphore_pend(semaphore_send, BIOS_WAIT_FOREVER);
//	  			xSemaphoreTake(xSemaphore_IPC,portMAX_DELAY ); //wait forever -> really big number (1000000000)
//				if (OsziData.SampledDataWriteDone == 1){	// notify FreeRTOS that new data is available
//					Transfer_ipc(); //Read out data from BareMetal into shadow register
//				}
	  	 //   xSemaphoreTake(xSemaphore_IPC, (TickType_t) 0);
	        // Block waiting for the semaphore to become available.
//	        if( xSemaphoreTake( xSemaphore_IPC, LONG_TIME ) == pdTRUE )
//	        {
	            // It is time to execute.

	            // ...
	            // We have finished our task.  Return to the top of the loop where
	            // we will block on the semaphore until it is time to execute
	            // again.  Note when using the semaphore for synchronisation with an
				// ISR in this manner there is no need to 'give' the semaphore back.
//	        }

//Tesyt for Ethernet
//NextPacketArrived =1;
	  		while(NextPacketArrived ==0){
	  			asm(" nop");
	  		}
	  		NextPacketArrived =0;

			nwsend.slowDataContent[i] 	= OsziData.slowDataContent;	// Clock_getTicks() - zeitnull;
			nwsend.val_01_uint16[i] 	= OsziData.val[0];
			nwsend.val_02_uint16[i] 	= OsziData.val[1];
			nwsend.val_03_uint16[i] 	= OsziData.val[2];
			nwsend.val_04_uint16[i]  	= OsziData.val[3];
			nwsend.val_05_uint16[i]  	= OsziData.val[4];
			nwsend.val_06_uint16[i]  	= OsziData.val[5];
			nwsend.val_07_uint16[i] 	= OsziData.val[6];
			nwsend.val_08_uint16[i] 	= OsziData.val[7];
			nwsend.val_09_uint16[i] 	= OsziData.val[8];
			nwsend.val_10_uint16[i] 	= OsziData.val[9];
			nwsend.val_11_uint16[i]  	= OsziData.val[10];
			nwsend.val_12_uint16[i]  	= OsziData.val[11];
			nwsend.val_13_uint16[i]  	= OsziData.val[12];
			nwsend.val_14_uint16[i] 	= OsziData.val[13];
			nwsend.val_15_uint16[i] 	= OsziData.val[14];
			nwsend.val_16_uint16[i] 	= OsziData.val[15];
			nwsend.val_17_uint16[i] 	= OsziData.val[16];
			nwsend.val_18_uint16[i] 	= OsziData.val[17];
			nwsend.val_19_uint16[i] 	= OsziData.val[18];
			nwsend.val_20_uint16[i] 	= OsziData.val[19];
			nwsend.slowDataID[i] 		= OsziData.slowDataID;
	    }
		nwsend.status = OsziData.status_BareToRTOS;

		i_LifeCheck_process_Ethernet++;
		if(i_LifeCheck_process_Ethernet > 2500){
			i_LifeCheck_process_Ethernet =0;
		}

		// write the data -> handle request /
		if ((nwrote = write(clientfd, &nwsend, sizeof(nwsend))) < 0) {
			xil_printf("%s: ERROR responding to client echo request. received = %d, written = %d\r\n",
					__FUNCTION__, nread, nwrote);
			xil_printf("Closing socket %d\r\n", clientfd);
			break;
		}
    	asm(" nop");

    	// read a max of RECV_BUF_SIZE bytes from socket /
        if (nwrote > 0){
        	//nwrote = read(clientfd, (char *)buffer, TCPPACKETSIZE);
    		// read a max of RECV_BUF_SIZE bytes from socket /
    		if ((nread = read(clientfd, (char *)recv_buf, TCPPACKETSIZE)) < 0) {
    			xil_printf("%s: error reading from socket %d, closing socket\r\n", __FUNCTION__, clientfd);
    			break;
    		}
        	//asm(" nop");
        	if (nread == 4){
        		command = *((u32_t*)recv_buf); // cast 4 bytes to Uint32
        		if (command != 0)
        		{
        			// UInt16 temp = ipc_mtoc->counter;
//        			if(TransferSendAllowed ==1)	{
          			ControlData.id = (u16_t)command; 			// Erste 2 Bytes: Commands in Form von Flags/Nummern
        			ControlData.value = (s16_t)(command >> 16);	// Letzte 2 Bytes: Zahlenwert Uebergabe
        			//TODO: //IPCMtoCFlagSet(IPC_FLAG3);
//        			}
        		}
        	}

    		// break if client closed connection /
    		if (nread <= 0){
    			close(clientfd);
    			break;
    		}
        }else{
            close(clientfd);
            // flag = FALSE;
        }
	}

	// close connection
	close(clientfd);
	vTaskDelete(NULL);
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  application_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      This is the tcpHandler.
 *      Creates new Task to handle new TCP connections.
 *---------------------------------------------------------------------------*/
void application_thread()
{
	int sock, new_clientfd;
	struct sockaddr_in address, remote;
	int size;

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	address.sin_family = AF_INET;
	address.sin_port = htons(TCPPORT);
	address.sin_addr.s_addr = INADDR_ANY;

	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
		return;

	lwip_listen(sock, 0);

	size = sizeof(remote);

	while (1) {
		if ((new_clientfd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			sys_thread_new("echos", process_request_thread,
				(void*)new_clientfd,
				THREAD_STACKSIZE,
				DEFAULT_THREAD_PRIO);
		}
	}
}
