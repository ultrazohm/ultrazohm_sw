#include "uz_AXI_testIP_hw.h"

static void TogglestrobeA(uz_AXI_testIP_hw_handle self);
static void TogglestrobeB(uz_AXI_testIP_hw_handle self);

struct uz_AXI_testIP_hw{
	uint32_t baseAddr;
};

uz_AXI_testIP_hw_handle uz_AXI_testIP_hw_init(uint32_t baseAddr){
	uz_assert_not_NULL(baseAddr);
	uz_AXI_testIP_hw_handle self=malloc(sizeof(uz_AXI_testIP_hw));
	uz_assert_not_NULL(self);
	self->baseAddr=baseAddr;
	return self;
}

void uz_AXI_testIP_hw_writeAfloat(uz_AXI_testIP_hw_handle self, float data){
	uz_assert_not_NULL(self);
	uz_axi_write_float(self->baseAddr+A_float_Data_AXI_testI_ip, data);
	TogglestrobeA(self);
}

void uz_AXI_testIP_hw_writeBfloat(uz_AXI_testIP_hw_handle self, float data){
	uz_assert_not_NULL(self);
	uz_axi_write_float(self->baseAddr+B_float_Data_AXI_testI_ip, data);
	TogglestrobeB(self);
}

float uz_AXI_testIP_hw_readCfloat(uz_AXI_testIP_hw_handle self){
	uz_assert_not_NULL(self);
	uz_axi_write_bool(self->baseAddr+C_float_Strobe_AXI_testI_ip, true);
	float read=uz_axi_read_float(self->baseAddr+C_float_Data_AXI_testI_ip);
	uz_axi_write_bool(self->baseAddr+C_float_Strobe_AXI_testI_ip, false);
	return read;
}

// int32 multiplication
void uz_AXI_testIP_hw_writeAint32(uz_AXI_testIP_hw_handle self, int32_t data){
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(self);
	uz_axi_write_int32(self->baseAddr+A_int32_Data_AXI_testI_ip, data);
}
void uz_AXI_testIP_hw_writeBint32(uz_AXI_testIP_hw_handle self, int32_t data){
	uz_assert_not_NULL(self);
	uz_axi_write_int32(self->baseAddr+B_int32_Data_AXI_testI_ip, data);
}

int32_t uz_AXI_testIP_hw_readCint32(uz_AXI_testIP_hw_handle self){
	uz_assert_not_NULL(self);
	return uz_axi_read_int32(self->baseAddr+C_int32_Data_AXI_testI_ip);
}

// uint32 multiplication
void uz_AXI_testIP_hw_writeAuint32(uz_AXI_testIP_hw_handle self, uint32_t data){
	uz_assert_not_NULL(self);
	uz_axi_write_uint32(self->baseAddr+A_uint32_Data_AXI_testI_ip, data);
}

void uz_AXI_testIP_hw_writeBuint32(uz_AXI_testIP_hw_handle self, uint32_t data){
	uz_assert_not_NULL(self);
	uz_axi_write_uint32(self->baseAddr+B_uint32_Data_AXI_testI_ip, data);
}

uint32_t uz_AXI_testIP_hw_readCuint32(uz_AXI_testIP_hw_handle self){
	uz_assert_not_NULL(self);
	return uz_axi_read_uint32(self->baseAddr+C_uint32_Data_AXI_testI_ip);
}

// fi(1,16,6) multiplication
void uz_AXI_testIP_hw_writeAfixed(uz_AXI_testIP_hw_handle self, float data){
	uz_assert_not_NULL(self);
	uint32_t fxd=uz_convert_float_to_sfixed(data,5);
	uz_axi_write_uint32(self->baseAddr+A_fx_1_16_5_Data_AXI_testI_ip, fxd );
}
void uz_AXI_testIP_hw_writeBfixed(uz_AXI_testIP_hw_handle self, float data){
	uz_axi_write_uint32(self->baseAddr+B_fx_1_16_5_Data_AXI_testI_ip, uz_convert_float_to_sfixed(data,5) );
}
float uz_AXI_testIP_hw_readCfixed(uz_AXI_testIP_hw_handle self){
	uint32_t read=uz_axi_read_uint32(self->baseAddr+C_fx_1_16_5_Data_AXI_testI_ip);
	return (uz_convert_sfixed_to_float(read, 5));
}

// private functions
static void TogglestrobeA(uz_AXI_testIP_hw_handle self){
	uz_axi_write_bool(self->baseAddr+A_float_Strobe_AXI_testI_ip, false); // off, on, off to force a rising edge on strobe register
	uz_axi_write_bool(self->baseAddr+A_float_Strobe_AXI_testI_ip, true);
	uz_axi_write_bool(self->baseAddr+A_float_Strobe_AXI_testI_ip, false);
}

static void TogglestrobeB(uz_AXI_testIP_hw_handle self){
	uz_axi_write_bool(self->baseAddr+B_float_Strobe_AXI_testI_ip, false); // off, on, off to force a rising edge on strobe register
	uz_axi_write_bool(self->baseAddr+B_float_Strobe_AXI_testI_ip, true);
	uz_axi_write_bool(self->baseAddr+B_float_Strobe_AXI_testI_ip, false);
}
