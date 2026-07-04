/*----------------------------------------------------------------------------
| xcp_gateway_a53.c
|   Option Z — A53 (FreeRTOS/lwIP) Ethernet gateway for the R5 XCPlite engine.
|   The A53 is a dumb pipe: it ferries XCP-on-UDP datagrams between CANape and
|   the OCM FIFO; the XCP slave logic lives on the R5 (arbitrary addressing).
|
|   Data path (mirrors uz_sw_xcp_hedrive_andi OCM_eth_adapter, but UDP):
|     CANape --UDP--> rx_task --queue--> IPI ISR --> XCP_IN  --> R5 XcpCommand
|     R5 XcpEvent/CRM --> XCP_OUT --> IPI ISR --queue--> tx_task --UDP--> CANape
|
|   Critical rule (hedrive F1): the IPI ISR touches ONLY OCM + FreeRTOS queues
|   (…FromISR). Sockets are used ONLY in the tasks — never in ISR context.
|   The R5 triggers the IPI once per control cycle, after xcp_r5_poll().
|
|   Copyright 2024 Eyke Liegmann, Apache-2.0.
 ----------------------------------------------------------------------------*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"   /* sys_thread_new */
#include "ocm_xcp_fifo.h"
#include <string.h>
#include <stdint.h>

#ifndef XCP_GATEWAY_UDP_PORT
#define XCP_GATEWAY_UDP_PORT 5556
#endif
#define XCP_GW_FRAME_MAX     256             /* FIFO frames are uint8_t-len capped */
#define XCP_GW_QUEUE_DEPTH   64

/* One XCP-on-Ethernet TL frame in transit between a task and the IPI ISR. */
typedef struct {
    uint16_t len;
    uint8_t  data[XCP_GW_FRAME_MAX];
} xcp_gw_frame_t;

static QueueHandle_t gRxQueue = NULL;        /* CANape -> R5 (commands)         */
static QueueHandle_t gTxQueue = NULL;        /* R5 -> CANape (responses + DAQ)  */
static int           gSock    = -1;

/* The IPI ISR is registered by initialize_ipi_runtime() long before this
 * gateway is initialised (network-up/DHCP), while the R5 fires an IPI every
 * control cycle from boot. Guard the ISR path until init completed, otherwise
 * xQueueSendToBackFromISR(NULL, ...) asserts inside the ISR. */
static volatile int   gGwReady = 0;

static struct sockaddr_in gMaster;           /* last master (CANape) endpoint   */
static volatile int       gMasterValid = 0;

/*--------------------------------------------------------------------------
 * IPI ISR hook — call from APU_IPI_ISR under the Option Z gateway mode.
 * Runs in ISR context: OCM + queue (FromISR) only, no sockets.
 *   1. read XCP_OUT (responses/DAQ from the R5) -> tx queue
 *   2. drain rx queue (commands from CANape)    -> XCP_IN
 *------------------------------------------------------------------------*/
void xcp_gateway_a53_on_ipi(BaseType_t *pxHigherPriorityTaskWoken) {
    xcp_gw_frame_t f;

    if (!gGwReady) {
        return; /* pre-init IPI (R5 boots first); isr.c still clears the status */
    }

    /* R5 -> A53: read every framed message currently in XCP_OUT. */
    ocm_xcp_fifo_cache_invalidate_before_read();
    ocm_xcp_fifo_prepare_read();
    uint8_t len;
    uint8_t *data;
    while (ocm_xcp_fifo_read(&len, &data)) {
        if (len <= XCP_GW_FRAME_MAX) {
            f.len = len;
            memcpy(f.data, data, len);
            (void)xQueueSendToBackFromISR(gTxQueue, &f, pxHigherPriorityTaskWoken);
        }
    }

    /* A53 -> R5: move queued commands into XCP_IN for the R5's next poll. */
    ocm_xcp_fifo_prepare_write();
    while (xQueueReceiveFromISR(gRxQueue, &f, pxHigherPriorityTaskWoken) == pdTRUE) {
        (void)ocm_xcp_fifo_write((uint8_t)f.len, f.data);
    }
    ocm_xcp_fifo_cache_flush_after_write();
}

/*--------------------------------------------------------------------------
 * RX task: receive XCP-on-UDP datagrams from CANape, remember the master
 * endpoint, and hand the frame to the IPI ISR via gRxQueue.
 *------------------------------------------------------------------------*/
static void xcp_gw_rx_task(void *arg) {
    (void)arg;
    xcp_gw_frame_t f;
    struct sockaddr_in src;
    socklen_t slen;
    for (;;) {
        slen = sizeof(src);
        int n = lwip_recvfrom(gSock, f.data, sizeof(f.data), 0, (struct sockaddr *)&src, &slen);
        if (n <= 0 || n > 255) {
            continue; /* FIFO records are u8-length capped; oversize would alias to len 0 */
        }
        gMaster = src;       /* learn / refresh the CANape endpoint            */
        gMasterValid = 1;
        f.len = (uint16_t)n;
        (void)xQueueSendToBack(gRxQueue, &f, 0); /* drop if full; master retries */
    }
}

/*--------------------------------------------------------------------------
 * TX task: send frames produced by the IPI ISR back to CANape.
 *------------------------------------------------------------------------*/
static void xcp_gw_tx_task(void *arg) {
    (void)arg;
    xcp_gw_frame_t f;
    for (;;) {
        if (xQueueReceive(gTxQueue, &f, portMAX_DELAY) != pdTRUE) {
            continue;
        }
        if (!gMasterValid) {
            continue; /* no master yet; drop (DAQ before CONNECT)              */
        }
        (void)lwip_sendto(gSock, f.data, f.len, 0,
                          (struct sockaddr *)&gMaster, sizeof(gMaster));
    }
}

/*--------------------------------------------------------------------------
 * Init: UDP socket on XCP_GATEWAY_UDP_PORT, the two queues, and the tasks.
 * Call once the lwIP interface is up (like the JavaScope/XCPlite server).
 * Returns 0 on success.
 *------------------------------------------------------------------------*/
int xcp_gateway_a53_init(uint32_t thread_stack, uint32_t thread_prio) {
    gRxQueue = xQueueCreate(XCP_GW_QUEUE_DEPTH, sizeof(xcp_gw_frame_t));
    gTxQueue = xQueueCreate(XCP_GW_QUEUE_DEPTH, sizeof(xcp_gw_frame_t));
    if (gRxQueue == NULL || gTxQueue == NULL) {
        return -1;
    }

    gSock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (gSock < 0) {
        return -2;
    }
    struct sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_port = lwip_htons(XCP_GATEWAY_UDP_PORT);
    a.sin_addr.s_addr = lwip_htonl(INADDR_ANY);
    if (lwip_bind(gSock, (struct sockaddr *)&a, sizeof(a)) < 0) {
        lwip_close(gSock);
        gSock = -1;
        return -3;
    }

    ocm_xcp_fifo_init(); /* A53 initialises XCP_OUT (the region it reads)       */

    if (sys_thread_new("xcp_gw_rx", xcp_gw_rx_task, NULL, thread_stack, thread_prio) == NULL) {
        return -4;
    }
    if (sys_thread_new("xcp_gw_tx", xcp_gw_tx_task, NULL, thread_stack, thread_prio) == NULL) {
        return -5;
    }
    gGwReady = 1; /* from here on the IPI ISR may touch the queues/FIFO */
    return 0;
}
