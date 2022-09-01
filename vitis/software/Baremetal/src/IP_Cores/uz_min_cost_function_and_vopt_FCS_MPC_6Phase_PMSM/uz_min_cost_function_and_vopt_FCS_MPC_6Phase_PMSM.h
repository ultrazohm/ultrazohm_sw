#ifndef UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_H
#define UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definitions of the output AXI_values for the MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM IP-Core driver
 * 
 */
typedef struct uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t{
    float d;    /**< Amplitude of the last applied optimal d-voltage */
    float q;    /**< Amplitude of the last applied optimal q-voltage */
    float x;    /**< Amplitude of the last applied optimal x-voltage */
    float y;    /**< Amplitude of the last applied optimal y-voltage */
}uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t;

/**
 * @brief Object data type definition of the MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM IP-Core driver
 *
 */
typedef struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t;

struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    _Bool use_AXI; /** true when AXI_values in use */
};

struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t{
    float J_in_AXI; /** Value of the actual cost function */
    int32_t Index_in_AXI; /** AXI-value of Index */
    float d_phase_voltage_per_switchimng_state_AXI; /** Value of the d-phase voltage per switching state for the corresponding cost function value */
    float q_phase_voltage_per_switchimng_state_AXI; /** Value of the q-phase voltage per switching state for the corresponding cost function value */
    float x_phase_voltage_per_switchimng_state_AXI; /** Value of the x-phase voltage per switching state for the corresponding cost function value */
    float y_phase_voltage_per_switchimng_state_AXI; /** Value of the y-phase voltage per switching state for the corresponding cost function value */
    _Bool valid_in_AXI; /** Valid flag to trigger the IP-Core */
};

/**
 * @brief Initialize an instance of the driver for the MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* Pointer to an initialized instance of the driver
 */
uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_init(struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config);

/** 
 * @brief Initialize AXI_values for J_in, Index_in, d_phase_voltage_per_switching_state, q_phase_voltage_per_switching_state, x_phase_voltage_per_switching_state, y_phase_voltage_per_switching_state and valid_in 
 * @param self Pointer to driver instance
 * @param AXI_values AXI values for the instance 
*/
void uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_set_AXI_values(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self, struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values);

/**
 * @brief Read the last applied optimal voltages d, q, x, y per switching state from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t
 */
uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self);

/**
 * @brief Read the done complete flag the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return _Bool
 */
_Bool uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_done_complete_AXI(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self);

/**
 * @brief Read the Index of the minimum of the cost function from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return int32_t
 */
int32_t uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_Index_out(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* self);

#endif // UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_H
