#ifndef UZ_VSD6phFD_H
#define UZ_VSD6phFD_H

#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief struct for fault indices for 6ph Open-Phase-Fault-Detection
 *
 */
typedef struct uz_6phFD_indices{
    float R1;    	/**< Fault index for phase 1 */
    float R2;     	/**< Fault index for phase 2 */
    float R3;       /**< Fault index for phase 3 */
    float R4;       /**< Fault index for phase 4 */
    float R5;       /**< Fault index for phase 5 */
    float R6;       /**< Fault index for phase 6 */
}uz_6phFD_indices;

/**
 * @brief Function for 6-phase open-phase-fault detection
 * @param input uz_6ph_alphabeta_t struct as input currents of 6-phase system
 * @return uz_6phFD_indeces fault indices for the six phases
 */
uz_6phFD_indices uz_vsd_opf_6ph_faultdetection(uz_6ph_alphabeta_t input);

/**
 * @brief hysteresis filter function for the vsd open phase fault detection procedure. values
 * @param input fault indices, value is set to 0 if the value of the index is outside of the hysteresis band
 * @param upperlimit upper limit of hysteresis band
 * @param lowerlimit lower limit of hysteresis bans
 * @return uz_6phFD_indices fault indices after filtering with the hysteresis band
 *
 */
uz_6phFD_indices uz_vsd_fd_hysteresis_filter(uz_6phFD_indices input, float lowerlimit, float upperlimit);

/**
 * @brief evaluates uz_6phFD_indices values if bigger than threshold
 * @param input input fault indices
 * @param threshold value from which a fault index is judged as an error
 * @return uz_6phFD_indices fault indices set to 0 if now error or 1 if an error occured in the correspondig phase
 */
uz_6phFD_indices uz_fsd_fd_evaluation(uz_6phFD_indices input, float threshold);

#endif //UZ_VSD6phFD_H
