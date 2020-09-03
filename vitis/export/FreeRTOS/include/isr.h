/******************************************************************************
*
* isr.h
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg,   All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#ifndef ISR_H_
#define ISR_H_

#include "../main.h"

void Transfer_ipc_Intr_Handler(void *baseaddr_p);						// ISR von Timer-Control
u32 Rpu_IpiHandler(XIpiPsu *IpiInstPtr);
int Initialize_InterruptHandler();
int Initialize_ISR();
int Initialize_Interrupts(u16 DeviceId);		//Init Hardware for ISR
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler,void *PeriphInstPtr);
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId);	//Init Hardware for IPI-ISR
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);			// Init InterruptHandler for ISR




#endif /* ISR_H_ */
