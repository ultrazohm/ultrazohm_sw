#ifndef UZ_VSD_6PH_FD_H
#define UZ_VSD_6PH_FD_H


#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_movingAverageFilter/uz_movingAverageFilter.h"

/**
 * @brief struct for fault indices for 6ph Open-Phase-Fault-Detection
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
 * @param vsdcurrents uz_6ph_alphabeta_t struct, vsd currents of 6-phase system
 * @param upperlimit upper limit of hysteresis band
 * @param lowerlimit lower limit of hysteresis band
 * @param threshold value from which a fault index is judged as an error
 * @param mov_average_filter_length maximal length of moving average filter
 * @param sample_frequency_Hz sample frequency in Hz
 * @param percent_of_el_period desired filter length in percent of an electric period
 * @param omega_el_rad_per_sec omega_el in rad per seconds
 * @param movingAverageFilter_R1 moving average filter for phase 1
 * @param movingAverageFilter_R2 moving average filter for phase 2
 * @param movingAverageFilter_R3 moving average filter for phase 3
 * @param movingAverageFilter_R4 moving average filter for phase 4
 * @param movingAverageFilter_R5 moving average filter for phase 5
 * @param movingAverageFilter_R6 moving average filter for phase 6
 * @return uz_6phFD_indices fault indices for the six phases filtered and evaluated 
 */
uz_6phFD_indices uz_vsd_opf_6ph_faultdetection(uz_6ph_alphabeta_t vsdcurrents, float upperlimit, float lowerlimit, float threshold, uint32_t mov_average_filter_length, float sample_frequency_Hz, float percent_of_el_period, float omega_el_rad_per_sec, uz_movingAverageFilter_t* movingAverageFilter_R1, uz_movingAverageFilter_t* movingAverageFilter_R2, uz_movingAverageFilter_t* movingAverageFilter_R3, uz_movingAverageFilter_t* movingAverageFilter_R4, uz_movingAverageFilter_t* movingAverageFilter_R5, uz_movingAverageFilter_t* movingAverageFilter_R6 );



/**
 * @brief Function to calculate the fault indices (unfiltered) for 6-phase open-phase-fault detection
 * @param vsdcurrents uz_6ph_alphabeta_t struct, vsd currents of 6-phase system
 * @return uz_6phFD_indices fault indices for the six phases
 */
uz_6phFD_indices uz_vsd_opf_6ph_fault_indices_calculation(uz_6ph_alphabeta_t vsdcurrents);


/**
 * @brief hysteresis filter function for the vsd open phase fault detection procedure. values
 * @param input fault indices, value is set to 0 if the value of the index is outside of the hysteresis band
 * @param upperlimit upper limit of hysteresis band
 * @param lowerlimit lower limit of hysteresis band
 * @return uz_6phFD_indices fault indices after filtering with the hysteresis band
 *
 */
uz_6phFD_indices uz_vsd_fd_hysteresis_filter(uz_6phFD_indices input, float lowerlimit, float upperlimit);

/**
 * @brief evaluates uz_6phFD_indices values if bigger than threshold value, indicating open phase fault
 * @param input input fault indices
 * @param threshold value from which a fault index is judged as an error
 * @return uz_6phFD_indices fault indices set to 0 if no open phase or 1 if an open phase fault occurred in the corresponding phase
 */
uz_6phFD_indices uz_vsd_fd_evaluation(uz_6phFD_indices input, float threshold);




#endif //UZ_VSD_6PH_FD_H

