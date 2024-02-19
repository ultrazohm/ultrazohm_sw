#ifndef UZ_PLATFORM_H
#define UZ_PLATFORM_H

#include <stdint.h>

// (De)Activate UZ auto-platform detection and platform-specific I/O-HAL framework (NB: disabling it turns most of its hooks into failing NOPs...)
#define UZ_PLATFORM_ENABLE	(0U)

// (De)Activate run-time warnings for (currently) unsupported GPIO operations
#define UZ_PLATFORM_OPWARN	(0U)

uint32_t uz_platform_init();
void uz_platform_printinfo();

// GPOs supported by this framework
enum uz_platform_gpo_id {
	I2CLED_FP1RDY = 0, I2CLED_FP2RUN, I2CLED_FP3ERR, I2CLED_FP4USR,
	I2CLED_FPRING,
	RST_PHY0, RST_PHY1,
	I2CLED_UZEXT_LED10, I2CLED_UZEXT_LED11, I2CLED_UZEXT_LED12,
	I2CLED_UZEXT_BEEP1, I2CLED_UZEXT_BEEP2,
	I2CLED_MZD10GREEN, I2CLED_MZD11RED, I2CLED_MZD12YELLOW, I2CLED_MZD13BLUE,
	//// NB: Do not add anything to/below the following line
	UZP_GPO_CNT, UZ_NOGPO = 255 };
// GPO operations (currently not all ops supported on all output drivers, cf. uz_platform.c)
enum uz_platform_gpo_op {
	UZP_GPO_DISABLE2TRISTATED = 0,		// Disable and tri-state the output
	UZP_GPO_ENABLE2PUSHPULLED,			// Enable and actively drive the output
	UZP_GPO_ASSERT,						// Assert output (i.e., high for non-inverted ones)	\ NB: Inversion is not yet
	UZP_GPO_DEASSERT,					// De-assert output (i.e., high for inverted ones)	/     implemented -> TODO!
	UZP_GPO_TOGGLE,						// Toggle output between asserted and de-asserted
	UZP_GPO_ASSERT_QUEUED,
	UZP_GPO_DEASSERT_QUEUED,
	UZP_GPO_TOGGLE_QUEUED,
};

// GPIs supported by this framework
enum uz_platform_gpi_id {
	I2CKEY_FP5ENABLESYS = 0, I2CKEY_FP6ENABLECTL, I2CKEY_FP7EMERGENCYSTOP, I2CKEY_FP8,
	I2CKEY_UZEXT_SW1, I2CKEY_UZEXT_SW2,
	I2CKEY_MZBB_USER,
	//// NB: Do not add anything to/below the following line
	UZP_GPI_CNT, UZ_NOGPI = UZ_NOGPO };

uint32_t uz_platform_gpoupdate();
uint32_t uz_platform_gposet(enum uz_platform_gpo_id uzpgpo_id, enum uz_platform_gpo_op uzpgpo_op);

uint32_t uz_platform_macread(uint8_t eeprom, uint8_t *addr);
uint32_t uz_platform_macread_primary(uint8_t *addrbuf_p);

#endif
