#include "../../uz/uz_global_configuration.h"
#if UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h"

struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t {
    bool is_ready;
    struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_config_t config;
    struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values;
};

static uint32_t instance_counter = 0U;
static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t instances[UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES] = { 0 };

static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_allocation(void);

static uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_allocation(void){
    uz_assert(instance_counter < UZ_MIN_COST_FUNCTION_AND_VOPT_FCS_MPC_6PHASE_PMSM_MAX_INSTANCES);
    uz_delay_compensation_fcs_mpc_6phase_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

#endif