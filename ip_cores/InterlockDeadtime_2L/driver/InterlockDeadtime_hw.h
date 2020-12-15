#ifndef INTERLOCKDEADTIME_HW
#define INTERLOCKDEADTIME_HW

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Header of IP-Core
#include "interlock_ip_addr.h"

// Xilinx libs
#include "xil_io.h"
#include "xil_assert.h"
#include "xstatus.h"
// The InterlockDeadtime_config data type contains configuration information of the device that does not change after compilation!

typedef struct InterlockDeadtime_hw_{
	uint32_t DeviceId;			/**< Unique ID of device */
	uint32_t BaseAddr;			/**< Register base address */
	bool IsReady;
	uint32_t (*ReadTimestamp)(const struct InterlockDeadtime_hw_ *self);
	bool (*ReadInverseBotSwitch)(const struct InterlockDeadtime_hw_ *self);
	uint32_t (*ReadDelayCycles)(const struct InterlockDeadtime_hw_ *self);
	bool (*ReadEnableOutput)(const struct InterlockDeadtime_hw_ *self);
	void (*WriteResetIPCore) (const struct InterlockDeadtime_hw_ *self, bool ResetIPCore);
	void (*WriteEnableIPCore) (const struct InterlockDeadtime_hw_ *self, bool EnableIPCore);
	int (*WriteDelayCycles) (const struct InterlockDeadtime_hw_ *self, uint32_t DelayCycles);
	void (*WriteEnableOutput) (const struct InterlockDeadtime_hw_ *self, bool Enable);
	void (*WriteInverseBotSwitch) (const struct InterlockDeadtime_hw_ *self, bool EnableOutput);
} InterlockDeadtime_hw;

// Init function
int InterlockDeadtime_hw_init(InterlockDeadtime_hw *self, uint32_t DeviceId, uint32_t BaseAddr);

// Code here 
#endif