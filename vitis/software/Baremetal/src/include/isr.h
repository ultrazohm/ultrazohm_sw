/******************************************************************************
* Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel, Philipp Löhdefink
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
#include "xgpio.h"
#include <stdbool.h>
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

typedef struct uz_PMSM__6ph_t {
	float R_ph_Ohm;/**< phase resitance inductance in Ohm. Must be greater than 0.0f */
	float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
	float Lq_Henry;/**< q-axis inductance in Henry. Must be greater than 0.0f */
	float Lx_Henry;/**< x-axis inductance in Henry. Must be greater than 0.0f */
	float Ly_Henry;/**< y-axis inductance in Henry. Must be greater than 0.0f */
	float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater or equal than 0.0f */
	float polePairs; /**< number of polePairs of the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
	float J_kg_m_squared; /**< inertia of the PMSM. Must be greater than 0.0f */
	float I_max_Ampere; /**< max allowed current per phase. Must be greater than 0.0f */
} uz_PMSM_6ph_t;

typedef struct rated_val_t {
	float VR;
	float IR;
	float nR;
}rated_val_t;

typedef struct base_val_t {
	float VB;
	float IB;
	float omegaB;
	float ZB;
	float LB;
	float psiB;
}base_val_t;

typedef struct pre_calc_val_t {
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ts_times_ZB_over_Lx;
	float Ts_times_ZB_over_Ly;
	float Ld_over_LB;
	float Lq_over_LB;
	float psi_pm_over_psiB;
}pre_calc_val_t;

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

#define Control_ISR_clear_pending_interrupt_reg		(XPAR_PSU_RCPU_GIC_DIST_BASEADDR + (XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_PENDING_CLR_OFFSET, Interrupt_ISR_ID)) )

void ISR_Control(void *baseaddr_p);								// ISR von Timer-Control
void Transfer_ipc_Intr_Handler(void *baseaddr_p);							// ISR von Timer-Control

int Initialize_Timer(void);													// Init Timer for ISRs
int Initialize_FPGAController(DS_Data* data);								// Init FPGA Control algorithm
int Initialize_ARMController(DS_Data* data);								// Init ARM Control algorithm
int Initialize_ISR(void);
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Tmr_Control_InstancePtr);	//Init Hardware for ISR
u32 Rpu_IpiInit(u16 DeviceId);	//Init Hardware for IPI-ISR


#endif /* ISR_H_ */
