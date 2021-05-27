#ifndef UZ_ADCLTC2311_PRIVATE_H
#define UZ_ADCLTC2311_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>
#include "uz_adcLtc2311.h"


struct uz_adcLtc2311 {
    const uint32_t base_address;
    const uint32_t ip_clk_frequency_Hz;
    bool is_ready;
};

#endif
