/******************************************************************************
* Copyright 2021 Sebastian Wendel
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

#ifndef ISR_H_
#define ISR_H_

#include "../main.h"

#define JS_NUM_BUFFERS 2
extern u32 js_mem_address[JS_NUM_BUFFERS];
extern sys_thread_t ethTaskHandle;

void Transfer_ipc_Intr_Handler(void *baseaddr_p);						// ISR von Timer-Control
u32 Rpu_IpiHandler(XIpiPsu *IpiInstPtr);
int Initialize_InterruptHandler();
int Initialize_ISR();
int Initialize_Interrupts(u16 DeviceId);		//Init Hardware for ISR
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler,void *PeriphInstPtr);
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId);	//Init Hardware for IPI-ISR
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);			// Init InterruptHandler for ISR
void Send_Command_to_RPU(u32 *msgBuf, u8 msgLength);



#endif /* ISR_H_ */
