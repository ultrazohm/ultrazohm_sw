#ifndef UZ_ADC_MAX11331_HW_ADDRESSES
#define UZ_ADC_MAX11331_HW_ADDRESSES

#define ADC_MAX11331_STATUS           		0x0U  // Read: ADC Status Register
#define ADC_MAX11331_ERROR_COUNTER    		0x4U  // Read: Count how many times the initialization is trying to get the right data from the MISO lines (echo messages)
#define ADC_MAX11331_ECHOED_BIPOLAR_12  	0x8U  // Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 1 and 2
#define ADC_MAX11331_ECHOED_BIPOLAR_34  	0xCU  // Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 3 and 4
#define ADC_MAX11331_ECHOED_BIPOLAR_56  	0x10U // Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 5 and 6
#define ADC_MAX11331_ECHOED_UNIPOLAR_12 	0x14U // Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 1 and 2
#define ADC_MAX11331_ECHOED_UNIPOLAR_34 	0x18U // Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 3 and 4
#define ADC_MAX11331_ECHOED_UNIPOLAR_56 	0x1CU // Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 5 and 6
#define ADC_MAX11331_ADCSELECTOR_FORCEINIT	0x20U // Write/Read: ADC_selector and Force_init function
#define ADC_MAX11331_CLK_DIVISION    		0x24U // Write/Read: The sck is generated internally based on the clock divider and provided input clock

#endif

