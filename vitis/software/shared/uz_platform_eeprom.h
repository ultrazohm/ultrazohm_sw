#ifndef UZ_PLATFORM_EEPROM_H
#define UZ_PLATFORM_EEPROM_H

#include <stdint.h>

#define UZ_PLATFORM_I2CADDR_EEPROM		(0x5B)
#define UZ_PLATFORM_EEPROM_INFOOFFSET	(0x78)

enum uz_platform_eeprom_group {
	UZP_HWGROUP_ADCARD =	000,
	UZP_HWGROUP_UZOHM3 =	001,
	UZP_HWGROUP_UZOHM6 =	002,
	UZP_HWGROUP_MZOHM =		003,
	UZP_HWGROUP_EXTERNAL =	998,
	UZP_HWGROUP_DUMMY	 =	999,
};

#define UZ_PLATFORM_HWMODEL_EXTOFFSET	(500U)

#pragma pack(push,1)
	typedef struct uz_platform_batchandserial_ {
		uint8_t  batch;
		uint16_t serial;
	} uz_platform_batchandserial;
	typedef struct uz_platform_externalserial_ {
		uint32_t extserial : 24;
	} uz_platform_externalserial;
#pragma pack(pop)

typedef struct uz_platform_eeprom_ {
	enum uz_platform_eeprom_group hw_group : 10;
	uint8_t fflags_model : 6;
	uint16_t hw_model : 10;
	uint8_t fflags_revision : 6;
	uint8_t hw_revision;
	union {
		struct uz_platform_batchandserial_ hw_batchandserial;
		struct uz_platform_externalserial_ hw_externalserial;
	} serialdata;
} uz_platform_eeprom;

#define UZ_PLATFORM_HWGROUP_MAX		(1023U)		// 10 bit
#define UZ_PLATFORM_HWMODEL_MAX		(1023U)		// 10 bit
#define UZ_PLATFORM_HWREVISION_MAX	(255U)		//  8 bit
#define UZ_PLATFORM_EXTSERIAL_MAX	(0xFFFFFF)	// 24 bit

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

void uz_platform_printinfo(uz_platform_eeprom *eeprom) {
	uz_printf("/=================\\\r\n");
	if (UZP_HWGROUP_EXTERNAL == eeprom->hw_group) {
		uz_printf("Hw group:       Ext\r\n");
	} else {
		uz_printf("Hw group:       %03i\r\n", eeprom->hw_group);
	}

	UZ_PLATFORM_FFLAGS2STR(fflags_model, eeprom->fflags_model)
	uz_printf("Hw model:       %03i (flags %s=0x%02X)\r\n", eeprom->hw_model, fflags_model, eeprom->fflags_model);

	UZ_PLATFORM_FFLAGS2STR(fflags_revision, eeprom->fflags_revision)
	uz_printf("Hw revision:     %02i (flags %s=0x%02X)\r\n", eeprom->hw_revision, fflags_revision, eeprom->fflags_revision);

	if (UZP_HWGROUP_EXTERNAL == eeprom->hw_group) {
		uz_printf("Ext. serial: %06i\r\n", eeprom->serialdata.hw_externalserial.extserial);
	} else {
		uz_printf("Hw batch:        %02i\r\n", eeprom->serialdata.hw_batchandserial.batch);
		uz_printf("Hw serial:     %04i\r\n", eeprom->serialdata.hw_batchandserial.serial);
	}
	uz_printf("\\=================/\r\n");
}

#endif
