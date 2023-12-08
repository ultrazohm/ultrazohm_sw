
// "Copyright [year] <Copyright Owner>"

#include "uz_EnDat.h"  // NOLINT  
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

static uz_EnDat_t* uz_EnDat_allocation(void) {
    uz_assert(instance_counter < UZ_EnDat_MAX_INSTANCES);
    uz_EnDat_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_EnDat_t* uz_EnDat_init(struct uz_EnDat_config_t config)  {
        uz_assert_not_zero(config.base_address);
        uz_assert_not_zero(config.ip_clk_frequency_Hz);
        uz_EnDat_t* self = uz_EnDat_allocation();
        self->config = config;
        return (self);
    }



int uz_EnDat_write_control_and_divider(uz_EnDat_t* self, uint16_t ctrlword, uint8_t divider) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    if (ctrlword < 1)
        ctrlword = 1;

    if (divider > 6)
    divider = 3;

    uz_EnDat_hw_write_controlword(self->config.base_address, ctrlword);
    uz_EnDat_hw_write_divider(self->config.base_address, divider);


    return(0);
}


int uz_EnDat_write_factor(uz_EnDat_t *self, uint16_t factor, uz_EnDat_factor factornumber) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    switch (factornumber) {
    case uz_EnDat_factor1_dataflow:
    uz_EnDat_hw_write_FKT1DATAFLOW(self->config.base_address, factor);
        break;

    case uz_EnDat_factor2_recoverytime:
    uz_EnDat_hw_write_FKT2RECOVERYTIME(self->config.base_address, factor);
        break;

    case uz_EnDat_factor3_initialoff:
    uz_EnDat_hw_write_FKT3INITIALOFF(self->config.base_address, factor);
    break;
    case uz_EnDat_factor4_data2clksync:
    uz_EnDat_hw_write_FKT4DATACLKSYNC(self->config.base_address, factor);
        break;
    case uz_EnDat_factor5_telegrammlength:
    uz_EnDat_hw_write_FKT5TELEGRAMLEN(self->config.base_address, factor);
        break;
    default:
        return (-1);
        break;
    }


    return (0);
}

uint16_t uz_EnDat_read_statusword(uz_EnDat_t* self) {
    uint16_t ret;
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    ret = uz_EnDat_hw_read_statusword(self->config.base_address);

    return(ret);
}



uint32_t uz_EnDat_read_pos(uz_EnDat_t *self, uz_EnDat_position t_x) {
    uint32_t ret;
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    switch (t_x) {
    case uz_EnDat_pos_t0:
        ret = uz_EnDat_hw_read_POS0BUS(self->config.base_address);
        break;

    case uz_EnDat_pos_t1:
        ret = uz_EnDat_hw_read_POS1BUS(self->config.base_address);
        break;

    case uz_EnDat_pos_t2:
        ret = uz_EnDat_hw_read_POS2BUS(self->config.base_address);
        break;

    case uz_EnDat_pos_t3:
        ret = uz_EnDat_hw_read_POS3BUS(self->config.base_address);
        break;

    case uz_EnDat_pos_t4:
        ret = uz_EnDat_hw_read_POS4BUS(self->config.base_address);
        break;

    default:
        return(0xFFFFFFFF);
        break;
    }
    return(ret);
}




uint8_t uz_EnDat_read_crc(uz_EnDat_t* self) {
    uint8_t ret;
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    ret = uz_EnDat_hw_read_CRCFFSTORED(self->config.base_address);

    return(ret);
}


int uz_EnDat_write_default_values(uz_EnDat_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint8_t i = 0;
    int j = 0;
    for (i = 0 ; i <= AMOUNT_OF_FACTORS-1 ; i++) {
        j = uz_EnDat_write_factor(self, FACTOR_DEFAULT, i);

        if (j ==-1)
        return(j);
    }
    j   =  uz_EnDat_write_control_and_divider(self, CONTROLWORD_DEFAULT, DIVIDER_DEFAULT);

    return(j);
}


uint16_t uz_EnDat_factor_converter(float in) {
    uint32_t i;
    if (in <= 0.00001f)
    return (0u);

    i = floorf(in * 100.0f);

    return ((uint16_t)i);
}

uint16_t uz_EnDat_controlword_builder(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    uint16_t out = 0x0000;
    int i = 0;
    int temp = 0;
    for (i = 0; i <= 15-1; i++) {
        if (*inp[i])
        temp |= (1 << (i));
        else
        temp &= ~(1 << (i));
    }
    out = (uint16_t)temp;
    return (out);
}


uint8_t uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_frequency frequency) {
uint8_t ret = 3U;
    switch (frequency) {
    case uz_EnDat_operatingfrequency_12500000Hz:
        ret = 0U;
        break;

    case uz_EnDat_operatingfrequency_6250000Hz:
        ret = 1U;
        break;

    case uz_EnDat_operatingfrequency_3125000Hz:
        ret = 2U;
        break;

    case uz_EnDat_operatingfrequency_1562500Hz:
        ret = 3U;
        break;

    case uz_EnDat_operatingfrequency_781250Hz:
        ret = 4U;
        break;

    case uz_EnDat_operatingfrequency_390625Hz:
        ret = 5U;
        break;

    case uz_EnDat_operatingfrequency_195312Hz:
        ret = 6U;
        break;
    default:
        return(3U);
        break;
    }
return(ret);
}


int8_t uz_EnDat_set_operation_mode(controlword_expanded* inp, uz_EnDat_protocol_opmode mode) {
    uz_assert_not_NULL(inp);

    switch (mode) {
    case uz_EnDat_Encoder_send_position_values:
        *inp[0] = true;
        *inp[1] = false;
        *inp[2] = true;
        *inp[3] = false;
        *inp[4] = false;
        *inp[5] = false;
            break;

    case uz_EnDat_Encoder_send_position_values_with_additional_data:
        *inp[0] = false;
        *inp[1] = false;
        *inp[2] = false;
        *inp[3] = true;
        *inp[4] = true;
        *inp[5] = true;
        break;

    case uz_EnDat_Selection_of_memory_area:
        *inp[0] = false;
        *inp[1] = true;
        *inp[2] = true;
        *inp[3] = true;
        *inp[4] = false;
        *inp[5] = false;
        break;

    case uz_EnDat_Encoder_send_position_values_and_selection_of_memory_area_or_of_the_additional_data:
        *inp[0] = true;
        *inp[1] = false;
        *inp[2] = false;
        *inp[3] = true;
        *inp[4] = false;
        *inp[5] = false;
        break;

    case uz_EnDat_Encoder_send_parameters:
        *inp[0] = true;
        *inp[1] = true;
        *inp[2] = false;
        *inp[3] = false;
        *inp[4] = false;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_send_position_values_and_send_parameter:
        *inp[0] = false;
        *inp[1] = false;
        *inp[2] = true;
        *inp[3] = false;
        *inp[4] = false;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_receive_parameters:
        *inp[0] = false;
        *inp[1] = false;
        *inp[2] = true;
        *inp[3] = true;
        *inp[4] = true;
        *inp[5] = false;
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_parameter:
        *inp[0] = true;
        *inp[1] = true;
        *inp[2] = false;
        *inp[3] = true;
        *inp[4] = true;
        *inp[5] = false;
        break;

    case uz_EnDat_Encoder_receive_reset:
        *inp[0] = false;
        *inp[1] = true;
        *inp[2] = false;
        *inp[3] = true;
        *inp[4] = false;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_error_reset:
        *inp[0] = true;
        *inp[1] = false;
        *inp[2] = true;
        *inp[3] = true;
        *inp[4] = false;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_receive_test_command:
        *inp[0] = true;
        *inp[1] = false;
        *inp[2] = false;
        *inp[3] = false;
        *inp[4] = true;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_test_command:
        *inp[0] = false;
        *inp[1] = true;
        *inp[2] = true;
        *inp[3] = false;
        *inp[4] = true;
        *inp[5] = true;
        break;

    case uz_EnDat_Encoder_send_test_values:
        *inp[0] = true;
        *inp[1] = false;
        *inp[2] = true;
        *inp[3] = false;
        *inp[4] = true;
        *inp[5] = false;
        break;


    case uz_EnDat_Encoder_receive_communication_command:
        *inp[0] = false;
        *inp[1] = true;
        *inp[2] = true;
        *inp[3] = false;
        *inp[4] = true;
        *inp[5] = false;
        break;
    default:
        return(-1);
        break;
    }
    return(0);
}

float uz_EnDat_pos_to_rad_converter(uint32_t pos) {
    uint32_t endatmax = ENDAT_23_BIT_MAX_VALUE;
    float ret = 0.0f;
    float posconv = 0.0f;
    float tick = 0.0f;
    float max_val = (float) endatmax;  // NOLINT
    tick = ((float) M_PI * 2.0f)/max_val;  // NOLINT
    posconv = (float) pos;  // NOLINT
    ret = posconv * tick;
    return (ret);
}

int8_t uz_EnDat_disable_config_evaluation_in_IP(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[15] = false;
    return(0);
}

int8_t uz_EnDat_enable_config_evaluation_in_IP(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[15] = true;
    return(0);
}

float uz_EnDat_read_pos_and_return_radiant(uz_EnDat_t *self, uz_EnDat_position t_x) {
    uint32_t retraw = 0;
    float retfloat = 0.0f;
    retraw = uz_EnDat_read_pos(self, t_x);
    retfloat = uz_EnDat_pos_to_rad_converter(retraw);
    return(retfloat);
}

int8_t uz_EnDat_reset_soft_reset_in_controlword(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[6] = false;
    return(0);
}

int8_t uz_EnDat_set_soft_reset_in_controlword(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[6] = true;
    return(0);
}


int8_t uz_EnDat_reset_output_enable_in_controlword(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[13] = false;
    return(0);
}

int8_t uz_EnDat_set_output_enable_in_controlword(controlword_expanded* inp) {
    uz_assert_not_NULL(inp);
    *inp[13] = true;
    return(0);
}

float uz_EnDat_mrps_to_rpm_converter(int32_t mrps) {
    float ret = 0.0f;
    float rpmconv = 0.0f;
    rpmconv = ((float) mrps / 1000.0f);
    ret = rpmconv; 
    return (ret);
}

uint32_t uz_EnDat_read_time_elapsed(uz_EnDat_t *self, uz_EnDat_elapsed tx_ty) {
    uint32_t ret;
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    switch (tx_ty) {
    case uz_EnDat_elapsed_t0_t1:
        ret = uz_EnDat_hw_read_TIMEELASPEDT0T1BUS(self->config.base_address);
        break;

    case uz_EnDat_elapsed_t0_t2:
        ret = uz_EnDat_hw_read_TIMEELASPEDT0T2BUS(self->config.base_address);
        break;

    case uz_EnDat_elapsed_t0_t3:
        ret = uz_EnDat_hw_read_TIMEELASPEDT0T3BUS(self->config.base_address);
        break;

    case uz_EnDat_elapsed_t0_t4:
        ret = uz_EnDat_hw_read_TIMEELASPEDT0T4BUS(self->config.base_address);
        break;

    default:
        return(0xFFFFFFFF);
        break;
    }
    return(ret);
}

float uz_EnDat_time_elapsed_ns_to_s_converter(uint32_t elapsed) {
    float ret = 0.0f;
    const float nstos = 1000000000.0f;

    ret = ((float) elapsed / nstos);
    return(ret);
}

float uz_EnDat_calc_revs_from_pos_delta_and_time(uint32_t pos1, uint32_t pos2, float time_elapsed, uint8_t invert) {
    float ret = 0.0f;
    int32_t dif = 0;
    uint32_t maxval = ENDAT_23_BIT_MAX_VALUE;
    int32_t endatnegboundry = ENDAT_23_BIT_HALF_VALUE_NEG;
    int32_t endatposboundry = ENDAT_23_BIT_HALF_VALUE;
    float diff = 0.0f;
    float maxvalf = 0.0f;
    float tick = 0.0f;
    dif = (int32_t)(pos2 - pos1);
    //repair overflow of positional value
    if (dif > endatposboundry) {
       dif -= (int32_t) maxval;

    }
    if (dif < endatnegboundry) {
    	dif += (int32_t) maxval;

    }
    diff = (float) dif;
    maxvalf = (float) maxval;
    tick = (diff / maxvalf);
    ret = (tick / time_elapsed);
    if (invert == 0x1U) {
        ret *= -60.0f;
    }
    else
    {
        ret *= 60.0f;
    }
    return (ret);
}

float uz_EnDat_rpm_to_rad_per_second_converter(float rpm) {
    float ret = 0.0f;
    ret = rpm / 60.0f;
    ret *= ((float) M_PI * 2.0f);
    return (ret);
}

float uz_EnDat_rpm_smoothening(float rawvalue, uint8_t amountofperiods) {
    float ret = 0.0f;
    float periods = (float) amountofperiods;
    ret -= (ret / periods);
    ret += (rawvalue / periods);

    return (ret);
}
#endif  // NOLINT
