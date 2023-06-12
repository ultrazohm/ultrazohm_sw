#include "uz_PI_controller.h"
#include <stdio.h>

int main(){
	float ref = -1.0f, act = -50.0f, ts = 0.0001f, KI = 0.01f, KP = 10.0f, limit = 10.0f;
	bool reset = false;
	float axi_referenceValue, axi_actualValue, error, P_sum;
	float out[6];

	for(int i=0; i<6; i++){
		out[i] = uz_PI_controller(ref, act, ts, KI, KP, limit, reset, &axi_referenceValue, &axi_actualValue, &error, &P_sum);
		printf("out[%d]=%f\n", i, out[i]);
		printf("axiref: %f, axiactu: %f, axierror: %f\n", axi_referenceValue, axi_actualValue, error);
	}
	return 0;
}
