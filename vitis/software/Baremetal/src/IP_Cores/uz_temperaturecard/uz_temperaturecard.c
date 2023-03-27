#include "../../uz/uz_global_configuration.h"
#if UZ_TEMPERATURE_CARD_MAX_INSTANCES > 0U
#include "uz_temperaturecard.h" 

struct uz_temperaturecard_t {
    uint32_t 				    base_address;
	uint32_t 				    ip_clk_frequency_Hz;
	bool 						is_ready;
	uint32_t 					Sample_Freq;
	uint32_t 					Stepcounter;
	uz_temperaturecard_OneGroup	Channel_A;
	uz_temperaturecard_OneGroup	Channel_B;
	uz_temperaturecard_OneGroup	Channel_C;
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
    self-> Sample_Freq          = config.Sample_Freq;
    self-> Stepcounter 			= 0;

    for(int i = 0; i < CHANNEL_COUNT; i++){
		//Select Channel_A
    	self-> Channel_A.Configdata[i] = config.Configdata_A[i];
		//Select Channel_B
    	self-> Channel_B.Configdata[i] = config.Configdata_B[i];
		//Select Channel_C
    	self-> Channel_C.Configdata[i] = config.Configdata_C[i];
    }

    //Write settings
    uz_TempCard_IF_hw_writeCounterReg(self->base_address,(uint32_t)((1.0f/((float)self->Sample_Freq))/(1.0f/(float)self->ip_clk_frequency_Hz)));
    for(int i = 0; i < CHANNEL_COUNT; i++){
        //Select Channel_A
        uz_TempCard_IF_hw_writeReg(self->base_address + TempCard_IF_Config_A_0 + (i * 0x4), self->Channel_A.Configdata[i]);
        //Select Channel_B
        uz_TempCard_IF_hw_writeReg(self->base_address + TempCard_IF_Config_B_0 + (i * 0x4), self->Channel_B.Configdata[i]);
        //Select Channel_C
        uz_TempCard_IF_hw_writeReg(self->base_address + TempCard_IF_Config_C_0 + (i * 0x4), self->Channel_C.Configdata[i]);
    }
    return (self);
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

void uz_TempCard_IF_MeasureTemps_all(uz_temperaturecard_t* self){
    uz_assert_not_NULL(self);
    for(int i = 0; i < CHANNEL_COUNT; i++){
        //Select Channel_A
    	self->Channel_A.temperature_raw[i]  = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_A_0 + (i * 0x4));   // Read raw Measurement
    	self->Channel_A.Channels_Valid[i]   = (self->Channel_A.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_A.Channels_Valid[i] == 1){
    		self->Channel_A.temperature[i]      = (float)(self->Channel_A.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
    		self->Channel_A.temperature[i]      = -333.3f;
    	}

        //Select Channel_B
    	self->Channel_B.temperature_raw[i]  = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_B_0 + (i * 0x4));   // Read raw Measurement
    	self->Channel_B.Channels_Valid[i]   = (self->Channel_B.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_B.Channels_Valid[i] == 1){
    	   self->Channel_B.temperature[i]       = (float)(self->Channel_B.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
        	self->Channel_B.temperature[i]      = -333.3f;
        }

        //Select Channel_C
    	self->Channel_C.temperature_raw[i]  = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_C_0 + (i * 0x4));   // Read raw Measurement
    	self->Channel_C.Channels_Valid[i]   = (self->Channel_C.temperature_raw[i] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_C.Channels_Valid[i] == 1){
    	self->Channel_C.temperature[i]          = (float)(self->Channel_C.temperature_raw[i] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
		}else{
    		self->Channel_C.temperature[i]      = -333.3f;
    	}
    }
}

void uz_TempCard_IF_MeasureTemps_cyclic(uz_temperaturecard_t* self){
	uz_assert_not_NULL(self);

    if(self->Stepcounter <= CHANNEL_COUNT){
        //Select Channel_A
    	self->Channel_A.temperature_raw[self->Stepcounter]   = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_A_0 + (self->Stepcounter * 0x4));   // Read raw Measurement
    	self->Channel_A.Channels_Valid[self->Stepcounter]    = (self->Channel_A.temperature_raw[self->Stepcounter] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_A.Channels_Valid[self->Stepcounter] == 1){
    		self->Channel_A.temperature[self->Stepcounter]   = (float)(self->Channel_A.temperature_raw[self->Stepcounter] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
    		self->Channel_A.temperature[self->Stepcounter]   = -333.3f;
    	}
    	self->Stepcounter 			= self->Stepcounter+1;
    }else if(self->Stepcounter > CHANNEL_COUNT && self->Stepcounter <= CHANNEL_COUNT*2){
        //Select Channel_B
    	self->Channel_B.temperature_raw[self->Stepcounter-CHANNEL_COUNT]  = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_B_0 + ((self->Stepcounter-CHANNEL_COUNT) * 0x4));   // Read raw Measurement
    	self->Channel_B.Channels_Valid[self->Stepcounter-CHANNEL_COUNT]   = (self->Channel_B.temperature_raw[(self->Stepcounter-CHANNEL_COUNT)] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_B.Channels_Valid[self->Stepcounter-CHANNEL_COUNT] == 1){
    	   self->Channel_B.temperature[self->Stepcounter-CHANNEL_COUNT]       = (float)(self->Channel_B.temperature_raw[self->Stepcounter-CHANNEL_COUNT] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
    	}else{
        	self->Channel_B.temperature[self->Stepcounter-CHANNEL_COUNT]      = -333.3f;
        }
    	self->Stepcounter 			= self->Stepcounter+1;
    }else if(self->Stepcounter > CHANNEL_COUNT*2 && self->Stepcounter <= CHANNEL_COUNT*3){
        //Select Channel_C
    	self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2]  = uz_TempCard_IF_hw_readReg(self->base_address + TempCard_IF_Result_C_0 + ((self->Stepcounter-CHANNEL_COUNT*2) * 0x4));   // Read raw Measurement
    	self->Channel_C.Channels_Valid[self->Stepcounter-CHANNEL_COUNT*2]   = (self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2] & 0xFF000000) >> 24;                              // extract measurement information
    	if(self->Channel_C.Channels_Valid[self->Stepcounter-CHANNEL_COUNT*2] == 1){
    	self->Channel_C.temperature[self->Stepcounter-CHANNEL_COUNT*2]          = (float)(self->Channel_C.temperature_raw[self->Stepcounter-CHANNEL_COUNT*2] & 0x00FFFFFF) * TEMP_CONVERSION_FACTOR;// extract temperature value
		}else{
    		self->Channel_C.temperature[self->Stepcounter-CHANNEL_COUNT*2]      = -333.3f;
    	}
    	self->Stepcounter 			= self->Stepcounter+1;
    }else{
    	self->Stepcounter 			= 0;
    }

}

#endif
