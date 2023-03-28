#include "uz_interlockDeadtime2L_staticAllocator.h"
#include "uz_interlockDeadtime2L_private.h"
#include "xparameters.h"

static uz_interlockDeadtime2L interlock_slotD1 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_0_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1.0, .inverse_bottom_switch = false };

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_slotD1(void) {
	return (uz_interlockDeadtime2L_init(&interlock_slotD1));
}
