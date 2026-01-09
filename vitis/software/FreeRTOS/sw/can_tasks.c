#include "FreeRTOS.h"
#include "task.h"
//#include "shared_memory.h"
#include "../include/can_tasks.h"
#include "../include/can.h"        /* can_frame_t, hal_can_* */
#include "../defines.h"
#include "../uz/uz_HAL.h"
#include "../include/isr.h"
#include "APU_RPU_shared.h"
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
uint8_t msgStateActual_cnt=0;

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
    	/* ============================== */
        /* Send Message MCU4_ActualValues */
    	// prepare data according to specification in DBC file
    	int16_t s16_tmp_TorqueActual = (int16_t)(data_R2A_localAPU.Torque_Actual*25.0f);
    	uint16_t u16_tmp_SpeedActual = (uint16_t)(data_R2A_localAPU.Speed_Actual*4.0f);
    	uint16_t u16_tmp_Voltage_DC_Link = (uint16_t)(data_R2A_localAPU.Voltage_DC_Link*50.0f);

    	// load data to CAN frame
        tx.std_id = 0x331;
        tx.dlc = 8;
        tx.data[0] = (uint8_t)(s16_tmp_TorqueActual);		// low byte
        tx.data[1] = (uint8_t)(s16_tmp_TorqueActual>>8);	// high byte
        tx.data[2] = (uint8_t)(u16_tmp_SpeedActual);		// low byte
        tx.data[3] = (uint8_t)(u16_tmp_SpeedActual>>8);		// high byte
        tx.data[4] = (uint8_t)(u16_tmp_Voltage_DC_Link);	// low byte
        tx.data[5] = (uint8_t)(u16_tmp_Voltage_DC_Link>>8);	// high byte
        tx.data[6] = 0;
        tx.data[7] = 0;
        hal_can_send_frame_blocking(&tx);


    	/* ================================ */
        /* Send Message MCU11_Diag_Failures */
        // prepare data
        uint32_t u32_tmp_Diag_GateDriver_Status = data_R2A_localAPU.Diag_GateDriver_Status;
        uint32_t u32_tmp_Diag_Limits_Status     = data_R2A_localAPU.Diag_Limits_Status;

    	// load data to CAN frame
        tx.std_id = 0x335;
        tx.dlc = 8;
        tx.data[0] = (uint8_t)(u32_tmp_Diag_GateDriver_Status);		// low byte
        tx.data[1] = (uint8_t)(u32_tmp_Diag_GateDriver_Status>>8);	// ...
        tx.data[2] = (uint8_t)(u32_tmp_Diag_GateDriver_Status>>16);	// ...
        tx.data[3] = (uint8_t)(u32_tmp_Diag_GateDriver_Status>>24);	// high byte
        tx.data[4] = (uint8_t)(u32_tmp_Diag_Limits_Status);			// low byte
        tx.data[5] = (uint8_t)(u32_tmp_Diag_Limits_Status>>8);		// ...
        tx.data[6] = (uint8_t)(u32_tmp_Diag_Limits_Status>>16);		// ...
        tx.data[7] = (uint8_t)(u32_tmp_Diag_Limits_Status>>24);		// high byte
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
    	/* ============================= */
        /* Send Message MCU6_StateActual */
    	// load data to CAN frame
        tx.std_id = 0x333;
        tx.dlc = 8;
        tx.data[0] = (++msgStateActual_cnt & 0x0F);		// 4-Bit Counter
        tx.data[1] = data_R2A_localAPU.SysState_Actual;
        tx.data[2] = data_R2A_localAPU.SysState_Requested;
        tx.data[3] = data_R2A_localAPU.SysState_Ack;
        tx.data[4] = 0;
        tx.data[5] = 0;
        tx.data[6] = 0;
        tx.data[7] = 0;
        hal_can_send_frame_blocking(&tx);


    	/* ======================================= */
        /* Send Message MCU5_Temperatures_Inverter */
    	// load data to CAN frame
        tx.std_id = 0x533;
        tx.dlc = 8;
        tx.data[0] = data_R2A_localAPU.Temp_Inv_Phase_1;
        tx.data[1] = data_R2A_localAPU.Temp_Inv_Phase_2;
        tx.data[2] = data_R2A_localAPU.Temp_Inv_Phase_3;
        tx.data[3] = data_R2A_localAPU.Temp_Inv_Phase_4;
        tx.data[4] = data_R2A_localAPU.Temp_Inv_Phase_5;
        tx.data[5] = data_R2A_localAPU.Temp_Inv_Phase_6;
        tx.data[6] = 0;
        tx.data[7] = 0;
        hal_can_send_frame_blocking(&tx);


    	/* ==================================== */
        /* Send Message MCU7_Temperatures_Motor */
    	// load data to CAN frame
        tx.std_id = 0x534;
        tx.dlc = 8;
        tx.data[0] = data_R2A_localAPU.Temp_Mot_Phase_1;
        tx.data[1] = data_R2A_localAPU.Temp_Mot_Phase_2;
        tx.data[2] = data_R2A_localAPU.Temp_Mot_Phase_3;
        tx.data[3] = data_R2A_localAPU.Temp_Mot_Phase_4;
        tx.data[4] = data_R2A_localAPU.Temp_Mot_Phase_5;
        tx.data[5] = data_R2A_localAPU.Temp_Mot_Phase_6;
        tx.data[6] = 0;
        tx.data[7] = 0;
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
