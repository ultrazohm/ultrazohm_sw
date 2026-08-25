#include "../include/d5_adapter_init.h"

/* Project Wizard BEGIN: D5 definitions */
/* Project Wizard generated content for D5 resolver IP channel 1 */
#include "xparameters.h"

static struct uz_resolverIP_config_t resolver_ip_d5_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_IP_D5_1_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .resolution = 16U,
    .freq_clockin = 8192000.0f,
    .zero_position_mechanical = 0.0f,
    .pole_pairs_machine = 4.0f,
    .pole_pairs_resolver = 1.0f,
    .mode_after_init = POSITION_VELOCITY_MODE
};

uz_resolverIP_t* initialize_resolver_ip_d5_1(void)
{
    return uz_resolverIP_init(resolver_ip_d5_1_config);
}
/* Project Wizard generated content for D5 resolver PL interface channel 1 */
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_resolver_pl_interface_config_t resolver_pl_interface_d5_1_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_PL_INTERFACE_D5_1_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .resolver_polepairs = 1,
    .machine_polepairs = 4,
    .position_intmax = 65535,
    .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
    .theta_m_offset_rad = -0.4f
};

static struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d5_1_outputs = {
    .revolution_counter = 0,
    .position_mech_2pi = 0.0f,
    .position_el_2pi = 0.0f,
    .omega_mech_rad_s = 0.0f,
    .n_mech_rpm = 0.0f
};

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_d5_1(void)
{
    return uz_resolver_pl_interface_init(
        resolver_pl_interface_d5_1_config,
        resolver_pl_interface_d5_1_outputs
    );
}
/* Project Wizard generated content for D5 resolver IP channel 2 */
#include "xparameters.h"

static struct uz_resolverIP_config_t resolver_ip_d5_2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_IP_D5_2_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .resolution = 16U,
    .freq_clockin = 8192000.0f,
    .zero_position_mechanical = 0.0f,
    .pole_pairs_machine = 4.0f,
    .pole_pairs_resolver = 1.0f,
    .mode_after_init = POSITION_VELOCITY_MODE
};

uz_resolverIP_t* initialize_resolver_ip_d5_2(void)
{
    return uz_resolverIP_init(resolver_ip_d5_2_config);
}
/* Project Wizard generated content for D5 resolver PL interface channel 2 */
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_resolver_pl_interface_config_t resolver_pl_interface_d5_2_config = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_RESOLVER_PL_INTERFACE_D5_2_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .resolver_polepairs = 1,
    .machine_polepairs = 4,
    .position_intmax = 65535,
    .bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
    .theta_m_offset_rad = -0.4f
};

static struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d5_2_outputs = {
    .revolution_counter = 0,
    .position_mech_2pi = 0.0f,
    .position_el_2pi = 0.0f,
    .omega_mech_rad_s = 0.0f,
    .n_mech_rpm = 0.0f
};

uz_resolver_pl_interface_t* initialize_resolver_pl_interface_d5_2(void)
{
    return uz_resolver_pl_interface_init(
        resolver_pl_interface_d5_2_config,
        resolver_pl_interface_d5_2_outputs
    );
}
/* Project Wizard END: D5 definitions */
