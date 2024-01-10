/*
 * Copyright (c) 2023 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 *
 * Interface between XCP data from OCM and Ethernet
 */

#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "netif/xadapter.h"
#include "lwip/sockets.h"
#include "queue.h"
#include "xil_printf.h"
#include "xil_cache.h"

#include "RPU_APU_exchange.h"

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
// Copied from XCP implementation on R5
#define XCP_HEADER_LEN          4
#define kXcpMaxCTO              100
#define kXcpMaxDTO              100

#define BUF_SIZE_XCP_RX         (kXcpMaxCTO + XCP_HEADER_LEN)
#define BUF_SIZE_XCP_TX         (kXcpMaxCTO + XCP_HEADER_LEN)

#define STACKSIZE_XCP           (1024 * 10)
#define PRIO_XCP_BACKGROUND     7
#define PRIO_XCP_RX             5
#define PRIO_XCP_TX             4

#define QUEUE_XCP_TX_LEN        1000
#define QUEUE_XCP_RX_LEN        10

#define XCP_ETH_PORT            (uint16_t) 12340

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static QueueHandle_t queue_xcp_tx;
static QueueHandle_t queue_xcp_rx = NULL;

static volatile uint8_t xcp_eth_connected = 0;

static volatile uint32_t txq_msg_written = 0;
static volatile uint32_t txq_msg_read = 0;

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/
static void my_print_ip(ip_addr_t *ip)
{
    xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
            ip4_addr3(ip), ip4_addr4(ip));
}

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

static void xcp_interface_init(void)
{
    queue_xcp_tx = xQueueGenericCreate(QUEUE_XCP_TX_LEN, BUF_SIZE_XCP_TX, 0);
    queue_xcp_rx = xQueueGenericCreate(QUEUE_XCP_RX_LEN, BUF_SIZE_XCP_RX, 0);

    rpu_apu_exchange_init();
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
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

void read_rxQueue_write_OCM(void)
{
	// This irq can occur before the queue is created (xcp main task)
	if (queue_xcp_rx == NULL) {
		return;
	}

	rpu_apu_exchange_reset(rapu_exchange_write_apu);
	while (1) {
		uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];

		// Abort receive if no message could be read
		if(xQueueReceiveFromISR(queue_xcp_rx, buf_xcp_rx, NULL) != pdPASS) {
			break;
		}

		rpu_apu_exchange_writeOCM(rapu_exchange_write_apu, BUF_SIZE_XCP_RX, buf_xcp_rx);
	}
}

void read_OCM_write_txQueue(void)
{
	rpu_apu_exchange_reset(rapu_exchange_read_apu);

	while (1) {
		if (xcp_eth_connected == 0) {
			break;
		}

		uint8_t *data;
		uint8_t len;
		if (! rpu_apu_exchange_readOCM(rapu_exchange_read_apu, &len, &data)) {
			// Could not read a message from OCM
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
