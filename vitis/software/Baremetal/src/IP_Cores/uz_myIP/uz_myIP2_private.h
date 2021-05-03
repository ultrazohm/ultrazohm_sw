#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "uz_myIP2.h"

struct uz_myIP2 {
    const uint32_t base_address;
    const uint32_t ip_clk_frequency_Hz;
    bool is_ready;
};