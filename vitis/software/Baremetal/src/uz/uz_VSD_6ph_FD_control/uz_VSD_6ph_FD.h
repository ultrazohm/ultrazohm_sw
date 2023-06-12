#ifndef UZ_VSD_6PH_FD_H
#define UZ_VSD_6PH_FD_H


#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_movingAverageFilter/uz_movingAverageFilter.h"

/**
 * @brief Struct for fault indices for the six phase Open-Phase-Fault-Detection
 */
typedef struct uz_6phFD_indices{
    float R1;    	/**< Fault index for phase 1 (a1) */
    float R2;     	/**< Fault index for phase 2 (b1)*/
    float R3;       /**< Fault index for phase 3 (c1)*/
    float R4;       /**< Fault index for phase 4 (a2)*/
    float R5;       /**< Fault index for phase 5 (b2)*/
    float R6;       /**< Fault index for phase 6 (c2)*/
}uz_6phFD_indices;


/**
 * @brief Struct definition for uz_VSD_6ph_FD_t
 *
 */
typedef struct uz_VSD_6ph_FD_t uz_VSD_6ph_FD_t;

/**
 * @brief Configuration struct for six phase VSD fault detection. Pass to init function. Accessible by the user.
 */
struct uz_VSD_6ph_FD_config
{
    float upperlimit;                   /**< upper limit of hysteresis band, recommended values: 1.1 (1 ... 1.5) */
    float lowerlimit;                   /**< lowerlimit lower limit of hysteresis band, recommended values: 0.9 (0.6 ... 1) */
    float threshold;                    /**< threshold value above which a fault index is judged as an error, recommended values: 0.4 (0.2 ... 0.7) */
    uint32_t mov_average_filter_length;    /**< maximal length of moving average filter, needs to be sufficiently long for all sampling values according to the operating motor speeds and the parameter percent_of_el_period*/
    float sample_frequency_Hz;             /**< sample frequency in Hz, frequency with which the OPF detection is called during operation */
    float percent_of_el_period;         /**< desired filter length as portion of an electric period, recommended values: 0.4 (0.3 ... 0.7) */
    uz_movingAverageFilter_t* movingAverageFilter_R1; /**< moving average filter for fault index R1*/
    uz_movingAverageFilter_t* movingAverageFilter_R2; /**< moving average filter for fault index R2*/
    uz_movingAverageFilter_t* movingAverageFilter_R3; /**< moving average filter for fault index R3*/
    uz_movingAverageFilter_t* movingAverageFilter_R4; /**< moving average filter for fault index R4*/
    uz_movingAverageFilter_t* movingAverageFilter_R5; /**< moving average filter for fault index R5*/
    uz_movingAverageFilter_t* movingAverageFilter_R6; /**< moving average filter for fault index R6*/
};

/**
 * @brief Init function for the six phase OPF detection
 * @param uz_VSD_6ph_FD_t* pointer to OPF fault detection struct
 * @param struct uz_VSD_6ph_FD_config, config for the fault detection
 * @return uz_VSD_6ph_FD_t*, pointer to the fault detection
*/
uz_VSD_6ph_FD_t *uz_VSD_6ph_FD_init(struct uz_VSD_6ph_FD_config config);



/**
 * @brief Function for six-phase open-phase-fault detection, has to be cyclicly called with a the frequency configured in sample_frequency_Hz
 * @param uz_VSD_6ph_FD_t* pointer to OPF fault detection struct
 * @param vsdcurrents VSD currents
 * @param omega_el_rad_per_sec omega_el in rad per seconds
 * @return uz_6phFD_indices fault indices for the six phases filtered and evaluated 
 */
uz_6phFD_indices uz_vsd_opf_6ph_faultdetection_step(uz_VSD_6ph_FD_t* VSD_FD, uz_6ph_alphabeta_t vsdcurrents, float omega_el_rad_per_sec);

/**
 * @brief Function to calculate the fault indices (unfiltered) for 6-phase open-phase-fault detection (used by uz_vsd_opf_6ph_faultdetection_step)
 * @param vsdcurrents uz_6ph_alphabeta_t struct, vsd currents of 6-phase system
 * @return uz_6phFD_indices fault indices for the six phases
 */
uz_6phFD_indices uz_vsd_opf_6ph_fault_indices_calculation(uz_6ph_alphabeta_t vsdcurrents);


/**
 * @brief Hysteresis filter function for the vsd open phase fault detection. Sets fault indices to zero if they are not in the hysteresis band bounded by the limits (used by uz_vsd_opf_6ph_faultdetection_step)
 * @param input fault indices, value is set to 0 if the value of the index is outside of the hysteresis band
 * @param upperlimit upper limit of hysteresis band
 * @param lowerlimit lower limit of hysteresis band
 * @return uz_6phFD_indices fault indices after filtering with the hysteresis band
 */
uz_6phFD_indices uz_vsd_fd_hysteresis_filter(uz_6phFD_indices input, float lowerlimit, float upperlimit);

/**
 * @brief Evaluates uz_6phFD_indices values with a threshold value (used by uz_vsd_opf_6ph_faultdetection_step)
 * @param input input fault indices
 * @param threshold value from which a fault index is judged as an error
 * @return uz_6phFD_indices fault indices set to 0 if fault index is below or set to 1 if fault index is above the threshold value
 */
uz_6phFD_indices uz_vsd_fd_evaluation(uz_6phFD_indices input, float threshold);




#endif //UZ_VSD_6PH_FD_H

