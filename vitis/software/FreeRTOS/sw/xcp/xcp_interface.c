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
typedef struct {
	uint8_t array_50_byte [50];
	uint8_t array_90_byte [90];
	uint8_t array_100_byte [100];

	uint8_t saw_u8;
	int8_t sin_u8;
	int8_t cos_u8;
	float sin_f;
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
extern xcp_data_t xcp_data;
xcp_data_t xcp_data = {0};

//static QueueHandle_t queue_tx;

static uint32_t xcp_msg_tx_cnt = 0;
static uint32_t xcp_msg_rx_cnt = 0;

volatile uint8_t flag_connection_active = 0;

static uint32_t xcp_timestamp = 0;

extern uint64_t timestamp;
uint64_t timestamp = 0;
extern uint64_t time_irq_ns, time_irq_max_ns;
uint64_t time_irq_ns = 0, time_irq_max_ns = 0;
extern uint64_t time_irq_rate_ns, time_irq_rate_max_ns;
uint64_t time_irq_rate_ns = 0, time_irq_rate_max_ns = 0;

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/
// Todo remove
static void init_dummy_variables(void)
{
	for (int i = 0; i < 50; i++) {
		xcp_data.meas.array_50_byte[i] = i;
	}
	for (int i = 0; i < 90; i++) {
		xcp_data.meas.array_90_byte[i] = i;
	}
	for (int i = 0; i < 100; i++) {
		xcp_data.meas.array_100_byte[i] = i;
	}
}

// Todo remove
static void set_dummy_variables(void)
{

	for (int i = 0; i < 50; i++) {
		xcp_data.meas.array_50_byte[i]++;
	}
	for (int i = 0; i < 90; i++) {
		xcp_data.meas.array_90_byte[i]++;
	}
	for (int i = 0; i < 100; i++) {
		xcp_data.meas.array_100_byte[i]++;
	}

	// Get sine wave with about 1 Hz
	static int div_cnt = 0;
	div_cnt++;
	if (div_cnt >= 800) {
		div_cnt = 0;

		static uint8_t cnt_sin = 0;
		cnt_sin++;
		xcp_data.meas.saw_u8 = cnt_sin;
		float angle = (M_PI * 2 * cnt_sin / UINT8_MAX);
		xcp_data.meas.sin_f = sinf(angle);
		xcp_data.meas.sin_u8 = sinf(angle) * INT8_MAX;
		xcp_data.meas.cos_u8 = cosf(angle) * INT8_MAX;
	}
}

static void print_frame(char *str, uint8_t *data, int len)
{
	xil_printf("%s, %d: ", str, len);
	for (int i = 0; i < len; i++) {
		xil_printf("%02X ", data[i]);
	}
	xil_printf("\n");
}

static void my_print_ip(ip_addr_t *ip)
{
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

static void xcp_interface_init(void)
{
	xil_printf("%s() \n", __func__);

//	queue_tx = xQueueGenericCreate(10, BUF_SIZE_XCP_TX, 0);

	// Init xcp basic driver
	XcpInit();

    bsp_timer_init();
    bsp_timer_start();
//	bsp_ringBuffer_init();

    init_dummy_variables();
}

static void xcp_eth_tx(void *arg_p)
{
	int sd = * (int *) arg_p;
	int nwrote;

	xil_printf("%s() start\n", __func__);
	vTaskDelay(1);

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
				xil_printf("ERROR: TCP socket write failed\n");
				break;
			}
		} else {
			vTaskDelay(1);
		}
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

	uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
	while (1) {

		// Will block here until new data is available
		if ((n = read(sd, buf_xcp_rx, BUF_SIZE_XCP_RX)) < 0) {
			xil_printf("ERROR: TCP socket read failed\n");
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

	xil_printf("%s(): delete\n", __func__);
	flag_connection_active = 0;
	close(sd);
	vTaskDelete(NULL);
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void timer_irq_callback_10kHz(void)
{
	static uint64_t ts_start = 0;
	uint64_t ts_now = bsp_timer_timestamp_u64_get();
	time_irq_rate_ns = bsp_timer_timestamp_u64_get_time_delta_ns(ts_start, ts_now);
	if (time_irq_rate_ns > time_irq_rate_max_ns)
		time_irq_rate_max_ns = time_irq_rate_ns;
	ts_start = ts_now;


	timestamp = bsp_timer_timestamp_u64_get();

	xcp_timestamp = bsp_timer_timestamp_get();

	XcpEvent(XCP_EVENT_FAST);

	static uint32_t cnt_div_100us = 1;
	cnt_div_100us++;
	if (cnt_div_100us >= 10) {
		cnt_div_100us = 0;
		XcpEvent(XCP_EVENT_100US);
	}

	static uint32_t cnt_div_10 = 1;
	cnt_div_10++;
	if (cnt_div_10 >= 100) {
		cnt_div_10 = 0;
		XcpEvent(XCP_EVENT_1MS);
	}

	static uint32_t cnt_div_100 = 2;
	cnt_div_100++;
	if (cnt_div_100 >= 1000) {
		cnt_div_100 = 0;
		XcpEvent(XCP_EVENT_10MS);
	}

	static uint32_t cnt_div_1000 = 3;
	cnt_div_1000++;
	if (cnt_div_1000 >= 10000) {
		cnt_div_1000 = 0;
		XcpEvent(XCP_EVENT_100MS);

		// No xcp background calculations necessary
//		XcpBackground();
	}

	static uint32_t cnt_div_10000 = 4;
	cnt_div_10000++;
	if (cnt_div_10000 >= 100000) {
		cnt_div_10000 = 0;
		XcpEvent(XCP_EVENT_1S);
	}


	uint8_t *data_p = 0;
	if (bsp_ringBuffer_get(rbt_rx, &data_p) > 0) {
		XcpCommand((uint32_t *) (data_p + XCP_HEADER_LEN));
	}

}

void timer_irq_callback__(void)
{
//    void foc_speed_test(void);
//    foc_speed_test();

	set_dummy_variables();

	uint64_t ts_start = bsp_timer_timestamp_u64_get();

	timer_irq_callback_10kHz();

	uint64_t ts_end = bsp_timer_timestamp_u64_get();
	time_irq_ns = bsp_timer_timestamp_u64_get_time_delta_ns(ts_start, ts_end);
	if (time_irq_ns > time_irq_max_ns)
		time_irq_max_ns = time_irq_ns;

	static uint32_t cnt_div_s = 0;
	cnt_div_s++;
	if (cnt_div_s >= 30000) {
		cnt_div_s = 0;
		time_irq_max_ns = 0;
		time_irq_rate_max_ns = 0;
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

	while (1) {
		int new_sd;
		int size = sizeof(remote);

		xil_printf("%s() waiting for xcp master connection\n", __func__);
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
	return (XcpDaqTimestampType) xcp_timestamp;
}
