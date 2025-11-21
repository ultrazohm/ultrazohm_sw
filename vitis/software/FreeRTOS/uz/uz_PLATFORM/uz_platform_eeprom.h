#ifndef UZ_PLATFORM_EEPROM_H
#define UZ_PLATFORM_EEPROM_H

#include <stdint.h>

// Definitions for Adapter Card IDs are separate as they shall be part of the user API (cf. uz_platform_cardread() in uz_platform_eeprom.[ch])
#include "uz_platform_cardeeprom.h"		// uz_platform_eeprom_group000models_enum2label()

// Platform EEPROM
#define UZ_PLATFORM_I2CADDR_EEPROM		(0x5BU)
#define UZ_PLATFORM_EEPROM_INFOOFFSET	(0x78U)

enum uz_platform_eeprom_group {
	UZP_HWGROUP_ADCARD =	  0,
	UZP_HWGROUP_UZOHM3 =	  1,
	UZP_HWGROUP_UZOHM6 =	  2,
	UZP_HWGROUP_MZOHM =		  3,
	UZP_HWGROUP_PERIPH =	  4,
	UZP_HWGROUP_MEASBOX =	 10,
	UZP_HWGROUP_MOTORTEST =	 20,
	UZP_HWGROUP_EXTERNAL =	998,
	UZP_HWGROUP_DUMMY	 =	999,
};

#define UZ_PLATFORM_HWMODEL_EXTOFFSET	(500U)

#pragma pack(push,1)
	typedef struct uz_platform_uzpart_variantandserial_ {
		uint8_t  vv;
		uint16_t sn;
	} uz_platform_uzpart_variantandserial;
	typedef struct uz_platform_externalpart_serialonly_ {
		uint32_t sn : 24;
	} uz_platform_externalpart_serialonly;
#pragma pack(pop)

typedef struct uz_platform_eeprom_ {
	enum uz_platform_eeprom_group hw_group : 10;
	uint8_t fflags_model : 6;
	uint16_t hw_model : 10;
	uint8_t fflags_revision : 6;
	uint8_t hw_revision;
	union {
		struct uz_platform_uzpart_variantandserial_ uzhw_variantandserial;
		struct uz_platform_externalpart_serialonly_ externalhw_serialonly;
	} serialdata;
} uz_platform_eeprom;

#define UZ_PLATFORM_HWGROUP_MAX		(1023U)		// 10 bit
#define UZ_PLATFORM_HWMODEL_MAX		(1023U)		// 10 bit
#define UZ_PLATFORM_HWREVISION_MAX	(255U)		//  8 bit
#define UZ_PLATFORM_EXTSERIAL_MAX	(0xFFFFFFU)	// 24 bit

#define UZ_PLATFORM_FFLAGS2STR(STR, FFLAGS)		\
	char STR[7];								\
	uz_platform_fflags2str_helper(STR, FFLAGS, sizeof(STR)/sizeof(STR[0]));
void uz_platform_fflags2str_helper(char *str, uint8_t fflags, size_t size) {
	size--;

	str += size;
	*str = '\0';

	int i;
	for(i=0; i<size; i++)
		*(--str) = (fflags & (1<<i)) ? '1' : '0';
}

// Model FFlags of I²C/SSD/S²C extension board for Rev04-UZ(C)s
#define UZ_PLATFORM_FFSMOD_GRP004MOD003_HOSTSERIAL_MASK	(0b011111)		// S# range: 0001 - 0031
#define UZ_PLATFORM_FFSMOD_GRP004MOD003_PREREV04UZC_BIT (0b100000)		// Set: Older than Rev04

void uz_platform_printhost_group004model003(uint8_t fflags_model) {
	char* hostrev;

	if (fflags_model & UZ_PLATFORM_FFSMOD_GRP004MOD003_PREREV04UZC_BIT)
		hostrev = "Pre-Rev04";
	else
		hostrev = "Rev04";

	uint8_t serial = fflags_model & UZ_PLATFORM_FFSMOD_GRP004MOD003_HOSTSERIAL_MASK;

	uz_printf(" UZ Host ID: %9s, serial %04i\r\n", hostrev, serial);
}

void uz_platform_printinfo(uz_platform_eeprom *eeprom) {
	uz_printf("/=================\\\r\n");
	if (UZP_HWGROUP_EXTERNAL == eeprom->hw_group) {
		uz_printf("Hw group:       Ext\r\n");
	} else {
		uz_printf("Hw group:       %03i\r\n", eeprom->hw_group);
	}

	UZ_PLATFORM_FFLAGS2STR(fflags_model, eeprom->fflags_model)
	uz_printf("Hw model:       %03i (flags %s=0x%02X)\r\n", eeprom->hw_model, fflags_model, eeprom->fflags_model);
	if ( (UZP_HWGROUP_PERIPH == eeprom->hw_group) && (3 == eeprom->hw_model) )
		uz_platform_printhost_group004model003(eeprom->fflags_model);
	if (UZP_HWGROUP_ADCARD == eeprom->hw_group)
		uz_printf(" UZ Card ID: %s\r\n", uz_platform_eeprom_group000models_enum2label(eeprom->hw_model));
	if ( (UZP_HWGROUP_MZOHM == eeprom->hw_group) && (UZP_HWGROUP_MZ_CARRIER != eeprom->hw_model) )
		uz_printf(" MZ Host ID: %s\r\n", uz_platform_eeprom_group003models_enum2label(eeprom->hw_model));

	UZ_PLATFORM_FFLAGS2STR(fflags_revision, eeprom->fflags_revision)
	uz_printf("Hw revision:     %02i (flags %s=0x%02X)\r\n", eeprom->hw_revision, fflags_revision, eeprom->fflags_revision);

	if (UZP_HWGROUP_EXTERNAL == eeprom->hw_group) {
		uz_printf("Ext. serial: %06i\r\n", eeprom->serialdata.externalhw_serialonly.sn);
	} else {
		uz_printf("Hw variant:      %02i\r\n", eeprom->serialdata.uzhw_variantandserial.vv);
		if ( (UZP_HWGROUP_ADCARD == eeprom->hw_group) && (UZP_HWGROUP_ADCARD_DIGOPT == eeprom->hw_model) )
			uz_printf(" Card Setup: %s\r\n", uz_platform_eeprom_group000model004variants_enum2label(eeprom->serialdata.uzhw_variantandserial.vv));
		uz_printf("Hw serial:     %04i\r\n", eeprom->serialdata.uzhw_variantandserial.sn);
	}
	uz_printf("\\=================/\r\n");
}

#endif
