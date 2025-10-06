#include "../include/endat.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"


struct uz_EnDat_config_t endat_config_d4_1 = {
		.base_address = XPAR_UZ_USER_ADAPTER_D4_UZ_ENDAT_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000U,
		.control = 0xB407,
		.divider = 3U
};


uz_EnDat_t* initialize_endat_D4_1(void) {
	return(uz_EnDat_init(endat_config_d4_1));
}
