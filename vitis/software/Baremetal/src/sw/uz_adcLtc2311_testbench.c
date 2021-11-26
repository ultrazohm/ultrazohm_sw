#include "../include/uz_adcLtc2311_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "xparameters.h"
#include <stdint.h>

bool sample_once=false;

void uz_adcLtc2311_testbench(void)
{
    struct uz_adcLtc2311_config_t default_configuration = {
        .base_address = XPAR_A1_ADC_LTC2311_S00_AXI_BASEADDR,
        .ip_clk_frequency_Hz = 100000000U,
        .channel_config = {
            .conversion_factor = 1.0f,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = 14,
                .fractional_bits = 4},
            .offset = 0,
        },
        .spi_master_config = {.samples = 1U, .sample_time = 6U},
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

    struct uz_adcLtc2311_channel_config_t channel_config = {
        .conversion_factor = 1.0f,
        .conversion_factor_definition = {
            .is_signed = true,
            .fractional_bits = 4,
            .integer_bits = 14},
        .offset = 0};
    uz_adcLtc2311_set_channel_config(test_instance, UZ_ADCLTC2311_MASTER1, UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3, channel_config);
    channel_config.conversion_factor=10.0f;
    channel_config.offset=100;
    uz_adcLtc2311_set_channel_config(test_instance, UZ_ADCLTC2311_MASTER1, UZ_ADCLTC2311_CH4, channel_config);

    while(1){
        if(sample_once){
            uz_adcLtc2311_software_trigger(test_instance, UZ_ADCLTC2311_MASTER1);
            sample_once=false;
        }
    }

    // // Adjust operation parameters
    // // 1: Select which channels you want to update
    // uz_adcLtc2311_set_master_select(test_instance, UZ_ADCLTC2311_MASTER1);
    // uz_adcLtc2311_set_channel_select(test_instance, UZ_ADCLTC2311_CH4);

    // // 2: Adjust the parameters in the software representation
    // // These parameters are channel specific
    // uz_adcLtc2311_set_conversion_factor(test_instance, 160);
    // uz_adcLtc2311_set_offset(test_instance, 10);

    // // These parameters are specific for a master but not channel specific
    // // Take 5 samples per trigger event
    // uz_adcLtc2311_set_samples(test_instance, 5);
    // // Wait at least 20 system clock cycles from the rising edge of SS_N to the next falling edge of SS_N
    // uz_adcLtc2311_set_sample_time(test_instance, 20);

    // // 3: Call the update functions to write the values to the hardware and check their return values
    // // Since these functions are potentially called during operation they do not stop the application
    // // by raising an exception if the action fails. The user has to take care about this case!!!
    // int32_t return_value = uz_adcLtc2311_update_conversion_factor(test_instance);
    // uz_assert(return_value == UZ_SUCCESS);
    // return_value = uz_adcLtc2311_update_offset(test_instance);
    // uz_assert(return_value == UZ_SUCCESS);
    // return_value = uz_adcLtc2311_update_samples(test_instance);
    // uz_assert(return_value == UZ_SUCCESS);
    // return_value = uz_adcLtc2311_update_sample_time(test_instance);
    // uz_assert(return_value == UZ_SUCCESS);

    // // Operation
    // while(1)
    // {
    //     // Software trigger with explicitely chosen SPI master
    //     uz_adcLtc2311_software_trigger(test_instance, UZ_ADCLTC2311_MASTER1);
    //     // When setting the choice to 0 the SPI masters from
    //     // test_instance->config.master_select are chosen for the trigger
    //     uz_adcLtc2311_software_trigger(test_instance_2, 0);
    //     uz_adcLtc2311_software_trigger(test_instance_3, 0);

    //     // Nap and sleep mode:
    //     uz_adcLtc2311_enter_nap_mode(test_instance);
    //     // This trigger event will not trigger any conversions
    //     // because the masters are in nap mode
    //     uz_adcLtc2311_software_trigger(test_instance, 0);
    //     uz_adcLtc2311_leave_nap_mode(test_instance);
    //     // The trigger works again
    //     uz_adcLtc2311_software_trigger(test_instance, 0);
    //     uz_adcLtc2311_enter_sleep_mode(test_instance);
    //     // This trigger event will not trigger any conversions
    //     // because the masters are in sleep mode
    //     uz_adcLtc2311_software_trigger(test_instance, 0);
    //     uz_adcLtc2311_leave_sleep_mode(test_instance);

    //     // After enabling continuous mode the ADC is triggered at maximum sampling frequency
    //     uz_adcLtc2311_set_continuous_mode(test_instance);
    //     // Execute some samples
    //     uz_sleep_useconds(5);
    //     // After enabling the triggered mode the current conversion is executed until the end
    //     // end the triggered mode is entered
    //     uz_adcLtc2311_set_triggered_mode(test_instance);
    //     uz_adcLtc2311_software_trigger(test_instance, 0);
    // }
}
