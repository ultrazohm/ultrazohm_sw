#pragma once
#include <stdint.h>
#include <stdbool.h>
struct uz_ipCore{
  const uint32_t base_address;
  const uint32_t ip_clk_frequency_Hz;
  bool is_ready;
  int variable;
};