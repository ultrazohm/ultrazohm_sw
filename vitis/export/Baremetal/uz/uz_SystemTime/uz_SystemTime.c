#include "uz_SystemTime.h"

// private functions
static uint64_t Timer_GetValue_u64(XTmrCtr * InstancePtr);

typedef struct{
	float isr_period_us;					// measured period of interrupt in micro seconds
	float isr_execution_time_us;			// measured execution time of interrupt service routine (isr)
	uint64_t 		interrupt_counter;	// counting interrupts since start up
	uint64_t		uptime_us; 			// total uptime in micro seconds (us)
	unsigned int 	uptime_ms; 			// total uptime in milli seconds (ms)
	unsigned int 	uptime_sec; 		// total uptime in seconds (sec)
	unsigned int	uptime_min; 		// total uptime in minutes (min)
	uint64_t		timestamp_ISR_start;
	uint64_t		timestamp_ISR_end;
} uz_SystemTime;

// private variables
static XTmrCtr Timer_Uptime;
static uz_SystemTime timingR5 = {.isr_period_us=0,
									.isr_execution_time_us=0,
									.interrupt_counter=0,
									.uptime_us=0,
									.uptime_ms=0,
									.uptime_sec=0,
									.uptime_min=0,
									.timestamp_ISR_start=0,
									.timestamp_ISR_end=0};


void uz_SystemTime_init(){

	// SETUP THE TIMER for global uptime
	XTmrCtr_Initialize(&Timer_Uptime, XPAR_TIMER_UPTIME_64BIT_DEVICE_ID);
	// stop timer
	XTmrCtr_Stop(&Timer_Uptime, 0);
	XTmrCtr_Stop(&Timer_Uptime, 1);
	// set reset value of timer to 0
	XTmrCtr_SetResetValue(&Timer_Uptime, 0, 0);
	XTmrCtr_SetResetValue(&Timer_Uptime, 1, 0);
	// reset timer
	XTmrCtr_Reset(&Timer_Uptime, 0);
	XTmrCtr_Reset(&Timer_Uptime, 1);
	// set cascade mode
	XTmrCtr_SetOptions(&Timer_Uptime, 0, XTC_CASCADE_MODE_OPTION);
	// start timer
	XTmrCtr_Start(&Timer_Uptime,0);

}

//----------------------------------------------------
// Measure system time
//----------------------------------------------------
void uz_SystemTime_update()
{

	uint64_t const Uptime_timer_counts_per_us = XPAR_TIMER_UPTIME_64BIT_CLOCK_FREQ_HZ * 1e-6; // for 100 MHz->10ns; 10ns * 100 = 1us
	uint64_t static previous_timestamp_ISR_start = 0;

	// measure uptime
	timingR5.uptime_us 	= timingR5.timestamp_ISR_start / Uptime_timer_counts_per_us;
	timingR5.uptime_ms 	= timingR5.uptime_us * 1e-3;
	timingR5.uptime_sec	= timingR5.uptime_ms * 1e-3;
	timingR5.uptime_min 	= timingR5.uptime_ms * 1e-3 / 60;

	// count number of interrupts
	timingR5.interrupt_counter++;

	// calculate ISR execution time of previous control cycle
	int timestamp_diff_isr_exec	 	= timingR5.timestamp_ISR_end - previous_timestamp_ISR_start;
	timingR5.isr_execution_time_us 	= (float)timestamp_diff_isr_exec / Uptime_timer_counts_per_us; //PL clock-Ticks* @100MHz Clock [us]

	// calculate ISR period
	int timestamp_diff_isr_period	= timingR5.timestamp_ISR_start - previous_timestamp_ISR_start;
	timingR5.isr_period_us 			= (float)timestamp_diff_isr_period / Uptime_timer_counts_per_us; //PL clock-Ticks* @100MHz Clock [us]

	// store previous timestamp at ISR start to calculate the ISR execution time in the next cycle
	previous_timestamp_ISR_start = timingR5.timestamp_ISR_start;
}

static uint64_t Timer_GetValue_u64(XTmrCtr * InstancePtr){

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	// read upper 32 bits
	uint32_t reg_upper = XTmrCtr_ReadReg(InstancePtr->BaseAddress, 1, XTC_TCR_OFFSET);
	// read lower 32 bits
	uint32_t reg_lower = XTmrCtr_ReadReg(InstancePtr->BaseAddress, 0, XTC_TCR_OFFSET);
	// read upper 32 bits
	uint32_t reg_upper_check = XTmrCtr_ReadReg(InstancePtr->BaseAddress, 1, XTC_TCR_OFFSET);

	if(reg_upper != reg_upper_check) // check if 1 bit has flipped while reading, as described in PG079: Ch. 3 "capture mode"
		reg_lower = XTmrCtr_ReadReg(InstancePtr->BaseAddress, 0, XTC_TCR_OFFSET);

	// combine both to one unsigned int with 64bits
	uint64_t timestamp = (uint64_t) reg_upper << 32 | reg_lower;

	return timestamp;
};

void uz_SystemTime_ReadTimer(){
	timingR5.timestamp_ISR_start = Timer_GetValue_u64(&Timer_Uptime);
}

void uz_SystemTime_StopStopwatch(){
	timingR5.timestamp_ISR_end = Timer_GetValue_u64(&Timer_Uptime);
}

float uz_SystemTime_GetIsrExectionTimeInUs(){
	return (timingR5.isr_execution_time_us);
}

unsigned int uz_SystemTime_GetUptimeInMs(){
	return (timingR5.uptime_ms);
}
unsigned int uz_SystemTime_GetUptimeInSec(){
	return (timingR5.uptime_sec);
}

uint64_t uz_SystemTime_GetUptimeInUs(){
	return (timingR5.uptime_us);
}

unsigned int uz_SystemTime_GetUptimeInMin(){
	return (timingR5.uptime_min);
}

float uz_SystemTime_GetIsrPeriodInUs(){
	return (timingR5.isr_period_us);
}

uint64_t uz_SystemTime_GetInterruptCounter(){
	return (timingR5.interrupt_counter);
}

