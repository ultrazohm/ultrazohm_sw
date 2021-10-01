#include "../include/uz_adcLtc2311_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "xparameters.h"
#include <stdint.h>

void uz_adcLtc2311_testbench(void)
{
    int32_t conversion_factor = 153;
    uint32_t samples = 4;
    int32_t offset = 0;
    uint32_t sample_time = 6;
    uint32_t cpol = 1;
    uint32_t cpha = 0;
    uint32_t pre_delay = 0;
    uint32_t post_delay = 0;
    uint32_t clk_div = 0;
    uint32_t master = UZ_ADCLTC2311_MASTER1;
    uint32_t channel = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3 | UZ_ADCLTC2311_CH4 | UZ_ADCLTC2311_CH5 | UZ_ADCLTC2311_CH6 | UZ_ADCLTC2311_CH7 | UZ_ADCLTC2311_CH8;
    // set max_attempts to non zero if you want to prevent that the IP core potentially tries to update
    // operation parameters infinitely
    uint32_t max_attempts = 10;

    struct uz_adcLtc2311_config_t default_configuration = {
        .base_address=XPAR_A1_ADC_LTC2311_S00_AXI_BASEADDR,
        .ip_clk_frequency_Hz=100000000U,
        .conversion_factor = conversion_factor,
        .samples = samples,
        .cpol = cpol,
        .cpha = cpha,
        .offset = offset,
        .napping_spi_masters=0,
        .sleeping_spi_masters=0,
        .master_select = master,
        .channel_select = channel,
        .sample_time = sample_time,
        .pre_delay = pre_delay,
        .post_delay = post_delay,
        .clk_div = clk_div,
        .max_attempts = max_attempts
    };



    uz_adcLtc2311_t* test_instance = uz_adcLtc2311_init(default_configuration);

    default_configuration.base_address = XPAR_A2_ADC_LTC2311_S00_AXI_BASEADDR;
    uz_adcLtc2311_t* test_instance_2 = uz_adcLtc2311_init(default_configuration);

    default_configuration.base_address = XPAR_A3_ADC_LTC2311_S00_AXI_BASEADDR;
    uz_adcLtc2311_t* test_instance_3 = uz_adcLtc2311_init(default_configuration);

    // Adjust operation parameters
    // 1: Select which channels you want to update
    uz_adcLtc2311_set_master_select(test_instance, UZ_ADCLTC2311_MASTER1);
    uz_adcLtc2311_set_channel_select(test_instance, UZ_ADCLTC2311_CH4);

    // 2: Adjust the parameters in the software representation
    // These parameters are channel specific
    uz_adcLtc2311_set_conversion_factor(test_instance, 160);
    uz_adcLtc2311_set_offset(test_instance, 10);

    // These parameters are global for a master
    uz_adcLtc2311_set_samples(test_instance, 5);
    uz_adcLtc2311_set_sample_time(test_instance, 20);

    // 3: Call the update functions to write the values to the hardware and check their return values
    int32_t return_value = uz_adcLtc2311_update_conversion_factor(test_instance);
    uz_assert(return_value == UZ_SUCCESS);

    return_value = uz_adcLtc2311_update_offset(test_instance);
    uz_assert(return_value == UZ_SUCCESS);

    return_value = uz_adcLtc2311_update_samples(test_instance);
    uz_assert(return_value == UZ_SUCCESS);

    return_value = uz_adcLtc2311_update_sample_time(test_instance);
    uz_assert(return_value == UZ_SUCCESS);



    while(1)
    {

//	    uz_adcLtc2311_software_trigger(test_instance, 0);
//	    uz_adcLtc2311_software_trigger(test_instance_2, 0);
//	    uz_adcLtc2311_software_trigger(test_instance_3, 0);
//	    uz_adcLtc2311_enter_nap_mode(test_instance);
//	    uz_adcLtc2311_software_trigger(test_instance, 0);
//	    uz_adcLtc2311_leave_nap_mode(test_instance);
//	    uz_adcLtc2311_software_trigger(test_instance, 0);
//	    uz_adcLtc2311_enter_sleep_mode(test_instance);
//	    uz_adcLtc2311_software_trigger(test_instance, 0);
//	    uz_adcLtc2311_leave_sleep_mode(test_instance);
//
	    uz_adcLtc2311_set_continuous_mode(test_instance);
	    uz_sleep_useconds(5);
	    uz_adcLtc2311_set_triggered_mode(test_instance);
	    uz_adcLtc2311_software_trigger(test_instance, 0);

    }
}
