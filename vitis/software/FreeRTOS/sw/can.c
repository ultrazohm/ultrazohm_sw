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

uint32_t can_received[8] = {0U};

extern uz_can_t *can_instance_0;
extern uz_can_t *can_instance_1;

void CAN_Thread_CAN0(void *p)
{

    uint32_t i_LifeCheck_CAN_Thread0 = 0;
    uz_can_frame_t can_framebuffer_rx;
    uz_can_frame_t can_framebuffer_tx;

    while (1)
    {
        if (!uz_can_is_rx_empty(can_instance_0))
        {
            uz_can_receive_frame_blocking(can_instance_0, &can_framebuffer_rx);

            if (can_framebuffer_rx.std_id == 0x22)
            {
                can_received[0] = can_framebuffer_rx.data[0];
                can_received[1] = can_framebuffer_rx.data[1];
                can_received[2] = can_framebuffer_rx.data[2];
                can_received[3] = can_framebuffer_rx.data[3];
                can_received[4] = can_framebuffer_rx.data[4];
                can_received[5] = can_framebuffer_rx.data[5];
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
