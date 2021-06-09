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

#pragma once
#ifndef UZ_TEMPCARD_IF_H
#define UZ_TEMPCARD_IF_H

#include <stdint.h>

void        uz_TempCard_IF_hw_Reset(uint32_t base_address);                         // Resets the Interface-IP to write new Channel configs
void        uz_TempCard_IF_hw_Start(uint32_t base_address);                         // Starts the Interface-IP
void        uz_TempCard_IF_hw_Stop(uint32_t base_address);                          // Stops the Interface-IP
void        uz_TempCard_IF_hw_writeReg(uint32_t base_address,int32_t B);            // write one Register
int32_t     uz_TempCard_IF_hw_readReg(uint32_t base_address);                       // read one Register

#endif // UZ_TEMPCARD_IF_H
