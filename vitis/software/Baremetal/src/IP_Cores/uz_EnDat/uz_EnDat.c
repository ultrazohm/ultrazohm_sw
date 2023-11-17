#include "uz_EnDat.h"
#include "uz_EnDat_hw.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_EnDat_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_HAL.h"


struct uz_EnDat_t {
    bool is_ready;
    struct uz_EnDat_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_EnDat_t instances[UZ_EnDat_MAX_INSTANCES] = { 0 };

static uz_EnDat_t* uz_EnDat_allocation(void);

static uz_EnDat_t* uz_EnDat_allocation(void)
{
    uz_assert(instance_counter < UZ_EnDat_MAX_INSTANCES);
    uz_EnDat_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_EnDat_t* uz_EnDat_init(struct uz_EnDat_config_t config)
    {
        uz_assert_not_zero(config.base_address);
        uz_EnDat_t* self = uz_EnDat_allocation();
        self->config=config;
        return (self);
    }
    

void uz_EnDat_write_control_and_divider (uz_EnDat_t* self, uint16_t ctrlword, uint8_t divider)
{

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    
    uz_EnDat_hw_write_controlword(self->config.base_address, ctrlword);
    uz_EnDat_hw_write_divider(self->config.base_address,divider);



}

#endif