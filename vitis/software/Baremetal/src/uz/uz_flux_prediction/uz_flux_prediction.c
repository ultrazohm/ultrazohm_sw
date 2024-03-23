#include "../uz_global_configuration.h"
#if UZ_FLUX_PREDICTION_MAX_INSTANCES > 0U
#include "flux_prediction_ert_rtw/flux_prediction.h"
#include "../uz_HAL.h"
#include "uz_flux_prediction.h"

struct uz_flux_prediction_t {
    bool is_ready;
    ExtY output;
    ExtU input;
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData;   
};

static uint32_t instance_counter = 0U;
static uz_flux_prediction_t instances[UZ_FLUX_PREDICTION_MAX_INSTANCES] = { 0 };

static uz_flux_prediction_t *uz_flux_prediction_allocation(void);

static uz_flux_prediction_t *uz_flux_prediction_allocation(void){
    uz_assert(instance_counter < UZ_FLUX_PREDICTION_MAX_INSTANCES);
    uz_flux_prediction_t *self = &instances[instance_counter];
    uz_assert(self->is_ready == false);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_flux_prediction_t* uz_flux_prediction_init(uz_PMSM_t config, float ts_regler, float omega_el){
    uz_flux_prediction_t* self = uz_flux_prediction_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    self->input.r_1 = config.R_ph_Ohm;
    self->input.omega_ell = omega_el;
    self->input.ts_regler = ts_regler;

    return(self);
}

uz_3ph_dq_t uz_flux_prediction_step(uz_flux_prediction_t* self, uz_3ph_dq_t i_actual_Ampere, uz_3ph_dq_t u_k0, uz_3ph_dq_t u_k1, uz_3ph_dq_t flux){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input.i_d=i_actual_Ampere.d;
    self->input.i_q=i_actual_Ampere.q;
    self->input.u_d_k0=u_k0.d;
    self->input.u_q_k0=u_k0.q;
    self->input.u_d_k1=u_k1.d;
    self->input.u_q_k1=u_k1.q;
    self->input.flux_d=flux.d;
    self->input.flux_q=flux.q;
    flux_prediction_step(self->PtrToModelData);
    uz_3ph_dq_t flux_pre = {0};
    flux_pre.d = self->output.flux_d_pre;
    flux_pre.q = self->output.flux_q_pre;
    return(flux_pre);
}
#endif
