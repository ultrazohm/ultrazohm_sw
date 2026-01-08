#include "FreeRTOS.h"
#include "task.h"
//#include "shared_memory.h"
#include "../include/can_tasks.h"
#include "../include/can.h"        /* can_frame_t, hal_can_* */
#include "../defines.h"
#include "../uz/uz_HAL.h"
#include <xstatus.h>               /* XST_SUCCESS */
#include <string.h>

typedef struct {
    volatile uint32_t sequence;
    volatile uint8_t  SignalRx1;
    volatile uint8_t  SignalRx2;
    volatile uint8_t  SignalTx;
    uint8_t reserved[2];
} shared_CAN_Data_t;
//static volatile shared_CAN_Data_t * const shared_CAN_Data = (shared_CAN_Data_t *)SHARED_MEM_BASE;
static shared_CAN_Data_t shared_CAN_Data;


static void can_rx_task(void *pv)
{
    (void)pv;
    can_frame_t frame;
    for (;;) {
        /* Poll RX fifo every 1 ms (cheap and deterministic). If RX is non-empty, read frame */
        if (!hal_can_is_rx_empty()) {
            if (hal_can_receive_frame_blocking(&frame) == XST_SUCCESS) {
                if (frame.std_id == 0x123 && frame.dlc >= 1) {
                    shared_CAN_Data.SignalRx1 = frame.data[0];
                    shared_CAN_Data.sequence++;
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

static void can_task_1ms(void *pv)
{
    TickType_t last = xTaskGetTickCount();
    can_frame_t tx;
    (void)pv;
    for (;;) {
        /* Example: periodic heartbeat on 1ms (can be replaced with real data) */
        tx.std_id = 0x100;
        tx.dlc = 1;
        tx.data[0] = 0xAA;
        hal_can_send_frame_blocking(&tx);

        vTaskDelayUntil(&last, pdMS_TO_TICKS(1));
    }
}

static void can_task_10ms(void *pv)
{
    TickType_t last = xTaskGetTickCount();
    can_frame_t tx;
    can_frame_t rx;
    (void)pv;
    for (;;) {
        /* Read value written by R5 and send on CAN ID 0x45 */
        uint8_t val = shared_CAN_Data.SignalTx;
        tx.std_id = 0x45;
        tx.dlc = 1;
        tx.data[0] = val;
        hal_can_send_frame_blocking(&tx);

        /* Limit processing CAN receive messages up to 64 frames per task to avoid blocking */
        uint8_t drained = 0;
        const uint8_t max_drain = 64;
        while (!hal_can_is_rx_empty() && (drained < max_drain)) {
            if (hal_can_receive_frame_blocking(&rx) == XST_SUCCESS) {
            	/* Message 1 */
                if (rx.std_id == 0x111 && rx.dlc >= 1) {
                    shared_CAN_Data.SignalRx1 = rx.data[0];
                    shared_CAN_Data.sequence++;
                }

                /* Message 2 */
                if (rx.std_id == 0x112 && rx.dlc >= 1) {
                    shared_CAN_Data.SignalRx2 = rx.data[0];
                    shared_CAN_Data.sequence++;
                }
            } else {
                break; /* receive failed, stop trying */
            }
            drained++;
        }

        vTaskDelayUntil(&last, pdMS_TO_TICKS(10));
    }
}



static void can_task_100ms(void *pv)
{
    TickType_t last = xTaskGetTickCount();
    can_frame_t tx;
    (void)pv;
    for (;;) {
        /* Status packet containing both signals */
        tx.std_id = 0x200;
        tx.dlc = 2;
        tx.data[0] = shared_CAN_Data.SignalRx1;
        tx.data[1] = shared_CAN_Data.SignalRx2;
        hal_can_send_frame_blocking(&tx);

        vTaskDelayUntil(&last, pdMS_TO_TICKS(100));
    }
}

/* Public init: create RX + periodic tasks. Call after hal_can_init(). */
void CAN_app_init(void)
{
	BaseType_t ret;
	uz_printf("CAN_app_init: free heap before create=%u\n\r", (unsigned)xPortGetFreeHeapSize());

    /* Create RX task */
//    ret = xTaskCreate(can_rx_task, "can_rx", configMINIMAL_STACK_SIZE + 256, NULL, tskIDLE_PRIORITY + 3, NULL);
//    if (ret != pdPASS) uz_printf("xTaskCreate can_rx failed=%d free=%u\n\r", (int)ret, (unsigned)xPortGetFreeHeapSize());


    /* Create periodic tasks: priorities chosen so 1ms highest */
//    ret = xTaskCreate(can_task_1ms, "can_1ms", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 4, NULL);
//    if (ret != pdPASS) uz_printf("xTaskCreate can_1ms failed=%d free=%u\n\r", (int)ret, (unsigned)xPortGetFreeHeapSize());

    ret = xTaskCreate(can_task_10ms, "can_10ms", configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 4, NULL);
    if (ret != pdPASS) uz_printf("xTaskCreate can_10ms failed=%d free=%u\n\r", (int)ret, (unsigned)xPortGetFreeHeapSize());

    ret = xTaskCreate(can_task_100ms,"can_100ms",configMINIMAL_STACK_SIZE + 200, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (ret != pdPASS) uz_printf("xTaskCreate can_100ms failed=%d free=%u\n\r", (int)ret, (unsigned)xPortGetFreeHeapSize());

    uz_printf("CAN_app_init: end reached\n\r");
}
