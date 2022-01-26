#include "../../uz/uz_global_configuration.h"
#if UZ_ERROR_HANDLER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_errorhandler.h"
#include "uz_errorhandler_hw.h"

struct uz_errorhandler_t {
    bool is_ready;
     struct uz_errorhandler_config_t config;
};

static size_t instance_counter = 0U;
static uz_errorhandler_t instances[UZ_ERROR_HANDLER_MAX_INSTANCES] = { 0 };

static uz_errorhandler_t* uz_errorhandler_allocation(void);

static uz_errorhandler_t* uz_errorhandler_allocation(void){
    uz_assert(instance_counter < UZ_ERROR_HANDLER_MAX_INSTANCES);
    uz_errorhandler_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_errorhandler_t *uz_errorhandler_init(struct uz_errorhandler_config_t config)
{
    uz_assert_not_zero(config.base_address);
//    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_errorhandler_t *self = uz_errorhandler_allocation();
    self->config = config;
    return (self);
}

void uz_errorhandler_setError(uz_errorhandler_t *self, int32_t error)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_errorhandler_hw_write_ERROR(self->config.base_address, error);
}
int32_t uz_errorhandler_getError(uz_errorhandler_t* self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_errorhandler_hw_read_ERROR(self->config.base_address));
}

void uz_errorhandler_setMask(uz_errorhandler_t *self, int32_t mask)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_errorhandler_hw_write_MASK(self->config.base_address, mask);
}
int32_t uz_errorhandler_getMask(uz_errorhandler_t* self)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return (uz_errorhandler_hw_read_MASK(self->config.base_address));
}

#endif
