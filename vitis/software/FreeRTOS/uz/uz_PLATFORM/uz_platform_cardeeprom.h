#ifndef UZ_PLATFORM_CARDEEPROM_H
#define UZ_PLATFORM_CARDEEPROM_H


//// EEPROM data offset (all systems)
#define UZ_PLATFORM_NONCARRIEREEPROM_INFOOFFSET	(0xF0U)


//// EEPROMs of adapter cards (UZohm)
#define UZ_PLATFORM_I2CADDR_UZCARDEEPROM_BASE	(0x50U)
#define UZ_PLATFORM_I2CADDR_UZCARDEEPROM_LAST	(0x57U)

// Define _enum2label() only when included from uz_platform.c
#ifndef UZ_PLATFORM_C
 #define UZ_NUMENUM_NOHELPER
#endif
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(uz_platform_eeprom_group000models)																	/* Models in Group 0: Adapter cards (in both A and D slots) */ \
	ENUMITEM( 2,	UZP_HWGROUP_ADCARD_LTC2311,		"ADC LTC2311-16")											/*  */ \
	ENUMITEM( 3,	UZP_HWGROUP_ADCARD_DIGVOLT,		"Digital Voltage 3V3/5V/15V/RS422")							/*  */ \
	ENUMITEM( 4,	UZP_HWGROUP_ADCARD_DIGOPT,	 	"Digital Optical xTX/xRX/xTXyRX")							/*  */ \
	ENUMITEM( 5,	UZP_HWGROUP_ADCARD_DIGRES,	 	"Digital Resolver")											/*  */ \
	ENUMITEM( 6,	UZP_HWGROUP_ADCARD_DIGENC,	 	"Digital Incremental Encoder")								/*  */ \
	ENUMITEM( 7,	UZP_HWGROUP_ADCARD_MAX11331C,	"ADC MAX11331 (CL)")										/*  */ \
	ENUMITEM( 8,	UZP_HWGROUP_ADCARD_MAX11331CD,	"ADC MAX11331 (CL, daughter)")								/*  */ \
	ENUMITEM( 9,	UZP_HWGROUP_ADCARD_MAX11331,	"ADC MAX11331 (24x)")										/*  */ \
	ENUMITEM(10,	UZP_HWGROUP_ADCARD_LTC2983,	 	"Digital Temperature LTC2983")								/*  */ \
	ENUMITEM(11,	UZP_HWGROUP_ADCARD_DIGINV,		"Digital Inverter")											/*  */ \
	ENUMITEM(12,	UZP_HWGROUP_ADCARD_DAC8831,	 	"DAC TI DAC8831")											/*  */ \
	ENUMITEM(13,	UZP_HWGROUP_ADCARD_DIGVOLT33, 	"Digital Voltage 3V3")										/*  */ \
	ENUMITEM(14,	UZP_HWGROUP_ADCARD_DIGVOLT5, 	"Digital Voltage 5V")										/*  */ \
	ENUMITEM(15,	UZP_HWGROUP_ADCARD_DIGVOLT335, 	"Digital Voltage 3V3/5V")									/*  */ \
	ENUMITEM(16,	UZP_HWGROUP_ADCARD_LEDEBUG, 	"Digital LED-Debug")										/*  */ \
	ENUMITEM(17,	UZP_HWGROUP_ADCARD_DIGABSENC,	"Digital Absolute Encoder")									/* ... and *no* \ after the end of the last line! */
#include "../uz_enum/uz_numberedenum.h"

// Variants for Digital Optical TXRX
#ifndef UZ_PLATFORM_C
 #define UZ_NUMENUM_NOHELPER
#endif
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(uz_platform_eeprom_group000model004variants)															/* Variants in Group 0 (Adapter cards), Model 4 (Digital Optical) */ \
	ENUMITEM( 0,	UZP_HWGROUP_ADCARD_DIGOPT_18TX,								"18 TX")						/*  */ \
	ENUMITEM( 1,	UZP_HWGROUP_ADCARD_DIGOPT_18RX,								"18 RX")						/*  */ \
	ENUMITEM( 2,	UZP_HWGROUP_ADCARD_DIGOPT_14TX4RX,							"14 TX / 4 RX")					/* ... and *no* \ after the end of the last line! */
#include "../uz_enum/uz_numberedenum.h"

// Bit masks for I²C GPIO of Digital Voltage 3V3/5V
#define UZP_CARDI2C_DIGVOLT335_GPIO_BASEADDR	(0x20U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_REGIN	(0U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_REGOUT	(1U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_REGCONF	(3U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_IN_VOUT	(0x01U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR1	(0x02U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR2	(0x04U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR3	(0x08U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR4	(0x10U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2R	(0x20U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2G	(0x40U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2B	(0x80U)
#define UZP_CARDI2C_DIGVOLT335_GPIO_INBITS	(UZP_CARDI2C_DIGVOLT335_GPIO_IN_VOUT|UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR1|UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR2|UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR3|UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR4)
#define UZP_CARDI2C_DIGVOLT335_GPIO_OUTBITS	(UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2R|UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2G|UZP_CARDI2C_DIGVOLT335_GPIO_OUT_D2B)

// Define card helpers only when included from uz_platform.c
#ifdef UZ_PLATFORM_C

 void uz_platform_printcard_model015(uint8_t slot, uint8_t data_regin) {
	if ( (slot < 3) || (slot > 7) ) {
		uz_printf("Invalid D slot (%i)\r\n", slot);
		return;
	}
	const uint8_t dslot = slot - 2;

	uz_printf("/=================\\\r\n");
	uz_printf("Hardware configuration of 3V3/5V card in slot D%i:\r\n", dslot);
	uz_printf(" Voltage level of outputs: %s\r\n", (data_regin & UZP_CARDI2C_DIGVOLT335_GPIO_IN_VOUT) ? "3.3V" : "5V");
	uz_printf(" Group 1 (DIG_IO_00 - 07): %s\r\n", (data_regin & UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR1) ? "Output" : "Input");
	uz_printf(" Group 2 (DIG_IO_08 - 15): %s\r\n", (data_regin & UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR2) ? "Output" : "Input");
	uz_printf(" Group 3 (DIG_IO_16 - 23): %s\r\n", (data_regin & UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR3) ? "Output" : "Input");
	uz_printf(" Group 4 (DIG_IO_24 - 29): %s\r\n", (data_regin & UZP_CARDI2C_DIGVOLT335_GPIO_IN_DIR4) ? "Output" : "Input");
	uz_printf("/=================\\\r\n");

	return;
 }

#else
 void uz_platform_printcard_model015(uint8_t slot, uint8_t data_regin);
#endif


//// EEPROM on MZ-hosting PCB (MZohm)
#define UZ_PLATFORM_I2CADDR_MZHOSTEEPROM_BASE	(UZ_PLATFORM_I2CADDR_UZCARDEEPROM_BASE)
#define UZ_PLATFORM_I2CADDR_MZHOSTEEPROM_ADDR	(2U)

// Define _enum2label() only when included from uz_platform.c
#ifndef UZ_PLATFORM_C
 #define UZ_NUMENUM_NOHELPER
#endif
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(uz_platform_eeprom_group003models)																	/* Models in Group 3: MZ */ \
	ENUMITEM( 1,	UZP_HWGROUP_MZ_CARRIER,								"Carrier Board")						/*  */ \
	ENUMITEM( 2,	UZP_HWGROUP_MZ_BREAKOUT,							"Breakout Board")						/* ... and *no* \ after the end of the last line! */
#include "../uz_enum/uz_numberedenum.h"


#endif
