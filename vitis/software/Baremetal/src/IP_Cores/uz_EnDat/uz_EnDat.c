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
        uz_assert_not_zero(config.ip_clk_frequency_Hz);
        uz_EnDat_t* self = uz_EnDat_allocation();
        self->config=config;
        return (self);
    }
    

int uz_EnDat_write_control_and_divider (uz_EnDat_t* self, uint16_t ctrlword, uint8_t divider)
{

    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    
    if (ctrlword <1) 
        ctrlword = 1;
    if (divider <1)
        divider = 1;

    uz_EnDat_hw_write_controlword(self->config.base_address, ctrlword);
    uz_EnDat_hw_write_divider(self->config.base_address,divider);


    return(0);
}

int uz_EnDat_write_factor(uz_EnDat_t* self, uint16_t factor, uint8_t num)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    if (factor <1)
    factor = 1;
    
    switch (num)
    {
    
    case 1:
        uz_EnDat_hw_write_FKT1DATAFLOW(self->config.base_address,factor);
        break;
    
    case 2:
        uz_EnDat_hw_write_FKT2RECOVERYTIME(self->config.base_address,factor);
        break;

    case 3:
        uz_EnDat_hw_write_FKT3INITIALOFF(self->config.base_address,factor);
        break;
    case 4:
        uz_EnDat_hw_write_FKT4DATACLKSYNC(self->config.base_address,factor);
        break;
    case 5:
        uz_EnDat_hw_write_FKT5TELEGRAMLEN(self->config.base_address,factor);
        break;
    default:
        return (-1);
        break;
        
    return (0);
    }



}

uint16_t uz_EnDat_read_statusword(uz_EnDat_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);


    
}


#endif