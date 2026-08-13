#include "../include/error_checks.h"
#include "../include/uz_platform_state_machine.h"
#include "../uz/uz_HAL.h"
#include <math.h>

volatile uint32_t error_reason = 0U;
float js_error_code = 0.0f;

static void error_checks_report(uint32_t error_mask)
{
	if (error_mask == 0U) {
		return;
	}

	error_reason |= error_mask;
	js_error_code = (float)error_reason;
	ultrazohm_state_machine_set_error(true);
}

bool error_checks_trip_pending(void)
{
	return error_reason != 0U;
}

uint32_t error_checks_step_im(float vdc,float ia,float ib,float ic,float speed,
	const error_checks_config_t *c,bool monitor_uv)
{
	uint32_t m=0U;
	if(!isfinite(vdc)||!isfinite(ia)||!isfinite(ib)||!isfinite(ic)||!isfinite(speed))m|=ERR_IM_NAN_MEASUREMENT;
	if(monitor_uv&&vdc<c->vdc_min_V)m|=ERR_IM_UNDERVOLTAGE_DC;
	if(vdc>c->vdc_max_V)m|=ERR_IM_OVERVOLTAGE_DC;
	if(fabsf(ia)>c->iphase_max_A)m|=ERR_IM_OVERCURRENT_U;
	if(fabsf(ib)>c->iphase_max_A)m|=ERR_IM_OVERCURRENT_V;
	if(fabsf(ic)>c->iphase_max_A)m|=ERR_IM_OVERCURRENT_W;
	if(fabsf(speed)>c->max_mechanical_speed_rpm)m|=ERR_IM_OVERSPEED;
	error_checks_report(m); return m;
}

void error_checks_reset(void)
{
	error_reason = 0U;
	js_error_code = 0.0f;
}
