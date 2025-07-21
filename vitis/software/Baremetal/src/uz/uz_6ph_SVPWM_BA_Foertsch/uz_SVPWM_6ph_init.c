#include "uz_SVPWM_6ph_init.h"


void uz_svm_6ph_calculate_and_shift_duty_cycles(int sector, uz_sector_sv Zeiger[24]){
			float shift_system_1 = 0.0f;
			float shift_system_2 = 0.0f;
		    switch (Zeiger[sector].first){
		        // shift system 2
		        case  56:
		            shift_system_1 = 0.0f;
		            shift_system_2 = 0.5f;

		            break;
		        // shift system 1
		        case  7:
		            shift_system_1 = 0.5f;
		            shift_system_2 = 0.0f;

		            break;
		        // shift both systems
		        case  63:
		            shift_system_1 = 0.5f;
		            shift_system_2 = 0.5f;

		            break;
		        // do nothing, no shift
		        default:
		        case  0:
		            shift_system_1 = 0.0f;
		            shift_system_2 = 0.0f;
		            break;
		    }
		    uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_0_to_5, shift_system_1, shift_system_1, shift_system_1);// Global Data nur an Funktio übergeben und nict in Funktion darauf zugreifen
		    uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_6_to_11, shift_system_2, shift_system_2, shift_system_2);
		};

struct uz_DutyCycle_2x3ph_t uz_SVPWM_6ph(SVMPWM_Parameters paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK){
	float upper_limit = 1.0f;
	float lower_limit = 0.0f;

	struct uz_DutyCycle_2x3ph_t out = {0};
	int i = 0, j = 0;
	int current_sector1_24 = 0;
	float SV_angle = 0.0f;
	//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);
	SV_angle = atan2f(inputdata.alpha, inputdata.beta);
	float AngleHelp = sqrtf(SV_angle * SV_angle);
	SV_angle = fmodf(AngleHelp, 2.0f * M_PI_FLOAT);




	current_sector1_24  = (int)floorf(SV_angle / (M_PI_FLOAT / 12.0f)) + 1;

	uz_inv_Ttv_sec_Matrix inv_Ttv;

	for (i = 0; i <= 3; i++){
		for(j = 0; j <=3; j++){
			inv_Ttv.inv_Ttv_matrix[i][j] = (1/U_ZK) * paramspwm.inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
		}
	}

	float Tsw = 1.0f;


	float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
	float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
	float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
	float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
	float T_V0 = Tsw - T_V1 - T_V2 - T_V3 - T_V4;

	int S_V01 = paramspwm.sector_sv[current_sector1_24 - 1].first;
	int S_V1 = paramspwm.sector_sv[current_sector1_24 - 1].second;
	int S_V2 = paramspwm.sector_sv[current_sector1_24 - 1].third;
	int S_V3 = paramspwm.sector_sv[current_sector1_24 - 1].fourth;
	int S_V4 = paramspwm.sector_sv[current_sector1_24 - 1].fifth;
	int S_V02 = paramspwm.sector_sv[current_sector1_24 - 1].sixth;
	float Duty_Cycles[6] = {0};

	for(i=0;i<=5; i++){
		Duty_Cycles[i] = (T_V0/2) * paramspwm.SV_64[S_V01][i] + T_V1 * paramspwm.SV_64[S_V1][i] + T_V2 * paramspwm.SV_64[S_V2][i] + T_V3 * paramspwm.SV_64[S_V3][i] + T_V4 * paramspwm.SV_64[S_V4][i] + (T_V0/2) * paramspwm.SV_64[S_V02][i];
	};
	// Begrenzung
	for(i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
		};


	//Apply Phase Shift to the Inverter
	uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm.sector_sv);

		out.system1.DutyCycle_A = Duty_Cycles[0];
		out.system1.DutyCycle_B = Duty_Cycles[1];
		out.system1.DutyCycle_C = Duty_Cycles[2];
		out.system2.DutyCycle_A = Duty_Cycles[3];
		out.system2.DutyCycle_B = Duty_Cycles[4];
		out.system2.DutyCycle_C = Duty_Cycles[5];


		return out;
	};

