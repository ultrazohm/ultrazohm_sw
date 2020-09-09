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
//#include "IP_Cores/ADC_Counter_V4_addr.h"				//Include from Simulink IP-Blocks for a counter
#include "IP_Cores/PWM_and_SS_control_V3_ip_addr.h"		//Include from Simulink IP-Blocks for PWM and SS control
#include "IP_Cores/ADC_Module_LVDS_v2_ip_addr.h"		//Include from hand coded IP-Blocks for ADCs


//==============================================================================================================================================================
//IP-Block for the ADCs
//#define ADC_CORE1_BASE_ADDR					XPAR_ADCS_ADC_MODULE_LVDS_A1_B_BASEADDR
//#define ADC_ConversionFactor_1_REG			ADC_CORE1_BASE_ADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip  //write date register for Outport Conversion factor for ADC 1
//#define ADC_OffsetFactor_1_REG				ADC_CORE1_BASE_ADDR + Offset_Factor_1_ADC_Module_LVDS_V2_ip	//write date register for Outport Offset factor for ADC 1
//#define ADC_RAW_Value_1_REG					ADC_CORE1_BASE_ADDR + RAW_Value_1_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 1
//#define ADC_RAW_Value_2_REG					ADC_CORE1_BASE_ADDR + RAW_Value_2_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 2
//#define ADC_RAW_Value_3_REG					ADC_CORE1_BASE_ADDR + RAW_Value_3_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 3
//#define ADC_RAW_Value_4_REG					ADC_CORE1_BASE_ADDR + RAW_Value_4_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 4

//#define ADC_CORE2_BASE_ADDR					XPAR_ADCS_ADC_MODULE_LVDS_A1_A_BASEADDR
//#define ADC_ConversionFactor_2_REG			ADC_CORE2_BASE_ADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip  //write date register for Outport Conversion factor for ADC 1
//#define ADC_OffsetFactor_2_REG				ADC_CORE2_BASE_ADDR + Offset_Factor_1_ADC_Module_LVDS_V2_ip	//write date register for Outport Offset factor for ADC 1
//#define ADC_RAW_Value_5_REG					ADC_CORE2_BASE_ADDR + RAW_Value_1_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 5
//#define ADC_RAW_Value_6_REG					ADC_CORE2_BASE_ADDR + RAW_Value_2_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 6
//#define ADC_RAW_Value_7_REG					ADC_CORE2_BASE_ADDR + RAW_Value_3_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 7
//#define ADC_RAW_Value_8_REG					ADC_CORE2_BASE_ADDR + RAW_Value_4_ADC_Module_LVDS_V2_ip	//read data register for Inport RAW value of ADC 8

//==============================================================================================================================================================
//AXI2TCM Block
// AXI2TCM Registers
#define R5_0_BTCM_SPLIT_REG	0x20000

#define TCM_ADC_A1_REG		R5_0_BTCM_SPLIT_REG + 0x00
#define TCM_ADC_A2_REG		R5_0_BTCM_SPLIT_REG + 0x02
#define TCM_ADC_A3_REG		R5_0_BTCM_SPLIT_REG + 0x04
#define TCM_ADC_A4_REG		R5_0_BTCM_SPLIT_REG + 0x06

#define TCM_ADC_B5_REG		R5_0_BTCM_SPLIT_REG + 0x08
#define TCM_ADC_B6_REG		R5_0_BTCM_SPLIT_REG + 0x0A
#define TCM_ADC_B7_REG		R5_0_BTCM_SPLIT_REG + 0x0C
#define TCM_ADC_B8_REG		R5_0_BTCM_SPLIT_REG + 0x0E


//==============================================================================================================================================================
//IP-Block for the PWM with DutyCycle
#define PWM_BASE_ADDR					XPAR_GATES_PWM_AND_SS_CONTROL_V_0_BASEADDR
#define PWM_SS_Con_Enable_REG			PWM_BASE_ADDR + PWM_en_AXI_Data_PWM_and_SS_control_V3_ip                //data register for Inport PWM_en_AXI
#define PWM_SS_Con_Mode_REG				PWM_BASE_ADDR + Mode_AXI_Data_PWM_and_SS_control_V3_ip                  //data register for Inport Mode_AXI
#define PWM_SS_Con_Scal_f_car_REG		PWM_BASE_ADDR + Scal_f_carrier_AXI_Data_PWM_and_SS_control_V3_ip        //data register for Inport PWM_f_carrier_kHz_AXI
#define PWM_SS_Con_Scal_T_car_REG		PWM_BASE_ADDR + Scal_T_carrier_AXI_Data_PWM_and_SS_control_V3_ip        //data register for Inport PWM_T_carrier_us_AXI
#define PWM_SS_Con_min_pulse_REG		PWM_BASE_ADDR + PWM_min_pulse_width_AXI_Data_PWM_and_SS_control_V3_ip   //data register for Inport PWM_min_pulse_width_AXI
#define PWM_SS_Con_m_u1_norm_REG		PWM_BASE_ADDR + m_u1_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u1_norm_AXI
#define PWM_SS_Con_m_u2_norm_REG		PWM_BASE_ADDR + m_u2_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u2_norm_AXI
#define PWM_SS_Con_m_u3_norm_REG		PWM_BASE_ADDR + m_u3_norm_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Inport m_u3_norm_AXI
#define PWM_SS_Con_Enable_Rd_REG		PWM_BASE_ADDR + PWM_en_rd_AXI_Data_PWM_and_SS_control_V3_ip             //data register for Outport PWM_en_rd_AXI
#define PWM_SS_Con_f_car_kHz_Rd_REG		PWM_BASE_ADDR + PWM_f_carrier_kHz_rd_AXI_Data_PWM_and_SS_control_V3_ip  //data register for Outport PWM_f_carrier_kHz_rd_AXI
#define PWM_SS_Con_T_car_us_Rd_REG		PWM_BASE_ADDR + PWM_T_carrier_us_rd_AXI_Data_PWM_and_SS_control_V3_ip   //data register for Outport PWM_T_carrier_us_rd_AXI
#define PWM_SS_Con_min_pulse_Rd_REG		PWM_BASE_ADDR + PWM_min_pulse_width_rd_AXI_Data_PWM_and_SS_control_V3_ip//data register for Outport PWM_min_pulse_width_rd_AXI
#define PWM_SS_Con_Mode_Rd_REG			PWM_BASE_ADDR + Mode_rd_AXI_Data_PWM_and_SS_control_V3_ip               //data register for Outport Mode_rd_AXI
#define PWM_SS_Con_TriState_HB1_REG		PWM_BASE_ADDR + TriState_HB1_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB1_AXI
#define PWM_SS_Con_TriState_HB2_REG		PWM_BASE_ADDR + TriState_HB2_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB2_AXI
#define PWM_SS_Con_TriState_HB3_REG		PWM_BASE_ADDR + TriState_HB3_AXI_Data_PWM_and_SS_control_V3_ip          //data register for Inport TriState_HB3_AXI


//==============================================================================================================================================================
#define INCR_ENCODER_BASE_ADDR			XPAR_INCREENCODER_IP_0_BASEADDR
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
#define Trans_123_dq_theta_offset_REG 	XPAR_TRANS_123_DQ_V11_IP_1_BASEADDR + theta_offset_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_idCurrent_REG 		XPAR_TRANS_123_DQ_V11_IP_1_BASEADDR + id_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_iqCurrent_REG 		XPAR_TRANS_123_DQ_V11_IP_1_BASEADDR + iq_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_i1Current_REG		XPAR_TRANS_123_DQ_V11_IP_1_BASEADDR + i1_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset
#define Trans_123_dq_i3Current_REG 		XPAR_TRANS_123_DQ_V11_IP_1_BASEADDR + i3_AXI_Data_Trans_123_dq_V11_ip  //data register for theta_offset

/*
//==============================================================================================================================================================
//IP-Block for the ADC-Converter
//	#define ADCCon_Temp_REG 				XPAR_DUT_V6_IP_0_BASEADDR + Temp_AXI4_Data_DUT_V6_ip  //data register for port i_soll
//	#define ADCCon_VccInt_REG 				XPAR_DUT_V6_IP_0_BASEADDR + VccInt_AXI4_Data_DUT_V6_ip   //data register for port n_ist
//	#define ADCCon_i_Ph1_REG 				XPAR_DUT_V6_IP_0_BASEADDR + i_Ph1_AXI4_Data_DUT_V6_ip  //data register for port ia_ist
//	#define ADCCon_i_Ph2_REG 				XPAR_DUT_V6_IP_0_BASEADDR + i_Ph2_AXI4_Data_DUT_V6_ip  //data register for port ia_ist
//	#define ADCCon_i_Ph3_REG 				XPAR_DUT_V6_IP_0_BASEADDR + i_Ph3_AXI4_Data_DUT_V6_ip  //data register for port ia_ist
//	#define ADCCon_Vaux0_REG 				XPAR_DUT_V6_IP_0_BASEADDR + Vaux0_AXI4_Data_DUT_V6_ip //data register for port Enable
//	#define ADCCon_Vaux8_REG 				XPAR_DUT_V6_IP_0_BASEADDR + Vaux8_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
//	#define ADCCon_RAW_CURRENT_REG 			XPAR_DUT_V6_IP_0_BASEADDR + RAW_CURRENT_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
//	#define ADCCon_VpVn_REG 				XPAR_DUT_V6_IP_0_BASEADDR + V_VpVn_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
//	#define ADCCon_Vaux0_REG 				XPAR_DUT_V6_IP_0_BASEADDR + Vaux0_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
//	#define ADCCon_Vaux8_REG 				XPAR_DUT_V6_IP_0_BASEADDR + Vaux8_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
//	#define ADCCon_Offset_REG 				XPAR_DUT_V6_IP_0_BASEADDR + OFFSET_I_AXI4_Data_DUT_V6_ip    //data register for torque of load M_L
 */

//==============================================================================================================================================================
//IP-Block for the Interrupt Prescaler of the control-timer Period = ( 2^32-1 � Reset Value + 2) * Axi-Clk Period
//F�r Timing Umso n�her der Wert an an 0xFFFFFFFF ist, desto schneller der 32-Bit Counter ( 0xFFFFFD28 = 10us bei 100MHz Prozessortakt)
//It is a 32-Bit Counter -> 2^32 = 0xFFFFFFFF, where in our case the counter is set to count down. AXI-Clock is 100MHz (=10 ns)
//Theory: 100us/10ns = 10000(dec) = 2710(hex) -> 0xFFFFFFFF - 0x2710 = 0xFFFFD8EF
//Reality: 10 kHz -> 100 us -> 100us - 0,9 us (interrupt handling) = 99,1 us -> 99,1 us/10 ns = 9910(dec) -> 0x26B6 -> 0xFFFFFFFF - 0x26B6 = 0xFFFFD949  !!!
#define Con_TIMER_DEVICE_ID				XPAR_TRIGGER_F_CC_DEVICE_ID //XPAR_TMRCTR_1_DEVICE_ID
//	#define INTC_Con_TIMER_INTERRUPT_ID 	XPAR_FABRIC_CONTROL_TIMER_INTERRUPT_INTR //SW: The Interrupt number of Bitstream generation was different (Wrong) in the xparameters avter Vvado version 2017, therefore i write directly down the used interrupt number (here 31)
#define INTC_Con_TIMER_INTERRUPT_ID 	XPAR_FABRIC_TRIGGER_F_CC_INTERRUPT_INTR 			//SW: The "Core0_nIRQ" Interrupt has the number "31" in Vivado inside of "ZQNQ7 Processing System"
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
#define INTERRUPT_ID_SCUG 					XPAR_SCUGIC_0_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
#define INTERRUPT_ID_IPI 					XPAR_XIPIPSU_0_DEVICE_ID			/* IPI device that Interrupt is connected to */
#define GPIO_out_ID							XPAR_AXI_GPIO_2_DEVICE_ID 			/* GPIO device that GPIO is connected to output*/
#define ADC_ID								XPAR_PS7_XADC_0_DEVICE_ID			/* Device that ADC is connected to*/


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
