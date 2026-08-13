#ifndef IM_TESTBENCH_H
#define IM_TESTBENCH_H

#include <stdbool.h>

struct _DS_Data_;

/** Initialize and configure the induction-machine controller for the testbench. */
void IM_testbench_init(struct _DS_Data_ *data);

/** Testbench controls used by the JavaScope buttons. */
void IM_testbench_toggle_control_mode(struct _DS_Data_ *data);
void IM_testbench_toggle_kalman_filter(struct _DS_Data_ *data);
void IM_testbench_toggle_resonant_control(struct _DS_Data_ *data);
void IM_testbench_reset(struct _DS_Data_ *data);

#endif
