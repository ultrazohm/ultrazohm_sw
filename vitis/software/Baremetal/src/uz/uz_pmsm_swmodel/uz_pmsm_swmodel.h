#ifndef UZ_PMSM_SWMODEL_H
#define UZ_PMSM_SWMODEL_H

#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"

struct uz_pmsm_swmodel_config_t {
    float sample_time; /**< Sample time for the software model in seconds */
    struct uz_PMSM_t pmsm_parameters; /**< Configuration struct for PMSM parameters */
};

// Todo: delete the double definition as this is present in pmsmModel.h as well for the IP-Core.
struct uz_pmsm_swmodel_outputs_t
{
    float i_d_A;          /**< Current in d-axis in A */
    float i_q_A;          /**< Current in q-Axis in A */
    float torque_Nm;      /**< Inner torque of PMSM in Nm*/
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s*/
};

/**
 * @brief Struct to be used to pass inputs to the PMSM Model
 *
 */
struct uz_pmsm_swmodel_inputs_t
{
    float v_d_V;          /**< Voltage in d-axis in V */
    float v_q_V;          /**< Voltage in q-axis in V */
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s */
    float load_torque;    /**< Applied load torque in Nm */
};

typedef struct uz_pmsm_swmodel_t uz_pmsm_swmodel_t;

uz_pmsm_swmodel_t* uz_pmsm_swmodel_init(struct uz_pmsm_swmodel_config_t config);
struct uz_pmsm_swmodel_outputs_t uz_pmsm_swmodel_step(uz_pmsm_swmodel_t *self, struct uz_pmsm_swmodel_inputs_t inputs);

#endif // UZ_PMSM_SWMODEL_H
