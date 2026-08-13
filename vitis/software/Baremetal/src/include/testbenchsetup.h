#ifndef TESTBENCHSETUP_H
#define TESTBENCHSETUP_H

/* Change this single define to select the motor used by the testbench. */
#ifndef MOTOR_CONFIG_SELECT
#define MOTOR_CONFIG_SELECT MOTOR_CONFIG_SIEMENS_1LA7073
#endif
#include "motor_config.h"
#include "../uz/uz_IM_Control/uz_im_control.h"

/** Machine and controller configuration used by the IM testbench. */
struct testbenchsetup_im_t {
    uz_IM_t machine;
    struct uz_im_control_configuration_t control;
};

/** Build the complete IM testbench setup for the configured ISR sample time. */
struct testbenchsetup_im_t testbenchsetup_create_im(float sample_time_s);

#endif
