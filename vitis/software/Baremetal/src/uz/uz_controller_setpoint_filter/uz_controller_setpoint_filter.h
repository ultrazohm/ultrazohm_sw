#ifndef UZ_CONTROLLER_SETPOINT_FILTER_H
#define UZ_CONTROLLER_SETPOINT_FILTER_H

#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"


/**
 * @brief Function to filter/smooth out a dq setpoint e.g. for current control
 *
 * @param filter_1 pointer instance of uz_IIR_Filter_t
 * @param filter_2 pointer instance of uz_IIR_Filter_t
 * @param setpoint raw setpoint for control algorithm
 * @return filtered dq struct
 */
uz_3ph_dq_t uz_signals_IIR_Filter_dq_setpoint(uz_IIR_Filter_t* filter_1, uz_IIR_Filter_t* filter_2, uz_3ph_dq_t setpoint);

#endif // UZ_CONTROLLER_SETPOINT_FILTER_H
