#ifndef UZ_PMSM_SWMODEL_H
#define UZ_PMSM_SWMODEL_H

#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../../uz_Transformation/uz_Transformation.h"

struct uz_pmsm_swmodel_config_t {
    float sample_time; /**< Sample time for the software model in seconds */
    struct uz_PMSM_t pmsm_parameters; /**< Configuration struct for PMSM parameters */
};

struct uz_pmsm_swmodel_outputs_t
{
    uz_3ph_dq_t i_dq_A;   /**< Current in dq-frame in A */
    float torque_Nm;      /**< Inner torque of PMSM in Nm*/
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s*/
};

/**
 * @brief Struct to be used to pass inputs to the PMSM Model
 *
 */
struct uz_pmsm_swmodel_inputs_t
{
    uz_3ph_dq_t v_dq_V;   /**< Voltage in dq-frame in V */
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s */
    float load_torque;    /**< Applied load torque in Nm */
};

typedef struct uz_pmsm_swmodel_t uz_pmsm_swmodel_t;

uz_pmsm_swmodel_t* uz_pmsm_swmodel_init(struct uz_pmsm_swmodel_config_t config);

/**
 * @brief Facilitates one integration step of the PMSM model.
 * 
 * @param self Pointer to instance
 * @param inputs Inputs of the current integration step k=0
 * @return struct uz_pmsm_swmodel_outputs_t Output values at k=1
 */
struct uz_pmsm_swmodel_outputs_t uz_pmsm_swmodel_step(uz_pmsm_swmodel_t *self, struct uz_pmsm_swmodel_inputs_t inputs);

/*
 * @brief Resets the PMSM software model, i.e., sets all internal states to zero
 * @param self Pointer to the PMSM software model instance
 */
void uz_pmsm_swmodel_reset(uz_pmsm_swmodel_t *self);

#endif // UZ_PMSM_SWMODEL_H
