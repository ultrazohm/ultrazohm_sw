/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */

#include "FreeRTOS.h"
#include "task.h"
#include "netif/xadapter.h"
#include "xil_printf.h"
#include "lwip/sockets.h"
#include "queue.h"
#include "math.h"
#include "stdint.h"
// TODO create functionality when used with cache
//#include "xil_cache_l.h"

#include "../bsp_timer/bsp_timer.h"
#include "../bsp_ringBuffer/bsp_ringBuffer.h"
#include "xcp_config.h"
#include "XCP_Basic/XcpBasic.h"


/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
#define STACKSIZE_XCP			(1024 * 10)

#define BUF_SIZE_XCP_RX			(kXcpMaxCTO + XCP_HEADER_LEN)
#define BUF_SIZE_XCP_TX			(kXcpMaxCTO + XCP_HEADER_LEN)

#define PRIO_XCP_RX				5
#define PRIO_XCP_TX				5

/*-------------------------------------------------------------------
 * Type definitions
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static uint32_t xcp_msg_tx_cnt = 0;
static uint32_t xcp_msg_rx_cnt = 0;

volatile uint8_t flag_connection_active = 0;

static uint32_t xcp_timestamp = 0;



/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/

static void my_print_ip(ip_addr_t *ip)
{
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

static void xcp_interface_init(void)
{
	//xil_printf("%s() \n", __func__);

//	queue_tx = xQueueGenericCreate(10, BUF_SIZE_XCP_TX, 0);

	// Init xcp basic driver
	XcpInit();

    bsp_timer_init();
    bsp_timer_start();
//	bsp_ringBuffer_init();
}

static void xcp_eth_tx(void *arg_p)
{
	int sd = * (int *) arg_p;
	int nwrote;

//	xil_printf("%s() start\n", __func__);
//	vTaskDelay(1);

	uint8_t buf_xcp_tx[BUF_SIZE_XCP_TX];
	while (flag_connection_active) {
		uint8_t *data_p = 0;
		if (bsp_ringBuffer_get(rbt_tx, &data_p) > 0) {
			// length was already written before msg was given to queue
			uint16_t len_tcp_tx =
					((data_p[0] << 0) | (data_p[1] << 8)) + XCP_HEADER_LEN;
			memcpy(buf_xcp_tx, data_p, len_tcp_tx);

			static uint16_t xcp_package_counter = 0;
			xcp_package_counter++;
			buf_xcp_tx[2] = (uint8_t) (xcp_package_counter >> 0);
			buf_xcp_tx[3] = (uint8_t) (xcp_package_counter >> 8);

			xcp_msg_tx_cnt++;

			if ((nwrote = write(sd, buf_xcp_tx, len_tcp_tx)) < 0) {
//				xil_printf("ERROR: TCP socket write failed\n");
				break;
			}
		} else {
			vTaskDelay(1);
		}
	}

	xil_printf("XCP connection closed\n");

//	xil_printf("%s(): delete\n", __func__);
	close(sd);
	vTaskDelete(NULL);
}

static void xcp_eth_rx(void *arg_p)
{
	int sd = * (int *) arg_p;
	int n;

//	xil_printf("%s() start\n", __func__);

	uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
	while (1) {

		// Will block here until new data is available
		if ((n = read(sd, buf_xcp_rx, BUF_SIZE_XCP_RX)) < 0) {
			//xil_printf("ERROR: TCP socket read failed\n");
			break;
		}

		// No bytes means socket was closed by counterpart
		if (n <= 0) {
			xil_printf("%s(): Socket closed by counterpart\n", __func__);
			continue;
		}

		xcp_msg_rx_cnt++;

		bsp_ringBuffer_write(rbt_rx, buf_xcp_rx, n);
	}

//	xil_printf("%s(): delete\n", __func__);
	flag_connection_active = 0;
	close(sd);
	vTaskDelete(NULL);
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
/*
 * Implement to override the default handler
 */
void timer_irq_callback__(void)
{
	return;
}

void xcp_event_fast(void)
{
	// Timestamp used for all xcp events
	xcp_timestamp = bsp_timer_timestamp_get();

	XcpEvent(XCP_EVENT_FAST);
}

// This function shall be called each 1 ms
// All xcp events, but the fast are derived from this function
void xcp_events_1ms(void)
{
	XcpEvent(XCP_EVENT_1MS);

	static uint32_t cnt_div_10ms = 2;
	cnt_div_10ms++;
	if (cnt_div_10ms >= 10) {
		cnt_div_10ms = 0;
		XcpEvent(XCP_EVENT_10MS);
	}

	static uint32_t cnt_div_100ms = 3;
	cnt_div_100ms++;
	if (cnt_div_100ms >= 100) {
		cnt_div_100ms = 0;
		XcpEvent(XCP_EVENT_100MS);

		// No xcp background calculations necessary
//		XcpBackground();
	}

	static uint32_t cnt_div_1s = 4;
	cnt_div_1s++;
	if (cnt_div_1s >= 1000) {
		cnt_div_1s = 0;
		XcpEvent(XCP_EVENT_1S);
	}

	// Also read one incoming XCP message per cycle
	uint8_t *data_p = 0;
	if (bsp_ringBuffer_get(rbt_rx, &data_p) > 0) {
		XcpCommand((uint32_t *) (data_p + XCP_HEADER_LEN));
	}
}

void xcp_interface(void *p)
{
	xil_printf("%s() start\n", __func__);

	xcp_interface_init();

	struct sockaddr_in address, remote;
	memset(&address, 0, sizeof(address));

	int sock;
	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		xil_printf("create socket failed\n");
        xil_printf("%s(): critical error!\n", __func__);
        vTaskDelay(5);
        return;
		return;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(XCP_ETH_PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0) {
		return;
	}
	lwip_listen(sock, 0);

	xil_printf("%s() waiting for xcp master connection\n", __func__);
	while (1) {
		int new_sd;
		int size = sizeof(remote);

		if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			xil_printf("xcp master connected from: ");
			my_print_ip((ip_addr_t*) &remote.sin_addr);

			bsp_ringBuffer_init();
			flag_connection_active = 1;

			sys_thread_new("xcp_eth_tx", xcp_eth_tx,
				(void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_TX);
			sys_thread_new("xcp_eth_rx", xcp_eth_rx,
				(void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_RX);
		}
	}

	xil_printf("%s(): delete\n", __func__);
	vTaskDelete(NULL);
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
	uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;

	msg_with_header_p[0] = (uint8_t) (len >> 0);
	msg_with_header_p[1] = (uint8_t) (len >> 8);

	len += XCP_HEADER_LEN;

	bsp_ringBuffer_write(rbt_tx, msg_with_header_p, len);

	XcpSendCallBack();
}

MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr )
{
	// Address extension is not used.
	// --> addr already holds the requested memory address

	return (MTABYTEPTR)((size_t)addr);
}

void ApplXcpInterruptDisable( void )
{
	// Do not disable IRQs. Synchronization is ensured by using OS tasks
	//Xil_ExceptionDisable();
}

void ApplXcpInterruptEnable( void )
{
	//Xil_ExceptionEnable();
}

vuint8 ApplXcpSendStall( void )
{
	return (vuint8) 0;
}

XcpDaqTimestampType ApplXcpGetTimestamp(void)
{
	return (XcpDaqTimestampType) xcp_timestamp;
}
