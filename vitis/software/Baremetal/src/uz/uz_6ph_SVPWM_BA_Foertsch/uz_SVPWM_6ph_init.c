#include "uz_SVPWM_6ph_init.h"

void uz_svm_6ph_calculate_and_shift_duty_cycles(int sector, const uz_sector_sv Zeiger[24], uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){
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
		    uz_PWM_SS_2L_set_triangle_shift(system_1, shift_system_1, shift_system_1, shift_system_1);// Global Data nur an Funktion übergeben und nict in Funktion darauf zugreifen
		    uz_PWM_SS_2L_set_triangle_shift(system_2, shift_system_2, shift_system_2, shift_system_2);
		}

output_with_test uz_SVPWM_4arrows_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){

	float upper_limit = 1.0f;
	float lower_limit = 0.0f;

	output_with_test out = {0};
	int i = 0, j = 0;
	int current_sector1_24 = 0;
	//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

	// atan2 calculates angle between -pi and +pi
	float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

	// nominates angle between 0 and 2 times pi
	SV_angle += (2.0f * M_PI_FLOAT);
	SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

	//calculate current sector between 1 and 24
	current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

	uz_inv_Ttv_sec_Matrix inv_Ttv;

	float U_ZK_Scaled = (1.0f/U_ZK);

	//scale transformation matrix
	for (i = 0; i <= 3; i++){
		for(j = 0; j <=3; j++){
			inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
		}
	}

// skalierung alpha beta
	//calculates switching times
	float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
	float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
	float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
	float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
	float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;

	//
	int S_V01 = paramspwm->sector_sv[current_sector1_24 - 1].first;
	int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
	int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
	int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
	int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
	int S_V02 = paramspwm->sector_sv[current_sector1_24 - 1].sixth;
	float Duty_Cycles[6] = {0};

	float T_V0_half = T_V0 / 2.0f;
	for(i=0;i<=5; i++){
		Duty_Cycles[i] = (T_V0_half) * paramspwm->SV_64[S_V01][i] + T_V1 * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i] + (T_V0_half) * paramspwm->SV_64[S_V02][i];
	};

	//Saturation
	for(i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
		};


	//Apply Phase Shift to the Inverter
	//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);








		out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
		out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
		out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
		out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
		out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
		out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

		//VSD Trafo für test
		uz_6ph_abc_t Vor_trafo;
		Vor_trafo.a1 = Duty_Cycles[0];
		Vor_trafo.b1 = Duty_Cycles[1];
		Vor_trafo.c1 = Duty_Cycles[2];
		Vor_trafo.a2 = Duty_Cycles[3];
		Vor_trafo.b2 = Duty_Cycles[4];
		Vor_trafo.c2 = Duty_Cycles[5];

		uz_6ph_alphabeta_t VSD_output;
		VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




		out.SV_angle = SV_angle;
		out.current_sector = current_sector1_24;
		out.alpha_trafo = VSD_output.alpha;
		out.beta_trafo = VSD_output.beta;
		out.x_trafo = VSD_output.x;
		out.y_trafo = VSD_output.y;
		out.nullplus_trafo = VSD_output.z1;
		out.nullminus_trafo = VSD_output.z2;
		out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
		out.t1 = T_V1;
		out.t2 = T_V2;
		out.t3 = T_V3;
		out.t4 = T_V4;
		return out;

	}

output_with_test uz_SVPWM_5arrows_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){

	float upper_limit = 1.0f;
	float lower_limit = 0.0f;

	output_with_test out = {0};
	int i = 0, j = 0;
	int current_sector1_24 = 0;
	//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

	// atan2 calculates angle between -pi and +pi
	float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

	// nominates angle between 0 and 2 times pi
	SV_angle += (2.0f * M_PI_FLOAT);
	SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

	//calculate current sector between 1 and 24
	current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

	uz_inv_Ttv_sec_Matrix inv_Ttv;

	float U_ZK_Scaled = (1.0f/U_ZK);

	//scale transformation matrix
	for (i = 0; i <= 3; i++){
		for(j = 0; j <=3; j++){
			inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
		}
	}

	//calculates switching times
	float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
	float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
	float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
	float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
	float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;



	int S_V01 = paramspwm->sector_sv[current_sector1_24 - 1].first;
	int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
	int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
	int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
	int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
	int S_V5 = paramspwm->sector_sv[current_sector1_24 -1].sixth;
	int S_V02 = paramspwm->sector_sv[current_sector1_24 - 1].seventh;
	float Duty_Cycles[6] = {0};

	float T_V0_half = T_V0 / 2.0f;
	float T_V1_half = T_V1 / 2.0f;
	for(i=0;i<=5; i++){
		Duty_Cycles[i] = (T_V0_half) * paramspwm->SV_64[S_V01][i] + T_V1_half * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i] + T_V1_half * paramspwm->SV_64[S_V5][i] + (T_V0_half) * paramspwm->SV_64[S_V02][i];
	};

	//Saturation
	for(i=0;i<=5; i++){
		Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
	};

	//Apply phase shift to the system
	//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);

	out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
	out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
	out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
	out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
	out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
	out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

	//VSD Trafo für test
	uz_6ph_abc_t Vor_trafo;
	Vor_trafo.a1 = Duty_Cycles[0];
	Vor_trafo.b1 = Duty_Cycles[1];
	Vor_trafo.c1 = Duty_Cycles[2];
	Vor_trafo.a2 = Duty_Cycles[3];
	Vor_trafo.b2 = Duty_Cycles[4];
	Vor_trafo.c2 = Duty_Cycles[5];

	uz_6ph_alphabeta_t VSD_output;
	VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




	out.SV_angle = SV_angle;
	out.current_sector = current_sector1_24;
	out.alpha_trafo = VSD_output.alpha;
	out.beta_trafo = VSD_output.beta;
	out.x_trafo = VSD_output.x;
	out.y_trafo = VSD_output.y;
	out.nullplus_trafo = VSD_output.z1;
	out.nullminus_trafo = VSD_output.z2;
	out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
	out.t1 = T_V1;
	out.t2 = T_V2;
	out.t3 = T_V3;
	out.t4 = T_V4;
	return out;
}

output_with_test uz_SVPWM_4arrows_discontinous_V1_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){
	float upper_limit = 1.0f;
		float lower_limit = 0.0f;

		output_with_test out = {0};
		int i = 0, j = 0;
		int current_sector1_24 = 0;
		//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

		// atan2 calculates angle between -pi and +pi
		float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

		// nominates angle between 0 and 2 times pi
		SV_angle += (2.0f * M_PI_FLOAT);
		SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

		//calculate current sector between 1 and 24
		current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

		uz_inv_Ttv_sec_Matrix inv_Ttv;

		float U_ZK_Scaled = (1.0f/U_ZK);

		//scale transformation matrix
		for (i = 0; i <= 3; i++){
			for(j = 0; j <=3; j++){
				inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
			}
		}


		//calculates switching times
		float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
		float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
		float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
		float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
		float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;

		//
		int S_V01 = paramspwm->sector_sv[current_sector1_24 - 1].first;
		int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
		int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
		int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
		int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
		float Duty_Cycles[6] = {0};


		for(i=0;i<=5; i++){
			Duty_Cycles[i] = T_V0 * paramspwm->SV_64[S_V01][i] + T_V1 * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i];
		};

		//Saturation
		for(i=0;i<=5; i++){
				Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
			};


		//Apply Phase Shift to the Inverter
		//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);








			out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
			out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
			out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
			out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
			out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
			out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

			//VSD Trafo für test
			uz_6ph_abc_t Vor_trafo;
			Vor_trafo.a1 = Duty_Cycles[0];
			Vor_trafo.b1 = Duty_Cycles[1];
			Vor_trafo.c1 = Duty_Cycles[2];
			Vor_trafo.a2 = Duty_Cycles[3];
			Vor_trafo.b2 = Duty_Cycles[4];
			Vor_trafo.c2 = Duty_Cycles[5];

			uz_6ph_alphabeta_t VSD_output;
			VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




			out.SV_angle = SV_angle;
			out.current_sector = current_sector1_24;
			out.alpha_trafo = VSD_output.alpha;
			out.beta_trafo = VSD_output.beta;
			out.x_trafo = VSD_output.x;
			out.y_trafo = VSD_output.y;
			out.nullplus_trafo = VSD_output.z1;
			out.nullminus_trafo = VSD_output.z2;
			out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
			out.t1 = T_V1;
			out.t2 = T_V2;
			out.t3 = T_V3;
			out.t4 = T_V4;
			return out;

}

output_with_test uz_SVPWM_4arrows_discontinous_V2_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){
	float upper_limit = 1.0f;
		float lower_limit = 0.0f;

		output_with_test out = {0};
		int i = 0, j = 0;
		int current_sector1_24 = 0;
		//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

		// atan2 calculates angle between -pi and +pi
		float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

		// nominates angle between 0 and 2 times pi
		SV_angle += (2.0f * M_PI_FLOAT);
		SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

		//calculate current sector between 1 and 24
		current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

		uz_inv_Ttv_sec_Matrix inv_Ttv;

		float U_ZK_Scaled = (1.0f/U_ZK);

		//scale transformation matrix
		for (i = 0; i <= 3; i++){
			for(j = 0; j <=3; j++){
				inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
			}
		}


		//calculates switching times
		float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
		float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
		float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
		float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
		float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;

		//Calculate Dwell Times
		int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
		int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
		int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
		int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
		int S_V02 = paramspwm->sector_sv[current_sector1_24 - 1].sixth;
		float Duty_Cycles[6] = {0};

		for(i=0;i<=5; i++){
			Duty_Cycles[i] = T_V1 * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i] + T_V0 * paramspwm->SV_64[S_V02][i];
		};

		//Saturation
		for(i=0;i<=5; i++){
				Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
			};


		//Apply Phase Shift to the Inverter
		//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);








			out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
			out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
			out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
			out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
			out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
			out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

			//VSD Trafo für test
			uz_6ph_abc_t Vor_trafo;
			Vor_trafo.a1 = Duty_Cycles[0];
			Vor_trafo.b1 = Duty_Cycles[1];
			Vor_trafo.c1 = Duty_Cycles[2];
			Vor_trafo.a2 = Duty_Cycles[3];
			Vor_trafo.b2 = Duty_Cycles[4];
			Vor_trafo.c2 = Duty_Cycles[5];

			uz_6ph_alphabeta_t VSD_output;
			VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




			out.SV_angle = SV_angle;
			out.current_sector = current_sector1_24;
			out.alpha_trafo = VSD_output.alpha;
			out.beta_trafo = VSD_output.beta;
			out.x_trafo = VSD_output.x;
			out.y_trafo = VSD_output.y;
			out.nullplus_trafo = VSD_output.z1;
			out.nullminus_trafo = VSD_output.z2;
			out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
			out.t1 = T_V1;
			out.t2 = T_V2;
			out.t3 = T_V3;
			out.t4 = T_V4;
			return out;
}

output_with_test uz_SVPWM_5arrows_discontinous_V1_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){
	float upper_limit = 1.0f;
		float lower_limit = 0.0f;

		output_with_test out = {0};
		int i = 0, j = 0;
		int current_sector1_24 = 0;
		//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

		// atan2 calculates angle between -pi and +pi
		float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

		// nominates angle between 0 and 2 times pi
		SV_angle += (2.0f * M_PI_FLOAT);
		SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

		//calculate current sector between 1 and 24
		current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

		uz_inv_Ttv_sec_Matrix inv_Ttv;

		float U_ZK_Scaled = (1.0f/U_ZK);

		//scale transformation matrix
		for (i = 0; i <= 3; i++){
			for(j = 0; j <=3; j++){
				inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
			}
		}

		//calculates switching times
		float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
		float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
		float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
		float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
		float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;



		int S_V01 = paramspwm->sector_sv[current_sector1_24 - 1].first;
		int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
		int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
		int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
		int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
		int S_V5 = paramspwm->sector_sv[current_sector1_24 -1].sixth;
		float Duty_Cycles[6] = {0};


		float T_V1_half = T_V1 / 2.0f;
		for(i=0;i<=5; i++){
			Duty_Cycles[i] = T_V0* paramspwm->SV_64[S_V01][i] + T_V1_half * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i] + T_V1_half * paramspwm->SV_64[S_V5][i];
		};

		//Saturation
		for(i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
		};

		//Apply phase shift to the system
		//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);

		out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
		out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
		out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
		out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
		out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
		out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

		//VSD Trafo für test
		uz_6ph_abc_t Vor_trafo;
		Vor_trafo.a1 = Duty_Cycles[0];
		Vor_trafo.b1 = Duty_Cycles[1];
		Vor_trafo.c1 = Duty_Cycles[2];
		Vor_trafo.a2 = Duty_Cycles[3];
		Vor_trafo.b2 = Duty_Cycles[4];
		Vor_trafo.c2 = Duty_Cycles[5];

		uz_6ph_alphabeta_t VSD_output;
		VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




		out.SV_angle = SV_angle;
		out.current_sector = current_sector1_24;
		out.alpha_trafo = VSD_output.alpha;
		out.beta_trafo = VSD_output.beta;
		out.x_trafo = VSD_output.x;
		out.y_trafo = VSD_output.y;
		out.nullplus_trafo = VSD_output.z1;
		out.nullminus_trafo = VSD_output.z2;
		out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;
		out.t1 = T_V1;
		out.t2 = T_V2;
		out.t3 = T_V3;
		out.t4 = T_V4;
		return out;
}

output_with_test uz_SVPWM_5arrows_discontinous_V2_6ph(const SVMPWM_Parameters* paramspwm, uz_6ph_alphabeta_t inputdata, float U_ZK, uz_PWM_SS_2L_t* system_1, uz_PWM_SS_2L_t* system_2){
	float upper_limit = 1.0f;
		float lower_limit = 0.0f;

		output_with_test out = {0};
		int i = 0, j = 0;
		int current_sector1_24 = 0;
		//float SV_angle = atan2f(inputdata.alpha, inputdata.beta);

		// atan2 calculates angle between -pi and +pi
		float SV_angle = atan2f(inputdata.beta, inputdata.alpha);

		// nominates angle between 0 and 2 times pi
		SV_angle += (2.0f * M_PI_FLOAT);
		SV_angle = fmodf(SV_angle, (2.0f * M_PI_FLOAT));

		//calculate current sector between 1 and 24
		current_sector1_24  = (int)(SV_angle * (12.0f / M_PI_FLOAT)) + 1;

		uz_inv_Ttv_sec_Matrix inv_Ttv;

		float U_ZK_Scaled = (1.0f/U_ZK);

		//scale transformation matrix
		for (i = 0; i <= 3; i++){
			for(j = 0; j <=3; j++){
				inv_Ttv.inv_Ttv_matrix[i][j] = U_ZK_Scaled * paramspwm->inv_Ttv_sec_Matrix[current_sector1_24 - 1].inv_Ttv_matrix[i][j];
			}
		}

		//calculates switching times
		float T_V1 = inv_Ttv.inv_Ttv_matrix[0][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[0][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[0][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[0][3]*inputdata.y;
		float T_V2 = inv_Ttv.inv_Ttv_matrix[1][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[1][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[1][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[1][3]*inputdata.y;
		float T_V3 = inv_Ttv.inv_Ttv_matrix[2][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[2][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[2][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[2][3]*inputdata.y;
		float T_V4 = inv_Ttv.inv_Ttv_matrix[3][0]*inputdata.alpha + inv_Ttv.inv_Ttv_matrix[3][1]*inputdata.beta + inv_Ttv.inv_Ttv_matrix[3][2]*inputdata.x + inv_Ttv.inv_Ttv_matrix[3][3]*inputdata.y;
		float T_V0 = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;



		int S_V1 = paramspwm->sector_sv[current_sector1_24 - 1].second;
		int S_V2 = paramspwm->sector_sv[current_sector1_24 - 1].third;
		int S_V3 = paramspwm->sector_sv[current_sector1_24 - 1].fourth;
		int S_V4 = paramspwm->sector_sv[current_sector1_24 - 1].fifth;
		int S_V5 = paramspwm->sector_sv[current_sector1_24 -1].sixth;
		int S_V02 = paramspwm->sector_sv[current_sector1_24 - 1].seventh;
		float Duty_Cycles[6] = {0};

		float T_V1_half = T_V1 / 2.0f;
		for(i=0;i<=5; i++){
			Duty_Cycles[i] = T_V1_half * paramspwm->SV_64[S_V1][i] + T_V2 * paramspwm->SV_64[S_V2][i] + T_V3 * paramspwm->SV_64[S_V3][i] + T_V4 * paramspwm->SV_64[S_V4][i] + T_V1_half * paramspwm->SV_64[S_V5][i] + T_V0 * paramspwm->SV_64[S_V02][i];
		};

		//Saturation
		for(i=0;i<=5; i++){
			Duty_Cycles[i] = uz_signals_saturation(Duty_Cycles[i], upper_limit, lower_limit);
		};

		//Apply phase shift to the system
		//uz_svm_6ph_calculate_and_shift_duty_cycles(current_sector1_24, paramspwm->sector_sv, system_1, system_2);

		out.DutyCycles.system1.DutyCycle_A = Duty_Cycles[0];
		out.DutyCycles.system1.DutyCycle_B = Duty_Cycles[1];
		out.DutyCycles.system1.DutyCycle_C = Duty_Cycles[2];
		out.DutyCycles.system2.DutyCycle_A = Duty_Cycles[3];
		out.DutyCycles.system2.DutyCycle_B = Duty_Cycles[4];
		out.DutyCycles.system2.DutyCycle_C = Duty_Cycles[5];

		//VSD Trafo für test
		uz_6ph_abc_t Vor_trafo;
		Vor_trafo.a1 = Duty_Cycles[0];
		Vor_trafo.b1 = Duty_Cycles[1];
		Vor_trafo.c1 = Duty_Cycles[2];
		Vor_trafo.a2 = Duty_Cycles[3];
		Vor_trafo.b2 = Duty_Cycles[4];
		Vor_trafo.c2 = Duty_Cycles[5];

		uz_6ph_alphabeta_t VSD_output;
		VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Vor_trafo);




		out.SV_angle = SV_angle;
		out.current_sector = current_sector1_24;
		out.alpha_trafo = VSD_output.alpha;
		out.beta_trafo = VSD_output.beta;
		out.x_trafo = VSD_output.x;
		out.y_trafo = VSD_output.y;
		out.nullplus_trafo = VSD_output.z1;
		out.nullminus_trafo = VSD_output.z2;
		out.gesamte_schaltzeit = 1.0f - T_V1 - T_V2 - T_V3 - T_V4;

		return out;
};
