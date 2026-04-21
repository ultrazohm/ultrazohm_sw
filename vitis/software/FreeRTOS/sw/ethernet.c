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
extern QueueHandle_t js_control_queue;
extern volatile int js_queue_overflow_dropped_samples;
extern volatile int js_queue_purge_requested;

#define JS_TX_STALL_TIMEOUT_TICKS pdMS_TO_TICKS(4000U)

volatile int js_connection_established = 0;
int i_LifeCheck_process_Ethernet = 0;

static int js_replace_active_client(const int new_clientfd)
{
	int old_clientfd = 0;

	taskENTER_CRITICAL();
	old_clientfd = js_connection_established;
	js_connection_established = new_clientfd;
	taskEXIT_CRITICAL();

	return old_clientfd;
}

static BaseType_t js_release_active_client_if_owner(const int clientfd)
{
	BaseType_t is_owner = pdFALSE;

	taskENTER_CRITICAL();
	if (js_connection_established == clientfd) {
		js_connection_established = 0;
		is_owner = pdTRUE;
	}
	taskEXIT_CRITICAL();

	return is_owner;
}

static BaseType_t js_is_active_client(const int clientfd)
{
	BaseType_t is_active = pdFALSE;

	taskENTER_CRITICAL();
	if (js_connection_established == clientfd) {
		is_active = pdTRUE;
	}
	taskEXIT_CRITICAL();

	return is_active;
}


//==============================================================================================================================================================
void print_javascope_app_header(ip_addr_t *ip)
{
    uz_printf("\r\n");
    uz_printf("APU: Connect JavaScope GUI to %d.%d.%d.%d:%d\r\n",
            ip4_addr1(ip), ip4_addr2(ip), ip4_addr3(ip), ip4_addr4(ip), TCPPORT);
    uz_printf("\r\n");
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  process_request_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Worker task for one accepted JavaScope TCP connection. It streams
 *      queued samples to the client and queues incoming control commands for
 *      the A53 ISR/R5 response path. The task exits when the socket closes or
 *      another connection becomes the active JavaScope client.
 *---------------------------------------------------------------------------*/
void process_request_thread(void *p)
{
	struct javascope_data_t javascope_data_sending = {0};
	NetworkSendStruct nwsend = {0};
	char recv_buf[2048] = {0};
	struct APU_to_RPU_t received_data = {0};
	size_t recv_buf_fill = 0U;
	const size_t control_data_bytes = sizeof(struct APU_to_RPU_t);

	int clientfd = (int)p;
	int nread = 0;
	int nwrote = 0;
	size_t tx_pending_len = 0U;
	size_t tx_pending_offset = 0U;
	TickType_t tx_last_progress_tick = xTaskGetTickCount();

	xQueueReset(js_queue); // Purge stale samples once a new connection is established.
	xQueueReset(js_control_queue); // Purge pending control commands from the old connection.
	taskENTER_CRITICAL();
	js_queue_overflow_dropped_samples = 0;
	js_queue_purge_requested = 0;
	taskEXIT_CRITICAL();

	while (1) {
		if (js_is_active_client(clientfd) == pdFALSE) {
			break;
		}

		// Always service incoming control stream, independent of TX readiness.
		nread = lwip_recv(clientfd, (char *)recv_buf + recv_buf_fill, TCPPACKETSIZE - recv_buf_fill, MSG_DONTWAIT);
		if (nread < 0) {
			if (js_is_active_client(clientfd) == pdFALSE) {
				break;
			}
			const int socket_error = errno;
			// On some lwIP ports errno may remain 0 for non-blocking "try again".
			if ((socket_error != 0) && (socket_error != EAGAIN) && (socket_error != EWOULDBLOCK)) {
				uz_printf("APU: %s: error reading from socket %d (errno=%d), closing JavaScope socket\r\n", __FUNCTION__, clientfd, socket_error);
				break;
			}
		}
		if (nread > 0) {
			recv_buf_fill += (size_t)nread;

			// Parse all complete control messages in the TCP stream.
			size_t complete_bytes = (recv_buf_fill / control_data_bytes) * control_data_bytes;
			for (size_t offset = 0U; offset < complete_bytes; offset += control_data_bytes) {
				memcpy(&received_data, recv_buf + offset, control_data_bytes);
				if (xQueueSendToBack(js_control_queue, &received_data, 0U) != pdPASS) {
					uz_printf("APU: Control queue full, dropping command id=%lu\r\n", (unsigned long)received_data.id);
				}
			}

			// Keep partial trailing bytes for the next read().
			recv_buf_fill -= complete_bytes;
			if (recv_buf_fill > 0U) {
				memmove(recv_buf, recv_buf + complete_bytes, recv_buf_fill);
			}
		}
		// read() == 0 means the peer performed an orderly TCP close.
		if (nread == 0){
			uz_printf("APU: JavaScope disconnected from socket %d \r\n", clientfd);
			break;
		}

		if (js_queue_purge_requested != 0) {
			int dropped_samples_from_overflow = 0;
			UBaseType_t queued_samples_to_purge = uxQueueMessagesWaiting(js_queue);
			taskENTER_CRITICAL();
			dropped_samples_from_overflow = js_queue_overflow_dropped_samples;
			js_queue_overflow_dropped_samples = 0;
			js_queue_purge_requested = 0;
			taskEXIT_CRITICAL();

			xQueueReset(js_queue);
			tx_pending_len = 0U;
			tx_pending_offset = 0U;
			uz_printf("APU: JavaScope queue overflow -> purged %lu queued + %d overflow-dropped samples\r\n",
					(unsigned long)queued_samples_to_purge,
					dropped_samples_from_overflow);
			taskYIELD();
			continue;
		}

			if (tx_pending_len == 0U) {
				if (uxQueueMessagesWaiting(js_queue) < NETWORK_SEND_FIELD_SIZE) {
					taskYIELD();
					continue;
				}

				for (size_t i=0; i<NETWORK_SEND_FIELD_SIZE; i++){

					// Queue depth was checked above, so this receive is non-blocking.
					xQueueReceive(js_queue, &javascope_data_sending, JS_QUEUE_RECEIVE_TICKS2WAIT);

					// Pack one sample into the batched JavaScope TCP frame.
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
				// TODO(robust framing): prepend a small header (magic, payload_len, seq, crc)
				// so the receiver can verify framing, detect loss, and re-sync after reconnects.
				nwsend.status = javascope_data_sending.status;
				tx_pending_len = sizeof(nwsend);
				tx_pending_offset = 0U;
			}

			const size_t tx_remaining_len = tx_pending_len - tx_pending_offset;
			nwrote = lwip_send(clientfd,
					((const char *)&nwsend) + tx_pending_offset,
					tx_remaining_len,
					MSG_DONTWAIT);
			if (nwrote < 0) {
				if (js_is_active_client(clientfd) == pdFALSE) {
					break;
				}
				const int socket_error = errno;
				// On some lwIP ports errno may remain 0 for non-blocking "try again".
				if ((socket_error != 0) && (socket_error != EAGAIN) && (socket_error != EWOULDBLOCK)) {
					uz_printf("APU: %s: ERROR sending JavaScope data. received = %d, written = %d (errno=%d)\r\n",
							__FUNCTION__, nread, nwrote, socket_error);
					uz_printf("APU: Closing socket %d\r\n", clientfd);
					break;
				}
				// TCP send buffer full: block until socket writable (ACK received) or
				// readable (incoming control data). Avoids busy-spin and CPU starvation
				// of the lwIP timer thread during the ~RTT wait for ACKs.
				{
					fd_set rset, wset;
					FD_ZERO(&rset);
					FD_ZERO(&wset);
					FD_SET(clientfd, &rset);
					FD_SET(clientfd, &wset);
					struct timeval tv = {.tv_sec = 0, .tv_usec = 50000U}; // 50ms max
					(void)lwip_select(clientfd + 1, &rset, &wset, NULL, &tv);
				}
			} else if (nwrote == 0) {
				uz_printf("APU: JavaScope disconnected from socket %d \r\n", clientfd);
				break;
			} else {
				tx_pending_offset += (size_t)nwrote;
				tx_last_progress_tick = xTaskGetTickCount();
				if (tx_pending_offset >= tx_pending_len) {
					tx_pending_len = 0U;
					tx_pending_offset = 0U;

					// At this point, one full Ethernet packet has been transmitted.
					i_LifeCheck_process_Ethernet++;
					if(i_LifeCheck_process_Ethernet > 2500){
						i_LifeCheck_process_Ethernet =0;
					}
				}
			}
			if ((tx_pending_len > 0U) &&
				((xTaskGetTickCount() - tx_last_progress_tick) > JS_TX_STALL_TIMEOUT_TICKS)) {
				uz_printf("APU: TX stalled on socket %d, closing stale JavaScope socket\r\n", clientfd);
				break;
			}
			asm("nop");
		}

	// Release ownership only if this worker still represents the active client.
	(void)js_release_active_client_if_owner(clientfd);
	close(clientfd);
	vTaskDelete(NULL);
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  application_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Accepts JavaScope TCP clients and starts one worker task per accepted
 *      socket. Only one client is active at a time; a new connection replaces
 *      the previous active client.
 *---------------------------------------------------------------------------*/
void application_thread()
{
	int sock;
	int new_clientfd;
	struct sockaddr_in address, remote;
	int size;
	uint32_t connection_count = 0U;

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	address.sin_family = AF_INET;
	address.sin_port = htons(TCPPORT);
	address.sin_addr.s_addr = INADDR_ANY;

	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
		return;

	lwip_listen(sock, 1);

	size = sizeof(remote);

	while (1) {
		if ((new_clientfd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			connection_count++;
			uz_printf("APU: JavaScope connected #%lu (socket 0x%x)\r\n", (unsigned long)connection_count, new_clientfd);

			// TODO: set TCP_SND_BUF = 32768 and MEMP_NUM_TCP_SEG = 512 in lwipopts.h (BSP).

			const int old_clientfd = js_replace_active_client(new_clientfd);
			if ((old_clientfd != 0) && (old_clientfd != new_clientfd)) {
				uz_printf("APU: Replacing old JavaScope socket with connection #%lu (old socket will close itself)\r\n", (unsigned long)connection_count);
			}

			sys_thread_new("javascope_client", process_request_thread,
				(void*)new_clientfd,
				THREAD_STACKSIZE,
				DEFAULT_THREAD_PRIO);
		}
	}
}
