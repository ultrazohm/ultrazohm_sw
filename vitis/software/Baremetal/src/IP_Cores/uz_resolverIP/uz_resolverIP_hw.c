/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Felix Kaiser, Thomas Effenberger, Eyke Liegmann
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

#include "uz_resolverIP_hw.h"
#include "uz_resolverIP_hwAddresses.h"

#include "../../uz/uz_AXI.h"

#include "../../uz/uz_HAL.h"


int32_t uz_resolverIP_hw_readRegister(uint32_t base_address, int32_t addr){
    uint8_t MSB = 128;
    uz_assert(addr < 2*MSB);
    uz_assert(addr >= 0);
    uz_assert_not_zero((uint8_t)(addr) & MSB); // check for MSB == 1 in address
    
    int32_t rescon = uz_resolverIP_hw_read_RESCON(base_address);
    rescon &= ~(RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_write_RESCON(base_address, rescon);

    uz_resolverIP_hw_write_RESADR(base_address, addr);

    rescon |= RESCON_Data_uz_axi_GO_bit;
    uz_resolverIP_hw_write_RESCON(base_address, rescon);
    rescon &= ~(RESCON_Data_uz_axi_GO_bit);
    uz_resolverIP_hw_write_RESCON(base_address, rescon);

    do{
        rescon = uz_resolverIP_hw_read_RESCON(base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);
    
    return uz_resolverIP_hw_read_RESRDA(base_address);
}

void uz_resolverIP_hw_writeRegister(uint32_t base_address, int32_t addr, int32_t val){
    uint8_t MSB = 128;
    uz_assert(addr < 2*MSB);
    uz_assert(addr >= 0);
    uz_assert_not_zero((uint8_t)(addr) & MSB); // check for MSB == 1 in address
    uz_assert(val <= 0xFF);
    uz_assert(val >= 0);

    int32_t rescon = uz_resolverIP_hw_read_RESCON(base_address);
    rescon |= RESCON_Data_uz_axi_RW_bit;
    uz_resolverIP_hw_write_RESCON(base_address, rescon);

    uz_resolverIP_hw_write_RESADR(base_address, addr);
    uz_resolverIP_hw_write_RESDAT(base_address, val);
    
    rescon |= RESCON_Data_uz_axi_GO_bit;
    uz_resolverIP_hw_write_RESCON(base_address, rescon);
    rescon &= ~(RESCON_Data_uz_axi_GO_bit);
    uz_resolverIP_hw_write_RESCON(base_address, rescon);

    do{
        rescon = uz_resolverIP_hw_read_RESCON(base_address);
    } while (rescon & RESCON_Data_uz_axi_BUSY_bit);
}



void uz_resolverIP_hw_write_RESCON(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESCON_Data_uz_resolverIP, val);
}

void uz_resolverIP_hw_write_RESDAT(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESDAT_Data_uz_resolverIP, val);
}

void uz_resolverIP_hw_write_RESADR(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESADR_Data_uz_resolverIP, val);
}

int32_t uz_resolverIP_hw_read_RESCON(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESCON_Data_uz_resolverIP));
}

int32_t uz_resolverIP_hw_read_RESDAT(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESDAT_Data_uz_resolverIP));
}
int32_t uz_resolverIP_hw_read_RESRDA(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESRDA_Data_uz_resolverIP));
}

int32_t uz_resolverIP_hw_read_RESADR(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESADR_Data_uz_resolverIP));
}

