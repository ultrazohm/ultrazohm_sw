#include "uz_FOC.h"
#include "../uz_global_configuration.h"
#include "../uz_PI_Controller/uz_PI_controller.h"

static size_t instances_counter_FOC_ActualValues = 0;
static size_t instances_counter_FOC_VoltageReference = 0;

static uz_FOC_ActualValues instances_FOC_ActualValues[UZ_FOC_ACTUALVALUES_MAX_INSTANCES] = { 0 };
static uz_FOC_VoltageReference instances_FOC_VoltageReference[UZ_FOC_VOLTAGEREFERENCE_MAX_INSTANCES] = { 0 };

/**
 * @brief Memory allocation of the ActualValues struct
 *
 * @return Pointer to ActualValues instance
 */
static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void);

static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void) {
	uz_assert(instances_counter_FOC_ActualValues < UZ_FOC_ACTUALVALUES_MAX_INSTANCES);
	uz_FOC_ActualValues* self = &instances_FOC_ActualValues[instances_counter_FOC_ActualValues];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_ActualValues++;
	self->is_ready = true;
	return (self);
}

/**
 * @brief Memory allocation of the uz_FOC_PI_Controller_output struct
 *
 * @return Pointer to uz_FOC_PI_Controller_output instance
 */
static uz_FOC_VoltageReference* uz_FOC_VoltageReference_allocation(void);

static uz_FOC_VoltageReference* uz_FOC_VoltageReference_allocation(void) {
	uz_assert(instances_counter_FOC_VoltageReference < UZ_FOC_VOLTAGEREFERENCE_MAX_INSTANCES);
	uz_FOC_VoltageReference* self = &instances_FOC_VoltageReference[instances_counter_FOC_VoltageReference];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_VoltageReference++;
	self->is_ready = true;
	return (self);
}

uz_FOC_ActualValues* uz_FOC_ActualValues_init(void) {
	uz_FOC_ActualValues* self = uz_FOC_ActualValues_allocation();
	return (self);
}

uz_FOC_VoltageReference* uz_FOC_VoltageReference_init(void) {
	uz_FOC_VoltageReference* self = uz_FOC_VoltageReference_allocation();
	return (self);
}

int uz_FOC_get_sign_of_value(float input) {
	int sign;
	if (input < 0)
		sign = -1;
	else if (input > 0) {
		sign = 1;
	} else {
		sign = 0;
	}
	return (sign);
}


void uz_FOC_linear_decouppling(uz_FOC_ActualValues* values, uz_FOC_config config, float* u_d_vor, float* u_q_vor){
	uz_assert_not_NULL(values);
	uz_assert_not_NULL(u_q_vor);
	uz_assert_not_NULL(u_d_vor);
	uz_assert(config.L_q>0.0f);
	uz_assert(config.L_d>0.0f);
	uz_assert(config.psi_pm>=0.0f);
	*u_d_vor = values->i_q_Ampere * -1.0f * config.L_q * values->omega_el_rad_per_sec;
	*u_q_vor = (values->i_d_Ampere * config.L_d + config.psi_pm) * values->omega_el_rad_per_sec;
}

bool uz_FOC_SpaceVector_Limitation(uz_FOC_VoltageReference* reference, uz_FOC_ActualValues* values){
	uz_assert_not_NULL(reference);
	uz_assert_not_NULL(values);
	uz_assert(values->U_zk_Volts > 0.0f);
	bool limit_on = false;
	float U_d_limit=0.0f;
	float U_q_limit=0.0f;

   	float U_RZ_max =values->U_zk_Volts / sqrtf(3.0f);
	float U_RZ_betrag = sqrtf(reference->u_d_ref_Volts * reference->u_d_ref_Volts + reference->u_q_ref_Volts * reference->u_q_ref_Volts);

	if ( U_RZ_betrag > U_RZ_max ){
		limit_on = true;
		if ((uz_FOC_get_sign_of_value(values->omega_el_rad_per_sec) == uz_FOC_get_sign_of_value(values->i_q_Ampere))) {
			if ((abs(reference->u_d_ref_Volts) > 0.95f * U_RZ_max)) {
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * 0.95f * U_RZ_max;
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_d_limit * U_d_limit);
			} else {
				U_d_limit = reference->u_d_ref_Volts;
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_d_limit * U_d_limit);
			}


	       } else if ((uz_FOC_get_sign_of_value(values->omega_el_rad_per_sec) != uz_FOC_get_sign_of_value(values->i_q_Ampere))) {
			if (abs(reference->u_q_ref_Volts) > 0.95f * U_RZ_max) {
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * 0.95f * U_RZ_max;
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_q_limit * U_q_limit);
			} else {
				U_q_limit = reference->u_q_ref_Volts;
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_q_limit * U_q_limit);
			}
		} else {
			U_d_limit = reference->u_d_ref_Volts;
			U_q_limit = reference->u_q_ref_Volts;
		}

	} else {
		U_d_limit = reference->u_d_ref_Volts;
		U_q_limit = reference->u_q_ref_Volts;
		limit_on = false;
	}

reference->u_d_ref_Volts = U_d_limit;
reference->u_q_ref_Volts = U_q_limit;
	return (limit_on);
}
