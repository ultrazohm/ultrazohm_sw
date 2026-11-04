#pragma once
#include "../globalData.h"
#include "uz_platform_state_machine.h"

/* Call after adapter readout and before project_wizard_update_pwm_outputs().
 * Mode requests are accepted only in idle_state. In deskbench control_state,
 * DUT current control uses A1 + D5_1 and drives D1 (half bridges 1..3).
 * Prime-mover speed control uses A2 + D5_2 and drives D2 (half bridges 4..6).
 * Inputs ready indicates assigned feedback; controller protection checks limits.
 * JavaScope MyButton1 selects CIL; MyButton2 selects real DUT, only in idle.
 * ACT indicators show the active backend. Send field 4 is unassigned.
 * Receive fields 1..4: DUT speed, id, iq and estimated electromagnetic torque.
 * Receive fields 7/8: active backend / inputs ready.
 * STOP disables both inverters and clears references; physical shaft speed
 * is not reset. A controlled mechanical stop requires a later application policy.
 */
void deskbench_step(DS_Data* data, platform_state_t state);

