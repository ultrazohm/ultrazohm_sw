#include "uz_AxiTimer64Bit.h"

static XTmrCtr Timer_Uptime;

void uz_AxiTimer64Bit_init(){
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
	XTmrCtr_Start(&Timer_Uptime,0);;
}

uint64_t uz_AxiTimer64Bit_ReadValue64Bit(){
	// read upper 32 bits
	uint32_t reg_upper = XTmrCtr_ReadReg(&Timer_Uptime.BaseAddress, 1, XTC_TCR_OFFSET);
	// read lower 32 bits
	uint32_t reg_lower = XTmrCtr_ReadReg(&Timer_Uptime.BaseAddress, 0, XTC_TCR_OFFSET);
	// read upper 32 bits
	uint32_t reg_upper_check = XTmrCtr_ReadReg(&Timer_Uptime.BaseAddress, 1, XTC_TCR_OFFSET);

	if(reg_upper != reg_upper_check) // check if 1 bit has flipped while reading, as described in PG079: Ch. 3 "capture mode"
		reg_lower = XTmrCtr_ReadReg(&Timer_Uptime.BaseAddress, 0, XTC_TCR_OFFSET);

	// combine both to one unsigned int with 64bits
	uint64_t timestamp = (uint64_t) reg_upper_check << 32 | reg_lower;

	return timestamp;
}
