#include "../include/uz_EnDat_IP_Core_init.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_EnDat/uz_EnDat.h"
#include <stdint.h>
#include <stdbool.h>
#include "xparameters.h"

#define XPAR_UZ_USER_UZ_ENDAT_0_IP_CORE_FREQUENCY 100000000U


 uz_EnDat_t* uz_EnDat_IP_core_init(void) {
    uz_EnDat_t* EnDat_init_object;
    struct uz_EnDat_config_t config = {
        .base_address = XPAR_UZ_USER_ADAPTER_D4_UZ_ENDAT_0_BASEADDR,
        .ip_clk_frequency_Hz = XPAR_UZ_USER_UZ_ENDAT_0_IP_CORE_FREQUENCY,
        .control = ENDAT_CONTROLWORD_DEFAULT,
        .divider = ENDAT_DIVIDER_DEFAULT,
        
    };

    EnDat_init_object = uz_EnDat_init(config);
    uz_EnDat_write_default_values(EnDat_init_object);
    uz_EnDat_write_control_and_divider(EnDat_init_object, uz_EnDat_set_output_enable_in_controlword(EnDat_init_object->config.control), EnDat_init_object->config.divider);
    return(EnDat_init_object);
}

uz_EnDat_t* uz_EnDat_IP_core_custom_init(void) {
    uz_EnDat_t* EnDat_temp_ptr = uz_EnDat_IP_core_init();

    EnDat_temp_ptr->config.control = uz_EnDat_set_operation_mode(EnDat_temp_ptr->config.control, uz_EnDat_Encoder_send_position_values);
    //start adjustment if necessary here:
    EnDat_temp_ptr->config.control = uz_EnDat_set_sensor_precision_in_controlword(EnDat_temp_ptr->config.control, uz_EnDat_25_bit);
    EnDat_temp_ptr->config.divider = uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_operatingfrequency_1562500Hz);
    EnDat_temp_ptr->config.factor1 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_1_DEFAULT, uz_EnDat_factor1_dataflow);
    EnDat_temp_ptr->config.factor2 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_2_DEFAULT, uz_EnDat_factor2_recoverytime);
    EnDat_temp_ptr->config.factor3 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_3_DEFAULT, uz_EnDat_factor3_initialoff);
    EnDat_temp_ptr->config.factor4 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_4_DEFAULT, uz_EnDat_factor4_data2clksync);
    EnDat_temp_ptr->config.factor5 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_5_DEFAULT, uz_EnDat_factor5_telegrammlength);
    EnDat_temp_ptr->config.factor6 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_6_DEFAULT, uz_EnDat_factor6_responsesync);
    EnDat_temp_ptr->config.factor7 = uz_EnDat_write_factor(EnDat_temp_ptr, ENDAT_FACTOR_7_DEFAULT+2, uz_EnDat_factor7_extrashift); //+2 should usually work for most odd behaviour
    //stop adjustment above this statement
    EnDat_temp_ptr->config.control = uz_EnDat_enable_config_evaluation_in_IP(EnDat_temp_ptr->config.control);
    EnDat_temp_ptr->config.control = uz_EnDat_set_output_enable_in_controlword(EnDat_temp_ptr->config.control);
    uz_EnDat_write_control_and_divider_from_object(EnDat_temp_ptr);
    return (EnDat_temp_ptr);
}


/*////////////////////////////////////////*/
/*//////////FOR MULTI SENSOR ONLY/////////*/
/*///////////////////////////////////////*/
uz_EnDat_t* uz_EnDat_IP_core_expert_init(uint32_t baseaddress, uint32_t ipcorefreq, int16_t fct1, int16_t fct2, int16_t fct3, int16_t fct4, int16_t fct5, int16_t fct6, int16_t fct7, controlword ctrl, uint8_t dvder) {
    uz_EnDat_t* EnDat_temp_ptr = uz_EnDat_IP_core_init_helper(baseaddress, ipcorefreq);

    EnDat_temp_ptr->config.divider = dvder;
    EnDat_temp_ptr->config.factor1 = uz_EnDat_write_factor(EnDat_temp_ptr, fct1, uz_EnDat_factor1_dataflow);
    EnDat_temp_ptr->config.factor2 = uz_EnDat_write_factor(EnDat_temp_ptr, fct2, uz_EnDat_factor2_recoverytime);
    EnDat_temp_ptr->config.factor3 = uz_EnDat_write_factor(EnDat_temp_ptr, fct3, uz_EnDat_factor3_initialoff);
    EnDat_temp_ptr->config.factor4 = uz_EnDat_write_factor(EnDat_temp_ptr, fct4, uz_EnDat_factor4_data2clksync);
    EnDat_temp_ptr->config.factor5 = uz_EnDat_write_factor(EnDat_temp_ptr, fct5, uz_EnDat_factor5_telegrammlength);
    EnDat_temp_ptr->config.factor6 = uz_EnDat_write_factor(EnDat_temp_ptr, fct6, uz_EnDat_factor6_responsesync);
    EnDat_temp_ptr->config.factor7 = uz_EnDat_write_factor(EnDat_temp_ptr, fct7, uz_EnDat_factor7_extrashift);
    EnDat_temp_ptr->config.control = ctrl;
    uz_EnDat_write_control_and_divider_from_object(EnDat_temp_ptr);
    return (EnDat_temp_ptr);
}

uz_EnDat_t* uz_EnDat_IP_core_init_helper(uint32_t baseaddress, uint32_t ipcorefreq) {
    uz_EnDat_t* EnDat_init_object;
    struct uz_EnDat_config_t config = {
        .base_address = baseaddress,
        .ip_clk_frequency_Hz = ipcorefreq,
        .control = 0x0,
        .divider = 0x0,
        
    };

    EnDat_init_object = uz_EnDat_init(config);
    uz_EnDat_write_default_values(EnDat_init_object);
    uz_EnDat_write_control_and_divider(EnDat_init_object, uz_EnDat_set_output_enable_in_controlword(EnDat_init_object->config.control), EnDat_init_object->config.divider);
    return(EnDat_init_object);
}
