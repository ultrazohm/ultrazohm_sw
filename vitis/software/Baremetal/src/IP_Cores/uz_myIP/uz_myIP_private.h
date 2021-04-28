#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "uz_myIP.h"

struct uz_myIP {
    const uint32_t base_address;
    const uint32_t ip_clk_frequency_Hz;
    bool is_ready;
};