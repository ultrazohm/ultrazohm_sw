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

uint32_t can_received_0[8] = {0U};
uint32_t can_received_1[8] = {0U};

extern uz_can_t *can_instance_0;
extern uz_can_t *can_instance_1;
uint32_t i_LifeCheck_CAN_Thread0 = 0;
uint32_t i_LifeCheck_CAN_Thread1 = 0;
volatile struct hioki_pw8001_can_values_t hioki_pw8001_can_values = {0};

static void process_hioki_pw8001_frame(const uz_can_frame_t *frame)
{
	if ((frame->std_id != HIOKI_PW8001_CAN_ID) || (frame->dlc < 3U)) {
		return;
	}

	/* Commissioning mapping: copy three payload bytes without scaling. */
	hioki_pw8001_can_values.u4 = (float)frame->data[0];
	hioki_pw8001_can_values.u5 = (float)frame->data[1];
	hioki_pw8001_can_values.u6 = (float)frame->data[2];
}

void CAN_Thread_CAN0(void *p)
{
    uz_can_frame_t can_framebuffer_rx={0};

    while (1)
    {
        while (!uz_can_is_rx_empty(can_instance_0))
        {
            uz_can_receive_frame_blocking(can_instance_0, &can_framebuffer_rx);
			process_hioki_pw8001_frame(&can_framebuffer_rx);
        }

        // create Lifecheck--------------------------------------------------------------------------------------------------------------------------
        i_LifeCheck_CAN_Thread0++;
        if (i_LifeCheck_CAN_Thread0 > 255)
        {
            i_LifeCheck_CAN_Thread0 = 0;
        }
        vTaskDelay(ThreadDelay_CAN_Thread0 / portTICK_RATE_MS);
    }
}

void CAN_Thread_CAN1(void *p)
{
    uz_can_frame_t can_framebuffer_rx={0};

    while (1)
    {
        while (!uz_can_is_rx_empty(can_instance_1))
        {
            uz_can_receive_frame_blocking(can_instance_1, &can_framebuffer_rx);

            if (can_framebuffer_rx.std_id == 0x22)
            {
                can_received_1[0] = can_framebuffer_rx.data[0];
                can_received_1[1] = can_framebuffer_rx.data[1];
                can_received_1[2] = can_framebuffer_rx.data[2];
                can_received_1[3] = can_framebuffer_rx.data[3];
                can_received_1[4] = can_framebuffer_rx.data[4];
                can_received_1[5] = can_framebuffer_rx.data[5];
            }
        }

        // create Lifecheck--------------------------------------------------------------------------------------------------------------------------
        i_LifeCheck_CAN_Thread1++;
        if (i_LifeCheck_CAN_Thread1 > 255)
        {
            i_LifeCheck_CAN_Thread1 = 0;
        }
        vTaskDelay(ThreadDelay_CAN_Thread1 / portTICK_RATE_MS);
    }
}
