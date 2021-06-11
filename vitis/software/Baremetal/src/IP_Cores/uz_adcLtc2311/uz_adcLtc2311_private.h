#ifndef UZ_ADCLTC2311_PRIVATE_H
#define UZ_ADCLTC2311_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>
#include "uz_adcLtc2311.h"

struct uz_adcLtc2311 {
	const uint32_t base_address;
	const uint32_t ip_clk_frequency_Hz;
	bool is_ready;
	uint32_t sleeping_spi_masters;
	uint32_t napping_spi_masters;
};

#endif
