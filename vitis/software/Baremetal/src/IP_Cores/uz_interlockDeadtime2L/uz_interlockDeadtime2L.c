#include "uz_interlockDeadtime2L.h"
#include "uz_interlockDeadtime2L_private.h"
#include "uz_interlockDeadtime2L_hw.h"

static int calculate_delay_cycles_from_microseconds(int clock_frequency_MHz, float deadtime_in_microseconds);
static int calculate_microseconds_from_delay_cycles(int clock_frequency_MHz, int delay_cycles);

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_init(uz_interlockDeadtime2L_handle self) {
	uz_assert_not_NULL(self); // Make sure no NULL pointer is passed to the function since this would be an error
	uz_assert((self->base_address) != 0); // Make sure that the base address is set
	uz_assert(self->is_ready == false); // Make sure this instance is not initialized two times
	self->max_deadtime_us = (float) 1 / (self->clock_frequency_MHz) * UZ_INTERLOCKDEADTIME2L_HW_MAX_DELAY_CYCLES;
	uz_assert(self->deadtime_us <= self->max_deadtime_us);
	self->is_ready = true;
	uz_interlockDeadtime2L_set_deadtime_us(self, self->deadtime_us);
	uz_interlockDeadtime2L_hw_set_inverseBotSwitch(self->base_address, self->inverse_bottom_switch);
	return (self);
}

void uz_interlockDeadtime2L_set_enable_output(uz_interlockDeadtime2L_handle self, bool enable_output) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_interlockDeadtime2L_hw_set_enableOutput(self->base_address, enable_output);
}

bool uz_interlockDeadtime2L_get_enable_output(uz_interlockDeadtime2L_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_interlockDeadtime2L_hw_get_enableOutput(self->base_address));
}

void uz_interlockDeadtime2L_set_deadtime_us(uz_interlockDeadtime2L_handle self, float deadtime_in_microseconds) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(uz_interlockDeadtime2L_get_enable_output(self) == false);
	uz_assert(deadtime_in_microseconds <= self->deadtime_us);
	self->deadtime_us = deadtime_in_microseconds;
	int deadtime_in_cycles = calculate_delay_cycles_from_microseconds(self->clock_frequency_MHz, self->deadtime_us);
	uz_interlockDeadtime2L_hw_set_delayCycles(self->base_address, deadtime_in_cycles);
}

float uz_interlockDeadtime2L_get_deadtime_us(uz_interlockDeadtime2L_handle self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	int deadtime_in_cycles = uz_interlockDeadtime2L_hw_get_delayCycles(self->base_address);
	return (calculate_microseconds_from_delay_cycles(self->clock_frequency_MHz, deadtime_in_cycles));
}

static int calculate_delay_cycles_from_microseconds(int clock_frequency_MHz, float deadtime_in_microseconds) {
	uz_assert(deadtime_in_microseconds >= (float ) 0.0);
	uz_assert(clock_frequency_MHz >= (int ) 0);
	float clk_us = 1.0 / (clock_frequency_MHz);		// calculates the time of one clock cycle in us
	int delay_cylces = (int) ceil(deadtime_in_microseconds / clk_us); // calculates the number of clock cycles required for the dead time - rounds up
	return (delay_cylces);
}

static int calculate_microseconds_from_delay_cycles(int clock_frequency_MHz, int delay_cycles) {
	uz_assert(delay_cycles >= (int ) 0);
	uz_assert(clock_frequency_MHz >= (int ) 0);
	float clk_us = 1.0 / (clock_frequency_MHz);		// calculates the time of one clock cycle in us
	float deadtime_in_us = clk_us * delay_cycles;
	return (deadtime_in_us);
}

