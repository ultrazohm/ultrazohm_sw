#include "../../uz/uz_global_configuration.h"
#if UZ_TEMPERATURE_CARD_MAX_INSTANCES > 0U
#include "uz_temperaturecard.h" 

struct uz_temperaturecard_t {
    uint32_t                    base_address;
    uint32_t                    ip_clk_frequency_Hz;
    bool                        is_ready;
    uint32_t                    Sample_Freq_Hz;
    uint32_t                    Config_Global_A;
    uint32_t                    Config_Mux_A;
    uint32_t                    Config_Global_B;
    uint32_t                    Config_Mux_B;
    uint32_t                    Config_Global_C;
    uint32_t                    Config_Mux_C;
    uint32_t                    Stepcounter;
    uz_temperaturecard_OneGroup Channel_A;
    uz_temperaturecard_OneGroup Channel_B;
    uz_temperaturecard_OneGroup Channel_C;
};

static uint32_t instance_counter = 0U;
static uz_temperaturecard_t instances[UZ_TEMPERATURE_CARD_MAX_INSTANCES] = { 0 };

static uz_temperaturecard_t* uz_temperaturecard_allocation(void);

static uz_temperaturecard_t* uz_temperaturecard_allocation(void){
    uz_assert(instance_counter < UZ_TEMPERATURE_CARD_MAX_INSTANCES);
    uz_temperaturecard_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_temperaturecard_t* uz_temperaturecard_init(struct uz_temperaturecard_config_t config) {
    uz_temperaturecard_t* self  = uz_temperaturecard_allocation();
    // Store settings
    self-> base_address         = config.base_address;
    self-> ip_clk_frequency_Hz  = config.ip_clk_frequency_Hz;
    self-> Sample_Freq_Hz       = config.Sample_Freq_Hz;
    self-> Config_Global_A 		= config.Config_Global_A;
    self-> Config_Mux_A 		= config.Config_Mux_A;
    self-> Config_Global_B 		= config.Config_Global_B;
    self-> Config_Mux_B 		= config.Config_Mux_B;
    self-> Config_Global_C 		= config.Config_Global_C;
    self-> Config_Mux_C 		= config.Config_Mux_C;
    self-> Stepcounter 			= 0U;

    for(uint32_t i = 0U; i < CHANNEL_COUNT; i++){
		//Select Channel_A
    	self-> Channel_A.Configdata[i] = config.Configdata_A[i];
		//Select Channel_B
    	self-> Channel_B.Configdata[i] = config.Configdata_B[i];
		//Select Channel_C
    	self-> Channel_C.Configdata[i] = config.Configdata_C[i];
    }

    // Write Config-Regs
    uint32_t Configbuffer = 0;
    Configbuffer = (self->Config_Global_C << 16U) | (self->Config_Global_B << 8U) | (self->Config_Global_A << 0U);
    uz_TempCard_IF_hw_writeGlobalConfigReg(self->base_address, Configbuffer);
    Configbuffer = (self->Config_Mux_C << 16U) | (self->Config_Mux_B << 8U) | (self->Config_Mux_A << 0U);
    uz_TempCard_IF_hw_writeMuxConfigReg(self->base_address, Configbuffer);

    //Write Channelsettings
    uz_TempCard_IF_hw_writeCounterReg(self->base_address,(uint32_t)((1.0f/((float)self->Sample_Freq_Hz))/(1.0f/(float)self->ip_clk_frequency_Hz)));   
    uz_TempCard_IF_write_channel_group_configdata(self);
    return (self);
}

void uz_TempCard_IF_write_channel_group_configdata(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_zero(self->base_address);
    uz_TempCard_IF_hw_write_channel_group_A_configdata(self->base_address, self->Channel_A.Configdata);
    uz_TempCard_IF_hw_write_channel_group_B_configdata(self->base_address, self->Channel_B.Configdata);
    uz_TempCard_IF_hw_write_channel_group_C_configdata(self->base_address, self->Channel_C.Configdata);
}

void uz_TempCard_IF_Reset(uz_temperaturecard_t* self){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Reset(self->base_address);
}

void uz_TempCard_IF_Start(uz_temperaturecard_t* self){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Start(self->base_address);
}

void uz_TempCard_IF_Stop(uz_temperaturecard_t* self){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_TempCard_IF_hw_Stop(self->base_address);
}

void uz_TempCard_IF_MeasureTemps_all(uz_temperaturecard_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_zero(self->base_address);
    for(uint32_t i = 0U; i < CHANNEL_COUNT; i++) {
        self->Channel_A.temperature_raw[i] = uz_TempCard_IF_hw_read_raw_value_channel_group_A(self->base_address, i);
        self->Channel_A.Channels_Valid[i]   = (self->Channel_A.temperature_raw[i] & 0xFF000000U) >> 24U;                              // extract measurement information
    	if(self->Channel_A.Channels_Valid[i] == 1U){
    		self->Channel_A.temperature[i]      = (float)(self->Channel_A.temperature_raw[i] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
    		self->Channel_A.temperature[i]      = -333.3f;
    	}

        self->Channel_B.temperature_raw[i] = uz_TempCard_IF_hw_read_raw_value_channel_group_B(self->base_address, i);
        self->Channel_B.Channels_Valid[i]   = (self->Channel_B.temperature_raw[i] & 0xFF000000) >> 24U;                              // extract measurement information
    	if(self->Channel_B.Channels_Valid[i] == 1U){
    	   self->Channel_B.temperature[i]       = (float)(self->Channel_B.temperature_raw[i] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
        	self->Channel_B.temperature[i]      = -333.3f;
        }
        self->Channel_C.temperature_raw[i] = uz_TempCard_IF_hw_read_raw_value_channel_group_C(self->base_address, i);    
        self->Channel_C.Channels_Valid[i]   = (self->Channel_C.temperature_raw[i] & 0xFF000000U) >> 24U;                              // extract measurement information
    	if(self->Channel_C.Channels_Valid[i] == 1U){
    	self->Channel_C.temperature[i]          = (float)(self->Channel_C.temperature_raw[i] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
		}else{
    		self->Channel_C.temperature[i]      = -333.3f;
    	}
    }    
}

void uz_TempCard_IF_MeasureTemps_cyclic(uz_temperaturecard_t* self){
	uz_assert_not_NULL(self);
    if(self->Stepcounter <= CHANNEL_COUNT){
        //Select Channel_A
    	self->Channel_A.temperature_raw[self->Stepcounter]   = uz_TempCard_IF_hw_read_raw_value_channel_group_A(self->base_address, self->Stepcounter);
    	self->Channel_A.Channels_Valid[self->Stepcounter]    = (self->Channel_A.temperature_raw[self->Stepcounter] & 0xFF000000U) >> 24U;                              // extract measurement information
    	if(self->Channel_A.Channels_Valid[self->Stepcounter] == 1U){
    		self->Channel_A.temperature[self->Stepcounter]   = (float)(self->Channel_A.temperature_raw[self->Stepcounter] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
    		self->Channel_A.temperature[self->Stepcounter]   = -333.3f;
    	}
    	self->Stepcounter 			= self->Stepcounter+1U;
    }else if(self->Stepcounter > CHANNEL_COUNT && self->Stepcounter <= CHANNEL_COUNT*2U){
        //Select Channel_B
    	self->Channel_B.temperature_raw[self->Stepcounter-CHANNEL_COUNT]  = uz_TempCard_IF_hw_read_raw_value_channel_group_B(self->base_address, self->Stepcounter);
    	self->Channel_B.Channels_Valid[self->Stepcounter-CHANNEL_COUNT]   = (self->Channel_B.temperature_raw[(self->Stepcounter-CHANNEL_COUNT)] & 0xFF000000U) >> 24U;                              // extract measurement information
    	if(self->Channel_B.Channels_Valid[self->Stepcounter-CHANNEL_COUNT] == 1U){
    	   self->Channel_B.temperature[self->Stepcounter-CHANNEL_COUNT]       = (float)(self->Channel_B.temperature_raw[self->Stepcounter-CHANNEL_COUNT] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
        	self->Channel_B.temperature[self->Stepcounter-CHANNEL_COUNT]      = -333.3f;
        }
    	self->Stepcounter 			= self->Stepcounter+1U;
    }else if(self->Stepcounter > CHANNEL_COUNT*2U && self->Stepcounter <= CHANNEL_COUNT*3U){
        //Select Channel_C
    	self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2U]  = uz_TempCard_IF_hw_read_raw_value_channel_group_C(self->base_address, self->Stepcounter);
    	self->Channel_C.Channels_Valid[self->Stepcounter-CHANNEL_COUNT*2U]   = (self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2U] & 0xFF000000U) >> 24U;                              // extract measurement information
    	if(self->Channel_C.Channels_Valid[self->Stepcounter-CHANNEL_COUNT*2U] == 1U){
    	self->Channel_C.temperature[self->Stepcounter-CHANNEL_COUNT*2U]          = (float)(self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2U] & 0x00FFFFFFU) * TEMP_CONVERSION_FACTOR;// extract temperature value
		}else{
    		self->Channel_C.temperature[self->Stepcounter-CHANNEL_COUNT*2U]      = -333.3f;
    	}
    	self->Stepcounter 			= self->Stepcounter+1U;
    }else{
    	self->Stepcounter 			= 0U;
    }

}

uz_temperaturecard_OneGroup uz_TempCard_IF_get_channel_Group(uz_temperaturecard_t* self, const char channel){
    uz_assert_not_NULL(self);
    uz_temperaturecard_OneGroup out = {0U};
    switch (channel){
        case 'a':
        case 'A':{
            out = self->Channel_A;
            break;}
        case 'b':
        case 'B':{
            out = self->Channel_B;
            break;}
        case 'c':
        case 'C':{
            out = self->Channel_C;
            break;}
        default:{
            break;}
    }
    return out;
}

float uz_TempCard_IF_get_channel(uz_temperaturecard_t* self, uint32_t channel){
	uz_assert(channel< (CHANNEL_COUNT*GROUP_COUNT));

	float Buffer_Tmp_Channel = 0.0f;

	if(channel < CHANNEL_COUNT){
	    //Select Channel_A
	    if(self->Channel_A.Channels_Valid[channel] == 1U){
	    	Buffer_Tmp_Channel  = (float)(self->Channel_A.temperature[channel]);
	    }else{
	    	Buffer_Tmp_Channel  = -333.3f;
	    }
	}else if(channel >= CHANNEL_COUNT && channel < CHANNEL_COUNT*2U){
	    //Select Channel_B
	    if(self->Channel_B.Channels_Valid[channel-CHANNEL_COUNT] == 1U){
	    	Buffer_Tmp_Channel  = (float)(self->Channel_B.temperature[channel-CHANNEL_COUNT]);
	    }else{
	    	Buffer_Tmp_Channel	= -333.3f;
	    }
	}else if(channel >= CHANNEL_COUNT*2U && channel < CHANNEL_COUNT*3U){
	    //Select Channel_C
	    if(self->Channel_C.Channels_Valid[channel-CHANNEL_COUNT*2U] == 1U){
	    	Buffer_Tmp_Channel  = (float)(self->Channel_C.temperature[channel-CHANNEL_COUNT*2U]);
		}else{
			Buffer_Tmp_Channel 	= -333.3f;
	    }
	}

	return Buffer_Tmp_Channel;
}

float uz_TempCard_IF_average_temperature_for_valid(uz_temperaturecard_OneGroup channeldata, const uint32_t lower, const uint32_t upper){
    uz_assert(lower <= upper);
    uz_assert(upper < 20U);
    float sum = 0.0f;
    float valid = 0.0f;
    for(uint32_t i=lower; i<=upper; i++){
        sum += channeldata.temperature[i]*(channeldata.Channels_Valid[i]==1U);
        valid += (channeldata.Channels_Valid[i]==1U);
    }
    if(valid != 0.0f){
        return (sum/valid);
    }else{
        return (-333.3f);
    }
}

#endif
