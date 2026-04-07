#include "uz_count_switching_IP.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_COUNT_SWITCHING_IP_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_count_switching_hw.h"

struct uz_count_switching_IP_t {
    bool is_ready;
    struct uz_count_switching_IP_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_count_switching_IP_t instances[UZ_COUNT_SWITCHING_IP_MAX_INSTANCES] = { 0 };

static uz_count_switching_IP_t* uz_count_switching_IP_allocation(void);

static uz_count_switching_IP_t* uz_count_switching_IP_allocation(void){
    uz_assert(instance_counter < UZ_COUNT_SWITCHING_IP_MAX_INSTANCES);
    uz_count_switching_IP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_count_switching_IP_t* uz_count_switching_IP_init(struct uz_count_switching_IP_config_t config) {
    uz_count_switching_IP_t* self = uz_count_switching_IP_allocation();
    self->config = config;

    return (self);
}

uint32_t uz_count_switching_IP_get_count(uz_count_switching_IP_t* self, unsigned int num){
    switch(num){
        case 0:
            return uz_count_switching_hw_read_count_0(self->config.base_address);
            break;
        case 1:
            return uz_count_switching_hw_read_count_1(self->config.base_address);
            break;
        case 2:
            return uz_count_switching_hw_read_count_2(self->config.base_address);
            break;
        case 3:
            return uz_count_switching_hw_read_count_3(self->config.base_address);
            break;
        case 4:
            return uz_count_switching_hw_read_count_4(self->config.base_address);
            break;
        case 5:
            return uz_count_switching_hw_read_count_5(self->config.base_address);
            break;
        case 6:
            return uz_count_switching_hw_read_count_6(self->config.base_address);
            break;
        case 7:
            return uz_count_switching_hw_read_count_7(self->config.base_address);
            break;
        case 8:
            return uz_count_switching_hw_read_count_8(self->config.base_address);
            break;
        default:
            return 0;
            break;
    }
}

uint32_t uz_count_switching_IP_get_count_sum(uz_count_switching_IP_t* self){
    return uz_count_switching_hw_read_count_sum(self->config.base_address);
}

void uz_count_switching_IP_set_reset(uz_count_switching_IP_t* self, bool reset){
    uz_count_switching_hw_reset(self->config.base_address,reset);
}


#endif
