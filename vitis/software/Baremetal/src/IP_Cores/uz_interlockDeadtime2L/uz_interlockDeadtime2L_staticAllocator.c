#include "uz_interlockDeadtime2L_staticAllocator.h"
#include "uz_interlockDeadtime2L_private.h"
#include "xparameters.h"

static uz_interlockDeadtime2L interlock_slotD1_pin_0_to_5 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_0_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 0, .inverse_bottom_switch = true};
static uz_interlockDeadtime2L interlock_slotD1_pin_6_to_11 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_1_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1, .inverse_bottom_switch = false };
static uz_interlockDeadtime2L interlock_slotD1_pin_12_to_17 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_2_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1, .inverse_bottom_switch = false };
static uz_interlockDeadtime2L interlock_slotD1_pin_18_to_23 = { .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_3_BASEADDR, .clock_frequency_MHz = 100, .deadtime_us = 1, .inverse_bottom_switch = false };

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_slotD1_pin_0_to_5(void) {
	return (uz_interlockDeadtime2L_init(&interlock_slotD1_pin_0_to_5));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_slotD1_pin_6_to_11(void) {
	return (uz_interlockDeadtime2L_init(&interlock_slotD1_pin_6_to_11));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_slotD1_pin_12_to_17(void) {
	return (uz_interlockDeadtime2L_init(&interlock_slotD1_pin_12_to_17));
}

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_staticAllocator_slotD1_pin_18_to_23(void) {
	return (uz_interlockDeadtime2L_init(&interlock_slotD1_pin_18_to_23));
}
