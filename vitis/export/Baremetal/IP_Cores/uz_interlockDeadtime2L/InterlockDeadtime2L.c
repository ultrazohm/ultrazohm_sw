#include "InterlockDeadtime2L.h"

// function definition
static void SetEnableOutput(InterlockDeadtime2L *self, bool EnableOutput);
static bool GetEnableOutput(const InterlockDeadtime2L *self);
static int SetDeadtimeInMicroseconds(InterlockDeadtime2L *self, float DeadtimeInMicroSeconds);
static float GetDeadtimeInMicroseconds(const InterlockDeadtime2L *self);

// Private Functions
static int CalculateDelayCyclesFromMicroseconds(int ClockFrequencyMHz, float DeadtimeInMicroseconds);
static int CalculateMicrosecondsFromDelayCycles(int ClockFrequencyMHz, int DelayCycles);
static void SetInverseBotSwitch(InterlockDeadtime2L *self, bool InverseBotSwitch);
static bool GetInverseBotSwitch(const InterlockDeadtime2L *self);

static void SetClockFrequencyMHz(InterlockDeadtime2L *self, int ClockFrequencyMHz);

int InterlockDeadtime2L_init(InterlockDeadtime2L *self, uint32_t DeviceId, uint32_t BaseAddr, int ClockFrequencyMHz, bool InverseBotSwitch, float DeadtimeInMicroSeconds){
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
    SetClockFrequencyMHz(self,ClockFrequencyMHz);
    SetInverseBotSwitch(self,InverseBotSwitch);
    self->MaxDeadtimeInMicroSeconds=(float)1/(self->ClockFrequencyMHz)*self->hw.MaxDelayCycles;
    Xil_AssertNonvoid(status==XST_SUCCESS);
    self->SetDeadtimeInMicroseconds(self,DeadtimeInMicroSeconds);

    // Check if initialization was correct
    Xil_AssertNonvoid( GetInverseBotSwitch(self)==InverseBotSwitch );
    Xil_AssertNonvoid( self->GetDeadtimeInMicroseconds(self)==DeadtimeInMicroSeconds);
    return status;
};

static void SetEnableOutput(InterlockDeadtime2L *self, bool EnableOutput){
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    self->hw.WriteEnableOutput(&self->hw,EnableOutput);
}

static bool GetEnableOutput(const InterlockDeadtime2L *self){
    bool EnableOutput;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    EnableOutput=self->hw.ReadEnableOutput(&self->hw);
    return EnableOutput;
};

static void SetInverseBotSwitch(InterlockDeadtime2L *self, bool InverseBotSwitch){
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    self->hw.WriteInverseBotSwitch(&self->hw,InverseBotSwitch);
};

static bool GetInverseBotSwitch(const InterlockDeadtime2L *self){
    bool InvBotSW;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    InvBotSW=self->hw.ReadInverseBotSwitch(&self->hw);
    return InvBotSW;
};

static void SetClockFrequencyMHz(InterlockDeadtime2L *self, int ClockFrequencyMHz){
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    Xil_AssertNonvoid(ClockFrequencyMHz > 0);
    self->ClockFrequencyMHz=ClockFrequencyMHz;
};

static int SetDeadtimeInMicroseconds(InterlockDeadtime2L *self, float DeadtimeInMicroSeconds){
    int status=XST_SUCCESS;
    float DelayCycles;
    Xil_AssertNonvoid(self != NULL);
    Xil_AssertNonvoid(self->IsReady);
    Xil_AssertNonvoid(DeadtimeInMicroSeconds >= (float)0.0 );
    Xil_AssertNonvoid(DeadtimeInMicroSeconds < self->MaxDeadtimeInMicroSeconds ); // 1024 is 2^10 for 10bit counter in deadtime module
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

static float GetDeadtimeInMicroseconds(const InterlockDeadtime2L *self){
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
