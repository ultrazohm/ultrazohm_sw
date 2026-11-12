#pragma once
#include "../globalData.h"
#include "uz_platform_state_machine.h"

/* Call after adapter readout and before project_wizard_update_pwm_outputs().
 * Mode requests are accepted only in idle_state. In deskbench control_state,
 * DUT current control uses A1 + D5_1 and drives D1 (half bridges 1..3).
 * Prime-mover speed control uses A2 + D4_1 SSI and drives D2 (half bridges 4..6).
 * The SSI mechanical angle feeds the controller's angle feedback and the existing speed PLL.
 * Inputs ready indicates assigned feedback; controller protection checks limits.
 * JavaScope MyButton1 selects CIL; MyButton2 selects real DUT, only in idle.
 * MyButton5 selects prime-mover duty mode (backend 2), only in idle.
 * Send field 4 stores duty [0..1]; MyButtons6/7/8 apply it to phase A/B/C
 * in control_state, with the other phases at 0.5. A fresh press is required.
 * Both closed-loop controllers and the DUT inverter stay disabled in duty mode.
 * Prime-mover current/voltage/speed protection remains active.
 * STOP, trip or mode change clears phase selection but retains the pending duty.
 * ACT indicators show the mode and the phase actually applied.
 * Receive fields 1..4: DUT speed, id, iq and estimated electromagnetic torque.
 * Receive fields 7/8: active backend / inputs ready.
 * STOP disables both inverters and clears references; physical shaft speed
 * is not reset. A controlled mechanical stop requires a later application policy.
 */
void deskbench_step(DS_Data* data, platform_state_t state);
bool deskbench_set_prime_mover_duty_cycle(DS_Data* data, float duty);
bool deskbench_apply_prime_mover_duty_cycle(DS_Data* data, platform_state_t state,
    enum prime_mover_duty_phase phase);
void deskbench_cancel_prime_mover_duty_cycle(DS_Data* data);

