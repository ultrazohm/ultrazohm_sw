#include "xparameters.h"
#include "uz_InterlockDeadtime3L_staticAllocator.h"
#include "uz_InterlockDeadtime3L_hw.h"
#include "uz_InterlockDeadtime3L_private.h"

static IntDead3L IntDead3L_instance = {
	.base_address = XPAR_INTERLOCK_IP_0_BASEADDR,
	.mode = 0,
	.delay_ns = 20,
	.en = true,
};

IntDead3L_handle uz_InterlockDeadtime3L_staticAllocator(void){
	return(&IntDead3L_instance);
}
