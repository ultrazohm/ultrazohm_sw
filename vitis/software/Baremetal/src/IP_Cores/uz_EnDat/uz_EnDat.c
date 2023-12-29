
// "Copyright [year] <Copyright Owner>"

#include "uz_EnDat.h"  // NOLINT  
#include "uz_EnDat_hw.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_EnDat_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_HAL.h"



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
        uz_assert_not_zero(config.control);
        uz_assert_not_zero(config.divider);
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

int uz_EnDat_write_control_and_divider_from_object(uz_EnDat_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_EnDat_write_control_and_divider(self, self->config.control, self->config.divider);
    return(0);
}

int uz_EnDat_write_factor(uz_EnDat_t *self, int16_t factor, uz_EnDat_factor factornumber) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    switch (factornumber) {
    case uz_EnDat_factor1_dataflow:
    uz_EnDat_hw_write_FKT1DATAFLOW(self->config.base_address, (uint16_t) factor);
        break;

    case uz_EnDat_factor2_recoverytime:
    uz_EnDat_hw_write_FKT2RECOVERYTIME(self->config.base_address, (uint16_t) factor);
        break;

    case uz_EnDat_factor3_initialoff:
    uz_EnDat_hw_write_FKT3INITIALOFF(self->config.base_address, (uint16_t) factor);
        break;

    case uz_EnDat_factor4_data2clksync:
    uz_EnDat_hw_write_FKT4DATACLKSYNC(self->config.base_address, (uint16_t) factor);
        break;

    case uz_EnDat_factor5_telegrammlength:
    uz_EnDat_hw_write_FKT5TELEGRAMLEN(self->config.base_address, (uint16_t) factor);
        break;
    
    case uz_EnDat_factor6_responsesync:
    uz_EnDat_hw_write_FKT6SYNCRESPONSE(self->config.base_address, (uint16_t) factor);
        break;
    
    case uz_EnDat_factor7_extrashift:
    uz_EnDat_hw_write_FKT7EXTRASHIFT(self->config.base_address, (int8_t) factor);
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
        if (i < 6) {
        j = uz_EnDat_write_factor(self, FACTOR_DEFAULT, i);
        }
        else {
        j = uz_EnDat_write_factor(self, FACTOR_DEFAULT2, i);    
        }

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


controlword uz_EnDat_set_operation_mode(controlword in, uz_EnDat_protocol_opmode mode) {
    controlword out = in;

    switch (mode) {
    case uz_EnDat_Encoder_send_position_values:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 5);

        break;

    case uz_EnDat_Encoder_send_position_values_with_additional_data:
        out  |= ((controlword)1 << 3);
        out  |= ((controlword)1 << 4);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 2);
        
        break;

    case uz_EnDat_Selection_of_memory_area:
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 5);
        
        break;

    case uz_EnDat_Encoder_send_position_values_and_selection_of_memory_area_or_of_the_additional_data:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 5);
        
        break;

    case uz_EnDat_Encoder_send_parameters:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 4);
        
        break;

    case uz_EnDat_Encoder_send_position_values_and_send_parameter:
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 4);
        
        break;

    case uz_EnDat_Encoder_receive_parameters:
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 3);
        out  |= ((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 5);
        
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_parameter:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 3);
        out  |= ((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 5);
        
        break;

    case uz_EnDat_Encoder_receive_reset:
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 3);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 4);
        
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_error_reset:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 3);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 4);
        
        break;

    case uz_EnDat_Encoder_receive_test_command:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 4);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 3);
        
        break;

    case uz_EnDat_Encoder_send_position_values_and_receive_test_command:
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 4);
        out  |= ((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 3);
        
        break;

    case uz_EnDat_Encoder_send_test_values:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 2);
        out  |= ((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 1);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 5);
        
        break;


    case uz_EnDat_Encoder_receive_communication_command:
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 0);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 5);
        out  &= (controlword)~((controlword)1 << 2);
        
        break;
    default:
        out  |= ((controlword)1 << 0);
        out  |= ((controlword)1 << 1);
        out  |= ((controlword)1 << 2);
        out  &= (controlword)~((controlword)1 << 3);
        out  &= (controlword)~((controlword)1 << 4);
        out  &= (controlword)~((controlword)1 << 5);
        break;
    }
    return(out);
}

float uz_EnDat_pos_to_rad_converter(uint32_t pos, uz_EnDat_precision sensorprecision) {
    uint32_t endatmax = 0;

    switch (sensorprecision) {
    case uz_EnDat_19_bit:
        endatmax = ENDAT_19_BIT_MAX_VALUE;
        break;

    case uz_EnDat_21_bit:
        endatmax = ENDAT_21_BIT_MAX_VALUE;
        break;

    case uz_EnDat_23_bit:
        endatmax = ENDAT_23_BIT_MAX_VALUE;
        break;

    case uz_EnDat_25_bit:
        endatmax = ENDAT_25_BIT_MAX_VALUE;
        break;

    case uz_EnDat_27_bit:
        endatmax = ENDAT_27_BIT_MAX_VALUE;
        break;

    default:
        endatmax = ENDAT_23_BIT_MAX_VALUE;
        break;
    }


    float ret = 0.0f;
    float posconv = 0.0f;
    float tick = 0.0f;
    float max_val = (float) endatmax;  // NOLINT
    tick = ((float) M_PI * 2.0f)/max_val;  // NOLINT
    posconv = (float) pos;  // NOLINT
    ret = posconv * tick;
    return (ret);
}

controlword uz_EnDat_disable_config_evaluation_in_IP(controlword in) {
    controlword out = in;
    out  &= (controlword)~((controlword)1 << 15);
    return(out);
}


controlword uz_EnDat_enable_config_evaluation_in_IP(controlword in) {
    controlword out = in;
    out  |= ((controlword)1 << 15);
    return(out);
}


float uz_EnDat_read_pos_and_return_radiant(uz_EnDat_t *self, uz_EnDat_position t_x) {
    uint32_t retraw = 0;
    float retfloat = 0.0f;
    uz_EnDat_precision sensorprecision = uz_EnDat_fetch_sensor_precision_from_EnDat_object(self);
    retraw = uz_EnDat_read_pos(self, t_x);
    retfloat = uz_EnDat_pos_to_rad_converter(retraw, sensorprecision);
    return(retfloat);
}


controlword uz_EnDat_reset_output_enable_in_controlword(controlword in) {
    controlword out = in;
    out  &= (controlword)~((controlword)1 << 12);
    return(out);
}

controlword uz_EnDat_set_output_enable_in_controlword(controlword in) {
    controlword out = in;
    out  |= ((controlword)1 << 12);
    return(out);
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

float uz_EnDat_calc_revs_from_pos_delta_and_time(uint32_t pos1, uint32_t pos2, float time_elapsed, uint8_t invert, uz_EnDat_precision sensorprecision, uint8_t testmode) {
    float ret = 0.0f;
    static float retold = 1.0f;
    int32_t dif = 0;
    uint32_t difabs = 0U;
    uint32_t difoldabs = 0U;
    static int32_t difold = 1;
    float diff = 0.0f;
    float maxvalf = 0.0f;
    float tick = 0.0f;
    uint32_t maxval = 0;
    int32_t endatnegboundry = 0;
    int32_t endatposboundry = 0;

    switch (sensorprecision) {
    case uz_EnDat_19_bit:
        maxval = ENDAT_19_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_19_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_19_BIT_OUTLIER_VALUE;
        break;

    case uz_EnDat_21_bit:
        maxval = ENDAT_21_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_21_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_21_BIT_OUTLIER_VALUE;
        break;

    case uz_EnDat_23_bit:
        maxval = ENDAT_23_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_23_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_23_BIT_OUTLIER_VALUE;
        break;

    case uz_EnDat_25_bit:
        maxval = ENDAT_25_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_25_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_25_BIT_OUTLIER_VALUE;
        break;

    case uz_EnDat_27_bit:
        maxval = ENDAT_27_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_27_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_27_BIT_OUTLIER_VALUE;
        break;

    default:
        maxval = ENDAT_23_BIT_MAX_VALUE;
        endatnegboundry = ENDAT_23_BIT_OUTLIER_VALUE_NEG;
        endatposboundry = ENDAT_23_BIT_OUTLIER_VALUE;
        break;
    }

    dif = (int32_t)(pos2 - pos1);
    //mitigation of singularity events
    if (testmode == 0x0U) {
    if (dif < 0) {
        difabs = (uint32_t )(dif * -1);
    }
    else {
        difabs = (uint32_t) dif;
    }
    if (difold < 0) {
        difoldabs = (uint32_t) (difold * -1);
    }
    else {
        difoldabs = (uint32_t) difold;
    }
    //mitigation of singularity events
    if ((dif > endatposboundry) || (dif < endatnegboundry) || ((difabs > (difoldabs * 1000)))) {
        dif = difold;
    }
    }
    
    diff = (float) dif;
    maxvalf = (float) maxval;
    tick = (diff / maxvalf);
    ret = (tick / time_elapsed);
    //mitigation of singularity events
    if (testmode == 0x0U) {
    if (((ret < 0.00001f) && (ret > -0.00001f)) || (fabsf(ret)-fabsf(retold)) > (fabsf(retold) * 10.0f)) {
        return (retold);
    }
    }

    if (invert == 0x1U) {
        ret *= -60.0f;
    }
    else {
        ret *= 60.0f;
    }
    
    difold = dif;
    retold = ret;
    return (ret);
}

float uz_EnDat_rpm_to_rad_per_second_converter(float rpm) {
    float ret = 0.0f;
    ret = rpm / 60.0f;
    ret *= ((float) M_PI * 2.0f);
    return (ret);
}

float uz_EnDat_rpm_smoothening(float rawvalue, uint16_t amountofperiods) {
    static float ret = 0.0f;
    float periods = (float) amountofperiods;
    ret -= (ret / periods);
    ret += (rawvalue / periods);

    return (ret);
}

controlword uz_EnDat_set_sensor_precision_in_controlword(controlword in, uz_EnDat_precision sensorprecision) {
    controlword out = in;

    switch (sensorprecision) {
    case uz_EnDat_19_bit:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 7);
        break;

    case uz_EnDat_21_bit:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 8);
        break;

    case uz_EnDat_23_bit:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 9);
        break;

    case uz_EnDat_25_bit:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 10);
        break;

    case uz_EnDat_27_bit:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 11);
        break;

    default:
        out  &= (controlword)~((controlword)31 << 7);
        out  |= ((controlword)1 << 9);
        break;
    }
    
    return(out);
}

uz_EnDat_precision uz_EnDat_fetch_sensor_precision_from_controlword(controlword in) {
    uz_EnDat_precision out = uz_EnDat_23_bit;
    controlword temp = in;
    temp  &= (controlword)~((controlword)15 << 12);
    temp  &= (controlword)~((controlword)127 << 0);

    switch (temp) {
    case 0x0080:
        out = uz_EnDat_19_bit;
        break;

    case 0x0100:
        out = uz_EnDat_21_bit;
        break;

    case 0x0200:
        out = uz_EnDat_23_bit;
        break;

    case 0x0400:
        out = uz_EnDat_25_bit;
        break;

    case 0x0800:
        out = uz_EnDat_27_bit;
        break;

    default:
        out = uz_EnDat_23_bit;
        break;
    }
    return(out);
}

uz_EnDat_precision uz_EnDat_fetch_sensor_precision_from_EnDat_object(uz_EnDat_t *self) {
    uz_assert_not_NULL(self);
    uz_EnDat_precision out;

    out = uz_EnDat_fetch_sensor_precision_from_controlword(self->config.control);
    return (out);
}

controlword uz_EnDat_fetch_statusword_from_EnDat_object(uz_EnDat_t *self) {
    uz_assert_not_NULL(self);
    controlword statusout;
    statusout = uz_EnDat_read_statusword(self);

    return(statusout);
}

bool uz_EnDat_fetch_errorbit_from_statusword(controlword in) {
    bool out;
    controlword temp = in;
    temp  &= (controlword)~((controlword)511 << 7);
    temp  &= (controlword)~((controlword)63 << 0);

    if (temp == 0x40U) {
        out = true;
    }
    else if ((temp != 0x40U)) {
        out = false;
    }
    
    return(out);
}

void uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object(uz_EnDat_t *self) {
    uz_assert_not_NULL(self);
    self->status.statusword = uz_EnDat_fetch_statusword_from_EnDat_object(self);
    self->status.errorbit = uz_EnDat_fetch_errorbit_from_statusword(self->status.statusword);
}
#endif  // NOLINT
