#include "../include/d4_adapter_init.h"

/* Project Wizard BEGIN: D4 definitions */
/* Project Wizard generated content for D4 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_temperaturecard_config_t config_temperature_card_d4 = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D4_ADAPTER_TEMPERATURE_CARD_INT_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .Sample_Freq_Hz = 5U,
    .Config_Global_A = 0U,
    .Config_Mux_A = 0U,
    .Config_Global_B = 0U,
    .Config_Mux_B = 0U,
    .Config_Global_C = 0U,
    .Config_Mux_C = 0U,
    .Configdata_A = {
        [0] = 0U,
        [1] = 0U,
        [2] = 0U,
        [3] = 0U,
        [4] = 0U,
        [5] = 0U,
        [6] = 0U,
        [7] = 0U,
        [8] = 0U,
        [9] = 0U,
        [10] = 0U,
        [11] = 0U,
        [12] = 0U,
        [13] = 0U,
        [14] = 0U,
        [15] = 0U,
        [16] = 0U,
        [17] = 0U,
        [18] = 0U,
        [19] = 0U,
    },
    .Configdata_B = {
        [0] = 0U,
    },
    .Configdata_C = {
        [0] = 0U,
    },
};

uz_temperaturecard_t* initialize_temperature_card_d4(void)
{
    return uz_temperaturecard_init(config_temperature_card_d4);
}
/* Project Wizard END: D4 definitions */
