/******************************************************************************
*
* defines.h
*
* Copyright (C) 2018 Institute ELSYS, TH Nürnberg,   All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
******************************************************************************/

#ifndef DEFINES_H_
#define DEFINES_H_

#include "xparameters.h"

//==============================================================================================================================================================
//IP-Block for the Interrupt Prescaler of the control-timer Period = ( 2^32-1 – Reset Value + 2) * Axi-Clk Period
//Für Timing Umso näher der Wert an an 0xFFFFFFFF ist, desto schneller der 32-Bit Counter ( 0xFFFFFD28 = 10us bei 100MHz Prozessortakt)
//It is a 32-Bit Counter -> 2^32 = 0xFFFFFFFF, where in our case the counter is set to count down. AXI-Clock is 100MHz (=10 ns)
//Theory: 100us/10ns = 10000(dec) = 2710(hex) -> 0xFFFFFFFF - 0x2710 = 0xFFFFD8EF
//Reality: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
	#define Con_TIMER_DEVICE_ID				XPAR_TRIGGER_F_CC_DEVICE_ID //XPAR_TMRCTR_1_DEVICE_ID
//	#define INTC_Con_TIMER_INTERRUPT_ID 	XPAR_FABRIC_CONTROL_TIMER_INTERRUPT_INTR //SW: The Interrupt number of Bitstream generation was different (Wrong) in the xparameters avter Vvado version 2017, therefore i write directly down the used interrupt number (here 31)
//	#define INTC_Con_TIMER_INTERRUPT_ID 	31 			//SW: The "Core0_nIRQ" Interrupt has the number "31" in Vivado inside of "ZQNQ7 Processing System"
	#define TMR_Con_LOAD					0xFFFFD949 	// Target: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
//	#define TMR_Con_LOAD					0xFFFFFC71 	// Target: 100 kHz -> 10 us -> 10us - 0,9 us (interrupt handling) = 9,1 us -> 9,1 us/10 ns = 910 (dec) -> 0x38E -> 0xFFFFFFFF - 0x38E = 0xFFFFFC71  !!!
//	#define TMR_Con_LOAD					0xFFFFFE8F 	// Target: 500 kHz -> 2 us -> 2us - 1,2 us (interrupt handling) = 0,8 us -> 0,8 us/10 ns = 80 (dec) -> 0x50 -> 0xFFFFFFFF - 0x50 = 0xFFFFFFAF  !!!
//	#define TMR_Con_LOAD					0xFFFFF828 	//bei 100 MHz Takt ergibt sich 50kHz
	//#define TMR_Con_LOAD					0xFFFFFFE3 	//(Default: 0xFD050F7F = 0,5 sec) (0xFFFF0F7F) bei 50MHz Takt
//with a clock frequency of 100 MHz for the timer -> t_count = 10ns
//counter value = 0xFFFFFFFF - Endvalue -> z.B. 0xFFFFFFFF - 0xFFFFFD28 = 0x2D7 = 727 (dec) -> 727 * 10ns = 7,27 us -> because of interrupt handling + 1,2 us -> every 8,47 us occurs an interrupt
//	#define INTC_IPC_Shared_INTERRUPT_ID 	0x0E
//	#define INTC_IPC_Shared_INTERRUPT_ID 	66 //0x43 = 67(dec) see page 313 of ug1085

//==============================================================================================================================================================
//IP-Block for the Interrupt of end of ADC-conversion
	#define INTC_ADC_Conv_INTERRUPT_ID 		XPAR_FABRIC_XADC_WIZ_0_EOC_OUT_INTR

//==============================================================================================================================================================

//Defines for the Interrupt
	#define Interrupt_INT 					XGPIO_IR_CH1_MASK
	//#define INTC_GPIO_INTERRUPT_ID 		XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR /*Definitions for Fabric interrupts connected to ps7_scugic_0 */


// Parameter definitions
	#define INTERRUPT_ID_SCUG 					XPAR_PSU_ACPU_GIC_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
	#define INTERRUPT_ID_IPI 					XPAR_XIPIPSU_0_DEVICE_ID			/* IPI device that Interrupt is connected to */
	#define GPIO_out_ID							XPAR_AXI_GPIO_2_DEVICE_ID 			/* GPIO device that GPIO is connected to output*/
	#define ADC_ID								XPAR_PS7_XADC_0_DEVICE_ID			/* Device that ADC is connected to*/


#endif /* DEFINES_H_ */
