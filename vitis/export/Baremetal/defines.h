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
#include "IP_Cores/IncreEncoder_ip_addr.h"				//Include from Simulink IP-Blocks for the incremental encoder
#include "IP_Cores/Trans_123_dq_V11_ip_addr.h"			//Include from Simulink IP-Blocks for the 123-to-dq transformation
#include "IP_Cores/ADC_Module_LVDS_v2_ip_addr.h"		//Include from hand coded IP-Blocks for ADCs


//#define UltraZohmV2

//==============================================================================================================================================================
// useful macros
#define SIGN(x) 	(((x)>=0) ? (1) : (-1)) 	// Sign of variable i
#define MAX(x, y) 	(((x) < (y)) ? (y) : (x)) // Max of x or y
#define MIN(x, y) 	(((x) > (y)) ? (y) : (x)) // Min of x or y
#define LIMIT(x,low,high) ((x)>(high)?(high):((x)<(low)?(low):(x))) // limit x to low<x<high

//==============================================================================================================================================================
#define INCR_ENCODER_BASE_ADDR			XPAR_INCREENCODER_V24_IP_0_BASEADDR
#define EncoderPI2_Inc_elek_REG   		INCR_ENCODER_BASE_ADDR + PI2_Inc_AXI4_Data_IncreEncoder_ip
#define EncoderPI2_Inc_mech_REG   		INCR_ENCODER_BASE_ADDR + Inc_PerTurn_mech_2PI_AXI4_Data_IncreEncoder_ip
#define EncoderIncsPerTurn_mech_REG  	INCR_ENCODER_BASE_ADDR + IncPerTurn_mech_AXI4_Data_IncreEncoder_ip
#define EncoderIncsPerTurn_elek_REG  	INCR_ENCODER_BASE_ADDR + IncrementePerTurn_elek_AXI4_Data_IncreEncoder_ip
#define Encoder_Time_REG  				INCR_ENCODER_BASE_ADDR + Timer_FPGA_ms_AXI4_Data_IncreEncoder_ip
#define Encoder_rps_REG  				INCR_ENCODER_BASE_ADDR + omega_AXI4_Data_IncreEncoder_ip
#define Encoder_theta_m_REG  			INCR_ENCODER_BASE_ADDR + theta_mech_AXI4_Data_IncreEncoder_ip
#define Encoder_theta_e_REG  			INCR_ENCODER_BASE_ADDR + theta_el_AXI4_Data_IncreEncoder_ip
#define Encoder_direction_REG  			INCR_ENCODER_BASE_ADDR + direction_AXI4_Data_IncreEncoder_ip
#define OverSamplingFactorInverseREG  	INCR_ENCODER_BASE_ADDR + OverSamplFactorInv_AXI4_Data_IncreEncoder_ip
#define OverSamplingFactorREG 			INCR_ENCODER_BASE_ADDR + OverSamplFactor_AXI4_Data_IncreEncoder_ip

//==============================================================================================================================================================
//IP-Block for the DMA-interface of the ADC
//	#define DMA_Data_ADC_REG   				XPAR_AXI_DMA_BASEADDR

//==============================================================================================================================================================
//IP-Block for the DMA-interface of the Control
//	#define DMA_Data_CONTROL_REG   			XPAR_AXI_DMA1_BASEADDR

//==============================================================================================================================================================
//IP-Block for the ADC-Counter
//	#define ADCCounter_EndValue_REG			XPAR_ADC_COUNTER_V4_0_BASEADDR + CounterValue_AXI4_Data_ADC_Counter_V4

//==============================================================================================================================================================
//IP-Block for the 123-dq-Transformation
#define Trans_123_dq_theta_offset_REG 	XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + theta_offset_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_idCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + id_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_iqCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + iq_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_i1Current_REG		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i1_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_i3Current_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i3_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset


//==============================================================================================================================================================
//IP-Block for the Interrupt Prescaler of the control-timer Period = ( 2^32-1 � Reset Value + 2) * Axi-Clk Period
//F�r Timing Umso n�her der Wert an an 0xFFFFFFFF ist, desto schneller der 32-Bit Counter ( 0xFFFFFD28 = 10us bei 100MHz Prozessortakt)
//It is a 32-Bit Counter -> 2^32 = 0xFFFFFFFF, where in our case the counter is set to count down. AXI-Clock is 100MHz (=10 ns)
//Theory: 100us/10ns = 10000(dec) = 2710(hex) -> 0xFFFFFFFF - 0x2710 = 0xFFFFD8EF
//Reality: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
#define Con_TIMER_DEVICE_ID				XPAR_TRIGGER_F_CC_DEVICE_ID //XPAR_TMRCTR_1_DEVICE_ID
//	#define INTC_Con_TIMER_INTERRUPT_ID 	XPAR_FABRIC_CONTROL_TIMER_INTERRUPT_INTR //SW: The Interrupt number of Bitstream generation was different (Wrong) in the xparameters avter Vvado version 2017, therefore i write directly down the used interrupt number (here 31)
#define INTC_Con_TIMER_INTERRUPT_ID 	123U //XPAR_FABRIC_TRIGGER_F_CC_INTERRUPT_INTR 			//SW: The "Core0_nIRQ" Interrupt has the number "31" in Vivado inside of "ZQNQ7 Processing System"
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
//Interrupt from end of DMA-transfer from the ADC
//	#define INTC_ADC_TRANS_INTERRUPT_ID 	XPAR_FABRIC_AXI_DMA_S2MM_INTROUT_INTR

//Defines for the Interrupt
#define Interrupt_INT 					XGPIO_IR_CH1_MASK
//#define INTC_GPIO_INTERRUPT_ID 		XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR /*Definitions for Fabric interrupts connected to ps7_scugic_0 */


// Parameter definitions
#define INTERRUPT_ID_SCUG 				XPAR_SCUGIC_0_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
#define INTERRUPT_ID_IPI 				XPAR_XIPIPSU_0_DEVICE_ID		/* IPI device that Interrupt is connected to */
#define GPIO_out_ID						XPAR_AXI_GPIO_2_DEVICE_ID 		/* GPIO device that GPIO is connected to output*/
#define ADC_ID							XPAR_PS7_XADC_0_DEVICE_ID		/* Device that ADC is connected to*/


//==============================================================================================================================================================
//Defines for ADC
#define SYSMON_DEVICE_ID 					XPAR_SYSMON_0_DEVICE_ID

#define XAdcPs_RawToVoltage2(AdcData) 					\
		((((float)(AdcData))* (1.0f))/65536.0f)
//2^16 (because of 16 Bit resolution) -> 65536.0f
//Auslegung f�r Spannungsteiler auf Adapterplatine am XADC des Zynqs mit 3 Windungen
#define XAdcPs_RawToCurrent_6A(AdcData)				\
		((float)(AdcData)*0.000229673f ) //Faktor 16 Bit vergleiche Excel: "Auslegung Stromsensoren LEM"
#define XAdcPs_VoltageToCurrent_6A(AdcData)				\
		((float)(AdcData)*15.05185185f ) //Faktor vergleiche Excel: "Auslegung Stromsensoren LEM"


#endif /* DEFINES_H_ */
