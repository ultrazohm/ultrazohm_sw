#include "uz_simExpl_testbench.h"



struct SimscapeInput{
	float amplitude;
	float frequency;
};

uz_simExpl_handle simscapeHDLInstance;
static struct SimscapeInput simscape_input;


void uz_simExpl_testbench_init(){
	simscapeHDLInstance=uz_simExpl_init(XPAR_SIMSCAPEHDL_EXAMPLE_0_BASEADDR);
}

void uz_simExpl_stepTestbench(){
	int tmp=(uz_SystemTime_GetInterruptCounter() % 10000);
	float t=tmp/10000.0;
	float sine=simscape_input.amplitude*sin(2*M_PI*t*simscape_input.frequency);
	uz_simExpl_setVin(simscapeHDLInstance,sine);
	uz_simExpl_getIR(simscapeHDLInstance);
	uz_simExpl_getVdiode(simscapeHDLInstance);
	uz_simExpl_getIout(simscapeHDLInstance);
}
