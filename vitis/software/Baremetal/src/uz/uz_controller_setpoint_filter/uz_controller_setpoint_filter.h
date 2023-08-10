#ifndef UZ_CONTROLLER_SETPOINT_FILTER_H
#define UZ_CONTROLLER_SETPOINT_FILTER_H

#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"


/**
 * @brief Configuration struct for Setpoint Filter. Pass to init function. Accessible by the user.
 */
struct uz_dq_setpoint_filter_config {
	struct uz_IIR_Filter_config config_filter_d; /**< Filter config d-setpoint \n */
    struct uz_IIR_Filter_config config_filter_q; /**< Filter config q-setpoint \n */
};

/**
 * @brief Object definition for generating a PI-Controller
 *
 */
typedef struct uz_dq_setpoint_filter uz_dq_setpoint_filter;

/**
 * @brief Initialization of the uz_dq_setpoint_filter object
 *
 * @param config uz_dq_setpoint_filter_config struct
 * @return Pointer to uz_dq_setpoint_filter instance
 */
uz_dq_setpoint_filter* uz_uz_dq_setpoint_filter_init(struct uz_dq_setpoint_filter_config config);

/**
 * @brief Function to filter/smooth out a dq setpoint e.g. for current control
 *
 * @param self pointer to instance
 * @param setpoint raw setpoint for control algorithm
 * @return filtered dq struct
 */
uz_3ph_dq_t uz_signals_IIR_Filter_dq_setpoint(uz_dq_setpoint_filter* self, uz_3ph_dq_t setpoint);

#endif // UZ_CONTROLLER_SETPOINT_FILTER_H
