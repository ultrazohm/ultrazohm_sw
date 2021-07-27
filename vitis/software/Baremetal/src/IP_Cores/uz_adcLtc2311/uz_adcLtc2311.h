#ifndef UZ_ADCLTC2311_H
#define UZ_ADCLTC2311_H

// #includes

#include <stdbool.h>
#include <stdint.h>

// defines

// SPI channel defintions
#define UZ_ADCLTC2311_CH1  (1<<0)
#define UZ_ADCLTC2311_CH2  (1<<1)
#define UZ_ADCLTC2311_CH3  (1<<2)
#define UZ_ADCLTC2311_CH4  (1<<3)
#define UZ_ADCLTC2311_CH5  (1<<4)
#define UZ_ADCLTC2311_CH6  (1<<5)
#define UZ_ADCLTC2311_CH7  (1<<6)
#define UZ_ADCLTC2311_CH8  (1<<7)
#define UZ_ADCLTC2311_CH9  (1<<8)
#define UZ_ADCLTC2311_CH10 (1<<9)
#define UZ_ADCLTC2311_CH11 (1<<10)
#define UZ_ADCLTC2311_CH12 (1<<11)
#define UZ_ADCLTC2311_CH13 (1<<12)
#define UZ_ADCLTC2311_CH14 (1<<13)
#define UZ_ADCLTC2311_CH15 (1<<14)
#define UZ_ADCLTC2311_CH16 (1<<15)
#define UZ_ADCLTC2311_CH17 (1<<16)
#define UZ_ADCLTC2311_CH18 (1<<17)
#define UZ_ADCLTC2311_CH19 (1<<18)
#define UZ_ADCLTC2311_CH20 (1<<19)
#define UZ_ADCLTC2311_CH21 (1<<20)
#define UZ_ADCLTC2311_CH22 (1<<21)
#define UZ_ADCLTC2311_CH23 (1<<22)
#define UZ_ADCLTC2311_CH24 (1<<23)
#define UZ_ADCLTC2311_CH25 (1<<24)
#define UZ_ADCLTC2311_CH26 (1<<25)
#define UZ_ADCLTC2311_CH27 (1<<26)
#define UZ_ADCLTC2311_CH28 (1<<27)
#define UZ_ADCLTC2311_CH29 (1<<28)
#define UZ_ADCLTC2311_CH30 (1<<29)
#define UZ_ADCLTC2311_CH31 (1<<30)
#define UZ_ADCLTC2311_CH32 (1<<31)

// SPI master definitions
#define UZ_ADCLTC2311_MASTER1  (1<<0)
#define UZ_ADCLTC2311_MASTER2  (1<<1)
#define UZ_ADCLTC2311_MASTER3  (1<<2)
#define UZ_ADCLTC2311_MASTER4  (1<<3)
#define UZ_ADCLTC2311_MASTER5  (1<<4)
#define UZ_ADCLTC2311_MASTER6  (1<<5)
#define UZ_ADCLTC2311_MASTER7  (1<<6)
#define UZ_ADCLTC2311_MASTER8  (1<<7)
#define UZ_ADCLTC2311_MASTER9  (1<<8)
#define UZ_ADCLTC2311_MASTER10 (1<<9)
#define UZ_ADCLTC2311_MASTER11 (1<<10)
#define UZ_ADCLTC2311_MASTER12 (1<<11)
#define UZ_ADCLTC2311_MASTER13 (1<<12)
#define UZ_ADCLTC2311_MASTER14 (1<<13)
#define UZ_ADCLTC2311_MASTER15 (1<<14)
#define UZ_ADCLTC2311_MASTER16 (1<<15)
#define UZ_ADCLTC2311_MASTER17 (1<<16)
#define UZ_ADCLTC2311_MASTER18 (1<<17)
#define UZ_ADCLTC2311_MASTER19 (1<<18)
#define UZ_ADCLTC2311_MASTER20 (1<<19)
#define UZ_ADCLTC2311_MASTER21 (1<<20)
#define UZ_ADCLTC2311_MASTER22 (1<<21)
#define UZ_ADCLTC2311_MASTER23 (1<<22)
#define UZ_ADCLTC2311_MASTER24 (1<<23)
#define UZ_ADCLTC2311_MASTER25 (1<<24)
#define UZ_ADCLTC2311_MASTER26 (1<<25)
#define UZ_ADCLTC2311_MASTER27 (1<<26)
#define UZ_ADCLTC2311_MASTER28 (1<<27)
#define UZ_ADCLTC2311_MASTER29 (1<<28)
#define UZ_ADCLTC2311_MASTER30 (1<<29)
#define UZ_ADCLTC2311_MASTER31 (1<<30)
#define UZ_ADCLTC2311_MASTER32 (1<<31)

// control register
#define UZ_ADCLTC2311_CR_MODE (1<<0)
#define UZ_ADCLTC2311_CR_TRIGGER (1<<1)
#define UZ_ADCLTC2311_CR_SW_RESET (1<<2)
#define UZ_ADCLTC2311_CR_CONV_VALUE_VALID (1<<3)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_0 (1<<4)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_1 (1<<5)
#define UZ_ADCLTC2311_CR_CONFIG_VALUE_2 (1<<6)

// SPI control register
#define UZ_ADCLTC2311_SPI_CR_SS_N (1<<0)
#define UZ_ADCLTC2311_SPI_CR_SS_N_STATUS (1<<1)
#define UZ_ADCLTC2311_SPI_CR_SCLK (1<<2)
#define UZ_ADCLTC2311_SPI_CR_SCLK_STATUS (1<<3)
#define UZ_ADCLTC2311_SPI_CR_CONTROL (1<<4)
#define UZ_ADCLTC2311_SPI_CR_CONTROL_STATUS (1<<5)
#define UZ_ADCLTC2311_SPI_CR_CPOL (1<<6)
#define UZ_ADCLTC2311_SPI_CR_CPHA (1<<7)

// SPI configuration register
#define UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_WIDTH 16
#define UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_WIDTH 8
#define UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_WIDTH 8
#define UZ_ADCLTC2311_SPI_CFGR_CLK_DIV_LSB 0
#define UZ_ADCLTC2311_SPI_CFGR_PRE_DELAY_LSB 16
#define UZ_ADCLTC2311_SPI_CFGR_POST_DELAY_LSB 24

// status conversion config
#define UZ_ADCLTC2311_SET_CONV_FAILED (1<<0)
#define UZ_ADCLTC2311_SET_OFFSET_FAILED (1<<1)
#define UZ_ADCLTC2311_SET_SAMPLES_FAILED (1<<2)

// status SPI config
#define UZ_ADCLTC2311_CLK_DIV_INVALID (1<<0)
#define UZ_ADCLTC2311_PRE_DELAY_INVALID (1<<0)
#define UZ_ADCLTC2311_POST_DELAY_INVALID (1<<0)

// status napSleepConfig
#define UZ_ADCLTC2311_NS_MAN_MODE_EN_FAILED (1<<0)
#define UZ_ADCLTC2311_NS_MAN_MODE_DIS_FAILED (1<<1)
#define UZ_ADCLTC2311_NS_ALREADY_IN_MODE (1<<2)
#define UZ_ADCLTC2311_NS_NOT_IN_MODE (1<<3)
#define UZ_ADCLTC2311_NS_TIMEOUT (1<<4)
#define UZ_ADCLTC2311_NS_NO_SELECTION (1<<5)
#define UZ_ADCLTC2311_NAP_PULSES 2
#define UZ_ADCLTC2311_SLEEP_PULSES 4

// typedefs
typedef struct uz_adcLtc2311 uz_adcLtc2311;

/**
 * @brief Configuration of the IP core
 *
 * @details
 *
 * Struct to configure the conversion unit of the IP core
 * The function @ref uz_adcLtc2311_configure
 * expects an instance of this struct as configuration.
 *
 * It is highly recommended to initialize the struct with the function
 * @ref uz_adcLtc2311_initConfig. After the initialization, the struct
 * can be customized and given to the function @ref uz_adcLtc2311_configure.
 *
 * The error code variable is one hot encoded.
 * If the following bits are set the appropriate action
 * failed
 *
 * 0: Setting of the conversion factor failed <BR>
 * 1: Setting of the offset failed <BR>
 * 2: Setting of the number of samples failed <BR>
 *
 */
typedef struct uz_adcLtc2311_config {
	uint32_t master_select;
	uint32_t channel_select;
	int32_t conversion_factor;
	int32_t offset;
	uint32_t samples;
	_Bool set_offset;
	_Bool set_conversion;
	_Bool set_samples;
	uint32_t error_code;
	_Bool try_infinite;
	uint32_t max_attempts;

} uz_adcLtc2311_config;

/********************************************************
 * Struct to configure the SPI unit of the IP core
 * The function uz_adcLtc2311_configureSpi(...)
 * expects an instance of this struct as configuration
 *
 * The error code variable is one hot encoded
 * If the following bits are set the appropriate action
 * failed
 *
 * 0: The CLK_DIV value is invalid
 * 1: The PRE_DELAY value is invalid
 * 2: The POST_DELAY value is invalid
 *
 *******************************************************/

/**
 * @brief Configuration of the SPI unit
 *
 * @details
 *
 * Struct to configure the SPI unit of the IP core
 * The function @ref uz_adcLtc2311_configureSpi
 * expects an instance of this struct as configuration
 *
 * It is highly recommended to initialize the struct with the function
 * @ref uz_adcLtc2311_initSpiConfig. After the initialization, the struct
 * can be customized and given to the function @ref uz_adcLtc2311_configureSpi.
 *
 * The error code variable is one hot encoded.
 * If the following bits are set the appropriate action
 * failed
 *
 * 0: The CLK_DIV value is invalid <BR>
 * 1: The PRE_DELAY value is invalid <BR>
 * 2: The POST_DELAY value is invalid <BR>
 *
 */

typedef struct uz_adcLtc2311_spiConfig {
	uint32_t error_code;
	uint32_t pre_delay;
	uint32_t post_delay;
	uint32_t clk_div;
	uint32_t cpha;
	uint32_t cpol;
} uz_adcLtc2311_spiConfig;

/**
 * @brief Configuration to leave and enter nap and sleep mode
 *
 * @details
 *
 * The functions
 *
 * <UL>
 * <LI> @ref uz_adcLtc2311_enterNapMode </LI>
 * <LI> @ref uz_adcLtc2311_leaveNapMode </LI>
 * <LI> @ref uz_adcLtc2311_enterSleepMode </LI>
 * <LI> @ref uz_adcLtc2311_leaveSleepMode </LI>
 * </UL>
 * expect an instance of this struct as configuration.
 *
 * The error code variable is one hot encoded.
 * If the following bits are set the appropriate action
 * failed
 *
 * 0: Enable of the manual control mode for the SPI failed <BR>
 * 1: Disable of the manual control mode for the SPI failed <BR>
 * 2: At least one of the chosen SPI masters is already in sleep
 *    or nap mode <BR>
 * 3: At least one of the chosen SPI masters is not in the requested
 *    mode on leaving the requested mode. <BR>
 * 4: Requested action timed out <BR>
 * 5: No SPI master has been selected <BR>
 *
 *
 */
typedef struct uz_adcLtc2311_napSleepConfig {
	uint32_t error_code; 	/**< This variable contains the error code which is set by the called function */
	uint32_t spi_masters;	/**< Indicates which SPI master shall be selected for the action */
	uint32_t max_attempts;	/**< Maximum AXI read operations to enter the manual SPI control mode if try_infinite is set to false */
	_Bool try_infinite;		/**< If true, the selected action will be tried infinitely */
} uz_adcLtc2311_napSleepConfig;

// function declarations
uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self);

/**
 * @brief Configure the IP core
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_configure(uz_adcLtc2311* self, uz_adcLtc2311_config* configuration);

/**
 * @brief Initialize the struct to configure the IP core
 *
 * @param configuration
 */
void uz_adcLtc2311_initConfig(uz_adcLtc2311_config* configuration);

/**
 * @brief Configure the SPI interface of the IP core
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_configureSpi(uz_adcLtc2311* self, uz_adcLtc2311_spiConfig* configuration);

/**
 * @brief Initialize the struct to configure the IP core
 *
 * @param configuration
 */
void uz_adcLtc2311_initSpiConfig(uz_adcLtc2311_spiConfig* configuration);

/**
 * @brief Reset the IP core. This function has the same effect as applying a low pulse to the
 * RESET_N pin of the IP core.
 *
 * @param self
 */
void uz_adcLtc2311_softwareReset(uz_adcLtc2311* self);

/**
 * @brief Trigger the selected SPI Masters
 *
 * @param self
 * @param spiMasters
 */
void uz_adcLtc2311_softwareTrigger(uz_adcLtc2311* self, uint32_t spiMasters);

/**
 * @brief Enable the continuous sampling mode
 *
 * @param self
 */
void uz_adcLtc2311_setContinuousMode(uz_adcLtc2311* self);

/**
 * @brief Enable the triggered sampling mode
 *
 * @param self
 */
void uz_adcLtc2311_setTriggeredMode(uz_adcLtc2311* self);

/**
 * @brief Enter the nap mode of the selected ADCs
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_enterNapMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration);

/**
 * @brief Leave the nap mode of the selected ADCs
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_leaveNapMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration);

/**
 * @brief Enter the sleep mode of the selected ADCs
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_enterSleepMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration);

/**
 * @brief Leave the sleep mode of the selected ADCs
 *
 * @param self
 * @param configuration
 * @return int32_t
 */
int32_t uz_adcLtc2311_leaveSleepMode(uz_adcLtc2311* self, uz_adcLtc2311_napSleepConfig* configuration);

/**
 * @brief Initialize the struct to for entering and leaving the nap or sleep modes of the ADC
 *
 * @param configuration
 */
void uz_adcLtc2311_initNapSleepConfig(uz_adcLtc2311_napSleepConfig* configuration);

#endif // UZ_ADCLTC2311_H
