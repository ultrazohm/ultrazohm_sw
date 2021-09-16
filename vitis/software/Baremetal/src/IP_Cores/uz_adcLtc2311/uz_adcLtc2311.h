#ifndef UZ_ADCLTC2311_H
#define UZ_ADCLTC2311_H
#include <stdint.h>
#include <stdbool.h>

// #defines

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

/**
 * @brief Data type for object adcLtc2311
 *
 */
typedef struct uz_adcLtc2311_t uz_adcLtc2311_t;

/**
 * @brief Configuration struct for adcLtc2311
 *
 */
struct uz_adcLtc2311_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */

    /* Operation parameter */
    uint32_t master_select; /**< One hot encoded variable to select the SPI masters that shall be configured */
	uint32_t channel_select; /**< One hot encoded variable to select the channels of the selected SPI masters shall be configured */
	int32_t conversion_factor; /**< Factor with which the sum of the offset and the raw value is multiplied */
	int32_t offset; /**< Offset that is added to the raw value before the multiplication */
	uint32_t samples; /**< Number of samples that shall be taken on a single trigger */
    uint32_t sample_time; /**<Minimal number of system clock cycles for sample and hold */
    
    /* SPI */
    uint32_t pre_delay; /**< See the SPI configuration register for explanation */
	uint32_t post_delay; /**< See the SPI configuration register for explanation */
	uint32_t clk_div; /**< See the SPI configuration register for explanation */
	uint32_t cpha; /**< SPI CPHA. Must be set to 0 for the LTC2311 */
	uint32_t cpol; /**< SPI CPOL. Must be set to 1 for the LTC2311 */

    /* Error code */
    uint32_t error_code; /**< One-Hot encoded error variable described above */

    /* Timing */
    _Bool try_infinite; /**< Set to true if the configuration shall not be aborted after a certain number of attempts */
	uint32_t max_attempts; /**< If try_infinite is set to false, the function @ref uz_adcLtc2311_configure tries to configure the IP core with max_attempts */
};

/**
 * @brief Initializes an instance of the adcLtc2311 driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_adcLtc2311_t* uz_adcLtc2311_init(struct uz_adcLtc2311_config_t config);

/**
 * @brief Configures the IP cores with the parameters in the self struct
 * 
 * @param self Configuration values for the IP-Core
 */
void uz_adcLtc2311_configure(uz_adcLtc2311_t* self);

/**
 * @brief Reset the IP core. This function has the same effect as applying a low pulse to the
 * RESET_N pin of the IP core.
 * 
 * @param self 
 */
void uz_adcLtc2311_softwareReset(uz_adcLtc2311_t* self);

/**
 * @brief Trigger the selected SPI Masters
 *
 * @param self
 * @param spiMasters
 */
void uz_adcLtc2311_softwareTrigger(uz_adcLtc2311_t* self);

/**
 * @brief Enable the continuous sampling mode
 *
 * @param self
 */
void uz_adcLtc2311_setContinuousMode(uz_adcLtc2311_t* self);

/**
 * @brief Enable the triggered sampling mode
 *
 * @param self
 */
void uz_adcLtc2311_setTriggeredMode(uz_adcLtc2311_t* self);

// set functions
void uz_adcLtc2311_set_master_select(uz_adcLtc2311_t* self, uint32_t value);
void uz_adcLtc2311_set_channel_select(uz_adcLtc2311_t* self, uint32_t value);
void uz_adcLtc2311_set_conversion_factor(uz_adcLtc2311_t* self, int32_t value);
void uz_adcLtc2311_set_offset(uz_adcLtc2311_t* self, int32_t value);
void uz_adcLtc2311_set_samples(uz_adcLtc2311_t* self, uint32_t value);
void uz_adcLtc2311_set_max_attempts(uz_adcLtc2311_t* self, uint32_t value);

// get functions
uint32_t uz_adcLtc2311_get_master_select(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_channel_select(uz_adcLtc2311_t* self);
int32_t uz_adcLtc2311_get_conversion_factor(uz_adcLtc2311_t* self);
int32_t uz_adcLtc2311_get_offset(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_samples(uz_adcLtc2311_t* self);
uint32_t uz_adcLtc2311_get_max_attempts(uz_adcLtc2311_t* self);

// update functions
int32_t uz_adcLtc2311_update_conversion_factor(uz_adcLtc2311_t* self);

#endif // UZ_ADCLTC2311_H
