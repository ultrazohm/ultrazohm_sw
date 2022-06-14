#include "../../uz/uz_global_configuration.h"
#if UZ_FCS_MPC_3PHASE_SPMSM_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_fcs_mpc_3phase_spmsm.h"
#include "uz_fcs_mpc_3phase_spmsm_hw.h"

struct uz_fcs_mpc_3phase_spmsm_t {
    bool is_ready;
    struct uz_fcs_mpc_3phase_spmsm_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_fcs_mpc_3phase_spmsm_t instances[UZ_FCS_MPC_3PHASE_SPMSM_MAX_INSTANCES] = { 0 };

static uz_fcs_mpc_3phase_spmsm_t* uz_fcs_mpc_3phase_spmsm_allocation(void);

static uz_fcs_mpc_3phase_spmsm_t* uz_fcs_mpc_3phase_spmsm_allocation(void){
    uz_assert(instance_counter < UZ_FCS_MPC_3PHASE_SPMSM_MAX_INSTANCES);
    uz_fcs_mpc_3phase_spmsm_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_fcs_mpc_3phase_spmsm_t* uz_fcs_mpc_3phase_spmsm_init(struct uz_fcs_mpc_3phase_spmsm_config_t config){
    uz_fcs_mpc_3phase_spmsm_t* self = uz_fcs_mpc_3phase_spmsm_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_zero_uint32(config.ip_clk_frequency_Hz);
    self->config = config;
    uz_fcs_mpc_3phase_spmsm_hw_set_u_dc_link(self->config.base_address, self->config.u_dc_link);
    uz_fcs_mpc_3phase_spmsm_hw_set_SampleTime(self->config.base_address, self->config.SampleTime);
    uz_fcs_mpc_3phase_spmsm_hw_set_Rs(self->config.base_address, self->config.Rs);
    uz_fcs_mpc_3phase_spmsm_hw_set_Ld(self->config.base_address, self->config.Ld);
    uz_fcs_mpc_3phase_spmsm_hw_set_Lq(self->config.base_address, self->config.Lq);
    uz_fcs_mpc_3phase_spmsm_hw_set_psiPM(self->config.base_address, self->config.psiPM);
    return (self);
}
#endif