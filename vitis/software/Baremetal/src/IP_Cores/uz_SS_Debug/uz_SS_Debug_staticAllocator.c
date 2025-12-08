#include "xparameters.h"
#include "uz_SS_Debug_staticAllocator.h"
#include "uz_SS_Debug_hw.h"
#include "uz_SS_Debug_private.h"

uint8_t instance_counter = 0;

static SSDebug SSDebug_instance_0 = {
	.base_address = XPAR_SS_DEBUG_0_BASEADDR
};

static SSDebug SSDebug_instance_1 = {
	.base_address = XPAR_SS_DEBUG_1_BASEADDR
};

// could be generalized in future, just did it like this because its meant for testing of another ip block
SSDebug_handle uz_SS_Debug_staticAllocator(void){
	switch (instance_counter){
		case 0:
			return(&SSDebug_instance_0);
			break;
		case 1:
			return(&SSDebug_instance_1);
			break;
		default:
			instance_counter = 0;
			return 0;
	}
	instance_counter ++;
}
