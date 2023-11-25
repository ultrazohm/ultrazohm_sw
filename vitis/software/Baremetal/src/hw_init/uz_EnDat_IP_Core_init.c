#include "../include/uz_EnDat_IP_Core_init.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_EnDat/uz_EnDat.h"
#include <stdint.h>
#include <stdbool.h>

#define XPARS_NON_FINAL_BASE_CLK 100000000U
#define XPARS_NON_FINAL_BASE_ADDRESS 0x8000000U

 uz_EnDat_t* uz_EnDat_IP_core_init(void) {
    uz_EnDat_t* EnDat_init_object;
    struct uz_EnDat_config_t config = {
        .base_address = XPARS_NON_FINAL_BASE_ADDRESS,
        .ip_clk_frequency_Hz = XPARS_NON_FINAL_BASE_CLK

    };

   EnDat_init_object = uz_EnDat_init(config);
   uz_EnDat_write_default_values(EnDat_init_object);
    return(EnDat_init_object);
}