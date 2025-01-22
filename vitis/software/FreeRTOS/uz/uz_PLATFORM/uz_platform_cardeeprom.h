#ifndef UZ_PLATFORM_CARDEEPROM_H
#define UZ_PLATFORM_CARDEEPROM_H


//// EEPROM data offset (all systems)
#define UZ_PLATFORM_NONCARRIEREEPROM_INFOOFFSET	(0xF0)


//// EEPROMs of adapter cards (UZohm)
#define UZ_PLATFORM_I2CADDR_UZCARDEEPROM_BASE	(0x50)
#define UZ_PLATFORM_I2CADDR_UZCARDEEPROM_LAST	(0x57)

// Define _enum2label() only when included from uz_platform.c
#ifndef UZ_PLATFORM_C
 #define UZ_NUMENUM_NOHELPER
#endif
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(uz_platform_eeprom_group000models)																	/* Group 0: Adapter cards (in both A and D slots) */ \
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
	ENUMITEM(14,	UZP_HWGROUP_ADCARD_DIGVOLT5, 	"Digital Voltage 5V")										/* ... and *no* \ after the end of the last line! */
#include "../uz_enum/uz_numberedenum.h"


//// EEPROM on MZ-hosting PCB (MZohm)
#define UZ_PLATFORM_I2CADDR_MZHOSTEEPROM_BASE	(UZ_PLATFORM_I2CADDR_UZCARDEEPROM_BASE)
#define UZ_PLATFORM_I2CADDR_MZHOSTEEPROM_ADDR	(2)

// Define _enum2label() only when included from uz_platform.c
#ifndef UZ_PLATFORM_C
 #define UZ_NUMENUM_NOHELPER
#endif
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(uz_platform_eeprom_group003models)																	/* Group 3: MZ */ \
	ENUMITEM( 1,	UZP_HWGROUP_MZ_CARRIER,								"Carrier Board")						/*  */ \
	ENUMITEM( 2,	UZP_HWGROUP_MZ_BREAKOUT,							"Breakout Board")						/* ... and *no* \ after the end of the last line! */
#include "../uz_enum/uz_numberedenum.h"


#endif
