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

#ifndef CAN_THREAD_
#define CAN_THREAD_

// DEBUG-DEFINES----------------------------------------------------------------------------------------------
#define DEBUG_ThreadAlive_CAN_Thread1   0       // Debug-Variable. Tells the Thread to signalize if he is active.
#define DEBUG_ThreadDelay_CAN_Thread1   1000    // time in ms. Controlls the period of the Thread (Debug only / active when ThreadAlive_CAN_Thread1 is 1)
// DEBUG-DEFINES----------------------------------------------------------------------------------------------

// Defines for the Thread

/**
 * @brief   Define to configure the send-intervale between each CAN-Send-Burst
 *
 * @param   Value time in ms between the CAN-Send-Bursts
 */
#define ThreadDelay_CAN_Thread1         100     // delays the Thread for 50 ms

/**
 * @brief   CAN-ID for the Control-Message
 *
 * @param   Value Defines which Message-ID is declared for controlling the UZ via CAN "NOT IMPLEMENTED YET"
 */
#define CAN_Msg_Control                 0x42    // CAN-ID for the Control-Message
/**
 * @brief   Start-CAN-ID for the Value-Messages
 *
 * @param   Value Defines which Message-ID is used as start-adress for the Slow-Data-Array. All other messages will increment from this start-adress.
 */
#define CAN_Msg_Start                   0x69    // Define the Start-ID for the CAN-Messages
/**
 * @brief   CAN-Message Dezimal-places
 *
 * @param   Value Specify how many dezimal-places should be used for the CAN-Message
 */
#define CAN_Msg_DecimalPlaces           1000    // Decimal Places, check with your DBF/DBC! enter for example 1000 for 3 decimal places

// ========== Functions and Threads ======================================================================
/**
 * @brief   Initialize the CAN0-Interfaces
 */
void CAN_Thread_Init_CAN0();


/**
 * @brief   Initialize the CAN1-Interfaces
 */
void CAN_Thread_Init_CAN1();

/**
 * @brief   Function to send the SlowData via CAN-Bus.
 * 
 * @param   Messagenumber Sets the CAN-ID for this Message
 * @param   dezimalscaler_Value1 Specify the amount of decimal-places for Value 1
 * @param   dezimalscaler_Value2 Specify the amount of decimal-places for Value 2
 * @param   Value1 Value1 to send over the CAN-Bus
 * @param   Value2 Value2 to send over the CAN-Bus
 */
int CAN_Thread_SendSlowData(int Messagenumber, int32_t dezimalscaler_Value1, int32_t dezimalscaler_Value2, float Value1, float Value2);

/**
 * @brief   Started by the network-Thread, this Thread will handle the Communication
 *          via the CAN-Bus. Primary this Thread will read Target Values from theCAN-Bus and
 *          writes them down to the R5 through the IPI. Furthermore this Thread will send
 *          actual Values regardign the Control and Measurement over the CAN-Bus, with limited data-rate.
 */
void CAN_Thread_CAN1();


#endif /* CAN_THREAD_ */
