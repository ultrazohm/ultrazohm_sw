#pragma once
#include <stdbool.h>

void ultrazohm_state_machine(void);

void ultrazohm_state_machine_set_enable_system(bool enable_system);
void ultrazohm_state_machine_set_enable_control(bool enable_control);
void ultrazohm_state_machine_set_stop(bool stop);
void ultrazohm_state_machine_set_error(bool error);
bool ultrazohm_state_machine_is_control_state(void);