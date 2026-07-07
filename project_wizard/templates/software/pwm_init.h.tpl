/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#pragma once

#include "../globalData.h"

{% for instance in pwm_2l_instances %}
uz_PWM_SS_2L_t* initialize_project_wizard_pwm_2l_{{ instance.index }}(void);
uz_interlockDeadtime2L_handle initialize_project_wizard_deadtime_2l_{{ instance.index }}(void);
{% endfor %}
{% if pwm_3l_enabled %}
void initialize_project_wizard_pwm_3l(DS_Data* data);
{% endif %}
void project_wizard_update_pwm_outputs(DS_Data* data);
