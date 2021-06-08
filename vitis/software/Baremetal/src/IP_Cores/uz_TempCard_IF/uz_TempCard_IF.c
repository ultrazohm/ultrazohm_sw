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

#include "uz_TempCard_IF.h"
#include "uz_TempCard_IF_private.h"
#include "uz_TempCard_IF_hwAddresses.h"

uz_TempCard_IF_handle uz_TempCard_IF_init(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self); // Make sure no NULL pointer is passed to the function since this would be an error
    uz_assert(self->base_address != 0); // Make sure that the base address is set
    uz_assert(self->is_ready == false); // Make sure this instance is not initialized two times
    self->is_ready = true;
    return (self);
}


// Resets the Interface-IP to write new Channel configs
void uz_TempCard_IF_Reset(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    self->Control_Reg  = (uz_axi_read_int32(self->base_address + TempCard_IF_Controlreg) & ~(0x00000002));          // clear the Reset-Bit
    uz_axi_write_int32(self->base_address + TempCard_IF_Controlreg, self->Control_Reg);
    // IP-Core should recognize one-cycle-reset and triggers a new power-up-sequence with reconfigurations of the LTC's
    self->Control_Reg  = (uz_axi_read_int32(self->base_address + TempCard_IF_Controlreg) | 0x00000002);             // set the Reset-Bit (since this is an active-low-Reset, the 1 represents the running state)
    uz_axi_write_int32(self->base_address + TempCard_IF_Controlreg, self->Control_Reg);
}

// Starts the Interface-IP
void uz_TempCard_IF_Start(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    self->Control_Reg  = (uz_axi_read_int32(self->base_address + TempCard_IF_Controlreg) | 0x00000001);
    uz_axi_write_int32(self->base_address + TempCard_IF_Controlreg, self->Control_Reg);                       // Readback the Register and set the Start-bit to 1
}

// Stops the Interface-IP
void uz_TempCard_IF_Stop(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    self->Control_Reg  = (uz_axi_read_int32(self->base_address + TempCard_IF_Controlreg) & ~(0x00000001));
    uz_axi_write_int32(self->base_address + TempCard_IF_Controlreg, self->Control_Reg);                        // Readback the Register and set the Start-bit to 0
}

// Readbacksthe Interface-IP
uint32_t uz_TempCard_IF_ReadBack(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    // Readback the Readbackregister
    self->Readback  = (uz_axi_read_int32(self->base_address + TempCard_IF_Design_RB) & ~(0x00000001));
    if (IP_CORE_READBACK_VALUE != self->Readback){
        return(UZ_FAILURE);
    }else{
        return(self->Readback);
    }
}

// Set the Counter for the internal trigger generator
void uz_TempCard_IF_setCounter(uz_TempCard_IF_handle self, uint32_t Counter){
    uz_assert_not_NULL(self);
    self->Counter_Period  = Counter;
    uz_axi_write_int32(self->base_address + TempCard_IF_Controlreg,TempCard_IF_Counterreg);            // Writes the countervalue down to the register
}

// Set the ConfigWord for the specified channel
uint32_t uz_TempCard_IF_SetConfig(uz_TempCard_IF_handle self, uint32_t ConfigWord, uint32_t Channel){
    uz_assert_not_NULL(self);
    if(Channel>=CHANNEL_TOTAL){
        return(UZ_FAILURE);
    }else{
        if(Channel<20){                         //Select Channel_A
            self->Channel_A.Configdata[Channel]     = ConfigWord;
        }else if(Channel>=20 && Channel<40){    //Select Channel_B
            self->Channel_B.Configdata[Channel-20]  = ConfigWord;
        }else{                                  //Select Channel_C
            self->Channel_C.Configdata[Channel-40]  = ConfigWord;
        }
        return(UZ_SUCCESS);
    }
}

// Read the Config of the specified Channel
uint32_t uz_TempCard_IF_GetConfig(uz_TempCard_IF_handle self, uint32_t Channel){
    uz_assert_not_NULL(self);
    if(Channel<20){                             //Select Channel_A
        return(self->Channel_A.Configdata[Channel]);
    }else if(Channel>=20 && Channel<40){        //Select Channel_B
        return(self->Channel_B.Configdata[Channel-20]);
    }else{                                      //Select Channel_C
        return(self->Channel_C.Configdata[Channel-40]);
    }
}

// Writes the in the struct stored config down to the Interface-IP
void uz_TempCard_IF_SyncConfig(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    for(int i = 0; i < CHANNEL_COUNT_OneChannel; i++){                       
        //Select Channel_A
        uz_axi_write_int32(self->base_address + TempCard_IF_Config_A_0 + (i * 0x4), self->Channel_A.Configdata[i]);
        //Select Channel_B
        uz_axi_write_int32(self->base_address + TempCard_IF_Config_B_0 + (i * 0x4), self->Channel_A.Configdata[i]);
        //Select Channel_C
        uz_axi_write_int32(self->base_address + TempCard_IF_Config_C_0 + (i * 0x4), self->Channel_A.Configdata[i]);
    }
}

// Checks wheather the in the IP stored config is in Sync with the config stored in the struct
bool uz_TempCard_IF_CheckSync(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    int failure_counter = 0;
    for(int i = 0; i < CHANNEL_COUNT_OneChannel; i++){                       
        //Select Channel_A
        if(self->Channel_A.Configdata[i] != uz_axi_read_int32(self->base_address + TempCard_IF_Config_A_0 + (i * 0x4))){
            failure_counter++;
        }
        //Select Channel_B
        if(self->Channel_B.Configdata[i] != uz_axi_read_int32(self->base_address + TempCard_IF_Config_B_0 + (i * 0x4))){
            failure_counter++;
        }
        //Select Channel_C//
        if(self->Channel_C.Configdata[i] != uz_axi_read_int32(self->base_address + TempCard_IF_Config_C_0 + (i * 0x4))){
            failure_counter++;
        }
    }
    if(failure_counter > 0 ){
        return(UZ_FAILURE);
    }else{
        return(UZ_SUCCESS);
    }
}

// Gets the Temperature-Data from all LTC2983, converts the results and stores the tempvalue in the struct
void uz_TempCard_IF_MeasureTemps(uz_TempCard_IF_handle self){
    uz_assert_not_NULL(self);
    for(int i = 0; i < CHANNEL_COUNT_OneChannel; i++){                       
        //Select Channel_A
    	self->Channel_A.temperature_raw[i]  = uz_axi_read_int32(self->base_address + TempCard_IF_Result_A_0 + (i * 0x4));           // Read raw Measurement
    	self->Channel_A.temperature[i]      = (float)(self->Channel_A.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;    // extract temperature value
    	self->Channel_A.Channels_Valid[i]   = (self->Channel_A.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information

        //Select Channel_B
    	self->Channel_B.temperature_raw[i]  = uz_axi_read_int32(self->base_address + TempCard_IF_Result_B_0 + (i * 0x4));           // Read raw Measurement
    	self->Channel_B.temperature[i]      = (float)(self->Channel_B.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;    // extract temperature value
    	self->Channel_B.Channels_Valid[i]   = (self->Channel_B.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information

        //Select Channel_C
    	self->Channel_C.temperature_raw[i]  = uz_axi_read_int32(self->base_address + TempCard_IF_Result_C_0 + (i * 0x4));           // Read raw Measurement
    	self->Channel_C.temperature[i]      = (float)(self->Channel_C.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;    // extract temperature value
    	self->Channel_C.Channels_Valid[i]   = (self->Channel_C.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information
    }

}

// Read the Temperature Value of the specified Channel
float uz_TempCard_IF_ReadMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel){
    uz_assert_not_NULL(self);
    if(Channel>=CHANNEL_TOTAL){
        return(UZ_FAILURE);
    }else{
		if(Channel<20){                             //Select Channel_A
			return(self->Channel_A.temperature[Channel]);
		}else if(Channel>=20 && Channel<40){        //Select Channel_B
			return(self->Channel_B.temperature[Channel-20]);
		}else{                                      //Select Channel_C
			return(self->Channel_C.temperature[Channel-40]);
		}
    }
}

// Checks wheather the measurement of the Channel is valid
uint8_t uz_TempCard_IF_CheckMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel){
    uz_assert_not_NULL(self);
    if(Channel<20){                             //Select Channel_A
        return(self->Channel_A.Channels_Valid[Channel]);
    }else if(Channel>=20 && Channel<40){        //Select Channel_B
        return(self->Channel_B.Channels_Valid[Channel-20]);
    }else{                                      //Select Channel_C
        return(self->Channel_C.Channels_Valid[Channel-40]);
    }
}
