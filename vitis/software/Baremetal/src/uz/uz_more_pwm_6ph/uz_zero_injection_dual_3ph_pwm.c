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

#include "uz_zero_injection_dual_3ph_pwm.h"
#include "uz_zero_injection_pwm_3ph.h"
//#include "../uz_signals/uz_signals.h"
//#include "../uz_HAL.h"
//#include <math.h>



struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_4_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_PWM_THI_1_4_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_PWM_THI_1_4_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_6_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_PWM_THI_1_6_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_PWM_THI_1_6_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_SVM_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_SVM_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_SVM_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float phi_rad, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_GDPWM_abc_3ph(u_abc_sys1, phi_rad, V_dc_volts);
	output.system2 = uz_GDPWM_abc_3ph(u_abc_sys2, phi_rad, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM0_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM0_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM0_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM1_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM1_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1PHI_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM1PHI_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM1PHI_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM2_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM2_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM2_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}

struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM3_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM3_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}

struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3PHI_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM3PHI_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM3PHI_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MAX_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM_MAX_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM_MAX_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MIN_abc_6ph(uz_6ph_abc_t u_abc1abc2_ref, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};

	struct uz_3ph_abc_t u_abc_sys1 = {u_abc1abc2_ref.a1, u_abc1abc2_ref.b1, u_abc1abc2_ref.c1};
	struct uz_3ph_abc_t u_abc_sys2 = {u_abc1abc2_ref.a2, u_abc1abc2_ref.b2, u_abc1abc2_ref.c2};

	output.system1 = uz_DPWM_MIN_abc_3ph(u_abc_sys1, V_dc_volts);
	output.system2 = uz_DPWM_MIN_abc_3ph(u_abc_sys2, V_dc_volts);

	return output;
}






struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_4_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_PWM_THI_1_4_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_6_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_PWM_THI_1_6_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_SVM_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_SVM_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float phi_rad, float V_dc_volts){

	return uz_Dual_GDPWM_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), phi_rad, V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM0_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM0_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM1_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1PHI_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM1PHI_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM2_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM2_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM3_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3PHI_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM3PHI_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MAX_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM_MAX_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}


struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MIN_alphabeta_6ph(uz_6ph_alphabeta_t u_6phalphabeta_ref, float V_dc_volts){

	return uz_Dual_DPWM_MIN_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(u_6phalphabeta_ref), V_dc_volts);

}




