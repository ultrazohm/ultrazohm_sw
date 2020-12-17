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

#ifndef DEFINES_H_
#define DEFINES_H_

//#define UltraZohmV2

//==============================================================================================================================================================
// useful macros
#define SIGN(x) 	(((x)>=0) ? (1) : (-1)) 	// Sign of variable i
#define MAX(x, y) 	(((x) < (y)) ? (y) : (x)) // Max of x or y
#define MIN(x, y) 	(((x) > (y)) ? (y) : (x)) // Min of x or y
#define LIMIT(x,low,high) ((x)>(high)?(high):((x)<(low)?(low):(x))) // limit x to low<x<high

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

//Frequencies in the system
#define FPGA_100MHz		100000000.0f		//Clock frequency
#define FPGA_50MHz		50000000.0f			//Clock frequency
#define FPGA_20MHz		20000000.0f			//Clock frequency
#define FPGA_10MHz		10000000.0f			//Clock frequency

//Fractional Bit defines
#define   Q32         32
#define   Q31         31
#define   Q30         30
#define   Q29         29
#define   Q28         28
#define   Q27         27
#define   Q26         26
#define   Q25         25
#define   Q24         24
#define   Q23         23
#define   Q22         22
#define   Q21         21
#define   Q20         20
#define   Q19         19
#define   Q18         18
#define   Q17         17
#define   Q16         16
#define   Q15         15
#define   Q14         14
#define   Q13         13
#define   Q12         12
#define   Q11         11
#define   Q10         10
#define   Q9          9
#define   Q8          8
#define   Q7          7
#define   Q6          6
#define   Q5          5
#define   Q4          4
#define   Q3          3
#define   Q2          2
#define   Q1          1

//Inverse fractional Bit defines
#define   Q30toF		-Q30
#define   Q29toF		-Q29
#define   Q28toF		-Q28
#define   Q27toF		-Q27
#define   Q26toF		-Q26
#define   Q25toF		-Q25
#define   Q24toF		-Q24
#define   Q23toF		-Q23
#define   Q22toF		-Q22
#define   Q21toF		-Q21
#define   Q20toF		-Q20
#define   Q19toF		-Q19
#define   Q18toF		-Q18
#define   Q17toF		-Q17
#define   Q16toF		-Q16
#define   Q15toF		-Q15
#define   Q14toF		-Q14
#define   Q13toF		-Q13
#define   Q12toF		-Q12
#define   Q11toF		-Q11
#define   Q10toF		-Q10
#define   Q09toF		-Q9
#define   Q08toF		-Q8
#define   Q07toF		-Q7
#define   Q06toF		-Q6
#define   Q05toF		-Q5
#define   Q04toF		-Q4
#define   Q03toF		-Q3
#define   Q02toF		-Q2
#define   Q01toF		-Q1

#endif /* DEFINES_H_ */
