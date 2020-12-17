//==============================================================================================================================================================
#include "uz_softwareDelay.h"

void uz_SoftwareWaitForCpuClks(int delay){
	Xil_AssertVoid(delay>0);
	Xil_AssertVoid(delay < INT_MAX);
	int x=0;
	int i=0;
	for (i=0;i<delay;i++){
		x=x+0;
	}
}
