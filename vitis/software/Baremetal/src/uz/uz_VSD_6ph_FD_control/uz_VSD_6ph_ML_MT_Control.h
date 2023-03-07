#ifndef UZ_VSD_6PH_ML_MT_CONTROL_H
#define UZ_VSD_6PH_ML_MT_CONTROL_H

#include "uz_VSD_6ph_FD.h"

/*
header-file for the parameter of ML- and MT-Control strategy for
open phase faults in asymmetric dual three-phase machines
*/

/**
 * @brief Struct for k-parameter for calculating controller reference values in 6ph VSD-control during open phase faults
 *
 */
struct uz_6ph_MLMT_kparameter{
    float k1;   /**< k1 parameter, for calculating i_x_ref = k1 * i_alpha_ref + k2 * i_beta_ref*/
    float k2;   /**< k2 parameter, for calculating i_x_ref = k1 * i_alpha_ref + k2 * i_beta_ref*/
    float k3;   /**< k3 parameter, for calculating i_y_ref = k3 * i_alpha_ref + k4 * i_beta_ref*/
    float k4;   /**< k4 parameter, for calculating i_y_ref = k3 * i_alpha_ref + k4 * i_beta_ref*/
    float k5;   /**< k5 parameter, for calculating i_z1_ref = k5 * i_alpha_ref + k6 * i_beta_ref*/
    float k6;   /**< k6 parameter, for calculating i_z1_ref = k5 * i_alpha_ref + k6 * i_beta_ref*/
    float k7;   /**< k7 parameter, for calculating i_z2_ref = k7 * i_alpha_ref + k8 * i_beta_ref*/
    float k8;   /**< k8 parameter, for calculating i_z2_ref = k7 * i_alpha_ref + k8 * i_beta_ref*/
    float deratingFaktor;    /**< derating factor*/
};

/**
 * @brief Enum for the neutral point connection
 * 
 */
typedef enum {
    N1 = 1,     /**< single neutral point*/
    N2 = 2,     /**< two separated neutral points*/
}neutral_point_configuration;

/**
 * @brief Enum for the optimization strategies
 * 
 */
typedef enum {
    MT = 0,     /**< Minimum Loss optimization*/
    ML = 1,     /**< Maximum Torque optimization*/
}ML_MT_optimization;

/**
 * @brief typedef for k parameter struct
 *
 */
typedef struct uz_6ph_MLMT_kparameter uz_6ph_MLMT_kparameter;


/**
 * @brief returns the k-parameters for a specified fault-scenario, neutral point configuration and optimization strategy
 * @param FD_indices uz_6phFD_indices fault indices of the 6 phases
 * @param neutral_point_configuration enum neutral-point configuration (N1 -> single neutral point, N2-> two separate neutral points for phases a1b1c1 and a2b2c2)
 * @param ML_MT_optimization enum (MT -> Maximum Torque (MT) optimization, ML -> Minimum Loss (MT) optimization)
 * @return uz_6ph_MLMT_kparameter struct with kparameters and derating factor
 */
uz_6ph_MLMT_kparameter get_k_parameter(uz_6phFD_indices FD_indices, neutral_point_configuration neutral_point_configuration, ML_MT_optimization ML_MT_optimization);




#endif // UZ_VSD_6PH_ML_MT_CONTROL_H

