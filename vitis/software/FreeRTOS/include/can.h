/******************************************************************************
* Copyright 2021 Technische Hochschule Nürnberg
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

#ifndef CAN_H
#define CAN_H

#include "inttypes.h"
typedef struct
{
	uint16_t std_id;
	uint8_t dlc;
	uint8_t data[8];
} can_frame_t;

int hal_can_init(uint32_t can_base_address, uint32_t can_device_id);
int hal_can_send_frame_blocking(can_frame_t* can_frame_tx_p);
int hal_can_send_frame_blocking_wrapper(uint16_t std_id, uint8_t dlc, uint8_t* data);
int hal_can_receive_frame_blocking(can_frame_t *data);
int hal_can_is_tx_done(void);
int hal_can_is_rx_empty(void);

#endif