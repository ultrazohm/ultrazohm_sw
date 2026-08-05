#ifndef ERROR_CHECKS_H_
#define ERROR_CHECKS_H_

#include "../globalData.h"
#include <stdbool.h>
#include <stdint.h>

/* VA error-reason bitmask, modelled after the local VA test-bench. */
#define ERR_VA_UNDERVOLTAGE_DC  (1U << 0)
#define ERR_VA_OVERVOLTAGE_DC   (1U << 1)
#define ERR_VA_OVERCURRENT_U    (1U << 2)
#define ERR_VA_OVERCURRENT_V    (1U << 3)
#define ERR_VA_OVERCURRENT_W    (1U << 4)
#define ERR_VA_OVERSPEED        (1U << 5)
#define ERR_VA_NAN_MEASUREMENT  (1U << 6)
#define ERR_IM_UNDERVOLTAGE_DC  (1U << 7)
#define ERR_IM_OVERVOLTAGE_DC   (1U << 8)
#define ERR_IM_OVERCURRENT_U    (1U << 9)
#define ERR_IM_OVERCURRENT_V    (1U << 10)
#define ERR_IM_OVERCURRENT_W    (1U << 11)
#define ERR_IM_OVERSPEED        (1U << 12)
#define ERR_IM_NAN_MEASUREMENT  (1U << 13)

typedef struct {
	float vdc_min_V;
	float vdc_max_V;
	float iphase_max_A;
	float max_mechanical_speed_rpm;
} error_checks_config_t;

extern volatile uint32_t error_reason;
extern float js_error_code;
extern float js_error_vdc_va;
extern float js_error_max_current_va;
extern float js_error_overspeed_va;
extern float js_error_nan_measurement;

uint32_t error_checks_step(const actualValues *av, const error_checks_config_t *config,
	bool monitor_dc_undervoltage);
bool error_checks_trip_pending(void);
void error_checks_reset(void);
uint32_t error_checks_step_im(float vdc,float ia,float ib,float ic,float speed_rpm,
	const error_checks_config_t *config,bool monitor_dc_undervoltage);

#endif /* ERROR_CHECKS_H_ */
