#include "../include/error_checks.h"
#include "../include/uz_platform_state_machine.h"
#include "../uz/uz_HAL.h"
#include <math.h>

volatile uint32_t error_reason = 0U;
float js_error_code = 0.0f;
float js_error_vdc_va = 0.0f;
float js_error_max_current_va = 0.0f;
float js_error_overspeed_va = 0.0f;
float js_error_nan_measurement = 0.0f;

static void error_checks_report(uint32_t error_mask)
{
	if (error_mask == 0U) {
		return;
	}

	error_reason |= error_mask;
	js_error_code = (float)error_reason;
	if ((error_mask & (ERR_VA_UNDERVOLTAGE_DC | ERR_VA_OVERVOLTAGE_DC)) != 0U) {
		js_error_vdc_va = 1.0f;
	}
	if ((error_mask & (ERR_VA_OVERCURRENT_U | ERR_VA_OVERCURRENT_V | ERR_VA_OVERCURRENT_W)) != 0U) {
		js_error_max_current_va = 1.0f;
	}
	if ((error_mask & ERR_VA_OVERSPEED) != 0U) {
		js_error_overspeed_va = 1.0f;
	}
	if ((error_mask & ERR_VA_NAN_MEASUREMENT) != 0U) {
		js_error_nan_measurement = 1.0f;
	}
	ultrazohm_state_machine_set_error(true);
}

uint32_t error_checks_step(const actualValues *av, const error_checks_config_t *config,
	bool monitor_dc_undervoltage)
{
	uz_assert_not_NULL(av);
	uz_assert_not_NULL(config);

	float const vdc = av->adc_ltc2311_a2_ch0;
	float const ia = av->adc_ltc2311_a2_ch3;
	float const ib = av->adc_ltc2311_a2_ch2;
	float const ic = av->adc_ltc2311_a2_ch1;
	float const speed_rpm = av->va_control_actual.speed_in_rpm;
	uint32_t error_mask = 0U;

	if (!isfinite(vdc) || !isfinite(ia) || !isfinite(ib) ||
		!isfinite(ic) || !isfinite(speed_rpm)) {
		error_mask |= ERR_VA_NAN_MEASUREMENT;
	}
	if (monitor_dc_undervoltage && (vdc < config->vdc_min_V)) {
		error_mask |= ERR_VA_UNDERVOLTAGE_DC;
	}
	if (vdc > config->vdc_max_V) {
		error_mask |= ERR_VA_OVERVOLTAGE_DC;
	}
	if (fabsf(ia) > config->iphase_max_A) {
		error_mask |= ERR_VA_OVERCURRENT_U;
	}
	if (fabsf(ib) > config->iphase_max_A) {
		error_mask |= ERR_VA_OVERCURRENT_V;
	}
	if (fabsf(ic) > config->iphase_max_A) {
		error_mask |= ERR_VA_OVERCURRENT_W;
	}
	if (fabsf(speed_rpm) > config->max_mechanical_speed_rpm) {
		error_mask |= ERR_VA_OVERSPEED;
	}

	error_checks_report(error_mask);
	return error_mask;
}

bool error_checks_trip_pending(void)
{
	return error_reason != 0U;
}

void error_checks_reset(void)
{
	error_reason = 0U;
	js_error_code = 0.0f;
	js_error_vdc_va = 0.0f;
	js_error_max_current_va = 0.0f;
	js_error_overspeed_va = 0.0f;
	js_error_nan_measurement = 0.0f;
}
