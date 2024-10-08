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

#include <string.h>
#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "FreeRTOS.h"
#include "task.h"
#include "APU_RPU_shared.h"

#include "../main.h"

extern QueueHandle_t js_queue;
extern struct APU_to_RPU_t ControlData;

int js_connection_established = 0;
int i_LifeCheck_process_Ethernet = 0;


//==============================================================================================================================================================
void print_echo_app_header()
{
    uz_printf("%20s %6d %s\r\n", "echo server",
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
	struct javascope_data_t javascope_data_sending = {0};
	NetworkSendStruct nwsend = {0};
	char recv_buf[2048] = {0};
	struct APU_to_RPU_t* Received_Data = {0};

	int clientfd = (int)p;
	int nread = 0;
	int nwrote = 0;

	uz_printf("APU: Javascope connected 0x%x\n", clientfd);
	js_connection_established = clientfd;

	xQueueReset(js_queue); //purge queue once new connection is established

	while (1) {

		for (size_t i=0; i<NETWORK_SEND_FIELD_SIZE; i++){

			// Take one element from queue
			// The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call.
			xQueueReceive(js_queue, &javascope_data_sending, JS_QUEUE_RECEIVE_TICKS2WAIT);

			// copy data into nwsend struct
			nwsend.val_01[i] 	= javascope_data_sending.scope_ch[0];
			nwsend.val_02[i] 	= javascope_data_sending.scope_ch[1];
			nwsend.val_03[i] 	= javascope_data_sending.scope_ch[2];
			nwsend.val_04[i]  	= javascope_data_sending.scope_ch[3];
			nwsend.val_05[i]  	= javascope_data_sending.scope_ch[4];
			nwsend.val_06[i]  	= javascope_data_sending.scope_ch[5];
			nwsend.val_07[i] 	= javascope_data_sending.scope_ch[6];
			nwsend.val_08[i] 	= javascope_data_sending.scope_ch[7];
			nwsend.val_09[i] 	= javascope_data_sending.scope_ch[8];
			nwsend.val_10[i] 	= javascope_data_sending.scope_ch[9];
			nwsend.val_11[i]  	= javascope_data_sending.scope_ch[10];
			nwsend.val_12[i]  	= javascope_data_sending.scope_ch[11];
			nwsend.val_13[i]  	= javascope_data_sending.scope_ch[12];
			nwsend.val_14[i] 	= javascope_data_sending.scope_ch[13];
			nwsend.val_15[i] 	= javascope_data_sending.scope_ch[14];
			nwsend.val_16[i] 	= javascope_data_sending.scope_ch[15];
			nwsend.val_17[i] 	= javascope_data_sending.scope_ch[16];
			nwsend.val_18[i] 	= javascope_data_sending.scope_ch[17];
			nwsend.val_19[i] 	= javascope_data_sending.scope_ch[18];
			nwsend.val_20[i] 	= javascope_data_sending.scope_ch[19];
			nwsend.slowDataContent[i] 	= javascope_data_sending.slowDataContent;
			nwsend.slowDataID[i] 		= javascope_data_sending.slowDataID;
		}
		nwsend.status = javascope_data_sending.status;

		// At this point, Ethernet Package is full and ready to be sent
		i_LifeCheck_process_Ethernet++;
		if(i_LifeCheck_process_Ethernet > 2500){
			i_LifeCheck_process_Ethernet =0;
		}

		// write the data -> handle request /
		// The data is sent here
		if ((nwrote = write(clientfd, &nwsend, sizeof(nwsend))) < 0) {
			uz_printf("APU: %s: ERROR responding to client echo request. received = %d, written = %d\r\n",
			__FUNCTION__, nread, nwrote);
			uz_printf("APU: Closing socket %d\r\n", clientfd);
			js_connection_established = 0;
			break;
		}
		asm("nop");

		// read a max of RECV_BUF_SIZE bytes from socket /
		if (nwrote > 0){
			// read a max of RECV_BUF_SIZE bytes from socket /
			nread = read(clientfd, (char *)recv_buf, TCPPACKETSIZE);
			if (nread < 0) {
				uz_printf("APU: %s: error reading from socket %d, closing Javascope socket\r\n", __FUNCTION__, clientfd);
				js_connection_established = 0;
				break;
			}
			//asm(" nop");
			if ( nread == sizeof(ControlData) ){
				Received_Data = ((struct APU_to_RPU_t*)recv_buf); // cast received bytes
				ControlData.id 		= Received_Data->id;
				ControlData.value 	= Received_Data->value;
			}

			// break if client closed connection /
			if (nread <= 0){
				close(clientfd);
				js_connection_established = 0;
				break;
			}
		}else{
			close(clientfd);
			js_connection_established = 0;
		}
	}

	// close connection
	close(clientfd);
	js_connection_established = 0;
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
	int sock;
	int new_clientfd;
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
