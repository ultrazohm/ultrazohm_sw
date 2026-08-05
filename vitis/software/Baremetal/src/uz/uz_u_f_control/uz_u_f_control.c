#include "../uz_global_configuration.h"
#if UZ_U_F_CONTROL_MAX_INSTANCES > 0U
#include "uz_u_f_control.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include <math.h>
#include <stdbool.h>
struct uz_u_f_control_t {bool ready; struct uz_u_f_control_config_t c; struct uz_u_f_control_data_t d; enum uz_u_f_control_safe_operating_region_violation fault;};
static uz_u_f_control_t instances[UZ_U_F_CONTROL_MAX_INSTANCES]; static unsigned count;
static void check_vdc(uz_u_f_control_t*s,float v){if(s->fault)return;if(!isfinite(v)||v<s->c.dc_link_voltage_lower_bound_V)s->fault=uz_u_f_control_dc_link_voltage_violation_lower;else if(v>s->c.dc_link_voltage_upper_bound_V)s->fault=uz_u_f_control_dc_link_voltage_violation_upper;}
uz_u_f_control_t *uz_u_f_control_init(struct uz_u_f_control_config_t c){uz_assert(count<UZ_U_F_CONTROL_MAX_INSTANCES);uz_u_f_control_t*s=&instances[count++];s->ready=true;s->c=c;s->fault=0;uz_u_f_control_reset(s);return s;}
void uz_u_f_control_reset(uz_u_f_control_t*s){uz_assert_not_NULL(s);s->d=(struct uz_u_f_control_data_t){0};}
void uz_u_f_control_set_frequency(uz_u_f_control_t*s,float f){uz_assert_not_NULL(s);s->c.frequency_setpoint_Hz=f;}
const struct uz_u_f_control_data_t *uz_u_f_control_get_data(uz_u_f_control_t*s){return &s->d;}
enum uz_u_f_control_safe_operating_region_violation uz_u_f_control_get_safe_operating_area_violation(uz_u_f_control_t*s){return s->fault;}
void uz_u_f_control_acknowledge_and_reset_error(uz_u_f_control_t*s,float v){s->fault=0;check_vdc(s,v);if(!s->fault)uz_u_f_control_reset(s);}
struct uz_DutyCycle_t uz_u_f_control_sample(uz_u_f_control_t*s,float v,float ts){check_vdc(s,v);if(s->fault)return s->c.default_duty_cycle;float target=fminf(fmaxf(s->c.frequency_setpoint_Hz,0),s->c.max_frequency_Hz),step=fmaxf(s->c.frequency_ramp_Hz_per_s,.1f)*fmaxf(ts,1e-6f),e=target-s->d.frequency_command_Hz;s->d.frequency_command_Hz+=(e>step)?step:(e< -step)?-step:e;float f=s->d.frequency_command_Hz;s->d.applied_voltage_magnitude_V=fminf(s->c.ratio_V_per_Hz*f+((f>.1f)?s->c.boost_voltage_V:0),s->c.max_voltage_V);s->d.electrical_phase_rad=fmodf(s->d.electrical_phase_rad+2*UZ_PIf*f*ts,2*UZ_PIf);float peak=fminf(s->d.applied_voltage_magnitude_V*sqrtf(2.0f/3.0f),v*(1-2*s->c.minimum_pulse_width)/sqrtf(3));uz_3ph_dq_t ref={.d=peak};struct uz_DutyCycle_t d=uz_Space_Vector_Modulation(ref,v,s->d.electrical_phase_rad);float lo=s->c.minimum_pulse_width,hi=1-lo;if(d.DutyCycle_A<lo||d.DutyCycle_B<lo||d.DutyCycle_C<lo)s->fault=uz_u_f_control_duty_cycle_violation_lower;else if(d.DutyCycle_A>hi||d.DutyCycle_B>hi||d.DutyCycle_C>hi)s->fault=uz_u_f_control_duty_cycle_violation_upper;return s->fault?s->c.default_duty_cycle:d;}
#endif
