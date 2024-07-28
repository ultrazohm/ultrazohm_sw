#ifndef UZ_ADCMAX11331_H
#define UZ_ADCMAX11331_H
#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"

// #defines

// SPI channel defintions
#define UZ_ADCMAX11331_CH1  (1U<<0)
#define UZ_ADCMAX11331_CH2  (1U<<1)
#define UZ_ADCMAX11331_CH3  (1U<<2)
#define UZ_ADCMAX11331_CH4  (1U<<3)
#define UZ_ADCMAX11331_CH5  (1U<<4)
#define UZ_ADCMAX11331_CH6  (1U<<5)
#define UZ_ADCMAX11331_CH7  (1U<<6)
#define UZ_ADCMAX11331_CH8  (1U<<7)
#define UZ_ADCMAX11331_CH9  (1U<<8)
#define UZ_ADCMAX11331_CH10 (1U<<9)
#define UZ_ADCMAX11331_CH11 (1U<<10)
#define UZ_ADCMAX11331_CH12 (1U<<11)
#define UZ_ADCMAX11331_CH13 (1U<<12)
#define UZ_ADCMAX11331_CH14 (1U<<13)
#define UZ_ADCMAX11331_CH15 (1U<<14)
#define UZ_ADCMAX11331_CH16 (1U<<15)
#define UZ_ADCMAX11331_CH17 (1U<<16)
#define UZ_ADCMAX11331_CH18 (1U<<17)
#define UZ_ADCMAX11331_CH19 (1U<<18)
#define UZ_ADCMAX11331_CH20 (1U<<19)
#define UZ_ADCMAX11331_CH21 (1U<<20)
#define UZ_ADCMAX11331_CH22 (1U<<21)
#define UZ_ADCMAX11331_CH23 (1U<<22)
#define UZ_ADCMAX11331_CH24 (1U<<23)
#define UZ_ADCMAX11331_CH25 (1U<<24)
#define UZ_ADCMAX11331_CH26 (1U<<25)
#define UZ_ADCMAX11331_CH27 (1U<<26)
#define UZ_ADCMAX11331_CH28 (1U<<27)
#define UZ_ADCMAX11331_CH29 (1U<<28)
#define UZ_ADCMAX11331_CH30 (1U<<29)
#define UZ_ADCMAX11331_CH31 (1U<<30)
#define UZ_ADCMAX11331_CH32 (1U<<31)

// SPI master definitions
#define UZ_ADCMAX11331_MASTER1  (1U<<0)
#define UZ_ADCMAX11331_MASTER2  (1U<<1)
#define UZ_ADCMAX11331_MASTER3  (1U<<2)
#define UZ_ADCMAX11331_MASTER4  (1U<<3)
#define UZ_ADCMAX11331_MASTER5  (1U<<4)
#define UZ_ADCMAX11331_MASTER6  (1U<<5)
#define UZ_ADCMAX11331_MASTER7  (1U<<6)
#define UZ_ADCMAX11331_MASTER8  (1U<<7)
#define UZ_ADCMAX11331_MASTER9  (1U<<8)
#define UZ_ADCMAX11331_MASTER10 (1U<<9)
#define UZ_ADCMAX11331_MASTER11 (1U<<10)
#define UZ_ADCMAX11331_MASTER12 (1U<<11)
#define UZ_ADCMAX11331_MASTER13 (1U<<12)
#define UZ_ADCMAX11331_MASTER14 (1U<<13)
#define UZ_ADCMAX11331_MASTER15 (1U<<14)
#define UZ_ADCMAX11331_MASTER16 (1U<<15)
#define UZ_ADCMAX11331_MASTER17 (1U<<16)
#define UZ_ADCMAX11331_MASTER18 (1U<<17)
#define UZ_ADCMAX11331_MASTER19 (1U<<18)
#define UZ_ADCMAX11331_MASTER20 (1U<<19)
#define UZ_ADCMAX11331_MASTER21 (1U<<20)
#define UZ_ADCMAX11331_MASTER22 (1U<<21)
#define UZ_ADCMAX11331_MASTER23 (1U<<22)
#define UZ_ADCMAX11331_MASTER24 (1U<<23)
#define UZ_ADCMAX11331_MASTER25 (1U<<24)
#define UZ_ADCMAX11331_MASTER26 (1U<<25)
#define UZ_ADCMAX11331_MASTER27 (1U<<26)
#define UZ_ADCMAX11331_MASTER28 (1U<<27)
#define UZ_ADCMAX11331_MASTER29 (1U<<28)
#define UZ_ADCMAX11331_MASTER30 (1U<<29)
#define UZ_ADCMAX11331_MASTER31 (1U<<30)
#define UZ_ADCMAX11331_MASTER32 (1U<<31)

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
    pl_trigger=0, /**< Conversion is only triggered by IP-Core PL port -> toDO: This is not implemented so far! */
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
    uint32_t master_select; /**< One hot encoded variable to select the SPI masters that shall be configured. This corresponds to the physical chip. 1 is the first chip, 2 the second chip, ... The original UZ adapter board from Chile has e.g. 6 chips. */
	uint32_t channel_select; /**< One hot encoded variable to select the channels of the selected SPI masters shall be configured. In case of MAX11331, there are 16 channels in case of single-ended and 8 channels in case of differential mode. */
	enum uz_adcMax11331_trigger_mode trigger_mode;

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


// get functions
uint32_t uz_adcMax11331_get_error_code(uz_adcMax11331_t* self);

// SPI parameters
uint32_t uz_adcMax11331_get_clk_div(uz_adcMax11331_t* self);

// Echo messages
/**
 * @brief Select the master from which the error status is read.
 *
 * @param self Pointer to driver instance
 */
void uz_adcMax11331_check_echo_of_master(uz_adcMax11331_t *self);


_Bool uz_adcMax11331_check_32_bit_int_if_msb_not_set(uint32_t value);
_Bool uz_adcMax11331_check_32_bit_int_if_not_more_sign_bits_set_than_spec(uint32_t value, uint32_t spec);



// /*********************************************************************
//  * MAX11331 type definitions, for ADC, daughter board and adapter slot
//  **********************************************************************/
// typedef struct max11331 {
// 	u16 	config_bipolar;
// 	u16 	config_unipolar;
// 	int16_t	Data_raw[8];
// 	float 	Data[8];
// 	int16_t offset[8];
// } MAX11331;

// typedef enum SCLK_freq {f_50MHz=0x01,f_25MHz=0x02,f_16_67MHz=0x03,f_12_5MHz=0x04,f_6_25MHz=0x08,f_low=0x0C} SCLK_freq;
// typedef enum adcstatus {adc_disabled,adc_init,adc_ready,adc_reading_data,adc_error} ADCstatus;

// typedef struct max11331_daughter_board{
// 	// Slot specific parameter
// 	//slot_number slot_id;
// 	const u32 AXI_BASEADDR;
// 	const u32 RESET_MASK;
// 	const u32 ENABLE_MASK;
// 	const u32 TCM_BASEADDR;
// 	// Status & general parameter
// 	ADCstatus status;
// 	SCLK_freq f_clk;
// 	u32 error_counter;
// 	u32 ADC_select;
// 	float conversion_factor;
// 	// ADC data objects
// 	MAX11331 ADC1;
// 	MAX11331 ADC2;
// 	MAX11331 ADC3;
// 	MAX11331 ADC4;
// } MAX11331_Daughter_Board;

// // Declare driver objects to make them globally available
// extern MAX11331_Daughter_Board slot_1;
// extern MAX11331_Daughter_Board slot_2;
// extern MAX11331_Daughter_Board slot_3;

// /*********************************************************************
//  * MAX11331 interface functions declaration
//  *********************************************************************/
// int AnalogAdapter_A2_Initialize();
// //void Config_Daughter_Board(MAX11331_Daughter_Board* slot,SCLK_freq f,u32 ADC_select);
// void Config_Daughter_Board_1(SCLK_freq f, u32 ADC_select);
// void Config_Daughter_Board_2(SCLK_freq f, u32 ADC_select);
// void Config_Daughter_Board_3(SCLK_freq f, u32 ADC_select);
// //void Reset_Daughter_Board(MAX11331_Daughter_Board* slot);
// void Reset_Daughter_Board_1();
// void Reset_Daughter_Board_2();
// void Reset_Daughter_Board_3();
// //void Update_Values(MAX11331_Daughter_Board* slot);
// void Update_Values_Board_1();
// void Update_Values_Board_2();
// void Update_Values_Board_3();
// ADCstatus Board_1_Status();
// ADCstatus Board_2_Status();
// ADCstatus Board_3_Status();

#endif // UZ_ADCMAX11331_H
