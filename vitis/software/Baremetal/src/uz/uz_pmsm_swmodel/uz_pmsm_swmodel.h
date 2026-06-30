#ifndef UZ_PMSM_SWMODEL_H
#define UZ_PMSM_SWMODEL_H

#include <stdbool.h>

#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief Selects the numerical integration method used by the software model.
 */
enum uz_pmsm_swmodel_integration_method_t {
    uz_pmsm_swmodel_euler_forward = 0, /**< Explicit Euler (1st order). Default. */
    uz_pmsm_swmodel_heun               /**< Heun's method (explicit trapezoidal, 2nd order). */
};

/**
 * @brief Selects which quantity is used as the electrical integrator state.
 *
 * For a linear machine (constant inductances) both choices are equivalent; the flux
 * formulation matches the FPGA IP-core reference and is the basis for nonlinear flux maps.
 */
enum uz_pmsm_swmodel_integrator_state_t {
    uz_pmsm_swmodel_integrator_state_current = 0, /**< Integrate the dq currents (default). */
    uz_pmsm_swmodel_integrator_state_flux         /**< Integrate the dq flux linkages. */
};

struct uz_pmsm_swmodel_config_t {
    float sample_time; /**< Sample time for the software model in seconds */
    struct uz_PMSM_t pmsm_parameters; /**< Configuration struct for PMSM parameters */
    enum uz_pmsm_swmodel_integration_method_t integration_method; /**< Integration method (defaults to Euler forward) */
    enum uz_pmsm_swmodel_integrator_state_t integrator_state; /**< Electrical integrator state (defaults to current) */
    bool simulate_mechanical_system; /**< If true, integrate the mechanical speed from the torque balance; otherwise the input speed is passed through (default false) */
    float coulomb_friction_constant; /**< Coulomb friction torque in Nm (only used if simulate_mechanical_system) */
    float friction_coefficient; /**< Viscous friction coefficient in Nm*s (only used if simulate_mechanical_system) */
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
