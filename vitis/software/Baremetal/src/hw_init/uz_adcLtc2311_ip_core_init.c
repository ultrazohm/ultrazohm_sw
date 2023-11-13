#include "../include/uz_adcLtc2311_ip_core_init.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "xparameters.h"
#include <stdint.h>
#include <stdbool.h>

#define XPAR_A1_ADC_LTC2311_IP_CORE_FREQUENCY 100000000U
//#define DEFAULT_CONVERSION_FACTOR 0.00255847f//1.0f // ADC Rev3v3 mit 250 Ohm Shunts
#define DEFAULT_CONVERSION_FACTOR 0.00177764f
#define VOLTAGE_CONVERSION_FACTOR 0.02140350f // ADC Rev3v3 mit 250 Ohm Shunts
#define DEFAULT_INTEGER_BITS 3//14
#define DEFAULT_FRACTIONAL_BITS 15//4
#define DEFAULT_OFFSET 0
#define VOLTAGE_OFFSET 21000 // ADC Rev3v3 mit 250 Ohm Shunts

uz_adcLtc2311_t *A1_instance;
uz_adcLtc2311_t *A2_instance;
uz_adcLtc2311_t *A3_instance;

    struct uz_adcLtc2311_channel_config_t voltage_CH4_configuration = {
            .conversion_factor = VOLTAGE_CONVERSION_FACTOR,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = DEFAULT_INTEGER_BITS,
                .fractional_bits = DEFAULT_FRACTIONAL_BITS},
            .offset = VOLTAGE_OFFSET,
        };

void uz_adcLtc2311_ip_core_init(void)
{
    struct uz_adcLtc2311_config_t default_configuration1 = {
        .base_address = XPAR_UZ_ANALOG_ADAPTER_A1_ADAPTER_A1_ADC_LTC2311_S00_AXI_BASEADDR,
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

    struct uz_adcLtc2311_config_t default_configuration2 = {
        .base_address = XPAR_UZ_ANALOG_ADAPTER_A2_ADAPTER_A2_ADC_LTC2311_S00_AXI_BASEADDR,
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

    struct uz_adcLtc2311_config_t default_configuration3 = {
        .base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_LTC2311_S00_AXI_BASEADDR,
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
    A1_instance = uz_adcLtc2311_init(default_configuration1);
//    default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A2_ADAPTER_A2_ADC_LTC2311_S00_AXI_BASEADDR;
    A2_instance = uz_adcLtc2311_init(default_configuration2);
//    default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_A3_ADC_LTC2311_S00_AXI_BASEADDR;
    A3_instance = uz_adcLtc2311_init(default_configuration3);

}

void reconfig_ADC(void)
{

//	uz_adcLtc2311_set_channel_config(A1_instance, UZ_ADCLTC2311_MASTER1, UZ_ADCLTC2311_CH4, voltage_CH4_configuration);
	uz_adcLtc2311_set_channel_config(A2_instance, UZ_ADCLTC2311_MASTER1, UZ_ADCLTC2311_CH4, voltage_CH4_configuration);
}
