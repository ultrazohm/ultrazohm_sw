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

#include "../uz_6ph_SVPWM/uz_pwm_help_functions.h"

#define SQRT_3_HALF sqrtf(3.0f)/2.0f
#define SQRT_3 sqrtf(3.0f)






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
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

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
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

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
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

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

	float u_max_2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min_2 = uz_getmin_3ph_abc(u_abc_sys2);


	if (sector_24_sys1 <= 1){
	    u_n1 = -V_DC_Volts/2.0f - u_min_1;
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = -V_DC_Volts/2.0f - u_min_1;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 =V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 4){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 5){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 6){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 7){
	    u_n1 = -V_DC_Volts/2.0f - u_min_1;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = -V_DC_Volts/2.0f - u_min_1;
	}


	if (sector_24_sys2 <= 1){
	    u_n2 = -V_DC_Volts/2.0f - u_min_2;
	}
	else if (sector_24_sys2 == 2){
		u_n2 = -V_DC_Volts/2.0f - u_min_2;
	}
	else if (sector_24_sys2 == 3){
		u_n2 =V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 4){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 5){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 6){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 7){
		u_n2 = -V_DC_Volts/2.0f - u_min_2;
	}
	else if (sector_24_sys2 >= 8){
		u_n2 = -V_DC_Volts/2.0f - u_min_2;
	}

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
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

	float u_max_2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min_2 = uz_getmin_3ph_abc(u_abc_sys2);




	if (sector_24_sys1 <= 1){
	    u_n1 = -u_min_1 - SQRT_3*u_max_1 + V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 = - u_min_1 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 4){
	    u_n1 = -u_max_1 - SQRT_3*u_min_1 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 5){
	    u_n1 = -u_max_1 - SQRT_3*u_min_1 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 6){
	    u_n1 = - u_min_1 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 7){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = -u_min_1 - SQRT_3*u_max_1 + V_DC_Volts/2.0f;
	}


	if (sector_24_sys2 <= 1){
	    u_n2 = -u_min_2 - SQRT_3*u_max_2 + V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 2){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 3){
		u_n2 = - u_min_2 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 4){
		u_n2 = -u_max_2 - SQRT_3*u_min_2 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 5){
		u_n2 = -u_max_2 - SQRT_3*u_min_2 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 6){
		u_n2 = - u_min_2 - V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 7){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 >= 8){
		u_n2 = -u_min_2 - SQRT_3*u_max_2 + V_DC_Volts/2.0f;
	}


	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
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

	float u_max_2 = uz_getmax_3ph_abc(u_abc_sys2);
	float u_min_2 = uz_getmin_3ph_abc(u_abc_sys2);



	if (sector_24_sys1 <= 1){
	    u_n1 = u_max_1 * (SQRT_3-1) -V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 2){
	    u_n1 = - u_min_1 -V_DC_Volts/2.0f;
	}
	else if (sector_24_sys1 == 3){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 4){
	    u_n1 = V_DC_Volts/2.0f + u_min_1 * (SQRT_3-1);
	}
	else if (sector_24_sys1 == 5){
	    u_n1 = V_DC_Volts/2.0f + u_min_1 * (SQRT_3 -1);
	}
	else if (sector_24_sys1 == 6){
	    u_n1 = V_DC_Volts/2.0f - u_max_1;
	}
	else if (sector_24_sys1 == 7){
	    u_n1 = -V_DC_Volts/2.0f - u_min_1;
	}
	else if (sector_24_sys1 >= 8){
	    u_n1 = u_max_1 * (SQRT_3-1) -V_DC_Volts/2.0f;
	}


	if (sector_24_sys2 <= 1){
		u_n2 = u_max_2 * (SQRT_3-1) -V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 2){
		u_n2 = - u_min_2 -V_DC_Volts/2.0f;
	}
	else if (sector_24_sys2 == 3){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 4){
		u_n2 = V_DC_Volts/2.0f + u_min_2 * (SQRT_3-1);
	}
	else if (sector_24_sys2 == 5){
		u_n2 = V_DC_Volts/2.0f + u_min_2 * (SQRT_3 -1);
	}
	else if (sector_24_sys2 == 6){
		u_n2 = V_DC_Volts/2.0f - u_max_2;
	}
	else if (sector_24_sys2 == 7){
		u_n2 = -V_DC_Volts/2.0f - u_min_2;
	}
	else if (sector_24_sys2 >= 8){
	    u_n2 = u_max_2 * (SQRT_3-1) -V_DC_Volts/2.0f;
	}

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}





float uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_1M_v2_D2(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;


	if (sector_24 <= 1){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 2){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 3){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 4){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 5){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 6){
		u_zero =- u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 7){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 >= 8){
		u_zero = V_DC_Volts/2.0f - u_max;
	}

	return u_zero;
}


struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_1M_v2_D2(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_1M_v2_D2(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}







float uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D1(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero = V_DC_Volts/2.0f  - u_min/2.0f - u_max * (SQRT_3_HALF+1.0f/2.0f);
	}
	else if (sector_24 == 2){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 3){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 4){
		u_zero = V_DC_Volts/2.0f - u_max/2.0f + u_min * (SQRT_3_HALF-1.0f/2.0f);
	}
	else if (sector_24 == 5){
		u_zero = -V_DC_Volts/2.0f   -u_max/2.0f  - u_min * (SQRT_3_HALF+1.0f/2.0f) ;
	}
	else if (sector_24 == 6){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 7){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 >= 8){
		u_zero = -V_DC_Volts/2.0f - u_min/2 + u_max * (SQRT_3_HALF-1.0f/2.0f);
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D1(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D1(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D2(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);


	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero =  -V_DC_Volts/2.0f - u_min   + u_min/2  + u_max * (sqrtf(3.0f)/2.0f-1.0f/2.0f);
	}
	else if (sector_24 == 2){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 3){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 4){
		u_zero = -V_DC_Volts/2.0f   -u_max/2.0f   - u_min * (sqrtf(3.0f)/2.0f + 1.0f/2.0f);
	}
	else if (sector_24 == 5){
		u_zero = V_DC_Volts/2.0f - u_max/2.0f   + u_min * (sqrtf(3.0f)/2.0f-1.0f/2.0f);
	}
	else if (sector_24 == 6){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 7){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 >= 8){
		u_zero = V_DC_Volts/2.0f  - u_min/2.0f  - u_max * (sqrtf(3.0f)/2.0f + 1.0f/2.0f);
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D2(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_2M_D2(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D1(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero = -(SQRT_3_HALF+0.5f)*u_max - 0.5f*u_min + V_DC_Volts/2.0f;
	}
	else if (sector_24 == 2){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 3){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 4){
		u_zero = -(SQRT_3_HALF+0.5)*u_min - 0.5f*u_max - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 5){
		u_zero = -(SQRT_3_HALF+0.5f)*u_min - 0.5f*u_max - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 6){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 7){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 >= 8){
		u_zero = -(SQRT_3_HALF+0.5f)*u_max - 0.5*u_min + V_DC_Volts/2.0f;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D1(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D1(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}


float uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D2(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero = -V_DC_Volts/2.0f - 0.5f*u_min + (SQRT_3_HALF-0.5f)*u_max;
	}
	else if (sector_24 == 2){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 3){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 4){
		u_zero = V_DC_Volts/2.0f - 0.5f*u_max + (SQRT_3_HALF-0.5f)*u_min;
	}
	else if (sector_24 == 5){
		u_zero = V_DC_Volts/2.0f - 0.5f*u_max + (SQRT_3_HALF-0.5f)*u_min;
	}
	else if (sector_24 == 6){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 7){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 >= 8){
		u_zero = -V_DC_Volts/2.0f - 0.5f*u_min + (SQRT_3_HALF-0.5f)*u_max;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D2(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_2L_1ML_2M_D2(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D1(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;



	if (sector_24 <= 1){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 2){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 3){
		u_zero =V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 4){
		u_zero = V_DC_Volts/2.0f + u_min * (SQRT_3-1);
	}
	else if (sector_24 == 5){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 6){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 7){
		u_zero = - u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 >= 8){
		u_zero = u_max * (SQRT_3-1) - V_DC_Volts/2.0f;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D1(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D1(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D2(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;


	if (sector_24 <= 1){
		u_zero = u_max * (SQRT_3-1) -V_DC_Volts/2.0f;
	}
	else if (sector_24 == 2){
		u_zero = - u_min -V_DC_Volts/2.0f;
	}
	else if (sector_24 == 3){
		u_zero = - u_min -V_DC_Volts/2.0f;
	}
	else if (sector_24 == 4){
		u_zero = - u_min -V_DC_Volts/2.0f;
	}
	else if (sector_24 == 5){
		u_zero = V_DC_Volts/2.0f + u_min * (SQRT_3-1);
	}
	else if (sector_24 == 6){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 7){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 >= 8){
		u_zero = V_DC_Volts/2.0f - u_max;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D2(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v1_D2(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D1(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero = -u_min - SQRT_3*u_max + V_DC_Volts/2.0f;
	}
	else if (sector_24 == 2){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 3){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 4){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 5){
		u_zero = -u_max - SQRT_3*u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 6){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 7){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 >= 8){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D1(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D1(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}

float uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D2(uz_3ph_abc_t u_abc_ref, float V_DC_Volts){

	uz_3ph_alphabeta_t u_alphabeta_ref = uz_transformation_3ph_abc_to_alphabeta(u_abc_ref);

	float theta = uz_get_angle_3ph_alphabeta_reference(u_alphabeta_ref);

	theta = fmod(theta, 2.0f*M_PI/3.0f); // symmetric to 2pi/3
	// get sector
	int sector_24 = getSector24(theta);

	float u_max = uz_getmax_3ph_abc(u_abc_ref);
	float u_min = uz_getmin_3ph_abc(u_abc_ref);

	float u_zero = 0.0f;

	if (sector_24 <= 1){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 2){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 3){
		u_zero = -V_DC_Volts/2.0f - u_min;
	}
	else if (sector_24 == 4){
		u_zero = -u_max - SQRT_3*u_min - V_DC_Volts/2.0f;
	}
	else if (sector_24 == 5){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 6){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 == 7){
		u_zero = V_DC_Volts/2.0f - u_max;
	}
	else if (sector_24 >= 8){
		u_zero = -u_min - SQRT_3*u_max + V_DC_Volts/2.0f;
	}

	return u_zero;
}

struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	// seperate both systems
	uz_3ph_abc_t u_abc_sys1 = {u_6ph_abc1abc2_ref_Volts.a1, u_6ph_abc1abc2_ref_Volts.b1, u_6ph_abc1abc2_ref_Volts.c1};
	uz_3ph_abc_t u_abc_sys2 = {u_6ph_abc1abc2_ref_Volts.a2, u_6ph_abc1abc2_ref_Volts.b2, u_6ph_abc1abc2_ref_Volts.c2};

	float u_n1 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D2(u_abc_sys1, V_DC_Volts);
	float u_n2 = uz_get_zero_sequence_one_system_DSVPWM_24_3L_1M_v2_D2(u_abc_sys2, V_DC_Volts);

	// adding zero sequence
	output = uz_add_zerosequence_and_saturate_6ph(u_6ph_abc1abc2_ref_Volts, u_n1, u_n2, V_DC_Volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_6ph_calculated_dutycycle_and_phaseshift(struct uz_DutyCycle_2x3ph_t input, int phaseshiftoption, float *shift_system_1, float *shift_system_2){
	// Phaseshiftoptions: 1: 2: 3: 4:
	struct uz_DutyCycle_2x3ph_t duty_output = {0};

	duty_output = input;

	//
	switch(phaseshiftoption){
	case 1:		// sys1 no phase shift, sys2 phase shift 180° - AAAEEE (7-56-56-7)
		*shift_system_1 = 0.0f;
		*shift_system_1 = 0.5f;
		break;
	case 2:		// sys1 phase shift 180°, sys2 phase shift 180° - EEEEEE (0-63-63-0)
		*shift_system_1 = 0.5f;
		*shift_system_2 = 0.5f;
		break;
	case 3: 	// sys1 phase shift 180°, sys2 no phase shift - EEEAAA (56-7-7-56)
		*shift_system_1 = 0.5f;
		*shift_system_2 = 0.0f;
		break;
	case 4:		// sys1 no phase shift, sys2 no phase shift - AAAAAA (63-0-0-63))
		*shift_system_1 = 0.0f;
		*shift_system_2 = 0.0f;
		break;
	default:
		break;
	}

	return duty_output;
}


/*
struct uz_DutyCycle_2x3ph_t uz_6ph_calculated_dutycycle_and_phaseshift(struct uz_DutyCycle_2x3ph_t input, int phaseshiftoption, float *shift_system_1, float *shift_system_2){
	// Phaseshiftoptions: 1: 2: 3: 4:
	struct uz_DutyCycle_2x3ph_t duty_output = {0};


	// evtl. muss das alles umgedreht werden, jenachdem wie verglichen wird!

	switch(phaseshiftoption){
	case 1:		// sys1 no phase shift, sys2 phase shift 180° - AAAEEE (7-56-56-7)
		duty_output.system1 = input.system1;
		duty_output.system2.DutyCycle_A = 1.0f-input.system2.DutyCycle_A;		// TODO: check if system1 or system2 needs to 1-x -> think it is the wrong way around see simulink
		duty_output.system2.DutyCycle_B = 1.0f-input.system2.DutyCycle_B;
		duty_output.system2.DutyCycle_C = 1.0f-input.system2.DutyCycle_C;
		*shift_system_1 = 0.0f;
		*shift_system_1 = 0.5f;
		break;
	case 2:		// sys1 phase shift 180°, sys2 phase shift 180° - EEEEEE (0-63-63-0)
		duty_output = input;
		duty_output.system1.DutyCycle_A = 1.0f-input.system1.DutyCycle_A;	// TODO: check if system1 or system2 needs to 1-x -> think it is the wrong way around see simulink
		duty_output.system1.DutyCycle_B = 1.0f-input.system1.DutyCycle_B;
		duty_output.system1.DutyCycle_C = 1.0f-input.system1.DutyCycle_C;
		duty_output.system2.DutyCycle_A = 1.0f-input.system2.DutyCycle_A;
		duty_output.system2.DutyCycle_B = 1.0f-input.system2.DutyCycle_B;
		duty_output.system2.DutyCycle_C = 1.0f-input.system2.DutyCycle_C;
		*shift_system_1 = 0.5f;
		*shift_system_2 = 0.5f;
		break;
	case 3: 	// sys1 phase shift 180°, sys2 no phase shift - EEEAAA (56-7-7-56)
		duty_output.system1.DutyCycle_A = 1.0f-input.system1.DutyCycle_A;
		duty_output.system1.DutyCycle_B = 1.0f-input.system1.DutyCycle_B;	// TODO: check if system1 or system2 needs to 1-x -> think it is the wrong way around see simulink
		duty_output.system1.DutyCycle_C = 1.0f-input.system1.DutyCycle_C;
		duty_output.system2 = input.system2;
		*shift_system_1 = 0.5f;
		*shift_system_2 = 0.0f;
		break;
	case 4:		// sys1 no phase shift, sys2 no phase shift - AAAAAA (63-0-0-63))
		duty_output.system1 = input.system1;	// TODO: check if system1 or system2 needs to 1-x -> think it is the wrong way around see simulink
		duty_output.system2 = input.system2;
		*shift_system_1 = 0.0f;
		*shift_system_2 = 0.0f;
		break;
	default:
		duty_output = input;
		break;
	}


	return duty_output;
}
*/








