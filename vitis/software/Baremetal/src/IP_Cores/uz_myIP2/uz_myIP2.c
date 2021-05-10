#include "uz_myIP2.h"
#include "../../uz/uz_HAL.h"
#include "uz_myIP2_private.h"
#include "uz_myIP2_hw.h"

uz_myIP2* uz_myIP2_init(uz_myIP2* self){
    uz_assert_not_NULL(self);
    uz_assert_not_zero(self->base_address);
    uz_assert_not_zero(self->ip_clk_frequency_Hz);
    uz_assert_false(self->is_ready);
    self->is_ready=true;
    return (self);
}

int32_t uz_myIP2_multiply(uz_myIP2* self, int32_t A, int32_t B){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_myIP2_hw_write_A(self->base_address,A);
    uz_myIP2_hw_write_B(self->base_address,B);
    return (uz_myIP2_hw_read_C(self->base_address));
}