#ifndef xup_MatrixMulti_HW_H
#define xup_MatrixMulti_HW_H
#include <stdint.h>
#include <stdbool.h>

void xup_MatrixMulti_hw_set_In1_matrix(uint32_t base_address, int * In1);
void xup_MatrixMulti_hw_set_In2_matrix(uint32_t base_address,  int * In2);
void xup_MatrixMulti_hw_set_out_matrix(uint32_t base_address, float *out);
void xup_MatrixMulti_hw_set_start(uint32_t base_address, bool flag);
bool xup_MatrixMulti_hw_get_is_done_output(uint32_t base_address);
bool xup_MatrixMulti_hw_get_is_idle_output(uint32_t base_address);
void xup_MatrixMulti_hw_set_auto_restart(uint32_t base_address, bool auto_restart);
void xup_MatrixMulti_hw_set_dim(uint32_t base_address, int dim);
#endif
