#include "uz_CSVPWM_init.h"

#define MAKRO_INVERT_DUTYCYCLE(val) (1.0f - (val))


void uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector, float *shift_system_1, float *shift_system_2);

output CSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_0_63(SVMPWM_Parameters paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK){

	output out = {0};
	int i = 0, j = 0;
	int current_sector1_24 = 0;

	float SV_angle = atan2(inputdata.alpha, inputdata.beta);
	SV_angle = fmod(SV_angle, 2*M_PI);

	current_sector1_24  = (int)floor(SV_angle / (M_PI / 12.0)) + 1;


	uz_inv_Ttv_sec_Matrix inv_Ttv;

	for (i = 0; i<5; i++){
		for(j = 0; j<5; j++){
			inv_Ttv[i][j] = (1/U_ZK) * paramspwm.inv_Ttv_sec_Matrix[current_sector1_24 - 1][i][j];
		}
	}

	int Tsw = 1;


	float T_V1 = inv_Ttv[0][0]*inputdata.alpha + inv_Ttv[0][1]*inputdata.beta + inv_Ttv[0][2]*inputdata.x + inv_Ttv[0][3]*inputdata.y;
	float T_V2 = inv_Ttv[1][0]*inputdata.alpha + inv_Ttv[1][1]*inputdata.beta + inv_Ttv[1][2]*inputdata.x + inv_Ttv[1][3]*inputdata.y;
	float T_V3 = inv_Ttv[2][0]*inputdata.alpha + inv_Ttv[2][1]*inputdata.beta + inv_Ttv[2][2]*inputdata.x + inv_Ttv[2][3]*inputdata.y;
	float T_V4 = inv_Ttv[3][0]*inputdata.alpha + inv_Ttv[3][1]*inputdata.beta + inv_Ttv[3][2]*inputdata.x + inv_Ttv[3][3]*inputdata.y;
	float T_V0 = Tsw - T_V1 - T_V2 - T_V3 - T_V4;

	int S_V01 = paramspwm.sector_sv[current_sector1_24 - 1].first;
	int S_V1 = paramspwm.sector_sv[current_sector1_24 - 1].second;
	int S_V2 = paramspwm.sector_sv[current_sector1_24 - 1].third;
	int S_V3 = paramspwm.sector_sv[current_sector1_24 - 1].fourth;
	int S_V4 = paramspwm.sector_sv[current_sector1_24 - 1].fifth;
	int S_V02 = paramspwm.sector_sv[current_sector1_24 - 1].sixth;


	float Duty_Cycles[6] = {0};

	for(i=0;i<6; i++){
		Duty_Cycles[i] = T_V1 * paramspwm.SV_64[S_V1][i] + T_V2 * paramspwm.SV_64[S_V2][i] + T_V3 * paramspwm.SV_64[S_V3][i] + T_V4 * paramspwm.SV_64[S_V4][i] + (T_V0/2) * paramspwm.SV_64[64][i];
	}



	// Begrenzung
		if (Duty_Cycles[0] > 1.0f) {
			Duty_Cycles[0] = 1.0f;
		} else if (Duty_Cycles[0] < 0.0f) {
			Duty_Cycles[0] = 0.0f;
		};

		if (Duty_Cycles[1] > 1.0f) {
			Duty_Cycles[1] = 1.0f;
		} else if (Duty_Cycles[1] < 0.0f) {
			Duty_Cycles[1] = 0.0f;
		};

		if (Duty_Cycles[2] > 1.0f) {
			Duty_Cycles[2] = 1.0f;
		} else if (Duty_Cycles[2] < 0.0f) {
			Duty_Cycles[2] = 0.0f;
		};

		if (Duty_Cycles[3] > 1.0f) {
			Duty_Cycles[3] = 1.0f;
		} else if (Duty_Cycles[3] < 0.0f) {
			Duty_Cycles[3] = 0.0f;
		};

		if (Duty_Cycles[4] > 1.0f) {
			Duty_Cycles[4] = 1.0f;
		} else if (Duty_Cycles[4] < 0.0f) {
			Duty_Cycles[4] = 0.0f;
		};

		if (Duty_Cycles[5] > 1.0f) {
			Duty_Cycles[5] = 1.0f;
		} else if (Duty_Cycles[5] < 0.0f) {
			Duty_Cycles[5] = 0.0f;
		};



	uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles[0], current_sector1_24, &out.shift_system1, &out.shift_system2);

	out.Dutycycles.system1.DutyCycle_A = Duty_Cycles[0];
	out.Dutycycles.system1.DutyCycle_B = Duty_Cycles[1];
	out.Dutycycles.system1.DutyCycle_C = Duty_Cycles[2];
	out.Dutycycles.system2.DutyCycle_A = Duty_Cycles[3];
	out.Dutycycles.system2.DutyCycle_B = Duty_Cycles[4];
	out.Dutycycles.system2.DutyCycle_C = Duty_Cycles[5];


	return out;


	void uz_svm_6ph_calculate_and_shift_duty_cycles(float Duty_Cycles[6], int sector, float *shift_system_1, float *shift_system_2){
	    switch (sector){
	        // shift system 2 and invert its DutyCycles
	        case  1:
	        case  2:
	        case  9:
	        case 10:
	        case 17:
	        case 18:
	            *shift_system_1 = 0.0f;
	            *shift_system_2 = 0.5f;
	            Duty_Cycles[3] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[3]);
	            Duty_Cycles[4] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[4]);
	            Duty_Cycles[5] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[5]);
	            break;
	        // shift system 1 and invert its DutyCycles
	        case  5:
	        case  6:
	        case 13:
	        case 14:
	        case 21:
	        case 22:
	            *shift_system_1 = 0.5f;
	            *shift_system_2 = 0.0f;
	            Duty_Cycles[0] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[0]);
	            Duty_Cycles[1] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[1]);
	            Duty_Cycles[2] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[2]);
	            break;
	        // shift both systems and invert both DutyCycles
	        case  7:
	        case  8:
	        case 15:
	        case 16:
	        case 23:
	        case 24:
	            *shift_system_1 = 0.5f;
	            *shift_system_2 = 0.5f;
	            Duty_Cycles[0] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[0]);
	            Duty_Cycles[1] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[1]);
	            Duty_Cycles[2] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[2]);
	            Duty_Cycles[3] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[3]);
	            Duty_Cycles[4] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[4]);
	            Duty_Cycles[5] = MAKRO_INVERT_DUTYCYCLE(Duty_Cycles[5]);
	            break;
	        // do nothing, no shift
	        default:
	        case  3:
	        case  4:
	        case 11:
	        case 12:
	        case 19:
	        case 20:
	            *shift_system_1 = 0.0f;
	            *shift_system_2 = 0.0f;
	            break;
	    }









































/*uz_cmp_signal CSVPWM_24_2L_1ML_1M_v1(u_ref_6ph_alphabeta_t inputdata, float U_ZK){

	uz_cmp_signal cmp_signals = {0}; // Setzt alle Compare Signale auf Null

	int current_sector1_24 = 0;
	float a_A = 0, a_B = 0, a_C = 0, a_X = 0, a_Y = 0, a_Z = 0;

	SV_angle = atan2(inputdata.alpha, inputdata.beta);
	SV_angle = mod(SV_angle, 2*M_PI);

	int current_sector1_24  = (int)floor(SV_angle / (M_PI / 12.0)) + 1;


	uz_sector_sv sector_sv[24] = {
	    {63, 43, 41,  9,  8,  0},   // 1
	    {63, 43, 11,  9,  1,  0},   // 2
	    {56, 25,  9, 11,  3,  7},   // 3
	    {56, 25, 27, 11, 15,  7},   // 4
	    { 0, 10, 11, 27, 31, 63},   // 5
	    { 0, 10, 26, 27, 59, 63},   // 6
	    { 7, 19, 27, 26, 58, 56},   // 7
	    { 7, 19, 18, 26, 24, 56},   // 8
	    {63, 30, 26, 18, 16,  0},   // 9
	    {63, 30, 22, 18,  2,  0},   // 10
	    {56, 50, 18, 22,  6,  7},   // 11
	    {56, 50, 54, 22, 23,  7},   // 12
	    { 0, 20, 22, 54, 55, 63},   // 13
	    { 0, 20, 52, 54, 62, 63},   // 14
	    { 7, 38, 54, 52, 60, 56},   // 15
	    { 7, 38, 36, 52, 48, 56},   // 16
	    {63, 53, 52, 36, 32,  0},   // 17
	    {63, 53, 37, 36,  4,  0},   // 18
	    {56, 44, 36, 37,  5,  7},   // 19
	    {56, 44, 45, 37, 39,  7},   // 20
	    { 0, 33, 37, 45, 47, 63},   // 21
	    { 0, 33, 41, 45, 61, 63},   // 22
	    { 7, 13, 45, 41, 57, 56},   // 23
	    { 7, 13,  9, 41, 40, 56}    // 24
	};

	uz_sector_sv Order_of_switching[24] = {
	    {3, 1, 0, 4, 0, 2},
	    {4, 2, 0, 3, 0, 1},
	    {0, 2, 4, 3, 1, 0},
	    {0, 1, 3, 4, 2, 0},
	    {1, 0, 3, 0, 2, 4},
	    {2, 0, 4, 0, 1, 3},
	    {2, 4, 0, 1, 0, 3},
	    {1, 3, 0, 2, 0, 4},
	    {0, 3, 1, 2, 4, 0},
	    {0, 4, 2, 1, 3, 0},
	    {4, 0, 2, 0, 3, 1},
	    {3, 0, 1, 0, 4, 2},
	    {3, 1, 0, 4, 0, 2},
	    {4, 2, 0, 3, 0, 1},
	    {0, 2, 4, 3, 1, 0},
	    {0, 1, 3, 4, 2, 0},
	    {1, 0, 3, 0, 2, 4},
	    {2, 0, 4, 0, 1, 3},
	    {2, 4, 0, 1, 0, 3},
	    {1, 3, 0, 2, 0, 4},
	    {0, 3, 1, 2, 4, 0},
	    {0, 4, 2, 1, 3, 0},
	    {4, 0, 2, 0, 3, 1},
	    {3, 0, 1, 0, 4, 2}
	};

	//transformationsmatrizen nach Sektoren

	uz_inv_Ttv_sec_Matrix inv_Ttv_sec_Matrix[24] = {
	    // 1
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 2
	    {.inv_Ttv_matrix = {
	        { 0.866025403784439, -1.500000000000000, -0.866025403784439, -1.500000000000000 },
	        { -0.866025403784439, 3.232050807568877, 0.866025403784439, -0.232050807568877 },
	        { 1.732050807568877, -1.732050807568878, -1.732050807568878, 1.732050807568877 },
	        { -0.232050807568878, 0.866025403784439, 3.232050807568878, -0.866025403784439 },
	    }},
	    // 3
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 4
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 5
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 6
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 7
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 8
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 9
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 10
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 11
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 12
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 13
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 14
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 15
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 16
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 17
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 18
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 19
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 20
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 21
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 22
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 23
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	    // 24
	    {.inv_Ttv_matrix = {
	        { -0.000000000000000, 1.732050807568877, -0.000000000000000, -1.732050807568877 },
	        { 0.866025403784439, -3.232050807568877, -0.866025403784438, 0.232050807568877 },
	        { 0.633974596215561, 2.366025403784439, 2.366025403784439, 0.633974596215562 },
	        { 0.232050807568878, -0.866025403784439, -3.232050807568878, 0.866025403784439 },
	    }},
	};


	uz_inv_Ttv_sec_Matrix inv_Ttv = (1/U_ZK) * inv_Ttv_sec_Matrix[current_sector1_24];

	float Tsw = 1; //normierung der gesamten Schaltzeit auf 1

	float T_V1 = inv_Ttv[0][0]*inputdata.alpha + inv_Ttv[0][1]*inputdata.beta + inv_Ttv[0][2]*inputdata.x + inv_Ttv[0][3]*inputdata.y;
	float T_V2 = inv_Ttv[1][0]*inputdata.alpha + inv_Ttv[1][1]*inputdata.beta + inv_Ttv[1][2]*inputdata.x + inv_Ttv[1][3]*inputdata.y;
	float T_V3 = inv_Ttv[2][0]*inputdata.alpha + inv_Ttv[2][1]*inputdata.beta + inv_Ttv[2][2]*inputdata.x + inv_Ttv[2][3]*inputdata.y;
	float T_V4 = inv_Ttv[3][0]*inputdata.alpha + inv_Ttv[3][1]*inputdata.beta + inv_Ttv[3][2]*inputdata.x + inv_Ttv[3][3]*inputdata.y;
	float T_V0 = Tsw - T_V1 - T_V2 - T_V3 - T_V4;

	//Berechnung Dutycycles
	float dutycycles[6] = {0};

	dutycycles[0] 	= (T_V0/2) + T_V4 + T_V3 + T_V2 + T_V1;
	dutycycles[1] 	= (T_V0/2) + T_V4 + T_V3 + T_V2;
	dutycycles[2]	= (T_V0/2) + T_V4 + T_V3;
	dutycycles[3] 	= (T_V0/2) + T_V4;
	dutycycles[4] 	= (T_V0/2);


	a_A = dutycycles[(Order_of_Switching[current_sector1_24].first) + 1];
	a_B = dutycycles[(Order_of_Switching[current_sector1_24].second) + 1];
	a_C = dutycycles[(Order_of_Switching[current_sector1_24].third) + 1];
	a_X = dutycycles[(Order_of_Switching[current_sector1_24].fourth) + 1];
	a_Y = dutycycles[(Order_of_Switching[current_sector1_24].fifth) + 1];
	a_Z = dutycycles[(Order_of_Switching[current_sector1_24].sixth) + 1];


	// Betrachtung der Umschaltrichtung nach Sektor

	if (curr_sector_24 == 2 || curr_sector_24 == 3 || curr_sector_24 == 10 || curr_sector_24 == 11 || curr_sector_24 == 18 || curr_sector_24 == 19) {

	    a_X = 1.0f - a_X;
	    a_Y = 1.0f - a_Y;
	    a_Z = 1.0f - a_Z;
	} else if (curr_sector_24 == 6 || curr_sector_24 == 7 || curr_sector_24 == 14 || curr_sector_24 == 15 || curr_sector_24 == 22 || curr_sector_24 == 23) {

	    a_A = 1.0f - a_A;
	    a_B = 1.0f - a_B;
	    a_C = 1.0f - a_C;
	} else if (curr_sector_24 == 0 || curr_sector_24 == 1 || curr_sector_24 == 8 || curr_sector_24 == 9 || curr_sector_24 == 16 || curr_sector_24 == 17) {

	    a_A = 1.0f - a_A;
	    a_B = 1.0f - a_B;
	    a_C = 1.0f - a_C;
	    a_X = 1.0f - a_X;
	    a_Y = 1.0f - a_Y;
	    a_Z = 1.0f - a_Z;
	}


	// Begrenzung
	if (a_A > 1.0f) {
	    a_A = 1.0f;
	} else if (a_A < 0.0f) {
	    a_A = 0.0f;
	}

	if (a_B > 1.0f) {
	    a_B = 1.0f;
	} else if (a_B < 0.0f) {
	    a_B = 0.0f;
	}

	if (a_C > 1.0f) {
	    a_C = 1.0f;
	} else if (a_C < 0.0f) {
	    a_C = 0.0f;
	}

	if (a_X > 1.0f) {
	    a_X = 1.0f;
	} else if (a_X < 0.0f) {
	    a_X = 0.0f;
	}

	if (a_Y > 1.0f) {
	    a_Y = 1.0f;
	} else if (a_Y < 0.0f) {
	    a_Y = 0.0f;
	}

	if (a_Z > 1.0f) {
	    a_Z = 1.0f;
	} else if (a_Z < 0.0f) {
	    a_Z = 0.0f;
	}


	// Ausgabe


	cmp_signals.cmpa = a_A;
	cmp_signals.cmpb = a_B;
	cmp_signals.cmpc = a_C;
	cmp_signals.cmpx = a_X;
	cmp_signals.cmpy = a_Y;
	cmp_signals.cmpz = a_Z;

	return cmp_signals;

};
*/
