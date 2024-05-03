// "Copyright [year] <Copyright Owner>"
#ifndef UZ_ENDAT_H  // NOLINT
#define UZ_ENDAT_H

// Useful Values to begin with
#define ENDAT_FACTOR_DEFAULT 100
#define ENDAT_FACTOR_DEFAULT2 0
#define ENDAT_FACTOR_1_DEFAULT 100
#define ENDAT_FACTOR_2_DEFAULT 100
#define ENDAT_FACTOR_3_DEFAULT 100
#define ENDAT_FACTOR_4_DEFAULT 100
#define ENDAT_FACTOR_5_DEFAULT 100
#define ENDAT_FACTOR_6_DEFAULT 0
#define ENDAT_FACTOR_7_DEFAULT 0
#define AMOUNT_OF_FACTORS 7
#define ENDAT_CONTROLWORD_DEFAULT 0xA407 //0xB407 //0xB207 //0xA807
#define ENDAT_DIVIDER_DEFAULT 3
#define	ENDAT_23_BIT_MAX_VALUE 0x7FFFFF
#define ENDAT_23_BIT_OUTLIER_VALUE 838860
#define ENDAT_19_BIT_MAX_VALUE 0x7FFFF
#define ENDAT_19_BIT_OUTLIER_VALUE 52428
#define ENDAT_21_BIT_MAX_VALUE 0x1FFFFF
#define ENDAT_21_BIT_OUTLIER_VALUE 209715
#define ENDAT_25_BIT_MAX_VALUE 0x1FFFFFF
#define ENDAT_25_BIT_OUTLIER_VALUE 3355443
#define ENDAT_27_BIT_MAX_VALUE 0x7FFFFFF
#define ENDAT_27_BIT_OUTLIER_VALUE 13421772


#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>



/**
 * @typedef Controlword
 *
 */
typedef uint16_t controlword;
/**
 * @struct Struct for position and age
 *
 */
typedef struct uz_EnDat_pos_with_age_of_pos{
    float pos; /**< Positional Value */
    float age;  /**< Age of this value */
}uz_EnDat_pos_with_age;

/**
 * @enum EnDat Factors to adjust the IP-Core
 *
 */
typedef enum uz_EnDat_factors {
    uz_EnDat_factor1_dataflow,
    uz_EnDat_factor2_recoverytime,
    uz_EnDat_factor3_initialoff,
    uz_EnDat_factor4_data2clksync,
    uz_EnDat_factor5_telegrammlength,
    uz_EnDat_factor6_responsesync,
    uz_EnDat_factor7_extrashift
}uz_EnDat_factor;
/**
 * @enum Positional values
 *
 */
typedef enum uz_EnDat_position_values {
    uz_EnDat_pos_t0,
    uz_EnDat_pos_t1,
    uz_EnDat_pos_t2
}uz_EnDat_position;
/**
 * @enum Elapsed time inbetween positional values
 *
 */
typedef enum uz_EnDat_time_elapsed_values {
    uz_EnDat_elapsed_t0_t1,
    uz_EnDat_elapsed_t0_t2
}uz_EnDat_elapsed;
/**
 * @enum Positional difference for values
 *
 */
typedef enum uz_EnDat_pos_dif_values {
    uz_EnDat_dif_t0_t1,
    uz_EnDat_dif_t0_t2
}uz_EnDat_dif;
/**
 * @typedef Frequency operators
 * @enum uz_EnDat_frequency_selector
 * @ref uz_EnDat_frequency
 */
typedef enum uz_EnDat_frequency_selector {
    uz_EnDat_operatingfrequency_12500000Hz,
    uz_EnDat_operatingfrequency_6250000Hz,
    uz_EnDat_operatingfrequency_3125000Hz,
    uz_EnDat_operatingfrequency_1562500Hz,
    uz_EnDat_operatingfrequency_781250Hz,
    uz_EnDat_operatingfrequency_390625Hz,
    uz_EnDat_operatingfrequency_195312Hz
  }/**Foo it with B*/uz_EnDat_frequency;



 /**
 * @enum Operating mode enumeration as of HDH documentation
 *
 */
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
 * @enum Positional precision setup
 *
 */
typedef enum uz_EnDat_positional_precision {
    uz_EnDat_19_bit,
    uz_EnDat_21_bit,
    uz_EnDat_23_bit,
    uz_EnDat_25_bit,
    uz_EnDat_27_bit
}uz_EnDat_precision;


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
    controlword control; /**< Controlword stored per instance */
    uint8_t divider; /**< Clockdivider stored per instance */
    uint16_t factor1;
    uint16_t factor2;
    uint16_t factor3;
    uint16_t factor4;
    uint16_t factor5;
    uint16_t factor6;
    int16_t factor7;
};

/**
 * @brief EnDat Status Information
 *
 */
struct uz_EnDat_status_t{
    controlword statusword; /**< statusword stored per instance */
    bool errorbit;  /**< errorbit from sensor stored per instance */
};
/**
 * @brief EnDat Object
 *
 */
struct uz_EnDat_t {
    bool is_ready;
    struct uz_EnDat_config_t config;
    struct uz_EnDat_status_t status;
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
 * @brief This function is to write to uz_EnDat - call it with precaution.
 * @return Returns 0 when everything went smooth.
 */
int uz_EnDat_write_control_and_divider_from_object(uz_EnDat_t *self);

/**
 * @param factornumber means which Factor you want to write 
 * @param factor value that you want to write 100 e.g. 1.00 is default for factors 1-5, factors 6&7 are absolute hence default is 0.
 * @brief The following factors are available as of now;
 * @brief uz_EnDat_factor1_dataflow = adjusts the data flow change timing;
 * @brief uz_EnDat_factor2_recoverytime = adjusts the recovery time after a telegramm;
 * @brief uz_EnDat_factor3_initialoff = adjusts the initial silence period length;
 * @brief uz_EnDat_factor4_data2clksync = adjusts the data to clock resync interval;
 * @brief uz_EnDat_factor5_telegrammlength = adjusts the length of the telegram;
 * @brief uz_EnDat_factor6_responsesync = delays the Data in pulses
 * @brief uz_EnDat_factor7_extrashift = alters the shifting behaviour of the response
 * @return Returns the factorvalue written. Returns 9999 if no factor was hit.
 */
int16_t uz_EnDat_write_factor(uz_EnDat_t *self, int16_t factor, uz_EnDat_factor factornumber);

/**
 * @brief This function is to read the status word from the EnDat IP-Core.
 * @return Returns status word as a word from the IP-Core.
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
 * @param mode Sets the EnDat mode - only return position is tested!
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_set_operation_mode(controlword in, uz_EnDat_protocol_opmode mode);

/**
 * 
 * @brief This function normalizes the positional output against 2PI (rad);  
 * @param pos Value which need to be transformed.
 * @param sensorprecision Which kind of EnDat sensor do you connect?
 * @return Returns the positional value in between 0 and 2 pi.
 */
float uz_EnDat_pos_to_rad_converter(uint32_t pos, uz_EnDat_precision sensorprecision);

/**
 * 
 * @brief This function disables the evaluation of the control word in the EnDat IP-Core.  
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_disable_config_evaluation_in_IP(controlword in);


/**
 * 
 * @brief This function enables the evaluation of the control word in the EnDat IP-Core.  
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_enable_config_evaluation_in_IP(controlword in);



/**
 * @param t_x  means which value you would like to fetch. uz_EnDat_pos_t0 to *_t4;
 * @brief This function fetches positional values from the EnDat IP-Core and converts them to rad (2PI) immediately. Precision is auto derived.
 * @return Returns the actual status word from the EnDat IP Core.
 */
float uz_EnDat_read_pos_and_return_radiant(uz_EnDat_t *self, uz_EnDat_position t_x);


/**
 * 
 * @brief This function enables output for EnDat IP-Core. 
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_set_output_enable_in_controlword(controlword in);

/**
 * 
 * @brief This function disables output for EnDat IP-Core. 
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_reset_output_enable_in_controlword(controlword in);


/**
 * @param tx_ty  means which value you would like to fetch. Time elapsed from t0_t1 to t0_t4
 * @brief This function fetches the time elapsed fetching for positional values from the EnDat IP-Core.
 * @return Returns the actual time value from the EnDat IP Core in ns.
 */
uint32_t uz_EnDat_read_time_elapsed(uz_EnDat_t *self, uz_EnDat_elapsed tx_ty);

/**
 * @param elapsed is the Value in ns from the EnDat IP-Core
 * @brief This function converts the ns value to floating point seconds.
 * @return Returns the actual time value elapsed in floating point seconds.
 */
float uz_EnDat_time_elapsed_ns_to_s_converter(uint32_t elapsed);

/**
 * @param pos1 First positional value - can be directly pasted from read pos value.
 * @param pos2 Second positional value - can be directly pasted from read pos value.
 * @param time_elapsed Time between both positions.
 * @param invert Inverts the RPM to negative or positive.
 * @param rawmode Write a 1U for ceedling test - because it disables singularity mitigations.
 * @param sensorprecision Which kind of EnDat sensor do you connect?
 * @brief This function calculate a rotation from two positional values for EnDat.
 * @return Returns the RPM value.
 */
float uz_EnDat_calc_revs_from_pos_delta_and_time(uint32_t pos1, uint32_t pos2, float time_elapsed, uint8_t invert, uz_EnDat_precision sensorprecision, uint8_t rawmode);

/**
 * @param rpm is the revolutions per minute value.
 * @brief This function converts RPM to RAD/S.
 * @return Returns the rotational speed in RAD/S.
 */
float uz_EnDat_rpm_to_rad_per_second_converter(float rpm);

/**
 * @param raw is a float value that you want to smooth out.
 * @param amountofperiods is a value with which you can adjust the smoothening factor.
 * @brief This smoothens float values.
 * @return Returns the smoothed value.
 */
float uz_EnDat_rpm_smoothening(float rawvalue, uint16_t amountofperiods);


/**
 * 
 * @brief This function sets the precision in the controlword of the EnDat IP-Core.  
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_set_sensor_precision_in_controlword(controlword in, uz_EnDat_precision sensorprecision);


/**
 * 
 * @brief This function sets an alternative POS age mode in the IP core.
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_set_alternative_age_mode_in_controlword(controlword in);

/**
 * 
 * @brief This function disables output for EnDat IP-Core. 
 * @param in Controlword to work with.
 * @return Returns the control word modified by this call.
 */
controlword uz_EnDat_reset_alternative_age_mode_in_controlword(controlword in);

/**
 * 
 * @brief This function gets the precision from the controlword of the EnDat IP-Core.  
 * @param in Controlword to work with.
 * @return Returns the precision stored into the control word.
 */
uz_EnDat_precision uz_EnDat_fetch_sensor_precision_from_controlword(controlword in);


/**
 * 
 * @brief This function gets the precision from the object of the EnDat IP-Core.  
 * @param self EnDat Object to work with.
 * @return Returns the precision stored into the EnDat object.
 */
uz_EnDat_precision uz_EnDat_fetch_sensor_precision_from_EnDat_object(uz_EnDat_t *self);

/**
 * 
 * @brief This function fetches the statusword from the EnDat IP-Core.  
 * @param self EnDat Object to work with.
 * @return Returns statusword from the EnDat IP-Core.
 */
controlword uz_EnDat_fetch_statusword_from_EnDat_object(uz_EnDat_t *self);

/**
 * 
 * @brief This function gets the errorbit from the statusword.  
 * @param in Statusword to extract errrobit from.
 * @return Returns the errobit of the sensor from the EnDat object.
 */
bool uz_EnDat_fetch_errorbit_from_statusword(controlword in);

/**
 * 
 * @brief This function gets the precision from the object of the EnDat IP-Core.  
 * @param self EnDat Object to work with.
 *
 */
void uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object(uz_EnDat_t *self);

/**
 * 
 * @brief This function reads the Responselength in bits from the EnDat IP-Core and converts it to float
 * @return Returns the Length of the response information.
 */
float uz_EnDat_read_reponselength_and_convert_to_float(uz_EnDat_t* self);

/**
 * @param dif  means which value you would like to fetch. uz_EnDat_dif_t0_t1 to uz_EnDat_dif_t0_t2
 * @brief This function fetches positional difference from the EnDat IP-Core.
 * @return Returns the actual positional difference from the EnDat IP Core.
 */
int32_t uz_EnDat_read_pos_dif(uz_EnDat_t *self, uz_EnDat_dif dif);

/**
 * @param dif Positional difference value from EnDat IP Core.
 * @param time_elapsed Time between both positions.
 * @param invert Inverts the RPM to negative or positive.
 * @param rawmode Write a 1U for ceedling test - because it disables singularity mitigations.
 * @param sensorprecision Which kind of EnDat sensor do you connect?
 * @brief This alternative function calculate a rotational speed from a positional difference for EnDat.
 * @return Returns the RPM value.
 */
float uz_EnDat_calc_revs_from_fpga_pos_dif_and_time(int32_t dif, float time_elapsed, uint8_t invert, uz_EnDat_precision sensorprecision, uint8_t rawmode);


/**
 * @param compensation  -1 = auto, 0 = off, > 0 Amount of cycles to compensate. 
 * @brief This function fetches positional value t0 from the EnDat IP-Core, convert it to radiant and delivers the age of that value.
 * @return Returns the actual positional value from the EnDat IP Core and the age of that value in s.
 */
uz_EnDat_pos_with_age uz_EnDat_read_pos_t0_as_radiant_and_age(uz_EnDat_t *self, int8_t compensation);

/**
 * @param compensation  -1 = auto, 0 = off, > 0 Amount of cycles to compensate. 
 * @param posorage true = age, false = pos
 * @param update update the underlying value
 * @brief This function fetches positional value t0 from the EnDat IP-Core, convert it to radiant and delivers the age of that value.
 * @return Returns the actual positional value from the EnDat IP Core and the age of that value in s.
 */
float uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper(uz_EnDat_t *self, int8_t compensation, bool posorage, bool update);

/**
 * @param divider converted divider
 * @param freqorperiod true = period, false = freq
 * @brief This function returns either the period or the frequency from the divider value.
 * @return Returns the actual period or frequency in float.
 */
float uz_EnDat_get_clk_frequency_or_period_from_divider(uint8_t divider, bool freqorperiod);

/**
 * @param valuecalctime Time used to calculate a value.
  * @brief This function calculates a quality of sync value based on one second of connection.
 * @return Returnns a precentage value of the sync quality.
 */
float uz_EnDat_calculate_sync_quality_indicator(uz_EnDat_t *self, float valuecalctime);




/* STATUSWORD CONTENT
| Bit |   Description   | Target  | Default |
| --- | :-------------: | :-----: | :-----: |
| 0   |     ModeCom     |   HDH   |    1    |
| 1   |     ModeCom     |   HDH   |    1    |
| 2   |     ModeCom     |   HDH   |    1    |
| 3   |     ModeCom     |   HDH   |    0    |
| 4   |     ModeCom     |   HDH   |    0    |
| 5   |     ModeCom     |   HDH   |    0    |
| 6   |   SENSORERROR   |   HDH   |    0    |
| 7   |     19_Bit      | IP-Core |    0    |
| 8   |     21_Bit      | IP-Core |    0    |
| 9   |     23_Bit      | IP-Core |    1    |
| 10  |     25_Bit      | IP-Core |    0    |
| 11  |     27_bit      | IP-Core |    0    |
| 12  |  Output_Enable  | IP-Core |    0    |
| 13  |  StartContMode  | IP-Core |    0    |
| 14  | StartUpSequence | IP-Core |    0    |
| 15  |   WriteConfig   | IP-Core |    0    |
*/
#endif  // UZ_ENDAT_H  // NOLINT
