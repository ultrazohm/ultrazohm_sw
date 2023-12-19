/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between UltraZohm project and XCP Basic Driver
 */


#include <stdint.h>


#include "FreeRTOS.h"
#include "task.h"
#include "netif/xadapter.h"
#include "lwip/sockets.h"
#include "queue.h"
#include "xil_printf.h"
#include "xil_cache.h"

#include "xcp_config.h"
#include "XCP_Basic/XcpBasic.h"

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
#define STACKSIZE_XCP           (1024 * 10)

#define XCP_CAN_QUEUE_TIMEOUT   1

#define BUF_SIZE_XCP_RX         (kXcpMaxCTO + XCP_HEADER_LEN)
#define BUF_SIZE_XCP_TX         (kXcpMaxCTO + XCP_HEADER_LEN)

#define PRIO_XCP_BACKGROUND     7
#define PRIO_XCP_RX             5
#define PRIO_XCP_TX             4

// Address definitions for data exchange R5 <-> A53
#define XCP_MEAS_R5_ADDR        0xFFFC0400
#define XCP_MEAS_R5_LEN         0x00001400
// Timestamp from R5 is used
#define XCP_TIMESTAMP_R5_ADDR   0xFFFC0400


/*
 * OCM bank3 is reserved for javascope: Address: 0xFFFF0000, len 0x10000 (= 65K).
 * Place XCP data behind javascope memory in same bank3. Use the last 32K for this.
 */
#define XCP_OUT_ADDR				0xFFFF8000
#define XCP_OUT_LEN					0x00007000
#define XCP_IN_ADDR 				(XCP_OUT_ADDR + XCP_OUT_LEN)
#define XCP_IN_LEN					0x00001000

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
#define QUEUE_XCP_TX_LEN        1000
#define QUEUE_XCP_RX_LEN        10

static QueueHandle_t queue_xcp_tx;
static QueueHandle_t queue_xcp_rx = NULL;

static uint32_t xcp_timestamp;

volatile size_t addr_out_w = 0;
volatile size_t addr_out_r = 0;
volatile size_t addr_in_w = 0;
volatile size_t addr_in_r = 0;
volatile uint8_t xcp_eth_connected = 0;

volatile uint32_t cnt_msg_out_w = 0;
volatile uint32_t cnt_msg_out_r = 0;


volatile uint32_t txq_msg_written = 0;
volatile uint32_t txq_msg_read = 0;

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/
#ifdef USE_XCP_ETH
void my_print_ip(ip_addr_t *ip)
{
    xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
            ip4_addr3(ip), ip4_addr4(ip));
}
#endif

void xcp_interface_init(void)
{
    queue_xcp_tx = xQueueGenericCreate(QUEUE_XCP_TX_LEN, BUF_SIZE_XCP_TX, 0);
    queue_xcp_rx = xQueueGenericCreate(QUEUE_XCP_RX_LEN, BUF_SIZE_XCP_RX, 0);

    *(uint32_t *)XCP_OUT_ADDR = 0;
    *(uint32_t *)XCP_IN_ADDR = 0;

    XcpInit();
//    bsp_timer_init();
//    bsp_timer_start();
}

/*
 * Memory exchange via OCM
 * Memory layout:
 * Byte [0..3]: package len
 * Byte [4..(3 + len)]: payload
 * Byte [len..(3 + len)]: zero. Indicator for OCM reader, this is end of msgs.
 * 						  (If a package follows it will be overwritten
 * 						  with actual length)
 */

void memcpy_volatile(volatile uint8_t *dst, volatile uint8_t *src, int len)
{
	for (int i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

void write_package_to_ocm(volatile size_t *dst_addr_p, uint8_t len, uint8_t *data)
{
	volatile uint8_t *dst_p = (volatile uint8_t *)(*dst_addr_p);

	// Write package len to [0..3]
    *(uint32_t *)dst_p = len;
    dst_p += 4;

    // Write payload to [4..(3+len)]
    memcpy_volatile(dst_p, data, len);
    dst_p += len;

    // Set next len to 0 at [(4+len)..(7+len)]
    *(uint32_t *)dst_p = 0;

    // Write current OCM write address to global variable
    *dst_addr_p = (size_t)dst_p;

    // Todo remove
    cnt_msg_out_w++;
}

void read_package_from_ocm(volatile size_t *src_addr_p, uint8_t *len, uint8_t **data_p)
{
	volatile uint8_t *src_p = (volatile uint8_t *)(*src_addr_p);

	// Read len from [0..3]
	*len = *(uint32_t *)src_p;
	// Immediately 'delete' current message
	*(uint32_t *)src_p = 0;
	src_p += 4;

	// Is a package ready to read?
	if (*len == 0) {
		return;
	}

	// Set data_p to start of message
	*data_p = (uint8_t *)src_p;

    // Write current OCM read address to global variable
	src_p += *len;
    *src_addr_p = (size_t)src_p;

	// todo remove
	cnt_msg_out_r++;
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/


static void xcp_eth_tx(void *arg_p)
{
    int sd = * (int *) arg_p;
    int nwrote;

    xil_printf("%s() start\n", __func__);

    xQueueReset(queue_xcp_tx);

    while (1) {
        uint8_t buf_xcp_tx[BUF_SIZE_XCP_TX];
        if(xQueueReceive(queue_xcp_tx, buf_xcp_tx, portMAX_DELAY) != pdPASS) {
            xil_printf("%s(): xQueueReceive() tx failed\n", __func__);
            xil_printf("%s(): critical error, can not recover\n", __func__);
            vTaskDelay(5);
            return;
        }
        txq_msg_read++;

        // length was already written before msg was given to queue
        uint16_t len_xcp_tx;
        len_xcp_tx = ((buf_xcp_tx[0] << 0) | (buf_xcp_tx[1] << 8));


        if ((nwrote = write(sd, buf_xcp_tx, (len_xcp_tx + XCP_HEADER_LEN))) < 0) {
            xil_printf("%s(): write() failed\n", __func__);
            break;
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

    xQueueReset(queue_xcp_tx);
    xcp_eth_connected = 1;

    while (1) {
        // Will block here until new data is available
        if ((n = read(sd, buf_xcp_rx, BUF_SIZE_XCP_RX)) < 0) {
            xil_printf("ERROR: could not read from xcp master socket\n");
            break;
        }

        // No bytes means socket was closed by counterpart
        if (n <= 0) {
            xil_printf("%s(): n <= 0\n", __func__);
            break;
        }

        if (xQueueSend(queue_xcp_rx, buf_xcp_rx, 0) != pdPASS) {
            xil_printf("%s(): xQueueSend() tcp_rx failed\n", __func__);
            xil_printf("%s(): critical error!\n", __func__);
            vTaskDelay(5);
            return;
        }
    }

    xcp_eth_connected = 0;
    xQueueReset(queue_xcp_tx);

    xil_printf("%s(): delete\n", __func__);
    close(sd);
    vTaskDelete(NULL);
}

void xcp_device(void *p)
{
    xil_printf("%s() start\n", __func__);

    extern void xcp_interface_init(void);
    xcp_interface_init();

    //void dummy_task(void *p);
    //sys_thread_new("dummy_task", dummy_task, NULL, STACKSIZE_XCP, PRIO_XCP_RX);

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

    /* The eth_tx task blocks at a queue and will not notice that the xcp
     * master closed the TCP connection. This task will continue to run. */
    int flag_xcp_eth_tx_created_once = 0;
    while (1) {
        int new_sd;
        int size = sizeof(remote);

        xil_printf("%s() waiting for xcp host connection on port %d\n", __func__, XCP_ETH_PORT);
        if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
//        	uint32_t before = lwip_fcntl(new_sd, F_GETFL, 0);
//        	lwip_fcntl(new_sd, F_SETFL, O_NONBLOCK);
//        	uint32_t after = lwip_fcntl(new_sd, F_GETFL, 0);
//        	xil_printf("sock opts: before %X, after %X\n", before, after);

            xil_printf("xcp master connected from\n");
            extern void my_print_ip(ip_addr_t *ip);
            my_print_ip((ip_addr_t*) &remote.sin_addr);

            if (! flag_xcp_eth_tx_created_once) {
                flag_xcp_eth_tx_created_once = 1;
                sys_thread_new("xcp_eth_tx", xcp_eth_tx,
                    (void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_TX);
            }
            sys_thread_new("xcp_eth_rx", xcp_eth_rx,
                (void*)&new_sd, STACKSIZE_XCP, PRIO_XCP_RX);
        }
    }

    xil_printf("%s(): delete\n", __func__);
    vTaskDelete(NULL);
}

void xcp_events_10kHz(void)
{
	// 'Delete' messages in exchange memory
	*(volatile uint32_t *)XCP_OUT_ADDR = 0;
	addr_out_w = XCP_OUT_ADDR;

    xcp_timestamp += 1; // = uz_SystemTime_GetUptimeInUs();

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
    }

    static uint32_t cnt_div_10000 = 3;
    cnt_div_10000++;
    if (cnt_div_10000 >= 10000) {
        cnt_div_10000 = 0;
        XcpEvent(XCP_EVENT_1S);
    }

}


void read_OCM_write_queue(void)
{
	addr_out_r = XCP_OUT_ADDR;

	while (1) {
		if (xcp_eth_connected == 0) {
			break;
		}

		uint8_t *data;
		uint8_t len;
		read_package_from_ocm(&addr_out_r, &len, &data);

		// Is a message present in the OCM?
		if (len == 0) {
			break;
		}
		BaseType_t* const taskWoken_p = 0;
		if(xQueueSendFromISR(queue_xcp_tx, data, taskWoken_p) != pdPASS) {
			xil_printf("%s(): xQueueSend() failed\n", __func__);
			xil_printf("%s(): critical error!\n", __func__);
			vTaskDelay(5);
			return;
		}
		txq_msg_written++;
	}
}

typedef struct {
	struct {
		uint8_t saw_90B[90];
		uint32_t ticks_run;
		uint8_t saw;
	} meas;
	struct {
		uint8_t enable;
	} stim;
} xcp_data_t;
static xcp_data_t xcp_data = {0};

void xcp_stim(void)
{
	// This irq can occur before the queue is created (xcp main task)
	if (queue_xcp_rx != NULL) {
		static uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
		if(xQueueReceiveFromISR(queue_xcp_rx, buf_xcp_rx, NULL) == pdPASS) {
			XcpCommand((uint32_t *) (buf_xcp_rx + XCP_HEADER_LEN));
		}
	}

#if 0
	addr_in_r = XCP_IN_ADDR;
	uint8_t *data;
	uint8_t len;
	read_package_from_ocm(&addr_in_r, &len, &data);
	if (len) {
		XcpCommand((uint32_t *)(data + XCP_HEADER_LEN));
	}
#endif
}

void dummy_task(void *p)
{
//	static int div_cnt = 0;
//	if (div_cnt++ < 100) {
//		return;
//	}
//	div_cnt = 0;

	static int init_once = 1;
	if (init_once) {
		init_once = 0;
		for (int i = 0; i < sizeof(xcp_data.meas.saw_90B); i++) {
			xcp_data.meas.saw_90B[i] = i;
		}
	}

	if (xcp_data.stim.enable) {
		xcp_data.meas.saw += 1;
		for (int i = 0; i < sizeof(xcp_data.meas.saw_90B); i++) {
			xcp_data.meas.saw_90B[i] += 1;
		}
	}

	xcp_events_10kHz();
	xcp_stim();

#if 0
	while (1) {
		// This task runs once before it is delayed by 1 FreeRTOS tick which is 10 ms
		// --> This task runs with 100 Hz
		for (int i = 0; i < 100; i++) {
			xcp_data.meas.ticks_run += 1;

			if (xcp_data.stim.enable) {
				xcp_data.meas.saw += 1;
				for (int i = 0; i < sizeof(xcp_data.meas.saw_90B); i++) {
					xcp_data.meas.saw_90B[i] += 1;
				}
			}

			xcp_events_10kHz();

			// This irq can occur before the queue is created (xcp main task)
			if (queue_xcp_rx != NULL) {
				static uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
				if(xQueueReceiveFromISR(queue_xcp_rx, buf_xcp_rx, NULL) == pdPASS) {
					XcpCommand((uint32_t *) (buf_xcp_rx + XCP_HEADER_LEN));
				}
			}
		}


        vTaskDelay(1);
	}
#endif
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
    uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;
    static uint16_t xcp_package_counter = 0;

    msg_with_header_p[0] = (uint8_t) (len >> 0);
    msg_with_header_p[1] = (uint8_t) (len >> 8);
    msg_with_header_p[2] = (uint8_t) (xcp_package_counter >> 0);
    msg_with_header_p[3] = (uint8_t) (xcp_package_counter >> 8);
    xcp_package_counter++;

    write_package_to_ocm(&addr_out_w, len + 4, msg_with_header_p);

//    BaseType_t * const pxHigherPriorityTaskWoken_ = 0;
//    if(xQueueSendFromISR(queue_xcp_tx,
//                         msg_with_header_p,
//                         pxHigherPriorityTaskWoken_) != pdPASS) {
//        xil_printf("%s(): xQueueSend() failed\n", __func__);
//        xil_printf("%s(): critical error!\n", __func__);
//        vTaskDelay(5);
//        return;
//    }

    // TODO necessary?
    XcpSendCallBack();
}

MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr )
{
    // Address extension is not used.
    // --> addr already holds the requested memory address
    return (MTABYTEPTR)((uint64_t)addr);
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
	return xcp_timestamp;
}


