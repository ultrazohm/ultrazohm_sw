#ifndef UZ_VSD_9PH_ML_MT_CONTROL_H
#define UZ_VSD_9PH_ML_MT_CONTROL_H

#include "uz_VSD_9ph_FD.h"
#include "../uz_VSD_6ph_FD_control/uz_VSD_6ph_ML_MT_Control.h"
#include <stdbool.h>



/**
 * @brief Struct for k-parameter for calculating controller reference values in 9ph VSD-control during open phase faults
 *
 */
typedef struct{
    float k_X1a;        /**< setpoint x1: factor for alpha */
    float k_X1b;        /**< setpoint x1: factor for beta */
    float k_Y1a;        /**< setpoint y1: factor for alpha */  
    float k_Y1b;        /**< setpoint y1: factor for beta */
    float k_X2a;        /**< setpoint x2: factor for alpha */
    float k_X2b;        /**< setpoint x2: factor for beta */
    float k_Y2a;        /**< setpoint y2: factor for alpha */
    float k_Y2b;        /**< setpoint y2: factor for beta */ 
    float k_X3a;        /**< setpoint x3: factor for alpha */  
    float k_X3b;        /**< setpoint x3: factor for beta */ 
    float k_Y3a;        /**< setpoint y3: factor for alpha */  
    float k_Y3b;        /**< setpoint y3: factor for beta */ 
    float derating;     /**< derating factor */ 
    bool valid;         /**< valid flag (true: parameter set for the fault is found, false: no parameter set is found, e.g. because of non optimized combination) */ 
}uz_9ph_MLMT_kparameter_t;


/**
 * @brief returns the k-parameters for a specified fault-scenario, neutral configuration and optimizations strategy
 * @param input_faultindices fault indices for all nine phases
 * @param optimization optimization strategiy (ML or MT)
 * @param neutral neutral configuration (1 or 3)
 * @return uz_9ph_MLMT_kparameter_t struct with kparameters and derating factor
 */
uz_9ph_MLMT_kparameter_t uz_get_k_parameter_9ph(uz_9ph_abc_t input_faultindices, ML_MT_optimization optimization, int neutral);

/**
 * @brief returns the the combined OPF index, meaning the indices of all phases are combined as integer (order: a1=bit0, b1=bit1, c1=bit2, a2=bit3, ..., c3=bit8)
 * @param input_faultindices fault indices for all nine phases
 * @return combined binary coded fault index
 */
int fault_indices_to_OPF_index(uz_9ph_abc_t input_faultindices);

#endif // UZ_VSD_9ph_ML_MT_CONTROL_H

