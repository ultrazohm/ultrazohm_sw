#ifndef UZ_CSVPMW_INIT_H
#define UZ_CSVPMW_INIT_H
#include "../uz_Transformation/uz_Transformation.h"
#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"


typedef struct {
	float cmpa;
	float cmpb;
	float cmpc;
	float cmpx;
	float cmpy;
	float cmpz;
} uz_cmp_signal;

typedef struct {
	int first;
	int second;
	int third;
	int fourth;
	int fifth;
	int sixth;
} uz_sector_sv;

typedef struct{
	double inv_Ttv_matrix[4][4];
}uz_inv_Ttv_sec_Matrix;


uz_cmp_signal CSVPWM_24_2L_1ML_1M_v1(uz_6ph_alphabeta_t input_parameter, float U_ZK);
