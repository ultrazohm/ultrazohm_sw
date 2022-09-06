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
void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3, uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *control_1, uint32_t *control_2, float buff[7]);

#endif
