#ifndef UZ_FOC_H
#define UZ_FOC_H

#endif // UZ_FOC_H

#include "../uz_HAL.h"
#include <math.h>
#include <stdbool.h>

typedef struct uz_FOC_config {
	float Kp_id;
	float Kp_iq;
	float Kp_n;
	float Ki_id;
	float Ki_iq;
	float Ki_n;
	float iq_ref_Ampere;
	float id_ref_Ampere;
	float n_ref_rpm;
	bool FOC_Select;
	bool ResetIntegrators;
} uz_FOC_config;

typedef struct uz_FOC_ActualValues {
	bool is_ready;
	float i_d_Ampere;
	float i_q_Ampere;
	float u_d_Volts;
	float u_q_Volts;
	float i_a_Ampere;
	float i_b_Ampere;
	float i_c_Ampere;
	float omega_el_rad_per_sec;
	float theta_el_rad;
	float U_zk_Volts;
	float u_a_Volts;
	float u_b_Volts;
	float u_c_Volts;
} uz_FOC_ActualValues;

typedef struct uz_FOC_PI_Controller_output {
	bool is_ready;
	float u_d_ref_Volts;
	float u_q_ref__Volts;
	float integrator_value;
} uz_FOC_PI_Controller_output;

static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void);
static uz_FOC_PI_Controller_output* uz_FOC_PI_Controller_output_allocation(void);
uz_FOC_ActualValues* uz_FOC_ActualValues_init(void);
uz_FOC_PI_Controller_output* uz_FOC_PI_Controller_output_init(void);
