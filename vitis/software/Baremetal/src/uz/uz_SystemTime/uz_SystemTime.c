#include "uz_SystemTime.h"
#include "uz_AxiTimer64Bit.h"
#include "../uz_HAL.h"

static void uz_SystemTime_update();

typedef struct {
	float isr_period_us;					// measured period of interrupt in micro seconds
	float isr_execution_time_us;			// measured execution time of interrupt service routine (isr)
	uint64_t interrupt_counter;	// counting interrupts since start up
	uint64_t uptime_us; 			// total uptime in micro seconds (us)
	unsigned int uptime_ms; 			// total uptime in milli seconds (ms)
	unsigned int uptime_sec; 		// total uptime in seconds (sec)
	unsigned int uptime_min; 		// total uptime in minutes (min)
	uint64_t timestamp_ISR_start;
	uint64_t timestamp_ISR_end;
	_Bool TicTocLock;
	_Bool IsReady;
} uz_SystemTime;

// private variables
static uz_SystemTime timingR5 = { .isr_period_us = 0, .isr_execution_time_us = 0, .interrupt_counter = 0, .uptime_us = 0, .uptime_ms = 0, .uptime_sec = 0, .uptime_min = 0, .timestamp_ISR_start = 0,
                .timestamp_ISR_end = 0, .TicTocLock = false, .IsReady = false };

void uz_SystemTime_init() {
	uz_AxiTimer64Bit_init();
	timingR5.IsReady = true;
}

//----------------------------------------------------
// Measure system time
//----------------------------------------------------
static void uz_SystemTime_update() {

	uint64_t const Uptime_timer_counts_per_us = UZ_AXI_TIMER_CLOCK_FREQ * 1e-6; // for 100 MHz->10ns; 10ns * 100 = 1us
	uint64_t static previous_timestamp_ISR_start = 0;

	// measure uptime
	timingR5.uptime_us = timingR5.timestamp_ISR_start / Uptime_timer_counts_per_us;
	timingR5.uptime_ms = timingR5.uptime_us * 1e-3;
	timingR5.uptime_sec = timingR5.uptime_ms * 1e-3;
	timingR5.uptime_min = timingR5.uptime_ms * 1e-3 / 60;

	// count number of interrupts
	timingR5.interrupt_counter++;

	// calculate ISR execution time of previous control cycle
	int timestamp_diff_isr_exec = timingR5.timestamp_ISR_end - previous_timestamp_ISR_start;
	timingR5.isr_execution_time_us = (float) timestamp_diff_isr_exec / Uptime_timer_counts_per_us; //PL clock-Ticks* @100MHz Clock [us]

	// calculate ISR period
	int timestamp_diff_isr_period = timingR5.timestamp_ISR_start - previous_timestamp_ISR_start;
	timingR5.isr_period_us = (float) timestamp_diff_isr_period / Uptime_timer_counts_per_us; //PL clock-Ticks* @100MHz Clock [us]

	// store previous timestamp at ISR start to calculate the ISR execution time in the next cycle
	previous_timestamp_ISR_start = timingR5.timestamp_ISR_start;
}

void uz_SystemTime_ISR_Tic() {
	uz_assert(timingR5.IsReady);
	timingR5.timestamp_ISR_start = uz_AxiTimer64Bit_ReadValue64Bit();
	uz_SystemTime_update();
	timingR5.TicTocLock = true;
}

void uz_SystemTime_ISR_Toc() {
	uz_assert(timingR5.IsReady);
	uz_assert(timingR5.TicTocLock);
	timingR5.TicTocLock = false;
	timingR5.timestamp_ISR_end = uz_AxiTimer64Bit_ReadValue64Bit();
}

float uz_SystemTime_GetIsrExectionTimeInUs() {
	uz_assert(timingR5.IsReady);
	return (timingR5.isr_execution_time_us);
}

unsigned int uz_SystemTime_GetUptimeInMs() {
	uz_assert(timingR5.IsReady);
	return (timingR5.uptime_ms);
}
unsigned int uz_SystemTime_GetUptimeInSec() {
	uz_assert(timingR5.IsReady);
	return (timingR5.uptime_sec);
}

uint64_t uz_SystemTime_GetUptimeInUs() {
	uz_assert(timingR5.IsReady);
	return (timingR5.uptime_us);
}

unsigned int uz_SystemTime_GetUptimeInMin() {
	uz_assert(timingR5.IsReady);
	return (timingR5.uptime_min);
}

float uz_SystemTime_GetIsrPeriodInUs() {
	uz_assert(timingR5.IsReady);
	return (timingR5.isr_period_us);
}

uint64_t uz_SystemTime_GetInterruptCounter() {
	uz_assert(timingR5.IsReady);
	return (timingR5.interrupt_counter);
}

float uz_SystemTime_GetGlobalTimeInSec() {
	uint64_t timestamp = uz_AxiTimer64Bit_ReadValue64Bit();
	float current_global_time = timestamp * (1.0 / UZ_AXI_TIMER_CLOCK_FREQ);
	return (current_global_time);
}
