#include "InterlockDeadtime_hw.h"

// Write function for every AXI register of the IP Core
static void InterlockDeadtimeHW_WriteResetIPCore(const InterlockDeadtime_hw *self, bool ResetIPCore);
static void InterlockDeadtimeHW_WriteEnableIPCore(const InterlockDeadtime_hw *self, bool EnableIPCore);
static int InterlockDeadtimeHW_WriteDelayCycles(const InterlockDeadtime_hw *self, uint32_t DelayCycles);
static void InterlockDeadtimeHW_WriteEnableOutput(const InterlockDeadtime_hw *self, bool Enable);
static void InterlockDeadtimeHW_WriteInverseBotSwitch(const InterlockDeadtime_hw *self, bool InverseBotSwitch);

// Read function for every AXI register of the IP Core
static uint32_t InterlockDeadtimeHW_ReadTimestamp(const InterlockDeadtime_hw *self);
static bool InterlockDeadtimeHW_ReadInverseBotSwitch(const InterlockDeadtime_hw *self);
static uint32_t InterlockDeadtimeHW_ReadDelayCycles(const InterlockDeadtime_hw *self);
static bool InterlockDeadtimeHW_ReadEnableOutput(const InterlockDeadtime_hw *self);


int InterlockDeadtime_hw_init(InterlockDeadtime_hw *self, uint32_t DeviceId, uint32_t BaseAddr){
	Xil_AssertNonvoid(self != NULL);
	Xil_AssertNonvoid(BaseAddr != (uint32_t)0);
	
	self->BaseAddr=BaseAddr;
	self->DeviceId=DeviceId;
	self->IsReady=true;
	self->WriteResetIPCore=&InterlockDeadtimeHW_WriteResetIPCore;
	self->WriteEnableIPCore=&InterlockDeadtimeHW_WriteEnableIPCore;
	self->WriteDelayCycles=&InterlockDeadtimeHW_WriteDelayCycles;
	self->WriteEnableOutput=&InterlockDeadtimeHW_WriteEnableOutput;
	self->WriteInverseBotSwitch=&InterlockDeadtimeHW_WriteInverseBotSwitch;
	self->ReadTimestamp=&InterlockDeadtimeHW_ReadTimestamp;
	self->ReadInverseBotSwitch=&InterlockDeadtimeHW_ReadInverseBotSwitch;
	self->ReadDelayCycles=&InterlockDeadtimeHW_ReadDelayCycles;
	self->ReadEnableOutput=&InterlockDeadtimeHW_ReadEnableOutput;

	return XST_SUCCESS;
};


static void InterlockDeadtimeHW_WriteResetIPCore(const InterlockDeadtime_hw *self, bool ResetIPCore){
	// Assert & Xil_Out
	Xil_AssertNonvoid(self != NULL);
	Xil_Out32(self->BaseAddr+IPCore_Reset_interlock_ip, (uint32_t)ResetIPCore);
	printf("Write to reset register of IPCore: %d\n",ResetIPCore);
};
static void InterlockDeadtimeHW_WriteEnableIPCore(const InterlockDeadtime_hw *self, bool EnableIPCore){
	Xil_AssertNonvoid(self != NULL);
	Xil_Out32(self->BaseAddr+IPCore_Enable_interlock_ip, (uint32_t)EnableIPCore);
	printf("Write to enable register of IPCore: %d\n",EnableIPCore);
};

static int InterlockDeadtimeHW_WriteDelayCycles(const InterlockDeadtime_hw *self, uint32_t DelayCycles){
	Xil_AssertNonvoid(self != NULL);
	int status=XST_SUCCESS;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);

	if(DelayCycles<1024){ // 10 bit counter -> 2^10=1024
		Xil_Out32(self->BaseAddr+AXI_DelayCycles_Data_interlock_ip, (uint32_t)DelayCycles);
		printf("Write to delay cycles register of IPCore: %i\n",DelayCycles);
	} else
	{
		status=XST_FAILURE;
	}		
    return status;
};

static void InterlockDeadtimeHW_WriteEnableOutput(const InterlockDeadtime_hw *self, bool EnableOutput){
	Xil_AssertNonvoid(self != NULL);
	Xil_Out32(self->BaseAddr+AXI_EnableOutput_Data_interlock_ip, (uint32_t)EnableOutput);
	printf("Write to enable output register of IPCore: %i\n",EnableOutput);
};

static void InterlockDeadtimeHW_WriteInverseBotSwitch(const InterlockDeadtime_hw *self, bool InverseBotSwitch){
	Xil_AssertNonvoid(self != NULL);
	//Xil_Out32(self->BaseAddr+AXI_InverseBotSwitch_Data_interlock_ip, (uint32_t)InverseBotSwitch);
	printf("Write to inverse bot switch register of IPCore: %i\n",InverseBotSwitch);
};

// Read function for every AXI register of the IP Core
static uint32_t InterlockDeadtimeHW_ReadTimestamp(const InterlockDeadtime_hw *self){
	Xil_AssertNonvoid(self != NULL);
	uint32_t timestamp;
	timestamp=Xil_In32(self->BaseAddr+IPCore_Timestamp_interlock_ip);
	printf("Read timestamp");
	return timestamp;
};

static bool InterlockDeadtimeHW_ReadInverseBotSwitch(const InterlockDeadtime_hw *self){
	Xil_AssertNonvoid(self != NULL);
	uint32_t InvBotSW;
	InvBotSW=Xil_In32(self->BaseAddr+AXI_fb_InverseBotSwitch_Data_interlock_ip);
	printf("Read inverse bot switch");
	return (bool)InvBotSW;
};

static uint32_t InterlockDeadtimeHW_ReadDelayCycles(const InterlockDeadtime_hw *self){
	Xil_AssertNonvoid(self != NULL);
	uint32_t DelayCycles;
	DelayCycles=Xil_In32(self->BaseAddr+AXI_fb_DelayCycles_Data_interlock_ip);
	printf("Read delay cycles");
	return DelayCycles;
};

static bool InterlockDeadtimeHW_ReadEnableOutput(const InterlockDeadtime_hw *self){
	Xil_AssertNonvoid(self != NULL);
	uint32_t EnableOutput;
	EnableOutput=Xil_In32(self->BaseAddr+AXI_fb_enable_Data_interlock_ip);
	printf("Read enableoutput");
	return (bool)EnableOutput;
};
