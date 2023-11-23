// "Copyright [year] <Copyright Owner>"
#ifndef UZ_ENDAT_H  // NOLINT
#define UZ_ENDAT_H

// Useful Values to begin with

#define FACTOR_DEFAULT 100
#define AMOUNT_OF_FACTORS 5
#define CONTROLWORD_DEFAULT 0xA807
#define DIVIDER_DEFAULT 3
#define	ENDAT_23_BIT_MAX_VALUE 0x7FFFFF

#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>



typedef bool controlword_expanded[16];
typedef enum uz_EnDat_factors {
    uz_EnDat_factor1_dataflow,
    uz_EnDat_factor2_recoverytime,
    uz_EnDat_factor3_initialoff,
    uz_EnDat_factor4_data2clksync,
    uz_EnDat_factor5_telegrammlength
}uz_EnDat_factor;
typedef enum uz_EnDat_position_values {
    uz_EnDat_pos_t0,
    uz_EnDat_pos_t1,
    uz_EnDat_pos_t2,
    uz_EnDat_pos_t3,
    uz_EnDat_pos_t4
}uz_EnDat_position;
typedef enum uz_EnDat_frequency_selector {
    uz_EnDat_operatingfrequency_12500000Hz,
    uz_EnDat_operatingfrequency_6250000Hz,
    uz_EnDat_operatingfrequency_3125000Hz,
    uz_EnDat_operatingfrequency_1562500Hz,
    uz_EnDat_operatingfrequency_781250Hz,
    uz_EnDat_operatingfrequency_390625Hz,
    uz_EnDat_operatingfrequency_195312Hz
  }uz_EnDat_frequency;
typedef enum uz_EnDat_EnDat_operating_mode {
    uz_EnDat_Encoder_send_position_values,
    uz_EnDat_Encoder_send_position_values_with_additional_data,
    uz_EnDat_Selection_of_memory_area,
    uz_EnDat_Encoder_send_position_values_and_selection_of_memory_area_or_of_the_additional_data,
    uz_EnDat_Encoder_send_parameters,
    uz_EnDat_Encoder_send_position_values_and_send_parameter,
    uz_EnDat_Encoder_receive_parameters,
    uz_EnDat_Encoder_send_position_values_and_receive_parameter,
    uz_EnDat_Encoder_receive_reset,
    uz_EnDat_Encoder_send_position_values_and_receive_error_reset,
    uz_EnDat_Encoder_receive_test_command,
    uz_EnDat_Encoder_send_position_values_and_receive_test_command,
    uz_EnDat_Encoder_send_test_values,
    uz_EnDat_Encoder_receive_communication_command
}uz_EnDat_protocol_opmode;


/**
 * @brief Data type for object EnDat
 *
 */
typedef struct uz_EnDat_t uz_EnDat_t;

/**
 * @brief Configuration struct for EnDat
 *
 */
struct uz_EnDat_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the EnDat driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_EnDat_t* uz_EnDat_init(struct uz_EnDat_config_t config);


/**
 * @param ctrlword converted control word
 * @param divider converted divider
 * @brief This function is to write to uz_EnDat - call it with precaution.
 * @return Returns 0 when everything went smooth.
 */
int uz_EnDat_write_control_and_divider(uz_EnDat_t *self, uint16_t ctrlword, uint8_t divider);


/**
 * @param factornumber means which Factor you want to write 
 * @param factor value that you want to write 100 (e.g. 1.00 is default)
 * @brief The following factors are available as of now;
 * @brief uz_EnDat_factor1_dataflow = adjusts the data flow change timing;
 * @brief uz_EnDat_factor2_recoverytime = adjusts the recovery time after a telegramm;
 * @brief uz_EnDat_factor3_initialoff = adjusts the initial silence period length;
 * @brief uz_EnDat_factor4_data2clksync = adjusts the data to clock resync interval;
 * @brief uz_EnDat_factor5_telegrammlength = adjusts the length of the telegram;
 * @return Returns 0 when everything went smooth. Returns -1 if no factor was hit.
 */
int uz_EnDat_write_factor(uz_EnDat_t *self, uint16_t factor, uz_EnDat_factor factornumber);

/**
 * @brief This function is to read the status word from the EnDat IP-Core.
 */
uint16_t uz_EnDat_read_statusword(uz_EnDat_t *self);
/**
 * @param t_x  means which value you would like to fetch. uz_EnDat_pos_t0 to *_t4;
 * @brief This function fetches positional values from the EnDat IP-Core.
 * @return Returns the actual positional value from the EnDat IP Core.
 */
uint32_t uz_EnDat_read_pos(uz_EnDat_t *self, uz_EnDat_position t_x);

/**
 * 
 * @brief This function writes default values to the EnDat IP-Core - use in init.
 * @return Returns 0 when everything went smooth. Returns -1 if something went wrong.
 */
int uz_EnDat_write_default_values(uz_EnDat_t *self);

/**
 * 
 * @brief This helper function converts float input to integer for EnDat IP-Core.
 * @param in Input factor normalized (e.g. 1.00, 1.50, 0.50 etc...)
 * @return Returns converted factor (e.g. 1.00 = 100);
 */
uint16_t uz_EnDat_factor_converter(float in);

/**
 * 
 * @brief This helper function converts a bitfield to a control WORD.
 * @param inp Pointer to a bit array where control word is stored.
 * @return Returns the actual control WORD which can be written to EnDat IP-Core.
 */
uint16_t uz_EnDat_controlword_builder(controlword_expanded* inp);
/**
 * 
 * @brief This helper function converts a frequency setpoint to the appropriate divider. 
 * @param frequency ENUM of selected frequencies. (e.g. uz_EnDat_operatingfrequency_1562500Hz)
 * @return Returns the divider which then can be written to the EnDat IP-Core.
 */
uint8_t uz_EnDat_get_clk_frequency_divider_from_frequency(uz_EnDat_frequency frequency);

/**
 * 
 * @brief This function reads the CRC information from the EnDat IP-Core
 * @return Returns the CRC information.
 */
uint8_t uz_EnDat_read_crc(uz_EnDat_t* self);
/**
 * 
 * @brief This function sets the operation mode part of the control word.  
 * @param inp Pointer to a bit array where control word is stored.
 * @return Returns 0 when everything went smooth. Returns -1 if something went wrong.
 */
int8_t uz_EnDat_set_operation_mode(controlword_expanded* inp, uz_EnDat_protocol_opmode mode);

/**
 * 
 * @brief This function normalizes the positional output against 2PI (rad);  
 * @param pos Value which need to be transformed.
 * @return Returns the positional value in between 0 and 2 pi.
 */
float uz_EnDat_pos_to_rad_converter(uint32_t pos);

/**
 * 
 * @brief This function disables the evaluation of the control word in the EnDat IP-Core.  
 * @param inp Pointer to a bit array where control word is stored.
 * @return Returns 0 when everything went smooth. Returns -1 if something went wrong.
 */
int8_t uz_EnDat_disable_config_evaluation_in_IP(controlword_expanded* inp);


/**
 * 
 * @brief This function enables the evaluation of the control word in the EnDat IP-Core.  
 * @param inp Pointer to a bit array where control word is stored.
 * @return Returns 0 when everything went smooth. Returns -1 if something went wrong.
 */
int8_t uz_EnDat_enable_config_evaluation_in_IP(controlword_expanded* inp);


/**
 * @param t_x  means which value you would like to fetch. uz_EnDat_pos_t0 to *_t4;
 * @brief This function fetches positional values from the EnDat IP-Core and converts them to rad (2PI) immediately.
 * @return Returns the actual status word from the EnDat IP Core.
 */
float uz_EnDat_read_pos_and_return_radiant(uz_EnDat_t *self, uz_EnDat_position t_x);

#endif  // UZ_ENDAT_H  // NOLINT
