#include "uz_6ph_SVPWM.h"
#include "../uz_HAL.h"
#include <math.h>
#include "../uz_signals/uz_signals.h"
#include "../uz_math_constants.h"
#include "uz_pwm_help_functions.h"
#include "../uz_Transformation/uz_Transformation.h"

struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2){

	struct uz_DutyCycle_2x3ph_PhaseShiftOpt output = {0};

	//-Angle from ref-----------------------------------------------------
	uz_3ph_alphabeta_t u_alphabeta_ref;

	u_alphabeta_ref.alpha = u_6ph_alphabeta_ref_Volts.alpha;
	u_alphabeta_ref.beta = u_6ph_alphabeta_ref_Volts.beta;

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);
	theta = fmod(theta, 2.0f*UZ_PIf);


	//-get sector-----------------------------------------------------
	int sector_24 = getSector24(theta);

	//-get SV-----------------------------------------------------
	uint8_t SV01 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][0]; // first zero SV
	uint8_t SV1 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][1]; // first zero SV
	uint8_t SV2 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][2]; // first zero SV
	uint8_t SV3 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][3]; // first zero SV
	uint8_t SV4 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][4]; // first zero SV
	uint8_t SV02 = svpwm_4active_2zero_24sector_SV_sequence[version][sector_24-1][5]; // first zero SV

	//-get inv_Ttv-----------------------------------------------------

	const float (*inv_T_tv)[4];

	inv_T_tv = get_inv_T_tv_Matrix_4active_sector_24(version, sector_24);
	//inv_T_tv[a][b];

	//-calculate On-Times-----------------------------------------------------

	uz_6ph_alphabeta_t u_6ph_alphabeta_ref_norm;

	u_6ph_alphabeta_ref_norm.alpha = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.alpha;
	u_6ph_alphabeta_ref_norm.beta = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.beta;
	u_6ph_alphabeta_ref_norm.x = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.x;
	u_6ph_alphabeta_ref_norm.y = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.y;

	float T_V1 = inv_T_tv[0][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[0][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[0][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[0][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V2 = inv_T_tv[1][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[1][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[1][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[1][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V3 = inv_T_tv[2][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[2][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[2][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[2][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V4 = inv_T_tv[3][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[3][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[3][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[3][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
	float T_V01 = 0.0f;
	float T_V02 = 0.0f;
	if(CD1D2 == CONTINIOUS){
		T_V01 = T_V0/2.0f;
		T_V02 = T_V0/2.0f;
	}
	else if (CD1D2 == DISCONTINIOUS1){
		T_V01 = T_V0;
		T_V02 = 0.0f;
	}
	else {// (CD1D2 == DISCONTINIOUS2){
		T_V01 = 0.0f;
		T_V02 = T_V0;
	}

	//-calculate Dutycycles-----------------------------------------------------

	float Duty_Cycles[6] ={0};

	for(int i = 0; i < 6; i++) {

	    Duty_Cycles[i] = 0;

	    if (SV01 & (1 << i)) Duty_Cycles[i] += T_V01;
	    if (SV1  & (1 << i)) Duty_Cycles[i] += T_V1;
	    if (SV2  & (1 << i)) Duty_Cycles[i] += T_V2;
	    if (SV3  & (1 << i)) Duty_Cycles[i] += T_V3;
	    if (SV4  & (1 << i)) Duty_Cycles[i] += T_V4;
	    if (SV02 & (1 << i)) Duty_Cycles[i] += T_V02;
	}


	//-Saturation-----------------------------------------------------

	for(int i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], 1.0f, 0.0f);
		};

	//-Save to output-----------------------------------------------------

	output.Dutycles.system1.DutyCycle_A = Duty_Cycles[0];
	output.Dutycles.system1.DutyCycle_B = Duty_Cycles[1];
	output.Dutycles.system1.DutyCycle_C = Duty_Cycles[2];
	output.Dutycles.system2.DutyCycle_A = Duty_Cycles[3];
	output.Dutycles.system2.DutyCycle_B = Duty_Cycles[4];
	output.Dutycles.system2.DutyCycle_C = Duty_Cycles[5];


	//-phaseshiftoption based on SV-Order-----------------------------------------------------
	if (SV01 == 0){
		output.phaseshiftoption = 2; // 2-> EEEEEE;
	}
	else if (SV01 == 63){
		output.phaseshiftoption = 4; // 4 -> AAAAAA
	}
	else if (SV01 == 7){
		output.phaseshiftoption = 1; // 1-> AAAEEE
	}
	else{ // (SV01 == 56)
		output.phaseshiftoption = 3; // 3-> EEEAAA
	}

	return output;
}


struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2){

	uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts = uz_transformation_asym30deg_6ph_abc_to_alphabeta(u_6ph_abc1abc2_ref_Volts);

	return  uz_6ph_SVPWM_24_4_active_SV_alphabeta(u_6ph_alphabeta_ref_Volts, V_DC_Volts, version, CD1D2);
}



struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2){

	struct uz_DutyCycle_2x3ph_PhaseShiftOpt output = {0};

	//-Angle from ref-----------------------------------------------------
	uz_3ph_alphabeta_t u_alphabeta_ref;

	u_alphabeta_ref.alpha = u_6ph_alphabeta_ref_Volts.alpha;
	u_alphabeta_ref.beta = u_6ph_alphabeta_ref_Volts.beta;

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);
	theta = fmod(theta, 2.0f*UZ_PIf);


	//-get sector-----------------------------------------------------
	int sector_24 = getSector24(theta);

	//-get SV-----------------------------------------------------
	uint8_t SV01 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][0]; // first zero SV
	uint8_t SV1 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][1]; // 1st SV
	uint8_t SV2 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][2]; // 2nd SV
	uint8_t SV3 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][3]; // 3rd SV
	uint8_t SV4 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][4]; // 4th SV
	uint8_t SV5 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][5]; // 5th SV
	uint8_t SV02 = svpwm_5active_2zero_24sector_SV_sequence[version][sector_24-1][6]; // second zero SV

	//-get inv_Ttv-----------------------------------------------------

	const float (*inv_T_tv)[4];

	inv_T_tv = get_inv_T_tv_Matrix_5active_sector_24(version, sector_24);
	//inv_T_tv[a][b];

	//-calculate On-Tiems-----------------------------------------------------

	uz_6ph_alphabeta_t u_6ph_alphabeta_ref_norm;

	u_6ph_alphabeta_ref_norm.alpha = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.alpha;
	u_6ph_alphabeta_ref_norm.beta = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.beta;
	u_6ph_alphabeta_ref_norm.x = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.x;
	u_6ph_alphabeta_ref_norm.y = 1/V_DC_Volts * u_6ph_alphabeta_ref_Volts.y;

	float T_V1 = inv_T_tv[0][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[0][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[0][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[0][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V2 = inv_T_tv[1][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[1][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[1][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[1][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V3 = inv_T_tv[2][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[2][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[2][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[2][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V4 = inv_T_tv[3][0] * u_6ph_alphabeta_ref_norm.alpha + inv_T_tv[3][1] * u_6ph_alphabeta_ref_norm.beta + inv_T_tv[3][2] * u_6ph_alphabeta_ref_norm.x + inv_T_tv[3][3] * u_6ph_alphabeta_ref_norm.y;
	float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
	float T_V01 = 0.0f;
	float T_V02 = 0.0f;
	if(CD1D2 == CONTINIOUS){
		T_V01 = T_V0/2.0f;
		T_V02 = T_V0/2.0f;
	}
	else if (CD1D2 == DISCONTINIOUS1){
		T_V01 = T_V0;
		T_V02 = 0.0f;
	}
	else {// (CD1D2 == DISCONTINIOUS2){
		T_V01 = 0.0f;
		T_V02 = T_V0;
	}

	//-calculate Dutycycles-----------------------------------------------------

	float Duty_Cycles[6] ={0};

	for(int i = 0; i < 6; i++) {

	    Duty_Cycles[i] = 0;

	    if (SV01 & (1 << i)) Duty_Cycles[i] += T_V01;
	    if (SV1  & (1 << i)) Duty_Cycles[i] += T_V1/2.0f;
	    if (SV2  & (1 << i)) Duty_Cycles[i] += T_V2;
	    if (SV3  & (1 << i)) Duty_Cycles[i] += T_V3;
	    if (SV4  & (1 << i)) Duty_Cycles[i] += T_V4;
	    if (SV5  & (1 << i)) Duty_Cycles[i] += T_V1/2.0f;
	    if (SV02 & (1 << i)) Duty_Cycles[i] += T_V02;
	}


	//-Saturation-----------------------------------------------------

	for(int i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], 1.0f, 0.0f);
		};

	//-Save to output-----------------------------------------------------

	output.Dutycles.system1.DutyCycle_A = Duty_Cycles[0];
	output.Dutycles.system1.DutyCycle_B = Duty_Cycles[1];
	output.Dutycles.system1.DutyCycle_C = Duty_Cycles[2];
	output.Dutycles.system2.DutyCycle_A = Duty_Cycles[3];
	output.Dutycles.system2.DutyCycle_B = Duty_Cycles[4];
	output.Dutycles.system2.DutyCycle_C = Duty_Cycles[5];


	//-phaseshiftoption based on SV-Order-----------------------------------------------------
	if (SV01 == 0){
		output.phaseshiftoption = 2; // 2-> EEEEEE;
	}
	else if (SV01 == 63){
		output.phaseshiftoption = 4; // 4 -> AAAAAA
	}
	else if (SV01 == 7){
		output.phaseshiftoption = 1; // 1-> AAAEEE
	}
	else{ // (SV01 == 56)
		output.phaseshiftoption = 3; // 3-> EEEAAA
	}

	return output;
}



struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2){

	uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts = uz_transformation_asym30deg_6ph_abc_to_alphabeta(u_6ph_abc1abc2_ref_Volts);

	return  uz_6ph_SVPWM_24_5_active_SV_alphabeta(u_6ph_alphabeta_ref_Volts, V_DC_Volts, version, CD1D2);
}


struct carrier_shift_values uz_svm_6ph_calc_carrier_shift_value(int phaseshiftoption){

	struct carrier_shift_values output;

	if(phaseshiftoption == 1){ // SV01 = 7
		output.carrier_shift_1 = 0.5f;
		output.carrier_shift_2 = 0.0f;

	}else if(phaseshiftoption == 2){ // SV01 = 0
		output.carrier_shift_1 = 0.0f;
		output.carrier_shift_2 = 0.0f;

	}else if(phaseshiftoption == 3){ // SV01 = 56
		output.carrier_shift_1 = 0.0f;
		output.carrier_shift_2 = 0.5f;

	}else if(phaseshiftoption == 4){ // SV01 = 63
		output.carrier_shift_1 = 0.5f;
		output.carrier_shift_2 = 0.5f;

	}else{
		output.carrier_shift_1 = 0.0f;
		output.carrier_shift_2 = 0.0f;
	}




	return output;


}


