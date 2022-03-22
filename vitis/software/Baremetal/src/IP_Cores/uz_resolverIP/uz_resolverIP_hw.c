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

