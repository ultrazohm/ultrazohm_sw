#include "uz_simExpl.h"

#include "uz_simExpl.h"

static void uz_simExpl_writeVin(uz_simExpl_handle self, float Vin);
static float uz_simExpl_readIR(uz_simExpl_handle self);
static float uz_simExpl_readIout(uz_simExpl_handle self);
static float uz_simExpl_readVdiode(uz_simExpl_handle self);


uz_simExpl_handle uz_simExpl_init(uint32_t baseAddr){
	uz_assertNotNull(baseAddr);
	uz_simExpl_handle self=malloc(sizeof(uz_simExpl));
	uz_assertNotNull(self);
	self->baseAddr=baseAddr;
	self->IR=0;
	self->Iout=0;
	self->Vdiode=0;
	return self;
}

void uz_simExpl_setVin(uz_simExpl_handle self,float Vin){
	uz_assertNotNull(self);
	self->Vin=Vin;
	uz_simExpl_writeVin(self,self->Vin);
}

float uz_simExpl_getIR(uz_simExpl_handle self){
	uz_assertNotNull(self);
	self->IR=uz_simExpl_readIR(self);
	return (self->IR);
}

float uz_simExpl_getVdiode(uz_simExpl_handle self){
	uz_assertNotNull(self);
	self->Vdiode=uz_simExpl_readVdiode(self);
	return (self->Vdiode);
}

float uz_simExpl_getIout(uz_simExpl_handle self){
	uz_assertNotNull(self);
	self->Iout=uz_simExpl_readIout(self);
	return (self->Iout);
}



// Private functions
static void uz_simExpl_writeVin(uz_simExpl_handle self, float Vin){
	uz_assertNotNull(self);
	uz_writeFloatToAxi(self->baseAddr+Vin_Data_simscapeHDL_example,Vin);
}

static float uz_simExpl_readIR(uz_simExpl_handle self){
	uz_assertNotNull(self);
	return (uz_readFloatFromAxi(self->baseAddr+IR_Data_simscapeHDL_example));
}

static float uz_simExpl_readIout(uz_simExpl_handle self){
	uz_assertNotNull(self); // @suppress("No return value")
	return (uz_readFloatFromAxi(self->baseAddr+Iout_Data_simscapeHDL_example));
}

static float uz_simExpl_readVdiode(uz_simExpl_handle self){
	uz_assertNotNull(self);
	return (uz_readFloatFromAxi(self->baseAddr+Vdiode_Data_simscapeHDL_example));
}
