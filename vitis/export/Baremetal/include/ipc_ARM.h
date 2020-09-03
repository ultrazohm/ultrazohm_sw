/******************************************************************************
 *
 * ipc_ARM.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 21.08.2018
 *      Author: Sebastian Wendel (SW) & Philipp Löhdefink (PL)
 *
******************************************************************************/

#ifndef IPC_H_
#define IPC_H_

#include "../main.h"

void ipc_Control_func(Xuint16 msgId, Xint16 value, DS_Data* data);

#endif /* IPC_H_ */
