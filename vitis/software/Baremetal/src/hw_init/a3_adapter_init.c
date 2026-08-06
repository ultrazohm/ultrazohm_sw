#include "../include/a3_adapter_init.h"

/* Project Wizard BEGIN: A3 definitions */
/* Project Wizard generated content for A3 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"
#include <stdbool.h>
#include <stdint.h>

static struct uz_adcLtc2311_config_t config_adc_ltc2311_a3 = {
    .base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_LTC2311_S00_AXI_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .software_raw_to_physical_value_factor = {
        10.0f / 0.03993f,
        10.0f / 0.03993f,
        10.0f / 0.03993f,
        10.0f / 0.003764f,
        10.0f,
        10.0f,
        10.0f,
        10.0f},
    .ip_core_channel_config = {
        .conversion_factor = 1.0f,
        .conversion_factor_definition = {.is_signed = true, .integer_bits = 14, .fractional_bits = 4},
        .offset = 0,
    },
    .spi_master_config = {.samples = 1U, .sample_time = 6U, .trigger_mode = pl_trigger},
    .cpol = 1U,
    .cpha = 0U,
    .napping_spi_masters = 0U,
    .sleeping_spi_masters = 0U,
    .master_select = UZ_ADCLTC2311_MASTER1,
    .channel_select = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3 | UZ_ADCLTC2311_CH4 | UZ_ADCLTC2311_CH5 | UZ_ADCLTC2311_CH6 | UZ_ADCLTC2311_CH7 | UZ_ADCLTC2311_CH8,
    .pre_delay = 0U,
    .post_delay = 0U,
    .clk_div = 0U,
    .max_attempts = 10U};

uz_adcLtc2311_t* initialize_adc_ltc2311_a3(void)
{
    return uz_adcLtc2311_init(config_adc_ltc2311_a3);
}
/* Project Wizard END: A3 definitions */
