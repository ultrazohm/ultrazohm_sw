#include "../include/a3_adapter_init.h"

/* Project Wizard BEGIN: A3 definitions */
/* Project Wizard generated content for A3 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"
#include <stdbool.h>
#include <stdint.h>

static struct uz_adcMax11331_config_t config_adc_max11331_a3 = {
    .base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_MAX11331_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .master_select = UZ_ADCMAX11331_MASTER1 | UZ_ADCMAX11331_MASTER2 | UZ_ADCMAX11331_MASTER3,
    .trigger_mode = UZ_ADCMAX11331_PL_TRIGGER,
    .adc_delay_offset = 0U,
    .clk_div = UZ_ADCMAX11331_SPI_CLK_16_67MHZ,
    .cpha = 1U,
    .cpol = 1U,
    .error_code = 0U,
    .channel_config = {
        .conversion_factor = 4.96241f*245.9f,
        .conversion_factor_definition = {
            .is_signed = true,
            .integer_bits = 14,
            .fractional_bits = 4},
        .offset = 0,
    }};

uz_adcMax11331_t* initialize_adc_max11331_a3(void)
{
    return uz_adcMax11331_init(config_adc_max11331_a3);
}

float convert_adc_max11331_a3_raw_to_physical_value(int16_t raw_value)
{
    return ((float)((int16_t)(raw_value << 4))) / (float)(1 << 15) * config_adc_max11331_a3.channel_config.conversion_factor;
}
/* Project Wizard END: A3 definitions */
