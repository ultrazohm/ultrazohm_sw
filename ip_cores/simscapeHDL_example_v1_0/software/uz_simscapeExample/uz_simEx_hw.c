#include "uz_simEx_hw.h"

static float uz_simEx_hw_readFloat(uint32_t addr);

struct uz_simEx_hw{
	uint32_t baseAddr;
};

uz_simEx_hw_handle uz_simEx_hw_init(uint32_t baseAddr){
	uz_assertNotNull(baseAddr);
	uz_simEx_hw_handle self=malloc(sizeof(uz_simEx_hw));
	uz_assertNotNull(self);
	self->baseAddr=baseAddr;
	return self;
}

void uz_simEx_hw_writeVin(uz_simEx_hw_handle self, float Vin){
	uz_assertNotNull(self);
	uz_writeFloatToAxi(self->baseAddr+Vin_Data_simscapeHDL_example,Vin);
}
float uz_simEx_hw_readIR(uz_simEx_hw_handle self){
	uz_assertNotNull(self);
	return (uz_readFloatFromAxi(self->baseAddr+IR_Data_simscapeHDL_example));
}
float uz_simEx_hw_readIout(uz_simEx_hw_handle self){
	uz_assertNotNull(self); // @suppress("No return value")
	return (uz_readFloatFromAxi(self->baseAddr+Iout_Data_simscapeHDL_example));
};
float uz_simEx_hw_readVdiode(uz_simEx_hw_handle self){
	uz_assertNotNull(self);
	return (uz_readFloatFromAxi(self->baseAddr+Vdiode_Data_simscapeHDL_example));
};

static float uz_simEx_hw_readFloat(uint32_t addr){
	uint32_t temp;
	temp=uz_Read32BitFromRegister(addr);
	float read=*((float*)&temp);
	return read;
}
