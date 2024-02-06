#include "uz_pmsm_linear_rfe.h"

#include "../uz_global_configuration.h"
#if UZ_PMSM_LINEAR_RFE_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_pmsm_linear_rfe.h"
#include "../uz_integrator/uz_integrator.h"

struct uz_pmsm_linear_rfe_t
{
    bool is_ready;
    uz_3ph_dq_t i_k;
    float R;
    float ts;
    float psi_pm;
    float L_d;
    float L_q;
    float rfe_d;
    float rfe_q;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_linear_rfe_t instances[UZ_PMSM_LINEAR_RFE_MAX_INSTANCES] = {0};

static uz_pmsm_linear_rfe_t *uz_pmsm_linear_rfe_allocation(void);

static uz_pmsm_linear_rfe_t *uz_pmsm_linear_rfe_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_LINEAR_RFE_MAX_INSTANCES);
    uz_pmsm_linear_rfe_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pmsm_linear_rfe_t *uz_pmsm_linear_rfe_init(float R, float psi_pm,float L_d, float L_q, float rfe_d, float rfe_q, float ts)
{

    uz_pmsm_linear_rfe_t *self = uz_pmsm_linear_rfe_allocation();
    uz_assert(R > 0.0f);
    uz_assert(ts > 0.0f);
    uz_assert(L_d > 0.0f);
    uz_assert(L_q > 0.0f);
    uz_assert(rfe_q > 0.0f);
    uz_assert(rfe_d > 0.0f);
    uz_assert(psi_pm >= 0.0f);
    self->psi_pm=psi_pm;
    self->R = R;
    self->L_d = L_d;
    self->L_q = L_q;
    self->rfe_q = rfe_q;
    self->rfe_d = rfe_d;
    self->ts = ts;

    return (self);
}

uz_3ph_dq_t uz_pmsm_linear_rfe_step(uz_pmsm_linear_rfe_t *self, uz_3ph_dq_t v, float omega_el){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float id_dt=1.0f/self->L_d*(v.d - (self->R + ((self->L_d*self->L_q*omega_el*omega_el)/self->rfe_q) ) * self->i_k.d + omega_el*self->L_q * self->i_k.q - ( (self->L_q * omega_el * omega_el)/self->rfe_q )*self->psi_pm  );
    float iq_dt=1.0f/self->L_q*(v.q - (self->R + (self->L_d*self->L_q*omega_el*omega_el)/self->rfe_d)*self->i_k.q - omega_el*self->L_d*self->i_k.d - omega_el*self->psi_pm );
    self->i_k.d = uz_integrator_eulerforward(id_dt, self->i_k.d, self->ts, false);
    self->i_k.q = uz_integrator_eulerforward(iq_dt, self->i_k.q, self->ts, false);
    return self->i_k;
}

void uz_pmsm_linear_rfe_reset(uz_pmsm_linear_rfe_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->i_k.d = 0.0f;
    self->i_k.q = 0.0f;
}
#endif