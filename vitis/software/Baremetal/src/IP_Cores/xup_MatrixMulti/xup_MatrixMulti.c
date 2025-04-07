#include "xup_MatrixMulti.h"

#include "../../uz/uz_global_configuration.h"
#if XUP_MATRIXMULTI_MULTIPLICATION_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "xup_MatrixMulti_hw.h"

struct xup_MatrixMulti_t {
	bool is_ready;
	struct xup_MatrixMulti_config config;
};

static uint32_t instance_counter = 0U;
static xup_MatrixMulti_t instances[XUP_MATRIXMULTI_MULTIPLICATION_MAX_INSTANCES] = { 0 };

static xup_MatrixMulti_t* xup_MatrixMulti_allocation(void);

static xup_MatrixMulti_t*xup_MatrixMulti_allocation(void){
    uz_assert(instance_counter < XUP_MATRIXMULTI_MULTIPLICATION_MAX_INSTANCES);
    xup_MatrixMulti_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

xup_MatrixMulti_t* xup_MatrixMulti_init(struct xup_MatrixMulti_config config){
	uz_assert_not_zero_uint32(config.base_address);
	xup_MatrixMulti_t* self = xup_MatrixMulti_allocation();
	//Current max size allowed for IP-Core
	self->config = config;
	uz_assert_not_zero(self->is_ready);
	xup_MatrixMulti_hw_set_In1_matrix(self->config.base_address, self->config.In1_data);
	xup_MatrixMulti_hw_set_In2_matrix(self->config.base_address, self->config.In2_data);
	xup_MatrixMulti_hw_set_out_matrix(self->config.base_address, self->config.out_data);
	return(self);
}

void xup_MatrixMulti_trigger_calculation(xup_MatrixMulti_t* self, bool flag) {
	uz_assert_not_NULL(self);
	xup_MatrixMulti_hw_set_start(self->config.base_address, flag);
}


bool xup_MatrixMulti_get_done_flag(xup_MatrixMulti_t* self) {
	uz_assert_not_NULL(self);
	bool is_done = xup_MatrixMulti_hw_get_is_done_output(self->config.base_address);
	return(is_done);
}

bool xup_MatrixMulti_get_idle_flag(xup_MatrixMulti_t* self) {
	uz_assert_not_NULL(self);
	bool is_idle = xup_MatrixMulti_hw_get_is_idle_output(self->config.base_address);
	return(is_idle);
}

void xup_MatrixMulti_set_auto_restart(xup_MatrixMulti_t* self, bool auto_restart) {
	uz_assert_not_NULL(self);
	xup_MatrixMulti_hw_set_auto_restart(self->config.base_address, auto_restart);
}

#endif
