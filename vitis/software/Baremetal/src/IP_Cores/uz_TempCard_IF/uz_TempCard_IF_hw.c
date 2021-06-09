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

#include "uz_TempCard_IF_hw.h"
#include "uz_TempCard_IF_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_TempCard_IF_hw_Reset(uint32_t base_address){                         // Resets the Interface-IP to write new Channel configs
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));          
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000002));     // clear the Reset-Bit

    // IP-Core should recognize one-cycle-reset and triggers a new power-up-sequence with reconfigurations of the LTC's

    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));             
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000002);  // set the Reset-Bit (since this is an active-low-Reset, the 1 represents the running state)
}

void uz_TempCard_IF_hw_Start(uint32_t base_address){                         // Starts the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata | 0x00000001);     // set the Reset-Bit
}

void uz_TempCard_IF_hw_Stop(uint32_t base_address){                          // Stops the Interface-IP
    uz_assert_not_zero(base_address);
    uint32_t Regdata = 0; 
    Regdata = (uz_axi_read_int32(base_address + TempCard_IF_Controlreg));
    uz_axi_write_int32(base_address + TempCard_IF_Controlreg, Regdata & ~(0x00000001));     // clear the Reset-Bit
}

void uz_TempCard_IF_hw_writeReg(uint32_t base_address,int32_t data){         // write one Register
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address,data);
}

int32_t uz_TempCard_IF_hw_readReg(uint32_t base_address){                    // read one Register
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address));
}
