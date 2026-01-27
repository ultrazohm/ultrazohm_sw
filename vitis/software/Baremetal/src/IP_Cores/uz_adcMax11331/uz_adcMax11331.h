#ifndef UZ_ADCMAX11331_H
#define UZ_ADCMAX11331_H
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

// #defines

// SPI master definitions
#define UZ_ADCMAX11331_MASTER1  (1U<<0)
#define UZ_ADCMAX11331_MASTER2  (1U<<1)
#define UZ_ADCMAX11331_MASTER3  (1U<<2)

// control register
#define UZ_ADCMAX11331_CR_MODE (1U<<0)
#define UZ_ADCMAX11331_CR_SW_TRIGGER_MODE (1U<<1)
#define UZ_ADCMAX11331_CR_TRIGGER (1U<<2)
#define UZ_ADCMAX11331_CR_SW_RESET (1U<<3)
#define UZ_ADCMAX11331_CR_CONV_VALUE_VALID (1U<<4)
#define UZ_ADCMAX11331_CR_CONFIG_VALUE_0 (1U<<5)
#define UZ_ADCMAX11331_CR_CONFIG_VALUE_1 (1U<<6)
#define UZ_ADCMAX11331_CR_CONFIG_VALUE_2 (1U<<7)

// SPI control register
#define UZ_ADCMAX11331_SPI_CR_SS_N (1U<<0)
#define UZ_ADCMAX11331_SPI_CR_SS_N_STATUS (1U<<1)
#define UZ_ADCMAX11331_SPI_CR_SCLK (1U<<2)
#define UZ_ADCMAX11331_SPI_CR_SCLK_STATUS (1U<<3)
#define UZ_ADCMAX11331_SPI_CR_CONTROL (1U<<4)
#define UZ_ADCMAX11331_SPI_CR_CONTROL_STATUS (1U<<5)
#define UZ_ADCMAX11331_SPI_CR_CPOL (1U<<6)
#define UZ_ADCMAX11331_SPI_CR_CPHA (1U<<7)

// SPI configuration register
#define UZ_ADCMAX11331_SPI_CFGR_CLK_DIV_WIDTH 16U

// SPI clock divider
#define UZ_ADCMAX11331_SPI_CLK_50MHZ     0x01
#define UZ_ADCMAX11331_SPI_CLK_25MHZ     0x02
#define UZ_ADCMAX11331_SPI_CLK_16_67MHZ  0x03
#define UZ_ADCMAX11331_SPI_CLK_12_5MHZ   0x04
#define UZ_ADCMAX11331_SPI_CLK_6_25MHZ   0x08
#define UZ_ADCMAX11331_SPI_CLK_test      0x0C
//typedef enum SCLK_freq_t {f_50MHz=0x01,f_25MHz=0x02, f_16_67MHz=0x03,f_12_5MHz=0x04,f_6_25MHz=0x08,f_test=0x0C} SCLK_freq_t;

/**
 * @brief Data type for object adcMax11331
 *
 */
typedef struct uz_adcMax11331_t uz_adcMax11331_t;

/**
 * @brief Enum to determine the trigger mode of a SPI-Master
 *
 */
enum uz_adcMax11331_trigger_mode{
    pl_trigger=0, /**< Conversion is only triggered by IP-Core PL port */
    continuous_trigger, /**< Conversion is triggered continuously with the maximum frequency -> this is the default mode */
};

/**
 * @brief Configuration struct that holds parameters that are adjustable on a per-channel basis
 *
 */
struct uz_adcMax11331_channel_config_t{
	float conversion_factor; /**< Factor with which the sum of the offset and the raw value is multiplied */
	struct uz_fixedpoint_definition_t conversion_factor_definition;
    int offset; /**< Offset that is added to the raw value before the multiplication */
};

/**
 * @brief Configuration struct for adcMax11331
 *
 */
struct uz_adcMax11331_config_t{
    uint32_t base_address; /**< Base address of the IP-Core. No get or set function available */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core. No get or set function available */

    /* Operation parameter */
    uint32_t master_select; /**< One hot encoded variable to select the SPI masters that shall be configured. This corresponds to the physical ADC chip. 1 is the first chip, 2 the second chip, ... The original UZ adapter board has e.g. 3 ADC chips The board from Chile has e.g. 6 ADC chips. */
	enum uz_adcMax11331_trigger_mode trigger_mode;
	uint32_t adc_delay_offset; /**< Offset defined in number of clock cycles. It defines the delay between channel sampling. As more cycles, as longer the ADC waits until the next channel is sampled.*/

    /* SPI */
	uint32_t clk_div; /**< See the SPI configuration register for explanation */
	uint32_t cpha; /**< SPI CPHA. Must be set to 1 for the Max11331 */
	uint32_t cpol; /**< SPI CPOL. Must be set to 1 for the Max11331 */

    /* Error code */
    uint32_t error_code; /**< One-Hot encoded error variable */

    /* Echo messages */

    struct uz_adcMax11331_channel_config_t channel_config;
};

/**
 * @brief Initializes an instance of the adcMax11331
 *
 * @details
 *
 * This function allocates an instance of the IP core and updates the operation
 * parameters that are shipped with the given @ref uz_adcMax11331_config_t configuration struct
 *
 * The function initializes the hardware by executing the following functions:
 *
 * <UL>
 * <LI> @ref uz_adcMax11331_set_clk_div </LI>
 * <LI> @ref uz_adcMax11331_check_echo_of_master </LI>
 * </UL>
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_adcMax11331_t* uz_adcMax11331_init(struct uz_adcMax11331_config_t config);

// SPI parameters
/**
 * @brief Asserts that not to many MSBs are set and that the value fits in the config register.
 *
 * @param self Pointer to driver instance
 * @param value Clock divider to scale the SCLK signal
 */
void uz_adcMax11331_set_clk_div(uz_adcMax11331_t* self, uint32_t value);

/**
 * @brief Asserts that not to many MSBs are set and that the value fits in the config register.
 *
 * @param self Pointer to driver instance
 * @param value Offset defined in number of clock cycles. It defines the delay between channel sampling. As more cycles, as longer the ADC waits until the next channel is sampled.
 */
void uz_adcMax11331_set_delay_offset(uz_adcMax11331_t* self, uint32_t value);

// get functions
uint32_t uz_adcMax11331_get_base_address(uz_adcMax11331_t *self);
uint32_t uz_adcMax11331_get_error_code(uz_adcMax11331_t* self);

// SPI parameters
uint32_t uz_adcMax11331_get_clk_div(uz_adcMax11331_t* self);
uint32_t uz_adcMax11331_get_delay_offset(uz_adcMax11331_t *self);

// Echo messages
/**
 * @brief Select the master from which the error status is read.
 *
 * @param self Pointer to driver instance
 */
void uz_adcMax11331_check_echo_of_master(uz_adcMax11331_t *self);


_Bool uz_adcMax11331_check_32_bit_int_if_msb_not_set(uint32_t value);
_Bool uz_adcMax11331_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec);


#endif // UZ_ADCMAX11331_H
