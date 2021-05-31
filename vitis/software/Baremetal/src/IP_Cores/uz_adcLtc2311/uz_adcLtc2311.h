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
#define UZ_ADCLTC2311_CR_OFF_CONV (1<<4)

// SPI control register
#define UZ_ADCLTC2311_SPI_CR_SS_N (1<<0)
#define UZ_ADCLTC2311_SPI_CR_SS_N_STATUS (1<<1)
#define UZ_ADCLTC2311_SPI_CR_SCLK (1<<2)
#define UZ_ADCLTC2311_SPI_CR_SCLK_STATUS (1<<3)
#define UZ_ADCLTC2311_SPI_CR_CONTROL (1<<4)
#define UZ_ADCLTC2311_SPI_CR_CPOL (1<<5)
#define UZ_ADCLTC2311_SPI_CR_CPHA (1<<6)

// status
#define UZ_ADCLTC2311_SET_CONV_FAILED (1<<0)
#define UZ_ADCLTC2311_SET_OFFSET_FAILED (1<<1)

// typedefs
typedef struct uz_adcLtc2311 uz_adcLtc2311;

/********************************************************
 * Struct to configure the conversion unit of the IP core
 * The function uz_adcLtc2311_configureConversion(...)
 * expects an instance of this struct as configuration
 * 
 * The error code variable is one hot encoded 
 * If the following bits are set the appropriate action
 * failed
 * 
 * 0: Setting of the conversion factor failed
 * 1: Setting of the offset failed
 * 
 *******************************************************/
typedef struct uz_adcLtc2311_conversionConfig
{
    uint32_t master_select;
    uint32_t channel_select;
    int32_t conversion_factor;
    int32_t offset;
    _Bool set_offset;
    _Bool set_conversion;
    uint32_t error_code;
    _Bool try_infinite;
    uint32_t max_attempts;

} uz_adcLtc2311_conversionConfig;

// function declarations
uz_adcLtc2311* uz_adcLtc2311_init(uz_adcLtc2311* self);
uz_adcLtc2311_conversionConfig* uz_adcLtc2311_configureConversion(uz_adcLtc2311* self, uz_adcLtc2311_conversionConfig* configuration);


#endif // UZ_ADCLTC2311_H
