#include "../uz_global_configuration.h"
#if UZ_APPROXIMATE_FLUX_MAX_INSTANCES > 0U
#include "approximate_flux_ert_rtw/approximate_flux.h"
#include "../uz_HAL.h"
#include "uz_approximate_flux.h"

struct uz_approximate_flux_t {
    bool is_ready;
    ExtY output;
    ExtU input;
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData;
    
};

static uint32_t instance_counter = 0U;
static uz_approximate_flux_t instances[UZ_APPROXIMATE_FLUX_MAX_INSTANCES] = { 0 };

static uz_approximate_flux_t *uz_approximate_flux_allocation(void);

static uz_approximate_flux_t *uz_approximate_flux_allocation(void){
    uz_assert(instance_counter < UZ_APPROXIMATE_FLUX_MAX_INSTANCES);
    uz_approximate_flux_t *self = &instances[instance_counter];
    uz_assert(self->is_ready == false);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_approximate_flux_t* uz_approximate_flux_init(uz_PMSM_flux_fitting_parameter_config_t fitting_config){
    uz_approximate_flux_t* self = uz_approximate_flux_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    self->input.fitting_parameters[0]=fitting_config.ad1_parameter;
    self->input.fitting_parameters[1]=fitting_config.ad2_parameter;
    self->input.fitting_parameters[2]=fitting_config.ad3_parameter;
    self->input.fitting_parameters[3]=fitting_config.ad4_parameter;
    self->input.fitting_parameters[4]=fitting_config.ad5_parameter;
    self->input.fitting_parameters[5]=fitting_config.ad6_parameter;
    self->input.fitting_parameters[6]=fitting_config.aq1_parameter;
    self->input.fitting_parameters[7]=fitting_config.aq2_parameter;
    self->input.fitting_parameters[8]=fitting_config.aq3_parameter;
    self->input.fitting_parameters[9]=fitting_config.aq4_parameter;
    self->input.fitting_parameters[10]=fitting_config.aq5_parameter;
    self->input.fitting_parameters[11]=fitting_config.aq6_parameter;
    self->input.fitting_parameters[12]=1/fitting_config.F1G1_parameter;
    self->input.fitting_parameters[13]=1/fitting_config.F2G2_parameter;
    self->input.fitting_parameters[14] = fitting_config.ad4_parameter*fitting_config.ad5_parameter;
    self->input.fitting_parameters[15] = fitting_config.ad1_parameter*fitting_config.ad2_parameter;
    self->input.fitting_parameters[16] = fitting_config.aq4_parameter*fitting_config.aq5_parameter;
    self->input.fitting_parameters[17] = fitting_config.aq1_parameter*fitting_config.aq2_parameter;
    self->input.fitting_parameters[18] = fitting_config.aq4_parameter/fitting_config.aq5_parameter;
    self->input.fitting_parameters[19] = fitting_config.aq1_parameter/fitting_config.aq2_parameter;
    self->input.fitting_parameters[20] = fitting_config.ad4_parameter/fitting_config.ad5_parameter;
    self->input.fitting_parameters[21] = fitting_config.ad1_parameter/fitting_config.ad2_parameter;
    self->input.fitting_parameters[22] = fitting_config.aq3_parameter-fitting_config.aq6_parameter;
    return(self);
}

uz_3ph_dq_t uz_approximate_flux_step(uz_approximate_flux_t* self, uz_3ph_dq_t i_actual_Ampere){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input.id=i_actual_Ampere.d;
    self->input.iq=i_actual_Ampere.q;
    approximate_flux_step(self->PtrToModelData);
    uz_3ph_dq_t flux_approx = {0};
    flux_approx.d = self->output.psid_approx;
    flux_approx.q = self->output.psiq_approx;
    return(flux_approx);
}

uz_3ph_dq_t uz_approximate_flux_reference_step(uz_approximate_flux_t* self, uz_3ph_dq_t i_reference_Ampere,uz_3ph_dq_t i_actual_Ampere){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //setting Function inputs to get flux_d_set
    self->input.id=i_reference_Ampere.d;
    self->input.iq=i_actual_Ampere.q;
    approximate_flux_step(self->PtrToModelData);
    uz_3ph_dq_t flux_reference_approx = {0};
    flux_reference_approx.d = self->output.psid_approx;
    //setting Function inputs to get flux_q_set
    self->input.id=i_actual_Ampere.d;
    self->input.iq=i_reference_Ampere.q;
    approximate_flux_step(self->PtrToModelData);
    flux_reference_approx.q = self->output.psiq_approx;
    return(flux_reference_approx);
}

#endif

