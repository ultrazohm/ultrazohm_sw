#include "uz_axiTestIP2.h"
#include "uz_axiTestIP2_private.h"
#include "uz_axiTestIP2_hw.h"
#include "../../uz/uz_HAL.h"
#include <limits.h>

uz_axiTestIP2* uz_axiTestIP2_init(uz_axiTestIP2* self){
    uz_assert_not_NULL(self);
	uz_assert_not_zero(self->base_address); // Make sure that the base address is set
	uz_assert_false(self->is_ready); // Make sure this instance is not initialized two times
	self->is_ready = true;
	return (self);
}

int uz_axiTestIP2_multiply(uz_axiTestIP2* self, int A, int B){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_axiTestIP2_hw_write_A_int32(self->base_address, A);
    uz_axiTestIP2_hw_write_B_int32(self->base_address, B);
    return (uz_axiTestIP2_hw_read_C_int32(self->base_address));
}