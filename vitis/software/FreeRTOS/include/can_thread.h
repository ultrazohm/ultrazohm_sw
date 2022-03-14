/******************************************************************************
* Copyright 2021 Robert Zipprich
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

/******************************************************************************
*   What have i done till now:
*   -   Found the realted Xilinx-PSCAN-Lib (C:\Xilinx\Vitis\2020.1\data\embeddedsw\XilinxProcessorIPLib\drivers\canps_v3_4\doc\html\api\index.html)
*   -   Found the FreeRtos-Refmanual (https://www.freertos.org/fr-content-src/uploads/2018/07/FreeRTOS_Reference_Manual_V10.0.0.pdf)
*   -   create the .h and .c files for the CAN-Thread
*   -   adding some defines in the defines.h to select the source of the Control-Signals
*   -   adding a switch-case in the ISR (isr.c) to select the source of the Control-Signals
*       (used a switch-case to add further control-signals-sources for next features 
*       (prob receiving Control-Signals from a second UZ using the High-speed-Transmitter?))
*   -   adding the spawn-point for the CAN-Thread in the network-thread right after the CAN-Init.
*
*   Next steps:
*   -   fill the CAN-Thread to read messages (is next to test)
*   -   fill the CAN-Thread to send messages (is next to implement)
*   -   make sure that the read/write form the CAN in the Struct for the IPI is atomar
*       (use semaphores or mutexes?)
*   -   find out how the values are declared in the IPI-Call
******************************************************************************/

#ifndef CAN_THREAD_
#define CAN_THREAD_

// DEBUG-DEFINES----------------------------------------------------------------------------------------------
#define DEBUG_ThreadAlive_CAN_Thread1	0       // Debug-Variable. Tells the Thread to signalize if he is active.
#define DEBUG_ThreadDelay_CAN_Thread1	1000	// time in ms. Controlls the period of the Thread (Debug only / active when ThreadAlive_CAN_Thread1 is 1)
// DEBUG-DEFINES----------------------------------------------------------------------------------------------

// Defines for the Thread
#define ThreadDelay_CAN_Thread1			100		// delays the Thread for 50 ms

#define CAN_Msg_Control					0x42	// CAN-ID for the Control-Message
#define CAN_Msg_Start					0x69	// Define the Start-ID for the CAN-Messages

#define CAN_Msg_DecimalPlaces			1000	// Decimal Places, check with your DBF/DBC! enter for example 1000 for 3 decimal places

// ========== Functions and Threads ======================================================================
/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_Init_CAN1
 *---------------------------------------------------------------------------*
 * Description:
 *     Initialize the CAN-Interfaces for the CAN_Thread_CAN1
 *---------------------------------------------------------------------------*/
void CAN_Thread_Init_CAN1();

/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_SendSlowData(_int_int / _int_float / _int_uint / _float_int / _float_float / _float_uint / _uint_int / _uint_float / _uint_uint)
 *---------------------------------------------------------------------------*
 * Description:
 *     Function to send the SlowData via CAN-Bus.
 *---------------------------------------------------------------------------*/
int CAN_Thread_SendSlowData(int Messagenumber, int32_t dezimalscaler_Value1, int32_t dezimalscaler_Value2, float Value1, float Value2);

/*---------------------------------------------------------------------------*
 * Routine:  CAN_Thread_CAN1
 *---------------------------------------------------------------------------*
 * Description:
 *      Started by the network-Thread, this Thread will handle the Communication
 *      via the CAN-Bus. Primary this Thread will read Target Values from the
 *      CAN-Bus and writes them down to the R5 through the IPI. Furthermore this 
 *      Thread will send actual Values regardign the Control and Measurement 
 *      over the CAN-Bus, with limited data-rate.
 *---------------------------------------------------------------------------*/
void CAN_Thread_CAN1();


#endif /* CAN_THREAD_ */
