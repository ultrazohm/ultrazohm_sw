#ifndef UZ_SVPWM_6PH_INIT_H //Namen ändern wegen Kontinuirlich diskontinuirlich + 6ph
#define UZ_SVPWM_6PH_INIT_H

#include <math.h>
#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../../globalData.h"
#include "../../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../../main.h"



#define M_PI_FLOAT 3.14159265359f
//Namen structs


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
	int seventh;
} uz_sector_sv;

typedef int s_64[6];


typedef struct{
	float inv_Ttv_matrix[4][4];
}uz_inv_Ttv_sec_Matrix;


typedef struct{
	uz_sector_sv sector_sv[24];
	s_64 SV_64[64];
	uz_inv_Ttv_sec_Matrix inv_Ttv_sec_Matrix[24];
}SVMPWM_Parameters;

typedef struct{
	struct uz_DutyCycle_2x3ph_t DutyCycles;
	int current_sector;
	float SV_angle;
	float alpha_trafo;
	float beta_trafo;
	float x_trafo;
	float y_trafo;
	float nullminus_trafo;
	float nullplus_trafo;
}output_with_test;









output_with_test uz_SVPWM_4arrows_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2);
output_with_test uz_SVPWM_4arrows_discontinous_V1_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2)
output_with_test uz_SVPWM_4arrows_discontinous_V2_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2)
output_with_test uz_SVPWM_5arrows_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2);
void uz_svm_6ph_calculate_and_shift(int sector, uz_sector_sv Zeiger[24]);

















#endif
