#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef struct uz_interlockDeadtime2L uz_interlockDeadtime2L;
typedef struct uz_interlockDeadtime2L *uz_interlockDeadtime2L_handle;

uz_interlockDeadtime2L_handle uz_interlockDeadtime2L_init(uz_interlockDeadtime2L_handle self);
void uz_interlockDeadtime2L_set_enable_output(uz_interlockDeadtime2L_handle self, bool enable_output);
bool uz_interlockDeadtime2L_get_enable_output(uz_interlockDeadtime2L_handle self);
void uz_interlockDeadtime2L_set_deadtime_us(uz_interlockDeadtime2L_handle self, float deadtime_in_microseconds);
float uz_interlockDeadtime2L_get_deadtime_us(uz_interlockDeadtime2L_handle self);
