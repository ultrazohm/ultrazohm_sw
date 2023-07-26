#include "../uz_HAL.h"

#include "uz_platform.h"
#include "uz_platform_eeprom.h"
#include "../uz_IIC/uz_iic.h"
#include "uz_platform_gpiops.h"

#define UZ_PLATFORM_SCLK_RATEKHZ	(400U)

//// Bus instance ID (currently fixed to 0 and bound to PS I²C *1*)
#define UZ_PLATFORM_I2CBUS_INSTID	(0U)
//// Slave addresses (currently fixed, but code ready for dynamic assignment)
/// NB: UZ_PLATFORM_I2CADDR_EEPROM is defined in uz_platform_eeprom.h
// 16-bit I/O expander (PCA....)
#define UZ_PLATFORM_I2CADDR_GPIO	(0x20)
// EEPROMs with MAC addresses for Ethernet
#define UZ_PLATFORM_I2CADDR_MACEE0	(0x50)		// On SoM or(/and!) on the extension board for UZ Rev04
#define UZ_PLATFORM_I2CADDR_MACEE1	(0x52)		// On UZ >=Rev05 or on the extension board for UZ Rev04

typedef enum uz_platform_gpiodrv_ {
	UZP_GPIOTYPE_I2C = 0,
	UZP_GPIOTYPE_PS,
	// Add additional GPIO types/channels here (without assigning an integer value)
	// NB: Do not add anything to/below the following line
	UZP_GPIOTYPE_CNT, UZP_GPIOTYPE_NOGPIO = UZ_NOGPO
} uz_platform_gpiodrv;

#define UZ_PLATFORM_GPIO_UNAVAILABLE	{ UZP_GPIOTYPE_NOGPIO, UZP_GPIOTYPE_NOGPIO }

typedef struct uz_platform_gpX_ {
	enum uz_platform_gpiodrv_ gpX2drv : 8;
	uint8_t gpX2pin;
} uz_platform_gpo;

typedef struct uz_platform_iomap_ {
	struct uz_platform_gpX_ gpo[UZP_GPO_CNT];
	struct uz_platform_gpX_ gpi[UZP_GPI_CNT];
} uz_platform_iomap;

typedef struct uz_platform_ {
	_Bool is_ready;

	uz_platform_iomap *iomap;

	uz_iic eeprom;
	uz_platform_eeprom data;

	uz_iic maceeprom[2];

	uz_iic gpioi2c;
	uint16_t gpioi2c_outmirror;

	XGpioPs gpiops;
} uz_platform;

#if (UZ_PLATFORM_ENABLE==1)
 static uz_platform_iomap uzp_iomap_UltraZohmRev04withExtensionBoardRev02 = {
	{
		// Cf. uz_platform_gpo_id in uz_platform.h:
		{UZP_GPIOTYPE_I2C,  0},			// I2CLED_FP1RDY
		{UZP_GPIOTYPE_I2C,  1},			// I2CLED_FP2RUN
		{UZP_GPIOTYPE_I2C,  2},			// I2CLED_FP3ERR
		{UZP_GPIOTYPE_I2C,  3},			// I2CLED_FP4USR
		{UZP_GPIOTYPE_I2C,  4},			// I2CLED_FPRING
		{UZP_GPIOTYPE_PS,  26},			// RST_PHY0
		{UZP_GPIOTYPE_PS,  27},			// RST_PHY1
		{UZP_GPIOTYPE_I2C,  5},			// I2CLED_UZEXT_LED10
		{UZP_GPIOTYPE_I2C,  6},			// I2CLED_UZEXT_LED11
		{UZP_GPIOTYPE_I2C,  7},			// I2CLED_UZEXT_LED12
		{UZP_GPIOTYPE_I2C, 12},			// I2CLED_UZEXT_BEEP1
		{UZP_GPIOTYPE_I2C, 13},			// I2CLED_UZEXT_BEEP2
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_MZD10GREEN
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_MZD11RED
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_MZD12YELLOW
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_MZD13BLUE		- NB: IO7 <-> M2
	},{
		// Cf. uz_platform_gpi_id in uz_platform.h:
		{UZP_GPIOTYPE_I2C,  8},			// I2CKEY_FP5ENABLESYS
		{UZP_GPIOTYPE_I2C,  9},			// I2CKEY_FP6ENABLECTL
		{UZP_GPIOTYPE_I2C, 10},			// I2CKEY_FP7EMERGENCYSTOP
		{UZP_GPIOTYPE_I2C, 11},			// I2CKEY_FP8
		{UZP_GPIOTYPE_I2C, 14},			// I2CKEY_UZEXT_SW1
		{UZP_GPIOTYPE_I2C, 15},			// I2CKEY_UZEXT_SW2
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CKEY_MZBB_USER
	}
 };
 static uz_platform_iomap uzp_iomap_MicroZohmRev01onBreakoutBoardRev01 = {
	{
		// Cf. uz_platform_gpo_id in uz_platform.h:
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_FP1RDY
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_FP2RUN
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_FP3ERR
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_FP4USR
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_FPRING
		{UZP_GPIOTYPE_I2C, 14},			// RST_PHY0
		{UZP_GPIOTYPE_I2C, 15},			// RST_PHY1
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_UZEXT_LED10
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_UZEXT_LED11
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_UZEXT_LED12
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_UZEXT_BEEP1
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CLED_UZEXT_BEEP2
		{UZP_GPIOTYPE_I2C, 10},			// I2CLED_MZD10GREEN
		{UZP_GPIOTYPE_I2C, 11},			// I2CLED_MZD11RED
		{UZP_GPIOTYPE_I2C, 12},			// I2CLED_MZD12YELLOW
		{UZP_GPIOTYPE_I2C, 13},			// I2CLED_MZD13BLUE
	},{
		// Cf. uz_platform_gpi_id in uz_platform.h:
		{UZP_GPIOTYPE_I2C,  6},			// I2CKEY_FP5ENABLESYS
		{UZP_GPIOTYPE_I2C,  7},			// I2CKEY_FP6ENABLECTL
		{UZP_GPIOTYPE_I2C,  8},			// I2CKEY_FP7EMERGENCYSTOP
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CKEY_FP8
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CKEY_UZEXT_SW1
		UZ_PLATFORM_GPIO_UNAVAILABLE,	// I2CKEY_UZEXT_SW2
		{UZP_GPIOTYPE_I2C,  9},			// I2CKEY_MZBB_USER
	}
 };

 static uz_platform uzp;
#endif

uint32_t uz_platform_init() {
#if (UZ_PLATFORM_ENABLE==1)
	uz_assert_false(uzp.is_ready);

	//// Primary I²C bus used by UZP (we might need a secondary for mixed-old/new combinations of UZC Rev<=04 and SoM)
	uz_iic_initbus(UZ_PLATFORM_I2CBUS_INSTID, XPAR_PSU_I2C_1_BASEADDR, XPAR_PSU_I2C_1_DEVICE_ID, XPAR_PSU_I2C_1_I2C_CLK_FREQ_HZ, UZ_PLATFORM_SCLK_RATEKHZ);

	//// Create I²C devices: EEPROM
	uz_iic_initdev(&uzp.eeprom, UZ_PLATFORM_I2CBUS_INSTID, UZ_PLATFORM_I2CADDR_EEPROM);

	int status;
	// Fetch platform data
	status = uz_iic_read_data(&uzp.eeprom, UZ_PLATFORM_EEPROM_INFOOFFSET, (uint8_t*) &uzp.data, sizeof(uzp.data));
	if ( XST_SUCCESS != status ) {
		uz_printf("APU: Error reading platform EEPROM!\r\n");
		return(UZ_FAILURE);
	}

	if (
			( uzp.data.hw_group == UZ_PLATFORM_HWGROUP_MAX ) &&
			( uzp.data.hw_model == UZ_PLATFORM_HWMODEL_MAX ) &&
			( uzp.data.hw_revision == UZ_PLATFORM_HWREVISION_MAX ) &&
			( uzp.data.serialdata.hw_externalserial.extserial == UZ_PLATFORM_EXTSERIAL_MAX )
	   ) {
		uz_printf("APU: Platform EEPROM is unconfigured!\r\n");
		return(UZ_FAILURE);
	} else {
		uz_platform_printinfo(&uzp.data);
	}

	// Populate IO map
	switch(uzp.data.hw_group) {
		case UZP_HWGROUP_UZOHM3:
			uzp.iomap = &uzp_iomap_UltraZohmRev04withExtensionBoardRev02;
			break;
		case UZP_HWGROUP_UZOHM6:
			uzp.iomap = &uzp_iomap_UltraZohmRev04withExtensionBoardRev02;
			break;
		case UZP_HWGROUP_MZOHM:
			uzp.iomap = &uzp_iomap_MicroZohmRev01onBreakoutBoardRev01;
			break;
		default:
			uz_printf("APU: Platform not supported!\r\n");
			return(UZ_FAILURE);
			break;
	}

	status = 0;
	int i;

	// Enumerate, initialize and configure GPIOs
	{
		uint8_t gpiotype_usage[UZP_GPIOTYPE_CNT] = { 0 };

		// [gpiodrv] I²C-GPIO
		uint16_t gpioi2c_confreg = 0xFFFF;			// All input
		// [gpiodrv] PS-GPIO
		uz_platform_gpiops_initxlnxcfg(&uzp.gpiops, XPAR_PSU_GPIO_0_BASEADDR, XPAR_PSU_GPIO_0_DEVICE_ID);

		// Enumerate GPOs
		for (i=0; i<UZP_GPO_CNT; i++) {
			uint8_t pin = uzp.iomap->gpo[i].gpX2pin;

			if ( UZ_NOGPO == pin )
				continue;

			enum uz_platform_gpiodrv_ drv = uzp.iomap->gpo[i].gpX2drv;

			// Count
			gpiotype_usage[drv]++;

			// Configure
			switch(drv) {
				case UZP_GPIOTYPE_I2C:
					//// [gpiodrv] I²C GPIO: Determine how to configure hardware (see below for the actual register write)
					gpioi2c_confreg &= ~(1<<pin);
					break;
				case UZP_GPIOTYPE_PS:
					//// [gpiodrv] PS GPIO: Configure hardware
					XGpioPs_SetDirectionPin(&uzp.gpiops, pin, GPIOPS_DIRECTION_OUT);
					break;
				case UZP_GPIOTYPE_CNT:
					break;
				case UZP_GPIOTYPE_NOGPIO:
					break;
			}
		}
		// Enumerate GPIs
		for (i=0; i<UZP_GPI_CNT; i++) {
			uint8_t pin = uzp.iomap->gpi[i].gpX2pin;

			if ( UZ_NOGPI == pin )
				continue;

			enum uz_platform_gpiodrv_ drv = uzp.iomap->gpi[i].gpX2drv;

			// Count
			gpiotype_usage[drv]++;

			// Configure
			switch(drv) {
				case UZP_GPIOTYPE_I2C:
					// Nothing to do here, as all pins not used as outputs (cf. above) have been pre-set as inputs (cf. gpioi2c_confreg)
					break;
				case UZP_GPIOTYPE_CNT:
					break;
				case UZP_GPIOTYPE_NOGPIO:
					break;
			}
		}

		//// [gpiodrv] I²C GPIO: Configure hardware if used
		if ( gpiotype_usage[UZP_GPIOTYPE_I2C] > 0 ) {
			// Create I²C device: GPIO
			uz_iic_initdev(&uzp.gpioi2c, UZ_PLATFORM_I2CBUS_INSTID, UZ_PLATFORM_I2CADDR_GPIO);

			// Populate (APU-)local mirror of output registers
			uzp.gpioi2c_outmirror = 0x0000;

			// Configure input/output direction according to iomap
			const uint8_t pca9535a9655e_regaddr_conf0 = 6;
			status += uz_iic_write_reg16(&uzp.gpioi2c, pca9535a9655e_regaddr_conf0, gpioi2c_confreg);
		}
	}

	//// Create I²C devices: MAC-EEPROMs (could be based on iomap, if needed)
	uz_iic_initdev(&uzp.maceeprom[0], UZ_PLATFORM_I2CBUS_INSTID, UZ_PLATFORM_I2CADDR_MACEE0);
	uz_iic_initdev(&uzp.maceeprom[1], UZ_PLATFORM_I2CBUS_INSTID, UZ_PLATFORM_I2CADDR_MACEE1);

	uz_printf("Platform IIC at %d kHz and with sum-status=%i\r\n", UZ_PLATFORM_SCLK_RATEKHZ, status);

	uzp.is_ready = true;

	return(UZ_SUCCESS);
#else
	return(UZ_FAILURE);
#endif
}

/**
 * @brief Pushes not-yet-written GPO changes to I²C hardware (NB: queuing is currently not supported for PS GPIO)
 *
 * @return XST_SUCCESS if successful or failure code in case of I²C comm error or subsystem disabled
 */
uint32_t uz_platform_gpoupdate() {
#if (UZ_PLATFORM_ENABLE==1)
	const uint8_t pca9535a9655e_regaddr_out0 = 2;

	return( uz_iic_write_reg16(&uzp.gpioi2c, pca9535a9655e_regaddr_out0, uzp.gpioi2c_outmirror) );
#else
	return(UZ_FAILURE);
#endif
}

/**
 * @brief Sets an UZP GPO
 *
 * @param uzpgpo_id ID of the GPO to be used (cf. uz_platform_gpo_id in uz_platform.h for available options).
 * @param uzpgpo_op Operation to be performed on the GPO (cf. uz_platform_gpo_op in uz_platform.h for available options).
 * @return UZ_SUCCESS if successful or failure code in case of I²C comm error or subsystem disabled
 */
uint32_t uz_platform_gposet(enum uz_platform_gpo_id uzpgpo_id, enum uz_platform_gpo_op uzpgpo_op) {
#if (UZ_PLATFORM_ENABLE==1)
	uz_assert(uzp.is_ready);

	// Look up GPO and map to pin
	uz_assert( uzpgpo_id < UZP_GPO_CNT );
	uint8_t pin = uzp.iomap->gpo[uzpgpo_id].gpX2pin;

	// Check whether this GPO exists on this platform
	if ( UZ_NOGPO == pin )
		return(UZ_FAILURE);

	int immediate = 0;

	switch(uzp.iomap->gpo[uzpgpo_id].gpX2drv) {
		case UZP_GPIOTYPE_I2C:
			switch(uzpgpo_op) {
				case UZP_GPO_ASSERT:
					immediate = 1;
					uzp.gpioi2c_outmirror |= 1<<pin;
					break;
				case UZP_GPO_ASSERT_QUEUED:
					uzp.gpioi2c_outmirror |= 1<<pin;
					break;
				case UZP_GPO_DEASSERT:
					immediate = 1;
					uzp.gpioi2c_outmirror &= ~(1<<pin);
					break;
				case UZP_GPO_DEASSERT_QUEUED:
					uzp.gpioi2c_outmirror &= ~(1<<pin);
					break;
				case UZP_GPO_TOGGLE:
					immediate = 1;
					uzp.gpioi2c_outmirror ^= 1<<pin;
					break;
				case UZP_GPO_TOGGLE_QUEUED:
					uzp.gpioi2c_outmirror ^= 1<<pin;
					break;
#if UZ_PLATFORM_OPWARN
				default:
					uz_printf("UZP: Unsupported OP=%i on GPO with ID=%2i\r\n", uzpgpo_op, uzpgpo_id);
					break;
#endif
			}

			if (immediate)
				return( uz_platform_gpoupdate() );

			break;
		case UZP_GPIOTYPE_PS:
			switch(uzpgpo_op) {
				case UZP_GPO_ASSERT:
					XGpioPs_WritePin(&uzp.gpiops, pin, 1);
					break;
				case UZP_GPO_DEASSERT:
					XGpioPs_WritePin(&uzp.gpiops, pin, 0);
					break;
				case UZP_GPO_DISABLE2TRISTATED:
					XGpioPs_SetOutputEnablePin(&uzp.gpiops, pin, GPIOPS_OUTPUTENABLE_DISABLEOP);	// FIXME: Not thread-safe → Replace via uz_platform_gpiops.c?
					break;
				case UZP_GPO_ENABLE2PUSHPULLED:
					XGpioPs_SetOutputEnablePin(&uzp.gpiops, pin, GPIOPS_OUTPUTENABLE_ENABLEOP);	// FIXME: Not thread-safe → Replace via uz_platform_gpiops.c?
					break;
#if UZ_PLATFORM_OPWARN
				default:
					uz_printf("UZP: Unsupported OP=%i on GPO with ID=%2i\r\n", uzpgpo_op, uzpgpo_id);
					break;
#endif
			}
			break;
		case UZP_GPIOTYPE_CNT:
			break;
		case UZP_GPIOTYPE_NOGPIO:
			break;
	}
	return(UZ_SUCCESS);
#else
	return(UZ_FAILURE);
#endif
}

/**
 * @brief Read six-byte MAC address from EEPROM
 *
 * @param eeprom ID of the MAC EEPROM to use.
 * @param addrbuf_p Pointer to (at least six-byte) buffer to be filled.
 * @return XST_SUCCESS if successful or failure code in case of I²C comm error or subsystem disabled
 */
uint32_t uz_platform_macread(uint8_t eeprom, uint8_t *addrbuf_p) {
#if (UZ_PLATFORM_ENABLE==1)
	uz_assert(uzp.is_ready);
	uz_assert(eeprom < sizeof(uzp.maceeprom)/sizeof(uzp.maceeprom[0]));

	const uint8_t maceeprom_addroffset = 0xFA;
	const uint8_t maceeprom_addrlength = 6;

	return( uz_iic_read_data(&uzp.maceeprom[eeprom], maceeprom_addroffset, addrbuf_p, maceeprom_addrlength) );
#else
	return(UZ_FAILURE);
#endif
}
