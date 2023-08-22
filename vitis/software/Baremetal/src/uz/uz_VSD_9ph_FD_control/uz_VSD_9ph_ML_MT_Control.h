#ifndef UZ_VSD_9PH_ML_MT_CONTROL_H
#define UZ_VSD_9PH_ML_MT_CONTROL_H

#include "uz_VSD_9ph_FD.h"

/*
header-file for the parameter of ML- and MT-Control strategy for
open phase faults in asymmetric dual three-phase machines
*/

/**
 * @brief Struct for k-parameter for calculating controller reference values in 9ph VSD-control during open phase faults
 *
 */
struct uz_9ph_MLMT_kparameter{
    float k_X1a;  
    float k_X1b;
    float k_Y1a;  
    float k_Y1b; 
    float k_X2a;  
    float k_X2b; 
    float k_Y2a;  
    float k_Y2b; 
    float k_X3a;  
    float k_X3b; 
    float k_Y3a;  
    float k_Y3b; 
    float derating;
};

/**
 * @brief typedef for k parameter struct
 *
 */
typedef struct uz_9ph_MLMT_kparameter uz_9ph_MLMT_kparameter;


/**
 * @brief returns the k-parameters for a specified fault-scenario, neutral point configuration and optimization strategy
 * @param FD_indices uz_9phFD_indices fault indices of the 6 phases
 * @param neutral_point_configuration enum neutral-point configuration (N1 -> single neutral point, N2-> two separate neutral points for phases a1b1c1 and a2b2c2)
 * @param ML_MT_optimization enum (MT -> Maximum Torque (MT) optimization, ML -> Minimum Loss (MT) optimization)
 * @return uz_9ph_MLMT_kparameter struct with kparameters and derating factor
 */
//uz_9ph_MLMT_kparameter uz_get_k_parameter(uz_9phFD_indices FD_indices, neutral_point_configuration neutral_point_configuration, ML_MT_optimization ML_MT_optimization);

uz_9ph_MLMT_kparameter uz_get_k_parameter_9ph_ML(uz_9ph_abc_t input_faultindices);



#endif // UZ_VSD_9ph_ML_MT_CONTROL_H

