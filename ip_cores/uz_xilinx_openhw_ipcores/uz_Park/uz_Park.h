#include <stdint.h>
#include <math.h>
void multiply(float arg1, float arg2, float *product);
void uz_matrix_multiply(float x1, float x2, float y1, float y2, float *out);
void double_multiply(float x1, float x2, float y1, float y2, float products[2]);
void uz_Park(float in_trafo_alpha, float in_trafo_beta, float in_inv_d, float in_inv_q, float theta_el, float *out_trafo_d, float *out_trafo_q, float *out_inv_alpha, float *out_inv_beta);
