#ifndef UZ_ADCLTC2311_PRIVATE_H
#define UZ_ADCLTC2311_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>
#include "uz_adcLtc2311.h"

/**
 * @brief Software representation of the IP core
 *
 *
 */
struct uz_adcLtc2311 {
	const uint32_t base_address;		/**< AXI Base Address of the IP core in the FPGA */
	const uint32_t ip_clk_frequency_Hz;	/**< System clock frequency, the IP core is driven with */
	bool is_ready;				/**< Status indicator that the IP core is usable */
	uint32_t sleeping_spi_masters;		/**< One hot encoded status variable, which SPI masters are currently in sleep mode */
	uint32_t napping_spi_masters;		/**< One hot encoded status variable, which SPI masters are currently in nap mode */
};

#endif
