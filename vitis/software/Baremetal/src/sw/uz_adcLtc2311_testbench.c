#include "uz_adcLtc2311_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311_staticAllocator.h"

void uz_adcLtc2311_testbench(void) {

	uz_adcLtc2311* test_instance = uz_adcLtc2311_allocate_instance_one();

	uz_adcLtc2311_spiConfig test_spi_config;
	uz_adcLtc2311_init_spiConfig(&test_spi_config);
	test_spi_config.clk_div = 4;
	uz_adcLtc2311_configureSpi(test_instance, &test_spi_config);
	uz_adcLtc2311_config test_config;
	uz_adcLtc2311_initConfig(&test_config);
	test_config.master_select = UZ_ADCLTC2311_MASTER1;
	test_config.channel_select = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3 | UZ_ADCLTC2311_CH4 | UZ_ADCLTC2311_CH5 | UZ_ADCLTC2311_CH6 | UZ_ADCLTC2311_CH7 | UZ_ADCLTC2311_CH8;
	test_config.set_conversion = true;
	test_config.set_offset = true;
	test_config.set_samples = true;
	test_config.try_infinite = false;
	test_config.max_attempts = 10;
	test_config.conversion_factor = 153;
	test_config.offset = 0;
	test_config.samples = 4;
	uz_adcLtc2311_configure(test_instance, &test_config);
	//uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);

	uz_adcLtc2311_napSleepConfig test_ns_config;

	uz_adcLtc2311_init_napSleepConfig(&test_ns_config);
	test_ns_config.max_attempts = 10;
	test_ns_config.try_infinite = false;
	test_ns_config.spi_masters = UZ_ADCLTC2311_MASTER1;

	uz_adcLtc2311_setTriggeredMode(test_instance);
	//uz_adcLtc2311_setContinuousMode(test_instance);

	while (1) {

		uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);

//		uz_adcLtc2311_enterNapMode(test_instance, &test_ns_config);
//		uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);
//		uz_adcLtc2311_leaveNapMode(test_instance, &test_ns_config);
//		uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);
//		uz_adcLtc2311_enterSleepMode(test_instance, &test_ns_config);
//		uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);
//		uz_adcLtc2311_leaveSleepMode(test_instance, &test_ns_config);
//		uz_adcLtc2311_softwareTrigger(test_instance, UZ_ADCLTC2311_MASTER1);

	}
}
