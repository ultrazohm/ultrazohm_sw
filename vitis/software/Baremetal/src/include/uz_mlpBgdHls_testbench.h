#pragma once

// includes
#include <stdbool.h>

// defines
#define MLP_HLS_PARAMETER_BASE_ADDRESS 0x20100U
#define MLP_HLS_PARAMETER_MEMORY_OFFSET_PL 0xFFE00000U

int uz_mlpBgdHls_testbench(bool testMlp, bool testBgd);
