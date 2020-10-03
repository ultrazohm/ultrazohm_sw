/******************************************************************************
*
* defines.h
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
* Description: Zynq UltraScale+
*
******************************************************************************/

#ifndef DEFINES_H_
#define DEFINES_H_

#include "xparameters.h"

//Includes from Simulink
#include "IP_Cores/IncreEncoder_V24_ip_addr.h"			//Include from Simulink IP-Blocks for the incremental encoder
#include "IP_Cores/Trans_123_dq_V12_ip_addr.h"			//Include from Simulink IP-Blocks for the 123-to-dq transformation
#include "IP_Cores/ADC_Module_LVDS_v2_ip_addr.h"		//Include from hand coded IP-Blocks for ADCs


//#define UltraZohmV2

//==============================================================================================================================================================
// useful macros
#define SIGN(x) 	(((x)>=0) ? (1) : (-1)) 	// Sign of variable i
#define MAX(x, y) 	(((x) < (y)) ? (y) : (x)) // Max of x or y
#define MIN(x, y) 	(((x) > (y)) ? (y) : (x)) // Min of x or y
#define LIMIT(x,low,high) ((x)>(high)?(high):((x)<(low)?(low):(x))) // limit x to low<x<high

//==============================================================================================================================================================
//IP-Block for the 123-dq-Transformation
#define Trans_123_dq_theta_offset_REG 	XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + theta_offset_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_idCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + id_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_iqCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + iq_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_i1Current_REG		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i1_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_i3Current_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i3_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset

//==============================================================================================================================================================
//IP-Block for the Interrupt Prescaler of the control-timer Period = ( 2^32-1 � Reset Value + 2) * Axi-Clk Period
//F�r Timing Umso n�her der Wert an an 0xFFFFFFFF ist, desto schneller der 32-Bit Counter ( 0xFFFFFD28 = 10us bei 100MHz Prozessortakt)
//It is a 32-Bit Counter -> 2^32 = 0xFFFFFFFF, where in our case the counter is set to count down. AXI-Clock is 100MHz (=10 ns)
//Theory: 100us/10ns = 10000(dec) = 2710(hex) -> 0xFFFFFFFF - 0x2710 = 0xFFFFD8EF
//Reality: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
#define Con_TIMER_DEVICE_ID				XPAR_INTERRUPT_TRIGGER_F_CC_DEVICE_ID //XPAR_TMRCTR_1_DEVICE_ID
//	#define INTC_Con_TIMER_INTERRUPT_ID 	XPAR_FABRIC_CONTROL_TIMER_INTERRUPT_INTR //SW: The Interrupt number of Bitstream generation was different (Wrong) in the xparameters avter Vvado version 2017, therefore i write directly down the used interrupt number (here 31)
#define TMR_Con_LOAD					0xFFFFD949 	// Target: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
//	#define TMR_Con_LOAD					0xFFFFFC71 	// Target: 100 kHz -> 10 us -> 10us - 0,9 us (interrupt handling) = 9,1 us -> 9,1 us/10 ns = 910 (dec) -> 0x38E -> 0xFFFFFFFF - 0x38E = 0xFFFFFC71  !!!
//	#define TMR_Con_LOAD					0xFFFFFE8F 	// Target: 500 kHz -> 2 us -> 2us - 1,2 us (interrupt handling) = 0,8 us -> 0,8 us/10 ns = 80 (dec) -> 0x50 -> 0xFFFFFFFF - 0x50 = 0xFFFFFFAF  !!!
//	#define TMR_Con_LOAD					0xFFFFF828 	//bei 100 MHz Takt ergibt sich 50kHz
//#define TMR_Con_LOAD					0xFFFFFFE3 	//(Default: 0xFD050F7F = 0,5 sec) (0xFFFF0F7F) bei 50MHz Takt

//with a clock frequency of 100 MHz for the timer -> t_count = 10ns
//counter value = 0xFFFFFFFF - Endvalue -> z.B. 0xFFFFFFFF - 0xFFFFFD28 = 0x2D7 = 727 (dec) -> 727 * 10ns = 7,27 us -> because of interrupt handling + 1,2 us -> every 8,47 us occurs an interrupt

#define INTC_IPC_Shared_INTERRUPT_ID 	66U //0x43 = 67(dec) see page 313 of ug1085

//==============================================================================================================================================================
//IP-Block for the Interrupt of end of ADC-conversion
#define INTC_ADC_Conv_INTERRUPT_ID 		XPAR_FABRIC_XADC_WIZ_0_EOC_OUT_INTR

//==============================================================================================================================================================
//Defines for the Interrupt
#define Interrupt_INT 					XGPIO_IR_CH1_MASK

// Parameter definitions
#define INTERRUPT_ID_SCUG 				XPAR_SCUGIC_0_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
#define INTERRUPT_ID_IPI 				XPAR_XIPIPSU_0_DEVICE_ID		/* IPI device that Interrupt is connected to */
#define GPIO_out_ID						XPAR_AXI_GPIO_2_DEVICE_ID 		/* GPIO device that GPIO is connected to output*/


//==============================================================================================================================================================
//Defines for ADC
#define XAdcPs_RawToVoltage2(AdcData) \
		((((float)(AdcData))* (1.0f))/65536.0f)
//2^16 (because of 16 Bit resolution) -> 65536.0f

#endif /* DEFINES_H_ */
