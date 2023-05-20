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

#include "../bsp_timer/bsp_timer.h"

/*-------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------*/
typedef struct _timing_A53_t {
    struct {
        float isr_period_us;
        float isr_execution_time_us;
        float xcp_cache_flush_stim_us;
        float xcp_cache_flush_meas_us;
        float xcp_event_1ms_us;
        float write_to_tx_queue_us;
        float write_to_tcp_socket_us;
    } now;

    struct {
        float isr_period_us;
        float isr_execution_time_us;
        float xcp_cache_flush_stim_us;
        float xcp_cache_flush_meas_us;
        float xcp_event_1ms_us;
        float write_to_tx_queue_us;
        float write_to_tcp_socket_us;
    } max;
} timing_A53_t;

#define TIMING_START() \
        uint16_t _ts_start = bsp_timer_timestamp_get();

#define TIMING_CALC(_name) \
        timing_A53.now._name = bsp_timer_timestamp_get_time_delta_us( \
                _ts_start, \
                bsp_timer_timestamp_get()); \
        if (timing_A53.now._name > timing_A53.max._name) \
            timing_A53.max._name = timing_A53.now._name;

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

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
#define QUEUE_XCP_TX_LEN        1000
#define QUEUE_XCP_RX_LEN        10

static QueueHandle_t queue_xcp_tx;
static QueueHandle_t queue_xcp_rx = NULL;

static uint32_t xcp_timestamp;

timing_A53_t timing_A53 = {0};

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

static void xcp_interface_cache_flush_measure(void)
{
    TIMING_START();
    Xil_DCacheFlushRange(XCP_MEAS_R5_ADDR, XCP_MEAS_R5_LEN);
    TIMING_CALC(xcp_cache_flush_stim_us);
}

/* TODO
 * Funktion überhaupt notwendig?
 * Stim+Meas in gleichem Bereich..
 */
static void xcp_interface_cache_flush_stimulate(void)
{
    TIMING_START();
    Xil_DCacheFlushRange(XCP_MEAS_R5_ADDR, XCP_MEAS_R5_LEN);
    TIMING_CALC(xcp_cache_flush_meas_us);
}

static void xcp_interface_init(void)
{
    queue_xcp_tx = xQueueGenericCreate(QUEUE_XCP_TX_LEN, BUF_SIZE_XCP_TX, 0);
    queue_xcp_rx = xQueueGenericCreate(QUEUE_XCP_RX_LEN, BUF_SIZE_XCP_RX, 0);

    XcpInit();
    bsp_timer_init();
    bsp_timer_start();

#ifdef USE_XCP_CAN
    if (bsp_can_init() != XST_SUCCESS) {
        xil_printf("%s(): can init failed \n", __func__);
    }
#endif
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
        xret_val = xQueueReceive(queue_xcp_tx, buf_xcp_tx, XCP_CAN_QUEUE_TIMEOUT);
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

    xQueueReset(queue_xcp_tx);

    while (1) {
        uint8_t buf_xcp_tx[BUF_SIZE_XCP_TX];
        if(xQueueReceive(queue_xcp_tx, buf_xcp_tx, portMAX_DELAY) != pdPASS) {
            xil_printf("%s(): xQueueReceive() tx failed\n", __func__);
            xil_printf("%s(): critical error, can not recover\n", __func__);
            vTaskDelay(5);
            return;
        }
        // length was already written before msg was given to queue
        uint16_t len_xcp_tx;
        len_xcp_tx = ((buf_xcp_tx[0] << 0) | (buf_xcp_tx[1] << 8));

        TIMING_START();

        if ((nwrote = write(sd, buf_xcp_tx, (len_xcp_tx + XCP_HEADER_LEN))) < 0) {
            xil_printf("%s(): write() failed\n", __func__);
            break;
        }
        XcpSendCallBack();

        TIMING_CALC(write_to_tcp_socket_us);
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
            xil_printf("ERROR: could not read from xcp master socket\n");
            break;
        }

        // No bytes means socket was closed by counterpart
        if (n <= 0) {
            xil_printf("%s(): n <= 0\n", __func__);
            break;
        }

        //XcpCommand((uint32_t *) (buf_xcp_rx + XCP_HEADER_LEN));
        if (xQueueSend(queue_xcp_rx, buf_xcp_rx, 0) != pdPASS) {
            xil_printf("%s(): xQueueSend() tcp_rx failed\n", __func__);
            xil_printf("%s(): critical error!\n", __func__);
            vTaskDelay(5);
            return;
        }
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
    static uint16_t _ts_start = 0;
    TIMING_CALC(isr_period_us);
    _ts_start = bsp_timer_timestamp_get();

    xcp_interface_cache_flush_measure();

    xcp_timestamp = *(uint32_t *)XCP_TIMESTAMP_R5_ADDR;

    XcpEvent(XCP_EVENT_FAST);

    static uint32_t cnt_div_10 = 0;
    cnt_div_10++;
    if (cnt_div_10 >= 10) {
        cnt_div_10 = 0;

        TIMING_START();
        XcpEvent(XCP_EVENT_1MS);
        TIMING_CALC(xcp_event_1ms_us);
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

    // This irq can occur before the queue is created (xcp main task)
    if (queue_xcp_rx != NULL) {
        static uint8_t buf_xcp_rx[BUF_SIZE_XCP_RX];
        if(xQueueReceiveFromISR(queue_xcp_rx, buf_xcp_rx, NULL) == pdPASS) {
            XcpCommand((uint32_t *) (buf_xcp_rx + XCP_HEADER_LEN));
        }
    }

    TIMING_CALC(isr_execution_time_us);
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

    /* The eth_tx task blocks at a queue and will not notice that the xcp
     * master closed the TCP connection. This task will continue to run. */
    int flag_xcp_eth_tx_created_once = 0;
    while (1) {
        int new_sd;
        int size = sizeof(remote);

        xil_printf("%s() waiting for xcp master connection on port %d\n", __func__, XCP_ETH_PORT);
        if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
            xil_printf("xcp master connected from\n");
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
#endif
    xil_printf("%s(): delete\n", __func__);
    vTaskDelete(NULL);
}

void ApplXcpSend( vuint8 len, const BYTEPTR msg )
{
    TIMING_START();

    uint8_t *msg_with_header_p = (uint8_t *)msg - XCP_HEADER_LEN;
    static uint16_t xcp_package_counter = 0;

    msg_with_header_p[0] = (uint8_t) (len >> 0);
    msg_with_header_p[1] = (uint8_t) (len >> 8);
    msg_with_header_p[2] = (uint8_t) (xcp_package_counter >> 0);
    msg_with_header_p[3] = (uint8_t) (xcp_package_counter >> 8);
    xcp_package_counter++;

    BaseType_t * const pxHigherPriorityTaskWoken_ = 0;
    if(xQueueSendFromISR(queue_xcp_tx,
                         msg_with_header_p,
                         pxHigherPriorityTaskWoken_) != pdPASS) {
        xil_printf("%s(): xQueueSend() failed\n", __func__);
        xil_printf("%s(): critical error!\n", __func__);
        vTaskDelay(5);
        return;
    }

    TIMING_CALC(write_to_tx_queue_us);
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
    return (XcpDaqTimestampType) xcp_timestamp;
}


// Todo remove
void timer_irq_callback__(void)
{
    static uint32_t div_cnt = 0;
    div_cnt++;
    // f = 10 kHz
    if (div_cnt >= (3 * 10000)) {
        div_cnt = 0;

//        static uint8_t cnt = 0;
//        cnt++;
//        xil_printf("%s(): %d\n", __func__, cnt);

        // Reset max times each few seconds
        memset(&timing_A53.max, 0x00, sizeof(timing_A53.max));
    }
}
