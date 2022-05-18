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

//==============================================================================================================================================================
// useful macros
#define SIGN(x) 	(((x)>=0) ? (1) : (-1)) 	// Sign of variable i
#define MAX(x, y) 	(((x) < (y)) ? (y) : (x)) // Max of x or y
#define MIN(x, y) 	(((x) > (y)) ? (y) : (x)) // Min of x or y
#define LIMIT(x,low,high) ((x)>(high)?(high):((x)<(low)?(low):(x))) // limit x to low<x<high

//==============================================================================================================================================================
// TIMER INTERRUPT
// with a clock frequency of 100 MHz for the timer -> t_count = 10ns
// counter value = 0xFFFFFFFF - Endvalue -> z.B. 0xFFFFFFFF - 0xFFFFFD28 = 0x2D7 = 727 (dec) -> 727 * 10ns = 7,27 us
// when enabling auto-reload, timer resets itself
#define TIMER_LOAD_VALUE      		0xFFFFD949
// e.g. Target: 10 kHz -> 100us -> 100 us/10 ns = 10000(dec) -> 0x2710 -> 0xFFFFFFFF - 0x2710 = 0xFFFFD8EF

//==============================================================================================================================================================

#define INTC_IPC_Shared_INTERRUPT_ID 	66U // see page 313 of ug1085

//==============================================================================================================================================================

// Parameter definitions
#define INTERRUPT_ID_SCUG 				XPAR_SCUGIC_0_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
#define INTERRUPT_ID_IPI 				XPAR_XIPIPSU_0_DEVICE_ID		/* IPI device that Interrupt is connected to */

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
