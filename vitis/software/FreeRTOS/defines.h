/******************************************************************************
* Copyright 2021 Sebastian Wendel, Eyke Liegmann
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

#include "xparameters.h"


//==============================================================================================================================================================

// Platform parameters
#define PLATFORM_EMAC_BASEADDR XPAR_XEMACPS_0_BASEADDR
#define PLATFORM_ZYNQMP

// Parameter definitions
#define INTERRUPT_ID_SCUG 					XPAR_PSU_ACPU_GIC_DEVICE_ID			/* SCUGIC device that Interrupt is connected to */
#define INTERRUPT_ID_IPI 					XPAR_XIPIPSU_0_DEVICE_ID			/* IPI device that Interrupt is connected to */

// JavaScope network packet size: number of samples batched per TCP packet.
#define JS_SAMPLES_PER_PACKET 15

//==============================================================================================================================================================
// Logging path selector -- compile-time XOR: JavaScope (TCP) vs XCPlite (UDP).
//
// Set exactly ONE to 1; the other must be 0.
//   LOGGING_PATH_JAVASCOPE -- existing JavaScope TCP logger (unchanged)
//   LOGGING_PATH_XCP_LITE  -- XCPlite UDP logger (MIT, CANape-compatible)
//
// Switch to XCPlite by flipping the two values below. Both code paths compile
// in either mode; only the server-start call in main.c changes.
//==============================================================================================================================================================
#define LOGGING_PATH_JAVASCOPE  0
#define LOGGING_PATH_XCP_LITE   1

#if (LOGGING_PATH_JAVASCOPE + LOGGING_PATH_XCP_LITE) != 1
#error "defines.h: exactly one of LOGGING_PATH_JAVASCOPE / LOGGING_PATH_XCP_LITE must be 1"
#endif


#endif /* DEFINES_H_ */
