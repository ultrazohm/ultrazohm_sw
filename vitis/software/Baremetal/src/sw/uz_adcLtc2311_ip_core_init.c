#include "../include/uz_adcLtc2311_ip_core_init.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "xparameters.h"
#include <stdint.h>
#include <stdbool.h>

#define XPAR_A1_ADC_LTC2311_IP_CORE_FREQUENCY 100000000U
#define DEFAULT_CONVERSION_FACTOR 1.0f
#define DEFAULT_INTEGER_BITS 14
#define DEFAULT_FRACTIONAL_BITS 4
#define DEFAULT_OFFSET 0

void uz_adcLtc2311_ip_core_init(void)
{
    struct uz_adcLtc2311_config_t default_configuration = {
        .base_address = XPAR_A1_ADC_LTC2311_S00_AXI_BASEADDR,
        .ip_clk_frequency_Hz = XPAR_A1_ADC_LTC2311_IP_CORE_FREQUENCY,
        .channel_config = {
            .conversion_factor = DEFAULT_CONVERSION_FACTOR,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = DEFAULT_INTEGER_BITS,
                .fractional_bits = DEFAULT_FRACTIONAL_BITS},
            .offset = DEFAULT_OFFSET,
        },
        .spi_master_config = {.samples = 1U, .sample_time = 6U, .trigger_mode=pl_trigger},
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

    // Apply the same configurations to all instances
    uz_adcLtc2311_t *test_instance = uz_adcLtc2311_init(default_configuration);
    default_configuration.base_address = XPAR_A2_ADC_LTC2311_S00_AXI_BASEADDR;
    uz_adcLtc2311_t *test_instance_2 = uz_adcLtc2311_init(default_configuration);
    default_configuration.base_address = XPAR_A3_ADC_LTC2311_S00_AXI_BASEADDR;
    uz_adcLtc2311_t *test_instance_3 = uz_adcLtc2311_init(default_configuration);
}
