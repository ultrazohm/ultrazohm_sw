#include "InterlockDeadtime.h"

// function definition
static int SetEnableOutput(InterlockDeadtime *self, bool EnableOutput);
static bool GetEnableOutput(const InterlockDeadtime *self);
static int SetDeadtimeInMicroseconds(InterlockDeadtime *self, float DeadtimeInMicroSeconds);
static float GetDeadtimeInMicroseconds(const InterlockDeadtime *self);

// Private Functions
static int CalculateDelayCyclesFromMicroseconds(int ClockFrequencyMHz, float DeadtimeInMicroseconds);
static int CalculateMicrosecondsFromDelayCycles(int ClockFrequencyMHz, int DelayCycles);

int InterlockDeadtime_init(InterlockDeadtime *self, uint32_t DeviceId, uint32_t BaseAddr, int ClockFrequencyMHz, bool InverseBotSwitch, float DeadtimeInMicroSeconds){
	Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(BaseAddr != (uint32_t)0);
    Xil_AssertNonvoid(ClockFrequencyMHz >= 0);

    // Public methods of the class are assigned
    self->GetEnableOutput=&GetEnableOutput;
    self->SetDeadtimeInMicroseconds=&SetDeadtimeInMicroseconds;
    self->GetDeadtimeInMicroseconds=&GetDeadtimeInMicroseconds;
    self->SetEnableOutput=&SetEnableOutput;

    // Initialization of the system
    int status=XST_SUCCESS;
    self->IsReady=true;
    status=InterlockDeadtime_hw_init(&self->hw, DeviceId, BaseAddr);
    self->ClockFrequencyMHz=ClockFrequencyMHz;
    status=self->SetDeadtimeInMicroseconds(self,DeadtimeInMicroSeconds);
    if (status!=XST_SUCCESS){
    	self->IsReady=false;
    }
    return status;
};

static int SetEnableOutput(InterlockDeadtime *self, bool EnableOutput){
    int status=XST_SUCCESS;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    self->hw.WriteEnableOutput(&self->hw,EnableOutput);
    return status;
}

static bool GetEnableOutput(const InterlockDeadtime *self){
    bool EnableOutput;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    EnableOutput=self->hw.ReadEnableOutput(&self->hw);
    return EnableOutput;
};

static int SetDeadtimeInMicroseconds(InterlockDeadtime *self, float DeadtimeInMicroSeconds){
    int status=XST_SUCCESS;
    float DelayCycles;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    Xil_AssertNonvoid(DeadtimeInMicroSeconds >= (float)0.0 );
    Xil_AssertNonvoid(DeadtimeInMicroSeconds < (float)self->ClockFrequencyMHz*1024 ); // 1024 is 2^10 for 10bit counter in deadtime module
    if(self->hw.ReadEnableOutput(&self->hw) == false){
    	self->DeadtimeInMicroSeconds=DeadtimeInMicroSeconds;
     DelayCycles=CalculateDelayCyclesFromMicroseconds(self->ClockFrequencyMHz,self->DeadtimeInMicroSeconds);
     status=self->hw.WriteDelayCycles(&self->hw,DelayCycles);
    }else
    {
        status=XST_FAILURE;
    }
    return status;
};

static float GetDeadtimeInMicroseconds(const InterlockDeadtime *self){
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    float DeadtimeinMicroseconds;
    int DelayCycles;
    DelayCycles=self->hw.ReadDelayCycles(&self->hw);
    DeadtimeinMicroseconds=CalculateMicrosecondsFromDelayCycles(self->ClockFrequencyMHz,DelayCycles);
    return DeadtimeinMicroseconds;
};

static int CalculateDelayCyclesFromMicroseconds(int ClockFrequencyMHz, float DeadtimeInMicroseconds){
    Xil_AssertNonvoid(DeadtimeInMicroseconds >= (float)0.0 );
    Xil_AssertNonvoid(ClockFrequencyMHz >= (int)0 );
    int DelayCylces;
    float clk_us=0.0;
	clk_us=1.0/(ClockFrequencyMHz);		// calculates the time of one clock cycle in us
	DelayCylces=(int)ceil(DeadtimeInMicroseconds/clk_us); // calculates the number of clock cycles required for the dead time - rounds up
    return DelayCylces;
};

static int CalculateMicrosecondsFromDelayCycles(int ClockFrequencyMHz, int DelayCycles){
    Xil_AssertNonvoid(DelayCycles >= (int)0 );
    Xil_AssertNonvoid(ClockFrequencyMHz >= (int)0 );
    float DeadtimeInMicroseconds;
    float clk_us=0.0;
	clk_us=1.0/(ClockFrequencyMHz);		// calculates the time of one clock cycle in us
    DeadtimeInMicroseconds=clk_us*DelayCycles;
    return DeadtimeInMicroseconds;
};
