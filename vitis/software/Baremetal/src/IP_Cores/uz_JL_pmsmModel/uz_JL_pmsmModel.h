
#ifndef UZ_JL_PMSMMODEL_H
#define UZ_JL_PMSMMODEL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object data type definition of the PMSM model IP-Core driver
 * 
 */
typedef struct uz_JL_pmsmModel_t uz_JL_pmsmModel_t;

/**
 * @brief Configuration struct for the JL PMSM model IP-Core driver
 * 
 */
struct uz_JL_pmsmModel_config_t
{
    uint32_t base_address; /**< Base address of the IP-Core instance to which thedriver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    float r_1; /**< Stator resistance in ohm */
    float L_d; /**< Direct inductance in Henry */
    float L_q; /**< Quadrature inductance in Henry */
    float psi_pm; /**< Linked magnetic flux of PM magnets */
    float mot_p; /**< Pole pairs of the PMSM */
    float mot_J; /**< Inertia of the PMSM */
    float mot_F;
    float mot_Fcoeff;
     float M_N;
     float n_N;
     float i_max;
};

/**
 * @brief Struct to return and read the outputs of the PMSM Model
 * 
 */
struct uz_JL_pmsmModel_outputs_t
{
    float i_a_A; /**< Current in d-axis in A */
    float i_b_A; /**< Current in q-Axis in A */
    float i_c_A; /**< Current in q-Axis in A */
    float phi_mech_rad; /**< Rotational angle of PMSM in rad*/
    float omega_mech_1_s; /**< Rotational speed of PMSM in 1/s*/
    float torque_Nm; /**< Inner torque of PMSM in Nm*/
};

/**
 * @brief Struct to be used to pass inputs to the PMSM Model
 * 
 */
struct uz_JL_pmsmModel_inputs_t
{
    bool bremse; /**< Select if PMSM is hold in stillstand */
    float Last_M; /**< Load torque in Nm */
    float Last_J; /**< Load inertia in kg/m^2 */
    bool SwitchUabc_dq;
    float Ud;
	float Uq;
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_pmsmModel_t* Pointer to an initialized instance of the driver
 */
uz_JL_pmsmModel_t *uz_JL_pmsmModel_init(struct uz_JL_pmsmModel_config_t config);


/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self 
 */
void uz_JL_pmsmModel_trigger_output_strobe(uz_JL_pmsmModel_t *self);

// void uz_JL_pmsmModel_trigger_input_strobe(uz_JL_pmsmModel_t *self);
/**
 * @brief Takes the values of the shadow register and pass them to the actual AXI register.
 * 
 * @param self Pointer to the instance
 * @param inputs Input values to set
 */
void uz_JL_pmsmModel_set_inputs(uz_JL_pmsmModel_t *self,struct uz_JL_pmsmModel_inputs_t inputs);

/**
 * @brief Returns current outputs of PMSM model IP-Core
 * 
 * @param self Pointer to driver instance
 * @return struct uz_pmsmModel_outputs_t Output values
 */
struct uz_JL_pmsmModel_outputs_t uz_JL_pmsmModel_get_outputs(uz_JL_pmsmModel_t *self);

/**
 * @brief Resets the PMSM model by writing zero to all inputs and sets integrators to zero
 * 
 * @param self Pointer to driver instance
 */
void uz_JL_pmsmModel_reset(uz_JL_pmsmModel_t *self);

#endif // UZ_JL_PMSMMODEL_H
