/******************************************************************************
 * Copyright 2021 Robert Zipprich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "APU_RPU_shared.h"

#include "../include/can.h"
#include "../uz/uz_can/uz_can.h"
#include "../shared/APU_RPU_shared.h"

static void process_can_frame(const uz_can_frame_t *can_framebuffer_rx);

uint32_t can_received_0[8] = {0U};
uint32_t can_received_1[8] = {0U};

extern uz_can_t *can_instance_0;
extern uz_can_t *can_instance_1;
uint32_t i_LifeCheck_CAN_Thread0 = 0;
uint32_t i_LifeCheck_CAN_Thread1 = 0;

void CAN_Thread_CAN0(void *p)
{


    uz_can_frame_t can_framebuffer_rx;
    uz_can_frame_t can_framebuffer_tx;

    while (1)
    {
        if (!uz_can_is_rx_empty(can_instance_0))
        {
            uz_can_receive_frame_blocking(can_instance_0, &can_framebuffer_rx);

            if (can_framebuffer_rx.std_id == 0x22)
            {
                process_can_frame(&can_framebuffer_rx);
            }
        }

        // create Lifecheck--------------------------------------------------------------------------------------------------------------------------
        i_LifeCheck_CAN_Thread0++;
        if (i_LifeCheck_CAN_Thread0 > 255)
        {
            i_LifeCheck_CAN_Thread0 = 0;
        }
        // Build Can-Message for the Lifecheck
        can_framebuffer_tx.std_id = CAN_Msg_Start;
        can_framebuffer_tx.dlc = 1;
        can_framebuffer_tx.data[0] = i_LifeCheck_CAN_Thread0;
        // Send Heartbeat of the CAN-Thread0
        uz_can_send_frame_blocking(can_instance_0, &can_framebuffer_tx);

        // Delays the Thread to decrease busload-----------------------------------------------------------------------------------------------------
        vTaskDelay(ThreadDelay_CAN_Thread0 / portTICK_RATE_MS);
    }
}

void CAN_Thread_CAN1(void *p)
{

    uz_can_frame_t can_framebuffer_rx;
    uz_can_frame_t can_framebuffer_tx;

    while (1)
    {
        if (!uz_can_is_rx_empty(can_instance_1))
        {
            uz_can_receive_frame_blocking(can_instance_1, &can_framebuffer_rx);

            if (can_framebuffer_rx.std_id == 0x22)
            {
               // process_can_frame(&can_framebuffer_rx); // only do it on CAN0 due to thread safety
            }
        }

        // create Lifecheck--------------------------------------------------------------------------------------------------------------------------
        i_LifeCheck_CAN_Thread1++;
        if (i_LifeCheck_CAN_Thread1 > 255)
        {
            i_LifeCheck_CAN_Thread1 = 0;
        }
        // Build Can-Message for the Lifecheck
        can_framebuffer_tx.std_id = CAN_Msg_Start;
        can_framebuffer_tx.dlc = 1;
        can_framebuffer_tx.data[0] = i_LifeCheck_CAN_Thread1;
        // Send Heartbeat of the CAN-Thread1
        uz_can_send_frame_blocking(can_instance_1, &can_framebuffer_tx);

        // Delays the Thread to decrease busload-----------------------------------------------------------------------------------------------------
        vTaskDelay(ThreadDelay_CAN_Thread1 / portTICK_RATE_MS);
    }
}

struct CAN_values can_values = {0};
struct CAN_values can_values_from_rpu = {0};

void process_can_frame(const uz_can_frame_t *can_framebuffer_rx)
{
    // uz_assert(can_framebuffer_rx == NULL);

    can_values.poti_p0 = ((float)can_framebuffer_rx->data[2]) / 255.0f;
    if (can_values.poti_p0 >= 0.9960937f)
    {
        can_values.poti_p0 = 1.0f;
    }
    can_values.poti_p1 = ((float)can_framebuffer_rx->data[3]) / 255.0f;
    if (can_values.poti_p1 >= 0.9960937f)
    {
        can_values.poti_p1 = 1.0f;
    }
    can_values.poti_p2 = ((float)can_framebuffer_rx->data[4]) / 255.0f;
    if (can_values.poti_p2 >= 0.9960937f)
    {
        can_values.poti_p2 = 1.0f;
    }
    can_values.poti_p3 = ((float)can_framebuffer_rx->data[5]) / 255.0f;
    if (can_values.poti_p3 >= 0.9960937f)
    {
        can_values.poti_p3 = 1.0f;
    }

    // Buttons and switches
    can_values.sw0 = (bool)((can_framebuffer_rx->data[1] & (1U << 7)) >> 7);
    can_values.sw1 = (bool)((can_framebuffer_rx->data[1] & (1U << 6)) >> 6);
    can_values.sw2 = (bool)((can_framebuffer_rx->data[1] & (1U << 5)) >> 5);
    can_values.sw3 = (bool)((can_framebuffer_rx->data[1] & (1U << 4)) >> 4);
    can_values.btn0 = (bool)((can_framebuffer_rx->data[1] & (1U << 3)) >> 3);
    can_values.btn1 = (bool)((can_framebuffer_rx->data[1] & (1U << 2)) >> 2);
    can_values.btn2 = (bool)((can_framebuffer_rx->data[1] & (1U << 1)) >> 1);
    can_values.btn3 = (bool)((can_framebuffer_rx->data[1] & (1U << 0)) >> 0);
}
