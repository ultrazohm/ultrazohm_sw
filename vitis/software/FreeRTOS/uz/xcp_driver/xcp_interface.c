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

//#include "../bsp/bsp_general.h"
//#include "../bsp/bsp_timer.h"
//#include "../bsp/bsp_can.h"
#include "xil_cache.h"


#include "../../../../software/FreeRTOS/uz/xcp_driver/xcp_config.h"
#include "../../../../software/FreeRTOS/uz/xcp_driver/XCP_Basic/XcpBasic.h"

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
#define STACKSIZE_XCP			(1024 * 10)

#define XCP_CAN_QUEUE_TIMEOUT		1

#define BUF_SIZE_XCP_RX			(kXcpMaxCTO + XCP_HEADER_LEN)
#define BUF_SIZE_XCP_TX			(kXcpMaxCTO + XCP_HEADER_LEN)

#define PRIO_XCP_BACKGROUND		7
#define PRIO_XCP_RX				5
#define PRIO_XCP_TX				4

/*-------------------------------------------------------------------
 * Type definitions
 *-----------------------------------------------------------------*/
typedef struct {
	uint8_t array_50_byte [50];
	uint8_t array_90_byte [90];
	uint8_t array_100_byte [100];

	uint8_t saw_u8;
	int8_t sine_u8;
	int8_t cos_u8;
	float sine_f;
} meas_t;

typedef struct {
	uint8_t stop_calc;
} stim_t;

typedef struct {
	meas_t meas;
	stim_t stim;
} xcp_data_t;

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static xcp_data_t xcp_data;

static uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
static uint8_t buf_xcp_tx[BUF_SIZE_XCP_TX];

static QueueHandle_t queue_tx;

static uint32_t xcp_timestamp;

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/
#ifdef USE_XCP_ETH
static void my_print_ip(ip_addr_t *ip)
{
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}
#endif

static void task_100ms(void *p)
{
	xil_printf("%s() \n", __func__);

	while(1) {
		if (xcp_data.stim.stop_calc == 0) {
			xcp_data.meas.saw_u8++;
			float arg_2pi = (float) xcp_data.meas.saw_u8 * (float)M_PI * 2 / 255;
			xcp_data.meas.sine_f = sinf(arg_2pi);
			xcp_data.meas.sine_u8 = xcp_data.meas.sine_f * 127;
			xcp_data.meas.cos_u8 = sinf(arg_2pi + (float)M_PI / 2) * 127;
		}

    	vTaskDelay(100 / portTICK_RATE_MS);
	}
}

static void xcp_interface_init(void)
{
	xil_printf("%s() \n", __func__);

	queue_tx = xQueueGenericCreate(10, BUF_SIZE_XCP_TX, 0);

	// Init xcp basic driver
	XcpInit();

//    bsp_timer_init();
//    bsp_timer_start();
//    if (bsp_can_init() != XST_SUCCESS) {
//		xil_printf("%s(): can init failed \n", __func__);
//	}

    // TODO: Replace sys_thread_new() with xTaskCreate()
    //xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask)
	// Set up Tasks for the slow DAQ xcp events
	sys_thread_new("task_100ms", task_100ms,
		NULL, STACKSIZE_XCP, PRIO_XCP_BACKGROUND);
}

#ifdef USE_XCP_CAN
static void xcp_can_trx(void *arg_p)
{
	xil_printf("%s() start\n", __func__);
	vTaskDelay(1);

	while (1) {
		//-----------------------------
		// CAN tx
		//-----------------------------
		BaseType_t xret_val;
		xret_val = xQueueReceive(queue_tx, buf_xcp_tx, XCP_CAN_QUEUE_TIMEOUT);
		if(xret_val != errQUEUE_EMPTY) {
			if(xret_val != pdPASS) {
				xil_printf("%s(): xQueueReceive() failed\n", __func__);
				bsp_non_recoverable_error(NULL);
			}

			// length is encoded in first four bytes of the queue items
			uint16_t len_xcp_tx;
			len_xcp_tx = ((buf_xcp_tx[0] << 0) | (buf_xcp_tx[1] << 8));

			can_frame_t frame_tx;
			frame_tx.len = len_xcp_tx;
			frame_tx.id = XCP_CAN_ID_TX;
			// XCP payload starts after header (first four bytes)
			uint8_t* u8_p = &buf_xcp_tx[XCP_HEADER_LEN];
			for (int lc = 0; lc < frame_tx.len; lc++) {
				frame_tx.data[lc] = u8_p[lc];
			}

			if (bsp_can_tx(&frame_tx) != XST_SUCCESS) {
				xil_printf("%s(): bsp_can_tx() failed\n", __func__);
				break;
			}

			XcpSendCallBack();
		}

		//-----------------------------
		// CAN rx
		//-----------------------------
		can_frame_t frame_rx;
		int ret_val;
		ret_val = bsp_can_rx(&frame_rx);
		if (ret_val != XST_NO_DATA) {
			if (ret_val != XST_SUCCESS) {
				xil_printf("%s(): bsp_can_rx() failed\n", __func__);
				break;
			}

			XcpCommand((uint32_t *) (frame_rx.data));
		}
	}

	xil_printf("%s(): delete\n", __func__);
	vTaskDelete(NULL);
}
#endif

#ifdef USE_XCP_ETH
static void xcp_eth_tx(void *arg_p)
{
	int sd = * (int *) arg_p;
	int nwrote;

	xil_printf("%s() start\n", __func__);
	vTaskDelay(1);

	while (1) {
		if(xQueueReceive(queue_tx, buf_xcp_tx, portMAX_DELAY) != pdPASS) {
			xil_printf("%s(): xQueueReceive() failed\n", __func__);
			xil_printf("%s(): critical error, can not recover\n", __func__);
			vTaskDelay(5);
			return;
		}

		static uint16_t xcp_package_counter = 0;
		xcp_package_counter++;
		// length was already written before msg was given to queue
		uint16_t len_xcp_tx;
		len_xcp_tx = ((buf_xcp_tx[0] << 0) | (buf_xcp_tx[1] << 8));

		buf_xcp_tx[2] = (uint8_t) (xcp_package_counter >> 0);
		buf_xcp_tx[3] = (uint8_t) (xcp_package_counter >> 8);

		if ((nwrote = write(sd, buf_xcp_tx, (len_xcp_tx + XCP_HEADER_LEN))) < 0) {
			xil_printf("%s(): write() failed\n", __func__);
			break;
		}

		XcpSendCallBack();
	}

	xil_printf("%s(): delete\n", __func__);
	close(sd);
	vTaskDelete(NULL);
}

static void xcp_eth_rx(void *arg_p)
{
	int sd = * (int *) arg_p;
	int n;

	xil_printf("%s() start\n", __func__);

	while (1) {
		// Will block here until new data is available
		if ((n = read(sd, buf_xcp_rx, BUF_SIZE_XCP_RX)) < 0) {
			xil_printf("ERROR: could not read from xcp master socket\n");
			break;
		}

		// No bytes means socket was closed by counterpart
		if (n <= 0) {
			xil_printf("%s(): n <= 0\n", __func__);
			continue;
		}

		XcpCommand((uint32_t *) (buf_xcp_rx + XCP_HEADER_LEN));
	}

	xil_printf("%s(): delete\n", __func__);
	close(sd);
	vTaskDelete(NULL);
}
#endif

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void timer_irq_callback_10kHz(void)
{
	// Set the timestamp which comes from R5 once.
	// TODO maybe there is a cleaner solution?
	//const uint32_t xcp_timestamp_addr = (MEM_SHARED_START + 0x1000);
	const uint32_t xcp_timestamp_addr = (0xFFFF0000 + 0x1000);
	uint32_t *xcp_timestamp_p = (uint32_t *)xcp_timestamp_addr;
	Xil_DCacheFlushRange(xcp_timestamp_addr, 4);
	xcp_timestamp = *xcp_timestamp_p;

	XcpEvent(XCP_EVENT_FAST);

	static uint32_t cnt_div_10 = 0;
	cnt_div_10++;
	if (cnt_div_10 >= 10) {
		cnt_div_10 = 0;
		XcpEvent(XCP_EVENT_1MS);
	}

	static uint32_t cnt_div_100 = 1;
	cnt_div_100++;
	if (cnt_div_100 >= 100) {
		cnt_div_100 = 0;
		XcpEvent(XCP_EVENT_10MS);
	}

	static uint32_t cnt_div_1000 = 2;
	cnt_div_1000++;
	if (cnt_div_1000 >= 1000) {
		cnt_div_1000 = 0;
		XcpEvent(XCP_EVENT_100MS);

		XcpBackground();
	}

	static uint32_t cnt_div_10000 = 3;
	cnt_div_10000++;
	if (cnt_div_10000 >= 10000) {
		cnt_div_10000 = 0;
		XcpEvent(XCP_EVENT_1S);
	}

//	static uint8_t cnt= 0;
//	cnt++;
//	static uint8_t cnt_array_50 = 0;
//	if (++cnt_array_50 >= 50) {
//		cnt_array_50 = 0;
//	}
//	xcp_data.meas.array_50_byte[cnt_array_50] = cnt;
//
//	static uint8_t cnt_array_90 = 0;
//	if (++cnt_array_90 >= 90) {
//		cnt_array_90 = 0;
//	}
//	xcp_data.meas.array_90_byte[cnt_array_90] = cnt;
}

void wait_for_xcp_master(void *p)
{
	xil_printf("%s() start\n", __func__);

	xcp_interface_init();

#ifdef USE_XCP_CAN
	sys_thread_new("xcp_can_trx", xcp_can_trx,
		0, STACKSIZE_XCP, PRIO_XCP_TX);
#endif
#ifdef USE_XCP_ETH
	struct sockaddr_in address, remote;
	memset(&address, 0, sizeof(address));

	int sock;
	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		xil_printf("create socket failed\n");
		return;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(XCP_ETH_PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0) {
		return;
	}
	lwip_listen(sock, 0);

	while (1) {
		int new_sd;
		int size = sizeof(remote);

		xil_printf("%s() waiting for xcp master connection on port %d\n", __func__, XCP_ETH_PORT);
		if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			xil_printf("xcp master connected from\n");
			my_print_ip((ip_addr_t*) &remote.sin_addr);
			sys_thread_new("xcp_eth_tx", xcp_eth_tx,
				(void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_TX);
			sys_thread_new("xcp_eth_rx", xcp_eth_rx,
				(void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_RX);
		}
	}
#endif
	xil_printf("%s(): delete\n", __func__);
	vTaskDelete(NULL);
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
	BaseType_t * const pxHigherPriorityTaskWoken_ = 0;
	uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;

	msg_with_header_p[0] = (uint8_t) (len >> 0);
	msg_with_header_p[1] = (uint8_t) (len >> 8);

	if(xQueueSendFromISR(queue_tx,
			  	  	     msg_with_header_p,
						 pxHigherPriorityTaskWoken_) != pdPASS) {
		xil_printf("%s(): xQueueSend() failed\n", __func__);
		xil_printf("%s(): critical error!\n", __func__);
		vTaskDelay(5);
		return;
	}
}

MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr )
{
	// Address extension is not used.
	// --> addr already holds the requested memory address
	return (MTABYTEPTR) addr;
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
	//return (XcpDaqTimestampType) bsp_timer_timestamp_get();
	return (XcpDaqTimestampType) xcp_timestamp;
}
