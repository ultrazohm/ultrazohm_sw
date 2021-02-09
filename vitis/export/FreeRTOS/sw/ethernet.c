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
#include <string.h>

#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"

#include "../main.h"

#define LONG_TIME 0xffff

extern ARM_to_Oszi_Data_shared_struct OsziData_Shadow;
extern Oszi_to_ARM_Data_shared_struct ControlData;

extern QueueHandle_t OsziData_queue;

NetworkSendStruct nwsend;

Xint16 i_LifeCheck_process_Ethernet =0, TransferSendAllowed=0;
char recv_buf[2048];

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
	int nread, nwrote;
	int foo;

	nwsend.status = 0x00;

	for(foo=0; foo<NETWORK_SEND_FIELD_SIZE; foo++){
		nwsend.slowDataContent[foo] = 0;
		nwsend.val_01[foo] = 0;
		nwsend.val_02[foo] = 0;
		nwsend.val_03[foo] = 0;
		nwsend.val_04[foo] = 0;
		nwsend.val_05[foo] = 0;
		nwsend.val_06[foo] = 0;
		nwsend.val_07[foo] = 0;
		nwsend.val_08[foo] = 0;
		nwsend.val_09[foo] = 0;
		nwsend.val_10[foo] = 0;
		nwsend.val_11[foo] = 0;
		nwsend.val_12[foo] = 0;
		nwsend.val_13[foo] = 0;
		nwsend.val_14[foo] = 0;
		nwsend.val_15[foo] = 0;
		nwsend.val_16[foo] = 0;
		nwsend.val_17[foo] = 0;
		nwsend.val_18[foo] = 0;
		nwsend.val_19[foo] = 0;
		nwsend.val_20[foo] = 0;
		nwsend.slowDataID[foo] = 0;
	}

	xil_printf("tcpWorker: start clientfd = 0x%x\n", clientfd);

	while (1) {

		u32_t command=0;
		u8_t i=0;


		for (i=0; i<NETWORK_SEND_FIELD_SIZE; i++){

				xQueueReceive(OsziData_queue,&OsziData_Shadow,100);
				nwsend.val_01[i] 	= OsziData_Shadow.val[0];
				nwsend.val_02[i] 	= OsziData_Shadow.val[1];
				nwsend.val_03[i] 	= OsziData_Shadow.val[2];
				nwsend.val_04[i]  	= OsziData_Shadow.val[3];
				nwsend.val_05[i]  	= OsziData_Shadow.val[4];
				nwsend.val_06[i]  	= OsziData_Shadow.val[5];
				nwsend.val_07[i] 	= OsziData_Shadow.val[6];
				nwsend.val_08[i] 	= OsziData_Shadow.val[7];
				nwsend.val_09[i] 	= OsziData_Shadow.val[8];
				nwsend.val_10[i] 	= OsziData_Shadow.val[9];
				nwsend.val_11[i]  	= OsziData_Shadow.val[10];
				nwsend.val_12[i]  	= OsziData_Shadow.val[11];
				nwsend.val_13[i]  	= OsziData_Shadow.val[12];
				nwsend.val_14[i] 	= OsziData_Shadow.val[13];
				nwsend.val_15[i] 	= OsziData_Shadow.val[14];
				nwsend.val_16[i] 	= OsziData_Shadow.val[15];
				nwsend.val_17[i] 	= OsziData_Shadow.val[16];
				nwsend.val_18[i] 	= OsziData_Shadow.val[17];
				nwsend.val_19[i] 	= OsziData_Shadow.val[18];
				nwsend.val_20[i] 	= OsziData_Shadow.val[19];
				nwsend.slowDataContent[i] 	= OsziData_Shadow.slowDataContent;
				nwsend.slowDataID[i] 		= OsziData_Shadow.slowDataID;
		}
		nwsend.status = OsziData_Shadow.status_BareToRTOS;

		// At this point, Ethernet Package is full and ready to be sent

		i_LifeCheck_process_Ethernet++;
		if(i_LifeCheck_process_Ethernet > 2500){
			i_LifeCheck_process_Ethernet =0;
		}

		// write the data -> handle request /
		// The data is sent here
		if ((nwrote = write(clientfd, &nwsend, sizeof(nwsend))) < 0) {
			xil_printf("%s: ERROR responding to client echo request. received = %d, written = %d\r\n",
			__FUNCTION__, nread, nwrote);
			xil_printf("Closing socket %d\r\n", clientfd);
			break;
		}
		asm(" nop");

		// read a max of RECV_BUF_SIZE bytes from socket /
		if (nwrote > 0){
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
					ControlData.id = (u16_t)command; 			// Erste 2 Bytes: Commands in Form von Flags/Nummern
					ControlData.value = (s16_t)(command >> 16);	// Letzte 2 Bytes: Zahlenwert Uebergabe
				}
			}

			// break if client closed connection /
			if (nread <= 0){
				close(clientfd);
				break;
			}
		}else{
			close(clientfd);
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
