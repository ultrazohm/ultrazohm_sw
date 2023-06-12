#include "uz_SPWM_3ph.h"
void uz_SPWM_3ph(float u_a, float u_b, float u_c, float u_dc, float *DC_a, float *DC_b, float *DC_c){
#pragma HLS INTERFACE mode=ap_none port=u_a
#pragma HLS INTERFACE mode=ap_none port=u_b
#pragma HLS INTERFACE mode=ap_none port=u_c
#pragma HLS INTERFACE mode=ap_none port=u_dc
#pragma HLS INTERFACE mode=ap_none port=DC_a
#pragma HLS INTERFACE mode=ap_none port=DC_b
#pragma HLS INTERFACE mode=ap_none port=DC_c
#pragma HLS DATAFLOW
	SPWM_single_phase(u_a, u_dc, DC_a);
	SPWM_single_phase(u_b, u_dc, DC_b);
	SPWM_single_phase(u_c, u_dc, DC_c);
}

void SPWM_single_phase(float voltage, float u_dc, float *DC){
	float DC_temp = ( (voltage/u_dc) + 0.5f);
	if(DC_temp < 0.0f)
		*DC = 0.0f;
	else if(DC_temp > 1.0f)
		*DC = 1.0f;
	else
		*DC = DC_temp;
}
