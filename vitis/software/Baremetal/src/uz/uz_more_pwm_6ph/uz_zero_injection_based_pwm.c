/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2025 Josef Knoblach
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "uz_zero_injection_based_pwm.h"
#include "../uz_HAL.h"
#include <math.h>
#include "../uz_signals/uz_signals.h"
#include "uz_zero_injection_pwm_3ph.h"

#define SQRT_3_HALF sqrt(3.0f)/2.0f





struct uz_DutyCycle_2x3ph_t uz_add_zerosequence_and_saturate(uz_6ph_abc_t u_abc1abc2_ref, float u_n1, float u_n2, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};
	// adding zero sequence

	uz_3ph_abc_t u_abc_ref1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	uz_3ph_abc_t u_abc_ref2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_add_zerosequence_and_saturate_3ph(u_abc_ref1, u_n1, V_dc_volts);
	output.system2 = uz_add_zerosequence_and_saturate_3ph(u_abc_ref2, u_n2, V_dc_volts);

	return output;
}



int getSector24(float theta){

	theta = uz_bring_angle_between_0_2_pi(theta);

	int sector_24 = floor( theta/(M_PI/12.0f) - fmod(theta, M_PI/12.0f) ) + 1;
	if(sector_24 > 24){
		sector_24 = 1;
	}
	return sector_24;
}



int getSector12(float theta){

	theta = uz_bring_angle_between_0_2_pi(theta);

	int sector_12 = floor( theta/(M_PI/6.0f) - fmod(theta, M_PI/6.0f) ) + 1;
	if(sector_12 > 12){
		sector_12 = 1;
	}
	return sector_12;
}









struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_CSVPWM_24_4_active_SV_V1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_CSVPWM_24_4_active_SV_V2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_5_active_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_CSVPWM_24_5_active_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}



struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	// alpha-beta in both systems
	uz_3ph_alphabeta_t u_alphabeta_ref_sys1 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys1);
	uz_3ph_alphabeta_t u_alphabeta_ref_sys2 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys2);

	// angle in both systems

	float theta_1 = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref_sys1);
	float theta_2 = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref_sys2);

	theta_1 = fmod(theta_1, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	theta_2 = fmod(theta_2, 2.0f*M_PI/3.0f);


	// get sector
	int sector_24_sys1 = getSector24(theta_1);
	int sector_24_sys2 = getSector24(theta_2);


	// calculation of zero sequence
	float u_n1 = 0;
	float u_n2 = 0;

	float u_max1 = uz_getmax_3ph_abc(u_abc_sys1);
	float u_min1 = uz_getmin_3ph_abc(u_abc_sys1);
	float u_mid1 = uz_getmid_3ph_abc(u_abc_sys1);

	float u_max2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min2 = uz_getmin_3ph_abc(u_abc_sys2);
	float u_mid2 = uz_getmid_3ph_abc(u_abc_sys2);


	if (sector_24_sys1 <= 1){
	    u_n1 = u_max1 * (sqrt(3)/2-1);
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 == 4 || sector_24_sys1 == 5){
	    u_n1 = u_min1 * (SQRT_3_HALF-1.0f);
	}
	else if (sector_24_sys1 == 6 || sector_24_sys1 == 7){
	    u_n1 = u_mid1/2;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = u_max1 * (SQRT_3_HALF-1.0f);
	}


	if (sector_24_sys2 <= 1){
	    u_n2 = u_max2 * (sqrt(3)/2-1);
	}
	else if (sector_24_sys2 == 2){
	    u_n2 = u_mid2/2;
	}
	else if (sector_24_sys2 == 3){
	    u_n2 = u_mid2/2;
	}
	else if (sector_24_sys2 == 4 || sector_24_sys2 == 5){
	    u_n2 = u_min2 * (SQRT_3_HALF-1.0f);
	}
	else if (sector_24_sys2 == 6 || sector_24_sys2 == 7){
	    u_n2 = u_mid2/2;
	}
	else if (sector_24_sys2 >= 8){
	    u_n2 = u_max2 * (SQRT_3_HALF-1.0f);
	}

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}



struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	// alpha-beta in both systems
	uz_3ph_alphabeta_t u_alphabeta_ref_sys1 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys1);
	uz_3ph_alphabeta_t u_alphabeta_ref_sys2 = uz_transformation_3ph_abc_to_alphabeta(u_abc_sys2);

	// angle in both systems
	float theta_1 = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref_sys1);
	float theta_2 = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref_sys2);

	theta_1 = fmod(theta_1, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	theta_2 = fmod(theta_2, 2.0f*M_PI/3.0f);

	// get sector
	int sector_24_sys1 = getSector24(theta_1);
	int sector_24_sys2 = getSector24(theta_2);

	// calculation of zero sequence
	float u_n1 = 0;
	float u_n2 = 0;

	float u_max_1 = uz_getmax_3ph_abc(u_abc_sys1);
	float u_min_1 = uz_getmin_3ph_abc(u_abc_sys1);
	float u_mid_1 = uz_getmid_3ph_abc(u_abc_sys1);

	float u_max_2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min_2 = uz_getmin_3ph_abc(u_abc_sys2);
	float u_mid_2 = uz_getmid_3ph_abc(u_abc_sys2);



	if (sector_24_sys1 <= 1){
	    u_n1 = -u_min_1-SQRT_3_HALF*u_max_1;
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = u_mid_1/2;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 = u_mid_1/2;
	}
	else if (sector_24_sys1 == 4){
	    u_n1 = -u_max_1 - SQRT_3_HALF*u_min_1;
	}
	else if (sector_24_sys1 == 5){
	    u_n1 = -u_max_1 - SQRT_3_HALF*u_min_1;
	}
	else if (sector_24_sys1 == 6){
	    u_n1 = u_mid_1/2;
	}
	else if (sector_24_sys1 == 7){
	    u_n1 = u_mid_1/2;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = -u_min_1-SQRT_3_HALF*u_max_1;
	}


	if (sector_24_sys2 <= 1){
	    u_n2 = -u_min_2-SQRT_3_HALF*u_max_2;
	}
	else if (sector_24_sys2 == 2){
		u_n2 = u_mid_2/2;
	}
	else if (sector_24_sys2 == 3){
		u_n2 = u_mid_2/2;
	}
	else if (sector_24_sys2 == 4){
		u_n2 = -u_max_2 - SQRT_3_HALF*u_min_2;
	}
	else if (sector_24_sys2 == 5){
		u_n2 = -u_max_2 - SQRT_3_HALF*u_min_2;
	}
	else if (sector_24_sys2 == 6){
		u_n2 = u_mid_2/2;
	}
	else if (sector_24_sys2 == 7){
		u_n2 = u_mid_2/2;
	}
	else if (sector_24_sys2 >= 8){
		u_n2 = -u_min_2-SQRT_3_HALF*u_max_2;
	}


	// adding zero sequence
	output = uz_add_zerosequence_and_saturate(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}



struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_5_active_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};


	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};


	// calculation of zero sequence
	float u_max_1 = uz_getmax_3ph_abc(u_abc_sys1);
	float u_min_1 = uz_getmin_3ph_abc(u_abc_sys1);

	float u_max_2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min_2 = uz_getmin_3ph_abc(u_abc_sys2);

	float u_n1 = -(u_max_1 + u_min_1)/2.0f;
	float u_n2 = -(u_max_2 + u_min_2)/2.0f;


	// adding zero sequence
	output = uz_add_zerosequence_and_saturate(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}



struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_2M_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_2M_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_2M_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_2L_1ML_2M_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_1M_v1_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_1M_v1_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_1M_v2_D1_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts){
	// reference in abc1abc2
	uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6ph_alphabeta_ref_Volts);

	return uz_6ph_DSVPWM_24_3L_1M_v2_D2_abc_INJ(u_6ph_abc1abc2_ref_Volts, V_DC_Volts);
}





struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	return output;
}










