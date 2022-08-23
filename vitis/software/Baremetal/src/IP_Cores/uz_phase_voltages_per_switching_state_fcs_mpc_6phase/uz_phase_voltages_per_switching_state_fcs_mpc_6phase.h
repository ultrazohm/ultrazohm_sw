#ifndef UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_H
#define UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definitions of the output AXI_values for the PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE IP-Core driver
 * 
 */
typedef struct uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t{
    float d;    /**< Amplitude of the d-voltage for the corresponding switching state*/
    float q;    /**< Amplitude of the q-voltage for the corresponding switching state */
    float x;    /**< Amplitude of the x-voltage for the corresponding switching state */
    float y;    /**< Amplitude of the y-voltage for the corresponding switching state */
}uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t;

/**
 * @brief Object data type definition of the PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE IP-Core driver
 *
 */
typedef struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t;

struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_el_offset; /**< Offset of theta_el */
    float u_dc_link_voltage; /**< link voltage of the 6-Phase 2-level inverter */
    _BOOL use_AXI; /** true when AXI_values in use */
};

struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t{
    float theta_el_AXI; /** AXI-value of theta_el */
    int32_t Index_AXI; /** AXI-value of Index */
};

/**
 * @brief Initialize an instance of the driver for the PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* Pointer to an initialized instance of the driver
 */
uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t config);

/** 
 * @brief Initialize AXI_values for theta_el and Index
 * @param self Pointer to driver instance
 * @param AXI_values AXI values for the instance 
*/
void uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_AXI_values(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self, struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t AXI_values);

/**
 * @brief Read the output voltages d, q, x and y from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t
 */
uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* self);

#endif // UZ_PHASE_VOLTAGES_PER_SWITCHING_STATE_FCS_MPC_6PHASE_H
