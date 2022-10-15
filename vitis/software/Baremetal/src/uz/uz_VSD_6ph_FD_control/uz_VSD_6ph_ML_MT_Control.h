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
struct kparameter{
    float k1;   /**< k1 parameter, for calculating i_x_ref = k1 * i_alpha_ref + k2 * i_beta_ref*/
    float k2;   /**< k2 parameter, for calculating i_x_ref = k1 * i_alpha_ref + k2 * i_beta_ref*/
    float k3;   /**< k3 parameter, for calculating i_y_ref = k3 * i_alpha_ref + k4 * i_beta_ref*/
    float k4;   /**< k4 parameter, for calculating i_y_ref = k3 * i_alpha_ref + k4 * i_beta_ref*/
    float k5;   /**< k5 parameter, for calculating i_z1_ref = k5 * i_alpha_ref + k6 * i_beta_ref*/
    float k6;   /**< k6 parameter, for calculating i_z1_ref = k5 * i_alpha_ref + k6 * i_beta_ref*/
    float k7;   /**< k7 parameter, for calculating i_z2_ref = k7 * i_alpha_ref + k8 * i_beta_ref*/
    float k8;   /**< k8 parameter, for calculating i_z2_ref = k7 * i_alpha_ref + k8 * i_beta_ref*/
    float a;    /**< derating factor*/
};

/**
 * @brief typedef for k parameter struct
 *
 */
typedef struct kparameter kparameter;


/**
 * @brief returns the k-parameters for a specified fault-scenario, neutral point configuration and optimization strategy
 * @param FD_indices uz_6phFD_indices fault indices of the 6 phases
 * @param N1N2 neutral-point configuration (N1 = 1 -> single neutral point, N2 = 2 -> two separate neutral points for phases a1b1c1 and a2b2c2)
 * @param ML optimization strategy (ML = 0 -> Maximum Torque (MT) optimization, ML = 1 -> Minimum Loss (MT) optimization)
 * @return kparameter struct with kparameters and derating factor
 */
kparameter get_k_parameter(uz_6phFD_indices FD_indices, int N1N2, int ML);




#endif // UZ_VSD_6PH_ML_MT_CONTROL_H

