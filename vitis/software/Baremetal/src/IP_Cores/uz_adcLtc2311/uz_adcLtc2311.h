#ifndef UZ_ADCLTC2311_H
#define UZ_ADCLTC2311_H
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

// #defines

// SPI channel defintions
#define UZ_ADCLTC2311_CH1  (1U<<0)
#define UZ_ADCLTC2311_CH2  (1U<<1)
#define UZ_ADCLTC2311_CH3  (1U<<2)
#define UZ_ADCLTC2311_CH4  (1U<<3)
#define UZ_ADCLTC2311_CH5  (1U<<4)
#define UZ_ADCLTC2311_CH6  (1U<<5)
#define UZ_ADCLTC2311_CH7  (1U<<6)
#define UZ_ADCLTC2311_CH8  (1U<<7)
#define UZ_ADCLTC2311_CH9  (1U<<8)
#define UZ_ADCLTC2311_CH10 (1U<<9)
#define UZ_ADCLTC2311_CH11 (1U<<10)
#define UZ_ADCLTC2311_CH12 (1U<<11)
#define UZ_ADCLTC2311_CH13 (1U<<12)
#define UZ_ADCLTC2311_CH14 (1U<<13)
#define UZ_ADCLTC2311_CH15 (1U<<14)
#define UZ_ADCLTC2311_CH16 (1U<<15)
#define UZ_ADCLTC2311_CH17 (1U<<16)
#define UZ_ADCLTC2311_CH18 (1U<<17)
#define UZ_ADCLTC2311_CH19 (1U<<18)
#define UZ_ADCLTC2311_CH20 (1U<<19)
#define UZ_ADCLTC2311_CH21 (1U<<20)
#define UZ_ADCLTC2311_CH22 (1U<<21)
#define UZ_ADCLTC2311_CH23 (1U<<22)
#define UZ_ADCLTC2311_CH24 (1U<<23)
#define UZ_ADCLTC2311_CH25 (1U<<24)
#define UZ_ADCLTC2311_CH26 (1U<<25)
#define UZ_ADCLTC2311_CH27 (1U<<26)
#define UZ_ADCLTC2311_CH28 (1U<<27)
#define UZ_ADCLTC2311_CH29 (1U<<28)
#define UZ_ADCLTC2311_CH30 (1U<<29)
#define UZ_ADCLTC2311_CH31 (1U<<30)
#define UZ_ADCLTC2311_CH32 (1U<<31)

// SPI master definitions
#define UZ_ADCLTC2311_MASTER1  (1U<<0)
#define UZ_ADCLTC2311_MASTER2  (1U<<1)
#define UZ_ADCLTC2311_MASTER3  (1U<<2)
#define UZ_ADCLTC2311_MASTER4  (1U<<3)
#define UZ_ADCLTC2311_MASTER5  (1U<<4)
#define UZ_ADCLTC2311_MASTER6  (1U<<5)
#define UZ_ADCLTC2311_MASTER7  (1U<<6)
#define UZ_ADCLTC2311_MASTER8  (1U<<7)
#define UZ_ADCLTC2311_MASTER9  (1U<<8)
#define UZ_ADCLTC2311_MASTER10 (1U<<9)
#define UZ_ADCLTC2311_MASTER11 (1U<<10)
#define UZ_ADCLTC2311_MASTER12 (1U<<11)
#define UZ_ADCLTC2311_MASTER13 (1U<<12)
#define UZ_ADCLTC2311_MASTER14 (1U<<13)
#define UZ_ADCLTC2311_MASTER15 (1U<<14)
#define UZ_ADCLTC2311_MASTER16 (1U<<15)
#define UZ_ADCLTC2311_MASTER17 (1U<<16)
#define UZ_ADCLTC2311_MASTER18 (1U<<17)
#define UZ_ADCLTC2311_MASTER19 (1U<<18)
#define UZ_ADCLTC2311_MASTER20 (1U<<19)
#define UZ_ADCLTC2311_MASTER21 (1U<<20)
#define UZ_ADCLTC2311_MASTER22 (1U<<21)
#define UZ_ADCLTC2311_MASTER23 (1U<<22)
#define UZ_ADCLTC2311_MASTER24 (1U<<23)
#define UZ_ADCLTC2311_MASTER25 (1U<<24)
#define UZ_ADCLTC2311_MASTER26 (1U<<25)
#define UZ_ADCLTC2311_MASTER27 (1U<<26)
#define UZ_ADCLTC2311_MASTER28 (1U<<27)
#define UZ_ADCLTC2311_MASTER29 (1U<<28)
#define UZ_ADCLTC2311_MASTER30 (1U<<29)
#define UZ_ADCLTC2311_MASTER31 (1U<<30)
#define UZ_ADCLTC2311_MASTER32 (1U<<31)

// control register
#define UZ_ADCLTC2311_CR_MODE (1U<<0)
#define UZ_ADCLTC2311_CR_SW_TRIGGER_MODE (1U<<1)
#define UZ_ADCLTC2311_CR_TRIGGER (1U<<2)
#define UZ_ADCLTC2311_CR_SW_RESET (1U<<3)
#define UZ_ADCLTC2311_CR_CONV_VALUE_VALID (1U<<4)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_0 (1U<<5)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_1 (1U<<6)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_2 (1U<<7)

// SPI control register
#define UZ_ADCLTC2311_SPI_CR_SS_N (1U<<0)
#define UZ_ADCLTC2311_SPI_CR_SS_N_STATUS (1U<<1)
#define UZ_ADCLTC2311_SPI_CR_SCLK (1U<<2)
#define UZ_ADCLTC2311_SPI_CR_SCLK_STATUS (1U<<3)
#define UZ_ADCLTC2311_SPI_CR_CONTROL (1U<<4)
#define UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS (1U<<5)
#define UZ_ADCLTC2311_SPI_CR_CPOL (1U<<6)
#define UZ_ADCLTC2311_SPI_CR_CPHA (1U<<7)

// SPI configuration register
#define UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH 16U
#define UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH 8U
#define UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH 8U
#define UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB 0U
#define UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB 16U
#define UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB 24U

// status napSleepConfig
#define UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED (1U<<0)
#define UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED (1U<<1)
#define UZ_ADCLTC2311_NS_ALREADY_IN_MODE (1U<<2)
#define UZ_ADCLTC2311_NS_NOT_IN_MODE (1U<<3)
#define UZ_ADCLTC2311_NS_NO_SELECTION (1U<<4)
#define UZ_ADCLTC2311_NAP_PULSES 2
#define UZ_ADCLTC2311_SLEEP_PULSES 4

/**
 * @brief Data type for object adcLtc2311
 *
 */
typedef struct uz_adcLtc2311_t uz_adcLtc2311_t;

/**
 * @brief Enum to determine the trigger mode of a SPI-Master
 * 
 */
enum uz_adcLtc2311_trigger_mode{
    pl_trigger=0, /**< Conversion is only triggered by IP-Core PL port */
    software_trigger, /**< Conversion is only triggered by software */
    continuous_trigger, /**< Conversion is triggered continuously with the maximum frequency */
};

/**
 * @brief Configuration struct that holds parameters that are adjustable on a per-channel basis
 * 
 */
struct uz_adcLtc2311_channel_config_t{
	float conversion_factor; /**< Factor with which the sum of the offset and the raw value is multiplied */
	struct uz_fixedpoint_definition_t conversion_factor_definition;
    int offset; /**< Offset that is added to the raw value before the multiplication */
};

/**
 * @brief Configuration struct that holds parameters that are adjustable on a per SPI master basis
 * 
 */
struct uz_adcLtc2311_spi_master_config_t{
	uint32_t samples; /**< Number of samples that shall be taken on a single trigger */
    uint32_t sample_time; /**<Minimal number of system clock cycles for sample and hold */
    enum uz_adcLtc2311_trigger_mode trigger_mode;
};

/**
 * @brief Configuration struct for adcLtc2311
 *
 */
struct uz_adcLtc2311_config_t{
    uint32_t base_address; /**< Base address of the IP-Core. No get or set function available */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core. No get or set function available */

    /* Operation parameter */
    uint32_t master_select; /**< One hot encoded variable to select the SPI masters that shall be configured */
	uint32_t channel_select; /**< One hot encoded variable to select the channels of the selected SPI masters shall be configured */

    /* SPI */
    uint32_t pre_delay; /**< See the SPI configuration register for explanation */
	uint32_t post_delay; /**< See the SPI configuration register for explanation */
	uint32_t clk_div; /**< See the SPI configuration register for explanation */
	uint32_t cpha; /**< SPI CPHA. Must be set to 0 for the LTC2311 */
	uint32_t cpol; /**< SPI CPOL. Must be set to 1 for the LTC2311 */

    /* Error code */
    uint32_t error_code; /**< One-Hot encoded error variable if the usage of nap or sleep mode fails */

    /* Timing */
	uint32_t max_attempts; /**< If non zero, the update of the operation parameters is tried max_attempts times. Otherwise it is tried infinitely (default) */

    /* Nap and Sleep mode */
    uint32_t sleeping_spi_masters;
    uint32_t napping_spi_masters;

    struct uz_adcLtc2311_spi_master_config_t spi_master_config;
    struct uz_adcLtc2311_channel_config_t channel_config;
};

/**
 * @brief Initializes an instance of the adcLtc2311
 * 
 * @details
 * 
 * This function allocates an instance of the IP core and updates the operation
 * parameters that are shipped with the given @ref uz_adcLtc2311_config_t configuration struct
 * 
 * The function initializes the hardware by executing the following functions:
 * 
 * <UL>
 * <LI> @ref uz_adcLtc2311_set_triggered_mode </LI>
 * <LI> @ref uz_adcLtc2311_update_conversion_factor </LI>
 * <LI> @ref uz_adcLtc2311_update_offset </LI>
 * <LI> @ref uz_adcLtc2311_update_samples </LI>
 * <LI> @ref uz_adcLtc2311_update_sample_time </LI>
 * <LI> @ref uz_adcLtc2311_update_spi </LI>
 * </UL>
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_adcLtc2311_t* uz_adcLtc2311_init(struct uz_adcLtc2311_config_t config);

/**
 * @brief Reset the IP core. This function has the same effect as applying a low pulse to the
 * RESET_N pin of the IP core.
 * 
 */
void uz_adcLtc2311_software_reset(uz_adcLtc2311_t* self);

/**
 * @brief Trigger the selected SPI Masters.
 *
 * @param self Pointer to driver instance
 * @param spi_masters If non zero, the argument is interpreted as a binary mask which masters shall be triggered.
 *                    If zero, the master_select value from @ref uz_adcLtc2311_config_t is considered instead.
 */
void uz_adcLtc2311_software_trigger(uz_adcLtc2311_t* self, uint32_t spi_masters);

/**
 * @brief Enable the continuous sampling mode
 * 
 * @param self Pointer to driver instance
 */
void uz_adcLtc2311_set_continuous_mode(uz_adcLtc2311_t* self);

/**
 * @brief Enable the triggered sampling mode
 * 
 * @param self Pointer to driver instance
 */
void uz_adcLtc2311_set_triggered_mode(uz_adcLtc2311_t* self);

/**
 * @brief In triggered mode: The IP core is triggered by software via AXI
 * 
 * @param self Pointer to driver instance
 */
void uz_adcLtc2311_set_software_trigger_mode(uz_adcLtc2311_t* self);

/**
 * @brief In triggered mode: The IP core is triggered by hardware through the PL pin
 * 
 * @param self Pointer to driver instance
 */
void uz_adcLtc2311_set_pl_trigger_mode(uz_adcLtc2311_t* self);

// update functions

/**
 * @brief Update the conversion factor of the indicated channels
 * 
 * @param self Pointer to driver instance 
 * 
 * @return UZ_FAILURE when the hardware did not acknowledge the update of the value within max_attempts. 
 *         Otherwise, the function returns UZ_SUCCESS.
 */
uint32_t uz_adcLtc2311_update_conversion_factor(uz_adcLtc2311_t* self);

/**
 * @brief Update the offset of the indicated channels
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE when the hardware did not acknowledge the update of the value within max_attempts. 
 *         Otherwise, the function returns UZ_SUCCESS.
 */
uint32_t uz_adcLtc2311_update_offset(uz_adcLtc2311_t* self);

/**
 * @brief Update the samples per trigger event of the indicated channels
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE when the hardware did not acknowledge the update of the value within max_attempts. 
 *         Otherwise, the function returns UZ_SUCCESS.
 */
uint32_t uz_adcLtc2311_update_samples(uz_adcLtc2311_t* self);

/**
 * @brief Update the sample time of the indicated channels
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE when the hardware did not acknowledge the update of the value within max_attempts. 
 *         Otherwise, the function returns UZ_SUCCESS.
 */
uint32_t uz_adcLtc2311_update_sample_time(uz_adcLtc2311_t* self);

/**
 * @brief Updates the global SPI configuration of the IP core.
 * 
 * @param self Pointer to driver instance
 */
void uz_adcLtc2311_update_spi(uz_adcLtc2311_t* self);

// Entering and leaving of Nap and Sleep mode

/**
 * @brief Send the selected channels to nap mode
 * 
 * @details
 * 
 * The function depends on the master_select and the max_attempts setting
 * in @ref uz_adcLtc2311_config_t. master_select determines, which channels are sent to nap mode and
 * max_attempts determines the maximum number of attempts to enter the manual
 * control mode of the SPI. Adjust these settings before calling the function.
 * 
 * \#defines for the error_code variable in case of failure are located in the
 * uz_adcLtc2311.h file (public interface of this software module).
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE if the operation failed. Check the error_code from
 *         @ref uz_adcLtc2311_config_t for details. Otherwise, return value is
 *         UZ_SUCCESS
 */
uint32_t uz_adcLtc2311_enter_nap_mode(uz_adcLtc2311_t* self);

/**
 * @brief Return the selected channels from nap mode to operation mode
 * 
 * @details
 * 
 * The function depends on the master_select and the max_attempts setting
 * in @ref uz_adcLtc2311_config_t. master_select determines, which channels leave nap mode and
 * max_attempts determines the maximum number of attempts to enter the manual
 * control mode of the SPI. Adjust these settings before calling the function.
 * 
 * \#defines for the error_code variable in case of failure are located in the
 * uz_adcLtc2311.h file (public interface of this software module).
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE if the operation failed. Check the error_code from
 *         @ref uz_adcLtc2311_config_t for details. Otherwise, return value is
 *         UZ_SUCCESS
 */
uint32_t uz_adcLtc2311_leave_nap_mode(uz_adcLtc2311_t* self);

/**
 * @brief Send the selected channels to sleep mode
 * 
 * @details
 * 
 * The function depends on the master_select and the max_attempts setting
 * in @ref uz_adcLtc2311_config_t. master_select determines, which channels are sent to sleep mode and
 * max_attempts determines the maximum number of attempts to enter the manual
 * control mode of the SPI. Adjust these settings before calling the function.
 * 
 * \#defines for the error_code variable in case of failure are located in the
 * uz_adcLtc2311.h file (public interface of this software module).
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE if the operation failed. Check the error_code from
 *         @ref uz_adcLtc2311_config_t for details. Otherwise, return value is
 *         UZ_SUCCESS
 */
uint32_t uz_adcLtc2311_enter_sleep_mode(uz_adcLtc2311_t* self);

/**
 * @brief Return the selected channels from sleep mode to operation mode
 * 
 * @details
 * 
 * The function depends on the master_select and the max_attempts setting
 * in @ref uz_adcLtc2311_config_t. master_select determines, which channels leave sleep mode and
 * max_attempts determines the maximum number of attempts to enter the manual
 * control mode of the SPI. Adjust these settings before calling the function.
 * After the datasheet of the LTC2311, one must wait 10ms before operating the ADC again
 * after exiting the sleep mode. This is not performed by this function. The user needs
 * to take care about this.
 * 
 * \#defines for the error_code variable in case of failure are located in the
 * uz_adcLtc2311.h file (public interface of this software module).
 * 
 * @param self Pointer to driver instance
 * 
 * @return UZ_FAILURE if the operation failed. Check the error_code from
 *         @ref uz_adcLtc2311_config_t for details. Otherwise, return value is
 *         UZ_SUCCESS
 */
uint32_t uz_adcLtc2311_leave_sleep_mode(uz_adcLtc2311_t* self);

// set functions
void uz_adcLtc2311_set_master_select(uz_adcLtc2311_t* self, uint32_t value);
void uz_adcLtc2311_set_channel_select(uz_adcLtc2311_t* self, uint32_t value);

void uz_adcLtc2311_set_conversion_factor(uz_adcLtc2311_t* self, float value, struct uz_fixedpoint_definition_t fixedpoint_definition);
void uz_adcLtc2311_set_offset(uz_adcLtc2311_t* self, int value);

/**
 * @brief Set the number of samples taken per trigger event. Asserts that the value is in a valid range.
 * 
 * @param self Pointer to driver instance
 * @param value Number of samples taken per trigger event. Min: 1 Max: (2^31)-1 = 2147483647
 */
void uz_adcLtc2311_set_samples(uz_adcLtc2311_t* self, uint32_t value);
void uz_adcLtc2311_set_max_attempts(uz_adcLtc2311_t* self, uint32_t value);

/**
 * @brief Set the minimum number of system clock cycles between two samples. 
 * 
 * @details
 * 
 * In this period, the sample and hold capacitor of the ADC is charged. The appropriate time depends on the driving 
 * strength of the signal. Asserts that the value is in a valid range.
 * 
 * @param self Pointer to driver instance
 * @param value Minimum number of system clock cycles that the SS_N signal stays high. Max: (2^31)-1 = 2147483647
 */
void uz_adcLtc2311_set_sample_time(uz_adcLtc2311_t* self, uint32_t value);

// SPI parameters
/**
 * @brief Asserts that not to many MSBs are set and that the value fits in the config register.
 * 
 * @param self Pointer to driver instance
 * @param value Number of system clock cycles for the PRE_DELAY
 */
void uz_adcLtc2311_set_pre_delay(uz_adcLtc2311_t* self, uint32_t value);

/**
 * @brief Asserts that not to many MSBs are set and that the value fits in the config register.
 * 
 * @param self Pointer to driver instance
 * @param value Number of system clock cycles for the POST_DELAY
 */
void uz_adcLtc2311_set_post_delay(uz_adcLtc2311_t* self, uint32_t value);

/**
 * @brief Asserts that not to many MSBs are set and that the value fits in the config register.
 * 
 * @param self Pointer to driver instance
 * @param value Clock devider to scale the SCLK signal
 */
void uz_adcLtc2311_set_clk_div(uz_adcLtc2311_t* self, uint32_t value);

/**
 * @brief Set the edge, on which edge the first bit is sampled. Must be the first edge (a.k.a. CPHA = 0) for the LTC2311.
 *        Asserts, that the value is 0.
 * 
 * @param self Pointer to driver instance
 * @param value If 0, the first bit is sampled on the first edge of SCLK. If non 0, the first bit is sampled on the second
 *              edge of SCLK.
 */
void uz_adcLtc2311_set_cpha(uz_adcLtc2311_t* self, uint32_t value);

/**
 * @brief Determines the IDLE state of SCLK. Must be the logic high (a.k.a. CPOL = 1) for the LTC2311.
 *        Asserts, that the value is non 0.
 * 
 * @param self Pointer to driver instance
 * @param value If 0, the IDLE state of SCLK is 0. If non 0, the IDLE state of SCLK is 1.
 */
void uz_adcLtc2311_set_cpol(uz_adcLtc2311_t* self, uint32_t value);


// get functions
uint32_t uz_adcLtc2311_get_error_code(uz_adcLtc2311_t* self);

// operation parameters
uint32_t uz_adcLtc2311_get_master_select(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_channel_select(uz_adcLtc2311_t* self);
float uz_adcLtc2311_get_conversion_factor(uz_adcLtc2311_t* self);
int32_t uz_adcLtc2311_get_offset(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_samples(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_max_attempts(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_sample_time(uz_adcLtc2311_t* self);

// SPI parameters
uint32_t uz_adcLtc2311_get_pre_delay(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_post_delay(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_clk_div(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_cpha(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_cpol(uz_adcLtc2311_t* self);

// Nap and Sleep mode
uint32_t uz_adcLtc2311_get_napping_masters(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_sleeping_masters(uz_adcLtc2311_t* self);




// do not use this function, only for internal use:
void uz_adcLtc2311_set_trigger_mode(uz_adcLtc2311_t *self);

/**
 * @brief Wrapper function to set the conversion factor and offset of specified channels of one or multiple SPI-Masters in a single function call
 * 
 * @param self Pointer to driver instance
 * @param master_select Bitmask to select SPI-Masters - use UZ_ADCLTC2311_MASTER defines
 * @param channel_select Bitmask to select ADC-Channels - use UZ_ADCLTC2311_CH32 defines 
 * @param channel_config Config struct that is written to the IP-Core to change offset and conversion factor
 */
void uz_adcLtc2311_set_channel_config(uz_adcLtc2311_t* self, uint32_t master_select, uint32_t channel_select,  struct uz_adcLtc2311_channel_config_t channel_config);

/**
 * @brief Wrapper function to set the trigger mode for the driver instance.
 * 
 * @param self Pointer to driver instance
 * @param trigger_mode 
 */
void uz_adcLtc2311_change_trigger_mode(uz_adcLtc2311_t *self, enum uz_adcLtc2311_trigger_mode trigger_mode);


#endif // UZ_ADCLTC2311_H
