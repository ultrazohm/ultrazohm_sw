#include "../include/uz_testbench_limits.h"
#include "../include/uz_platform_state_machine.h"
#include <stddef.h>

const float UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP = -5.0f;
const float UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP = 5.0f;
const float UZ_TESTBENCH_LIMIT_SPEED_MIN_RPM = -1000.0f;
const float UZ_TESTBENCH_LIMIT_SPEED_MAX_RPM = 1000.0f;
const float UZ_TESTBENCH_LIMIT_DC_LINK_MIN_V = 40.0f;
const float UZ_TESTBENCH_LIMIT_DC_LINK_MAX_V = 60.0f;
const float UZ_TESTBENCH_LIMIT_TORQUE_MIN_NM = -9.0f;
const float UZ_TESTBENCH_LIMIT_TORQUE_MAX_NM = 9.0f;

volatile uint32_t uz_testbench_limits_error_reason = 0U;
float js_error_max_current_left = 0.0f;
float js_error_max_current_right = 0.0f;
float js_error_vdc_left = 0.0f;
float js_error_vdc_right = 0.0f;
float js_error_overspeed = 0.0f;
float js_error_overtorque = 0.0f;

static bool is_outside_limits(float value, float min_value, float max_value)
{
	return (value < min_value) || (value > max_value);
}

static void update_global_data_error_latches(actualValues *av, uint32_t error_mask)
{
	if (av == NULL) {
		return;
	}

	if ((error_mask & (UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A |
					   UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B |
					   UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C)) != 0U) {
		av->overcurrent_ac = 1.0f;
	}
	if ((error_mask & (UZ_TESTBENCH_ERROR_LEFT_OVERVOLTAGE_DC |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERVOLTAGE_DC)) != 0U) {
		av->overvoltage_dc = 1.0f;
	}
	if ((error_mask & (UZ_TESTBENCH_ERROR_LEFT_OVERSPEED |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED)) != 0U) {
		av->overspeed = 1.0f;
	}
	if ((error_mask & UZ_TESTBENCH_ERROR_OVERTORQUE) != 0U) {
		av->overtorque = 1.0f;
	}
}

static void update_javascope_error_latches(uint32_t error_mask)
{
	if ((error_mask & (UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A |
					   UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B |
					   UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C)) != 0U) {
		js_error_max_current_left = 1.0f;
	}
	if ((error_mask & (UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C)) != 0U) {
		js_error_max_current_right = 1.0f;
	}
	if ((error_mask & UZ_TESTBENCH_ERROR_LEFT_OVERVOLTAGE_DC) != 0U) {
		js_error_vdc_left = 1.0f;
	}
	if ((error_mask & UZ_TESTBENCH_ERROR_RIGHT_OVERVOLTAGE_DC) != 0U) {
		js_error_vdc_right = 1.0f;
	}
	if ((error_mask & (UZ_TESTBENCH_ERROR_LEFT_OVERSPEED |
					   UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED)) != 0U) {
		js_error_overspeed = 1.0f;
	}
	if ((error_mask & UZ_TESTBENCH_ERROR_OVERTORQUE) != 0U) {
		js_error_overtorque = 1.0f;
	}
}

void uz_testbench_limits_report(actualValues *av, uint32_t error_mask)
{
	if (error_mask == 0U) {
		return;
	}

	uz_testbench_limits_error_reason |= error_mask;
	update_global_data_error_latches(av, error_mask);
	update_javascope_error_latches(error_mask);
	ultrazohm_state_machine_set_error(true);
}

uint32_t uz_testbench_limits_step(actualValues *av)
{
	if (av == NULL) {
		return 0U;
	}

	uint32_t error_mask = 0U;

	if (is_outside_limits(av->i_a_left, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A;
	}
	if (is_outside_limits(av->i_b_left, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B;
	}
	if (is_outside_limits(av->i_c_left, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C;
	}
	if (is_outside_limits(av->i_a_right, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A;
	}
	if (is_outside_limits(av->i_b_right, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B;
	}
	if (is_outside_limits(av->i_c_right, UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP, UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP)) {
		error_mask |= UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C;
	}
	if (is_outside_limits(av->v_dc_left, UZ_TESTBENCH_LIMIT_DC_LINK_MIN_V, UZ_TESTBENCH_LIMIT_DC_LINK_MAX_V)) {
		error_mask |= UZ_TESTBENCH_ERROR_LEFT_OVERVOLTAGE_DC;
	}
	if (is_outside_limits(av->v_dc_right, UZ_TESTBENCH_LIMIT_DC_LINK_MIN_V, UZ_TESTBENCH_LIMIT_DC_LINK_MAX_V)) {
		error_mask |= UZ_TESTBENCH_ERROR_RIGHT_OVERVOLTAGE_DC;
	}
	if (is_outside_limits(av->n_mech_rpm_d3_1, UZ_TESTBENCH_LIMIT_SPEED_MIN_RPM, UZ_TESTBENCH_LIMIT_SPEED_MAX_RPM)) {
		error_mask |= UZ_TESTBENCH_ERROR_LEFT_OVERSPEED;
	}
	if (is_outside_limits(av->n_mech_rpm_d4_1, UZ_TESTBENCH_LIMIT_SPEED_MIN_RPM, UZ_TESTBENCH_LIMIT_SPEED_MAX_RPM)) {
		error_mask |= UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED;
	}
	if (is_outside_limits(av->torque_filt, UZ_TESTBENCH_LIMIT_TORQUE_MIN_NM, UZ_TESTBENCH_LIMIT_TORQUE_MAX_NM)) {
		error_mask |= UZ_TESTBENCH_ERROR_OVERTORQUE;
	}

	uz_testbench_limits_report(av, error_mask);
	return error_mask;
}

bool uz_testbench_limits_trip_pending(void)
{
	return uz_testbench_limits_error_reason != 0U;
}

void uz_testbench_limits_reset(actualValues *av)
{
	uz_testbench_limits_error_reason = 0U;
	js_error_max_current_left = 0.0f;
	js_error_max_current_right = 0.0f;
	js_error_vdc_left = 0.0f;
	js_error_vdc_right = 0.0f;
	js_error_overspeed = 0.0f;
	js_error_overtorque = 0.0f;

	if (av != NULL) {
		av->overcurrent_ac = 0.0f;
		av->overvoltage_dc = 0.0f;
		av->overspeed = 0.0f;
		av->overtorque = 0.0f;
	}
}
