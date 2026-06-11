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
#define kXcpMaxCTO              32
#define kXcpMaxDTO              64

#define BUF_SIZE_XCP_RX         (kXcpMaxDTO + XCP_HEADER_LEN)
#define BUF_SIZE_XCP_TX         (kXcpMaxDTO + XCP_HEADER_LEN)

#define STACKSIZE_XCP           (1024 * 10)
#define PRIO_XCP_BACKGROUND     7
#define PRIO_XCP_RX             5
#define PRIO_XCP_TX             4

/* DAQ (DTO) queue: sized for bounded latency, not maximum buffering. A deep
 * queue only delays the inevitable when DAQ rate exceeds TCP drain rate, and
 * the backlog latency made CANape requests time out (observed ~4 min into a
 * measurement with the previous 10000-entry queue). 512 frames ~= 35 KB is
 * tens of milliseconds at typical drain rates. */
#define QUEUE_XCP_TX_LEN        512
#define QUEUE_XCP_RX_LEN        10

/* Dedicated queue for CTO packets (command responses RES/ERR/EV/SERV,
 * PID >= 0xFC). Responses must never wait behind the DAQ backlog and must
 * survive a DAQ purge, otherwise the master times out under DAQ load. */
#define QUEUE_XCP_TX_CTO_LEN    16

/* TX batching: collect queued frames into one buffer of roughly a TCP MSS
 * before write(), instead of one socket call per 68-byte frame. */
#define TX_BATCH_BUF_SIZE       1400

/* First payload byte after the 4-byte transport header is the XCP PID.
 * 0xFC..0xFF = CTO (SERV/EV/ERR/RES); 0x00..0xFB = DAQ DTO (ODT number). */
#define XCP_PID_CTO_MIN         0xFC

#define XCP_ETH_PORT            (uint16_t) 12340

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static QueueHandle_t queue_xcp_tx;
static QueueHandle_t queue_xcp_tx_cto = NULL;
static QueueHandle_t queue_xcp_rx = NULL;

static volatile uint8_t xcp_eth_connected = 0;

// TODO delete
static volatile uint32_t msg_txq_written = 0;
static volatile uint32_t msg_txq_read = 0;
static volatile uint32_t msg_rxq_written = 0;
static volatile uint32_t msg_rxq_read = 0;

volatile uint32_t try_to_read_ocm = 0;

// TX-queue backpressure (cf. read_OCM_write_txQueue / ocm_eth_adapter_tx).
// When the Ethernet link cannot keep up with the XCP DAQ rate the TX queue
// fills. The producer runs in ISR context, so it must never block: it drops
// the frame, counts it, and asks the TX task to purge the stale backlog so
// latency stays bounded. This replaces a former vTaskDelay()/xil_printf() call
// from ISR context that corrupted the FreeRTOS scheduler and froze the system.
static volatile uint32_t xcp_txq_overflow_dropped = 0;
static volatile int      xcp_txq_purge_requested  = 0;

// Per-connection worker lifecycle. The accept loop sets these before spawning
// the TX/RX tasks and waits for both to clear before accepting the next master,
// so the socket fd is never reused/closed while a worker still holds it and only
// one TX task ever drains queue_xcp_tx.
static volatile uint8_t xcp_tx_task_running = 0;
static volatile uint8_t xcp_rx_task_running = 0;

/*-------------------------------------------------------------------
 * Static functions
 *-----------------------------------------------------------------*/
static void my_print_ip(ip_addr_t *ip)
{
    xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
            ip4_addr3(ip), ip4_addr4(ip));
}

/* Append one length-prefixed frame to the batch buffer. Returns the new fill
 * level (unchanged if the frame's length field is corrupt). */
static uint32_t tx_batch_append(uint8_t *batch_buf, uint32_t batch_fill, const uint8_t *frame)
{
    uint16_t len_xcp_tx = (uint16_t)((frame[0] << 0) | (frame[1] << 8));
    uint32_t frame_total = (uint32_t)len_xcp_tx + XCP_HEADER_LEN;

    if (frame_total > BUF_SIZE_XCP_TX) {
        return batch_fill;  // corrupt length field; drop the frame
    }

    memcpy(&batch_buf[batch_fill], frame, frame_total);
    msg_txq_read++;
    return batch_fill + frame_total;
}

static void ocm_eth_adapter_tx(void *arg_p)
{
    int sd = (int)(intptr_t) arg_p;
    int nwrote;

    xil_printf("%s() start\n", __func__);

    xQueueReset(queue_xcp_tx);
    xQueueReset(queue_xcp_tx_cto);
    xcp_txq_purge_requested = 0;

    // Run until the connection is torn down (rx clears xcp_eth_connected) or a
    // socket write fails. The receive timeout lets the task notice a disconnect
    // even with no DAQ data queued, so it always exits and is recreated for the
    // next connection (it used to be created once per boot and never resumed).
    while (xcp_eth_connected) {
        // Backpressure: if the ISR flagged a DAQ-queue overflow, drop the
        // stale DAQ backlog rather than streaming seconds-old frames after a
        // stall. CTO responses live in their own queue and are NOT purged.
        if (xcp_txq_purge_requested) {
            xcp_txq_purge_requested = 0;
            xQueueReset(queue_xcp_tx);
        }

        // Batch as many queued frames as fit into ~one TCP MSS and send them
        // with a single write(). Each write() goes through the lwIP socket
        // layer / tcpip_thread mailbox, so one write per 68-byte frame was the
        // main throughput limiter at DAQ rates. Frames are length-prefixed on
        // the wire, so concatenating them does not change the stream format.
        uint8_t  batch_buf[TX_BATCH_BUF_SIZE];
        uint32_t batch_fill = 0;
        uint8_t  buf_xcp_tx[BUF_SIZE_XCP_TX];

        // CTO responses first: they jump any DAQ backlog so the master's
        // request never times out under DAQ load.
        while ((batch_fill + BUF_SIZE_XCP_TX) <= TX_BATCH_BUF_SIZE
               && xQueueReceive(queue_xcp_tx_cto, buf_xcp_tx, 0) == pdPASS) {
            batch_fill = tx_batch_append(batch_buf, batch_fill, buf_xcp_tx);
        }

        if (batch_fill == 0) {
            // No pending CTO: block for DAQ data. Short timeout so a CTO
            // arriving on an idle connection waits at most ~20 ms and a
            // disconnect is still detected promptly.
            if(xQueueReceive(queue_xcp_tx, buf_xcp_tx, pdMS_TO_TICKS(20)) != pdPASS) {
                continue;  // timeout: re-check connection/CTO, keep waiting
            }
            batch_fill = tx_batch_append(batch_buf, batch_fill, buf_xcp_tx);
        }

        // Top up the batch with further DAQ frames without blocking.
        while ((batch_fill + BUF_SIZE_XCP_TX) <= TX_BATCH_BUF_SIZE
               && xQueueReceive(queue_xcp_tx, buf_xcp_tx, 0) == pdPASS) {
            batch_fill = tx_batch_append(batch_buf, batch_fill, buf_xcp_tx);
        }

        if (batch_fill == 0) {
            continue;
        }

        if ((nwrote = write(sd, batch_buf, batch_fill)) < 0) {
            break;  // socket closed/error; the accept loop owns close()
        }
    }

    xil_printf("%s(): tx exit\n", __func__);
    xcp_tx_task_running = 0;
    vTaskDelete(NULL);
}

static void ocm_eth_adapter_rx(void *arg_p)
{
    int sd = (int)(intptr_t) arg_p;
    int n;

    xil_printf("%s() start\n", __func__);
    uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];

    while (1) {
        // Blocks until the master sends data or closes the connection.
        n = read(sd, buf_xcp_rx, BUF_SIZE_XCP_RX);
        if (n <= 0) {
            // n < 0 = socket error, n == 0 = orderly close by the master
            break;
        }

        if (xQueueSend(queue_xcp_rx, buf_xcp_rx, 0) != pdPASS) {
            // RX command queue full (ISR not draining fast enough): drop this
            // frame but keep the connection alive. Do NOT return here without
            // teardown -- that previously leaked the task and wedged reconnects.
        } else {
            msg_rxq_written++;
        }
    }

    // Connection teardown: signal the tx task to stop (xcp_eth_connected = 0)
    // and drop the TX backlog. The accept loop closes the socket once both
    // workers have exited, so the fd is never closed while still in use.
    xcp_eth_connected = 0;
    xQueueReset(queue_xcp_tx);

    xil_printf("%s(): rx exit\n", __func__);
    xcp_rx_task_running = 0;
    vTaskDelete(NULL);
}

static void ocm_eth_adapter_init(void)
{
    queue_xcp_tx = xQueueGenericCreate(QUEUE_XCP_TX_LEN, BUF_SIZE_XCP_TX, 0);
    queue_xcp_tx_cto = xQueueGenericCreate(QUEUE_XCP_TX_CTO_LEN, BUF_SIZE_XCP_TX, 0);
    queue_xcp_rx = xQueueGenericCreate(QUEUE_XCP_RX_LEN, BUF_SIZE_XCP_RX, 0);

    rpu_apu_exchange_init();
}

static BaseType_t read_rxQueue_write_OCM(void)
{
	BaseType_t task_woken = pdFALSE;

	// This irq can occur before the queue is created (xcp main task)
	if (queue_xcp_rx == NULL) {
		return pdFALSE;
	}

	while (1) {
		uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];

		// Peek first: if the message does not fit into the OCM region we leave
		// it queued for the next IPI cycle instead of losing it. XCP_IN is only
		// 256 bytes (~3 commands), so command bursts must be drained over
		// several cycles rather than overrunning the region.
		if(xQueuePeekFromISR(queue_xcp_rx, buf_xcp_rx) != pdPASS) {
			break;
		}

		if (! rpu_apu_exchange_writeOCM(BUF_SIZE_XCP_RX, buf_xcp_rx)) {
			break;	// OCM write region full; retry remaining commands next cycle
		}

		// Written to OCM: now actually consume the message from the queue.
		(void)xQueueReceiveFromISR(queue_xcp_rx, buf_xcp_rx, &task_woken);
		msg_rxq_read++;
	}

	return task_woken;
}

static BaseType_t read_OCM_write_txQueue(void)
{
	BaseType_t task_woken = pdFALSE;

	while (1) {
		if (xcp_eth_connected == 0) {
			break;
		}

		uint8_t *data;
		uint8_t len;
		try_to_read_ocm++;
		if (! rpu_apu_exchange_readOCM(&len, &data)) {
			// Could not read a message from OCM
			break;
		}

		// Classify by XCP PID (first payload byte after the 4-byte transport
		// header): CTO packets (command responses etc.) take the dedicated
		// queue so they never wait behind -- or get purged with -- the DAQ
		// backlog. The master times out if a response is late or lost.
		if (data[XCP_HEADER_LEN] >= XCP_PID_CTO_MIN) {
			if (xQueueSendFromISR(queue_xcp_tx_cto, data, &task_woken) == pdPASS) {
				msg_txq_written++;
			}
			// CTO queue full is practically impossible (request/response is
			// serialized); if it happens the frame is dropped silently.
			continue;
		}

		if(xQueueSendFromISR(queue_xcp_tx, data, &task_woken) != pdPASS) {
			// DAQ queue full: the Ethernet client/link cannot keep up with the
			// XCP DAQ rate. Drop this frame and ask the TX task to purge its
			// stale backlog so latency stays bounded. Must NOT block, delay or
			// printf from ISR context here -- doing so corrupts the FreeRTOS
			// scheduler and freezes the system (the previous behaviour).
			// Keep draining the OCM (continue, not break): a CTO response
			// behind the overflowing DAQ frames must still get through.
			xcp_txq_overflow_dropped++;
			xcp_txq_purge_requested = 1;
			continue;
		}
		msg_txq_written++;
	}

	return task_woken;
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
void ocm_eth_adapter_task(void *p)
{
    xil_printf("%s() start\n", __func__);

    ocm_eth_adapter_init();

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

        xil_printf("%s() waiting for xcp host connection on port %d\n", __func__, XCP_ETH_PORT);
        new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size);
        if (new_sd < 0) {
            continue;  // accept failed; retry
        }

        xil_printf("xcp master connected from\n");
        my_print_ip((ip_addr_t*) &remote.sin_addr);

        // Start a fresh TX+RX worker pair for this connection. The socket fd is
        // passed BY VALUE; the old code passed &new_sd, a dangling pointer to a
        // loop-local. Recreating the TX task every connection fixes XCP not
        // resuming after a reconnect (it was previously created only once).
        xcp_eth_connected   = 1;
        xcp_tx_task_running = 1;
        xcp_rx_task_running = 1;
        sys_thread_new("xcp_eth_tx", ocm_eth_adapter_tx,
            (void*)(intptr_t)new_sd, STACKSIZE_XCP, PRIO_XCP_TX);
        sys_thread_new("xcp_eth_rx", ocm_eth_adapter_rx,
            (void*)(intptr_t)new_sd, STACKSIZE_XCP, PRIO_XCP_RX);

        // Single XCP master at a time: wait for both workers of this connection
        // to finish, then close the fd exactly once before accepting the next.
        // This prevents fd reuse-while-held and two TX tasks draining the queue.
        while (xcp_tx_task_running || xcp_rx_task_running) {
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        close(new_sd);
    }

    xil_printf("%s(): delete\n", __func__);
    vTaskDelete(NULL);
}

int ocm_eth_adapter_irq(void)
{
	BaseType_t task_woken = pdFALSE;

	rpu_apu_exchange_cache_invalidate_before_read();
	rpu_apu_exchange_prepare_read();
	if (read_OCM_write_txQueue() != pdFALSE) {
		task_woken = pdTRUE;
	}

	rpu_apu_exchange_prepare_write();
	if (read_rxQueue_write_OCM() != pdFALSE) {
		task_woken = pdTRUE;
	}
	rpu_apu_exchange_cache_flush_after_write();

	// Nonzero asks the IPI ISR to portYIELD_FROM_ISR so the TX task runs
	// immediately instead of waiting for the next tick interrupt.
	return (task_woken != pdFALSE) ? 1 : 0;
}
