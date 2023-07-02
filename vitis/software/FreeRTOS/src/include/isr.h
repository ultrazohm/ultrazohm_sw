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

#include "../uz/uz_global_configuration.h"

//Defines for the Interrupt fixed by hand from Vivado Block Design.
//signals are concatenated in this order forming an 8 bit interrupt vector.
// Shared Peripheral Interrupts: PL->PS
#define Interrupt_2L_max_min		XPS_FPGA0_INT_ID
#define Interrupt_2L_min			XPS_FPGA1_INT_ID
#define Interrupt_2L_max			XPS_FPGA2_INT_ID
#define Interrupt_3L_start_center	XPS_FPGA3_INT_ID
#define Interrupt_3L_start			XPS_FPGA4_INT_ID
#define Interrupt_3L_center			XPS_FPGA5_INT_ID
#define Interrupt_timer_fcc			XPAR_FABRIC_INTERRUPT_TRIGGER_F_CC_INTERRUPT_INTR

#if INTERRUPT_ISR_SOURCE_USER_CHOICE == 0
	#define Interrupt_ISR_ID			Interrupt_2L_max_min
	#define Interrupt_ISR_freq_factor	2
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 1
	#define Interrupt_ISR_ID			Interrupt_2L_min
	#define Interrupt_ISR_freq_factor	1
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 2
	#define Interrupt_ISR_ID			Interrupt_2L_max
	#define Interrupt_ISR_freq_factor	1
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 3
	#define Interrupt_ISR_ID			Interrupt_3L_start_center
	#define Interrupt_ISR_freq_factor 	2
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 4
	#define Interrupt_ISR_ID			Interrupt_3L_start
	#define Interrupt_ISR_freq_factor	1
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 5
	#define Interrupt_ISR_ID			Interrupt_3L_center
	#define Interrupt_ISR_freq_factor	1
#elif INTERRUPT_ISR_SOURCE_USER_CHOICE == 6
	#define Interrupt_ISR_ID			Interrupt_timer_fcc
	#define Interrupt_ISR_freq_factor	1
#else
	#warning no ISR interrupt ID defined
#endif



void Transfer_ipc_Intr_Handler(void *baseaddr_p);						// ISR von Timer-Control
u32 Rpu_IpiHandler(XIpiPsu *IpiInstPtr);
int Initialize_InterruptHandler();
int Initialize_ISR();
int Initialize_Interrupts(u16 DeviceId);		//Init Hardware for ISR
u32 Apu_GicInit(XScuGic *IntcInstPtr, u32 IntId, Xil_ExceptionHandler Handler,void *PeriphInstPtr);
u32 Apu_IpiInit(XIpiPsu *IntcInst_IPI_Ptr,u16 DeviceId);	//Init Hardware for IPI-ISR
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);			// Init InterruptHandler for ISR



#endif /* ISR_H_ */
