#ifndef _DATA_LOGGER_PL_H_
#define _DATA_LOGGER_PL_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ap_fixed.h>

#define LOGGING_OCM_BASE_ADDRESS 0x00FFFC0000

#define ap_fixed_wordlength 32
#define ap_fixed_integerbits 20
#define NUM_TRANS 50

typedef struct data_logger_pl_t data_logger_pl_t;

typedef float din_t;
typedef float dout_t;
typedef ap_fixed<ap_fixed_wordlength, ap_fixed_integerbits>  din_apf_t;
typedef ap_fixed<ap_fixed_wordlength, ap_fixed_integerbits>  dout_apf_t;

//void uz_log_data(int *value_1, float *value_2, din_apf_t *value_3, float *value_4, din_apf_t *value_5, float *value_6, din_apf_t *value_7,  float *dlog_1);
//void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3, uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *control_1, uint32_t *control_2, float *dlog_1);
void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3, uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *value_8,
					uint32_t *value_9, uint32_t *value_10, uint32_t *value_11, uint32_t *value_12, uint32_t *value_13, uint32_t *value_14, uint32_t *value_15, uint32_t *value_16,
					uint32_t *value_17, uint32_t *value_18, uint32_t *value_19, uint32_t *value_20, uint32_t *value_21, uint32_t *value_22, uint32_t *value_23, uint32_t *value_24,
					uint32_t *value_25, uint32_t *value_26, uint32_t *value_27, uint32_t *value_28, uint32_t *value_29, uint32_t *value_30, uint32_t *value_31, uint32_t *value_32,
					uint32_t *value_33, uint32_t *value_34, uint32_t *value_35, uint32_t *value_36, uint32_t *value_37, uint32_t *value_38, uint32_t *value_39, uint32_t *value_40,
					uint32_t *control_1, uint32_t *control_2, float buff[32]);

#endif
