#include "../include/uz_adcMax11331_ip_core_init.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcMax11331/uz_adcMax11331.h"
#include "xparameters.h"
#include <stdint.h>
#include <stdbool.h>

#define XPAR_A3_ADC_MAX11331_IP_CORE_FREQUENCY 100000000U
#define DEFAULT_MAX11331_CONVERSION_FACTOR 1.0f
#define DEFAULT_MAX11331_INTEGER_BITS 14
#define DEFAULT_MAX11331_FRACTIONAL_BITS 4
#define DEFAULT_MAX11331_OFFSET 0

void uz_adcMax11331_ip_core_init(void)
{
   //Parameter set for one MAX11331 chip, thus one master
   struct uz_adcMax11331_config_t default_configuration = {
        .base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_ADC_MAX11331_A3_BASEADDR,
        .ip_clk_frequency_Hz = XPAR_A3_ADC_MAX11331_IP_CORE_FREQUENCY,
        .channel_config = {
            .conversion_factor = DEFAULT_MAX11331_CONVERSION_FACTOR,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = DEFAULT_MAX11331_INTEGER_BITS,
                .fractional_bits = DEFAULT_MAX11331_FRACTIONAL_BITS},
            .offset = DEFAULT_MAX11331_OFFSET,
        },
        .trigger_mode=pl_trigger,
        .cpol = 1U,
        .cpha = 1U,
        .master_select = UZ_ADCMAX11331_MASTER1 | UZ_ADCMAX11331_MASTER2  | UZ_ADCMAX11331_MASTER3,
        .adc_delay_offset = 0,
		.clk_div = UZ_ADCMAX11331_SPI_CLK_16_67MHZ};

	//1.) Create the instance of the first Max11331 adapter card with one or may several master = several physical Max11331 chips
    uz_adcMax11331_t *instance_1 = uz_adcMax11331_init(default_configuration);

    // Apply same configuration to all following instances, despite the base address of the FPGA IP Core
    //2.) Create the instance of the second Max11331 adapter board with one or may several master = several physical Max11331 chips
//    default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A1_ADAPTER_A1_ADC_MAX11331_BASEADDR;
//    uz_adcMax11331_t *instance_2 = uz_adcMax11331_init(default_configuration);
	//3.) Create the instance of the third Max11331 adapter board with one or may several master = several physical Max11331 chips
//    default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A2_ADAPTER_A2_ADC_MAX11331_BASEADDR;
//    uz_adcMax11331_t *instance_3 = uz_adcMax11331_init(default_configuration);
}
