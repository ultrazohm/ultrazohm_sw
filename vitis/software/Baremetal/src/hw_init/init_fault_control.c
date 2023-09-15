#include "../include/init_fault_control.h"

// config for moving average filter
const struct uz_movingAverageFilter_config movAvF_config = {
  .filterLength = 1U
};

#define ARRAYSIZE 100

// circular Buffers for 6 moving average filters
float dataR1 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R1 = {
.length = ARRAYSIZE,
.data = &dataR1[0]
};
float dataR2 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R2 = {
.length = ARRAYSIZE,
.data = &dataR2[0]
};
float dataR3 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R3 = {
.length = ARRAYSIZE,
.data = &dataR3[0]
};
float dataR4 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R4 = {
.length = ARRAYSIZE,
.data = &dataR4[0]
};
float dataR5 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R5 = {
.length = ARRAYSIZE,
.data = &dataR5[0]
};
float dataR6 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R6 = {
.length = ARRAYSIZE,
.data = &dataR6[0]
};
float dataR7 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R7 = {
.length = ARRAYSIZE,
.data = &dataR7[0]
};
float dataR8 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R8 = {
.length = ARRAYSIZE,
.data = &dataR8[0]
};
float dataR9 [ARRAYSIZE] = {0};
uz_array_float_t circularBuffer_R9 = {
.length = ARRAYSIZE,
.data = &dataR9[0]
};


uz_VSD_9ph_FD_t* init_uz_VSD_9ph_FD(void){
	uz_movingAverageFilter_t* movAvFilter_R1 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R1);
	uz_movingAverageFilter_t* movAvFilter_R2 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R2);
	uz_movingAverageFilter_t* movAvFilter_R3 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R3);
	uz_movingAverageFilter_t* movAvFilter_R4 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R4);
	uz_movingAverageFilter_t* movAvFilter_R5 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R5);
	uz_movingAverageFilter_t* movAvFilter_R6 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R6);
	uz_movingAverageFilter_t* movAvFilter_R7 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R7);
	uz_movingAverageFilter_t* movAvFilter_R8 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R8);
	uz_movingAverageFilter_t* movAvFilter_R9 = uz_movingAverageFilter_init(movAvF_config, circularBuffer_R9);
	struct uz_VSD_9ph_FD_config fault_detection_cfg = {
		.upperlimit = 1.1f,
		.lowerlimit = 0.9f,
		.threshold = 0.5f,
		.mov_average_filter_length = ARRAYSIZE,
		.sample_frequency_Hz = UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE,
		.percent_of_el_period = 0.5f,
		.movingAverageFilter_R1 = movAvFilter_R1,
		.movingAverageFilter_R2 = movAvFilter_R2,
		.movingAverageFilter_R3 = movAvFilter_R3,
		.movingAverageFilter_R4 = movAvFilter_R4,
		.movingAverageFilter_R5 = movAvFilter_R5,
		.movingAverageFilter_R6 = movAvFilter_R6,
		.movingAverageFilter_R7 = movAvFilter_R7,
		.movingAverageFilter_R8 = movAvFilter_R8,
		.movingAverageFilter_R9 = movAvFilter_R9};
	return uz_VSD_9ph_FD_init(fault_detection_cfg);
}

