/******************************************************************************
 * Copyright 2025 Andreas Geiger
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

#include "misc_IO.h"

/**
 * Function returns bit pattern of several input signals to the FPGA interfaced via AXI-GPIO block
 * @param no base address as parameter, function specific for only one AXI-GPIO IP Core
 * @return	Bit 0 --> D1_23_IN_KL_15_PG
 * 			Bit 1 --> D1_25_IN_IGNITION_SUCCESS
 * 			Bit 2 --> D1_27_IN_RELAY2_NOT_CLOSED
 * 			Bit 3 --> D1_29_IN_RELAY3_NOT_CLOSED
 */
uint32_t uz_get_misc_inputs(void){
	uint32_t base_address = XPAR_UZ_USER_AXI_GPIO_INPUT_BASEADDR;
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address));
}


/**
 * Function writes bit pattern of several output signals to the FPGA interface via AXI-GPIO block
 * @param 	D1_22_KL15 			--> Bit 0
 * 			D1_24_PYRO_TRIGGER	--> Bit 1
 * 			D1_26_RELAY2_CLOSE	--> Bit 2
 * 			D1_28_RELAY3_CLOSE	--> Bit 3
 * @return no return value
 */
void uz_set_misc_outputs(uint8_t KL15, uint8_t PYRO_TRIGGER, uint8_t RELAY2_CLOSE, uint8_t RELAY3_CLOSE){
	uint32_t base_address = XPAR_UZ_USER_AXI_GPIO_OUTPUT_BASEADDR;
    uint32_t output_bit_word;

    uz_assert_not_zero(base_address);

    output_bit_word = (RELAY3_CLOSE & 0x01)<<3 | (RELAY2_CLOSE & 0x01)<<2 | (PYRO_TRIGGER & 0x01)<<1 | (KL15 & 0x01);

    uz_axi_write_uint32(base_address, output_bit_word);
}
