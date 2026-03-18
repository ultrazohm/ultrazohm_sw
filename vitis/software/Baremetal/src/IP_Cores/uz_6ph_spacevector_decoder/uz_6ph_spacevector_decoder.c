#include "uz_6ph_spacevector_decoder.h"



#include "../../uz/uz_global_configuration.h"
#if UZ_SPACEVECTOR_DECODER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_6ph_spacevector_decoder_hw.h"

struct uz_6ph_spacevector_decoder_t {
    bool is_ready;
    struct uz_6ph_spacevector_decoder_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_6ph_spacevector_decoder_t instances[UZ_SPACEVECTOR_DECODER_MAX_INSTANCES] = { 0 };

static uz_6ph_spacevector_decoder_t* uz_6ph_spacevector_decoder_allocation(void);

static uz_6ph_spacevector_decoder_t* uz_6ph_spacevector_decoder_allocation(void){
    uz_assert(instance_counter < UZ_SPACEVECTOR_DECODER_MAX_INSTANCES);
    uz_6ph_spacevector_decoder_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}


uz_6ph_spacevector_decoder_t* uz_6ph_spacevector_decoder_init(struct uz_6ph_spacevector_decoder_config_t config){
    uz_6ph_spacevector_decoder_t* self = uz_6ph_spacevector_decoder_allocation();
    self->config = config;
    return (self);
}

uint32_t uz_6ph_spacevector_decoder_get_spacevector_num(uz_6ph_spacevector_decoder_t* self, unsigned int num){
    uz_assert((num >=1) && (num <= 14));
    switch(num){
        case 1:
            return uz_6ph_spacevector_decoder_hw_read_out1(self->config.base_address);
            break;
        case 2:
            return uz_6ph_spacevector_decoder_hw_read_out2(self->config.base_address);
            break;
        case 3:
            return uz_6ph_spacevector_decoder_hw_read_out3(self->config.base_address);
            break;
        case 4:
            return uz_6ph_spacevector_decoder_hw_read_out4(self->config.base_address);
            break;
        case 5:
            return uz_6ph_spacevector_decoder_hw_read_out5(self->config.base_address);
            break;
        case 6:
            return uz_6ph_spacevector_decoder_hw_read_out6(self->config.base_address);
            break;
        case 7:
            return uz_6ph_spacevector_decoder_hw_read_out7(self->config.base_address);
            break;
        case 8:
            return uz_6ph_spacevector_decoder_hw_read_out8(self->config.base_address);
            break;
        case 9:
            return uz_6ph_spacevector_decoder_hw_read_out9(self->config.base_address);
            break;
        case 10:
            return uz_6ph_spacevector_decoder_hw_read_out10(self->config.base_address);
            break;
        case 11:
            return uz_6ph_spacevector_decoder_hw_read_out11(self->config.base_address);
            break;
        case 12:
            return uz_6ph_spacevector_decoder_hw_read_out12(self->config.base_address);
            break;
        case 13:
            return uz_6ph_spacevector_decoder_hw_read_out13(self->config.base_address);
            break;
        case 14:
            return uz_6ph_spacevector_decoder_hw_read_out14(self->config.base_address);
            break;
        default:
            return 0;
            break;
    }
}

spacevector_decoder_output uz_6ph_spacevector_decoder_get_all_spacevectors(uz_6ph_spacevector_decoder_t* self){
    spacevector_decoder_output output;
    output.sv1 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 1);
    output.sv2 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 2);
    output.sv3 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 3);
    output.sv4 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 4);
    output.sv5 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 5);
    output.sv6 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 6);
    output.sv7 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 7);
    output.sv8 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 8);
    output.sv9 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 9);
    output.sv10 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 10);
    output.sv11 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 11);
    output.sv12 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 12);
    output.sv13 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 13);
    output.sv14 = uz_6ph_spacevector_decoder_get_spacevector_num(self, 14);

    return output;
}



#endif