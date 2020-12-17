/******************************************************************************
 *
 * ipc_ARM.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH N�rnberg, All rights reserved.
 *
 *  Created on: 21.08.2018
 *      Author: Sebastian Wendel (SW) & Philipp L�hdefink (PL)
 *
******************************************************************************/

#ifndef IPC_H_
#define IPC_H_

#include <stdint.h>
#include "../globalData.h"

void ipc_Control_func(uint16_t msgId, uint16_t value, DS_Data* data);

#endif /* IPC_H_ */
