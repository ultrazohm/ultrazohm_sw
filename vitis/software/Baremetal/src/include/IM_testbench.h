#ifndef IM_TESTBENCH_H
#define IM_TESTBENCH_H

#include <stdbool.h>

struct _DS_Data_;

/** Initialize and configure the induction-machine controller for the testbench. */
void IM_testbench_init(struct _DS_Data_ *data);

/** Testbench controls used by the JavaScope buttons. */
void IM_testbench_toggle_control_mode(struct _DS_Data_ *data);
/** @brief Toggle the IM speed PI controller used in FOC mode. */
void IM_testbench_toggle_speed_control(struct _DS_Data_ *data);
void IM_testbench_toggle_kalman_filter(struct _DS_Data_ *data);
void IM_testbench_toggle_resonant_control(struct _DS_Data_ *data);
/**
 * @brief Reset setpoints and controller dynamics when entering idle.
 *
 * Preserves the selected IM control mode, observer, resonant-control setting,
 * VA speed-control selection and trajectory enable setting.
 */
void IM_testbench_reset_idle(struct _DS_Data_ *data);

/** @brief Full Error Reset including all mode selections and error latches. */
void IM_testbench_reset(struct _DS_Data_ *data);

#endif
