#pragma once

#include "../globalData.h"
#include <stdbool.h>
#include <stdint.h>

#define UZ_TESTBENCH_ERROR_LEFT_OVERVOLTAGE_DC   (1U << 0)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERVOLTAGE_DC  (1U << 1)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A    (1U << 2)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B    (1U << 3)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C    (1U << 4)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A   (1U << 5)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B   (1U << 6)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C   (1U << 7)
#define UZ_TESTBENCH_ERROR_LEFT_OVERSPEED        (1U << 8)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED       (1U << 9)
#define UZ_TESTBENCH_ERROR_OVERTORQUE            (1U << 10)

extern const float UZ_TESTBENCH_LIMIT_CURRENT_MIN_AMP;
extern const float UZ_TESTBENCH_LIMIT_CURRENT_MAX_AMP;
extern const float UZ_TESTBENCH_LIMIT_SPEED_MIN_RPM;
extern const float UZ_TESTBENCH_LIMIT_SPEED_MAX_RPM;
extern const float UZ_TESTBENCH_LIMIT_DC_LINK_MIN_V;
extern const float UZ_TESTBENCH_LIMIT_DC_LINK_MAX_V;
extern const float UZ_TESTBENCH_LIMIT_TORQUE_MIN_NM;
extern const float UZ_TESTBENCH_LIMIT_TORQUE_MAX_NM;

extern volatile uint32_t uz_testbench_limits_error_reason;
extern float js_error_max_current_left;
extern float js_error_max_current_right;
extern float js_error_vdc_left;
extern float js_error_vdc_right;
extern float js_error_overspeed;
extern float js_error_overtorque;

uint32_t uz_testbench_limits_step(actualValues *av);
void uz_testbench_limits_report(actualValues *av, uint32_t error_mask);
bool uz_testbench_limits_trip_pending(void);
void uz_testbench_limits_reset(actualValues *av);
