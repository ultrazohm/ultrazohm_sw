#ifndef UZ_ENCOFFEST_H
#define UZ_ENCOFFEST_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
#include "../../globalData.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_EncOffEst_config {
    actualValues *actual;       /**< Poitner to global data actual values */
    float polepair;             /**< Polepairs of maschine */
    float setpoint_current;     /**< Setpoint current for tests */
};

typedef struct uz_EncOffEst_t uz_EncOffEst_t;

/**
 * @brief Initialize an instance
 * 
 * @param config Config struct
 * @return uz_EncOffEst_t* Pointer to an initialized instance
 */
uz_EncOffEst_t* uz_EncOffEst_init(struct uz_EncOffEst_config);

/**
 * @brief Step the function
 * 
 * @param self Pointer to instance
 * @return setpoint for current controller
 */
uz_3ph_dq_t uz_EncOffEst_step(uz_EncOffEst_t* self);

/**
 * @brief Get finished flag
 * 
 * @param self Pointer to instance
 * @return finished flag
 */
bool uz_EncOffEst_get_finished(uz_EncOffEst_t* self);

#endif // UZ_ENCOFFEST_H
