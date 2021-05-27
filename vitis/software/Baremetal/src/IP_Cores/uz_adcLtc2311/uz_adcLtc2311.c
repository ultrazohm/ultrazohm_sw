#include "uz_adcLtc2311.h"
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311_private.h"

uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self)
{
    // Check correct initialization
    uz_assert_not_NULL(self);
    uz_assert_false(self->is_ready);
    self->is_ready=true;
    uz_assert_not_zero(self->base_address);
    uz_assert_not_zero(self->ip_clk_frequency_Hz);
    return (self);
}