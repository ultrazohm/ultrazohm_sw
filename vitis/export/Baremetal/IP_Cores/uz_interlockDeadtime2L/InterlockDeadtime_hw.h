#ifndef InterlockDeadtime2L_hw
#define InterlockDeadtime2L_hw

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Header of IP-Core
#include "interlock_ip_addr.h"

// Xilinx libs
#include "xil_io.h"
#include "xil_assert.h"
#include "xstatus.h"

typedef struct InterlockDeadtime2L_hw_{
	uint32_t DeviceId;			/**< Unique ID of device */
	uint32_t BaseAddr;			/**< Register base address */
	bool IsReady;
	int MaxDelayCycles;
	uint32_t (*ReadTimestamp)(const struct InterlockDeadtime2L_hw_ *self);
	bool (*ReadInverseBotSwitch)(const struct InterlockDeadtime2L_hw_ *self);
	uint32_t (*ReadDelayCycles)(const struct InterlockDeadtime2L_hw_ *self);
	bool (*ReadEnableOutput)(const struct InterlockDeadtime2L_hw_ *self);
	void (*WriteResetIPCore) (const struct InterlockDeadtime2L_hw_ *self, bool ResetIPCore);
	void (*WriteEnableIPCore) (const struct InterlockDeadtime2L_hw_ *self, bool EnableIPCore);
	int (*WriteDelayCycles) (const struct InterlockDeadtime2L_hw_ *self, uint32_t DelayCycles);
	void (*WriteEnableOutput) (const struct InterlockDeadtime2L_hw_ *self, bool Enable);
	void (*WriteInverseBotSwitch) (const struct InterlockDeadtime2L_hw_ *self, bool EnableOutput);
} InterlockDeadtime_hw;

int InterlockDeadtime_hw_init(InterlockDeadtime_hw *self, uint32_t DeviceId, uint32_t BaseAddr);

#endif
