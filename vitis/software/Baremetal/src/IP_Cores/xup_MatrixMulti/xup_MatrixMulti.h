#ifndef XUP_MATRIXMULTI_H
#define XUP_MATRIXMULTI_H

#include <stdint.h>
#include <stdbool.h>

typedef struct xup_MatrixMulti_t xup_MatrixMulti_t;

struct xup_MatrixMulti_config{
	 uint32_t base_address;              /**< Base address of the IP-Core */
	 int *In1_data;
	 int *In2_data;
	 int *out_data;
};


xup_MatrixMulti_t* xup_MatrixMulti_init(struct xup_MatrixMulti_config config);
void xup_MatrixMulti_trigger_calculation(xup_MatrixMulti_t* self, bool flag);
bool xup_MatrixMulti_get_done_flag(xup_MatrixMulti_t* self);
bool xup_MatrixMulti_get_idle_flag(xup_MatrixMulti_t* self);
void xup_MatrixMulti_set_auto_restart(xup_MatrixMulti_t* self, bool auto_restart);
void uz_MatrixMulti_set_copy_mats_flag(xup_MatrixMulti_t* self, bool copy_mats_flag);
#endif
