/******************************************************************************
 *
 * isr.h
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 21.08.2016
 *      Author: Sebastian Wendel (SW)
 *
******************************************************************************/

#ifndef ISR_H_
#define ISR_H_

#include "../main.h"

//Variables for ISR-time measurement
Xuint32 time_ISR_total, time_ISR_start, time_ISR_end;

//static int Initialize_Interrupts(u16 DeviceId, XTmrCtr *Tmr_Control_InstancePtr);		//Init Hardware for ISR
//static int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);				// Init InterruptHandler for ISR
//static void Conv_ADC_Intr_Handler(void *baseaddr_p);						// ISR after ADC conversion
//static void TMR_Con_Intr_Handler(void *baseaddr_p);						// ISR von Timer-Control
void TMR_Con_Intr_Handler(void *baseaddr_p);								// ISR von Timer-Control
void Transfer_ipc_Intr_Handler(void *baseaddr_p);							// ISR von Timer-Control


int MeasureTime(void);														// Function for time measurement
int Initialize_Timer(void);													// Init Timer for ISRs
int Initialize_Trigger_ADC_Conversion (void);								// Init Timer for current control
int Initialize_FPGAController(DS_Data* data);								// Init FPGA Control algorithm
int Initialize_ARMController(DS_Data* data);								// Init ARM Control algorithm
int Initialize_ISR(void);
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Tmr_Control_InstancePtr);	//Init Hardware for ISR
u32 Rpu_IpiInit(u16 DeviceId);	//Init Hardware for IPI-ISR



#endif /* ISR_H_ */
