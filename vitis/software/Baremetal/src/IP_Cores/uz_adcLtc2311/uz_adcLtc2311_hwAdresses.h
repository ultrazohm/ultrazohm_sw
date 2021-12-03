#ifndef UZ_ADC_LTC2311_HW_ADDRESSES
#define UZ_ADC_LTC2311_HW_ADDRESSES

#define ADC_LTC2311_CR               0x0U  // ADC Control Register
#define ADC_LTC2311_SPI_CR           0x4U  // SPI Control Register
#define ADC_LTC2311_SPI_CFGR         0x8U  // SPI Configuration Register
#define ADC_LTC2311_MASTER_CHANNEL   0xCU  // Master Channel Selection
#define ADC_LTC2311_CHANNEL          0x10U // ADC Channel Selection
#define ADC_LTC2311_MASTER_FINISH    0x14U // Transmission Ended Register
#define ADC_LTC2311_MASTER_SI_FINISH 0x18U // Addition and Multiplication Ended Register
#define ADC_LTC2311_MASTER_BUSY      0x1CU // Conversion Ongoing Register
#define ADC_LTC2311_VALUE            0x20U // Configuration Value Register
#define ADC_LTC2311_ADC_AVAILABLE    0x24U // ADC Available Indicator

#endif
