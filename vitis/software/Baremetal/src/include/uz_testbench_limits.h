#pragma once

#include "../globalData.h"
#include <stdbool.h>
#include <stdint.h>

#define UZ_TESTBENCH_ERROR_OVERVOLTAGE_DC        (1U << 0)
#define UZ_TESTBENCH_ERROR_UNDERVOLTAGE_DC       (1U << 1)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A    (1U << 2)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B    (1U << 3)
#define UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C    (1U << 4)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A   (1U << 5)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B   (1U << 6)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C   (1U << 7)
#define UZ_TESTBENCH_ERROR_LEFT_OVERSPEED        (1U << 8)
#define UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED       (1U << 9)
#define UZ_TESTBENCH_ERROR_OVERTORQUE            (1U << 10)

/*
 * Error code bitmask explanation:
 * 0x0001 / 1    UZ_TESTBENCH_ERROR_OVERVOLTAGE_DC
 * 0x0002 / 2    UZ_TESTBENCH_ERROR_UNDERVOLTAGE_DC
 * 0x0004 / 4    UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_A
 * 0x0008 / 8    UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_B
 * 0x0010 / 16   UZ_TESTBENCH_ERROR_LEFT_OVERCURRENT_C
 * 0x0020 / 32   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_A
 * 0x0040 / 64   UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_B
 * 0x0080 / 128  UZ_TESTBENCH_ERROR_RIGHT_OVERCURRENT_C
 * 0x0100 / 256  UZ_TESTBENCH_ERROR_LEFT_OVERSPEED
 * 0x0200 / 512  UZ_TESTBENCH_ERROR_RIGHT_OVERSPEED
 * 0x0400 / 1024 UZ_TESTBENCH_ERROR_OVERTORQUE
 *
 * Multiple active errors are OR-combined. Example: 0x0005 / 5 means
 * overvoltage DC and left phase A overcurrent.
 */

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
extern float js_error_overvoltage_dc;
extern float js_error_undervoltage_dc;
extern float js_error_overspeed;
extern float js_error_overtorque;

uint32_t uz_testbench_limits_step(actualValues *av);
void uz_testbench_limits_report(actualValues *av, uint32_t error_mask);
bool uz_testbench_limits_trip_pending(void);
void uz_testbench_limits_reset(actualValues *av);
