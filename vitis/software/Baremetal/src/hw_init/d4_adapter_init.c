#include "../include/d4_adapter_init.h"

/* xz Project Wizard BEGIN: D4 definitions */
/* xz Project Wizard generated content for D4 */
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
    .Configdata_A = {0U},
    .Configdata_B = {0U},
    .Configdata_C = {0U},
};

uz_temperaturecard_t* initialize_temperature_card_d4(void)
{
    return uz_temperaturecard_init(config_temperature_card_d4);
}
/* xz Project Wizard END: D4 definitions */
