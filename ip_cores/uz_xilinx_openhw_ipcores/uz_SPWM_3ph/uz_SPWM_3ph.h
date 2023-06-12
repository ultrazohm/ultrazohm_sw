#include <stdint.h>
#include <math.h>

void SPWM_single_phase(float voltage, float u_dc, float *DC);
void uz_SPWM_3ph(float u_a, float u_b, float u_c, float u_dc, float *DC_a, float *DC_b, float *DC_c);
